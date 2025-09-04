/*
    Project: Topological Sorting
    Parsa Zamani
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

// Enum for node colors in DFS (used for cycle detection)
enum Color { WHITE, GRAY, BLACK };

// DFS function for topological sorting and cycle detection
bool dfs(int node, const vector<vector<int>>& graph, vector<Color>& colors, 
         vector<bool>& visited, stack<int>& topoStack) {
    colors[node] = GRAY;  // Node is being visited

    for (int neighbor : graph[node]) {
        if (colors[neighbor] == GRAY) {
            // Found a back edge -> cycle detected
            return false;
        }
        if (colors[neighbor] == WHITE) {
            if (!dfs(neighbor, graph, colors, visited, topoStack)) {
                return false;
            }
        }
    }

    colors[node] = BLACK;  // Node fully processed
    visited[node] = true;
    topoStack.push(node);  // Push to stack after visiting all neighbors
    return true;
}

// Function to perform topological sort
void topologicalSort(const vector<vector<int>>& graph, int n) {
    vector<Color> colors(n, WHITE);  // Initially all nodes are unvisited (white)
    vector<bool> visited(n, false);
    stack<int> topoStack;
    bool hasCycle = false;

    // Run DFS from all unvisited nodes
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && colors[i] == WHITE) {
            if (!dfs(i, graph, colors, visited, topoStack)) {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle) {
        cout << "Graph has a cycle! No topological sort possible." << endl;
    } else {
        // Print the topological order
        while (!topoStack.empty()) {
            cout << topoStack.top();
            topoStack.pop();
            if (!topoStack.empty()) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    ifstream file("graph.txt");
    if (!file.is_open()) {
        cerr << "Error opening file graph.txt" << endl;
        return 1;
    }

    int n;
    file >> n;  // Number of vertices

    // Read adjacency matrix and build adjacency list
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int edge;
            file >> edge;
            if (edge == 1) {
                graph[i].push_back(j);  // Directed edge i -> j
            }
        }
    }

    file.close();

    // Perform topological sort
    topologicalSort(graph, n);

    return 0;
}
