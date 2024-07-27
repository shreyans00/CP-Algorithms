#include <bits/stdc++.h>
using namespace std;

class dsu
{
    vector<int> rank, par, sz;

public:
    dsu(int n)
    {
        rank.resize(n + 1, 0);
        par.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            par[i] = i;
            sz[i] = 1;
        }
    }

    int findpar(int node)
    {
        if (node == par[node])
            return node;
        return par[node] = findpar(par[node]);
    }
    void unionbyrank(int u, int v)
    {
        int up = findpar(u), vp = findpar(v);
        if (up == vp)
            return;
        if (rank[up] < rank[vp])
            par[up] = vp;
        else if (rank[up] > rank[vp])
            par[vp] = up;
        else
        {
            par[vp] = up;
            rank[up]++;
        }
    }
    void unionbysize(int u, int v)
    {
        int up = findpar(u), vp = findpar(v);
        if (up == vp)
            return;
        if (sz[up] < sz[vp])
        {
            par[up] = vp;
            sz[vp] += sz[up];
        }
        else
        {
            par[vp] = up;
            sz[up] += sz[vp];
        }
    }
};