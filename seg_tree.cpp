#include <bits/stdc++.h>
using namespace std;

/******************* Segment Tree Start Here ************************/
// This code is written for Range Minimum Query
// define node according to question
// change merge function according to question

const int inf = 1e9;

struct node
{
    int num;
    node(int x = inf)
    {
        num = x;
    }
};

node merge(node a, node b)
{
    if (a.num < b.num)
        return a;
    else
        return b;
}

vector<int> arr;
vector<node> segt;

void build(int index, int l, int r)
{
    if (l == r)
    {
        segt[index] = node(arr[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(index * 2, l, mid);
    build(index * 2 + 1, mid + 1, r);
    segt[index] = merge(segt[index * 2], segt[index * 2 + 1]);
}

void update(int index, int l, int r, int pos, int val)
{
    if (pos < l || pos > r)
        return;
    if (l == r)
    {
        segt[index] = node(val);
        arr[pos] = val;
        return;
    }
    int mid = (l + r) / 2;
    update(index * 2, l, mid, pos, val);
    update(index * 2 + 1, mid + 1, r, pos, val);
    segt[index] = merge(segt[index * 2], segt[index * 2 + 1]);
}

node query(int index, int l, int r, int lq, int rq)
{
    if (l > rq || r < lq)
        return node(inf);
    if (l >= lq && r <= rq)
        return segt[index];
    int mid = (l + r) / 2;
    return merge(query(index * 2, l, mid, lq, rq), query(index * 2 + 1, mid + 1, r, lq, rq));
}

void solve()
{
    int n, m;
    cin >> n >> m;
    segt.resize(4 * n);
    arr.resize(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    build(1, 0, n - 1);
    for (int i = 0; i < m; i++)
    {
        int ch, y, z;
        cin >> ch >> y >> z;
        if (ch == 1)
            update(1, 0, n - 1, y, z);
        else if (ch == 2)
            cout << query(1, 0, n - 1, y, z).num << endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _t = 1;
    cin >> _t;
    while (_t--)
        solve();
    return 0;
}