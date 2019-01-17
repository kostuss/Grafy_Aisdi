#include <iostream>
#include <fstream>
#include "Graf.h"

int main() {

    Graph other;
    other.createGraph();
    other.findBridge();
    other.clear();
    return 0;
}