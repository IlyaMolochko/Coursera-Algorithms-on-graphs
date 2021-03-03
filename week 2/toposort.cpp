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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> order;
    vector<bool> was_visited(n);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
    }
    for (int i = 0; i < n; ++i){
        if (!was_visited[i]){
            dfs(g, was_visited, order, i);
        }
    }
    for (int i = n - 1; i >= 0; --i){
        cout << order[i] + 1 << ' ';
    }
}
