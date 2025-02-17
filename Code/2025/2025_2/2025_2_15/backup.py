with open("d:/Code/single_boat/Code/2025/2025_2/2025_2_15/冷雨夜.txt", "r", encoding="UTF-8") as f1:
    with open("d:/Code/single_boat/Code/2025/2025_2/2025_2_15/冷雨夜backup.txt", "w", encoding="UTF-8") as f2:
        for row in f1:
            if row != '\n':
                f2.write(row)