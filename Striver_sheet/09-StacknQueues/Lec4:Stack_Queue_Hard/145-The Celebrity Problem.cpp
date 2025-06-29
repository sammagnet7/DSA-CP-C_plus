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

1. Title: The Celebrity Problem

Links:
https://www.youtube.com/watch?v=cEadsbTeze4
https://takeuforward.org/plus/dsa/problems/celebrity-problem?tab=editorial
https://leetcode.com/problems/find-the-celebrity/description/
https://www.naukri.com/code360/problems/the-celebrity-problem_10728328


Problem statement:
There are ‘N’ people at a party. Each person has been assigned a unique id between 0 to 'N' - 1(both inclusive). A celebrity is a person who is known to everyone but does not know anyone at the party.

Given a helper function ‘knows(A, B)’, It will returns "true" if the person having id ‘A’ know the person having id ‘B’ in the party, "false" otherwise. Your task is to find out the celebrity at the party. Print the id of the celebrity, if there is no celebrity at the party then print -1.

Note:
1. The helper function ‘knows’ is already implemented for you.
2. ‘knows(A, B)’ returns "false", if A doesn't know B.
3. You should not implement helper function ‘knows’, or speculate about its implementation.
4. You should minimize the number of calls to function ‘knows(A, B)’.
5. There are at least 2 people at the party.
6. At most one celebrity will exist.
Detailed explanation ( Input/output format, Notes, Images )
Constraints:
1 <= T <= 50
2 <= N <= 10^4

Where ‘T’ is the total number of test cases, ‘N’ is the number of people at the party.

Time Limit: 1sec
Sample Input 1:
1
2
Call function ‘knows(0, 1)’ // returns false
Call function ‘knows(1, 0)’ // returns true
Sample Output 1:
0
Explanation For Sample Input 1:
In the first test case, there are 2 people at the party. When we call function knows(0,1), it returns false. That means the person having id ‘0’ does not know a person having id ‘1'. Similarly, the person having id ‘1’  knows a person having id ‘0’ as knows(1,0) returns true. Thus a person having id ‘0’ is a celebrity because he is known to everyone at the party but doesn't know anyone.
Sample Input 2:
1
2
Call ‘knows(0, 1)’ // returns true
Call ‘knows(1, 0)’ // returns true
2
Call ‘knows(0, 1)’ // returns false
Call ‘knows(1, 0)’ // returns false
Sample Output 2:
-1
-1
Explanation For Sample Input 2:
In first test case, there are 2 people at the party. The person having id ‘0’  knows a person having id ‘1’. The person having id ‘1’  knows a person having id ‘0’. Thus there is no celebrity at the party, because both know each other.
In second test case, there are 2 people at the party. The person having id ‘0’ does not knows a person having id ‘1’. The person having id ‘1’  also does not knows a person having id ‘0’. Thus there is no celebrity at the party, because both does not know each other.


INPUT::::::


OUTPUT::::::


*/

//------------------------------------------------------------------------
// 1. The Celebrity Problem
//

int matrix[1000][1000];

/*
    This is signature of helper function 'knows'.
    You should not implement it, or speculate about its implementation.

    bool knows(int A, int B);
    Function 'knows(A, B)' will returns "true" if the person having
    id 'A' know the person having id 'B' in the party, "false" otherwise.
*/
bool knows(int i, int j)
{
    return matrix[i][j];
}

//

// // Approach:1 : My approach
// // Optimal approach: Using two pointers from same direction
// // Time: O(2N)
// // SPace: O(1)
// int findCelebrity(int n) {
//  	// Write your code here.

// 	int i=0;
// 	int j=1;

// 	while(i<n && j<n){	// O(N)

// 		// if(i==j){	// This is getting handled by 4th case
// 		// 	j=i+1;
// 		// }
// 		// if(i>=n || j>= n) break;

// 		if(knows(i,j) && knows(j,i)){	// 1st case: i knows j, j knows i
// 			j++;
// 			i=j;
// 		}
// 		else if(knows(i,j) && !knows(j,i)){	// 2nd case: i knows j, j NOTknows i
// 			i=j;
// 			j++;
// 		}
// 		else if(!knows(i,j) && knows(j,i)){	// 3rd case: i NOTknows j, j knows i
// 			j++;
// 		}
// 		else if(!knows(i,j) && !knows(j,i)){	// 4th case: i NOTknows j, j NOTknows i
// 			i=j; j++;
// 		}
// 	}

// 	if(i>=n) return -1; // If `i` invalid return -1

// 	for(int k=0; k<n; k++){	// O(N): double checking
// 		if(i!=k && knows(i,k)) return -1;
// 		if(i!=k && !knows(k,i)) return -1;
// 	}

// 	return i;	// `i` is a celebrity
// }

// Approach2 : Striver's approach
// Optimal approach: Using two pointers from opposit direction
// Time: O(2N)
// SPace: O(1)
int findCelebrity(int N)
{
    // Size of given matrix

    // Top and Down pointers
    int top = 0, down = N - 1;

    // Traverse for all the people
    while (top < down)
    {

        /* If top knows down,
        it can not be a celebrity */
        if (knows(top, down))
        {
            top = top + 1;
        }

        /* If down knowns top,
        it can not be a celebrity */
        else if (knows(down, top))
        {
            down = down - 1;
        }

        /* If both does not know each other,
        both cannot be the celebrity */
        else
        {
            top++;
            down--;
        }
    }

    // Return -1 if no celebrity is found
    if (top > down)
        return -1;

    /* Check if the person pointed
    by top is celebrity */
    for (int i = 0; i < N; i++)
    {
        if (i == top)
            continue;

        // Check if it is not a celebrity
        if (knows(top, i) || !knows(i, top))
        {
            return -1;
        }
    }

    // Return the index of celebrity
    return top;
}

int main()
{
    return 0;
}
