#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int MAX_VALUE = INT_MAX;
const int N = 5;

void dijkstra(vector<vector<int>>& graph, int start, int end) {
    vector<int> distance(N, MAX_VALUE);
    vector<bool> visited(N, false);

    distance[start] = 0;

    for (int i = 0; i < N; ++i) {
        int minDistance = MAX_VALUE;
        int minIndex = -1;

        for (int j = 0; j < N; ++j) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                minIndex = j;
            }
        }

        if (minIndex == -1) break;

        visited[minIndex] = true;

        for (int j = 0; j < N; ++j) {
            if (!visited[j] && graph[minIndex][j] && distance[minIndex] != MAX_VALUE &&
                distance[minIndex] + graph[minIndex][j] < distance[j]) {
                distance[j] = distance[minIndex] + graph[minIndex][j];
            }
        }
    }

    if (distance[end] == MAX_VALUE) {
        cout << "No hay camino desde " << start << " hasta " << end << endl;
    } else {
        cout << "El camino más corto desde " << start << " hasta " << end << " es " << distance[end] << endl;
    }
}

int main() {
    vector<vector<int>> graph = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };

    int start = 0;
    int end = 3;

    dijkstra(graph, start, end);

    return 0;
}
