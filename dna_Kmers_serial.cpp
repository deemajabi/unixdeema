#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

void countKmersSerial(const std::string &sequence, int k, std::unordered_map<std::string, int> &kmer_counts) {
    for (int i = 0; i <= sequence.size() - k; i++) {
        std::string kmer = sequence.substr(i, k);
        kmer_counts[kmer]++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <dna_sequence_file> <k>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    int k = std::atoi(argv[2]);

    std::string dna_sequence;
    std::ifstream file(filename);
    if (file) {
        dna_sequence.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::unordered_map<std::string, int> kmer_counts;
    countKmersSerial(dna_sequence, k, kmer_counts);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Serial execution time: " << duration.count() << " seconds" << std::endl;

    // طباعة نتائج k-mer counts
    std::cout << "K-mer counts:\n";
    for (const auto &entry : kmer_counts) {
        std::cout << entry.first << " : " << entry.second << "\n";
    }

    return 0;
}
