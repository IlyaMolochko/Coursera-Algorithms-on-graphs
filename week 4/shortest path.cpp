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

void sift_up(vector<pair<int, int>> &q, int i){
    while (q[i].first < q[i / 2 - (i % 2 == 0)].first and i > 0){
        swap(q[i], q[i / 2 - (i % 2 == 0)]);
        i = i / 2 - (i % 2 == 0);
    }
}

void insert(vector<pair<int, int>> &q, pair<int, int> p){
    q.push_back(p);
    if (q.size() > 1){
        sift_up(q, q.size() - 1);
    }
}

void sift_down(vector<pair<int, int>> &q, int i){
    int l, r, m;
    while (2 * i + 1 < q.size()){
        l = 2 * i + 1;
        r = 2 * i + 2;
        m = l;
        if (r < q.size() and q[l] > q[r]){
            m = r;
        }
        if (q[i].first > q[m].first){
            swap(q[i], q[m]);
            i = m;
        } else {
            break;
        }
    }
}

pair<int, int> extract(vector<pair<int, int>> &q){
    pair<int, int> mn = q[0];
    if (q.size() > 1){
        swap(q[0], q[q.size() - 1]);
        q.pop_back();
        sift_down(q, 0);
    } else {
        q.pop_back();
    }
    return mn;
}

int dijkstra(vector<vector<pair<int, int>>> &g, int s, int e){
    vector<pair<int, int>> q;
    vector<int> d(g.size(), numeric_limits<int>::max());
    d[s] = 0;
    q.emplace_back(d[s], s);
    pair<int, int> u, v;
    while (!q.empty()){
        u = extract(q);
        if (u.first <= d[u.second]){
            for (int i = 0; i < g[u.second].size(); ++i){
                v = g[u.second][i];
                if (d[v.second] > d[u.second] + v.first){
                    d[v.second] = d[u.second] + v.first;
                    insert(q, {d[v.second], v.second});
                }
            }
        }

    }
    return d[e];
}

struct edge{
    int u;
    int v;
    ll d;
};

void ford_bellman(){
    int n, m;
    cin >> n >> m;
    vector<edge> g(m);
    for (auto &i : g){
        cin >> i.u >> i.v >> i.d;
        --i.u;
        --i.v;
    }
    int s, e;
    cin >> s >> e;
    --s;
    --e;
    vector<ll> d(n, numeric_limits<ll>::max());
    d[s] = 0;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (d[g[j].u] < numeric_limits<ll>::max()){
                if (d[g[j].v] > d[g[j].u] + g[j].d){
                    d[g[j].v] = d[g[j].u] + g[j].d;
                }
            }
        }
    }
    if (d[e] == numeric_limits<ll>::max()){
        cout << -1 << '\n';
    } else {
        cout << d[e] << '\n';
    }
}

void contain_cycle(){
    int n, m;
    cin >> n >> m;
    vector<edge> g(m);
    for (auto &i : g){
        cin >> i.u >> i.v >> i.d;
        --i.u;
        --i.v;
    }
    vector<ll> d(n, 10000);
    d[0] = 0;
    bool answ;
    for (int i = 0; i <= n; ++i){
        answ = false;
        for (int j = 0; j < m; ++j){
            if (d[g[j].u] < numeric_limits<ll>::max()){
                if (d[g[j].v] > d[g[j].u] + g[j].d){
                    d[g[j].v] = max(d[g[j].u] + g[j].d, ll(-10e7));
                    answ = true;
                }
            }
        }
    }
    cout << int(answ) << '\n';
}

void shortest_path(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> g(n, vector<pair<int, ll>>());
    int u, v, dist;
    for (int i = 0; i < m; ++i){
        cin >> u >> v >> dist;
        --u;
        --v;
        g[u].emplace_back(v, dist);
    }
    vector<ll> d(n, 10e12);
    int s;
    cin >> s;
    --s;
    d[s] = 0;
    for (int k = 0; k < n - 1; ++k){
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < g[i].size(); ++j){
                if (d[i] < 10e12){
                    if (d[g[i][j].first] > d[i] + g[i][j].second){
                        d[g[i][j].first] = max(d[i] + g[i][j].second, ll(-10e15));
                    }
                }
            }
        }
    }
    set<int> path;
    vector<bool> cycle(n, false);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < g[i].size(); ++j){
            if (d[i] < 10e12){
                if (d[g[i][j].first] > d[i] + g[i][j].second){
                    d[g[i][j].first] = max(d[i] + g[i][j].second, ll(-10e15));
                    path.insert(i);
                    cycle[i] = true;
                }
            }
        }
    }
    int top;
    while (!path.empty()){
        top = *path.begin();
        for (auto &i : g[top]){
            if (!cycle[i.first]){
                path.insert(i.first);
                cycle[i.first] = true;
            }
        }
        path.erase(top);
    }
    for (int i = 0; i < n; ++i){
        if (!cycle[i] and d[i] != 10e12){
            cout << d[i] << '\n';
        } else if (d[i] != 10e12){
            cout << '-' << '\n';
        } else {
            cout << '*' << '\n';
        }
    }
//    vector<edge> g(m);
//    for (auto &i : g){
//        cin >> i.u >> i.v >> i.d;
//        --i.u;
//        --i.v;
//    }
//    vector<ll> d(n, 10e10);
//    vector<int> p(n, -1);
//    int s;
//    cin >> s;
//    --s;
//    d[s] = 0;
//    set<int> path;
//    for (int i = 0; i < n; ++i){
//        for (int j = 0; j < m; ++j){
//            if (d[g[j].u] < 10e10){
//                if (d[g[j].v] > d[g[j].u] + g[j].d){
//                    d[g[j].v] = max(d[g[j].u] + g[j].d, ll(-10e15));
//                    p[g[j].v] = g[j].u;
//                    if (i == n - 1){
//                        path.insert(g[j].v);
//                        path.insert(g[j].u);
//                    }
//                }
//            }
//        }
//    }
//
//    for (int i = 0; i < n; ++i){
//        if (d[i] != 10e10 and path.find(i) == path.end()){
//            cout << d[i] << '\n';
//        } else if (d[i] != 10e10){
//            cout << '-' << '\n';
//        } else {
//            cout << '*' << '\n';
//        }
//    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
//    int n, m;
//    cin >> n >> m;
//    vector<vector<pair<int, int>>> g(n, vector<pair<int, int>>());
//    int u, v, d;
//    for (int i = 0; i < m; ++i){
//        cin >> u >> v >> d;
//        --u;
//        --v;
//        g[u].emplace_back(d, v);
//    }
//    cin >> u >> v;
//    --u;
//    --v;
//    int answ = dijkstra(g, u, v);
//    if (answ != numeric_limits<int>::max()){
//        cout << answ << '\n';
//    } else {
//        cout << -1 << '\n';
//    }
//    ford_bellman();
//    contain_cycle();
    shortest_path();
}