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

using namespace std;

/*

M - Coloring Problem:

https://takeuforward.org/data-structure/m-coloring-problem/
https://www.naukri.com/code360/problems/m-coloring-problem_991934?leftPanelTabValue=PROBLEM

Problem statement:
Given an undirected graph and a number m, determine if the graph can be colored with at most m colors such that no two adjacent vertices of the graph are colored with the same color.

Examples:

Example 1:
Input:
N = 4
M = 3
E = 5
Edges[] = {
  (0, 1),
  (1, 2),
  (2, 3),
  (3, 0),
  (0, 2)
}
Output: 1
Explanation: It is possible to colour the given graph using 3 colours.

Example 2:
Input:
N = 3
M = 2
E = 3
Edges[] = {
  (0, 1),
  (1, 2),
  (0, 2)
}
Output: 0
Explanation: It is not possible to color.


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // M - Coloring Problem:

    // O(N)
    bool checkColorApplicable(vector<vector<int>> &adjMatrix, vector<int> &nodeColors, int curNodeIdx, int curColor)
    {

        for (int nodeIdx = 0; nodeIdx < adjMatrix.size(); nodeIdx++)
        {
            if (adjMatrix[curNodeIdx][nodeIdx] && nodeColors[nodeIdx] == curColor)
                return false;
        }
        return true;
    }

    // O(M^N)
    bool recursiveMcoloring(vector<vector<int>> &adjMatrix, vector<int> &nodeColors, int totNodes, int totColors, int curNodeIdx)
    {

        if (curNodeIdx == totNodes)
            return true;

        for (int i = 0; i < totColors; i++)
        {
            if (!checkColorApplicable(adjMatrix, nodeColors, curNodeIdx, i))
                continue;

            nodeColors[curNodeIdx] = i;
            bool ret = recursiveMcoloring(adjMatrix, nodeColors, totNodes, totColors, (curNodeIdx + 1));
            nodeColors[curNodeIdx] = -1;

            if (ret)
                return true;
        }

        return false;
    }

    // Optimal approach: Take all different color combinations possible.
    // Time: O(M^N) because there are M possibilities to color it and there are N nodes
    // Space: O(N) because We are using an array of size N for storing the colors of each vertex
    string graphColoring(vector<vector<int>> &adjMatrix, int n, int m)
    {
        vector<int> nodeColors(n, -1);

        bool ret = recursiveMcoloring(adjMatrix, nodeColors, n, m, 0);

        return ret ? "Yes" : "No";
    }
    
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
