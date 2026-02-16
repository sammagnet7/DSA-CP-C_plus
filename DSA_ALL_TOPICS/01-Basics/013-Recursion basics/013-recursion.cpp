#include <iostream>

using namespace std;

/*
https://takeuforward.org/recursion/print-1-to-n-using-recursion/
https://takeuforward.org/recursion/print-n-to-1-using-recursion/
https://takeuforward.org/data-structure/sum-of-first-n-natural-numbers/
*/

class Solution
{
public:
    bool dummy(int N)
    {
        
        return true;
    }
};

//{ Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int N;
        cin >> N;
        Solution ob;

        cout<<boolalpha;
        cout << ob.dummy(N) << endl;
        cout << "--" << endl;
        cout<<noboolalpha;
    }
    return 0;
}
// } Driver Code Ends