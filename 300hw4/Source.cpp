#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <queue>

using namespace std;

typedef vector<vector<int>> Graph;

Graph readGraph(const string& filename) {
    ifstream file(filename);
    int V, E;
    file >> V >> E;

    Graph graph(V+1);

    for (int i = 0; i < E; i++) {
        int u, v;
        file >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    return graph;
}

void dfs(Graph& graph, vector<bool>& visitedNodes, vector<int>& colors, int color, int index,bool &isBipartite) {
    colors[index] = color;
    visitedNodes[index] = true;

    for (int i : graph[index]) {
        if (colors[i] == colors[index]) {
            isBipartite = false;
        }
        if (!visitedNodes[i]) {
            dfs(graph, visitedNodes, colors, (color * -1), i, isBipartite);
        }
    }

}

bool isGraphBipartite(Graph& graph) {
    vector<bool> visitedNodes(graph.size(),false);
    vector<int> colors(graph.size());
    bool isBipartite = true;

    if (graph[0].empty()) {
        dfs(graph, visitedNodes, colors, 1, 1,isBipartite);
    }
    else {
        dfs(graph, visitedNodes, colors , 1, 0,isBipartite);
    }

    return isBipartite;
}

bool bfs(int start, vector<int>& match, Graph& graph) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    vector<int> parent(graph.size(), -1);
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                parent[neighbor] = node;
                visited[neighbor] = true;
                if (match[neighbor] == -1) {
                    int current = neighbor;
                    while (current != -1) {
                        int prev = parent[current];
                        if (prev != -1) {
                            match[current] = prev;
                            match[prev] = current;
                        }
                        current = parent[prev];
                    }
                    return true;
                }
                else {
                    q.push(match[neighbor]);
                    visited[match[neighbor]] = true;
                }
            }
        }
    }
    return false;
}

int findAugmentingPaths(Graph& graph) {
    int augmentingPathCount = 0;
    vector<int> match(graph.size(), -1);

    for (int i = 1; i < graph.size(); ++i) {
        if (match[i] == -1) {
            if (bfs(i, match, graph)) {
                augmentingPathCount++;
            }
        }
    }

    for (int i = 0; i < match.size(); i++) {
        if (match[i] == 0) {
            augmentingPathCount--;
        }
    }

    return augmentingPathCount;
}

int main() {

    string fileName;

    while (true) {
        cout << "Enter the graph name (e.g., 'graph1' or 'exit' to terminate): ";
        cin >> fileName;

        if (fileName == "exit") {
            break;
        }

        Graph graph = readGraph(fileName + ".txt");

        if (isGraphBipartite(graph)){
            int augmentingPathCount = findAugmentingPaths(graph);
            cout << "The graph is bipartite." << endl;
            cout << "Maximum matching size: " << augmentingPathCount <<  endl;
        }
        else {
            cout << "The graph is not bipartite." << endl;
        }
    }

}