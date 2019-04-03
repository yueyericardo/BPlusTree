//
//  BPlusTree.hpp
//  cop5536
//
//  Created by Richard Xue on 3/31/19.
//  Copyright © 2019 jinzexue. All rights reserved.
//

#ifndef BPlusTree_hpp
#define BPlusTree_hpp

#define M 2

#include <stdio.h>
#pragma once

typedef struct btree_nodes {
    int key[2*M-1];
    double value[2*M-1];
    struct btree_nodes *child[2*M];
    int num;
    bool is_leaf;
    struct btree_nodes *prev;
    struct btree_nodes *next;  
    
} btree_node;

class BPlusTree
{
private:
    // basic data
    btree_node *roots;
    int btree_node_num;
    int t;
    
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
    void btree_search(btree_node *root, int target1, int target2);
    btree_node* btree_root_search(btree_node *root, int target);
    
    void Save(btree_node *root);

public:
    BPlusTree(void);
    ~BPlusTree(void);
    
    // insert
    void Insert(int target, double target_value){
        roots = btree_insert(roots, target, target_value);
        Save(roots);  // 即时保存
    };
    
    // delete
    void Delete(int target) {roots = btree_delete(roots, target);};
    
    // print
    void linear_print();
    void pretty_display();
    void value_display();
    void NodeNum_print();
    
    // search
    void Search(int target){
        double* result = btree_search(roots, target);
        if (result) {
            printf("find key %d, the value is %.0f \n", target, *result);
        }else{
            printf("Null");
        }
    }
    void Search(int target1, int target2){
        printf("in range %d ~ %d: \n", target1, target2);
        btree_search(roots, target1, target2);
        printf("\n");
    }
};

#endif /* BPlusTree_hpp */
