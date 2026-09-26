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

1. Title: Making a Large Island

Links:
https://takeuforward.org/data-structure/making-a-large-island-dsu-g-52/
https://www.youtube.com/watch?v=lgiz0Oup6gM
https://takeuforward.org/plus/dsa/problems/making-a-large-island?tab=editorial
https://leetcode.com/problems/making-a-large-island/description/


Problem statement:
You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
Return the size of the largest island in grid after applying this operation.
An island is a 4-directionally connected group of 1s.

Examles:
    Example 1:
    Input: grid = [[1,0],[0,1]]
    Output: 3
    Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

    Example 2:
    Input: grid = [[1,1],[1,0]]
    Output: 4
    Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.

    Example 3:
    Input: grid = [[1,1],[1,1]]
    Output: 4
    Explanation: Can't change any 0 to 1, only one island with area = 4.


Constraints:
    n == grid.length
    n == grid[i].length
    1 <= n <= 500
    grid[i][j] is either 0 or 1.


INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

2. Title:


Links:




Problem statement:



INPUT::::::


OUTPUT::::::


----------------------------------------------------------------------------------------------------

*/

//-------------------------------------------------------------------------------
// 1. Title: Making a Large Island
//-------------------------------------------------------------------------------

class DSU
{
private:
    vector<int> parent, size;
    int existingMaxSize;

public:
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);

        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }

        existingMaxSize = 1;
    }

    int getPar(int i)
    {
        int p = parent[i];

        if (p == i)
        {
            return p;
        }
        else
        {
            return parent[i] = getPar(p);
        }
    }

    bool isConnected(int u, int v)
    {

        int pu = getPar(u);
        int pv = getPar(v);

        if (pu == pv)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void dunion(int u, int v)
    {

        int pu = getPar(u);
        int pv = getPar(v);

        if (pu == pv)
        {
            return;
        }

        int su = size[pu];
        int sv = size[pv];

        if (su <= sv)
        {
            parent[pu] = pv;
            size[pv] += size[pu];

            existingMaxSize = max(existingMaxSize, size[pv]);
        }
        else
        {
            parent[pv] = pu;
            size[pu] += size[pv];

            existingMaxSize = max(existingMaxSize, size[pu]);
        }
    }

    int getSize(int u)
    {
        int p = getPar(u);
        return size[p];
    }

    int getExistingMaxSize()
    {
        return existingMaxSize;
    }
};

class Solution
{
public:
    int largestIsland(vector<vector<int>> &grid)
    {

        int n = grid.size();
        DSU dsu(n * n);
        vector<vector<int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                if (grid[i][j] == 0)
                {
                    continue;
                }

                int pos = (i * n) + j;

                for (int k = 0; k < 4; ++k)
                {

                    int ni = i + dir[k][0];
                    int nj = j + dir[k][1];

                    if (ni < 0 || nj < 0 || ni >= n || nj >= n)
                    {
                        continue;
                    }

                    if (grid[ni][nj] == 0)
                    {
                        continue;
                    }

                    int npos = (ni * n) + nj;

                    dsu.dunion(pos, npos);
                }
            }
        }

        int maxSize = dsu.getExistingMaxSize();

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {

                if (grid[i][j] == 1)
                {
                    continue;
                }

                int pos = (i * n) + j;

                unordered_set<int> localPars;
                int curSize = 1;

                for (int k = 0; k < 4; ++k)
                {

                    int ni = i + dir[k][0];
                    int nj = j + dir[k][1];

                    if (ni < 0 || nj < 0 || ni >= n || nj >= n)
                    {
                        continue;
                    }

                    if (grid[ni][nj] == 0)
                    {
                        continue;
                    }

                    int npos = (ni * n) + nj;

                    int par = dsu.getPar(npos);

                    if (localPars.find(par) != localPars.end())
                    {
                        continue;
                    }

                    localPars.insert(par);

                    curSize += dsu.getSize(par);
                }

                maxSize = max(maxSize, curSize);
            }
        }

        return maxSize;
    }
};

int main()
{
    return 0;
}