import random
import numpy as np

sizes = np.logspace(3, 7, num=50, dtype=int)
for size in sizes:
    random_data = random.sample(range(1, size + 1), size)
    filename = f"{size}.txt"

    with open(filename, "w") as file:
        for num in random_data:
            file.write(str(num) + ",")
