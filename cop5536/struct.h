//
//  struct.h
//  cop5536
//
//  Created by Richard Xue on 3/31/19.
//  Copyright © 2019 jinzexue. All rights reserved.
//

#ifndef struct_h
#define struct_h

#pragma once
// the degree of btree
#define M 2

typedef struct btree_nodes {
    int k[2*M-1];
    double value[2*M-1];
    struct btree_nodes *p[2*M];
    int num;
    bool is_leaf;
    struct btree_nodes *prev;  // use one struct just for simple,Õâ2¸ö£¬¹©B+Tree used
    struct btree_nodes *next;  // ¹©B+Tree used
    
} btree_node;


typedef struct StorageNode{
    btree_node bnode;
    int index[M];   // Ë÷Òý¼¯ºÏ:index_set
}storage_node;

typedef struct StorageStruct{
    storage_node *snode;
    int len;
}storage_struct;

#endif /* struct_h */
