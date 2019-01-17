#include <iostream>
#include <fstream>
#include <string>
#include "Graf.h"

Graph::Graph() =default;

Graph::~Graph() =default;

Graph::Graph(Graph::Node **table, size_t size): table(table), graph_size(size)
{}

void Graph::createGraph()
{
    std::string input;
    std::cout << "Give the input file: " ;
    std::cin >> input;
    std::ifstream myfile (input);

    if(myfile.is_open())
    {
        myfile>> graph_size;
        if(graph_size==0) { return;}
        table = new Node* [graph_size] {nullptr};
        int a, b;
        while (myfile>>a && myfile>>b)
        {
           Node* nodeA= new Node(a, table[b]);
           Node* nodeB= new Node(b, table[a]);
           table[b]=nodeA;
           table[a]=nodeB;
        }
        getchar();

    }else {
        throw std::runtime_error ("Unable to open file");
    }

}
void Graph::clear() {
    if (graph_size!=0) {
        size_t i;
        Node *temporary;
        Node *helper;
        for (i = 0; i != graph_size; i++) {
            temporary = table[i];
            while (temporary != nullptr) {
                helper = temporary;
                temporary = temporary->next;
                delete helper;
            }
        }
        delete[] table;
    }
    graph_size=0;
    table= nullptr;
    visited= nullptr;
}

void Graph::findBridge() {

    if (isEmpty()) {
        std::cout << "This graph is empty" << std::endl;
    } else {
        //controlTab= new bool[graph_size]; //
        visited = new bool[graph_size];
        size_t tableindex;
        Node *listindex;
        for (tableindex = 0; tableindex != graph_size; tableindex++) {
            for (listindex = table[tableindex]; listindex != nullptr; listindex = listindex->next) {
                if (listindex->Vertex < tableindex) continue;  // no to repeat removing  A B edge and B A edge
                for (size_t i = 0; i != graph_size; i++) {
                    visited[i] = false;
                }
                visited[tableindex] = true;
                visited[listindex->Vertex] = true;

                if (tableindex == 0 && listindex->Vertex == 1) deepSearch(2);
                else if (tableindex == 0) deepSearch(1);
                else deepSearch(0);

                for (size_t i = 0; i != graph_size; i++) {
                    if (!visited[i]) {
                        std::cout << "Bridge found from " << tableindex << " to " << listindex->Vertex << std::endl;
                        break;
                    }
                }
            }
        }
        delete[] visited;
    }
}

void Graph::deepSearch(int v) {
    Node* temporary;
    visited[v]= true;

    for (temporary=table[v]; temporary!= nullptr; temporary=temporary->next) {
        if (!visited[temporary->Vertex]) deepSearch(temporary->Vertex);
    }
}

bool Graph::isEmpty() {
    return graph_size==0;
}
