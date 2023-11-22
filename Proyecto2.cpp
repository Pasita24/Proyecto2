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

    bool hasConnection(const string& startCity, const string& endCity) {
        int startIndex = getIndex(startCity);
        int endIndex = getIndex(endCity);

        return adjacencyMatrix[startIndex][endIndex] != 0;
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

    // graph.printDetailedGraph(); // Imprimir lista detallada de ciudades y conexiones

    // Verificar si hay conexión entre dos ciudades
    string startCity = "Silverstone City";
    string endCity = "Valley City";
    if (graph.hasConnection(startCity, endCity)) {
        cout << "Hay conexion entre " << startCity << " y " << endCity << endl;
    } else {
        cout << "No hay conexion entre " << startCity << " y " << endCity << endl;
    }

    return 0;
}
