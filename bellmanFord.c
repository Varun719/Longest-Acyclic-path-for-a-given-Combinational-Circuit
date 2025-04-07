#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NODES 10
#define EDGES 10
#define INF 9999

const char* nodeNames[NODES] = {
    "I1", "I2", "I3", "I4", "G1", "G2", "G3", "G4", "O1", "O2"
};

// Graph edges: u → v with weight (delay)
typedef struct {
    int from, to, weight;
} Edge;

Edge edges[EDGES] = {
    {0, 4, 1},  // I1 → G1
    {1, 4, 2},  // I2 → G1
    {1, 5, 2},  // I2 → G2
    {2, 5, 3},  // I3 → G2
    {3, 7, 4},  // I4 → G4
    {4, 6, 2},  // G1 → G3
    {5, 6, 3},  // G2 → G3
    {5, 7, 3},  // G2 → G4
    {6, 8, 1},  // G3 → O1
    {7, 9, 2}   // G4 → O2
};

int distance[NODES];
int prev[NODES];

void initialize() {
    for (int i = 0; i < NODES; i++) {
        distance[i] = -INF;  // Since we want to maximize
        prev[i] = -1;
    }

    // Inputs (I1-I4) are potential sources, so set their delay to 0
    distance[0] = 0;
    distance[1] = 0;
    distance[2] = 0;
    distance[3] = 0;
}

void bellmanFord() {
    for (int i = 0; i < NODES - 1; i++) {
        for (int j = 0; j < EDGES; j++) {
            int u = edges[j].from;
            int v = edges[j].to;
            int w = edges[j].weight;

            if (distance[u] + w > distance[v]) {
                distance[v] = distance[u] + w;
                prev[v] = u;
            }
        }
    }
}

void printPath(int node) {
    if (prev[node] != -1)
        printPath(prev[node]);
    printf("%s ", nodeNames[node]);
}

int main() {
    initialize();
    bellmanFord();

    printf("Delay to O1: %d ns\n", distance[8]);
    printf("Path to O1: ");
    printPath(8);
    printf("\n\n");

    printf("Delay to O2: %d ns\n", distance[9]);
    printf("Path to O2: ");
    printPath(9);
    printf("\n");

    return 0;
}
