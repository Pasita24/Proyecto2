#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <queue>

using namespace std;

void buildGraphFromFile(const string& filename, unordered_map<string, unordered_set<string>>& adjacencyList, vector<string>& cities) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    string line;
    // Ignorar la primera línea que contiene los encabezados
    getline(file, line);

    set<string> uniqueCities; // Para almacenar nombres únicos de ciudades y conexiones
    while (getline(file, line)) {
        istringstream iss(line);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
            adjacencyList[city].insert(connection); // Solo insertar la conexión como arista

            uniqueCities.insert(city); // Agregar la ciudad pero no la conexión a la lista única de ciudades
        }
    }

    file.close();

    cities.assign(uniqueCities.begin(), uniqueCities.end()); // Asignar los nombres de las ciudades a la lista
}

void printCityConnections(const unordered_map<string, unordered_set<string>>& adjacencyList) {
    int counter = 1;
    for (const auto& city : adjacencyList) {
        cout << counter << ".- " << city.first;
        for (const auto& connection : city.second) {
            cout << " -> " << connection;
        }
        cout << endl;
        counter++;
    }
}

bool hasConnection(const unordered_map<string, unordered_set<string>>& adjacencyList, const string& vertex, const string& edge) {
    for (const auto& city : adjacencyList) {
        if (city.first == vertex) {
            for (const auto& connection : city.second) {
                if (connection == edge) {
                    return true;
                }
            }
        }
    }
    return false;
}

void printCitiesAndConnections(const unordered_map<string, unordered_set<string>>& adjacencyList) {
    cout << "Lista de Ciudades y Conexiones:" << endl;

    for (const auto& city : adjacencyList) {
        cout << "Ciudad: " << city.first << endl;
        cout << "Conexiones: ";
        for (const auto& connection : city.second) {
            cout << connection << " ";
        }
        cout << "\n\n";
    }
}

int main() {
    string filename = "Ciudades.txt"; // Nombre del archivo con las ciudades y conexiones

    unordered_map<string, unordered_set<string>> cityAdjacencyList;
    vector<string> cities;

    buildGraphFromFile(filename, cityAdjacencyList, cities);

    // Imprimir la lista de ciudades con sus conexiones
    printCitiesAndConnections(cityAdjacencyList);

    // Verificar si hay conexión entre dos ciudades específicas
    string cityA = "Silverstone City";
    string cityB = "Valley City";

    if (hasConnection(cityAdjacencyList, cityA, cityB)) {
        cout << "Hay conexión entre " << cityA << " y " << cityB << endl;
    } else {
        cout << "No hay conexión entre " << cityA << " y " << cityB << endl;
    }

    return 0;
}
