// Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform
// BFS. Use the map of the area around the college as the graph. Identify the prominent land marks as
// nodes and perform DFS and BFS on that.
#include <iostream>     
#include <stack>        // For DFS stack
#include <queue>        // For BFS queue
using namespace std;    

const int MAX = 10;     
struct Node { // Structure to represent a node in the adjacency list
    int vertex;
    Node* next;
};

class Graph {
private:
    int n;
    Node* adj_list[MAX] = {nullptr}; // Array of pointers to head nodes of adjacency list
    bool visited[MAX];             // Array to track visited nodes for DFS/BFS

    void add_edge(int src, int dest) {
        Node* newNode = new Node{dest, nullptr}; // Create new node with dest as vertex
        if (adj_list[src] == nullptr) {
            // If no edge exists from src, make this the first edge
            adj_list[src] = newNode;
        } else {
            Node* temp = adj_list[src];
            while (temp->next) temp = temp->next; // Traverse to last node
            temp->next = newNode;
        }
    }

    void reset() {
        for (int i = 0; i < MAX; i++)
            visited[i] = false;
    }

public:
    void create_graph();
    void dfs(int start);
    void bfs(int start);
};

void Graph::create_graph() {
    cout << "Enter number of vertices: ";
    cin >> n;
    char reply; 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) continue; // Skip self-loops
            cout << "Are vertices " << i << " and " << j << " adjacent? (Y/N): ";
            cin >> reply;
            if (reply == 'Y' || reply == 'y') {
                add_edge(i, j); // Add edge from i to j
            }
        }
    }
}

void Graph::dfs(int start) {
    reset();          // Mark all vertices as unvisited
    stack<int> s;             // Stack for DFS
    s.push(start);            // Start from the given vertex
    cout << "DFS Traversal: ";
    while (!s.empty()) {
        int curr = s.top();   // Get top of stack
        s.pop();              // Remove it from stack
        if (!visited[curr]) { // If not already visited
            cout << curr << " ";    // Print it
            visited[curr] = true;   // Mark as visited
        }
        for (Node* temp = adj_list[curr]; temp; temp = temp->next) {// Push all unvisited adjacent vertices
            if (!visited[temp->vertex]) {
                s.push(temp->vertex);
            }
        }
    }
    cout << endl;
}

void Graph::bfs(int start) {
    reset();          // Mark all vertices as unvisited
    queue<int> q;             // Queue for BFS
    q.push(start);            // Start from the given vertex
    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int curr = q.front(); // Get front of queue
        q.pop();              // Remove it from queue
        if (!visited[curr]) { // If not already visited
            cout << curr << " ";    // Print it
            visited[curr] = true;   // Mark as visited
        }
        for (Node* temp = adj_list[curr]; temp; temp = temp->next) {// Enqueue all unvisited adjacent vertices
            if (!visited[temp->vertex]) {
                q.push(temp->vertex);
            }
        }
    }
    cout << endl;
}

int main() {
    Graph g;
    g.create_graph();
    int start;
    cout << "\nEnter starting vertex for DFS: ";
    cin >> start;
    g.dfs(start);
    cout << "Enter starting vertex for BFS: ";
    cin >> start;
    g.bfs(start);
    return 0;
}