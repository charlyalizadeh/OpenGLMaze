#include "../include/MazeGenerator.hpp"

template<typename Iter, typename RandomGenerator>
Iter static select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter static select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

std::vector<int> getUnvisitedNeighbor(int v, const std::vector<bool>& visited, int width, int height) {
    std::vector<int> adjacentVertex;
    int dim;

    dim = width * height;

    // UP
    if(v - width > 0 && v - width < dim && !visited[v - width])
        adjacentVertex.push_back(v - width);
    // DOWN
    if(v + width > 0 && v + width < dim && !visited[v + width])
        adjacentVertex.push_back(v + width);
    // LEFT
    if(v % width != 0 && !visited[v - 1])
        adjacentVertex.push_back(v - 1);
    // RIGHT
    if((v + 1) % width != 0 && !visited[v + 1])
        adjacentVertex.push_back(v + 1);
    return adjacentVertex;
}

std::vector<int> dfs(int width, int height) {
    std::vector<int> path;
    int ncell;
    std::vector<bool> visited;
    std::stack<int> S;
    std::random_device dev;
    std::mt19937 rng(dev());

    ncell = width * height;
    for(size_t i = 0; i < ncell; i++) {
        visited.push_back(false);
    }
    std::uniform_int_distribution<std::mt19937::result_type> distNcell(0, ncell);
    int v = distNcell(rng);
    S.push(v);
    visited[v] = true;
    while(!S.empty()) {
        v = S.top();
        S.pop();
        auto neighbors = getUnvisitedNeighbor(v, visited, width, height);
        if(!neighbors.empty()) {
            S.push(v);
            int n = *select_randomly(neighbors.begin(), neighbors.end());
            path.push_back(v);
            path.push_back(n);
            visited[n] = true;
            S.push(n);
        }
    }
    return path;
}
