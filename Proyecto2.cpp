#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

class DirectedGraph {
private:
    unordered_map<string, int> cityIndexMap;
    vector<vector<int>> adjacencyMatrix;
    vector<string> cities;

public:
    DirectedGraph() = default;

    void addEdge(const string& src, const string& dest, int weight) {
        int srcIndex = getIndex(src);
        int destIndex = getIndex(dest);

        adjacencyMatrix[srcIndex][destIndex] = weight;
        cout << "Conexion agregada: " << src << " -> " << dest << " con peso: " << weight << endl;
    }

    int getIndex(const string& city) {
        if (cityIndexMap.find(city) == cityIndexMap.end()) {
            int newIndex = cities.size();
            cities.push_back(city);
            cityIndexMap[city] = newIndex;
            adjacencyMatrix.emplace_back(cities.size(), 0);
            for (auto& row : adjacencyMatrix) {
                row.resize(cities.size(), 0);
            }
            return newIndex;
        }
        return cityIndexMap[city];
    }

    void printDetailedGraph() {
        cout << "Ciudades y sus conexiones:" << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            cout << cities[i] << " conectada a: ";
            bool hasConnection = false;
            for (size_t j = 0; j < cities.size(); ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    cout << cities[j] << " (peso: " << adjacencyMatrix[i][j] << ") ";
                    hasConnection = true;
                }
            }
            if (!hasConnection) {
                cout << "Ninguna conexion";
            }
            cout << endl;
        }
    }

     vector<int> dijkstra(const string& startCity, const string& endCity) {
        const int MAX_VALUE = numeric_limits<int>::max();
        int start = getIndex(startCity);
        int end = getIndex(endCity);

        vector<int> distances(cities.size(), MAX_VALUE);
        vector<bool> discovered(cities.size(), false);
        distances[start] = 0;

        for (int k = 0; k < cities.size(); ++k) {
            int minDistance = MAX_VALUE;
            int minIndex = -1;

            for (int i = 0; i < cities.size(); ++i) {
                if (distances[i] < minDistance && !discovered[i]) {
                    minDistance = distances[i];
                    minIndex = i;
                }
            }

            if (minDistance == MAX_VALUE || minIndex == end) break;
            discovered[minIndex] = true;

            for (int i = 0; i < cities.size(); ++i) {
                if (adjacencyMatrix[minIndex][i] != 0 && distances[i] > distances[minIndex] + adjacencyMatrix[minIndex][i]) {
                    distances[i] = distances[minIndex] + adjacencyMatrix[minIndex][i];
                }
            }
        }

        return distances;
    }
};

int main() {
    ifstream file("Ciudades.txt");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    } else {
        cout << "Archivo abierto correctamente." << endl;
    }

    DirectedGraph graph;

    string line;
    getline(file, line); // Ignorar la primera línea

    while (getline(file, line)) {
        istringstream iss(line);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
            int weight = 1; // Peso por defecto
            graph.addEdge(city, connection, weight); // Agregar la conexión al grafo
        }
    }

    file.close();

    graph.printDetailedGraph(); // Imprimir lista detallada de ciudades y conexiones

    // Realizar otras operaciones con el grafo, como Dijkstra para encontrar el camino más corto
    // graph.dijkstra(startCity, endCity);

    return 0;
}
