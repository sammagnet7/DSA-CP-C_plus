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

1. Title: Accounts Merge - DSU: G-50
Links:
https://takeuforward.org/data-structure/accounts-merge-dsu-g-50/
https://www.youtube.com/watch?v=FMwpt_aQOGw
https://takeuforward.org/plus/dsa/problems/accounts-merge?tab=editorial
https://leetcode.com/problems/accounts-merge/description/


Problem statement:
Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.
Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.
After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

Examples:
    Example 1:
    Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Explanation:
    The first and second John's are the same person as they have the common email "johnsmith@mail.com".
    The third John and Mary are different people as none of their email addresses are used by other accounts.
    We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
    ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.

    Example 2:
    Input: accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
    Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]

Constraints:
    1 <= accounts.length <= 1000
    2 <= accounts[i].length <= 10
    1 <= accounts[i][j].length <= 30
    accounts[i][0] consists of English letters.
    accounts[i][j] (for j > 0) is a valid email.



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
// 1. Title: Accounts Merge - DSU: G-50
//-------------------------------------------------------------------------------
//

class Solution
{
public:
    // ------------------------------------------------------------------------
    // Disjoint Set (Union-Find) with Union by Size + Path Compression
    // ------------------------------------------------------------------------
    class DJS
    {
    public:
        vector<int> p, s; // parent array, size array

        // Constructor
        // Initialize DSU with n nodes, each node is its own parent
        // Complexity: O(n)
        DJS(int n)
        {
            p.resize(n + 1);
            s.resize(n + 1, 1); // each set starts with size = 1
            for (int i = 0; i <= n; i++)
            {
                p[i] = i; // parent of itself
            }
        }

        // Find ultimate parent with path compression
        // Complexity: Amortized O(α(n)) ~ constant
        int fUP(int u)
        {
            if (u == p[u])
                return u;
            return p[u] = fUP(p[u]); // compress path
        }

        // Check if two nodes belong to the same set
        bool isSame(int u, int v)
        {
            return (fUP(u) == fUP(v));
        }

        // Union by Size
        // Attach smaller set to larger set
        // Complexity: Amortized O(α(n))
        void UBS(int u, int v)
        {
            int pu = fUP(u);
            int pv = fUP(v);

            if (pu == pv)
                return; // already connected

            if (s[pu] == s[pv])
            {
                p[pu] = pv;
                s[pv] += s[pu];
            }
            else if (s[pu] < s[pv])
            {
                p[pu] = pv;
                s[pv] += s[pu];
            }
            else
            {
                p[pv] = pu;
                s[pu] += s[pv];
            }
        }
    };

    // ------------------------------------------------------------------------
    // Problem: Accounts Merge (LeetCode 721)
    //
    // Intuition:
    // - Each account has a name and multiple emails.
    // - If two accounts share at least one email, they belong to the same person.
    // - This forms a graph: accounts are nodes, shared emails form edges.
    // - DSU (Disjoint Set Union) efficiently merges such connected components.
    //
    // Approach:
    // 1. Initialize a DSU with "n = accounts.size()" (each account = one node).
    // 2. Map emails to accounts:
    //    - Traverse each account and its emails.
    //    - If an email is seen for the first time, map it → current account ID.
    //    - If already seen, union the current account with the previous account
    //      that owned this email.
    // 3. Build a map from DSU rootID → list of emails.
    // 4. For each connected component:
    //    - Sort emails lexicographically.
    //    - Add the owner's name (from original accounts list).
    //    - Append [name, email1, email2...] to result.
    //
    // Complexity Analysis:
    // - Traversing emails: O(N + E)
    // - Union operations: O(E * α(N))
    // - Grouping emails: O(E * α(N))
    // - Sorting emails: O(E log E) (worst case: all in one account)
    // - Overall: O(N + E log E)
    //
    // Space Complexity:
    // - HashMap email→ID: O(E)
    // - DSU arrays: O(N)
    // - Grouped emails: O(E)
    // - Total: O(N + E)
    // ------------------------------------------------------------------------
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {

        unordered_map<string, int> EmailtoID; // maps email → accountID
        DJS DS(accounts.size());              // DSU on account IDs

        // Step 1: Union accounts that share the same email
        for (int ID = 0; ID < accounts.size(); ID++)
        {
            for (int j = 1; j < accounts[ID].size(); j++)
            {
                string &email = accounts[ID][j];

                if (EmailtoID.find(email) != EmailtoID.end())
                {
                    // email already seen → merge current account with previous
                    int preExistingID = EmailtoID[email];
                    DS.UBS(preExistingID, ID);
                }
                else
                {
                    // first time seeing this email
                    EmailtoID[email] = ID;
                }
            }
        }

        // Step 2: Group emails by their ultimate parent account
        unordered_map<int, vector<string>> IDtoemails;
        for (auto &it : EmailtoID)
        {
            string email = it.first;
            int ID = it.second;
            int rootID = DS.fUP(ID); // ultimate parent ID
            IDtoemails[rootID].push_back(email);
        }

        // Step 3: Build the merged accounts
        vector<vector<string>> ans;
        for (auto &it : IDtoemails)
        {
            int ID = it.first;
            vector<string> &emails = it.second;

            if (emails.empty())
                continue;

            sort(emails.begin(), emails.end()); // sort emails
            string &name = accounts[ID][0];     // account name

            vector<string> entry;
            entry.push_back(name); // add name first
            entry.insert(entry.end(), emails.begin(), emails.end());
            ans.push_back(move(entry));
        }

        return ans;
    }
};

// Utility function to print vector<vector<string>>
void printAccounts(const vector<vector<string>> &accounts)
{
    cout << "[\n";
    for (auto &acc : accounts)
    {
        cout << "  [";
        for (int i = 0; i < acc.size(); i++)
        {
            cout << "\"" << acc[i] << "\"";
            if (i != acc.size() - 1)
                cout << ",";
        }
        cout << "]\n";
    }
    cout << "]\n";
}

int main()
{
    Solution sol;

    // ------------------- Test Case 1 -------------------
    vector<vector<string>> accounts1 = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}};
    cout << "Test Case 1 Output:\n";
    auto res1 = sol.accountsMerge(accounts1);
    printAccounts(res1);

    cout << "\nExpected:\n";
    cout << "[[\"John\",\"john00@mail.com\",\"john_newyork@mail.com\",\"johnsmith@mail.com\"],"
            "[\"Mary\",\"mary@mail.com\"],"
            "[\"John\",\"johnnybravo@mail.com\"]]\n\n";

    // ------------------- Test Case 2 -------------------
    vector<vector<string>> accounts2 = {
        {"Gabe", "Gabe0@m.co", "Gabe3@m.co", "Gabe1@m.co"},
        {"Kevin", "Kevin3@m.co", "Kevin5@m.co", "Kevin0@m.co"},
        {"Ethan", "Ethan5@m.co", "Ethan4@m.co", "Ethan0@m.co"},
        {"Hanzo", "Hanzo3@m.co", "Hanzo1@m.co", "Hanzo0@m.co"},
        {"Fern", "Fern5@m.co", "Fern1@m.co", "Fern0@m.co"}};
    cout << "Test Case 2 Output:\n";
    auto res2 = sol.accountsMerge(accounts2);
    printAccounts(res2);

    cout << "\nExpected:\n";
    cout << "[[\"Ethan\",\"Ethan0@m.co\",\"Ethan4@m.co\",\"Ethan5@m.co\"],"
            "[\"Gabe\",\"Gabe0@m.co\",\"Gabe1@m.co\",\"Gabe3@m.co\"],"
            "[\"Hanzo\",\"Hanzo0@m.co\",\"Hanzo1@m.co\",\"Hanzo3@m.co\"],"
            "[\"Kevin\",\"Kevin0@m.co\",\"Kevin3@m.co\",\"Kevin5@m.co\"],"
            "[\"Fern\",\"Fern0@m.co\",\"Fern1@m.co\",\"Fern5@m.co\"]]\n";

    return 0;
}