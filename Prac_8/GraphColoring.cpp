#include <iostream>
using namespace std;

#define V 5  // change to 5 for Graph 2
// for second graph change v 6 to V 5

bool isSafe(int v, bool graph[V][V], int color[], int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}

bool graphColoringUtil(bool graph[V][V], int m, int color[], int v) {
    if (v == V)
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;
            color[v] = 0;
        }
    }
    return false;
}

void findMinColoring(bool graph[V][V]) {
    int color[V] = {0};

    int minColors = 1;
    while (true) {
        if (graphColoringUtil(graph, minColors, color, 0))
            break;
        minColors++;
    }

    cout << "Minimum colors required: " << minColors << endl;
    cout << "Color assigned to each vertex:\n";
    for (int i = 0; i < V; i++)
        cout << "Vertex " << i + 1 << " ---> Color " << color[i] << endl;
}

int main() {
    // ---------------------
    //  Graph 1 (6 vertices)
    // bool graph[V][V] = {
    //     {0, 1, 1, 0, 1, 0},
    //     {1, 0, 1, 1, 0, 0},
    //     {1, 1, 0, 0, 1, 0},
    //     {0, 1, 0, 0, 1, 1},
    //     {1, 0, 1, 1, 0, 1},
    //     {0, 0, 0, 1, 1, 0}
    // };

    //  Graph 2 (5 vertices – complete graph)
    
    
    bool graph[V][V] = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}
    };
    

    findMinColoring(graph);

    return 0;
}
