#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <set>

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

bool dfs1(vector<vector<int>> &g, vector<bool> &was_visited, int i) {
    vector<pair<int, int>> st(1, {i, 0});
    pair<int, int> top;
    was_visited[i] = true;
    vector<int> components(1, i);
    while (!st.empty()) {
        top = st.back();
        if (top.second < g[top.first].size()) {
            if (was_visited[g[top.first][top.second]]) {
                ++st.back().second;
            } else {
                ++st.back().second;
                st.emplace_back(g[top.first][top.second], 0);
                components.push_back(g[top.first][top.second]);
                was_visited[g[top.first][top.second]] = true;
            }
        } else {
            st.pop_back();
        }
    }
    return components.size() > 1;
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
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        gr[v].push_back(u);
    }
    for (int i = 0; i < n; ++i){
        if (!was_visited[i]){
            dfs(g, was_visited, order, i);
        }
    }
    was_visited.assign(n, false);
    int answ = 0;
    for (int i = 0; i < n; ++i){
        v = order[n - i - 1];
        if (!was_visited[v]){
            dfs1(gr, was_visited, v);
            ++answ;
        }
    }
    cout << answ << '\n';
}
