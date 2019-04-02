//
//  BPlusTree.cpp
//  cop5536
//
//  Created by Richard Xue on 3/31/19.
//  Copyright © 2019 jinzexue. All rights reserved.
//

#include "BPlusTree.hpp"

#include <iostream>
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include<queue>

#ifdef WIN32
#include <io.h>
#endif

#ifdef LINUX
#include <unistd.h>
#endif

btree_node* BPlusTree::btree_node_new()
{
    btree_node *node = (btree_node *)malloc(sizeof(btree_node));
    if(NULL == node) {
        return NULL;
    }

    for(int i = 0; i < 2 * M -1; i++) {
        node->k[i] = 0;
    }

    for(int i = 0; i < 2 * M; i++) {
        node->p[i] = NULL;
    }

    node->num = 0;
    node->is_leaf = true;
    node->prev = NULL;
    node->next = NULL;
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
            new_child->k[i] = child->k[i+M];
        }
        
        for(int i = 0; i < M; i++) {
            new_child->p[i] = child->p[i+M];
        }
    }
    // not leaf, left: M-1, right:M, right[0] go up level
    if(true == child->is_leaf) {
        new_child->num = M;
        for(int i = 0; i < M; i++) {
            new_child->k[i] = child->k[i+M-1];
        }
    }

    for(int i = parent->num; i > pos; i--) {
        parent->p[i+1] = parent->p[i];
    }
    parent->p[pos+1] = new_child;

    for(int i = parent->num - 1; i >= pos; i--) {
        parent->k[i+1] = parent->k[i];
    }
    
    if(false == new_child->is_leaf) {
        parent->k[pos] = child->k[M-1];
    }
    if(true == child->is_leaf) {
        parent->k[pos] = new_child->k[0];
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
    printf("\n");
    
    return 1;
}

void BPlusTree::btree_insert_nonfull(btree_node *node, int target)
{
    if(true == node->is_leaf) {
        int pos = node->num;
        while(pos >= 1 && target < node->k[pos-1]) {
            node->k[pos] = node->k[pos-1];
            pos--;
        }

        node->k[pos] = target;
        node->num += 1;
        btree_node_num+=1;
        
    } else {
        int pos = node->num;
        while(pos > 0 && target < node->k[pos-1]) {
            pos--;
        }

        if(2 * M -1 == node->p[pos]->num) {
            btree_split_child(node, pos, node->p[pos]);
            if(target > node->k[pos]) {
                pos++;
            }
        }

        btree_insert_nonfull(node->p[pos], target);
    }
}

btree_node* BPlusTree::btree_insert(btree_node *root, int target)
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
        node->p[0] = root;
        btree_split_child(node, 0, root);
        btree_insert_nonfull(node, target);
        return node;
    } else {
        btree_insert_nonfull(root, target);
        return root;
    }
}

void BPlusTree::btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z)
{
    if(true == y->is_leaf) {
        y->num = 2 * M - 2;
        for(int i = M; i < 2 * M - 1; i++) {
            y->k[i-1] = z->k[i-M];
        }
    } else {
        y->num = 2 * M - 1;
        for(int i = M; i < 2 * M - 1; i++) {
            y->k[i] = z->k[i-M];
        }
        y->k[M-1] = root->k[pos];
        for(int i = M; i < 2 * M; i++) {
            y->p[i] = z->p[i-M];
        }
    }

    for(int j = pos + 1; j < root->num; j++) {
        root->k[j-1] = root->k[j];
        root->p[j] = root->p[j+1];
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
        btree_node *y = root->p[0];
        btree_node *z = root->p[1];
        if(NULL != y && NULL != z &&
           M - 1 == y->num && M - 1 == z->num) {
            btree_merge_child(root, 0, y, z);
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

void BPlusTree::btree_delete_nonone(btree_node *root, int target)
{
    if(true == root->is_leaf) {
        printf("node found in: ");
        btree_pretty_display(root);
        int i = 0;
        while(i < root->num && target > root->k[i]) {
            printf("when i = %d,  target = %d, key=%d \n", i, target, root->k[i]);
            i++;
            
        }
        printf("index is = %d\n", i);
        if(target == root->k[i]) {
            for(int j = i + 1; j < 2 * M - 1; j++) {
                root->k[j-1] = root->k[j];
            }
            root->num -= 1;
            btree_node_num-=1;

        } else {
            printf("root is_leaf %d\n", root->is_leaf);
            printf("===================================\n");
            printf("target not found\n");
            printf("===================================\n");
        }
    } else {
        int i = root->num;
        btree_node *y = NULL, *z = NULL;
        while(i >0 && target < root->k[i-1]) i--;
        
        y = root->p[i];
        if(i < root->num) {
            z = root->p[i+1];
        }
        btree_node *p = NULL;
        if(i > 0) {
            p = root->p[i-1];
        }

        if(y->num == M - 1) {
            if(i > 0 && p->num > M - 1) {
                printf("before shift to right child\n");
                btree_pretty_display(root);
                btree_shift_to_right_child(root, i-1, p, y);
                printf("shift to right child\n");
                btree_pretty_display(root);
            } else if(i < root->num && z->num > M - 1) {
                btree_shift_to_left_child(root, i, y, z);
                printf("shift to left child\n");
                btree_pretty_display(root);
            } else if(i > 0) {
                printf("Merging\n");
                btree_merge_child(root, i-1, p, y);
                btree_pretty_display(root);
                y = p;
            } else {
                printf("Merging\n");
                btree_merge_child(root, i, y, z);
                btree_pretty_display(root);
            }
            int child0_before_delete = y->k[0];
            btree_delete_nonone(y, target);
            if (y->k[0] != child0_before_delete && i>0) {
                printf("child0 is changed, child0_before: %d, child0_after: %d\n", child0_before_delete, y->k[0]);
                // TODO if go to tree root, there is no need to update, the code now actually update something he should not touch
                int root_before_change = root->k[i-1];
                root->k[i-1]=y->k[0];
                printf("update root, root: %d changed to %d\n", root_before_change ,root->k[i-1]);
            }
        } else {
            int child0_before_delete = y->k[0];
            btree_delete_nonone(y, target);
            if (y->k[0] != child0_before_delete && i>0) {
                printf("child0 is changed, child0_before: %d, child0_after: %d\n", child0_before_delete, y->k[0]);
                // TODO if go to tree root, there is no need to update, the code now actually update something he should not touch (solved)
                // TODO 问题变成了最右面的最小值改变，根结点不会被改变
                // Internal node 不会有重复
                // TODO 内部节点child0改变不应该更新内部节点的父亲
                int root_before_change = root->k[i-1];
                root->k[i-1]=y->k[0];
                printf("update root, root: %d changed to %d\n", root_before_change ,root->k[i-1]);
            }
        }
    }
}

int BPlusTree::btree_search_predecessor(btree_node *root)
{
    btree_node *y = root;
    while(false == y->is_leaf) {
        y = y->p[y->num];
    }
    return y->k[y->num-1];
}

int BPlusTree::btree_search_successor(btree_node *root)
{
    btree_node *z = root;
    while(false == z->is_leaf) {
        z = z->p[0];
    }
    return z->k[0];
}

void BPlusTree::btree_shift_to_right_child(btree_node *root, int pos,
                                           btree_node *y, btree_node *z)
{
    z->num += 1;
    for(int i = z->num -1; i > 0; i--) {
        z->k[i] = z->k[i-1];
    }
    if(false == z->is_leaf) {
        z->k[0] = root->k[pos];
        root->k[pos] = y->k[y->num-1];
    } else {
        z->k[0] = y->k[y->num-1];
        printf("root->k %d\n", root->k[pos]);
        root->k[pos+1] = z->k[0];
    }

    if(false == z->is_leaf) {
        for(int i = z->num; i > 0; i--) {
            z->p[i] = z->p[i-1];
        }
        z->p[0] = y->p[y->num];
    }

    y->num -= 1;
}

void BPlusTree::btree_shift_to_left_child(btree_node *root, int pos,
                                          btree_node *y, btree_node *z)
{
    y->num += 1;

    if(false == z->is_leaf) {
        y->k[y->num-1] = root->k[pos];
        root->k[pos] = z->k[0];
    } else {
        y->k[y->num-1] = z->k[0];
        root->k[pos] = z->k[0];
    }

    for(int j = 1; j < z->num; j++) {
        z->k[j-1] = z->k[j];
    }

    if(false == z->is_leaf) {
        y->p[y->num] = z->p[0];
        for(int j = 1; j <= z->num; j++) {
            z->p[j-1] = z->p[j];
        }
    }

    z->num -= 1;
}

void BPlusTree::btree_inorder_print(btree_node *root)
{
    if(NULL != root) {
        btree_inorder_print(root->p[0]);
        for(int i = 0; i < root->num; i++) {
            printf("%d ", root->k[i]);
            //     fwrite(&root,sizeof(root),1,fp);
            btree_inorder_print(root->p[i+1]);
        }
    }
}

void BPlusTree::btree_linear_print(btree_node *root)
{
    if(NULL != root) {
        btree_node *leftmost = root;
        while(false == leftmost->is_leaf) {
            leftmost = leftmost->p[0];
        }

        btree_node *iter = leftmost;
        do {
            for(int i = 0; i < iter->num; i++) {
                printf("%d ", iter->k[i]);
                //    fwrite(&root,sizeof(root),1,fp);
            }
            iter = iter->next;
        } while(iter != leftmost);
        printf("\n");
    }
}

void BPlusTree::Save(btree_node *root)
{
    //    fwrite(root,sizeof(root),1,pfile);
}

void BPlusTree::btree_level_display(btree_node *root)
{
    // just for simplicty, can't exceed 200 nodes in the tree
    btree_node *queue[200] = {NULL};
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while(front < rear) {
        btree_node *node = queue[front++];

        printf("[");
        for(int i = 0; i < node->num; i++) {
            printf("%d ", node->k[i]);
        }
        printf("]");

        for(int i = 0; i <= node->num; i++) {
            if(NULL != node->p[i]) {
                queue[rear++] = node->p[i];
            }
        }
    }
    printf("\n");
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
            std::cout <<" "<< tmp->k[i]<<" ";
            if (!tmp->is_leaf&&i != tmp->num - 1) {
                std::cout << "|";
            }
        }
        
        std::cout << ")";
        if (!tmp->is_leaf) {   //不是叶子结点才有孩子
            std::cout << "|";
            for (int i = 0;i < tmp->num + 1;++i) {
                Q.push(tmp->p[i]);
            }
        }
        if (!last->is_leaf&&tmp == last) {
            std::cout << std::endl;
            last = last->p[last->num];
        }
    }
    std::cout << std::endl;
}

void BPlusTree::linear_print()
{
    btree_linear_print(roots);
}

//BPlusTree::BPlusTree(void)
//{
//    // 先判断文件是否存在
//    // windows下，是io.h文件，linux下是 unistd.h文件
//    // int access(const char *pathname, int mode);
//    if(-1==access("define.Bdb",F_OK))
//    {
//        // 不存在 ,创建
//        //           pfile = fopen("bplus.bp","w");
//        roots = btree_create();
//    }
//    else
//    {
//        //           pfile = fopen("bplus.bp","r+");
//        roots = btree_create();
//        //           fread(roots,sizeof(roots),1,pfile);
//    }
//}

BPlusTree::BPlusTree(void)
{
    roots = btree_create();
}


BPlusTree::~BPlusTree(void)
{

}
