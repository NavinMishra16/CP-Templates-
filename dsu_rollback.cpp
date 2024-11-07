#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define inf LLONG_MAX
using namespace std;
using ll = long long;
using pll = pair<long long, long long>;
const int mod = 1e9+7;

struct DSU {
    vector<int> parent;
    vector<int> size;
    stack<pair<int, int>> history; 

    DSU(int n) {
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; 
            size[i] = 1;
        }
    }

    int getsize(int x) {
        int par_x = find(x);
        return size[par_x];
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return find(parent[x]);
    }

    void unite(int x, int y) {
        int par_X = find(x);
        int par_Y = find(y);
        if (par_X != par_Y) {
            if (size[par_X] < size[par_Y]) swap(par_X, par_Y);
            // Save the state before uniting for rollback
            history.push({par_X, size[par_X]});
            history.push({par_Y, parent[par_Y]});
            size[par_X] += size[par_Y];
            parent[par_Y] = par_X;
        }
    }
    void rollback() {
        if (history.empty()) return;
        auto &[nodeY, prv_parY] = history.top();
        history.pop();
        parent[nodeY] = prv_parY;
        auto &[nodeX, prv_size_X] = history.top();
        history.pop();
        size[nodeX] = prv_size_X;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}
