#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>
#include <random>
#include <mpi.h>

// Modern C++11/14: constexpr functions for index calculation
constexpr int calcBeginIndex(int vecSize, int myRank, int numOfProc) {
    return vecSize * myRank / numOfProc;
}

constexpr int calcEndIndex(int vecSize, int myRank, int numOfProc) {
    return vecSize * (myRank + 1) / numOfProc;
}

using itVec = std::vector<int>::iterator;

int main(int argc, char* argv[]) {
    constexpr int root = 0;
    constexpr int size = 20;
    constexpr int m = 1000;
    int numOfProc;
    int myRank;
    double clockTime;
    std::vector<int> vec(size);
    
    // C++11: Use better random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m - 1);
    std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numOfProc);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    
    // Check initial conditions
    if (myRank == 0 && (size < std::pow(numOfProc, 2) || numOfProc == 1)) {
        std::cout << "Initial condition not fulfilled! ";
        std::cout << "Size must be >= num_processes^2\n";
        MPI_Finalize();
        return 0;
    }
    
    if (myRank == 0) {
        std::cout << "Available processors: " << numOfProc << "\n"
                  << "\nArray before sort:\n\t";
        for (const auto& val : vec) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    
    int indexBegin = calcBeginIndex(size, myRank, numOfProc);
    int indexEnd = calcEndIndex(size, myRank, numOfProc);
    int lenSum = 0;

    itVec iterBegin = vec.begin() + indexBegin;
    itVec iterEnd   = vec.begin() + indexEnd;

    std::vector<int> regularSamples(numOfProc);
    std::vector<int> privots(numOfProc-1);
    std::vector<int> sendLength(numOfProc);
    std::vector<int> sendIndex(numOfProc);
    std::vector<int> recvLength(numOfProc);
    std::vector<int> recvIndex(numOfProc);
    std::vector<int> gatherVec(size);
    std::vector<int> partVec(iterBegin, iterEnd);
    std::vector<int> gatherRegSamples;

    clockTime = MPI_Wtime();

    std::sort(partVec.begin(), partVec.end());

    for (int i = 0; i < numOfProc; i++)
    {
        regularSamples[i] = *(iterBegin + (i * size / pow(numOfProc, 2))-1);
    }

    if (myRank == root)
    {
        gatherRegSamples.resize(pow(numOfProc, 2));
    }

    MPI_Gather(regularSamples.data(), numOfProc, MPI_INT,
            gatherRegSamples.data(), numOfProc, MPI_INT,
            root, MPI_COMM_WORLD);

    if (myRank == root)
    {
        std::sort(gatherRegSamples.begin(), gatherRegSamples.end());

        for (int i = 0; i < numOfProc-1; i++)
        {
            privots[i] = gatherRegSamples[(i+1)*numOfProc];
        }
    }

    MPI_Bcast(privots.data(), numOfProc, MPI_INT, root, MPI_COMM_WORLD);

    auto j = 0u;
    for (int i = 0; i<numOfProc-1; i++)
    {
        sendIndex[i] = j;
        sendLength[i] = 0;

        while((j < partVec.size()) && (partVec[j] <= privots[i]))
        {
            j++;
            sendLength[i]++;
        }
    }
    sendIndex[numOfProc-1] = j;
    sendLength[numOfProc-1] = partVec.size() - j;

    MPI_Alltoall(sendLength.data(), 1, MPI_INT,
                 recvLength.data(), 1, MPI_INT,
                 MPI_COMM_WORLD);

    for (int i = 0; i < numOfProc; i++)
    {
        recvIndex[i] = lenSum;
        lenSum += recvLength[i];
    }
    std::vector<int> recvVec(lenSum);

    MPI_Alltoallv(partVec.data(), sendLength.data(), sendIndex.data(), MPI_INT,
                 recvVec.data(), recvLength.data(), recvIndex.data(), MPI_INT,
                 MPI_COMM_WORLD);

    std::sort(recvVec.begin(), recvVec.end());

    auto count = lenSum;
    MPI_Gather(&count, 1, MPI_INT,
            recvLength.data(), 1, MPI_INT,
            root, MPI_COMM_WORLD);

    lenSum = 0;
    for (int i = 0; i < numOfProc; i++)
    {
        recvIndex[i] = lenSum;
        lenSum += recvLength[i];
    }

    MPI_Gatherv(recvVec.data(), count, MPI_INT,
            vec.data(), recvLength.data(), recvIndex.data(), MPI_INT,
            root, MPI_COMM_WORLD);

    clockTime = MPI_Wtime() - clockTime;
    
    if (myRank == root) {
        std::cout << "\nArray after sort:\n\t";
        for (const auto& val : vec) {
            std::cout << val << " ";
        }
        std::cout << "\n\nProcessing time: " << clockTime << " seconds\n";
    }
    
    MPI_Finalize();
    return 0;
}
