#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

struct Student {
    std::string name;
    int studentNumber;
};

void addRecord(const std::string &dataFile, const std::string &indexFile, const Student &student) {
    std::ofstream dataOut(dataFile, std::ios::app);  
    std::ofstream indexOut(indexFile, std::ios::app);

    if (!dataOut || !indexOut) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    dataOut << student.studentNumber << "," << student.name << std::endl;

    indexOut << student.studentNumber << "," << dataOut.tellp() - (student.name.length() + 1 + std::to_string(student.studentNumber).length()) << std::endl;

    dataOut.close();
    indexOut.close();
}

void retrieveRecord(const std::string &dataFile, const std::string &indexFile, int studentNumber) {
    std::ifstream indexIn(indexFile);
    std::ifstream dataIn(dataFile);

    if (!indexIn || !dataIn) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }

    std::unordered_map<int, long> indexMap;
    std::string line;
    
    while (std::getline(indexIn, line)) {
        std::istringstream iss(line);
        int key;
        long position;
        char delimiter;
        if (iss >> key >> delimiter >> position) {
            indexMap[key] = position;
        }
    }

    auto it = indexMap.find(studentNumber);
    if (it != indexMap.end()) {
        long position = it->second;

        dataIn.seekg(position);
        std::getline(dataIn, line);
        std::cout << "Record found: " << line << std::endl;
    } else {
        std::cout << "Record not found!" << std::endl;
    }

    indexIn.close();
    dataIn.close();
}

int main() {
    std::string dataFile = "data.txt";
    std::string indexFile = "index.txt";

    Student student1 = {"Jalal Khalid", 12345};
    Student student2 = {"Jana Ahmed", 67890};

    addRecord(dataFile, indexFile, student1);
    addRecord(dataFile, indexFile, student2);

    int searchNumber = 12345;
    retrieveRecord(dataFile, indexFile, searchNumber);

    return 0;
}
