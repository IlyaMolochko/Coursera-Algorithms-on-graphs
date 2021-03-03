#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;

void dfs(vector<vector<int>> &g, vector<bool> &was_visited, int i, int &cnt) {
    vector<pair<int, int>> st(1, {i, 0});
    pair<int, int> top;
    was_visited[i] = true;
    ++cnt;
    while (!st.empty()) {
        top = st.back();
        if (top.second < g[top.first].size()) {
            if (was_visited[g[top.first][top.second]]) {
                ++st.back().second;
            } else {
                ++st.back().second;
                st.emplace_back(g[top.first][top.second], 0);
                was_visited[g[top.first][top.second]] = true;
                ++cnt;
            }
        } else {
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
    vector<bool> was_visited(n, false);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int cnt = 0;
    int i = 0;
    int answ = 0;
    while (cnt != n){
        if (!was_visited[i]){
            dfs(g, was_visited, i, cnt);
            ++answ;
        } else {
            ++i;
        }
    }
    cout << answ << '\n';
}
