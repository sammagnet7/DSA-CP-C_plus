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

1. Title: Does array represent Heap

Links:
https://takeuforward.org/plus/dsa/heaps/theory-and-implementation/check-if-an-array-represents-a-min-heap-?tab=editorial
https://www.geeksforgeeks.org/problems/does-array-represent-heap4345/1


Problem statement:
Given an array arr of size n, the task is to check if the given array can be a level order representation of a Max Heap.

Example 1:

Input:
n = 6
arr[] = {90, 15, 10, 7, 12, 2}
Output: 
1
Explanation: 
The given array represents below tree
       90
     /    \
   15      10
  /  \     /
7    12  2
The tree follows max-heap property as every
node is greater than all of its descendants.
Example 2:
Input:  
n = 6
arr[] = {9, 15, 10, 7, 12, 11}
Output:
0
Explanation:
The given array represents below tree
       9
     /    \
   15      10
  /  \     /
7    12  11
The tree doesn't follows max-heap property 9 is
smaller than 15 and 10, and 10 is smaller than 11. 
Your Task:  
You don't need to read input or print anything. Your task is to complete the function isMaxHeap() which takes the array arr[] and its size n as inputs and returns True if the given array could represent a valid level order representation of a Max Heap, or else, it will return False.

Expected Time Complexity: O(n)
Expected Auxiliary Space: O(1)


INPUT::::::


OUTPUT::::::

----------------------------------------------------------------------------------------------------


*/


class Solution {
  public:
    //-------------------------------------------------------------------------------
    // 1. Title: Does array represent Heap
    //-------------------------------------------------------------------------------

    // Optimal approach
    // Time: O(N/2)
    // Space: O(1)
    bool isMaxHeap(int arr[], int n) {
        // Your code goes here
        
        for(int i=(n/2-1); i>=0; i--){
            
            int lc_x = 2*i+1; 
            int rc_x = 2*i+2;
            
            if(lc_x<n && arr[lc_x]>arr[i])
                return false;
            if(rc_x<n && arr[rc_x]>arr[i])
                return false;
        }
        
        return true;
    }

    
};

int main()
{
    return 0;
}
