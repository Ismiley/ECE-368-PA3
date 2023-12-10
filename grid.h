#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graph.h"

void upwardHeapify(PriorityQueue * q, int i);
void downwardHeapify(PriorityQueue * q, int i);
void push(PriorityQueue *q, GraphNode * tempNode);
GraphNode * pop(PriorityQueue *q);
int checkPQ(PriorityQueue * q, GraphNode * tempNode);
void dijkstras(PriorityQueue * q, GraphNode ** grid, int rows, int cols, int idx);
void readGrid(char * filename, char * textFileName, char * timesFileName, char * pathFileName);