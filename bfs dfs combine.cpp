#include <iostream>
#include <vector>
#include <queue>
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

    // BFS Traversal
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

    // DFS Traversal
    void dfs(int node, vector<bool> &visited)
    {
        visited[node] = true;

        #pragma omp critical
        cout << node << " ";

        for(int neighbor : adj[node])
        {
            if(!visited[neighbor])
            {
                dfs(neighbor, visited);
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

    vector<bool> visited(vertices, false);

    cout << "\n\nDFS Traversal:\n";
    g.dfs(start, visited);

    return 0;
}


BFS (Breadth First Search)
Algorithm
Start from the root node.
Mark the node as visited.
Insert the node into a queue.
Remove a node from the queue.
Visit all unvisited adjacent nodes.
Insert adjacent nodes into the queue.
Repeat until the queue becomes empty.
Time Complexity

O(V+E)

Space Complexity

O(V)

2. DFS (Depth First Search)
Algorithm
Start from the root node.
Mark the node as visited.
Visit one adjacent unvisited node recursively.
Continue until no unvisited node remains.
Backtrack and repeat for remaining nodes.



Time Complexity

O(V+E)

Space Complexity

O(V)