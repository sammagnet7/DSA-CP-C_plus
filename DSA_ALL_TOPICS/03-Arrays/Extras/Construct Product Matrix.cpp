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

1. Title: Construct Product Matrix

Links:
https://leetcode.com/problems/construct-product-matrix/description/


Problem statement:
Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size n * m as the product matrix of grid if the following condition is met:

Each element p[i][j] is calculated as the product of all elements in grid except for the element grid[i][j]. This product is then taken modulo 12345.
Return the product matrix of grid.

 

Example 1:
    Input: grid = [[1,2],[3,4]]
    Output: [[24,12],[8,6]]
    Explanation: p[0][0] = grid[0][1] * grid[1][0] * grid[1][1] = 2 * 3 * 4 = 24
    p[0][1] = grid[0][0] * grid[1][0] * grid[1][1] = 1 * 3 * 4 = 12
    p[1][0] = grid[0][0] * grid[0][1] * grid[1][1] = 1 * 2 * 4 = 8
    p[1][1] = grid[0][0] * grid[0][1] * grid[1][0] = 1 * 2 * 3 = 6
    So the answer is [[24,12],[8,6]].

Example 2:
    Input: grid = [[12345],[2],[1]]
    Output: [[2],[0],[0]]
    Explanation: p[0][0] = grid[0][1] * grid[0][2] = 2 * 1 = 2.
    p[0][1] = grid[0][0] * grid[0][2] = 12345 * 1 = 12345. 12345 % 12345 = 0. So p[0][1] = 0.
    p[0][2] = grid[0][0] * grid[0][1] = 12345 * 2 = 24690. 24690 % 12345 = 0. So p[0][2] = 0.
    So the answer is [[2],[0],[0]].
 

Constraints:
    1 <= n == grid.length <= 10^5
    1 <= m == grid[i].length <= 10^5
    2 <= n * m <= 10^5
    1 <= grid[i][j] <= 10^9

----------------------------------------------------------------------------------------------------


2. Title: 

Links:


Problem statement:



----------------------------------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------
// 1. Title: Construct Product Matrix
//-------------------------------------------------------------------------------

/**
 * ============================================================================
 * Approach: 2-Pass Prefix & Suffix Products
 * ============================================================================
 * * Concept:
 * We avoid division (and the fatal modular inverse trap) by calculating the 
 * product of everything BEFORE a cell, and multiplying it by the product of 
 * everything AFTER a cell.
 * * 1. Forward Pass: We iterate row-major (top-left to bottom-right). We place 
 * the current `prefix` product into our answer matrix, then multiply `prefix` 
 * by the current grid value.
 * 2. Backward Pass: We iterate reverse row-major (bottom-right to top-left). 
 * We multiply the answer matrix by the current `suffix` product, then 
 * multiply `suffix` by the current grid value.
 * * ============================================================================
 * Complexity:
 * - Time: O(M * N). We touch every cell exactly twice.
 * - Space: O(1) auxiliary space. We only use two `long long` integers for state 
 * tracking (excluding the required output matrix `p`).
 * ============================================================================
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        
        int m = grid.size();
        int n = grid[0].size();
        int MOD = 12345;
        
        // The output matrix, initially filled with 0s
        vector<vector<int>> p(m, vector<int>(n, 0));
        
        // --------------------------------------------------------
        // PASS 1: Calculate Prefix Products
        // --------------------------------------------------------
        long long prefix = 1;
        
        // Cache-friendly row-major traversal
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Store the product of everything BEFORE this cell
                p[i][j] = prefix;
                
                // Update the prefix for the next cell
                // We use grid[i][j] % MOD just in case the raw value is huge
                prefix = (prefix * (grid[i][j] % MOD)) % MOD;
            }
        }
        
        // --------------------------------------------------------
        // PASS 2: Calculate Suffix Products & Finalize
        // --------------------------------------------------------
        long long suffix = 1;
        
        // Reverse row-major traversal
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // Multiply the existing prefix product by the suffix product
                p[i][j] = (p[i][j] * suffix) % MOD;
                
                // Update the suffix for the next cell (moving backwards)
                suffix = (suffix * (grid[i][j] % MOD)) % MOD;
            }
        }
        
        return p;
    }
};


int main()
{
    return 0;
}
