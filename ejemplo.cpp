#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Guardian {
    string name;
    int powerLevel;
    string master;
    string city;
};

class UndirectedGraph {
private:
    unordered_map<string, vector<string>> adjacencyList;
    unordered_map<string, Guardian> guardians;

public:
    void addEdge(const string& src, const string& dest) {
        adjacencyList[src].push_back(dest);
        adjacencyList[dest].push_back(src);
    }

    void addGuardian(const Guardian& guardian) {
        guardians[guardian.name] = guardian;
        adjacencyList[guardian.city].push_back(guardian.name);
    }

    void printCityConnections(const string& city) {
        cout << "Conexiones de la ciudad " << city << ":" << endl;
        for (const auto& connectedCity : adjacencyList[city]) {
            cout << "- " << connectedCity << endl;
        }
    }

    void printGuardianDetails(const string& guardianName) {
        Guardian guardian = guardians[guardianName];
        cout<<"------------------------------------------------"<< endl;
        cout << "Detalles del guardian " << guardian.name << ":" << endl;
        cout << "Nombre: " << guardian.name << endl;
        cout << "Nivel de Poder: " << guardian.powerLevel << endl;
        cout << "Maestro: " << guardian.master << endl;
        cout << "Ciudad: " << guardian.city << endl;
        cout<<"------------------------------------------------"<< endl;

        cout << "Aprendices y Maestros en la ciudad de " << guardian.city << ":" << endl;
        for (const auto& g : guardians) {
            if (g.second.city == guardian.city && (g.second.master == guardian.name || guardian.master == g.second.name)) {
                cout << "- " << g.second.name << " (" << (g.second.master == guardian.name ? "Aprendiz" : "Maestro") << ")" << endl;
            }
        }
    }

    Guardian getGuardian(const string& guardianName) {
        return guardians[guardianName];
    }

    void printCityDetails(const string& city) {
        cout << "Detalles de la ciudad " << city << ":" << endl;
        printCityConnections(city);
        cout << "Guardianes en la ciudad " << city << ":" << endl;
        for (const auto& guardian : adjacencyList[city]) {
            printGuardianDetails(guardian);
        }
    }

    void printAllGuardians() {
        cout << "Guardianes Disponibles:" << endl;
        int count = 1;
        for (const auto& guardian : guardians) {
            cout << count << ". " << guardian.second.name << endl;
            count++;
        }
    }
};
int main() {
    ifstream cityFile("Ciudades.txt");
    if (!cityFile.is_open()) {
        cout << "No se pudo abrir el archivo de ciudades." << endl;
        return 1;
    }

    UndirectedGraph graph;

    string cityLine;
    getline(cityFile, cityLine); // Ignorar la primera línea

    while (getline(cityFile, cityLine)) {
        istringstream iss(cityLine);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
            graph.addEdge(city, connection);
        }
    }

    cityFile.close();

    ifstream guardianFile("Guardianes.txt");
    if (!guardianFile.is_open()) {
        cout << "No se pudo abrir el archivo de guardianes." << endl;
        return 1;
    }

    string guardianLine;
    getline(guardianFile, guardianLine); // Ignorar la primera línea

    while (getline(guardianFile, guardianLine)) {
        istringstream iss(guardianLine);
        string name, powerLevelStr, master, city;
        if (getline(iss, name, ',') && getline(iss, powerLevelStr, ',') &&
            getline(iss, master, ',') && getline(iss, city, ',')) {
            int powerLevel = stoi(powerLevelStr);

            Guardian guardian;
            guardian.name = name;
            guardian.powerLevel = powerLevel;
            guardian.master = master;
            guardian.city = city;

            graph.addGuardian(guardian);
        }
    }

    guardianFile.close();

    cout << "Ciudades y sus conexiones:" << endl;
    // Aquí puedes agregar la lógica para imprimir todas las ciudades y sus conexiones

    string chosenGuardian;
    cout << "Ingrese el nombre del guardián para ver detalles: ";
    cin >> chosenGuardian;

    graph.printGuardianDetails(chosenGuardian);

    Guardian guardian = graph.getGuardian(chosenGuardian);
    
    cout << "Detalles de la ciudad del guardián:" << endl;
    graph.printCityDetails(guardian.city);

    return 0;
}
