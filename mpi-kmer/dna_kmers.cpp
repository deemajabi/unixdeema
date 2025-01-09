#include <mpi.h>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <string>

void countKmers(const std::string& sequence, int k, int start, int end, std::unordered_map<std::string, int>& kmer_counts) {
    for (int i = start; i <= end - k; i++) {
        std::string kmer = sequence.substr(i, k);
        kmer_counts[kmer]++;
    }
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 3) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " <dna_sequence_file> <k>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    std::string filename = argv[1];
    int k = std::atoi(argv[2]);

    std::string dna_sequence;
    if (rank == 0) {
        std::ifstream file(filename);
        if (file) {
            dna_sequence.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        }
        else {
            std::cerr << "Error opening file: " << filename << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    int dna_length;
    if (rank == 0) {
        dna_length = dna_sequence.size();
    }
    MPI_Bcast(&dna_length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank != 0) {
        dna_sequence.resize(dna_length);
    }
    MPI_Bcast(&dna_sequence[0], dna_length, MPI_CHAR, 0, MPI_COMM_WORLD);

    int chunk_size = dna_length / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? dna_length - 1 : (start + chunk_size + k - 1);

    std::unordered_map<std::string, int> local_kmer_counts;
    countKmers(dna_sequence, k, start, end, local_kmer_counts);

    std::unordered_map<std::string, int> global_kmer_counts;
    if (rank == 0) {
        global_kmer_counts = local_kmer_counts;

        for (int i = 1; i < size; i++) {
            int recv_size;
            MPI_Recv(&recv_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < recv_size; j++) {
                std::vector<char> kmer(k + 1);
                int count;
                MPI_Recv(kmer.data(), k + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&count, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                global_kmer_counts[std::string(kmer.data())] += count;
            }
        }
    }
    else {
        int send_size = local_kmer_counts.size();
        MPI_Send(&send_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        for (const auto& entry : local_kmer_counts) {
            MPI_Send(entry.first.c_str(), k + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&entry.second, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        std::cout << "K-mer counts:\n";
        for (const auto& entry : global_kmer_counts) {
            std::cout << entry.first << " : " << entry.second << "\n";
        }
    }

    MPI_Finalize();
    return 0;
}

