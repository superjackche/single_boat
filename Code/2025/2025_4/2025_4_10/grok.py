import json
import random
from datasets import load_dataset, DatasetDict

# Function to filter out non-ASCII characters from text
def filter_non_ascii(text):
    return ''.join([char for char in text if ord(char) < 128])

# Function to remove duplicate entries from a dataset
def remove_duplicates(data):
    seen = set()
    unique_data = []
    for item in data:
        item_str = json.dumps(item, sort_keys=True)
        if item_str not in seen:
            seen.add(item_str)
            unique_data.append(item)
    return unique_data

# Function for stratified sampling based on labels (if present)
def stratified_sample(dataset, n_samples):
    dataset_list = [dict(item) for item in dataset]  # Convert to list of dicts
    if 'label' in dataset.features:
        labels = dataset['label']
        unique_labels = list(set(labels))
        label_counts = {label: labels.count(label) for label in unique_labels}
        total_samples = len(dataset)
        samples_per_label = {label: min(int(n_samples * (count / total_samples)), count) 
                            for label, count in label_counts.items()}
        
        sampled_data = []
        for label in unique_labels:
            label_data = [item for item in dataset_list if item.get('label') == label]
            sampled_data.extend(random.sample(label_data, samples_per_label[label]))
        
        return sampled_data
    else:
        return random.sample(dataset_list, min(n_samples, len(dataset_list)))

# Function to process a single dataset
def process_dataset(dataset_name, dataset_link):
    try:
        # Load dataset from Hugging Face
        dataset = load_dataset(dataset_link.replace("https://hf-mirror.com/datasets/", ""))
        
        # Handle DatasetDict or single dataset
        if isinstance(dataset, DatasetDict):
            train_data = dataset.get('train', None)
            test_data = dataset.get('test', None)
        else:
            train_data = dataset
            test_data = None
        
        # Skip if no train or test data is available
        if not train_data:
            print(f"Dataset {dataset_name} has no training data. Skipping.")
            return
        if not test_data:
            test_data = train_data  # Use train data for test if no test split exists
        
        # Convert to list of dictionaries and filter non-ASCII characters
        train_data_list = [{k: filter_non_ascii(v) if isinstance(v, str) else v 
                           for k, v in item.items()} for item in train_data]
        test_data_list = [{k: filter_non_ascii(v) if isinstance(v, str) else v 
                          for k, v in item.items()} for item in test_data]
        
        # Remove duplicates
        train_data_list = remove_duplicates(train_data_list)
        test_data_list = remove_duplicates(test_data_list)
        
        # Ensure no crossover between train and test
        train_data_set = set(json.dumps(item, sort_keys=True) for item in train_data_list)
        test_data_list = [item for item in test_data_list 
                         if json.dumps(item, sort_keys=True) not in train_data_set]
        
        # Sample training and test sets
        if len(train_data_list) > 3000:
            train_sample = stratified_sample(train_data, 3000)
        else:
            train_sample = random.sample(train_data_list, min(3000, len(train_data_list)))
        
        if len(test_data_list) > 200:
            test_sample = stratified_sample(test_data, 200)
        else:
            test_sample = random.sample(test_data_list, min(200, len(test_data_list)))
        
        # Format into the requested JSON structure (example-based)
        formatted_train = [{"instruction": item.get("instruction", ""), 
                           "input": item.get("input", ""), 
                           "output": item.get("output", "")} 
                          for item in train_sample]
        formatted_test = [{"instruction": item.get("instruction", ""), 
                          "input": item.get("input", ""), 
                          "output": item.get("output", "")} 
                         for item in test_sample]
        
        # Save to JSON files
        with open(f"{dataset_name}_train.json", 'w', encoding='utf-8') as f:
            json.dump(formatted_train, f, indent=4, ensure_ascii=False)
        with open(f"{dataset_name}_test.json", 'w', encoding='utf-8') as f:
            json.dump(formatted_test, f, indent=4, ensure_ascii=False)
        
        print(f"Processed {dataset_name} successfully: {len(formatted_train)} train, {len(formatted_test)} test samples.")
    
    except Exception as e:
        print(f"Error processing {dataset_name}: {str(e)}")

# Main function to read JSON and process all datasets
def main():
    with open('D:/Code/single_boat/Code/2025/2025_4/2025_4_7/nlp.json', 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    for dataset in data['datasets']:
        name = dataset['name']
        link = dataset['link']
        process_dataset(name, link)

if __name__ == "__main__":
    main()