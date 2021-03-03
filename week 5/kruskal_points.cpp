#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <queue>
#include <cmath>
#include <random>
#include <ctime>
#include <fstream>
#include <set>
#include <iomanip>

using namespace std;
typedef long long ll;

struct element {
    int p;
    int r;

    explicit element(int p = -1, int r = 0) : p(p), r(r) {}
};

struct DisjointSet {
    vector<element> sets;

    explicit DisjointSet(int size) {
        sets = vector<element>(size);
        for (int i = 0; i < size; ++i) {
            sets[i].p = i;
        }
    }

    int find(int i) {
        return sets[i].p = (sets[i].p == sets[sets[i].p].p ? sets[i].p : find(sets[i].p));
    }

    void union_set(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (sets[a].r == sets[b].r) {
                ++sets[a].r;
            }
            if (sets[a].r < sets[b].r) {
                sets[a].p = b;
            } else {
                sets[b].p = a;
            }
        }
    }
};

struct edge {
    int u;
    int v;
    long double d;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> points(n);
    for (auto &i : points) {
        cin >> i.first >> i.second;
    }
    vector<edge> v;
    v.reserve(n * n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            v.push_back({i, j, static_cast<long double>(sqrt(
                    static_cast<long double>((points[i].first - points[j].first) *
                                             (points[i].first - points[j].first)) +
                    static_cast<long double>((points[i].second - points[j].second) *
                                             (points[i].second - points[j].second))))});
        }
    }
    sort(v.begin(), v.end(), [](edge e1, edge e2){
        return e1.d < e2.d;
    });
    DisjointSet dset(n);
    long double answ = 0;
    for (auto &[u, v, d] : v){
        if (dset.find(u) != dset.find(v)){
            dset.union_set(u, v);
            answ += d;
        }
    }
    cout << setprecision(15) << fixed;
    cout << answ << '\n';
    return 0;
}