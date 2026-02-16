#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <climits>
#include <sstream>
#include <algorithm>

using namespace std;

/*

Range Minimum Query

https://www.geeksforgeeks.org/problems/range-minimum-query/1


Problem statement:
Given an array A[ ] and its size N your task is to complete two functions  a constructST  function which builds the segment tree  and a function RMQ which finds range minimum query in a range [a,b] of the given array.

Input:
The task is to complete two functions constructST and RMQ.
The constructST function builds the segment tree and takes two arguments the array A[ ] and the size of the array N.
It returns a pointer to the first element of the segment tree array.
The RMQ function takes 4 arguments the first being the segment tree st constructed, second being the size N and then third and forth arguments are the range of query a and b. The function RMQ returns the min of the elements in the array from index range a and b. There are multiple test cases. For each test case, this method will be called individually.

Output:
The function RMQ should return the min element in the array from range a to b.

Example:

Input (To be used only for expected output)
1
4
1 2 3 4
2
0 2 2 3
Output
1 3
Explanation
1. For query 1 ie 0 2 the element in this range are 1 2 3
   and the min element is 1.
2. For query 2 ie 2 3 the element in this range are 3 4
   and the min element is 3.

   Constraints:
1<=T<=100
1<=N<=10^3+1
1<=A[i]<=10^9
1<=Q(no of queries)<=10000
0<=a<=b

*/

//-------------------------------------------
// Approach: Segment tree
//-------------------------------------------

/* * Global pointer for the Segment Tree array.
 * This stores the tree nodes. Since it's global, the build function
 * can access it directly without passing it around.
 */
int *segT;

/*
 * Function: buildSegT
 * -------------------
 * Recursively builds the Segment Tree from the input array.
 *
 * @param l     Left index of the current range in 'arr'
 * @param r     Right index of the current range in 'arr'
 * @param segI  Current index in the Segment Tree array (Root is 0)
 * @param arr   Input array containing original data
 *
 * Time Complexity: O(N) - We visit every node once.
 */
void buildSegT(int l, int r, int segI, int arr[])
{

    // Base Case: Leaf Node
    // If l == r, the range contains only one element.
    // This is a leaf node of the segment tree.
    if (l == r)
    {
        segT[segI] = arr[l];
        return;
    }

    int mid = l + (r - l) / 2;

    // Recursive Step: Divide
    // Build the left child (indices 2*i + 1)
    buildSegT(l, mid, 2 * segI + 1, arr);

    // Build the right child (indices 2*i + 2)
    buildSegT(mid + 1, r, 2 * segI + 2, arr);

    // Merge Step: Conquer
    // The value of the current internal node is the Minimum of its children.
    segT[segI] = min(segT[2 * segI + 1], segT[2 * segI + 2]);
}

/*
 * Function: recMin
 * ----------------
 * Queries the Segment Tree for the minimum value in range [qL, qR].
 *
 * @param l, r  Current range covered by the node 'segI'
 * @param segI  Current node index in the Segment Tree
 * @param qL, qR Query range (inclusive)
 * @param st    Pointer to the segment tree array (passed as argument here)
 * @param n     Size of the array (not strictly needed for logic, but often passed)
 *
 * Time Complexity: O(log N) - Worst case visits 4 nodes per level.
 */
int recMin(int l, int r, int segI, int qL, int qR, int st[], int n)
{

    // Case 1: Total Overlap
    // The current node's range [l, r] is completely inside the query range [qL, qR].
    // We can simply return the pre-calculated value of this node.
    if (qL <= l && r <= qR)
    {
        return st[segI];
    }

    // Case 2: No Overlap
    // The current node's range is completely outside the query range.
    // Return INT_MAX (Identity element for Min) so it doesn't affect the result.
    if (r < qL || qR < l)
    {
        return INT_MAX;
    }

    // Case 3: Partial Overlap
    // The ranges partially overlap, so we must look deeper into both children.
    int mid = l + (r - l) / 2;

    //

    // Query Left Child
    int left = recMin(l, mid, 2 * segI + 1, qL, qR, st, n);

    // Query Right Child
    int right = recMin(mid + 1, r, 2 * segI + 2, qL, qR, st, n);

    // Combine results from both sides
    return min(left, right);
}

/* * Function: constructST
 * ---------------------
 * allocatest memory and triggers the build process.
 *
 * @param arr Input array
 * @param n   Size of input array
 * @return    Pointer to the built segment tree
 */
int *constructST(int arr[], int n)
{

    // Allocate memory for the Segment Tree.
    // Size is 4*n to handle the worst-case padding for a complete binary tree.
    segT = new int[4 * n];

    // Start building from the root (index 0) covering range [0, n-1]
    buildSegT(0, n - 1, 0, arr);

    return segT;
}

/* * Function: RMQ (Range Minimum Query)
 * -----------------------------------
 * Wrapper function for the query.
 *
 * @param st Segment Tree array
 * @param n  Size of original array
 * @param a  Query start index
 * @param b  Query end index
 * @return   Minimum value in range [a, b]
 */
int RMQ(int st[], int n, int a, int b)
{

    // Call the recursive query helper starting from the root
    return recMin(0, n - 1, 0, a, b, st, n);
}

int main()
{

    return 0;
}