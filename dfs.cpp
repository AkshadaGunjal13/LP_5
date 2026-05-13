#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

class Graph
{
    int vertices;
    vector<int> *adj;

public:
    Graph(int v)
    {
        vertices = v;
        adj = new vector<int>[v];
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int node, vector<bool> &visited)
    {
        visited[node] = true;

        #pragma omp critical
        cout << node << " ";

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                for(int neighbor : adj[node])
                {
                    if(!visited[neighbor])
                    {
                        dfs(neighbor, visited);
                    }
                }
            }
        }
    }
};

int main()
{
    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    Graph g(vertices);

    cout << "Enter edges (u v):\n";

    for(int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    vector<bool> visited(vertices, false);

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    cout << "\nDFS Traversal:\n";

    g.dfs(start, visited);

    return 0;
}


Enter number of vertices: 5
Enter number of edges: 4
Enter edges (u v):
0 1
0 2
1 3
1 4
Enter starting vertex: 0

DFS Traversal:
0 1 3 4 2


        0
       / \
      1   2
     / \
    3   4