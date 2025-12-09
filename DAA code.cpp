#include <stdio.h>
#include <limits.h>

#define V 10 // Maximum number of vertices

// ------------------- DIJKSTRA ALGORITHM -------------------
int minDistance(int dist[], int visited[], int vertices) {
    int min = INT_MAX, index = -1;
    for (int i = 0; i < vertices; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void dijkstra(int graph[V][V], int src, int vertices) {
    int dist[V], visited[V];

    for (int i = 0; i < vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < vertices - 1; count++) {
        int u = minDistance(dist, visited, vertices);
        visited[u] = 1;

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph[u][v] != 0 &&
                dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {

                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nDijkstra - Shortest distances from source %d:\n", src);
    for (int i = 0; i < vertices; i++)
        printf("To %d: %d\n", i, dist[i]);
}

// ------------------- BELLMAN-FORD ALGORITHM -------------------
void bellmanFord(int graph[V][V], int src, int vertices) {
    int dist[V];

    for (int i = 0; i < vertices; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;

    for (int k = 0; k < vertices - 1; k++) {
        for (int u = 0; u < vertices; u++) {
            for (int v = 0; v < vertices; v++) {
                if (graph[u][v] != 0 && dist[u] != INT_MAX &&
                    dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    // Check for negative weight cycles
    for (int u = 0; u < vertices; u++) {
        for (int v = 0; v < vertices; v++) {
            if (graph[u][v] != 0 && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                printf("\nGraph contains a negative weight cycle!\n");
                return;
            }
        }
    }

    printf("\nBellman-Ford - Shortest distances from source %d:\n", src);
    for (int i = 0; i < vertices; i++)
        printf("To %d: %d\n", i, dist[i]);
}

// ------------------- MAIN FUNCTION -------------------
int main() {
    int graph[V][V], vertices, src;

    printf("Enter number of vertices (<= %d): ", V);
    scanf("%d", &vertices);

    printf("Enter adjacency matrix (0 means no edge):\n");
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src, vertices);
    bellmanFord(graph, src, vertices);

    return 0;
}
