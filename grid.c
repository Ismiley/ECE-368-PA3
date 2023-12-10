#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "grid.h"

// downward heapify
void downwardHeapify(PriorityQueue * q, int i){
    GraphNode * tempNode = q->nodes[i];
    int j = 2 * i + 1;
    while(j <= q->size - 1){
        if (j < q->size - 1 && q->nodes[j]->distance > q->nodes[j+1]->distance){
            j += 1;
        }
        if (tempNode->distance <= q->nodes[j]->distance){
            break;
        }
        else{
            q->nodes[i] = q->nodes[j];
            i = j;
            j = 2 * i + 1;
        }
    }
    q->nodes[i] = tempNode;

}

// upward heapify
void upwardHeapify(PriorityQueue * q, int n){

    GraphNode * newNode = q->nodes[n];
    int child = n;
    int parent = (child - 1) / 2;
    while( child > 0 && q->nodes[parent]->distance > newNode->distance){
        q->nodes[child] = q->nodes[parent];
        child = parent;
        parent = (child - 1) / 2;
    }
    q->nodes[child] = newNode;
}


// Add a node to the priority queue
void push(PriorityQueue *q, GraphNode * tempNode) {

    q->nodes[q->size] = tempNode;
    q->size++;

}

// Remove the node with the smallest distance from the priority queue
GraphNode * pop(PriorityQueue *q) {
    // Save the node at the front of the queue
    GraphNode * node = q->nodes[0];

    q->nodes[0] = q->nodes[q->size - 1];

    downwardHeapify(q, 0); // downward heapify
  
    q->size--;
 
    return node;
}

// Check if the node is in the priority queue
int checkPQ(PriorityQueue * q, GraphNode * tempNode){
    int nodeInPQ = -1;
    for (int i = 0; i < q->size; i++){
        if ((q->nodes[i]->row == tempNode->row) && (q->nodes[i]->col == tempNode->col)){
            nodeInPQ = i;
        }
    }
    return nodeInPQ;
}



// dijsktra's algo
void dijkstras(PriorityQueue * q, GraphNode ** grid, int rows, int cols, int idx){

    q->size = 0;

    // iterate through first row of nodes as source nodes --> in this function or outside?
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            grid[r][c].distance = INT_MAX;
            grid[r][c].pred = NULL;
            grid[r][c].row = r;
            grid[r][c].col = c;
            push(q, &(grid[r][c]));
        }
    }
    
    grid[0][idx].distance = 0;
    int tempIndx = checkPQ(q, &(grid[0][idx]));
    upwardHeapify(q, tempIndx); // upward

    while(q->size != 0){
        GraphNode * tempNode = pop(q);
        
        // go through each direction and check if within bounds and if not visited
        int indx = -1;
        // check right
        if (tempNode->col + 1 < cols){
            indx = checkPQ(q, &(grid[tempNode->row][tempNode->col + 1]));
            if (indx != -1 && 
                (grid[tempNode->row][tempNode->col + 1].distance > 
                    grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight)){
                grid[tempNode->row][tempNode->col + 1].distance = grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight;
                
                grid[tempNode->row][tempNode->col + 1].pred = &(grid[tempNode->row][tempNode->col]);   
                
                upwardHeapify(q, indx);   
            }
        }

        // check left
        if (tempNode->col - 1 >= 0){
            indx = checkPQ(q, &(grid[tempNode->row][tempNode->col - 1]));
            if (indx != -1 && 
                (grid[tempNode->row][tempNode->col - 1].distance > 
                grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight)){
                    
                grid[tempNode->row][tempNode->col - 1].distance = grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight;
                
                grid[tempNode->row][tempNode->col - 1].pred = &(grid[tempNode->row][tempNode->col]);  
                
                upwardHeapify(q, indx);     
            }
        }

        // check up
        if (tempNode->row - 1 >= 0){
            indx = checkPQ(q, &(grid[tempNode->row - 1][tempNode->col]));
            if (indx != -1 && 
                (grid[tempNode->row - 1][tempNode->col].distance 
                > grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight)){

                grid[tempNode->row - 1][tempNode->col].distance = grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight;
                
                grid[tempNode->row - 1][tempNode->col].pred = &(grid[tempNode->row][tempNode->col]); 
                
                upwardHeapify(q, indx);      
            }
        }

        // check down
        if (tempNode->row + 1 < rows){
            indx = checkPQ(q, &(grid[tempNode->row + 1][tempNode->col]));
            if (indx != -1 && 
                (grid[tempNode->row + 1][tempNode->col].distance > 
                grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight)){
                
                grid[tempNode->row + 1][tempNode->col].distance = grid[tempNode->row][tempNode->col].distance + grid[tempNode->row][tempNode->col].weight;
                
                grid[tempNode->row + 1][tempNode->col].pred = &(grid[tempNode->row][tempNode->col]);  
                
                upwardHeapify(q, indx);     
            }
        }

    }
}



// input grid (2d array)
void readGrid(char * filename, char * textFileName, char * timesFileName, char * pathFileName){
    
    FILE *fptr = fopen(filename, "rb");
    if(fptr == NULL){
        fclose(fptr);
    }
    
    short * tempVal = (short *) malloc(sizeof(short));

    // set num rows
    fread(tempVal, sizeof(short), 1, fptr);
    int rows = (int) *tempVal;

    // set num cols
    fread(tempVal, sizeof(short), 1, fptr);
    int cols = (int) *tempVal;

    // allocate grid memory
    GraphNode** grid = (GraphNode**)malloc(rows * sizeof(GraphNode*));
    for (int i = 0; i < rows; i++)
        grid[i] = (GraphNode*) malloc(cols * sizeof(GraphNode));

    
    // fill in grid
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            fread(tempVal, sizeof(short), 1, fptr);
            (grid[r][c]).weight = (int) *tempVal;
        }
    }

    free(tempVal);
    fclose(fptr);

    FILE *fptr3 = fopen(timesFileName, "wb");
    if(fptr3 == NULL){
        fclose(fptr3);
    } 
    fwrite(&cols, 1, sizeof(short), fptr3);

    // test minheap
    PriorityQueue * q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    q->size = 0;
    q->nodes = (GraphNode **) malloc(rows * cols * sizeof(GraphNode *));
    
    int minIdx = 0;
    int minDistance = INT_MAX;
    int minRow = INT_MAX;
    int minCol = INT_MAX;
    for (int rIdx = 0; rIdx < cols; rIdx++){
        dijkstras(q, grid, rows, cols, rIdx);
        int minDistanceForWrite = INT_MAX;
        for (int i = 0; i < cols; i++){
            if (grid[rows-1][i].distance + grid[rows-1][i].weight < minDistance){
                minDistance = grid[rows-1][i].distance + grid[rows-1][i].weight;
                minRow = grid[rows-1][i].row;
                minCol = grid[rows-1][i].col;
                minIdx = rIdx;
                
            }
            if (grid[rows-1][i].distance + grid[rows-1][i].weight < minDistanceForWrite){
                minDistanceForWrite = grid[rows-1][i].distance + grid[rows-1][i].weight;
                
            }
        }
        fwrite(&minDistanceForWrite, 1, sizeof(int), fptr3);
        
        /*
        printf("MINDISTANCE: %hd\n", minDistance);
        printf("MINDISTANCETEMP: %d\n", minDistanceForWrite);
        for (int r = 0; r < rows; r++){
            for (int c = 0; c < cols; c++){
                printf("%hd ", (grid[r][c]).distance);
            }
            printf("\n");
        }
        */
        
    }

    dijkstras(q, grid, rows, cols, minIdx);
    
    /*
    printf("MINDISTANCE: %d\n", minDistance);
    
    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            printf("%d ", (grid[r][c]).distance);
        }
        printf("\n");
    }
    */

    
    
    // make text file
    FILE *fptr2 = fopen(textFileName, "w");
    if(fptr2 == NULL){
        fclose(fptr2);
    }
    
    fprintf(fptr2, "%hd %hd\n", (short) rows, (short) cols);

    for (int r = 0; r < rows; r++){
        for (int c = 0; c < cols; c++){
            fprintf(fptr2, "%hd", (short) (grid[r][c]).weight);
            if (c != cols - 1){
                fprintf(fptr2, " ");
            }
        }
        fprintf(fptr2, "\n");
    }

    fclose(fptr2);

    

    // make fastest time file

    fclose(fptr3);

    // make fastest time's path file
    FILE *fptr4 = fopen(pathFileName, "wb");
    if(fptr4 == NULL){
        fclose(fptr4);
    }
    
    int timeToWrite = (int) minDistance;
    //printf("MINDSTNACE: %d\n", timeToWrite);
    fwrite(&timeToWrite, 1, sizeof(int), fptr4);

    int pathSize = 1;
    
    LinkedList * head = (LinkedList*) malloc(sizeof(LinkedList));
    head->row = minRow;
    head->col = minCol;

    
    
    //printf("\n%hd,%hd\n", minRow, minCol);
    while(grid[minRow][minCol].pred != NULL){
        int tempRow;
        int tempCol;
        tempRow = (grid[minRow][minCol].pred)->row;
        tempCol = (grid[minRow][minCol].pred)->col;
        minRow = tempRow;
        minCol = tempCol;
        LinkedList * tempListNode = (LinkedList*) malloc(sizeof(LinkedList));
        tempListNode->row = minRow;
        tempListNode->col = minCol;
        tempListNode->next = head;
        head = tempListNode;
        //printf("\n%hd,%hd\n", minRow, minCol);
        pathSize += 1;
    }
    
    //printf("PATHSIZE: %d\n", pathSize);
    fwrite(&pathSize, 1, sizeof(int), fptr4);
    
    LinkedList * pathNode;
    for(int i = 0; i < pathSize; i++){
        //printf("\n%hd,%hd\n", head->row, head->col);
        fwrite(&(head->row), 1, sizeof(short), fptr4);
        fwrite(&(head->col), 1, sizeof(short), fptr4);
        pathNode = head;
        head = head->next;
        free(pathNode);
    }
    

    fclose(fptr4);

    
    free(q->nodes);
    free(q);

    for (int i = 0; i < rows; i++)
        free(grid[i]);
    
    free(grid);

}

