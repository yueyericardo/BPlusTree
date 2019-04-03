# BPlusTree

C++ Implementation of B+Tree.  
The way how this work is similar to [B+Tree visualization](https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html)

Features:
- insert a key-value pair (key:int, value:double)
- delete a key
- search a key
- search a key range

Usage:  
```c++
BPlusTree bpt = BPlusTree(m); //m is the degree of B+ tree
bpt.Insert(key, value);
bpt.Delete(key);
bpt.Search(key);
bpt.Search(key1, key2); 
```

Output example:
```

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
Final: 
( 10  12  18  31 )
key: 10 12 18 31 
val: 10 12 18 31 

Inserting 15
Final: 
( 10  12  15  18  31 )
key: 10 12 15 18 31 
val: 10 12 15 18 31 

Inserting 48
splitting
 | ( 15 )|
( 10  12 )( 15  18  31 )
Final: 
 | ( 15 )|
( 10  12 )( 15  18  31  48 )
key: 10 12 15 18 31 48 
val: 10 12 15 18 31 48 

Inserting 45
Final: 
 | ( 15 )|
( 10  12 )( 15  18  31  45  48 )
key: 10 12 15 18 31 45 48 
val: 10 12 15 18 31 45 48 

Inserting 47
splitting
 | ( 15 | 31 )|
( 10  12 )( 15  18 )( 31  45  48 )
Final: 
 | ( 15 | 31 )|
( 10  12 )( 15  18 )( 31  45  47  48 )
key: 10 12 15 18 31 45 47 48 
val: 10 12 15 18 31 45 47 48 

Inserting 50
Final: 
 | ( 15 | 31 )|
( 10  12 )( 15  18 )( 31  45  47  48  50 )
key: 10 12 15 18 31 45 47 48 50 
val: 10 12 15 18 31 45 47 48 50 

Inserting 63
splitting
 | ( 15 | 31 | 47 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48  50 )
Final: 
 | ( 15 | 31 | 47 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48  50  63 )
key: 10 12 15 18 31 45 47 48 50 63 
val: 10 12 15 18 31 45 47 48 50 63 

Inserting 56
Final: 
 | ( 15 | 31 | 47 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48  50  56  63 )
key: 10 12 15 18 31 45 47 48 50 56 63 
val: 10 12 15 18 31 45 47 48 50 56 63 

Inserting 90
splitting
 | ( 15 | 31 | 47 | 50 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  56  63 )
Final: 
 | ( 15 | 31 | 47 | 50 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  56  63  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 90 
val: 10 12 15 18 31 45 47 48 50 56 63 90 

Inserting 87
Final: 
 | ( 15 | 31 | 47 | 50 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  56  63  87  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 87 90 
val: 10 12 15 18 31 45 47 48 50 56 63 87 90 

Inserting 77
splitting
 | ( 15 | 31 | 47 | 50 | 63 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  56 )( 63  87  90 )
Final: 
 | ( 15 | 31 | 47 | 50 | 63 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  56 )( 63  77  87  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 77 87 90 
val: 10 12 15 18 31 45 47 48 50 56 63 77 87 90 

Inserting 66
splitting
 | ( 47 )|
 | ( 15 | 31 )| | ( 50 | 63 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  56 )( 63  77  87  90 )
Final: 
 | ( 47 )|
 | ( 15 | 31 )| | ( 50 | 63 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  56 )( 63  66  77  87  90 )
key: 10 12 15 18 31 45 47 48 50 56 63 66 77 87 90 
val: 10 12 15 18 31 45 47 48 50 56 63 66 77 87 90 

Inserting 52
Final: 
 | ( 47 )|
 | ( 15 | 31 )| | ( 50 | 63 )|
( 10  12 )( 15  18 )( 31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 31 45 47 48 50 52 56 63 66 77 87 90 

Inserting 23
Final: 
 | ( 47 )|
 | ( 15 | 31 )| | ( 50 | 63 )|
( 10  12 )( 15  18  23 )( 31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 23 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 23 31 45 47 48 50 52 56 63 66 77 87 90 

Inserting 30
Final: 
 | ( 47 )|
 | ( 15 | 31 )| | ( 50 | 63 )|
( 10  12 )( 15  18  23  30 )( 31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 23 30 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 23 30 31 45 47 48 50 52 56 63 66 77 87 90 

Inserting 20
Final: 
 | ( 47 )|
 | ( 15 | 31 )| | ( 50 | 63 )|
( 10  12 )( 15  18  20  23  30 )( 31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 20 23 30 31 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 31 45 47 48 50 52 56 63 66 77 87 90 

 | ( 47 )|
 | ( 15 | 31 )| | ( 50 | 63 )|
( 10  12 )( 15  18  20  23  30 )( 31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
10 12 15 18 20 23 30 31 45 47 48 50 52 56 63 66 77 87 90 

===================================
deleteing data
===================================

deleting 31
Merging p y
 | ( 15 | 31 | 47 | 50 | 63 )|
( 10  12 )( 15  18  20  23  30 )( 31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
before shift to right child
 | ( 15 | 31 | 47 | 50 | 63 )|
( 10  12 )( 15  18  20  23  30 )( 31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
shift to right child
 | ( 15 | 30 | 47 | 50 | 63 )|
( 10  12 )( 15  18  20  23 )( 30  31  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
node found in: ( 30  31  45 )
31 index is = 1
 | ( 15 | 30 | 47 | 50 | 63 )|
( 10  12 )( 15  18  20  23 )( 30  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 20 23 30 45 47 48 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 45 47 48 50 52 56 63 66 77 87 90 

deleting 48
before shift to left child
 | ( 15 | 30 | 47 | 50 | 63 )|
( 10  12 )( 15  18  20  23 )( 30  45 )( 47  48 )( 50  52  56 )( 63  66  77  87  90 )
shift to left child
 | ( 15 | 30 | 47 | 52 | 63 )|
( 10  12 )( 15  18  20  23 )( 30  45 )( 47  48  50 )( 52  56 )( 63  66  77  87  90 )
node found in: ( 47  48  50 )
48 index is = 1
 | ( 15 | 30 | 47 | 52 | 63 )|
( 10  12 )( 15  18  20  23 )( 30  45 )( 47  50 )( 52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 20 23 30 45 47 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 45 47 50 52 56 63 66 77 87 90 

deleting 45
before shift to right child
 | ( 15 | 30 | 47 | 52 | 63 )|
( 10  12 )( 15  18  20  23 )( 30  45 )( 47  50 )( 52  56 )( 63  66  77  87  90 )
shift to right child
 | ( 15 | 23 | 47 | 52 | 63 )|
( 10  12 )( 15  18  20 )( 23  30  45 )( 47  50 )( 52  56 )( 63  66  77  87  90 )
node found in: ( 23  30  45 )
45 index is = 2
 | ( 15 | 23 | 47 | 52 | 63 )|
( 10  12 )( 15  18  20 )( 23  30 )( 47  50 )( 52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 20 23 30 47 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 47 50 52 56 63 66 77 87 90 

deleting 47
Merging p y
 | ( 15 | 23 | 52 | 63 )|
( 10  12 )( 15  18  20 )( 23  30  47  50 )( 52  56 )( 63  66  77  87  90 )
node found in: ( 23  30  47  50 )
47 index is = 2
 | ( 15 | 23 | 52 | 63 )|
( 10  12 )( 15  18  20 )( 23  30  50 )( 52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 20 23 30 50 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 50 52 56 63 66 77 87 90 

deleting 50
node found in: ( 23  30  50 )
50 index is = 2
 | ( 15 | 23 | 52 | 63 )|
( 10  12 )( 15  18  20 )( 23  30 )( 52  56 )( 63  66  77  87  90 )
key: 10 12 15 18 20 23 30 52 56 63 66 77 87 90 
val: 10 12 15 18 20 23 30 52 56 63 66 77 87 90 

find key 52, the value is 52 
find key 20, the value is 20 
find key 15, the value is 15 
in range 12 ~ 13: 12 
in range 50 ~ 87: 30 52 56 63 66 77 87 
in range 63 ~ 63: 63 
in range 56 ~ 66: 56 63 66 
in range 50 ~ 87: 30 52 56 63 66 77 87 

Program ended with exit code: 0
```
