#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <set>
#include <map>

using namespace std;
using ll = long long;

void dfs(vector<vector<int>> &g, vector<bool> &was_visited, vector<int> &order, int i) {
    vector<pair<int, int>> st(1, {i, 0});
    pair<int, int> top;
    was_visited[i] = true;
    while (!st.empty()) {
        top = st.back();
        if (top.second < g[top.first].size()) {
            if (was_visited[g[top.first][top.second]]) {
                ++st.back().second;
            } else {
                ++st.back().second;
                st.emplace_back(g[top.first][top.second], 0);
                was_visited[g[top.first][top.second]] = true;
            }
        } else {
            order.push_back(top.first);
            st.pop_back();
        }
    }
}

void bfs(vector<vector<int>> &g, vector<map<int, int>> &dist, vector<bool> &visited, int u){
    queue<pair<int, int>> q;
    q.push({u, 0});
    pair<int, int> top;
    dist[u][u] = 0;
    visited[u] = true;
    int v;
    while (!q.empty()){
        top = q.front();
        if (top.second < g[top.first].size()){
            v = g[top.first][top.second];
            auto it = dist[u].lower_bound(v);
            if (it != dist[u].end() and it->first == v){
                dist[u][v] = min(dist[u][v], dist[u][top.first] + 1);
            } else {
                dist[u][v] = min(1000000, dist[u][top.first] + 1);
            }

            if (!visited[v]){
                q.push({v, 0});
                visited[v] = true;
            }
            ++q.front().second;
        } else {
            q.pop();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<vector<int>> gr(n);
    vector<int> order;
    vector<bool> was_visited(n);
    vector<map<int, int>> dist(n);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
        dist[u][v] = 10e6;
        dist[v][u] = 10e6;
    }
    cin >> u >> v;
    --u;
    --v;

    bfs(g, dist, was_visited, u);
    if (dist[u].find(v) != dist[u].end()){
        cout << dist[u][v] << '\n';
    } else {
        cout << -1 << '\n';
    }
}
