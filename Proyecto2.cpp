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
        cout << "Cities and their connections:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            cout << cityMap[i] << " connects to: ";
            for (const auto& neighbor : adjList[i]) {
                cout << cityMap[neighbor] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    ifstream file("Ciudades.txt");
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    unordered_map<string, int> cityIndexMap;
    int index = 0;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
            if (cityIndexMap.find(city) == cityIndexMap.end()) {
                cityIndexMap[city] = index++;
            }
            if (cityIndexMap.find(connection) == cityIndexMap.end()) {
                cityIndexMap[connection] = index++;
            }
        }
    }

    file.clear();
    file.seekg(0);

    DirectedGraph graph(index);

    while (getline(file, line)) {
        istringstream iss(line);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
            int cityIndex = cityIndexMap[city];
            int connectionIndex = cityIndexMap[connection];

            graph.addEdge(cityIndex, connectionIndex);
            graph.addCity(cityIndex, city);
            graph.addCity(connectionIndex, connection);
        }
    }

    file.close();

    graph.printGraph();

    return 0;
}
