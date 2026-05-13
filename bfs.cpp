#include <iostream>
#include <vector>
#include <queue>
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

    void bfs(int start)
    {
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while(!q.empty())
        {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for(int neighbor : adj[node])
            {
                if(!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
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

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    cout << "\nBFS Traversal:\n";

    g.bfs(start);

    return 0;
}


//Enter number of vertices: 5
Enter number of edges: 4
Enter edges (u v):
0 1
0 2
1 3
1 4
Enter starting vertex: 0

BFS Traversal:
0 1 2 3 4 //

        0
       / \
      1   2
     / \
    3   4