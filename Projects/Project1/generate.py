import os
import random
import numpy as np

folder_path = "./datasets"

if not os.path.exists(folder_path):
    os.makedirs(folder_path)

sizes = np.logspace(3, 7, num=50, dtype=int)

for size in sizes:
    random_data = random.sample(range(1, size + 1), size)
    filename = os.path.join(folder_path, f"{size}.txt") 

    with open(filename, "w") as file:
        for num in random_data:
            file.write(str(num) + ",")