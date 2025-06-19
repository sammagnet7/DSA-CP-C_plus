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

Rat In A Maze:

https://takeuforward.org/data-structure/rat-in-a-maze/
https://www.naukri.com/code360/problems/rat-in-a-maze_1215030?leftPanelTabValue=PROBLEM


Problem statement:
Consider a rat placed at (0, 0) in a square matrix of order N * N. It has to reach the destination at (N - 1, N - 1). Find all possible paths that the rat can take to reach from source to destination. The directions in which the rat can move are 'U'(up), 'D'(down), 'L' (left), 'R' (right). Value 0 at a cell in the matrix represents that it is blocked and the rat cannot move to it while value 1 at a cell in the matrix represents that rat can travel through it.
Note: In a path, no cell can be visited more than one time.
Print the answer in lexicographical(sorted) order

Examples:

Example 1:
Input:
N = 4
m[][] = {{1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}}
Output: DDRDRR DRDDRR
Explanation:
The rat can reach the destination at (3, 3) from (0, 0) by two paths - DRDDRR and DDRDRR, when printed in sorted order we get DDRDRR DRDDRR.

Example 2:
Input: N = 2
       m[][] = {{1, 0},
                {1, 0}}
Output:
 No path exists and the destination cell is blocked.


INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Rat In A Maze:

    // O(4^(N^2))
    void recursiveMaze(vector<vector<int>> &arr, vector<string> &ans, string &path, int n, int rowIdx, int colIdx)
    {

        if (rowIdx == (n - 1) && colIdx == (n - 1))
        {
            ans.push_back(path);
            return;
        }

        if (rowIdx < 0 || colIdx < 0 || rowIdx >= n || rowIdx >= n)
            return;

        if (arr[rowIdx][colIdx] == -1 || arr[rowIdx][colIdx] == 0)
        {
            return;
        }

        arr[rowIdx][colIdx] = -1;

        path.push_back('D');
        recursiveMaze(arr, ans, path, n, (rowIdx + 1), colIdx); // down
        path.pop_back();

        path.push_back('L');
        recursiveMaze(arr, ans, path, n, rowIdx, (colIdx - 1)); // left
        path.pop_back();

        path.push_back('R');
        recursiveMaze(arr, ans, path, n, rowIdx, (colIdx + 1)); // right
        path.pop_back();

        path.push_back('U');
        recursiveMaze(arr, ans, path, n, (rowIdx - 1), colIdx); // up
        path.pop_back();

        arr[rowIdx][colIdx] = 1;
    }

    // Optimal approach: Backtracking
    // Time: O(4^(N^2) * N^2) because at each step 4 possible paths and copying the vector
    // Space: O(N^2) i.e. auxiliary space for recursion stack space
    vector<string> searchMaze(vector<vector<int>> &arr, int n)
    {

        vector<string> ans;
        string path;

        if (arr[0][0] == 0)
            return ans;

        recursiveMaze(arr, ans, path, n, 0, 0);

        // sort(ans.begin(), ans.end()); // No need of sorting if
        //  recursive search is done in Lexicographical order itself
        //  i.e. D->L->R->U
        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
