/*

MIT License

Copyright (c) 2019 ouuan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

// for further information and bug tracking,
// please visit https://github.com/ouuan/segmentTree

#ifndef SEGMENT_TREE_BY_OUUAN
#define SEGMENT_TREE_BY_OUUAN 1

#include <vector>

using std::vector;

template<typename valueType, typename tagType>
class segmentTreeNode
{
public:
	int left, right;
	valueType val;
	tagType tag;
};

template<typename valueType, typename tagType>
class segmentTree
{
#define ls (cur << 1)
#define rs (cur << 1 | 1)
#define mid ((l + r) >> 1)

public:
	typedef segmentTreeNode<valueType, tagType> nodeType;
	
private:
	int leftRange, rightRange;
	vector<valueType> initValue;
	vector<nodeType> nodes;
	valueType (*merge)(valueType, valueType);
	void (*update)(nodeType&, tagType);
	valueType zero;
	
	void pushup(int cur)
	{
		nodes[cur].val = merge(nodes[ls].val, nodes[rs].val);
	}
	
	void pushdown(int cur)
	{
		update(nodes[ls], nodes[cur].tag);
		update(nodes[rs], nodes[cur].tag);
		nodes[cur].tag = 0;
	}
	
	void build(int cur, int l, int r)
	{
		nodes[cur].left = l;
		nodes[cur].right = r;
		nodes[cur].tag = 0;
		if (l == r - 1) nodes[cur].val = initValue[l - leftRange];
		else
		{
			build(ls, l, mid);
			build(rs, mid, r);
			pushup(cur);
		}
	}
	
	void init(const vector<valueType>& _initValue,
			  const valueType& _zero,
			  valueType (*_merge)(valueType, valueType),
			  void (*_update)(nodeType&, tagType))
	{
		initValue = _initValue;
		zero = _zero;
		merge = _merge;
		update = _update;
		nodes.resize((rightRange - leftRange) << 2);
		build(1, leftRange, rightRange);
	}
	
	void init(int _leftRange,
			  int _rightRange,
			  const vector<valueType>& _initValue,
			  const valueType& _zero,
			  valueType (*_merge)(valueType, valueType),
			  void (*_update)(nodeType&, tagType))
	{
		leftRange = _leftRange;
		rightRange = _rightRange;
		init(_initValue, _zero, _merge, _update);
	}
	
	void init(int size,
			  const vector<valueType>& _initValue,
			  const valueType& _zero,
			  valueType (*_merge)(valueType, valueType),
			  void (*_update)(nodeType&, tagType))
	{
		leftRange = 1;
		rightRange = size + 1;
		init(_initValue, _zero, _merge, _update);
	}
	
	void modify(int cur, int l, int r, int L, int R, const tagType& tag)
	{
		if (l >= R || r <= L) return;
		if (L <= l && r <= R) update(nodes[cur], tag);
		else
		{
			pushdown(cur);
			modify(ls, l, mid, L, R, tag);
			modify(rs, mid, r, L, R, tag);
			pushup(cur);
		}
	}
	
	valueType query(int cur, int l, int r, int L, int R)
	{
		if (l >= R || r <= L) return zero;
		if (L <= l && r <= R) return nodes[cur].val;
		pushdown(cur);
		return merge(query(ls, l, mid, L, R), query(rs, mid, r, L, R));
	}
	
public:
	segmentTree() {}
	
	segmentTree(int _leftRange,
				int _rightRange,
				const vector<valueType>& _initValue,
				const valueType& _zero,
				valueType (*_merge)(valueType, valueType),
				void (*_update)(nodeType&, tagType))
	{
		init(_leftRange, _rightRange, _initValue, _zero, _merge, _update);
	}
	
	segmentTree(int size,
				const vector<valueType>& _initValue,
				const valueType& _zero,
				valueType (*_merge)(valueType, valueType),
				void (*_update)(nodeType&, tagType))
	{
		init(size, _initValue, _zero, _merge, _update);
	}
	
	void modify(int l, int r, const tagType& tag)
	{
		modify(1, leftRange, rightRange, l, r, tag);
	}
	
	void modify(int p, const tagType& tag)
	{
		modify(p, p + 1, tag);
	}
	
	valueType query(int l, int r)
	{
		return query(1, leftRange, rightRange, l, r);
	}
	
	valueType query(int p)
	{
		return query(p, p + 1);
	}

#undef ls
#undef rs
#undef mid
};

#endif
