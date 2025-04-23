// Represent a given graph using adjacency matrix to find length of shortest path between every pair of
// vertices. Use Floyd Warshall's algorithm to implement it.
#include <iostream>
#include <algorithm>
using namespace std;
#define v 5
#define INF 99999

void printSolution(int dist[][v]) {
	for(int i = 0; i < v; i++) {
		for(int j = 0; j < v; j++){
		if(dist[i][j] == INF) {
			cout << "INF";
		} else {
			cout << dist[i][j] << " ";
		}
	}
	cout << endl;
	}
}

void floydWarshall(int dist[][v]) {
	int i,j,k;
	for(k = 0; k < v; k++){
		for(i = 0; i < v; i++){
			for(j = 0; j < v; j++){
				dist[i][j] = min(dist[i][j],(dist[i][k] + dist[k][j]));
			}
		}
	}
	printSolution(dist);
}

int main() {
int graph[v][v] = {
        {0, 4, INF, 5, INF},
        {INF, 0, 1, INF, 6},
        {2, INF, 0, 3, INF},
        {INF, INF, 1, 0, 2},
        {1, INF, INF, 4, 0}
    };
    floydWarshall(graph);
    return 0;
}