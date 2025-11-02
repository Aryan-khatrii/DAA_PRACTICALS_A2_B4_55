#include <iostream>
using namespace std;

#define V 5   // Number of vertices in each graph


bool isSafe(int v, bool graph[V][V], int path[], int pos) {
    // ch-if vertex adjacent    
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Ch if vertex exist al
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

// Recursive fn
bool hamCycleUtil(bool graph[V][V], int path[], int pos) {
    // Base case
    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        return false;
    }

        //Differetn path
    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            
            if (hamCycleUtil(graph, path, pos + 1))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }
    return false;
}


bool hamCycle(bool graph[V][V], string names[V]) {
    int path[V];
    for (int i = 0; i < V; i++)
        path[i] = -1;

    
    path[0] = 0;

    
    if (!hamCycleUtil(graph, path, 1)) {
        cout << "No Hamiltonian Cycle exists for this route.\n";
        return false;
    }

    
    cout << "Hamiltonian Cycle found:\n";
    for (int i = 0; i < V; i++)
        cout << names[path[i]] << " -> ";
    cout << names[path[0]] << endl;

    return true;
}


int main() {
    //  Graph 1: A B C D E 
    bool graph1[V][V] = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };

    string names1[V] = {"A", "B", "C", "D", "E"};

    cout << "For Graph 1 (Areas A - E):\n";
    hamCycle(graph1, names1);

   

    //  Graph 2: T M S H C 
    bool graph2[V][V] = {
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0}
    };

    string names2[V] = {"T", "M", "S", "H", "C"};

    cout << "For Graph 2 (Areas T - M - S - H - C):\n";
    hamCycle(graph2, names2);

    return 0;
}
