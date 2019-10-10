#include <cstdio>
#include "segmenttree.h"

typedef long long ll;

int n, m;
std::vector<ll> a;

ll merge(ll x, ll y)
{
    return x + y;
}

void update(segmentTreeNode<ll, int>& node, int x)
{
    node.val += x; 
}

int main()
{
    scanf("%d%d", &n, &m);
    
    a.resize(n);
    for (int i = 0; i < n; ++i) scanf("%lld", &a[i]);
    
    segmentTree<ll, int, merge, update> t(n, a, 0);
    
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1) t.modify(x, y);
        else printf("%lld\n", t.query(x, y + 1));
    }
    
    return 0;
}
