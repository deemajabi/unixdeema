#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

void applyKernel(const vector<vector<int>>& image, vector<vector<int>>& newImage, const vector<vector<int>>& kernel, int rows, int cols) {
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            int sum = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sum += image[i + k][j + l] * kernel[k + 1][l + 1];
                }
            }
            newImage[i][j] = sum;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: <input_image> <kernel_file> <output_image>" << endl;
        return 1;
    }

    ifstream inputImageFile(argv[1]);
    ifstream kernelFile(argv[2]);
    ofstream outputImageFile(argv[3]);

    int rows, cols;
    inputImageFile >> rows >> cols;

    vector<vector<int>> image(rows, vector<int>(cols));
    vector<vector<int>> newImage(rows, vector<int>(cols));
    vector<vector<int>> kernel(3, vector<int>(3));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inputImageFile >> image[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            kernelFile >> kernel[i][j];
        }
    }

    auto start = chrono::high_resolution_clock::now();

    applyKernel(image, newImage, kernel, rows, cols);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Execution Time (Serial): " << duration.count() << " seconds" << endl;

    outputImageFile << rows << " " << cols << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outputImageFile << newImage[i][j] << " ";
        }
        outputImageFile << endl;
    }

    return 0;
}

