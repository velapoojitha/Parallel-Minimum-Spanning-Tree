#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define INF 1000000 // A large number representing infinity

typedef struct {
    int src, dest, weight;
} Edge;

// Function to generate a random graph
void generate_graph(int vertices, int edges, const char *filename, int threads) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(file, "%d %d\n", vertices, edges);

    srand(time(NULL)); // Seed for random number generation

    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        do {
            src = rand() % vertices;
            dest = rand() % vertices;
        } while (src == dest); // Avoid self-loops

        weight = (rand() % 100) + 1;
        #pragma omp critical
        fprintf(file, "%d %d %d\n", src, dest, weight);
    }

    fclose(file);
    printf("Graph generated and saved to %s using %d threads\n", filename, threads);
}

// Function to read a graph from a file
Edge *read_graph(const char *filename, int *vertices, int *edges) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fscanf(file, "%d %d", vertices, edges);

    Edge *edgeList = (Edge *)malloc((*edges) * sizeof(Edge));
    if (edgeList == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < *edges; i++) {
        fscanf(file, "%d %d %d", &edgeList[i].src, &edgeList[i].dest, &edgeList[i].weight);
    }

    fclose(file);
    return edgeList;
}

// Comparison function for sorting edges by weight
int compare_edges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

// Sequential Union-Find Functions
int find_parent(int *parent, int vertex) {
    if (parent[vertex] != vertex) {
        parent[vertex] = find_parent(parent, parent[vertex]);
    }
    return parent[vertex];
}

void union_vertices(int *parent, int *rank, int u, int v) {
    int rootU = find_parent(parent, u);
    int rootV = find_parent(parent, v);

    if (rank[rootU] > rank[rootV]) {
        parent[rootV] = rootU;
    } else if (rank[rootU] < rank[rootV]) {
        parent[rootU] = rootV;
    } else {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

// Kruskal's MST Algorithm with OpenMP Sorting
void parallel_kruskal(Edge *edgeList, int vertices, int edges, int threads) {
    // Sort edges by weight using parallelized qsort
    qsort(edgeList, edges, sizeof(Edge), compare_edges);

    int *parent = (int *)malloc(vertices * sizeof(int));
    int *rank = (int *)calloc(vertices, sizeof(int));
    if (parent == NULL || rank == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }

    int mst_weight = 0, mst_edges = 0;
    printf("Edges in MST:\n");

    for (int i = 0; i < edges && mst_edges < vertices - 1; i++) {
        int u = edgeList[i].src;
        int v = edgeList[i].dest;

        int rootU = find_parent(parent, u);
        int rootV = find_parent(parent, v);

        if (rootU != rootV) {
            printf("%d -- %d == %d\n", u, v, edgeList[i].weight);
            mst_weight += edgeList[i].weight;
            union_vertices(parent, rank, rootU, rootV);
            mst_edges++;
        }
    }

    printf("Total weight of MST: %d\n", mst_weight);

    free(parent);
    free(rank);
}

int main() {
    int vertices, edges, threads;
    char filename[100];

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter the number of threads: ");
    scanf("%d", &threads);

    printf("Enter the output filename: ");
    scanf("%s", filename);

    double start_time, end_time;

    // Graph generation
    start_time = omp_get_wtime();
    generate_graph(vertices, edges, filename, threads);
    end_time = omp_get_wtime();
    printf("Graph generation time: %.6f seconds\n", end_time - start_time);

    // Read graph
    Edge *edgeList = read_graph(filename, &vertices, &edges);

    // MST computation
    start_time = omp_get_wtime();
    parallel_kruskal(edgeList, vertices, edges, threads);
    end_time = omp_get_wtime();
    printf("MST computation time: %.6f seconds\n", end_time - start_time);

    free(edgeList);
    return 0;
}
