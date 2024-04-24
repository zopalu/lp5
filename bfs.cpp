#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];
bool visited[MAX];

void bfs(int start_node) {
    queue<int> q;
    q.push(start_node);
    visited[start_node] = true;

    while (!q.empty()) {
        int curr_node = q.front();
        q.pop();
        cout << curr_node << " "; // Output the current node

        #pragma omp parallel for
        for (int i = 0; i < graph[curr_node].size(); i++) {
            int adj_node = graph[curr_node][i];
            if (!visited[adj_node]) {
                #pragma omp critical
                {
                    visited[adj_node] = true;
                }
                q.push(adj_node);
            }
        }
    }
}

int main() {
    int n, m, start_node;
    cout << "Enter No of Nodes, Edges, and start node: ";
    cin >> n >> m >> start_node;
    cout << "Enter Pairs of Edges: ";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    cout << "BFS starting from node " << start_node << ": ";
    
    double start_time = omp_get_wtime();
	bfs(start_node);
	double end_time = omp_get_wtime();
	double elapsed_time = end_time - start_time;
    cout << "Time Required for BFS: " << elapsed_time << " seconds" << endl;

    

    return 0;
}
