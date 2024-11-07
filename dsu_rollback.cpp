#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair
#define inf LLONG_MAX
using namespace std;
using ll = long long;
using pll = pair<long long, long long>;
const int mod = 1e9+7;
struct DSU{
    vector<int>parent;
    vector<int>size;
    stack<pair<int,int>>history ; 
    DSU(int n){
        parent.resize(n+1);
        size.resize(n+1);
        for(int i = 0 ; i < n+1 ;i++){
            parent[i] = i; 
            size[i] = 1;
        }
    }
    int getsize(int x){
        int par_x = find(x);
        return size[par_x];
    }

    int find(int x){
        if(parent[x]==x)return x ;
        return find(parent[x]);
    }
    void unite(int x ,int y){
        // Asumed x is bigger than y  
        int par_X = find(x);
        int par_Y = find(y);
        if(par_X!=par_Y){
            if(size[par_X] < size[par_Y])swap(par_X,par_Y);
            // Save the State before uniting so we could perform Rollbacks 
            pair<int,int>state  = make_pair(size[par_X],parent[par_Y]);
            history.push(state);
            size[par_X] += size[par_Y];
            parent[par_Y] = par_X;
        }
    }
    void rollback(){
        if(history.empty())return ;
        auto &[sz,par] = history.top();
        history.pop();
        int affected = find(par);
        size[affected] = sz;
        parent[par] = par;
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    DSU dsu(5);
    dsu.unite(3,4);
    dsu.unite(1,2);
    cout << "Parent of 4 : " << dsu.find(4) << endl;
    cout << "Parent of 2 : " << dsu.find(2) << endl;
    cout << "Size of  Componet 1 After Merge : " << dsu.getsize(1) << endl;
    dsu.rollback();
    cout << "Size of  Componet 1 After rollback : " << dsu.getsize(1) << endl;
    cout << "Parent of 2 after rollback : " << dsu.find(2) << endl;
    return 0;

}