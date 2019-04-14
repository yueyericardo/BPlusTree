<h2><center> COP 5536 Project Report: B+ Tree</center></h2>
<p style="text-align: center; margin-top: 5px;">
Jinze Xue &nbsp;/&nbsp; 2019.04.02 &nbsp;<br>
Email: jinzexue@ufl.edu &nbsp;/&nbsp; UFID: 38239101<br>
Repo: <a href="https://github.com/yueyericardo/BPlusTree">https://github.com/yueyericardo/BPlusTree</a>, will be public after 2019.04.14 12PM.
</p>



### 0. C++ Implementation of B+Tree. 

- The way how this work is similar to [B+Tree visualization](https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)

- Features:
  - insert a key-value pair (key:int, value:double)
  - delete a key
  - search a key
  - search a key range

- Usage:  
```c++
BPlusTree bpt = BPlusTree(m); //m is the degree of B+ tree
bpt.Insert(key, value);
bpt.Delete(key);
bpt.Search(key);
bpt.Search(key1, key2); 
```



### 1. For every node it has the structure of below

```c++
typedef struct btree_nodes {
    int* key; 										// 2 * M - 1
    double* value;								// 2 * M - 1
    struct btree_nodes **child;		// 2 * M
    int num;
    bool is_leaf;
    struct btree_nodes *prev;
    struct btree_nodes *next;  
    ~btree_nodes() {num = 0; free(child); child = nullptr; free(key); key = nullptr; free(value); value = nullptr;}
} btree_node;
```

​	

### 2. For BPlusTree Class

```c++
class BPlusTree
{
private:
    // basic data
    btree_node *roots;
    int btree_node_num;
    int M;
    
    // insert key
    btree_node* btree_create();
    btree_node* btree_node_new();
    btree_node* btree_insert(btree_node *root, int target, double target_value);
    void btree_insert_nonfull(btree_node *node, int target, double target_value);
    int btree_split_child(btree_node *parent, int pos, btree_node *child);
    
    // delete key
    btree_node *btree_delete(btree_node *root, int target);
    void btree_delete_nonone(btree_node *root, int target);
    void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z);
    int btree_search_successor(btree_node *root);
    int btree_search_predecessor(btree_node *root);
    void btree_shift_to_left_child(btree_node *root, int pos, btree_node *y, btree_node *z);
    void btree_shift_to_right_child(btree_node *root, int pos, btree_node *y, btree_node *z);
    
    // print
    void btree_pretty_display(btree_node *root);
    void btree_linear_print(btree_node *root);
    void btree_value_print(btree_node *root);
    
    // search
    double* btree_search(btree_node *root, int target);
    std::vector<double> btree_search(btree_node *root, int target1, int target2);
    btree_node* btree_root_search(btree_node *root, int target);
    void post_order_delete(btree_node*& root);
    void Save(btree_node *root);

public:
    //construct deconstruct
    BPlusTree(int m) {M = m; roots = btree_create(); btree_node_num = 0;};
    ~BPlusTree(){post_order_delete(roots);};
    
    // insert
    void Insert(int target, double target_value);
    
    // delete
    void Delete(int target) {roots = btree_delete(roots, target);};
    
    // print
    void linear_print();
    void pretty_display();
    void value_display();
    void NodeNum_print();
    
    // search
    double* Search(int target);
    std::vector<double> Search(int target1, int target2);
};
```



### 3. Output example:

in this example, the degree of tree == 2. to check it's working well, the value and key have the same number.

```c++
m = 2

Inserting 18
Final: 
( 18 )
key: 18 
val: 18 

Inserting 31
Final: 
( 18  31 )
key: 18 31 
val: 18 31 

Inserting 12
Final: 
( 12  18  31 )
key: 12 18 31 
val: 12 18 31 

Inserting 10
splitting
 | ( 18 )|
( 12 )( 18  31 )
Final: 
 | ( 18 )|
( 10  12 )( 18  31 )
key: 10 12 18 31 
val: 10 12 18 31 

Inserting 15
Final: 
 | ( 18 )|
( 10  12  15 )( 18  31 )
key: 10 12 15 18 31 
val: 10 12 15 18 31 

Inserting 48
Final: 
 | ( 18 )|
( 10  12  15 )( 18  31  48 )
key: 10 12 15 18 31 48 
val: 10 12 15 18 31 48 

Inserting 45
splitting
 | ( 18 | 31 )|
( 10  12  15 )( 18 )( 31  48 )
Final: 
 | ( 18 | 31 )|
( 10  12  15 )( 18 )( 31  45  48 )
key: 10 12 15 18 31 45 48 
val: 10 12 15 18 31 45 48 

Inserting 47
splitting
 | ( 18 | 31 | 45 )|
( 10  12  15 )( 18 )( 31 )( 45  48 )
Final: 
 | ( 18 | 31 | 45 )|
( 10  12  15 )( 18 )( 31 )( 45  47  48 )
key: 10 12 15 18 31 45 47 48 
val: 10 12 15 18 31 45 47 48 

Inserting 50
splitting
 | ( 31 )|
 | ( 18 )| | ( 45 )|
( 10  12  15 )( 18 )( 31 )( 45  47  48 )
splitting
 | ( 45 | 47 )|
( 31 )( 45 )( 47  48 )
Final: 
 | ( 31 )|
 | ( 18 )| | ( 45 | 47 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47  48  50 )
key: 10 12 15 18 31 45 47 48 50 
val: 10 12 15 18 31 45 47 48 50 

Inserting 63
splitting
 | ( 45 | 47 | 48 )|
( 31 )( 45 )( 47 )( 48  50 )
Final: 
 | ( 31 )|
 | ( 18 )| | ( 45 | 47 | 48 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48  50  63 )
key: 10 12 15 18 31 45 47 48 50 63 
val: 10 12 15 18 31 45 47 48 50 63 

Inserting 56
splitting
 | ( 31 | 47 )|
 | ( 18 )| | ( 45 )| | ( 48 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48  50  63 )
splitting
 | ( 48 | 50 )|
( 47 )( 48 )( 50  63 )
Final: 
 | ( 31 | 47 )|
 | ( 18 )| | ( 45 )| | ( 48 | 50 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50  56  63 )
key: 10 12 15 18 31 45 47 48 50 56 63 
val: 10 12 15 18 31 45 47 48 50 56 63 

Inserting 90
splitting
 | ( 48 | 50 | 56 )|
( 47 )( 48 )( 50 )( 56  63 )
Final: 
 | ( 31 | 47 )|
 | ( 18 )| | ( 45 )| | ( 48 | 50 | 56 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50 )( 56  63  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 90 
val: 10 12 15 18 31 45 47 48 50 56 63 90 

Inserting 87
splitting
 | ( 31 | 47 | 50 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50 )( 56  63  90 )
splitting
 | ( 56 | 63 )|
( 50 )( 56 )( 63  90 )
Final: 
 | ( 31 | 47 | 50 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 | 63 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50 )( 56 )( 63  87  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 87 90 
val: 10 12 15 18 31 45 47 48 50 56 63 87 90 

Inserting 77
splitting
 | ( 47 )|
 | ( 31 )| | ( 50 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 | 63 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50 )( 56 )( 63  87  90 )
splitting
 | ( 56 | 63 | 87 )|
( 50 )( 56 )( 63 )( 87  90 )
Final: 
 | ( 47 )|
 | ( 31 )| | ( 50 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 | 63 | 87 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50 )( 56 )( 63  77 )( 87  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 77 87 90 
val: 10 12 15 18 31 45 47 48 50 56 63 77 87 90 

Inserting 66
splitting
 | ( 50 | 63 )|
 | ( 48 )| | ( 56 )| | ( 87 )|
( 47 )( 48 )( 50 )( 56 )( 63  77 )( 87  90 )
Final: 
 | ( 47 )|
 | ( 31 )| | ( 50 | 63 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 66 77 87 90 
val: 10 12 15 18 31 45 47 48 50 56 63 66 77 87 90 

Inserting 52
Final: 
 | ( 47 )|
 | ( 31 )| | ( 50 | 63 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18 )( 31 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 31 45 47 48 50 52 56 63 66 77 87 90 

Inserting 23
Final: 
 | ( 47 )|
 | ( 31 )| | ( 50 | 63 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  23 )( 31 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 23 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 23 31 45 47 48 50 52 56 63 66 77 87 90 

Inserting 30
Final: 
 | ( 47 )|
 | ( 31 )| | ( 50 | 63 )|
 | ( 18 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  23  30 )( 31 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 23 30 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 23 30 31 45 47 48 50 52 56 63 66 77 87 90 

Inserting 20
splitting
 | ( 18 | 23 )|
( 10  12  15 )( 18 )( 23  30 )
Final: 
 | ( 47 )|
 | ( 31 )| | ( 50 | 63 )|
 | ( 18 | 23 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23  30 )( 31 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 20 23 30 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 31 45 47 48 50 52 56 63 66 77 87 90 

 | ( 47 )|
 | ( 31 )| | ( 50 | 63 )|
 | ( 18 | 23 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23  30 )( 31 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
10 12 15 18 20 23 30 31 45 47 48 50 52 56 63 66 77 87 90 

===================================
deleteing data
===================================

deleting 31
before shift to left child
 | ( 47 )|
 | ( 31 )| | ( 50 | 63 )|
 | ( 18 | 23 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23  30 )( 31 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
shift to left child
 | ( 50 )|
 | ( 31 | 47 )| | ( 63 )|
 | ( 18 | 23 )| | ( 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23  30 )( 31 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
before shift to right child
 | ( 31 | 47 )|
 | ( 18 | 23 )| | ( 45 )| | ( 48 )|
( 10  12  15 )( 18  20 )( 23  30 )( 31 )( 45 )( 47 )( 48 )
shift to right child
 | ( 23 | 47 )|
 | ( 18 )| | ( 31 | 45 )| | ( 48 )|
( 10  12  15 )( 18  20 )( 23  30 )( 31 )( 45 )( 47 )( 48 )
before shift to right child
 | ( 31 | 45 )|
( 23  30 )( 31 )( 45 )
shift to right child
 | ( 30 | 45 )|
( 23 )( 30  31 )( 45 )
node found in: ( 30  31 )
31 index is = 1
 | ( 50 )|
 | ( 23 | 47 )| | ( 63 )|
 | ( 18 )| | ( 30 | 45 )| | ( 48 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 45 )( 47 )( 48 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 20 23 30 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 45 47 48 50 52 56 63 66 77 87 90 

deleting 48
before shift to right child
 | ( 23 | 47 )|
 | ( 18 )| | ( 30 | 45 )| | ( 48 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 45 )( 47 )( 48 )
shift to right child
 | ( 23 | 45 )|
 | ( 18 )| | ( 30 )| | ( 47 | 48 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 45 )( 47 )( 48 )
Merging p y
 | ( 47 )|
( 45 )( 47  48 )
node found in: ( 47  48 )
48 index is = 1
 | ( 50 )|
 | ( 23 | 45 )| | ( 63 )|
 | ( 18 )| | ( 30 )| | ( 47 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 45 )( 47 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 20 23 30 45 47 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 45 47 50 52 56 63 66 77 87 90 

deleting 45
Merging p y
 | ( 23 )|
 | ( 18 )| | ( 30 | 45 | 47 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 45 )( 47 )
Merging p y
 | ( 30 | 47 )|
( 23 )( 30  45 )( 47 )
node found in: ( 30  45 )
45 index is = 1
 | ( 50 )|
 | ( 23 )| | ( 63 )|
 | ( 18 )| | ( 30 | 47 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 47 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 20 23 30 47 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 47 50 52 56 63 66 77 87 90 

deleting 47
Merging p y
 | ( 23 | 50 | 63 )|
 | ( 18 )| | ( 30 | 47 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 47 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
Merging p y
 | ( 30 )|
( 23 )( 30  47 )
node found in: ( 30  47 )
47 index is = 1
 | ( 23 | 50 | 63 )|
 | ( 18 )| | ( 30 )| | ( 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 20 23 30 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 50 52 56 63 66 77 87 90 

deleting 50
Merging p y
 | ( 23 | 63 )|
 | ( 18 )| | ( 30 | 50 | 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 50  52 )( 56 )( 63  66  77 )( 87  90 )
node found in: ( 50  52 )
50 index is = 0
----------target is in internal node, internal node needs to be updated--------------
before chang: 50 after chang: 52 
 | ( 23 | 63 )|
 | ( 18 )| | ( 30 | 52 | 56 )| | ( 87 )|
( 10  12  15 )( 18  20 )( 23 )( 30 )( 52 )( 56 )( 63  66  77 )( 87  90 )
key: 10 12 15 18 20 23 30 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 52 56 63 66 77 87 90 

find key 52, the value is 52 
find key 20, the value is 20 
find key 15, the value is 15 
in range 12 ~ 13: 12 
in range 50 ~ 87: 52 56 63 66 77 87 
in range 63 ~ 63: 63 
in range 56 ~ 66: 56 63 66 
in range 50 ~ 87: 52 56 63 66 77 87 
in range 50 ~ 86: 52 56 63 66 77 
in range 50 ~ 88: 52 56 63 66 77 87 

Program ended with exit code: 0
```



### 4. Reference:

- [Intro to Algorithms: CHAPTER 19: B-TREES](http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap19.htm)
- https://github.com/orange1438/BTree-and-BPlusTree-Realize
- https://github.com/alvin906/BTree