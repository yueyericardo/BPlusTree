//
//  main_bplus.cpp
//  cop5536
//
//  Created by Richard Xue on 3/31/19.
//  Copyright © 2019 jinzexue. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "BTree.hpp"
#include "BPlusTree.hpp"
#include "Context.h"

int main()
{
    
    /*************************************直接调用B  B+ 的调度使用****************************************/
    /************************************* Direct call B + B method ****************************************/
    BTree bt;
    BPlusTree bpt;
    
    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20};
//    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20, 60, 46, 70, 36};
//    int arr[] = {18, 31, 12, 10, 15, 48, 45};
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
//        bt.insert(arr[i]);
        printf("\n");
        printf("Inserting %d\n", arr[i]);
        bpt.insert(arr[i]);
        bpt.pretty_display();
    }
//    printf("no delete data:\n");
//    printf("display about B-Tree:\n");
//    bt.level_display();
//    bt.inorder_print();
//    printf("\n");
//    bt.pretty_display();
//    printf("\n\n");
    
//    printf("display about B+ Tree:\n");
//    bpt.level_display();
//    bpt.inorder_print();
    printf("\n");
    bpt.pretty_display();
//    bpt.linear_print();
    printf("\n");
//    bt.NodeNum_print();
//    bpt.NodeNum_print();
    printf("===================================\n");
    printf("deleteing data\n");
    printf("===================================\n\n");
    int todel[] = {15, 18, 23, 30, 31, 52, 50};
//    int todel[] = {48, 31, 18};
//
//    bt.pretty_display();
//    for(int i = 0; i < sizeof(todel) / sizeof(int); i++) {
//        printf("after delete %d\n", todel[i]);
//        bt.del(todel[i]);
//        bt.pretty_display();
//        printf("\n");
//    }
    bpt.pretty_display();
    for(int i = 0; i < sizeof(todel) / sizeof(int); i++) {
        printf("deleting %d\n", todel[i]);
        bpt.del(todel[i]);
        bpt.pretty_display();
        printf("\n");
    }
//
//    bt.NodeNum_print();
//    bpt.NodeNum_print();
//
//    printf("\n\ndelete after data:\n");
//    printf("display about B-Tree:\n");
//    bt.level_display();
//    bt.inorder_print();
//    printf("\n\n");
//
//    printf("display about B+ Tree:\n");
//    bpt.level_display();
//    bpt.inorder_print();
//    printf("\n");
//    bpt.linear_print();
//    printf("\n");
}

