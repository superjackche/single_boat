import time

# w模式下，如果文件不存在，则创建该文件；文件存在，则清空该文件重新创建。
with open("d:/Code/single_boat/Code/2025/2025_2/2025_2_4/第三人称.txt", "w", encoding="UTF-8") as f:
    f.write("你好.再见啦再见啦~")
    # f.close()     close()自带flush()功能