#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODES 10

const char* nodeNames[NODES] = {
    "I1", "I2", "I3", "I4", "G1", "G2", "G3", "G4", "O1", "O2"
};

int graph[NODES][NODES];      
int delay[NODES];             
int visited[NODES];           
int prev[NODES];              

void setupGraph() {
    memset(graph, 0, sizeof(graph));
    memset(delay, -1, sizeof(delay));  
    memset(visited, 0, sizeof(visited));
    memset(prev, -1, sizeof(prev));

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

int dfs(int node) {
    if (delay[node] != -1) return delay[node];

    int maxDelay = 0;

    for (int i = 0; i < NODES; i++) {
        if (graph[i][node] > 0) {
            int temp = dfs(i) + graph[i][node];
            if (temp > maxDelay) {
                maxDelay = temp;
                prev[node] = i;
            }
        }
    }

    delay[node] = maxDelay;
    return maxDelay;
}

void printPath(int node) {
    if (prev[node] != -1) printPath(prev[node]);
    printf("%s ", nodeNames[node]);
}

int main() {
    setupGraph();

    int delayToO1 = dfs(8);  
    int delayToO2 = dfs(9);  

    printf("Delay to O1: %d ns\n", delayToO1);
    printf("Path to O1: ");
    printPath(8);
    printf("\n\n");

    printf("Delay to O2: %d ns\n", delayToO2);
    printf("Path to O2: ");
    printPath(9);
    printf("\n");

    return 0;
}
