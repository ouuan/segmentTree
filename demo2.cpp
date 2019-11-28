#include "segmenttree.h"
#include <cstdio>

typedef long long ll;

int n, m, p;
std::vector<int> a;

struct Tag
{
    int add, mul;
    Tag(int _add = 0, int _mul = 1) { add = _add; mul = _mul; }
    void operator+=(const Tag& y)
    {
        add = ((ll) add * y.mul + y.add) % p;
        mul = (ll) mul * y.mul % p;
    }
};

int merge(int x, int y)
{
    return (x + y) % p;
}

void update(segmentTreeNode<int, Tag>& node, Tag tag)
{
    node.val = ((ll) node.val * tag.mul + (ll) tag.add * (node.right - node.left)) % p;
    node.tag += tag;
}

int main()
{
    scanf("%d%d%d", &n, &m, &p);
    
    a.resize(n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    
    segmentTree<int, Tag, merge, update> t(n, a, 0, Tag());
    
    while (m--)
    {
        int opt, l, r;
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
        {
            int x;
            scanf("%d", &x);
            t.modify(l, r + 1, Tag(0, x));
        }
        else if (opt == 2)
        {
            int x;
            scanf("%d", &x);
            t.modify(l, r + 1, Tag(x, 1));
        }
        else printf("%d\n", t.query(l, r + 1));
    }
    
    return 0;
}
