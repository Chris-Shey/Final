#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <sstream>
#include <string>
#define INF std::numeric_limits<int>::max()

//Function display adjaceny matrix
void displayMatrix(const std::vector<std::vector<int>>& matrix) {
    std::cout << "Adjacency Matrix:\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == INF)
                std::cout << "INF\t";
            else
                std::cout << val << "\t";
        }
        std::cout << "\n";
    }
}
//Function calculates trip costs
int calculateTripCost(const std::vector<int>& path, const std::vector<std::vector<int>>& graph) {
    int totalCost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        int cost = graph[path[i]][path[i + 1]];
        if (cost == INF) return INF;
        totalCost += cost;
    }
    return totalCost;
}
//Function find all different trips and costs
void findTrips(const std::vector<std::vector<int>>& graph, int startNode) {
    int n = graph.size();
    std::vector<int> cities;
    for (int i = 0; i < n; ++i) {
        if (i != startNode) cities.push_back(i);
    }
    int minCost = INF;
    std::vector<int> bestPath;
    std::cout << "\nAll possible trips and their costs:\n";
    do {
        std::vector<int> path = { startNode };
        path.insert(path.end(), cities.begin(), cities.end()); //No returning to start

        int cost = calculateTripCost(path, graph);
        std::cout << "Path: ";
        for (int city : path) std::cout << city << " ";
        std::cout << " | Cost: " << (cost == INF ? "INF" : std::to_string(cost)) << "\n";

        if (cost < minCost) {
            minCost = cost;
            bestPath = path;
        }
    } while (std::next_permutation(cities.begin(), cities.end()));

    std::cout << "\nShortest (most cost-efficent) trip: \nPath: ";
    for (int city : bestPath) std::cout << city << " ";
    std::cout << "| Total Cost: " << minCost << "\n";
}
int main() {
    //0 = Rivers, 1 = Moreno Valley, 2 = Perris, 3 = Hemet 
    std::vector<std::vector<int>> graph = {
      {0, 16, 24, 33}, //Riverside (0)
      {16, 0, 18, 26}, //Moreno Valley (1)
      {24, 18, 0, 30}, //Perris (2)
      {33, 26, 30, 0}, //Hemet (3)
    };
    //Display adjaceny matric
    displayMatrix(graph);

    //Start from Riverside
    findTrips(graph, 0);
    return 0;
}
