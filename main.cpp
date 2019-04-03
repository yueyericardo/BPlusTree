//
//  main_bplus.cpp
//  cop5536
//
//  Created by Richard Xue on 3/31/19.
//  Copyright © 2019 jinzexue. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "BPlusTree.hpp"

int main()
{
    BPlusTree bpt = BPlusTree(3) ;
    
    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 63, 56, 90, 87, 77, 66, 52, 23, 30, 20};
    double value[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 63, 56, 90, 87, 77, 66, 52, 23, 30, 20};
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("\n");
        printf("Inserting %d\n", arr[i]);
        bpt.Insert(arr[i], value[i]);
        printf("Final: \n");
        bpt.pretty_display();
        printf("key: ");
        bpt.linear_print();
        printf("val: ");
        bpt.value_display();
    }

    printf("\n");
    bpt.pretty_display();
    bpt.linear_print();
    printf("\n");

    printf("===================================\n");
    printf("deleteing data\n");
    printf("===================================\n\n");

    int todel[] = {31, 48, 45, 47, 50};

    for(int i = 0; i < sizeof(todel) / sizeof(int); i++) {
        printf("deleting %d\n", todel[i]);
        bpt.Delete(todel[i]);
        bpt.pretty_display();
        printf("key: ");
        bpt.linear_print();
        printf("val: ");
        bpt.value_display();
        printf("\n");
    }

    bpt.Search(52);
    bpt.Search(20);
    bpt.Search(15);
    bpt.Search(12, 13);
    bpt.Search(50, 87);
    bpt.Search(63, 63);
    bpt.Search(56, 66);
    bpt.Search(50, 87);
}

