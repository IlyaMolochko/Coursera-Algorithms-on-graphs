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

bool bfs(vector<vector<int>> &g, vector<bool> &visited, vector<int> &color, int u){
    queue<pair<int, int>> q;
    q.push({u, 0});
    pair<int, int> top;
    visited[u] = true;
    int v;
    color[u] = 1;
    int cnt = 1;
    while (!q.empty()){
        top = q.front();
        if (top.second < g[top.first].size()){
            v = g[top.first][top.second];
            if (!visited[v]){
                q.push({v, 0});
                visited[v] = true;
                color[v] = color[top.first] % 2 + 1;
                ++cnt;
            } else if (color[v] == color[top.first]){
                return false;
            }
            ++q.front().second;
        } else {
            q.pop();
        }
    }
    return true;
}

//bool bfs(vector<vector<int>> &g, vector<bool> &visited, vector<int> &color, int u){
//    queue<int> q;
//    q.push(u);
//    int top;
//    visited[u] = true;
//    int v;
//    color[u] = 1;
//    while (!q.empty()){
//        top = q.front();
//        for (int i = 0; i < g[top].size(); ++i){
//            v = g[top][i];
//            if (!visited[v]){
//                q.push(v);
//                visited[v] = true;
//                color[v] = color[top] % 2 + 1;
//            } else if (color[v] == color[top]){
//                return false;
//            }
//        }
//        q.pop();
//    }
//    return true;
//}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<vector<int>> gr(n);
    vector<int> order;
    vector<bool> was_visited(n, false);
    vector<int> color(n);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bool answ = true;
    for (int i = 0; i < n and answ; ++i){
        if (!was_visited[i]){
            answ = bfs(g, was_visited, color, i);
        }
    }
    cout << int(answ) << '\n';
}
