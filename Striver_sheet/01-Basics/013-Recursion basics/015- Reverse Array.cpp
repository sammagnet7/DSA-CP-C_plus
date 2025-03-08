#include <iostream>
#include <vector>
#include <string>
#include <sstream> // Include this for std::stringstream


using namespace std;

/*
https://takeuforward.org/data-structure/reverse-a-given-array/
https://www.geeksforgeeks.org/problems/reverse-an-array/0

Problem statement:
You are given an array of integers arr[]. Your task is to reverse the given array.

Note: Modify the array in place.

Examples:
Input: arr = [1, 4, 3, 2, 6, 5]
Output: [5, 6, 2, 3, 4, 1]
Explanation: The elements of the array are 1 4 3 2 6 5. After reversing the array, the first element goes to the last position, the second element goes to the second last position and so on. Hence, the answer is 5 6 2 3 4 1.

Input: arr = [4, 5, 2]
Output: [2, 5, 4]
Explanation: The elements of the array are 4 5 2. The reversed array will be 2 5 4.

Input: arr = [1]
Output: [1]
Explanation: The array has only single element, hence the reversed array is same as the original.

Constraints:
1<=arr.size()<=105
0<=arr[i]<=105
*/

class Solution
{
public:
    void reverseArray(vector<int> &arr)
    {
        // code here
        int len = arr.size();

        for (int i = 0; (i + 1) <= (len / 2); i++)
        {
            int temp = arr[len - 1 - i];
            arr[len - 1 - i] = arr[i];
            arr[i] = temp;
        }
    }

    //Recursiuve approach
    void reverseArrayRec(vector<int> &arr, int l, int r)
    {
        // code here
        if (l >= r)
            return;

        swap(arr[l], arr[r]);

        reverseArrayRec(arr, ++l, --r);
    }

    void reverseArray_RECURSIVE(vector<int> &arr)
    {

        reverseArrayRec(arr, 0, arr.size() - 1);
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    cin.ignore();
    cout<<endl;

    while (t--)
    {
        vector<int> arr;
        string input;
        getline(cin, input);
        stringstream ss(input);
        int number;
        while (ss >> number)
        {
            arr.push_back(number);
        }

        Solution ob;
        ob.reverseArray(arr);
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;

        ob.reverseArray_RECURSIVE(arr);
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "--" << endl;
    }
    return 0;
}
// } Driver Code Ends