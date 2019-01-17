#ifndef GRAFY_GRAF_H
#define GRAFY_GRAF_H

#include <cstddef>

class Graph {

private:
    class Node {
    public:
        size_t Vertex;
        Node* next;

        Node(int Vertex, Node* next= nullptr ): Vertex(Vertex), next(next)
        {}
    };
    Node** table;
    size_t graph_size;
    bool* visited;
    void deepSearch(int v);

public:
    Graph();

    ~Graph();

    Graph(Node** table, size_t size);

    void createGraph();

    void findBridge();

    void clear();

    bool isEmpty();
};
#endif //GRAFY_GRAF_H
