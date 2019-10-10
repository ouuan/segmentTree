#include <cmath>
#include <cstdio>
#include <algorithm>
#include "segmenttree.h"

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

const int N = 50010;

int n, a[N];
vector<pli> init;

pli merge(pli x, pli y)
{
	return pli(x.first + y.first, min(x.second, y.second));
}

struct Tag
{
	bool flag; // here the flag means if it is needed to perform the sqrt
	int cnt;
	Tag(int x = 0)
	{
		flag = bool(x);
		cnt = x;
	}
};

void update(segmentTreeNode<pli, Tag>& node, Tag x)
{
	if (node.val.second >= 5 || !x.cnt) return;
	if (x.flag)
	{
		while (node.val.second < 5 && x.cnt--)
		{
			++node.val.second;
			++node.tag.cnt;
			for (int i = node.left; i < node.right; ++i)
			{
				a[i] = sqrt(a[i]) + 1e-12;
			}
		}
	}
	else
	{
		node.val.second += x.cnt;
		node.tag.cnt += x.cnt;
	}
	node.val.first = 0;
	for (int i = node.left; i < node.right; ++i) node.val.first += a[i];
}

int main()
{
	scanf("%d", &n);
	
	init.resize(n);
	
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		init[i - 1] = pli(a[i], 0);
	}
	
	segmentTree<pli, Tag> t(n, init, pli(0, 0), merge, update);
	
	for (int i = 1; i <= n; ++i)
	{
		int opt, l, r, c;
		scanf("%d%d%d%d", &opt, &l, &r, &c);
		if (opt) printf("%lld\n", t.query(l, r + 1).first);
		else t.modify(l, r + 1, Tag(1));
	}
	
	return 0;
}
