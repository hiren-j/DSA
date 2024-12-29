// Program to find the breadth-first-search traversal of an undirected and disconnected graph ~ coded by Hiren
#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

// Solution class:
class Solution {
    vector<vector<int>> bfsOrder; // Buffer to store the bfs order of all the components (result arrays) 
    vector<vector<int>> adjList;  // Stores the list of neighbours of each vertex 
    vector<int> visited;          // Tracks the vertices which are visited
    
    // Method to perform the bfs traversal from the source vertex of the component - O(V+E) & O(V)
    void BFS(int vertex) {
        // Mark the source vertex as visited
        visited[vertex]++;

        // Requires to visit the neighbours of each vertex in the correct order
        queue<int> q;
        q.push(vertex);

        // Buffer to Store the bfs order of the current component
        vector<int> component;
    
        while(!q.empty()) {
            // Extract the front vertex of the queue
            vertex = q.front(); q.pop();
            // Store the vertex to the component buffer
            component.push_back(vertex);
            // Iterate each neighbour of the vertex
            for(auto neighbor : adjList[vertex]) {
                // If the current neighbour is not visited then mark it as visited and then store it to the queue
                if(!visited[neighbor]) {
                    visited[neighbor]++;
                    q.push(neighbor);
                }
            }
        }
        
        // Store the bfs order of the component to the result buffer
        bfsOrder.push_back(component);
    }

public:
    // Method to find the bfs traversal of an undirected graph having disconnected components - O(V+E) & O(V+E) : Where V let be the total number of vertices and E let be the total number of edges
    vector<vector<int>> breadthFirstSearch(int n, vector<vector<int>>& edges) {
        visited.resize(n);
        adjList.resize(n);
        
        // Iterate and create the adjacency list
        for(auto edge : edges) {
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }

        // Iterate and perform the bfs traversal on each component from their source vertex
        for(int vertex = 0; vertex < n; ++vertex) {
            // If the vertex is not visited then perform the bfs traversal on the component
            if(!visited[vertex]) {
                BFS(vertex);
            }
        }

        // Return the result buffer containing the bfs order of all the components
        return bfsOrder;
    }
};

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the size of the graph
        int V;
        cout<<"Enter the total number of vertices: ";
        cin>>V;

        // Input the size of edges
        int E;
        cout<<"Enter the total number of edges: ";
        cin>>E;

        // Check the given values are lying within the problem constraints or not
        if(V < 2 || V > 1e3) {
            std::cout<<"You must enter the size of vertices, which lies between 2 and 10^3!";
        }
        else if(E < 1 || E > 5e3) {
            std::cout<<"You must enter the size of edges, which lies between 1 and 50^3!";
        }
        else {
            // Stores the edges
            vector<vector<int>> edges(E);

            // Requires to avoid the duplication of edges
            set<vector<int>> uniqEdges;

            // Input the edges
            cout<<"\nNote: An edge consist of two vertex [u, v]. It denotes a bi-directional edge between vertex (u) and vertex (v):-\n";
            for(int edge = 0; edge < E;) {
                // Input the vertices of the edge
                int u, v;
                cout<<"Enter the "<<edge<<"th edge [u, v]: ";
                cin>>u>>v;
                // Check the given arrays are lying within the problem constraints or not
                if(uniqEdges.count({u, v})) {
                    cout<<"The edge ["<<u<<", "<<v<<"] already exists! Kindly enter unique edges, no duplicates allowed!\n";
                }
                else if(u == v) {
                    std::cout<<"You must enter the different arrays, vertices can't be same!\n";
                }
                else if(u <= -1 || u >= V || v <= -1 || v >= V) {
                    cout<<"You must enter the edge [u, v] which lies between 0 and "<<V - 1<<"!\n";
                }
                else {
                    edges[edge] = {u, v};
                    uniqEdges.insert({u, v});
                    edge++;
                }
            }

            // Call to get the list containing the bfs order
            Solution solution;
            vector<vector<int>> bfsOrder = solution.breadthFirstSearch(V, edges);

            // Print the bfs order of each component
            cout<<"\nThe BFS order of:\n";
            int size1 = bfsOrder.size();
            for(int component = 0; component < size1; ++component) {
                int size2 = bfsOrder[component].size();
                cout<<"Component "<<component + 1<<": [";
                for(int vertex = 0; vertex < size2; ++vertex) {
                    cout<<bfsOrder[component][vertex];
                    if(vertex < size2 - 1) {
                        cout<<", ";
                    }
                }
                cout<<"]\n";
            }
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userRunsApp = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Breadth-first-search | Graph
    Link  : https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/0
*/
