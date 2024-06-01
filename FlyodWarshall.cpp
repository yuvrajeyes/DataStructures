#include<bits/stdc++.h>
using namespace std;

const int MAXN = 4;
const int INF = 1e9; // Define infinity as a large value
// int d[MAXN][MAXN] = {INF};   // Distance matrix
int d[MAXN][MAXN] = {{0, 3, INF, 5},
                    {2, 0, INF, 4},
                    {INF, 1, 0, INF},
                    {INF, INF, 2, 0}};;
int p[MAXN][MAXN];   // Ancestor matrix

void floydWarshall(int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] < INF && d[k][j] < INF) {
                    if (d[i][j] > d[i][k] + d[k][j]) {
                        d[i][j] = d[i][k] + d[k][j];
                        p[i][j] = p[k][j];
                    }
                }
            }
        }
    }
}

void initializeMatrices(int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && d[i][j] < INF)
                p[i][j] = i;
            else
                p[i][j] = -1;
        }
    }
}

void printPath(int i, int j) {
    if (i != j)
        printPath(i, p[i][j]);
    cout << j << " ";
}

int main() {
    int n = 4;

    // Initialize the ancestor matrix
    initializeMatrices(n);

    // Run the Floyd-Warshall algorithm
    floydWarshall(n);

    // Now you can reconstruct the path from vertex `u` to vertex `v` like this:
    int u = 0, v = 2; // Example vertices
    if (d[u][v] < INF) {
        cout << "Shortest path from " << u << " to " << v << ": ";
        printPath(u, v);
        cout << endl;
    } else {
        cout << "No path exists from " << u << " to " << v << endl;
    }

    return 0;
}

