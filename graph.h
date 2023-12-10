// GraphNode structure
typedef struct _GraphNode {
  int weight;
  int distance;
  int row;
  int col;
  struct _GraphNode *pred;
} GraphNode;


// Priority queue data structure
typedef struct _PriorityQueue {
    // array of GraphNodes
    GraphNode ** nodes;
    // Number of nodes in the queue
    int size;
} PriorityQueue;

// linked list for path
typedef struct _LinkedList {
    int row;
    int col;
    struct _LinkedList * next;
} LinkedList;