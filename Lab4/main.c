//
//  main.c
//  Lab4
//
//  Created by Matthew Taylor on 7/19/20.
//  Copyright © 2020 Matthew Taylor. All rights reserved.
//
// CST 334 Lab 4 – FIFO Page Replacement Simulation File I/O Template

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "node.h"

struct queue *q;

typedef struct {//to
    int pageno;
} ref_page;

int main(int argc, char *argv[]){
    int C_SIZE = atoi(argv[1]); // Size of Cache passed by user
    //int C_SIZE = 5;
    ref_page cache[C_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    q = queue_create();

    int i;
    int hit = 0;
    int entries = 0;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < C_SIZE; i++){//initialise cache array
         cache[i].pageno = -1;
    }
    
    while (fgets(pageCache, 100, stdin)){
        int page_num = atoi(pageCache); //Stores number read from file as int
        
        //If the q has room, add current record to q
        if (entries < C_SIZE) {
            enqueue(q, page_num);
            cache[entries].pageno = page_num;
            entries++;
            totalFaults++;
        }
        // otherwise, something needs to be replaced
        else {
            //this is a new page?
            if(queue_find(q, page_num) == NULL) {
                dequeue(q);
                totalFaults++;
                enqueue(q, page_num);
            }
            else {
                //already there, do nothing
                hit++;
            }
        }
        
    }

    printf("%d Total Page Faults \n%d Total Page Hits\n", totalFaults, hit);
    return 0;

}
