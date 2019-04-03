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
    BTree bt;
    BPlusTree bpt;
    
    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 63, 56, 90, 87, 77, 66, 52, 23, 30, 20};
//    int arr[] = {62, 89, 79, 80, 92, 50, 58, 24, 61, 99, 48, 70, 35, 97, 72, 6, 53, 3, 59, 52, 83, 93, 13, 23, 56, 60, 42, 41, 86, 84, 67, 96, 65, 10, 64, 55, 73, 29, 68, 31, 46, 57, 14, 12, 43, 26, 4, 16, 19, 32, 37, 91, 30, 9, 11, 27, 33, 74, 25, 15, 94, 51, 47, 34, 18, 69, 54, 17, 1, 2, 78, 66, 77, 5, 45, 40, 87, 39, 8, 88, 20, 36, 22, 0, 81, 75, 85, 38, 7, 82, 76, 98, 71, 63, 21, 28, 95, 44, 90, 49};
//    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20, 60, 46, 70, 36};
//    int arr[] = {18, 31, 12, 10, 15, 48, 45};
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
//        bt.insert(arr[i]);
        printf("\n");
        printf("Inserting %d\n", arr[i]);
        bpt.insert(arr[i]);
        printf("Final: \n");
        bpt.pretty_display();
    }

    printf("\n");
    bpt.pretty_display();
    bpt.linear_print();
    printf("\n");

    printf("===================================\n");
    printf("deleteing data\n");
    printf("===================================\n\n");
//    int todel[] = {15, 18, 23, 30, 31, 52, 50};
//    int todel[] = {15, 18, 23, 30, 31};
    int todel[] = {31, 48, 45, 47, 50, 30, 23, 63, 56, 90, 87, 77, 66};
//    int todel[] = {42, 5, 64, 27, 85, 41, 82, 95, 62, 88, 92, 2, 11, 59, 20, 8, 32, 28, 84, 60, 47, 86, 23, 79, 1, 77, 76, 63, 44, 0, 34, 39, 89, 21, 56, 36, 38, 6, 13, 9, 48, 72, 67, 29, 55, 70, 40, 57, 69, 97, 54, 68, 96, 35, 33, 16, 43, 78, 19, 22, 30, 98, 74, 3, 73, 94, 65, 7, 50, 15};
//    int todel[] = {12, 15, 20, 23, 30, 18, 31};

    for(int i = 0; i < sizeof(todel) / sizeof(int); i++) {
        printf("deleting %d\n", todel[i]);
        bpt.del(todel[i]);
        bpt.pretty_display();
        printf("\n");
    }
    bpt.linear_print();
}

