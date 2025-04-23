#include <iostream>
#include <queue>
using namespace std;

const int V = 5; // Number of nodes (landmarks)
int adjList[V][V];
int adjMatrix[V][V] = {
                        {0, 1, 0, 1, 0}, // College Building -> Library, Sports Complex
                        {1, 0, 1, 0, 1}, // Library -> College Building, Cafeteria, Hostel
                        {0, 1, 0, 1, 1}, // Cafeteria -> Library, Sports Complex, Hostel
                        {1, 0, 1, 0, 1}, // Sports Complex -> College Building, Cafeteria, Hostel
                        {0, 1, 1, 1, 0}}; // Hostel -> Library, Cafeteria, Sports Complex

// Landmark names array
string landmarks[V] = {"College Building", "Library", "Cafeteria", "Sports Complex", "Hostel"};

// DFS using adjacency matrix
void DFS(int node, bool visited[]) {
    cout << landmarks[node] << " ";
    visited[node] = true; // value 1
    for (int i = 0; i < V; i++) {
        if (adjMatrix[node][i] == 1 && visited[i] != 1) {
            DFS(i, visited);
        }
    }
}

// BFS using adjacency list
void BFS(int startNode) {
    bool visited[V] = {false};
    queue<int> q;
    visited[startNode] = true;
    q.push(startNode);

    while (q.empty() != true) {
        int node = q.front();
        q.pop();
        cout << landmarks[node] << " ";
        for (int i = 0; i < V; i++) {
            if (adjList[node][i] == 1 && visited[i] != 1) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

// Function to convert adjacency matrix to adjacency list for BFS
void convertMatrixToList() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (adjMatrix[i][j] == 1) {
                adjList[i][j] = 1;
            }
        }
    }
}

int main() {
    bool visited[V] = {false};

    cout << "DFS using Adjacency Matrix (starting from College Building):- \n";
    DFS(0, visited);  // Start DFS from College Building (node 0)
    cout << endl;

    // Convert adjacency matrix to adjacency list for BFS
    convertMatrixToList();

    cout << "BFS using Adjacency List (starting from College Building):- \n";
    BFS(0);  // Start BFS from College Building (node 0)
    cout << endl;

    // Print adjacency matrix and adjacency list for clarity
    cout << "\nAdjacency Matrix (for DFS):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nAdjacency List (for BFS):\n";
    for (int i = 0; i < V; i++) {
        cout << landmarks[i] << ": ";
        for (int j = 0; j < V; j++) {
            if (adjList[i][j] == 1) {
                cout << landmarks[j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
