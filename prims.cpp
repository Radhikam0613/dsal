// You have a business with several offices; you want to lease phone lines to
// connect them up with each other; and the phone company charges different
// amounts of money to connect different pairs of cities. You want a set of lines that
// connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures

// class:-
    // input
    // display
    // minimum
#include<iostream>
#include<climits> // Include to use INT_MAX for representing infinity in graphs
using namespace std;

class tree {
    int adjMatrix[100][100], visited[100], V, E; 
    public:
        void input();  
        void display();
        void minimum();
};

void tree::input() {
    cout << "Enter the number of offices (vertices):- ";
    cin >> V;    
    for (int i = 0; i < V; i++) { // Initialize the adjacency matrix with 0
        for (int j = 0; j < V; j++) {
            adjMatrix[i][j] = 0; 
        }
    }
    cout << "Enter the number of connections (edges):- ";
    cin >> E;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cout << "Enter the start office, end office, and cost of the connection:- ";
        cin >> u >> v >> w;  // u, v represent office numbers, w is the cost of the connection
        adjMatrix[u - 1][v - 1] = adjMatrix[v - 1][u - 1] = w;  // As the graph is undirected, set both directions
    }
}

void tree::display() {
    cout << "\nAdjacency matrix:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void tree::minimum() {
    int totalCost = 0, minCost, u = 0, v = 0;
    visited[0] = 1;
    for (int count = 0; count < (V - 1); count++) {
        minCost = INT_MAX;
        for (int i = 0; i < V; i++) {
            if (visited[i] == 1) {
                for (int j = 0; j < V; j++) {
                    if (visited[j] == 0 && adjMatrix[i][j] != 0) {
                        if (adjMatrix[i][j] < minCost) {
                            minCost = adjMatrix[i][j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }
        }
        visited[v] = 1;
        totalCost += minCost;
        cout << "Minimum cost connection: " << (u + 1) << " -> " << (v + 1) << " with charge: " << minCost << endl;
    }
    cout << "Minimum total cost of connections: " << totalCost << endl;
}

int main() {
    tree t;
    t.input();
    t.display();
    t.minimum();
    return 0;
}
