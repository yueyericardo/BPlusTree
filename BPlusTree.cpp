//
//  BPlusTree.cpp
//  cop5536
//
//  Created by Richard Xue on 3/31/19.
//  Copyright © 2019 jinzexue. All rights reserved.
//

#include "BPlusTree.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<queue>
#include <vector>

btree_node* BPlusTree::btree_node_new()
{
    btree_node *node = (btree_node *)malloc(sizeof(btree_node));
    if(NULL == node) {
        return NULL;
    }
    node->key = (int *)calloc((2 * M - 1), sizeof(int));
    node->value = (double *)calloc((2 * M - 1), sizeof(double));
    node->child = (btree_node **)calloc(2 * M, sizeof(btree_node*));
    if(NULL == node->key || NULL == node->value || NULL == node->child) {
        return NULL;
    }
    
    node->num = 0;
    node->is_leaf = true;
    node->prev = nullptr;
    node->next = nullptr;
    return node;
}

btree_node *BPlusTree::btree_create()
{
    btree_node *node = btree_node_new();
    if(NULL == node) {
        return NULL;
    }

    node->next = node;
    node->prev = node;

    return node;
}

int BPlusTree::btree_split_child(btree_node *parent, int pos, btree_node *child)
{
    btree_node *new_child = btree_node_new();
    if(NULL == new_child) {
        return -1;
    }

    new_child->is_leaf = child->is_leaf;
    child->num = M - 1;
    // not leaf, left: M-1, right:M-1, center one go up level
    if(false == new_child->is_leaf) {
        new_child->num = M - 1;
        for(int i = 0; i < M - 1; i++) {
            new_child->key[i] = child->key[i+M];
//            new_child->value[i] = child->value[i+M];
        }
        
        for(int i = 0; i < M; i++) {
            new_child->child[i] = child->child[i+M];
        }
    }
    // is leaf, left: M-1, right:M, right[0] go up level
    if(true == child->is_leaf) {
        new_child->num = M;
        for(int i = 0; i < M; i++) {
            new_child->key[i] = child->key[i+M-1];
            new_child->value[i] = child->value[i+M-1];
        }
    }

    for(int i = parent->num; i > pos; i--) {
        parent->child[i+1] = parent->child[i];
    }
    parent->child[pos+1] = new_child;

    for(int i = parent->num - 1; i >= pos; i--) {
        parent->key[i+1] = parent->key[i];
    }
    
    if(false == new_child->is_leaf) {
        parent->key[pos] = child->key[M-1];
    }
    if(true == child->is_leaf) {
        parent->key[pos] = new_child->key[0];
        parent->value[pos] = new_child->value[0];
    }
    
    parent->num += 1;

    // update link
    if(true == child->is_leaf) {
        new_child->next = child->next;
        child->next->prev = new_child;
        new_child->prev = child;
        child->next = new_child;
    }
    printf("splitting\n");
    btree_pretty_display(parent);
    
    return 1;
}

void BPlusTree::btree_insert_nonfull(btree_node *node, int target, double target_value)
{
    if(true == node->is_leaf) {
        int pos = node->num;
        while(pos >= 1 && target < node->key[pos-1]) {
            node->key[pos] = node->key[pos-1];
            node->value[pos] = node->value[pos-1];
            pos--;
        }

        node->key[pos] = target;
        node->value[pos] = target_value;
        node->num += 1;
        btree_node_num+=1;
        
    } else {
        int pos = node->num;
        while(pos > 0 && target < node->key[pos-1]) {
            pos--;
        }

        if(2 * M -1 == node->child[pos]->num) {
            btree_split_child(node, pos, node->child[pos]);
            if(target > node->key[pos]) {
                pos++;
            }
        }

        btree_insert_nonfull(node->child[pos], target, target_value);
    }
}

btree_node* BPlusTree::btree_insert(btree_node *root, int target, double target_value)
{
    if(NULL == root) {
        return NULL;
    }

    if(2 * M - 1 == root->num) {
        btree_node *node = btree_node_new();
        if(NULL == node) {
            return root;
        }

        node->is_leaf = false;
        node->child[0] = root;
        btree_split_child(node, 0, root);
        btree_insert_nonfull(node, target, target_value);
        return node;
    } else {
        btree_insert_nonfull(root, target, target_value);
        return root;
    }
}

void BPlusTree::btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z)
{
    if(true == y->is_leaf) {
        y->num = 2 * M - 2;
        for(int i = M; i < 2 * M - 1; i++) {
            y->key[i-1] = z->key[i-M];
            y->value[i-1] = z->value[i-M];
        }
    } else {
        y->num = 2 * M - 1;
        for(int i = M; i < 2 * M - 1; i++) {
            y->key[i] = z->key[i-M];
        }
        y->key[M-1] = root->key[pos];
        for(int i = M; i < 2 * M; i++) {
            y->child[i] = z->child[i-M];
        }
    }

    for(int j = pos + 1; j < root->num; j++) {
        root->key[j-1] = root->key[j];
        root->child[j] = root->child[j+1];
    }

    root->num -= 1;

    // update link
    if(true == y->is_leaf) {
        y->next = z->next;
        z->next->prev = y;
    }

    free(z);
}

btree_node *BPlusTree::btree_delete(btree_node *root, int target)
{
    if(1 == root->num) {
        btree_node *y = root->child[0];
        btree_node *z = root->child[1];
        if(NULL != y && NULL != z &&
           M - 1 == y->num && M - 1 == z->num) {
            printf("Merging p y\n");
            btree_merge_child(root, 0, y, z);
            btree_pretty_display(y);
            free(root);
            btree_delete_nonone(y, target);
            return y;
        } else {
            btree_delete_nonone(root, target);
            return root;
        }
    } else {
        btree_delete_nonone(root, target);
        return root;
    }
}

btree_node* BPlusTree::btree_root_search(btree_node *root, int target){
    if(NULL == root) {
        return nullptr;
    }
    
    int i = root->num;

    while(i >0 && target < root->key[i-1]) {
        i--;
    }
    
    if (root->is_leaf) {
        return root;
    }else{
        btree_node* tmp = root->child[i];
        return btree_root_search(tmp, target);
    }
}

double* BPlusTree::btree_search(btree_node *root, int target)
{
    btree_node* target_root = btree_root_search(root, target);
    if(NULL == target_root) {
        return nullptr;
    }
    
    int i = target_root->num;
    double* result = nullptr;
    while(i >0 && target < target_root->key[i-1]) {
        i--;
    }

    if (target_root->key[i-1]  == target) {
        result = &(target_root->value[i-1]);
//            printf("%.0f \n",*result);
//            printf("%.0f \n",result);
//            std::cout<<result<<std::endl;
        return result;
    }else{
        return nullptr;
    }
}

std::vector<double> BPlusTree::btree_search(btree_node *root, int target1, int target2){
    btree_node* target1_root = btree_root_search(root, target1);
    btree_node* target2_root = btree_root_search(root, target2);
    
    std::vector<double> result;
    
    if(NULL == target1_root || NULL == target2_root) {
        printf("nothing found");
//        return 0;
        return result;
    }
    
    // search for index of target1
    int i = target1_root->num;
    while(i >0 && target1 < target1_root->key[i-1]) {
        i--;
    }
    
    // search for index of target2
    int j = target2_root->num;
    while(j >0 && target2 < target2_root->key[j-1]) {
        j--;
    }
    
    // print
    if (target1_root != target2_root) {
        if (target1 >= target1_root->key[i-1]) {
            
            // print the first node
            btree_node *iter = target1_root;
            if (target1 == target1_root->key[i-1]) {
                result.push_back(iter->value[i-1]);
            }
            for(int k = i; k < iter->num; k++) {
                result.push_back(iter->value[k]);
            }
            
            // print the middle node
            iter = iter->next;
            while (iter != target2_root) {
                for(int i = 0; i < iter->num; i++) {
                    result.push_back(iter->value[i]);
                }
                iter = iter->next;
            }
            
            // print the last node
            if (iter == target2_root) {
                for (int k = 0; k < j; k++) {
                    result.push_back(iter->value[k]);
                }
            }

        }
    }else if (target1_root == target2_root){
        btree_node *iter = target1_root;
        
        // target 2 smaller than smallest key, return null
        if (target2 < iter->key[0]) {
            return result;
        }
        // target 1 bigger than biggest key, return null
        else if(target1 > iter->key[iter->num -1]) {
            return result;
        }
        // print this range at this node
        if (target1 == target1_root->key[i-1]) {
            result.push_back(iter->value[i-1]);
        }
        for(int k = i; k < j; k++) {
            result.push_back(iter->value[k]);
        }
    }
    return result;
}

void BPlusTree::btree_delete_nonone(btree_node *root, int target)
{
    if(true == root->is_leaf) {
        int i = 0;
        while(i < root->num && target > root->key[i]) {
            i++;
        }
        
        if(target == root->key[i]) {
            printf("node found in: ");
            btree_pretty_display(root);
            printf("%d index is = %d\n", target, i);
            for(int j = i + 1; j < 2 * M - 1; j++) {
                root->key[j-1] = root->key[j];
                root->value[j-1] = root->value[j];
            }
            root->num -= 1;
            btree_node_num-=1;

        } else {
//            printf("root is_leaf %d\n", root->is_leaf);
            printf("===================================\n");
            printf("target not found\n");
            printf("===================================\n");
        }
    } else {
        int i = root->num;
        btree_node *y = NULL, *z = NULL;
        bool internal_node_change = false;
        while(i >0 && target < root->key[i-1]) {
            i--;
        }
        
        y = root->child[i];
        if(i < root->num) {
            z = root->child[i+1];
        }
        btree_node *p = NULL;
        if(i > 0) {
            p = root->child[i-1];
        }
        
//        if y->num == M-1
        if(y->num == M - 1) {
            if(i > 0 && p->num > M - 1) {
                printf("before shift to right child\n");
                btree_pretty_display(root);
                btree_shift_to_right_child(root, i-1, p, y);
                printf("shift to right child\n");
                btree_pretty_display(root);
            } else if(i < root->num && z->num > M - 1) {
                printf("before shift to left child\n");
                btree_pretty_display(root);
                btree_shift_to_left_child(root, i, y, z);
                printf("shift to left child\n");
                btree_pretty_display(root);
            } else if(i > 0) {
                printf("Merging p y\n");
                btree_merge_child(root, i-1, p, y);
                btree_pretty_display(root);
                y = p;
            } else {
                printf("Merging y z\n");
                btree_merge_child(root, i, y, z);
                btree_pretty_display(root);
            }
            
            btree_delete_nonone(y, target);
        } else { //y->num != M - 1

            if (root->key[i-1] == target) {
                internal_node_change = true;
            }
            
            btree_delete_nonone(y, target);
            if (internal_node_change) {
                printf("----------target is in internal node, internal node needs to be updated--------------\n");
                printf("before chang: %d ", root->key[i-1]);
                btree_node *tmp = root->child[i];
                while (tmp->is_leaf == false) {
                    tmp = tmp->child[0];
                }
                root->key[i-1] = tmp->key[0];
                printf("after chang: %d \n", root->key[i-1]);
            }
        }
    }
}

int BPlusTree::btree_search_predecessor(btree_node *root)
{
    btree_node *y = root;
    while(false == y->is_leaf) {
        y = y->child[y->num];
    }
    return y->key[y->num-1];
}

int BPlusTree::btree_search_successor(btree_node *root)
{
    btree_node *z = root;
    while(false == z->is_leaf) {
        z = z->child[0];
    }
    return z->key[0];
}

void BPlusTree::btree_shift_to_right_child(btree_node *root, int pos,
                                           btree_node *y, btree_node *z)
{
    z->num += 1;

    if(false == z->is_leaf) {
        for(int i = z->num -1; i > 0; i--) {
            z->key[i] = z->key[i-1];
        }
        z->key[0] = root->key[pos];
        root->key[pos] = y->key[y->num-1];
//        root->key[pos] = z->key[0];
    } else {
        for(int i = z->num -1; i > 0; i--) {
            z->key[i] = z->key[i-1];
            z->value[i] = z->value[i-1];
        }
        z->key[0] = y->key[y->num-1];
        z->value[0] = y->value[y->num-1];
//        printf("root->key %d\n", root->key[pos]);
        root->key[pos] = z->key[0];
    }

    if(false == z->is_leaf) {
        for(int i = z->num; i > 0; i--) {
            z->child[i] = z->child[i-1];
        }
        z->child[0] = y->child[y->num];
    }

    y->num -= 1;
}

void BPlusTree::btree_shift_to_left_child(btree_node *root, int pos,
                                          btree_node *y, btree_node *z)
{
    y->num += 1;

    if(false == z->is_leaf) {
        y->key[y->num-1] = root->key[pos];
        root->key[pos] = z->key[0];
//        printf("%d", root->key[pos]);
    } else {
        y->key[y->num-1] = z->key[0];
        y->value[y->num-1] = z->value[0];
        root->key[pos] = z->key[0];
    }

    for(int j = 1; j < z->num; j++) {
        z->key[j-1] = z->key[j];
        z->value[j-1] = z->value[j];
    }

    if(false == z->is_leaf) {
        y->child[y->num] = z->child[0];
        for(int j = 1; j <= z->num; j++) {
            z->child[j-1] = z->child[j];
        }
    }else{
        root->key[pos] = z->key[0];
    }

    z->num -= 1;
}

void BPlusTree::btree_linear_print(btree_node *root)
{
    if(NULL != root) {
        btree_node *leftmost = root;
        while(false == leftmost->is_leaf) {
            leftmost = leftmost->child[0];
        }

        btree_node *iter = leftmost;
        do {
            for(int i = 0; i < iter->num; i++) {
                printf("%d ", iter->key[i]);
                //    fwrite(&root,sizeof(root),1,fp);
            }
            iter = iter->next;
        } while(iter != leftmost);
        printf("\n");
    }
}

void BPlusTree::btree_value_print(btree_node *root)
{
    if(NULL != root) {
        btree_node *leftmost = root;
        while(false == leftmost->is_leaf) {
            leftmost = leftmost->child[0];
        }
        
        btree_node *iter = leftmost;
        do {
            for(int i = 0; i < iter->num; i++) {
                printf("%.0f ", iter->value[i]);
                //    fwrite(&root,sizeof(root),1,fp);
            }
            iter = iter->next;
        } while(iter != leftmost);
        printf("\n");
    }
}

void BPlusTree::btree_pretty_display(btree_node *root)
{
    // just for simplicty, can't exceed 200 nodes in the tree
    
    btree_node* last = root;
    btree_node* p = root;
    std::queue<btree_node*> Q;
    if(p){
        Q.push(p);
    }
    while(!Q.empty()){
        btree_node* tmp = Q.front();
        Q.pop();
        if (!tmp->is_leaf) {
            std::cout << " | ";
        }
        std::cout << "(";
        for (int i = 0;i < tmp->num;++i) {
            std::cout <<" "<< tmp->key[i]<<" ";
            if (!tmp->is_leaf&&i != tmp->num - 1) {
                std::cout << "|";
            }
        }
        
        std::cout << ")";
        if (!tmp->is_leaf) {   //不是叶子结点才有孩子
            std::cout << "|";
            for (int i = 0;i < tmp->num + 1;++i) {
                Q.push(tmp->child[i]);
            }
        }
        if (!last->is_leaf&&tmp == last) {
            std::cout << std::endl;
            last = last->child[last->num];
        }
    }
    std::cout << std::endl;
}

void BPlusTree::linear_print()
{
    btree_linear_print(roots);
}

void BPlusTree::pretty_display(){
    btree_pretty_display(roots);
}
void BPlusTree::value_display(){
    btree_value_print(roots);
}
void BPlusTree::NodeNum_print(){
    printf("%d\n", btree_node_num);
}

void BPlusTree::post_order_delete(btree_node*& node) {
    if (node->is_leaf) {  //Delete leaf directly
//        delete[] node->key;
//        delete[] node->value;
        delete node;
        node = nullptr;
    }
    else { // delete every child
        for (int i = 0; i < node->num + 1; ++i) {
            post_order_delete(node->child[i]);
        }
//        delete[] node->key;
//        delete[] node->value;
        delete node;
        node = nullptr;
    }
}
