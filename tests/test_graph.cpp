#include <gtest/gtest.h>
#include "../lib_graph/graph.h"

std::vector<std::pair<std::pair<int, int>, int>> graph = {
    {{1, 4}, 1}, {{1, 2}, 1},
    {{4, 6}, 1}, {{4, 2}, 1},
    {{6, 3}, 1}, {{2, 3}, 1},
    {{2, 5}, 1}, {{3, 0}, 1},
    {{5, 0}, 1}
};

std::vector<std::pair<std::pair<int, int>, int>> edges = {
    {{1, 2}, 5},
    {{2, 3}, 2},
    {{1, 5}, 4},
    {{3, 7}, 1},
    {{5, 6}, 3},
    {{6, 7}, 6},
    {{3, 5}, 2}
};

TEST(GraphListTest, print) {
    GraphList<int> g(graph, false);
    g.print();
}

TEST(GraphListTest, path) {
    GraphList<int> g(edges, false);
    std::vector<int> path = g.dijkstra(Vertex(1), Vertex(7));

    for (int i = 0; i < (int)path.size(); i++) {
        if (i < path.size() - 1) std::cout << path[i] << " -> ";
        else std::cout << path[i];
    }
    std::cout << std::endl;
}