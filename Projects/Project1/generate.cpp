#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <direct.h>

int main() {
    std::string folder_path = "./datasets";

    // if (mkdir("./datasets") == -1) {
    //     std::cerr << "Error creating directory" << std::endl;
    //     return 1;
    // }

    srand(time(nullptr));

    for (int size = 5; size <= 10000000; size += 5) {
        std::vector<int> random_data;
        random_data.reserve(size);

        for (int i = 1; i <= size; ++i) {
            random_data.push_back(i);
        }

        // Shuffle the data randomly
        for (int i = size - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            std::swap(random_data[i], random_data[j]);
        }

        std::string filename = folder_path + "/" + std::to_string(size) + ".txt";
        std::ofstream file(filename);

        if (!file) {
            std::cerr << "Error creating file: " << filename << std::endl;
            return 1;
        }

        for (int num : random_data) {
            file << num << ",";
        }

        file.close();
    }

    return 0;
}



