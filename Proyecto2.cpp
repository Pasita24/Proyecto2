#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

class UndirectedGraph {
private:
    unordered_map<string, int> cityIndexMap;
    vector<vector<int>> adjacencyMatrix;
    vector<string> cities;

public:
    UndirectedGraph() = default;

    void addEdge(const string& src, const string& dest, int weight) {
        int srcIndex = getIndex(src);
        int destIndex = getIndex(dest);

        adjacencyMatrix[srcIndex][destIndex] = weight;
        adjacencyMatrix[destIndex][srcIndex] = weight; // Agregar la conexión inversa

        cout << "Conexion agregada: " << src << " <-> " << dest << " con peso: " << weight << endl;
    }

    int getIndex(const string& city) {
        if (cityIndexMap.find(city) == cityIndexMap.end()) {
            int newIndex = cities.size();
            cities.push_back(city);
            cityIndexMap[city] = newIndex;

            // Ajustar la matriz de adyacencia al tamaño correcto
            for (auto& row : adjacencyMatrix) {
                row.resize(cities.size(), 0);
            }
            adjacencyMatrix.resize(cities.size(), vector<int>(cities.size(), 0));

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

    vector<string> getConnectedCities(const string& city) {
        vector<string> connectedCities;
        int cityIndex = getIndex(city);

        cout << "Ciudades conectadas a " << city << ":" << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (adjacencyMatrix[cityIndex][i] != 0) {
                connectedCities.push_back(cities[i]);
                cout << cities[i] << endl;
            }
        }

        return connectedCities;
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

    UndirectedGraph graph;

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

    // Obtener las ciudades conectadas a "Capital City"
    string startCity = "Capital City";
    vector<string> connectedCities = graph.getConnectedCities(startCity);

    // Mostrar las ciudades conectadas en un menú
    cout << "Ciudades a las que puedes viajar desde " << startCity << ":" << endl;
    for (size_t i = 0; i < connectedCities.size(); ++i) {
        cout << i + 1 << ". " << connectedCities[i] << endl;
    }

    return 0;
}
