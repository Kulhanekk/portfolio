//
// Created by ASUS on 30.09.2026.
//

#include "DifferenceComputation.h"
#include <algorithm>
#include <iostream>
#include <ostream>
#include <vector>

void computeDifference(const std::vector<std::vector<int> > &records,
std::vector<std::vector<int> > &differences) {
    const long long n = records.size();
    differences.assign(n, std::vector<int>(n, 0));

#pragma omp parallel
    {
        std::vector<int> prev;
        std::vector<int> curr;

#pragma omp for schedule(dynamic, 1)
        for (long long i = 0; i < n; ++i) {
            for (long long j = i + 1; j < n; ++j) {
                const auto &a = records[i];
                const auto &b = records[j];
                const size_t la = a.size();
                const size_t lb = b.size();

                prev.assign(lb + 1, 0);
                curr.assign(lb + 1, 0);
                for (size_t c = 0; c <= lb; ++c) {
                    prev[c] = (int)c;
                }

                for (size_t r = 1; r <= la; ++r) {
                    curr[0] = (int)r;
                    for (size_t c = 1; c <= lb; ++c) {
                        int cost = (a[r - 1] != b[c - 1]) ? 1 : 0;
                        curr[c] = std::min({prev[c] + 1,
                                            curr[c - 1] + 1,
                                            prev[c - 1] + cost});
                    }
                    std::swap(prev, curr);
                }

                int d = prev[lb];
                differences[i][j] = d;
                differences[j][i] = d;
            }
        }
    }
}

void printDifferences(const std::vector<std::vector<int> > &differences) {
    std::cout << "\n--- Edit Differences Adjacency Matrix ---\n";
    std::cout << "     ";

    size_t n = differences.size();

    // Print column headers
    for (size_t j = 0; j < n; ++j) {
        std::cout << "Rec " << j << "\t";
    }
    std::cout << "\n";

    // Print rows
    for (size_t i = 0; i < n; ++i) {
        std::cout << "Rec " << i << ": ";
        for (size_t j = 0; j < n; ++j) {
            std::cout << differences[i][j] << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "----------------------------------------\n";
}

void computeDifferenceSeq(const std::vector<std::vector<int>> &records, std::vector<std::vector<int>> &differences) {
    size_t n = records.size();
    differences.assign(n, std::vector<int>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (j <= i) {
                continue;
            }
            const auto &record_a = records[i];
            const auto &record_b = records[j];

            auto len_a = record_a.size();
            auto len_b = record_b.size();

            std::vector<std::vector<int> > temp_sums(len_a + 1, std::vector<int>(len_b + 1, 0));

            for (size_t r = 0; r <= len_a; ++r) {
                temp_sums[r][0] = r;
            }

            for (size_t c = 0; c <= len_b; ++c) {
                temp_sums[0][c] = c;
            }

            for (size_t r = 1; r <= len_a; ++r) {
                for (size_t c = 1; c <= len_b; ++c) {
                    int cost = 0;
                    if (record_a[r - 1] != record_b[c - 1]) {
                        cost = 1;
                    }
                    temp_sums[r][c] = std::min({
                        temp_sums[r - 1][c] + 1,
                        temp_sums[r][c - 1] + 1,
                        temp_sums[r - 1][c - 1] + cost
                    });
                }
            }

            differences[i][j] = temp_sums[len_a][len_b];
            differences[j][i] = differences[i][j];
        }
    }
}
