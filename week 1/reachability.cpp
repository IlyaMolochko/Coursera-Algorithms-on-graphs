#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;

bool dfs(vector<vector<int>> &g, int u, int v){
    vector<pair<int, int>> st(1, {u, 0});
    pair<int, int> top;
    vector<bool> was_visited(g.size(), false);
    was_visited[u] = true;
    while (!st.empty()){
        top = st.back();
        if (top.second < g[top.first].size()){
            if (g[top.first][top.second] == v){
                return true;
            } else if (was_visited[g[top.first][top.second]]){
                ++st.back().second;
            }else {
                ++st.back().second;
                st.emplace_back(g[top.first][top.second], 0);
                was_visited[g[top.first][top.second]] = true;
            }
        } else {
            st.pop_back();
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    int u, v;
    for (int i = 0; i < m; ++i){
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    cin >> u >> v;
    --u;
    --v;
    if (find(g[u].begin(), g[u].end(), v) != g[u].end() or dfs(g, u, v)){
        cout << 1 << '\n';
    } else {
        cout << 0 << '\n';
    }
}
