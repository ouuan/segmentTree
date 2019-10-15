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

template<typename valueType, typename tagType>
class segmentTreeNode
{
public:
    int id, left, right;
    valueType val;
    tagType tag;
};

template<typename valueType,
         typename tagType,
         valueType (*merge)(valueType, valueType),
         void (*update)(segmentTreeNode<valueType, tagType>&, tagType)>
class segmentTree
{
private:
    int leftRange, rightRange;
    std::vector<segmentTreeNode<valueType, tagType> > nodes;
    valueType zero;
    
    void pushup(int cur)
    {
        nodes[cur].val = merge(nodes[cur << 1].val, nodes[cur << 1 | 1].val);
    }
    
    void pushdown(int cur)
    {
        update(nodes[cur << 1], nodes[cur].tag);
        update(nodes[cur << 1 | 1], nodes[cur].tag);
        nodes[cur].tag = 0;
    }
    
    void build(int cur, int l, int r, const std::vector<valueType>& initValue)
    {
        nodes[cur].id = cur;
        nodes[cur].left = l;
        nodes[cur].right = r;
        nodes[cur].tag = 0;
        if (l == r - 1) nodes[cur].val = initValue[l - leftRange];
        else
        {
            build(cur << 1, l, (l + r) >> 1, initValue);
            build(cur << 1 | 1, (l + r) >> 1, r, initValue);
            pushup(cur);
        }
    }
    
    void init(const std::vector<valueType>& _initValue,
              const valueType& _zero)
    {
        zero = _zero;
        nodes.resize((rightRange - leftRange) << 2);
        build(1, leftRange, rightRange, _initValue);
    }
    
    void modify(int cur, int l, int r, int L, int R, const tagType& tag)
    {
        if (l >= R || r <= L) return;
        if (L <= l && r <= R) update(nodes[cur], tag);
        else
        {
            pushdown(cur);
            modify(cur << 1, l, (l + r) >> 1, L, R, tag);
            modify(cur << 1 | 1, (l + r) >> 1, r, L, R, tag);
            pushup(cur);
        }
    }
    
    valueType query(int cur, int l, int r, int L, int R)
    {
        if (l >= R || r <= L) return zero;
        if (L <= l && r <= R) return nodes[cur].val;
        pushdown(cur);
        return merge(query(cur << 1, l, (l + r) >> 1, L, R),
                     query(cur << 1 | 1, (l + r) >> 1, r, L, R));
    }
    
public:
    segmentTree() {}
    
    segmentTree(int _leftRange,
                int _rightRange,
                const std::vector<valueType>& _initValue,
                const valueType& _zero)
    {
        leftRange = _leftRange;
        rightRange = _rightRange;
        init(_initValue, _zero);
    }
    
    segmentTree(int size,
                const std::vector<valueType>& _initValue,
                const valueType& _zero)
    {
        leftRange = 1;
        rightRange = size + 1;
        init(_initValue, _zero);
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
};

#endif
