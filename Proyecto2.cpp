#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

// Función para construir el grafo a partir del archivo de texto
void buildGraphFromFile(const string& filename, unordered_map<string, vector<string>>& adjacencyList, unordered_map<string, unordered_map<string, int>>& adjacencyMatrix) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string line;
    // Leer la primera línea que contiene los encabezados
    getline(file, line);

    while (getline(file, line)) {
        istringstream iss(line);
        string city, neighbor;
        if (getline(iss, city, ',') && getline(iss, neighbor)) {
            adjacencyList[city].push_back(neighbor);
            adjacencyList[neighbor].push_back(city); // Bidireccional

            // Construir la matriz de adyacencia
            adjacencyMatrix[city][neighbor] = 1;
            adjacencyMatrix[neighbor][city] = 1;
        }
    }

    file.close();
}
// Función para imprimir la matriz de adyacencia
void printAdjacencyMatrix(const unordered_map<string, unordered_map<string, int>>& adjacencyMatrix, const vector<string>& cities) {
    cout << "Matriz de adyacencia del grafo:" << endl;

    // Imprimir la primera fila (nombres de las ciudades)
    cout << "    ";
    for (const auto& city : cities) {
        cout << city << " ";
    }
    cout << endl;

    for (const auto& city1 : cities) {
        cout << city1 << " | "; // Imprimir el nombre de la ciudad al principio de la fila
        for (const auto& city2 : cities) {
            // Comprobar si hay conexión y mostrar 1 o 0
            int connection = adjacencyMatrix.at(city1).count(city2) > 0 ? 1 : 0;
            cout << connection << " ";
        }
        cout << endl;
    }
}

int main() {
    string filename = "Ciudades.txt"; // Nombre del archivo con las ciudades y conexiones

    unordered_map<string, vector<string>> cityAdjacencyList;
    unordered_map<string, unordered_map<string, int>> cityAdjacencyMatrix;

    buildGraphFromFile(filename, cityAdjacencyList, cityAdjacencyMatrix);

    // Obtener la lista de ciudades
    vector<string> cities;
    for (const auto& city : cityAdjacencyList) {
        cities.push_back(city.first);
    }

    // Imprimir la matriz de adyacencia
    printAdjacencyMatrix(cityAdjacencyMatrix, cities);

    return 0;
}

