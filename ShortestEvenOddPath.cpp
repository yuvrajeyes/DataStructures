#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

const int INF = INT_MAX;

struct Node {
    int vertex, distance;
    Node(int v, int d) : vertex(v), distance(d) {}
};

void shortest_even_odd_path(int n, vector<vector<int>>& adj, int s) {
    vector<int> d0(n, INF), d1(n, INF);
    queue<Node> q;

    d0[s] = 0;
    q.push(Node(s, 1));

    while (!q.empty()) {
        Node current = q.front();
        q.pop();
        int v = current.vertex;
        int t = current.distance;

        for (int w : adj[v]) {
            if (t % 2 == 0 && d0[w] == INF) {
                d0[w] = t;
                q.push(Node(w, t + 1));
            } else if (t % 2 != 0 && d1[w] == INF) {
                d1[w] = t;
                q.push(Node(w, t + 1));
            }
        }
    }

    cout << "Even distance from source " << s << " to each node:\n";
    for (int i = 0; i < n; ++i) {
        if (d0[i] == INF) {
            cout << "Node " << i << ": INF\n";
        } else {
            cout << "Node " << i << ": " << d0[i] << "\n";
        }
    }

    cout << "\nOdd distance from source " << s << " to each node:\n";
    for (int i = 0; i < n; ++i) {
        if (d1[i] == INF) {
            cout << "Node " << i << ": INF\n";
        } else {
            cout << "Node " << i << ": " << d1[i] << "\n";
        }
    }
}

int main() {
    int n = 5;  // Number of nodes
    vector<vector<int>> adj(n);

    adj[0] = {1, 2, 3};
    adj[1] = {0, 2, 4};
    adj[2] = {0, 1};
    adj[3] = {0, 4};
    adj[4] = {1, 3};

    int s = 0; // Source node
    shortest_even_odd_path(n, adj, s);

    return 0;
}
