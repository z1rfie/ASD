#ifndef LIB_GRAPH
#define LIB_GRAPH

#include <iostream>
#include "../lib_list/list.h"
#include <vector>
#include "../lib_priority_queue/priority_queue.h"

#define INF 10000

struct Vertex {
	int id;
	Vertex(int id) : id(id) {}
	bool operator==(const Vertex& other) const { return id == other.id; }
};

struct Edge {
	Vertex first;
	Vertex second;
	int weight;
	Edge(Vertex f, Vertex s, int w = 1) : first(f), second(s), weight(w) {}
};

template<class T>
class GraphList {
	std::vector<std::pair<Vertex, std::list<std::pair<int, int>>>> adjacency_list;
	bool _is_directed;
	bool _is_weighted;
public:
	GraphList(std::vector<std::pair<std::pair<T, T>, int>> graph, bool directed = false);
	void add_edge(Vertex, Vertex, int);
	void delete_edge(Edge);
	void delete_vertex(Vertex);

    void print() const;

    int size() const;
    bool is_directed() const;
    bool is_weighted() const;
    int get_vertex_id(int index) const { return adjacency_list[index].first.id; }

    std::vector<int> dijkstra(Vertex start, Vertex finish);
private:
    int find_vertex(const Vertex& v) const;
    int ensure_vertex(const Vertex& v);
    std::list<std::pair<int, int>>& get_neighbors(int index);
};

template<class T>
GraphList<T>::GraphList(std::vector<std::pair<std::pair<T, T>, int>> graph, bool directed) : _is_directed(directed) {
	adjacency_list.reserve(graph.size() * 2);

	_is_weighted = false;
	for (int i = 0; i < graph.size(); i++) {
		if (graph[i].second != 1) { _is_weighted = true; break; }
	}

	for (int i = 0; i < graph.size(); i++) {
		add_edge(Vertex(graph[i].first.first), Vertex(graph[i].first.second), graph[i].second);
	}
}

template<class T>
void GraphList<T>::add_edge(Vertex v1, Vertex v2, int w) {
    int i1 = ensure_vertex(v1);
    int i2 = ensure_vertex(v2);

    adjacency_list[i1].second.push_back({ i2, w });
    if (!_is_directed) adjacency_list[i2].second.push_back({ i1, w });
}

template<class T>
void GraphList<T>::delete_edge(Edge e) {
    int i1 = find_vertex(e.first);
    int i2 = find_vertex(e.second);
    if (i1 == -1 || i2 == -1) return;

    for (auto it = adjacency_list[i1].second.begin(); it != adjacency_list[i1].second.end(); ++it) {
        if (it->first == i2) { adjacency_list[i1].second.erase(it); break; }
    }

    if (!is_directed) {
        for (auto it = adjacency_list[i2].second.begin(); it != adjacency_list[i2].second.end(); ++it) {
            if (it->first == i1) {
                adjacency_list[i2].second.erase(it); break;
            }
        }
    }
}

template<class T>
void GraphList<T>::delete_vertex(Vertex v) {
    int idx = find_vertex(v);
    if (idx == -1) return;

    adjacency_list.erase(adjacency_list.begin() + idx);

    for (int i = 0; i < adjacency_list.size(); i++) {
        for (auto it = adjacency_list[i].second.begin(); it != adjacency_list[i].second.end(); ) {
            if (it->first == idx)
                it = adjacency_list[i].second.erase(it);
            else {
                if (it->first > idx) it->first--;
                ++it;
            }
        }
    }
}

template<class T>
void GraphList<T>::print() const {
    for (int i = 0; i < adjacency_list.size(); i++) {
        std::cout << adjacency_list[i].first.id << " -> ";
        for (auto it = adjacency_list[i].second.begin(); it != adjacency_list[i].second.end(); ++it) {
            std::cout << "(" << adjacency_list[it->first].first.id;
            if (_is_weighted) std::cout << ", w=" << it->second;
            std::cout << ") ";
        }
        std::cout << std::endl;
    }
}

template<class T>
int GraphList<T>::size() const { return adjacency_list.size();  }

template<class T>
bool GraphList<T>::is_directed() const { return _is_directed; }

template<class T>
bool GraphList<T>::is_weighted() const { return _is_weighted; }

template<class T>
int GraphList<T>::find_vertex(const Vertex& v) const {
    for (int i = 0; i < adjacency_list.size(); i++) {
        if (adjacency_list[i].first == v) return i;
    }
    return -1;
}

template<class T>
int GraphList<T>::ensure_vertex(const Vertex& v) {
    int idx = find_vertex(v);
    if (idx == -1) {
        adjacency_list.push_back({ v, {} });
        idx = adjacency_list.size() - 1;
    }
    return idx;
}

template<class T>
std::list<std::pair<int, int>>& GraphList<T>::get_neighbors(int index) {
    return adjacency_list[index].second;
}

template<class T>
std::vector<int> GraphList<T>::dijkstra(Vertex start, Vertex finish) {
    int total_vertices = size();
    int start_index = find_vertex(start);
    int finish_index = find_vertex(finish);

    if (start_index == -1 || finish_index == -1) {
        return std::vector<int>();
    }

    std::vector<int> best_distance(total_vertices, INF);
    std::vector<int> previous_vertex(total_vertices, -1);
    best_distance[start_index] = 0;

    PriorityQueue<int> queue;
    queue.push(start_index, INF - best_distance[start_index]);

    while (!queue.is_empty()) {
        int current_index = queue.pop();
        int current_distance = best_distance[current_index];

        if (current_index == finish_index) break;

        std::list<std::pair<int, int>>& neighbors = get_neighbors(current_index);
        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            int neighbor_index = it->first;
            int edge_weight = _is_weighted ? it->second : 1;
            int new_distance = current_distance + edge_weight;

            if (new_distance < best_distance[neighbor_index]) {
                best_distance[neighbor_index] = new_distance;
                previous_vertex[neighbor_index] = current_index;
                queue.push(neighbor_index, INF - new_distance);
            }
        }
    }

    if (best_distance[finish_index] == INF) {
        return std::vector<int>();
    }

    std::vector<int> path;
    for (int vertex = finish_index; vertex != -1; vertex = previous_vertex[vertex]) {
        path.push_back(get_vertex_id(vertex));
    }

    for (int i = 0, j = path.size() - 1; i < j; i++, j--) {
        std::swap(path[i], path[j]);
    }

    return path;
}

#endif  // LIB_GRAPH
