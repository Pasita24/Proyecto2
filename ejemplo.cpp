#include <iostream>
#include <vector>

using namespace std;

class DirectedGraph {
private :

    int numVertices;
    vector<vector<int>>adjList;

}
public:
    DirectedGraph(int vertices) : numVertices(vertices)
    {
        adjList.resize(numVertices);
    }
    void addEdge(int src,int dest)
    {
        if(src >= 0 && src < numVertices && dest >= 0 && dest < numVerices)
        {
            adjList[src].push_back(dest);
        }
    }

    void printGraph(){
        cout << "Adjacency List:"<<endl;
        for(int =0; i< numVertices;++i)
        {
            cout<<"Vertex "<<i<< ": ";
            for(const auto& neighbor :adjList[i])
            {
                cout <<neighbor <<"";
            }
            cout<<endl;
        }
    }