#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <limits>

using namespace std;

struct Guardian {
    string name;
    int powerLevel;
    string master;
    string city;
    vector<string> apprentices;
};
struct Node {
    Guardian guardian;
    Node* left;
    Node* right;

    Node(const Guardian& guard) : guardian(guard), left(nullptr), right(nullptr) {}
};
struct GuardianTreeNode {
    Guardian guardian;
    vector<GuardianTreeNode*> apprentices;
    GuardianTreeNode* master;

    GuardianTreeNode(const Guardian& guard) : guardian(guard), master(nullptr) {}
};
void bstInsert(Node*& root, const Guardian& guardian) {
    if (root == nullptr) {
        root = new Node(guardian);
        return;
    }

    if (guardian.powerLevel < root->guardian.powerLevel) {
        bstInsert(root->left, guardian);
    } else if (guardian.powerLevel > root->guardian.powerLevel) {
        bstInsert(root->right, guardian);
    }
}

void printDescendingPower(Node* root) {
    if (root == nullptr) return;

    printDescendingPower(root->right);
    
    // Agregar condición para imprimir solo guardianes con poder entre 90 y 99
    if (root->guardian.powerLevel >= 90 && root->guardian.powerLevel <= 99) {
        cout << "Nombre: " << root->guardian.name << ", Nivel de Poder: " << root->guardian.powerLevel << endl;
    }
    
    printDescendingPower(root->left);
}
class UndirectedGraph {
private:
    unordered_map<string, int> cityIndexMap;
    vector<vector<int>> adjacencyMatrix;
    vector<string> cities;
    unordered_map<string, GuardianTreeNode*> cityGuardianTrees; // Nuevo mapa para árboles de guardianes
    unordered_map<string, GuardianTreeNode*> cityMasterTrees;

public:
    UndirectedGraph() = default;

    void addEdge(const string& src, const string& dest, int weight) {
        int srcIndex = getIndex(src);
        int destIndex = getIndex(dest);

        adjacencyMatrix[srcIndex][destIndex] = weight;
        adjacencyMatrix[destIndex][srcIndex] = weight; // Agregar la conexión inversa

        cout << "Conexion agregada: " << src << " <-> " << dest << " con peso: " << weight << endl;
    }
    

    size_t getNumberOfCities() const {
        return cities.size();
    }

    // Obtener el nombre de una ciudad por su índice
    string getCityName(size_t index) const {
        if (index < cities.size()) {
            return cities[index];
        }
        return "";
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
        for (size_t i = 0; i < cities.size(); ++i) 
        {
            cout << cities[i] << ", Sus conexiones: ";
            bool hasConnection = false;
            for (size_t j = 0; j < cities.size(); ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    if (hasConnection) {
                        cout << ", "; // Agregar coma entre conexiones
                    }
                    cout << cities[j] << " (peso: " << adjacencyMatrix[i][j] << ")";
                    hasConnection = true;
                }
            }
            if (!hasConnection) {
                cout << "Ninguna conexion";
            }
            cout << endl;
        }
    }

    void printCityConnections(const string& city) {
        int cityIndex = getIndex(city);

        cout << city << " conectada a: ";
        bool hasConnection = false;
        for (size_t i = 0; i < cities.size(); ++i) {
            if (adjacencyMatrix[cityIndex][i] != 0) {
                cout << cities[i] << " (peso: " << adjacencyMatrix[cityIndex][i] << ") ";
                hasConnection = true;
            }
        }
        if (!hasConnection) {
            cout << "Ninguna conexion";
        }
        cout << endl;
    }
    void addGuardianToCity(const string& city, const Guardian& guardian) {
        if (cityGuardianTrees.find(city) == cityGuardianTrees.end()) {
            cityGuardianTrees[city] = new GuardianTreeNode(guardian);
        } else {
            addApprentice(cityGuardianTrees[city], new GuardianTreeNode(guardian));
        }
    }

    void printGuardiansInCity(const string& city, const vector<Guardian>& guardians) {
        cout << "Guardianes en la ciudad de " << city << ":" << endl;

        if (cityGuardianTrees.find(city) != cityGuardianTrees.end()) {
            GuardianTreeNode* cityGuardianTree = cityGuardianTrees[city];

            // Imprimir el maestro y sus aprendices en la ciudad
            cout << "Guardian: " << cityGuardianTree->guardian.name << endl;
            for (const auto& apprentice : cityGuardianTree->apprentices) {
                cout << "- " << apprentice->guardian.name << endl;
            }

            // Imprimir los maestros de los aprendices en la misma ciudad
            for (const auto& apprentice : cityGuardianTree->apprentices) {
                for (const auto& guardian : guardians) {
                    if (guardian.name == apprentice->guardian.master && guardian.city == city) {
                        cout << "Maestro de " << apprentice->guardian.name << ": " << guardian.name << endl;
                        break;
                    }
                }
            }
        } else {
            cout << "No hay guardianes en esta ciudad." << endl;
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
  
     // Función para obtener el árbol general de guardianes de una ciudad específica
    GuardianTreeNode* getMasterTreeOfCity(const string& city) {
        if (cityMasterTrees.find(city) != cityMasterTrees.end()) {
            return cityMasterTrees[city];
        }
        return nullptr;
    }
    bool isConnected(const string& cityA, const string& cityB) {
        int indexA = getIndex(cityA);
        int indexB = getIndex(cityB);

        if (adjacencyMatrix[indexA][indexB] != 0 || adjacencyMatrix[indexB][indexA] != 0) {
            cout << cityA << " y " << cityB << " están conectadas directamente." << endl;
            return true;
        } else {
            cout << cityA << " y " << cityB << " no están conectadas directamente." << endl;
            return false;
        }
    }
    
    
    private:
        // Función para insertar un aprendiz bajo un maestro en el árbol general
        void addApprentice(GuardianTreeNode* master, GuardianTreeNode* apprentice) {
            apprentice->master = master;
            master->apprentices.push_back(apprentice);
        }
};

int main() {
    //<-------------------------------- Carga de Archivos de ciudades ------------------------>
    ifstream cityFile("Ciudades.txt");
    if (!cityFile.is_open()) {
        cout << "No se pudo abrir el archivo de ciudades." << endl;
        return 1;
    } else {
        cout << "Archivo de ciudades abierto correctamente." << endl;
    }

    UndirectedGraph graph;

    string cityLine;
    getline(cityFile, cityLine); // Ignorar la primera línea

    while (getline(cityFile, cityLine)) 
    {
        istringstream iss(cityLine);
        string city, connection;
        if (getline(iss, city, ',') && getline(iss, connection)) {
                int weight = 1; // Peso por defecto
                graph.addEdge(city, connection, weight); // Agregar la conexión al grafo
            }
    }

    cityFile.close();
        //Podemos hacer un menu que ingrese que desea buscar con sus conexiones
    /*graph.printDetailedGraph(); 
    graph.printCityConnections("Capital City"); // Imprimir lista detallada de ciudades y conexiones*/
//<-------------------------Carga de archivo Guardianes.txt------------------------------>
    ifstream guardianFile("Guardianes.txt");
    if (!guardianFile.is_open()) {
        cout << "No se pudo abrir el archivo de guardianes." << endl;
        return 1;
    } else {
        cout << "Archivo de guardianes abierto correctamente." << endl;
    }

    vector<Guardian> guardians; // Vector para almacenar los guardianes

    string guardianLine;
     Node* powerTree = nullptr;
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

            guardians.push_back(guardian);
            bstInsert(powerTree, guardian);

                    // Verificar si el guardián tiene una ciudad asignada y corregirlo si es necesario
            if (city.empty()) {
                // Asignar la ciudad al guardián
                guardian.city = "DefaultCity"; // Asignar a una ciudad por defecto o permitir al usuario elegir
            }
            graph.addGuardianToCity(guardian.city, guardian);
        }
    }

    guardianFile.close();
//<------------------------- Fin Carga de archivo Guardianes.txt------------------------------>
     bool exitGame = false;
     //Variables
     int availableGuardiansCount = 0; 
     

    while (!exitGame) {
        cout << "------------Bienvenido al Juego de Guardianes-----------------" << endl;
        cout << "Menu:" << endl;
        cout << "1. Ver la lista de candidatos" << endl;
        cout << "2. Ver al guardian" << endl;
        cout << "3. Conocer el reino" << endl;
        cout << "4. Presenciar una Batalla" << endl;
        cout << "5. Salir" << endl;

        int choice;
        cout << "Ingresa tu eleccion: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Ver la lista de candidatos (Guardianes)
                cout<<"----------------------------------"<<endl;
                cout << "Guardianes ordenados por nivel de poder (de mayor a menor):" << endl;
                printDescendingPower(powerTree);
                cout<<"----------------------------------"<<endl;
                break;
            case 2:
                cout << "Guardianes:" << endl;
                for (const auto& guardian : guardians) {
                    cout << "Nombre: " << guardian.name << endl;
                    cout << "Nivel de Poder: " << guardian.powerLevel << endl;
                    cout << "Maestro: " << guardian.master << endl;
                    cout << "Ciudad: " << guardian.city << endl;
                    cout << endl;
                }
                break;
            case 3:
            // Conocer el reino
            cout << "1. Ver la lista de ciudades y sus conexiones" << endl;
            cout << "2. Conocer las conexiones de una ciudad especifica" << endl;

            int kingdomChoice;
            cout << "Ingresa tu eleccion: ";
            cin >> kingdomChoice;

            if (kingdomChoice == 1) {
                graph.printDetailedGraph();
            } else if (kingdomChoice == 2) {
                // Mostrar un menú de ciudades disponibles
                cout << "Ciudades disponibles:" << endl;
                for (size_t i = 0; i < graph.getNumberOfCities(); ++i) {
                    cout << i + 1 << ". " << graph.getCityName(i) << endl;
                }

                int cityNumber;
                cout << "Ingresa el numero de la ciudad para conocer sus conexiones: ";
                cin >> cityNumber;

                if (cityNumber >= 1 && cityNumber <= graph.getNumberOfCities()) {
                    string cityToCheck = graph.getCityName(cityNumber - 1);
                    graph.printCityConnections(cityToCheck);
                } else {
                    cout << "Numero de ciudad invalido." << endl;
                }
                
            } else if (kingdomChoice == 3) {
                string cityA, cityB;
                cout << "Ingresa el nombre de la primera ciudad: ";
                cin >> cityA;
                cout << "Ingresa el nombre de la segunda ciudad: ";
                cin >> cityB;

                graph.isConnected(cityA, cityB); 
           } else {
                cout << "Opcion invalida." << endl;
            }
            break;
          case 4:
                cout << "Presenciar una Batalla" << endl;

                // Filtrar y mostrar solo los guardianes disponibles para la batalla
                cout << "Guardianes disponibles para la batalla:" << endl;
                availableGuardiansCount = 0;

                for (const auto& guardian : guardians) {
                    // Verificar que el guardián no sea maestro y su poder no esté entre 90 y 99
                    bool isMaster = false;
                    bool isInRange = guardian.powerLevel >= 90 && guardian.powerLevel <= 99;
                    
                    for (const auto& otherGuardian : guardians) {
                        if (otherGuardian.master == guardian.name) {
                            isMaster = true;
                            break;
                        }
                    }
                    
                    if (!isMaster && !isInRange) {
                        cout << availableGuardiansCount + 1 << ". " << guardian.name << endl;
                        availableGuardiansCount++;
                    }
                }

                if (availableGuardiansCount == 0) {
                    cout << "No hay guardianes disponibles para la batalla." << endl;
                } else {
                    int chosenGuardianIndex;
                    cout << "Elige el numero del guardian para la batalla: ";
                    cin >> chosenGuardianIndex;

                    if (chosenGuardianIndex >= 1 && chosenGuardianIndex <= availableGuardiansCount) {
                        int currentGuardianIndex = 0;
                        for (const auto& guardian : guardians) {
                            // Verificar nuevamente que el guardián elegido cumpla las condiciones
                            bool isMaster = false;
                            bool isInRange = guardian.powerLevel >= 90 && guardian.powerLevel <= 99;
                            
                            for (const auto& otherGuardian : guardians) {
                                if (otherGuardian.master == guardian.name) {
                                    isMaster = true;
                                    break;
                                }
                            }
                            
                            if (!isMaster && !isInRange) {
                                currentGuardianIndex++;
                                
                                if (currentGuardianIndex == chosenGuardianIndex) {
                                    Guardian chosenGuardian = guardian;
                                    cout << "Has elegido al guardian: " << chosenGuardian.name << endl; 
                                    // Mostrar las características del guardian elegido
                                    bool exitBattleMenu = false;

                                    while (!exitBattleMenu) {
                                        cout << "<------------------------------------------------------->"<<endl;
                                        cout << "Detalles del guardian elegido:" << endl;
                                        cout << "Nombre: " << chosenGuardian.name << endl;
                                        cout << "Nivel de Poder: " << chosenGuardian.powerLevel << endl;
                                        cout << "Maestro: " << chosenGuardian.master << endl;
                                        cout << "Ciudad: " << chosenGuardian.city << endl;
                                        cout << "<------------------------------------------------------->"<<endl;
                                        // Mostrar el menú de opciones
                                        cout << "Opciones:" << endl;
                                        cout << "1.- Viajar a otra ciudad" << endl;
                                        cout << "2.- Mostrar los aprendices y maestros de la ciudad" << endl;
                                        cout << "3.- Batalla" << endl;
                                        cout << "4.- Salir" << endl;

                                        int battleChoice;
                                        cout << "Ingresa tu eleccion: ";
                                        cin >> battleChoice;
                                        
                                        vector<string> connectedCities;

                                        switch (battleChoice) {
                                            case 1:
                                                            // Lógica para viajar a otra ciudad
                                                cout << "Te encuentras en la ciudad de " << chosenGuardian.city << ", que es la ciudad del guardian." << endl;
            
                                                // Obtener las conexiones de la ciudad actual
                                                connectedCities = graph.getConnectedCities(chosenGuardian.city);
                                                cout << "Conexiones disponibles desde " << chosenGuardian.city << ":" << endl;
                                                for (size_t i = 0; i < connectedCities.size(); ++i) {
                                                    cout << i + 1 << ". " << connectedCities[i] << endl;
                                                }

                                                int cityToTravel;
                                                cout << "Elige el numero de la ciudad a la que quieres viajar: ";
                                                cin >> cityToTravel;

                                                if (cityToTravel >= 1 && cityToTravel <= connectedCities.size()) {
                                                    string newCity = connectedCities[cityToTravel - 1];
                                                    cout << "Viajando a la ciudad de " << newCity << "..." << endl;
                                                    chosenGuardian.city = newCity; // Cambiar la ciudad del guardian

                                                    for (auto& guardian : guardians) {
                                                    if (guardian.name == chosenGuardian.name) {
                                                        guardian.city = chosenGuardian.city; // Actualizar la ciudad del guardián
                                                        break;
                                                    }
                                                }
                                                cout << "Ahora te encuentras en la ciudad de " << newCity << "." << endl;
                                                choice = 0; 
                                                } else {
                                                    cout << "Número de ciudad invalido." << endl;
                                                }
                                                break;
                                          case 2:
                                                graph.printGuardiansInCity(chosenGuardian.city, guardians);
                                                break;
                                            case 3:
                                                // Lógica para la batalla
                                                break;
                                            case 4:
                                            exitBattleMenu = true;
                                            break; // Salir del bucle del menú de batalla
                                            default:
                                                cout << "Opcion no valida." << endl;
                                                break;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        cout << "Número de guardián no válido." << endl;
                    }
                }
                break;
             //<-------------------------------------------------------Aqui estamos trabajando -------------------------------------------->
            case 5:
                exitGame = true;
                break;
            default:
                cout << "Opcion invalida. Por favor, elige una opcion del menu." << endl;
                break;
        }
    }

    cout << "Gracias por jugar. Hasta luego." << endl;

    return 0;
}
