#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class DirectedGraph {
private:
    int numVertices;
    vector<vector<int>> adjList;
    unordered_map<int, string> cityMap;

public:
    DirectedGraph(int vertices) : numVertices(vertices) {
        adjList.resize(numVertices);
    }

    void addEdge(int src, int dest) {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) {
            adjList[src].push_back(dest);
        }
    }

    void addCity(int index, const string& cityName) {
        cityMap[index] = cityName;
    }

    void printGraph() {
        cout << "Ciudades y conexiones:" << endl << endl;
        for (int i = 0; i < numVertices; ++i) {
            if (!adjList[i].empty()) {
                cout << cityMap[i] << " conectado a: ";
                for (const auto& neighbor : adjList[i]) {
                    cout << cityMap[neighbor] << " ";
                }
                cout << endl;
            }
        }
    }

    int getNumVertices() const {
        return numVertices;
    }

    void incrementNumVertices() {
        ++numVertices;
    }

    bool hasConnection(const string& cityA, const string& cityB) {
        int indexA = -1, indexB = -1;

        for (const auto& pair : cityMap) {
            if (pair.second == cityA) {
                indexA = pair.first;
            } else if (pair.second == cityB) {
                indexB = pair.first;
            }
        }

        if (indexA == -1 || indexB == -1) {
            return false; // Si alguna de las ciudades no existe en el grafo
        }

        for (const auto& neighbor : adjList[indexA]) {
            if (neighbor == indexB) {
                return true; // Si hay conexión entre las ciudades
            }
        }

        return false; // Si no hay conexión entre las ciudades
    }
};

int main() {
    ifstream file("Ciudades.txt");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string line;
    getline(file, line); // Ignora la primera línea

    unordered_map<string, int> cityIndexMap;
    DirectedGraph graph(0); // Grafo inicializado sin vértices

    while (getline(file, line)) {
        istringstream iss(line);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
            if (cityIndexMap.find(city) == cityIndexMap.end()) {
                cityIndexMap[city] = graph.getNumVertices(); // Asigna un índice a la ciudad
                graph.addCity(graph.getNumVertices(), city); // Agrega la ciudad al grafo
                graph.incrementNumVertices(); // Incrementa el contador de vértices
            }
            if (cityIndexMap.find(connection) == cityIndexMap.end()) {
                cityIndexMap[connection] = graph.getNumVertices(); // Asigna un índice a la ciudad
                graph.addCity(graph.getNumVertices(), connection); // Agrega la ciudad al grafo
                graph.incrementNumVertices(); // Incrementa el contador de vértices
            }

            int cityIndex = cityIndexMap[city];
            int connectionIndex = cityIndexMap[connection];

            graph.addEdge(cityIndex, connectionIndex); // Agrega la conexión al grafo
        }
    }

    file.close();

    graph.printGraph();

    // Verificar conexión entre dos ciudades
    string cityA = "Silverstone City";
    string cityB = "Valley City";

    if (graph.hasConnection(cityA, cityB)) {
        cout << "\nHay conexión entre " << cityA << " y " << cityB << endl;
    } else {
        cout << "\nNo hay conexión entre " << cityA << " y " << cityB << endl;
    }

    return 0;
}
