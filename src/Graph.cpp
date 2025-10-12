#include "Graph.h"
#include <queue>
#include <vector>

Graph::Graph(int vertices): V(vertices), adj(vertices), degree(vertices,0) {}

void Graph::addEdge(int u, int v) {
    if (u>=0 && u < V && v>=0 && v < V) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
}

int Graph::getEdgeCount() const{
    int sum = 0;
    for (int d: degree){
        sum+=d;
    }
    return sum / 2;
}

bool Graph::isConnected() const {
    if (V==0) return true;

    std::vector<bool> visited(V,false);
    std::queue<int> q;
    int visitedCount = 0;

    q.push(0);
    visited[0] = true;
    visitedCount++;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                visitedCount++;
                q.push(v);
            }
        }
    }

    return visitedCount == V;
}

std::pair<bool, std::pair<int, int>> Graph::isBipartite() const {
    if (V==0) return {true, {0,0}};

    std::vector<int> color(V, -1);
    std::queue<int> q;
    bool bipartite = true;

    for (int i = 0; i < V && bipartite; i++){
        if (color[i] == -1) {
            color[i] = 0;
            q.push(i);

            while (!q.empty() && bipartite){
                int u = q.front();
                q.pop();

                for (int v : adj[u]){
                    if (color[v]==-1){
                        color[v]= 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]){
                        bipartite = false;
                        break;
                    }
                }   
            } 
        }
    }

    if (!bipartite) return {false, {0,0}};
    
    int count0=0, count1 = 0;
    for (int c : color) {
        if (c == 0) count0++;
        else count1++;
    }

    return {true, {count0, count1}};
}

void Graph::clear(){
    V = 0;
    adj.clear();
    degree.clear();
}

void Graph::resize(int vertices) {
    V = vertices;
    adj.resize(vertices);
    degree.assign(vertices, 0);
}

