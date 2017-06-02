#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <map>
#include <assert.h>
using namespace std;


class graph{
private:
    int num_of_Nodes;
    //      ((src, dest),cost)
    vector<int> nodePath;   //used to store the path

public:
    map <pair<int, int>, int> edgePairs;
    graph(int number_of_nodes){
        //initialize the graph with the number of nodes in the graph
        num_of_Nodes = number_of_nodes;
    }
    void addEdge(int src, int dest, int cost){
        //stores the two vertices and their cost
        //will used to reference later to connect the nodes
        edgePairs.insert(make_pair(make_pair(src, dest), cost));

    }
    void printPath() {
        cout << "length of nodepath is: " << nodePath.size() << endl;
        cout << "path: ";
        for(int i = 0; i < nodePath.size(); i++){
            cout << nodePath[i];
            if(i < nodePath.size() - 1){
                cout << ", ";
            }
        }
        cout << endl;
    }
    void shortestPath(int src, int dest, map <pair<int, int>, int> edges){ //defaults as edgePairs
        cout << "source is " << src << " destination is " << dest << endl;
        //used to store the paths from source to destination
        //create a temp copy of nodePairs
        map <pair<int, int>, int> temp = edges;
        //   connected pairs of nodes and their cost
        //we'll first look at the node and compare the costs of each  each edge in the nodePairs
        //after finding the node with the lowest cost, we'll append the node to the nodePath vector
        //then finally when finished, we'll print(cout) the nodePath
        int current;
        int currentCost = 0;
        int lowestCost = 1000;
        //used keeps track of visted edges
        //vector<pair<int, int>> visited;
        //edgePair type
        for (auto iter = temp.begin(); iter != temp.end(); iter++) {

            //store vertice(v1) and vertice(v2)
            auto v1 = iter->first.first; //vertex 1
            auto v2 = iter->first.second;//vertex 2
            auto cost = iter->second;    //cost
            current = v1;
            currentCost = cost;
            if (current == dest){
                cout << current;
                cout << " destination reached \n";
                nodePath.push_back(dest);
                break;
            }
            //we can iterate through the number of nodes as v2 to find the lowest cost
            if ((current == src) && (dest != v2) && (src != dest)) {
                cout << "second loop";
                //if we are at the starting node and the next node isnt the end
                nodePath.push_back(current);
                //add node to the path
                //now loop through all possible connections
                for (int i = 0; i < num_of_Nodes; i++) {
                    cout << " i = " << i << endl;
                    for (auto it = temp.begin(); it != temp.end(); it++) {
                        //iterate through all possible connections, whether they exist or not using i++
                        //use current as the v1 to find the possible v2 with i
                            auto connection = temp.find(make_pair(current, i));
                            if ((connection->second <= currentCost)) {
                                //self call with the new source
                                //cout << connection->first.first << ", " << connection->first.second << " cost: "
                                //<< connection->second << endl;
                                //start at the new source based on lost cost
                                int nextNode = connection->first.second;
                                cout << "pushing back connection first second: " << nextNode << endl;
                                nodePath.push_back(nextNode);
                                shortestPath(nextNode, dest, temp);
                            }
                        }
                    }
                }
            }
        }

    //////////////
    void print_edgePairs(){
        cout << "{";
        for(auto iter = edgePairs.begin(); iter != edgePairs.end(); iter++){
            auto connected = iter -> first;
            auto cost = iter -> second;
            cout << "((" << connected.first << "," << connected.second << ")," << cost << ")";
            if (iter != edgePairs.end()){
                cout << ", ";
            }
        }
        cout << "}" << endl;
    }
};
int main() {
    int n;
    cout <<  "how many nodes are there in your graph? \n";
    cin >> n;
    //sanitizing input (int)
    /*
     * this sanitization is unnecessary in this case, I did it to brush up
     */
    while (cin.fail()){
        cin.clear();
        cin.ignore();
        cerr << "invalid input! try again: \n" << endl;
        cin >> n;
    }
    //create graph object
    graph g(n);
    //start adding edges to the graph
    //      src,dest,cost
    //https://github.com/DzouOnionGardener/dijkstra-s-Algorithm/blob/master/DSC_0001.JPG?raw=true
    /*
    g.addEdge(1,  2,  3);
    g.addEdge(1,  3,  5);
    g.addEdge(1,  4,  4);
    g.addEdge(2,  5,  3);
    g.addEdge(2,  6,  6);
    g.addEdge(3,  4,  2);
    g.addEdge(3,  7,  4);
    g.addEdge(4,  8,  5);
    g.addEdge(4,  5,  1);
    g.addEdge(5,  6,  2);
    g.addEdge(5,  9,  4);
    g.addEdge(6,  10, 5);
    g.addEdge(7,  11, 6);
    g.addEdge(7,  8,  3);
    g.addEdge(8,  9,  6);
    g.addEdge(8,  11, 7);
    g.addEdge(9,  10, 3);
    g.addEdge(9,  12, 5);
    g.addEdge(10, 12, 9);
    g.addEdge(11, 12, 8);

     */

    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 3);
    g.addEdge(2, 5, 2);
    g.addEdge(4, 5, 2);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 6, 1);
    g.addEdge(5, 6, 1);
    //g.printPairs();           //used for debugging
    //g.print_nodePairs();        //show pairs
    g.print_edgePairs();
    g.shortestPath(1, 5, g.edgePairs);
    g.printPath();

    return 0;
}
