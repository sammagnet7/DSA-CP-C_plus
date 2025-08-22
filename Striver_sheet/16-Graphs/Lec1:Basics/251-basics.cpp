#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <queue>
#include <climits>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_set>
#include <stack>
#include <string.h>
#include <list>

using namespace std;

/*

1. Title: Introduction to Graph

Links:
https://takeuforward.org/graph/introduction-to-graph/
https://www.youtube.com/watch?v=M3_pLsDdeuU
https://takeuforward.org/plus/dsa/problems/introduction-to-graph?tab=editorial




Problem statement:



INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------

2. Title: Graph Representation | C++

Links:
https://takeuforward.org/graph/graph-representation-in-c/
https://www.youtube.com/watch?v=3oI-34aPMWM
https://takeuforward.org/plus/dsa/problems/introduction-to-graph?tab=editorial


Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

class Solution
{
public:
    //-------------------------------------------------------------------------------
    // 1. Title:
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    // 2. Title: Graph Representation | C++
    //-------------------------------------------------------------------------------

    void printGraph(int V, vector<vector<int>> &edges)
    {
        // code here

        vector<vector<int>> adj_matrix(V + 1, vector<int>(V + 1, 0));

        vector<vector<int>> adj_list(V + 1);

        for (int i = 0; i < edges.size(); i++)
        {

            int n1 = edges[i][0];
            int n2 = edges[i][1];

            // building Adjascency matrix
            adj_matrix[n1][n2] = 1;
            adj_matrix[n2][n1] = 1;

            // building Adjascency list
            adj_list[n1].push_back(n2);
            adj_list[n2].push_back(n1);
        }

        cout << "====Printing adjacency matrix=======";
        cout << endl;

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << " " << adj_matrix[i][j];
            }
            cout << endl;
        }

        cout << "====Printing adjacency list=======";
        cout << endl;

        for (int i = 0; i < V; i++)
        {   
            cout<<"node_"<<i<<": ";
            for (int j = 0; j < adj_list[i].size(); j++)
            {
                cout << " " << adj_list[i][j];
            }
            cout << endl;
        }
    }

};

int main()
{   

    vector<vector<int>> edges;

    edges.push_back({0,1});
    edges.push_back({2,1});
    edges.push_back({3,4});

    Solution ob;

    ob.printGraph(5, edges);
    return 0;
}
