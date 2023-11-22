#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

class DirectedGraph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;
    map<string, int> cityIndex;

public:
    DirectedGraph() : numVertices(0) {}

    void addVertex(const string& city) {
        if (cityIndex.find(city) == cityIndex.end()) {
            cityIndex[city] = numVertices++;
            adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
        }
    }

    void addEdge(const string& src, const string& dest) {
        int srcIndex = cityIndex[src];
        int destIndex = cityIndex[dest];
        adjMatrix[srcIndex][destIndex] = 1;
        adjMatrix[destIndex][srcIndex] = 1;
    }

    void printGraph() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<string> getNeighbors(const string& city) {
        vector<string> neighbors;
        int cityIndex = cityIndex[city];

        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[cityIndex][i] == 1) {
                for (auto const& pair : cityIndex) {
                    if (pair.second == i) {
                        neighbors.push_back(pair.first);
                        break;
                    }
                }
            }
        }

        return neighbors;
    }
};

int main() {
    DirectedGraph graph;

    ifstream file("Ciudades.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream ss(line);
            string city, connection;
            getline(ss, city, ',');
            graph.addVertex(city);
            while (getline(ss, connection, ',')) {
                graph.addVertex(connection);
                graph.addEdge(city, connection);
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file!" << endl;
        return 1;
    }

    graph.printGraph();

    string startingCity = "CiudadInicial"; // Cambia por tu ciudad inicial
    vector<string> neighbors = graph.getNeighbors(startingCity);

    cout << "Las ciudades vecinas a " << startingCity << " son:" << endl;
    for (const auto& neighbor : neighbors) {
        cout << neighbor << endl;
    }

    return 0;
}
