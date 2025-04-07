#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODES 10

const char* nodeNames[NODES] = {
    "I1", "I2", "I3", "I4", "G1", "G2", "G3", "G4", "O1", "O2"
};

int graph[NODES][NODES];

int delay[NODES] = {0};

int prev[NODES];

int inDegree[NODES] = {0};

void setupGraph()
 {
    memset(graph, 0, sizeof(graph));
    memset(inDegree, 0, sizeof(inDegree));
    memset(delay, 0, sizeof(delay));
    for (int i = 0; i < NODES; i++) prev[i] = -1;

    graph[0][4] = 1;  
    graph[1][4] = 2; 
    graph[1][5] = 2;  
    graph[2][5] = 3;  
    graph[3][7] = 4; 
    graph[4][6] = 2;  
    graph[5][6] = 3;  
    graph[5][7] = 3;  
    graph[6][8] = 1;  
    graph[7][9] = 2;  
}

void printPath(int node)
 {
    if (prev[node] != -1)
        printPath(prev[node]);
    printf("%s ", nodeNames[node]);
}

void computeDelays() {
    int queue[NODES], front = 0, rear = 0;

    for (int i = 0; i < NODES; i++) {
        for (int j = 0; j < NODES; j++) {
            if (graph[i][j] > 0)
                inDegree[j]++;
        }
    }

    for (int i = 0; i < NODES; i++) {
        if (inDegree[i] == 0)
            queue[rear++] = i;
    }

    while (front < rear) {
        int current = queue[front++];

        for (int next = 0; next < NODES; next++) {
            if (graph[current][next] > 0) {
                int edgeDelay = graph[current][next];
                if (delay[next] < delay[current] + edgeDelay) {
                    delay[next] = delay[current] + edgeDelay;
                    prev[next] = current;
                }
                if (--inDegree[next] == 0)
                    queue[rear++] = next;
            }
        }
    }
}

int main() {
    setupGraph();  

    computeDelays();

    printf("Delay to O1: %d ns\n", delay[8]);
    printf("Path to O1: ");
    printPath(8);
    printf("\n\n");

    printf("Delay to O2: %d ns\n", delay[9]);
    printf("Path to O2: ");
    printPath(9);
    printf("\n");

    return 0;
}

Delay to O1: 7 ns
Path to O1: I3 G2 G3 O1 

Delay to O2: 8 ns
Path to O2: I3 G2 G4 O2
