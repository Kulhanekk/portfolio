//
// Created by ASUS on 01.10.2026.
//

#include "primsAlg.h"

#include <algorithm>
#include <climits>
#include <queue>

int calculateMstValue(std::vector<std::vector<int> > &graph) {
    const int size = graph.size();
    if (size == 0) return 0;

    int total = 0;
    std::vector<int> key(size, INT_MAX);
    std::vector<bool> visited(size, false);
    key[0] = 0;

    for (int count = 0; count < size; count++) {
        // find the closest unvisited vertex
        int min = INT_MAX;
        int min_idx = -1;

#pragma omp parallel
{

        int local_min = INT_MAX;
        int local_min_idx = -1;

#pragma omp for nowait
        for (int i = 0; i < size; i++) {
            if (!visited[i] && key[i] < local_min) {
                local_min = key[i];
                local_min_idx = i;
            }
        }

#pragma omp critical
{
        if (local_min_idx != -1 && (min == -1 || local_min < min)) {
            min = local_min;
            min_idx = local_min_idx;
        }
}

}

        visited[min_idx] = true;
        total += key[min_idx];

#pragma omp parallel for
        for (int v = 0; v < size; v++) {
            if (!visited[v] && graph[min_idx][v] < key[v]) {
                key[v] = graph[min_idx][v];
            }
        }
    }
    return total;
}

int calculateMstValueSeq(std::vector<std::vector<int> > &graph) {
    int n = graph.size();

    using P = std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P> > pq;
    std::vector<bool> visited(n, false);

    int total = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        total += w;

        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                pq.push({graph[u][v], v});
            }
        }
    }
    return total;
}
