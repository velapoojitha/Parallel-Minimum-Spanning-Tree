#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define INF 1000000  // A large value representing infinity

// Edge structure
typedef struct {
    int src, dest, weight;
} Edge;

// Function to find the parent of a vertex (union-find)
int find(int parent[], int vertex) {
    if (parent[vertex] != vertex)
        parent[vertex] = find(parent, parent[vertex]);  // Path compression
    return parent[vertex];
}

// Function to unite two sets
void unite(int parent[], int rank[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Borůvka's algorithm for MST
void boruvkaMST(Edge edges[], int V, int E, int num_threads) {
    int *parent = (int *)malloc(V * sizeof(int));
    int *rank = (int *)malloc(V * sizeof(int));
    int *cheapest = (int *)malloc(V * sizeof(int));
    int num_components = V;
    int MST_weight = 0;

    // Initialize union-find sets
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
        cheapest[i] = -1;
    }

    omp_set_num_threads(num_threads);

    while (num_components > 1) {
        // Reset cheapest array
        for (int i = 0; i < V; i++) {
            cheapest[i] = -1;
        }

        // Find cheapest edge for each component in parallel
        #pragma omp parallel for
        for (int i = 0; i < E; i++) {
            int u = find(parent, edges[i].src);
            int v = find(parent, edges[i].dest);
            if (u != v) {  // Only consider edges between different components
                #pragma omp critical
                {
                    if (cheapest[u] == -1 || edges[i].weight < edges[cheapest[u]].weight) {
                        cheapest[u] = i;
                    }
                    if (cheapest[v] == -1 || edges[i].weight < edges[cheapest[v]].weight) {
                        cheapest[v] = i;
                    }
                }
            }
        }

        // Add selected edges to MST
        for (int i = 0; i < V; i++) {
            if (cheapest[i] != -1) {
                int u = find(parent, edges[cheapest[i]].src);
                int v = find(parent, edges[cheapest[i]].dest);

                if (u != v) {
                    MST_weight += edges[cheapest[i]].weight;
                    printf("Adding edge: %d -- %d (Weight: %d)\n",
                           edges[cheapest[i]].src, edges[cheapest[i]].dest,
                           edges[cheapest[i]].weight);
                    unite(parent, rank, u, v);
                    num_components--;
                }
            }
        }
    }

    printf("Total weight of MST: %d\n", MST_weight);

    free(parent);
    free(rank);
    free(cheapest);
}

int main() {
    int V, E, num_threads;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    Edge *edges = (Edge *)malloc(E * sizeof(Edge));

    printf("Enter the edges (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    printf("Enter the number of threads to use: ");
    scanf("%d", &num_threads);

    // Measure execution time
    double start_time = omp_get_wtime();
    printf("Finding MST using Borůvka's Algorithm with %d threads...\n", num_threads);
    boruvkaMST(edges, V, E, num_threads);
    double end_time = omp_get_wtime();

    printf("Execution time with %d threads: %f seconds\n", num_threads, end_time - start_time);

    free(edges);
    return 0;
}
