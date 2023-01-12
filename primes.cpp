// Author: Raciel Antela Pardo
// Date: 1-11-2023

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

const int MAX_NUM = 100000000;
const int MAX_THREADS = 8; // Total threads used
const int MAIN_THREADS = MAX_THREADS * 2 / 3; // Thread count used for most of the work
const int MAIN_THREADS_STEP_MULTIPLIER = 3;

// Writes the following to a primes.txt file:
// <execution time>  <total number of primes found>  <sum of all primes found>
// <top ten maximum primes, listed in order from lowest to highest>
void writeToFile(vector<int> primes, int64_t durationMs) {
    ofstream f;
    f.open("primes.txt");
    vector<int> topPrimes;
    uint64_t primesSum = 0;
    uint64_t primesCount = 0;

    for (int i = MAX_NUM; i >= 2; i--) {
        if (primes[i]) {
            if (topPrimes.size() < 10) {
                topPrimes.push_back(i);
            }
            primesSum += i;
            primesCount++;
        }
    }

    f << durationMs << "ms " << primesCount << " " << primesSum << endl;
    for (int i = 9; i >= 0; i--) {
        f << topPrimes[i] << " ";
    }
    f << endl;
    f.close();
}

// Sets to false all composite numbers in the primes array
void markComposite(vector<int> &primes, uint64_t start, uint64_t end) {
    auto startTimer = chrono::high_resolution_clock::now();
    for (uint64_t i = start; i <= end; i++) {
        if (primes[i]) {
            for (uint64_t j = i * 2; j <= MAX_NUM; j += i) {
                primes[j] = 0;
            }
        }
    }
}

int main() {
    vector<int> primes(MAX_NUM + 1, 1);
    auto sqrtMaxNum = uint64_t(sqrt(MAX_NUM));

    // Spawn 8 threads to mark composite numbers
    vector<thread> threads;
    uint64_t prevChunkEnd = 2;
    auto startTimer = chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_THREADS; i++) {
        // Assign a larger thread count to the smaller multiples (as there are more of them) for better performance
        if (i < MAIN_THREADS) {
            auto nextChunk = prevChunkEnd * MAIN_THREADS_STEP_MULTIPLIER;
            auto end = nextChunk < sqrtMaxNum ? nextChunk : sqrtMaxNum;

            threads.emplace_back(markComposite, ref(primes), prevChunkEnd, end);
            prevChunkEnd = end;
        } else {
            auto chunkSize = (sqrtMaxNum - prevChunkEnd) / (MAX_THREADS - MAIN_THREADS);
            auto start = prevChunkEnd + (i - MAIN_THREADS) * chunkSize;
            auto end = start + chunkSize;

            threads.emplace_back(markComposite, ref(primes), start, end);
        }
    }
    for (auto &t: threads) {
        t.join();
    }
    auto endTimer = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(endTimer - startTimer);

    cout << "Finished finding primes in " << duration.count() << "ms" << endl;
    cout << "Writing to file..." << endl;

    writeToFile(primes, duration.count());

    cout << "Done!" << endl;
}
