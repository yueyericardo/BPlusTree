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
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;


// if the command is Insert, Delete, or Search one key
void run(char* com, int key1, double key2, BPlusTree *bpt, std::ofstream& outputfile){
    string command = com;
    if (command.compare("Insert") == 0){
        printf("Insert %d\n", key1);
        bpt->Insert(key1, key2);
    } else if (command.compare("Delete") == 0){
        printf("Delete %d\n", key1);
        bpt->Delete(key1);
    } else if (command.compare("Search") == 0){
        printf("Search %d\n", key1);
        double* result = bpt->Search(key1);
        if (result != NULL) {
            if (outputfile.is_open()){
                outputfile << *result;
                outputfile<<endl;
            }else {
                cout << "Unable to open file";
            }
        }else{
            if (outputfile.is_open()){
                outputfile << "Null";
                outputfile<<endl;
            }else {
                cout << "Unable to open file";
            }
        }

    } else {
        printf("This operation is not defined");
    }
}

// if the command is search two key
void run_search_twokey(int key1, double key2, BPlusTree *bpt, std::ofstream& outputfile){
    std::vector<double> result = bpt->Search(key1, key2);
    if (outputfile.is_open()){
        if (result.size() == 0) {
            outputfile << "Null";
        }else{
            for(int i = 0; i < result.size(); i++){
                outputfile << result[i];
                if (i < result.size()-1) {outputfile<<',';}
            }
        }
        outputfile<<endl;
    }
    else {
        cout << "Unable to open file";
    }
}

// Test
void test(BPlusTree *bpt){

    int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 63, 56, 90, 87, 77, 66, 52, 23, 30, 20};
    double value[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 63, 56, 90, 87, 77, 66, 52, 23, 30, 20};
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++) {
        printf("\n");
        printf("Inserting %d\n", arr[i]);
        bpt->Insert(arr[i], value[i]);
        printf("Final: \n");
        bpt->pretty_display();
        printf("key: ");
        bpt->linear_print();
        printf("val: ");
        bpt->value_display();
    }
    
    printf("\n");
    bpt->pretty_display();
    bpt->linear_print();
    printf("\n");
    
    printf("===================================\n");
    printf("deleteing data\n");
    printf("===================================\n\n");
    
    int todel[] = {31, 48, 45, 47, 50};
    
    for(int i = 0; i < sizeof(todel) / sizeof(int); i++) {
        printf("deleting %d\n", todel[i]);
        bpt->Delete(todel[i]);
        bpt->pretty_display();
        printf("key: ");
        bpt->linear_print();
        printf("val: ");
        bpt->value_display();
        printf("\n");
    }
    
    // single key search
    bpt->Search(52);
    bpt->Search(13);
    
    // range key search
    // smaller than smallest
    bpt->Search(9, 9);
    
    // bigger than biggest
    bpt->Search(13, 13);
    bpt->Search(100, 101);
    
    // between a range, but this range contain no key
    bpt->Search(53, 54);
    
    bpt->Search(10, 11);
    bpt->Search(50, 87);
    bpt->Search(63, 63);
    bpt->Search(56, 66);
    bpt->Search(50, 86);
    bpt->Search(50, 87);
    bpt->Search(50, 88);
}

int main(int argc,char **argv) {
    
//    ifstream inputfile (argv[1]);
    ifstream inputfile ("example_input.txt");
    ofstream outputfile ("output_file.txt");
    
    string line;
    
    // Initialize
    getline(inputfile, line);
    char* buffer = strdup(line.c_str());
    char command[20];
    int key1;
    std::sscanf(buffer, "%[a-zA-Z] (%d)", command, &key1);
    BPlusTree bpt = BPlusTree(key1) ;
    printf("%s BPlustree, m = %d\n", command, key1);
    
    
    if (inputfile.is_open()){
        while (getline(inputfile, line))
        {
             printf("----------------------------------------------\n");
            std::cout << line << '\n';

            char* buffer = strdup(line.c_str());
            char command[20];
            int key1;
            double key2;
            std::sscanf(buffer, "%[a-zA-Z] (%d, %lf)", command, &key1, &key2);
            
            // if the command is search two key
            if(std::regex_match (line, std::regex("Search[ ]*\\([0-9]*,[ ]*[0-9]*\\)") )){
                run_search_twokey(key1, key2, &bpt, outputfile);
            }
            // else
            else{
                run(command, key1, key2, &bpt, outputfile);
            }
            
            free(buffer);
        }
        inputfile.close();
        
    }
    else {
        std::cout << "Unable to open file \n";
    }
    outputfile.close();
    bpt.pretty_display();

//    BPlusTree bpt = BPlusTree(2) ;
//    test(&bpt);
    
}

