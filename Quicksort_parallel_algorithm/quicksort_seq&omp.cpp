#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <random>

// C++11/14: Use chrono for timing
double timeSum(const std::vector<double>& timeVec) {
    double sum = std::accumulate(timeVec.begin(), timeVec.end(), 0.0);
    return sum / timeVec.size();
}

// C++11: Use std::swap instead of custom swap
int partition(std::vector<int>& vec, int l, int h) {
    int pivot = vec[h];
    int i = l - 1;
    
    for (int j = l; j <= h - 1; ++j) {
        if (vec[j] <= pivot) {
            ++i;
            if (i != j) {
                std::swap(vec[i], vec[j]);
            }
        }
    }
    
    std::swap(vec[i + 1], vec[h]);
    return i + 1;
}

void quicksortWhile(std::vector<int>& vec, int l, int h) {
    int i = l;
    int j = h;
    int pivot = vec[(l + h) >> 1];  // Bit shift for divide by 2
    
    do {
        while (vec[i] < pivot) ++i;
        while (vec[j] > pivot) --j;
        if (i <= j) {
            std::swap(vec[i++], vec[j--]);
        }
    } while (i <= j);
    
    if (l < j) quicksortWhile(vec, l, j);
    if (h > i) quicksortWhile(vec, i, h);
}

void quicksortFor(std::vector<int>& vec, int l, int h) {
    if (l < h) {
        int p = partition(vec, l, h);
        quicksortFor(vec, l, p - 1);
        quicksortFor(vec, p + 1, h);
    }
}

void quicksortForOpt(std::vector<int>& vec, int l, int h) {
    std::vector<int> stack;  // C++11: Use vector instead of raw array
    stack.reserve(h - l + 1);
    
    stack.push_back(l);
    stack.push_back(h);
    
    while (!stack.empty()) {
        h = stack.back(); stack.pop_back();
        l = stack.back(); stack.pop_back();
        
        int p = partition(vec, l, h);
        
        if (p - 1 > l) {
            stack.push_back(l);
            stack.push_back(p - 1);
        }
        
        if (p + 1 < h) {
            stack.push_back(p + 1);
            stack.push_back(h);
        }
    }
}

void quicksortParallel(std::vector<int>& vec) {
    constexpr int num_threads = 4;
    int div = vec.size() / num_threads;
    std::vector<std::vector<int>> vecVec;
    vecVec.reserve(num_threads);
    
    for (int i = 0; i < num_threads; ++i) {
        vecVec.emplace_back(vec.begin() + div * i, 
                           vec.begin() + div * (i + 1));
    }
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            quicksortForOpt(vecVec[0], 0, vecVec[0].size() - 1);
        }
        #pragma omp section
        {
            quicksortForOpt(vecVec[1], 0, vecVec[1].size() - 1);
        }
        #pragma omp section
        {
            quicksortForOpt(vecVec[2], 0, vecVec[2].size() - 1);
        }
        #pragma omp section
        {
            quicksortForOpt(vecVec[3], 0, vecVec[3].size() - 1);
        }
    }
    
    std::vector<int> temp1(vec.size() / 2);
    std::vector<int> temp2(vec.size() / 2);
    
    std::merge(vecVec[0].begin(), vecVec[0].end(), 
               vecVec[1].begin(), vecVec[1].end(), temp1.begin());
    std::merge(vecVec[2].begin(), vecVec[2].end(), 
               vecVec[3].begin(), vecVec[3].end(), temp2.begin());
    std::merge(temp1.begin(), temp1.end(), 
               temp2.begin(), temp2.end(), vec.begin());
}

int main() {
    constexpr int n = 50;   // Number of repetitions
    constexpr int s = 500;  // Array size
    constexpr int m = 1024; // Max random value
    
    std::vector<double> time1(n), time2(n), time3(n), time4(n), time5(n);
    std::vector<int> vec(s);
    
    // C++11: Better random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m - 1);
    std::generate(vec.begin(), vec.end(), [&]() { return dist(gen); });
    
    auto vec1(vec);  // Copy for std::sort
    
    // Benchmark std::sort
    for (int i = 0; i < n; ++i) {
        auto start = std::chrono::high_resolution_clock::now();
        std::sort(vec1.begin(), vec1.end());
        auto end = std::chrono::high_resolution_clock::now();
        time1[i] = std::chrono::duration<double>(end - start).count();
        vec1 = vec;  // Reset
    }
    
    // Benchmark while-loop quicksort
    for (int i = 0; i < n; ++i) {
        auto vec2 = vec;
        auto start = std::chrono::high_resolution_clock::now();
        quicksortWhile(vec2, 0, vec2.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        time2[i] = std::chrono::duration<double>(end - start).count();
    }
    
    // Benchmark for-loop quicksort
    for (int i = 0; i < n; ++i) {
        auto vec3 = vec;
        auto start = std::chrono::high_resolution_clock::now();
        quicksortFor(vec3, 0, vec3.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        time3[i] = std::chrono::duration<double>(end - start).count();
    }
    
    // Benchmark optimized quicksort
    for (int i = 0; i < n; ++i) {
        auto vec4 = vec;
        auto start = std::chrono::high_resolution_clock::now();
        quicksortForOpt(vec4, 0, vec4.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        time4[i] = std::chrono::duration<double>(end - start).count();
    }
    
    // Benchmark parallel quicksort
    for (int i = 0; i < n; ++i) {
        auto vec5 = vec;
        auto start = std::chrono::high_resolution_clock::now();
        quicksortParallel(vec5);
        auto end = std::chrono::high_resolution_clock::now();
        time5[i] = std::chrono::duration<double>(end - start).count();
    }
    
    std::cout << "\n=== Quicksort Performance Comparison ===\n";
    std::cout << "Array size: " << s << " | Repetitions: " << n << "\n\n";
    std::cout << "1. std::sort                    : " << timeSum(time1) << " seconds\n";
    std::cout << "2. While-loop quicksort         : " << timeSum(time2) << " seconds\n";
    std::cout << "3. For-loop quicksort           : " << timeSum(time3) << " seconds\n";
    std::cout << "4. Optimized iterative quicksort: " << timeSum(time4) << " seconds\n";
    std::cout << "5. OpenMP parallel quicksort    : " << timeSum(time5) << " seconds\n\n";
    
    return 0;
}
