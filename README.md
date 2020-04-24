This repository is DEPRECATED and NO LONGER MAINTAINED. You can use [the segment tree header](https://github.com/ouuan/CPTH/blob/master/headers/SegmentTree.h) in [CPTH](https://github.com/ouuan/CPTH) instead.

<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>

---

# segmentTree

A Segment Tree Template

## Demos

[single element add, segment query for sum](https://loj.ac/problem/130): [demo1.cpp](demo1.cpp)

```cpp
#include "segmenttree.h"
#include <cstdio>

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
    
    segmentTree<ll, int, merge, update> t(n, a, 0, 0);
    
    while (m--)
    {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1) t.modify(x, y);
        else printf("%lld\n", t.query(x, y + 1));
    }
    
    return 0;
}
```

[segment add & multiply, segment query for sum modulo p](https://www.luogu.org/problem/P3373): [demo2.cpp](demo2.cpp)

[segment sqrt, segment query for sum](https://loj.ac/problem/6281): [demo3.cpp](demo3.cpp)

## What can it do?

Almost everything a segment tree can do. (Except unbasic things like binary search on segment tree, segment tree merging and persistent segment tree.)

If you understand how to use it, you will know how powerful it is. (And also what it can't do.)

## How to use it?

### The problem

First, let's define a problem which can be solved by a segment tree (the version in this template) as following:

There is a sequence of **value**s a[1..n], and the **value**s are **merge**-able, which means you can **merge** two **value**s into one. If we merge x and y, we will get x + y, and the **value** of a subsequence a[l..r] is a[l] + a[l + 1] + … + a[r]. We can also perform **modification** to a **value**.

(If you are familar with abstract algebra, you'll find that the **value**s form a [monoid](https://en.wikipedia.org/wiki/Monoid).)

The problem is: give you a sequence, you have to perform **modification** to some subsegment, or report the **value** of some subsegment.

For example: given you a sequence of integers, you have to either add x to a all integers of a subsegment or report the sum of a subsegment.

In this example, a **value** is an integer, to **merge** is to add two integers together, to perform a **modification** is to add an integer to an element in the sequence.

### The segment tree

Second, you have to know what a segment tree is, and the [lazy propagation tech](https://www.geeksforgeeks.org/lazy-propagation-in-segment-tree/) (which is called "lazy-tag" in this guidebook). You can find many resources about it on the Internet.

Then, we can find that, in most segment tree problems, the only difference is the type of **value**, how to **merge**, and how to perform **modification**. And the **modification** is the same as pushing down a lazy-**tag**.

In this template, you only have to implement these key parts of a segment tree, and don't have to code the duplicate part of nearly every segment tree.

### Details

First, you have to `#include "segmenttree.h"` (and put the header file in the same path as the source file, or use the compile option `-I`), or paste the whole header file in your source file.

To construct a segment tree, you have to choose a type for the **value**, a type for the **tag** (the same as **modification**), implement the `merge` function and the `update` function.

The declaration: `segmentTree<valueType, tagType, merge, update>`.

#### Value

- supports the `=` operator
- has default constructor
- have a special element **valueZero**, where `merge(valueZero, x) == x` and `merge(x, valueZero) == x` for all possible **value** x. It can also be called "identity element". For example, it is 0 if merging is to add together, it is -INF (a sufficiently negative number) if merging is to calculate the max.

#### tag

- supports the `=` operator
- has default constructor
- have a special element **tagZero**, and if you perform **tagZero** to any **value**, the **value** keep unchanged. For example, it is 0 if modification is to add, it is INF (a sufficiently large number) if modification is to choose the smaller one.

#### merge

- accepts two **value**s as parameters
- returns a single **value**, which is the result of merging the two parameters
- The prototype: `valueType (*merge)(valueType, valueType)`

#### node

```cpp
template<typename valueType, typename tagType>
class segmentTreeNode
{
public:
	int id, left, right;
	valueType val;
	tagType tag;
};
```

- the `id` of the root is 1, the `id` of the left child of x is 2x, the `id` of the right child of x is 2x+1
- the `left` and `right` represent for the subsegment [left, right)

#### update

- accepts a **node&** and a **tag** as parameters
- performs the modification **tag** to the **node**, returns nothing (void).
- If lazy-tag is needed, update the tag, too. Remember that the tag is the same as the modification.
- The prototype: `void (*update)(segmentTreeNode<valueType, tagType>&, tagType)`

#### public functions

`segmentTree()`: default constructor. The segment tree will be uninitialized, which may cause errors.

`segmentTree(int _leftRange, int _rightRange, const vector<valueType>& _initValue, const valueType& _valueZero, const tagType& _tagZero)`: construct a segment tree represents for the segment [`_leftRange`, `_rightRange`), initially a[i] = `initValue[i - _leftRange]`, the identity element of values is `_valueZero`, the no-effect element of tags is `_tagZero`.

`segmentTree(int size, const vector<valueType>& _initValue, const valueType& _valueZero, const tagType& _tagZero)`: the same as `segmentTree(1, size + 1, _initValue, _valueZero, _tagZero)`.

`void modify(int l, int r, const tagType& tag)`: perform modification of tag to the subsegment [l, r).

`void modify(void modify(int p, const tagType& tag)`: perform modification of tag to the single element a[p].

`valueType query(int l, int r)`: returns the value of the subsegment [l, r).

`valueType query(int p)`: returns the value of the single element a[p].

#### read the demos

You can learn how to use it via the [demos](#Demos).

## I found a bug! / It can be improved

Please [open an issue](https://github.com/ouuan/segmentTree/issues), describe the situation, and provide your codes.

That will help a lot since this template hasn't been well tested.
