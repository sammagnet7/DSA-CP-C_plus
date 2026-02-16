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

Expression Add Operators:

https://leetcode.com/problems/expression-add-operators/description/


Problem statement:
Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.
Note that operands in the returned expressions should not contain leading zeros.
 
Examples:

Example 1:
Input: num = "123", target = 6
Output: ["1*2*3","1+2+3"]
Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.

Example 2:
Input: num = "232", target = 8
Output: ["2*3+2","2+3*2"]
Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.

Example 3:
Input: num = "3456237490", target = 9191
Output: []
Explanation: There are no expressions that can be created from "3456237490" to evaluate to 9191.
 
Example 4:
num = "105"
target =
5
Expected
["1*0+5","10-5"]

Example 5:
num = "2147483648"
target =
-2147483648
Expected
[]

Example 6:
num =
"00"
target =
0
Expected
["0*0","0+0","0-0"]

Example 7:
num = "123456789"
target =
45
Expected
["1*2*3*4*5-6-78+9","1*2*3*4+5+6-7+8+9","1*2*3+4+5+6+7+8+9","1*2*3+4+5-6*7+8*9","1*2*3+4-5*6+7*8+9","1*2*3+4-5*6-7+8*9","1*2*3-4*5+6*7+8+9","1*2*3-4*5-6+7*8+9","1*2*3-4*5-6-7+8*9","1*2*3-45+67+8+9","1*2*34+56-7-8*9","1*2*34-5+6-7-8-9","1*2+3*4-56+78+9","1*2+3+4+5*6+7+8-9","1*2+3+4-5+6*7+8-9","1*2+3+4-5-6+7*8-9","1*2+3+45+67-8*9","1*2+3-45+6+7+8*9","1*2+34+5-6-7+8+9","1*2+34+56-7*8+9","1*2+34-5+6+7-8+9","1*2+34-56+7*8+9","1*2+34-56-7+8*9","1*2-3*4+5+67-8-9","1*2-3+4-5-6*7+89","1*2-3-4*5+67+8-9","1*2-3-4+56-7-8+9","1*2-34+5*6+7*8-9","1*23+4*5-6+7-8+9","1*23-4-56-7+89","1+2*3*4*5+6+7-89","1+2*3*4+5*6+7-8-9","1+2*3*4-5+6*7-8-9","1+2*3+4*5*6+7-89","1+2*3+4*5-6+7+8+9","1+2*3-4-5-6*7+89","1+2*34-5*6+7+8-9","1+2+3*4*5+6-7-8-9","1+2+3*4+5+6*7-8-9","1+2+3*45-6-78-9","1+2+3+4+5+6+7+8+9","1+2+3+4+5-6*7+8*9","1+2+3+4-5*6+7*8+9","1+2+3+4-5*6-7+8*9","1+2+3-4*5+6*7+8+9","1+2+3-4*5-6+7*8+9","1+2+3-4*5-6-7+8*9","1+2+3-45+67+8+9","1+2-3*4*5+6+7+89","1+2-3*4+5*6+7+8+9","1+2-3*4-5+6*7+8+9","1+2-3*4-5-6+7*8+9","1+2-3*4-5-6-7+8*9","1+2-3+4*5+6*7-8-9","1+2-3+45+6-7-8+9","1+2-3+45-6+7+8-9","1+2-3-4-5*6+7+8*9","1+2-3-45-6+7+89","1+2-34+5+6+7*8+9","1+2-34+5+6-7+8*9","1+2-34-5-6+78+9","1+23*4+5-6-7*8+9","1+23*4-5-6*7+8-9","1+23*4-56+7-8+9","1+23+4+5+6+7+8-9","1+23+4-5*6+7*8-9","1+23+4-5-67+89","1+23-4*5+6*7+8-9","1+23-4*5-6+7*8-9","1+23-4-5+6+7+8+9","1+23-4-5-6*7+8*9","1+23-45+67+8-9","1-2*3*4+5-6+78-9","1-2*3*4-5-6+7+8*9","1-2*3+4*5+6+7+8+9","1-2*3+4*5-6*7+8*9","1-2*3+4+5+6*7+8-9","1-2*3+4+5-6+7*8-9","1-2*3+4+56+7-8-9","1-2*3+45-67+8*9","1-2*3-4+5*6+7+8+9","1-2*3-4-5+6*7+8+9","1-2*3-4-5-6+7*8+9","1-2*3-4-5-6-7+8*9","1-2*34+5*6-7+89","1-2+3*4*5-6-7+8-9","1-2+3+4-5*6+78-9","1-2+3+45+6-7+8-9","1-2+3-4*5-6+78-9","1-2+3-45+6-7+89","1-2-3*4+5+6+7*8-9","1-2-3*4-5-6+78-9","1-2-3+4-5+67-8-9","1-2-3+45-6-7+8+9","1-2-34+5+6+78-9","1-2-34+56+7+8+9","1-2-34-5+6+7+8*9","1-23*4+5+6*7+89","1-23+4*5-6*7+89","1-23+4-5+67-8+9","1-23+45-67+89","1-23-4+5+67+8-9","1-23-4-5-6-7+89","12*3*4-5*6-78+9","12*3+4+5+6-7-8+9","12*3+4+5-6+7+8-9","12*3-4-5-6+7+8+9","12*3-4-56+78-9","12+3*4+5+6-7+8+9","12+3*45-6-7-89","12+3+4-56-7+89","12+3-4*5+67-8-9","12+3-45+6+78-9","12+34-5-6-7+8+9","12-3*4*5+6+78+9","12-3*4-5+67-8-9","12-3+4*5+6-7+8+9","12-3+4+56-7-8-9","12-3-4+5*6-7+8+9","12-3-4-56+7+89","12-3-45-6+78+9"]

Constraints:
1 <= num.length <= 10
num consists of only digits.
-231 <= target <= 231 - 1

Note: below solution is not optimal. Was getting TLE. 

INPUT::::::


OUTPUT::::::

*/

class Solution
{
public:
    // ---------------------------------------------
    // Expression Add Operators:

    // Helper of O(n)
    // Must eliminate to escape from TLE
    int evaluateExpression(string &expression, int target) {

        long result = 0;
        long currentNum = 0;
        char operation = '+'; // Assume a '+' before first number
        stack<int> stk;

        for (int i = 0; i < expression.size(); i++) {
            char c = expression[i];

            if (isdigit(c)) {
                currentNum = currentNum * 10 + (c - '0');
            }

            // If operator or end of expression, apply previous operation
            if (!isdigit(c) || i == expression.size() - 1) {
                if (operation == '+') {
                    stk.push(currentNum);
                } else if (operation == '-') {
                    stk.push(-currentNum);
                } else if (operation == '*') {
                    long temp = stk.top(); 
                    stk.pop();
                    stk.push(temp * currentNum);
                } else if (operation == '/') {
                    int temp = stk.top(); stk.pop();
                    stk.push(temp / currentNum);
                }

                operation = c;    // Update operation
                currentNum = 0;   // Reset current number
            }
        }

        // Sum up everything in the stack
        while (!stk.empty()) {
            result += stk.top();
            stk.pop();
        }

        return result;
    }


    // Solve TLE
    void recurseExpression(vector<string> &ans,string &expression, vector<char> &exprArr, string &num, int target, int curIdx){
        
        if(curIdx == num.size()){
            if( !isdigit(expression.back()) ) return;
            long res = evaluateExpression(expression, target);
            if(res == target)
                ans.push_back(expression);
            return;
        }

        if (!expression.empty() && expression.back() == '0') {

            if (expression.size() == 1 ||
                    (expression.size() >= 2 &&
                        (expression[expression.size() - 2] == '+' ||
                        expression[expression.size() - 2] == '-' ||
                        expression[expression.size() - 2] == '*')))
                return;
        }

        char cur = num[curIdx];
        expression.push_back(cur);

        recurseExpression( ans,expression, exprArr, num, target, (curIdx+1) );  // Call with NO_OP

        for(char c: exprArr){   // Call with 3 operators
            expression.push_back(c);

            recurseExpression( ans,expression, exprArr, num, target, (curIdx+1) );

            expression.pop_back();
        }

        expression.pop_back();
    }

    // // Solve TLE with calculating `result ` on the fly
    //
    //
    vector<string> addOperators(string num, int target) {
        vector<string> ans;
        string expression = "";
        vector<char> exprArr = {'*','+', '-'};

        recurseExpression( ans,expression, exprArr, num, target, 0 );

        return ans;
    }
};

int main()
{
    Solution *obj = new Solution();

    return 0;
}
