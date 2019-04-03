//
//  BPlusTree.hpp
//  cop5536
//
//  Created by Richard Xue on 3/31/19.
//  Copyright © 2019 jinzexue. All rights reserved.
//

#ifndef BPlusTree_hpp
#define BPlusTree_hpp

#include <stdio.h>
#pragma once
#include "struct.h"
#include "Tree.h"

class BPlusTree :
public Tree
{
protected:
    virtual btree_node* btree_create();
    virtual btree_node* btree_node_new();
    virtual int btree_split_child(btree_node *parent, int pos, btree_node *child);
    virtual void btree_insert_nonfull(btree_node *node, int target, double target_value);
    virtual void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z);
    virtual void btree_delete_nonone(btree_node *root, int target);
    virtual double* btree_search(btree_node *root, int target);
    virtual btree_node* btree_root_search(btree_node *root, int target);
    virtual void btree_search(btree_node *root, int target1, int target2);
    virtual int btree_search_successor(btree_node *root);
    virtual int btree_search_predecessor(btree_node *root);
    virtual void btree_shift_to_left_child(btree_node *root, int pos, btree_node *y, btree_node *z);
    virtual void btree_shift_to_right_child(btree_node *root, int pos, btree_node *y, btree_node *z);
    virtual btree_node* btree_insert(btree_node *root, int target, double target_value);
    virtual btree_node *btree_delete(btree_node *root, int target);
    virtual void btree_inorder_print(btree_node *root);
    virtual void btree_level_display(btree_node *root);
    virtual void btree_pretty_display(btree_node *root);
    virtual void Save(btree_node *root);
//     @brief print tree linearly using prev/next pointer
//     @param root: root of tree
    void btree_linear_print(btree_node *root);
    void btree_value_print(btree_node *root);

public:
    BPlusTree(void);
    ~BPlusTree(void);
    void linear_print();
};

#endif /* BPlusTree_hpp */
