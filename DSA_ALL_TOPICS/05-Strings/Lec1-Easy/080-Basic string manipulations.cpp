#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>
#include <stack>

using namespace std;

/*
1) Title: Remove outer most paranthesis

Link:
https://leetcode.com/problems/remove-outermost-parentheses/description/

Problem statement:
A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.

For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.

Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.

Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.


Examples:
Example 1:
    Input: s = "(()())(())"
    Output: "()()()"
    Explanation:
    The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
    After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Example 2:
    Input: s = "(()())(())(()(()))"
    Output: "()()()()(())"
    Explanation:
    The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
    After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Example 3:
    Input: s = "()()"
    Output: ""
    Explanation:
    The input string is "()()", with primitive decomposition "()" + "()".
    After removing outer parentheses of each part, this is "" + "" = "".

INPUT::::::
3
(()())(())
(()())(())(()(()))
()()

OUTPUT::::::
()()()
()()()()(())

-----------------------------------------------------------------------
2) Title: Reverse Words in a String

Link:
https://takeuforward.org/data-structure/reverse-words-in-a-string/
https://leetcode.com/problems/reverse-words-in-a-string/

Problem Statement: Given a string s, reverse the words of the string.

Given an input string s, reverse the order of the words.

A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.

Return a string of the words in reverse order concatenated by a single space.

Note that s may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

Example:

Example 1:
    Input: s = "the sky is blue"
    Output: "blue is sky the"

Example 2:
    Input: s = "  hello world  "
    Output: "world hello"
    Explanation: Your reversed string should not contain leading or trailing spaces.

Example 3:
    Input: s = "a good   example"
    Output: "example good a"
    Explanation: You need to reduce multiple spaces between two words to a single space in the reversed string.


INPUT::::::
3
the sky is blue
  hello world
a good   example

OUTPUT::::::
blue is sky the
world hello
example good a

-----------------------------------------------------------------------
3) Title: Largest Odd Number in String

Link:
https://leetcode.com/problems/largest-odd-number-in-string/

You are given a string num, representing a large integer. Return the largest-valued odd integer (as a string) that is a non-empty substring of num, or an empty string "" if no odd integer exists.

A substring is a contiguous sequence of characters within a string.


Example 1:
    Input: num = "52"
    Output: "5"
    Explanation: The only non-empty substrings are "5", "2", and "52". "5" is the only odd number.

Example 2:
    Input: num = "4206"
    Output: ""
    Explanation: There are no odd numbers in "4206".

Example 3:
    Input: num = "35427"
    Output: "35427"
    Explanation: "35427" is already an odd number.


Constraints:
    1 <= num.length <= 105
    num only consists of digits and does not contain any leading zeros.

-----------------------------------------------------------------------
4) Title: Longest Common Prefix in a String array

Link:
https://leetcode.com/problems/longest-common-prefix/description/

Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".

Example 1:
    Input: strs = ["flower","flow","flight"]
    Output: "fl"

Example 2:
    Input: strs = ["dog","racecar","car"]
    Output: ""
    Explanation: There is no common prefix among the input strings.


Constraints:
    1 <= strs.length <= 200
    0 <= strs[i].length <= 200
    strs[i] consists of only lowercase English letters if it is non-empty.

-----------------------------------------------------------------------
5) Title: Isomorphic Strings

Link:
https://leetcode.com/problems/isomorphic-strings/description/


Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.
All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character, but a character may map to itself.

Example 1:
    Input: s = "egg", t = "add"
    Output: true
    Explanation:
    The strings s and t can be made identical by:
    Mapping 'e' to 'a'.
    Mapping 'g' to 'd'.

Example 2:
    Input: s = "foo", t = "bar"
    Output: false
    Explanation:
    The strings s and t can not be made identical as 'o' needs to be mapped to both 'a' and 'r'.

Example 3:
    Input: s = "paper", t = "title"
    Output: true

Constraints:
    1 <= s.length <= 5 * 10^4
    t.length == s.length
    s and t consist of any valid ascii character.


INPUT::::::
3
egg
add
foo
bar
paper
title

OUTPUT::::::
true
false
true

-----------------------------------------------------------------------
6) Title: Rotate String

Link:
https://leetcode.com/problems/rotate-string/description/

Given two strings s and `goal`, return true if and only if s can become `goal` after some number of shifts on s.
A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.

Example 1:
    Input: s = "abcde", goal = "cdeab"
    Output: true

Example 2:
    Input: s = "abcde", goal = "abced"
    Output: false

Constraints:
    1 <= s.length, goal.length <= 100
    s and `goal` consist of lowercase English letters.


INPUT::::::
    2
    abcde
    cdeab
    abcde
    abced


OUTPUT::::::
true
false

-----------------------------------------------------------------------
7) ttile: Valid Anagram

Links:
https://takeuforward.org/data-structure/check-if-two-strings-are-anagrams-of-each-other/
https://leetcode.com/problems/valid-anagram/

Problem Statement: Check if two Strings are anagrams of each other

Anagrams of a string are all the possible permutations of that string

Example 1:
    Input: CAT, ACT
    Output: true
    Explanation: Since the count of every letter of both strings are equal.

Example 2:
    Input: RULES, LESRT
    Output: false
    Explanation: Since the count of U and T  is not equal in both strings.


Constraints:
    1 <= s.length, t.length <= 5 * 104
    s and t consist of lowercase English letters.


Follow up: What if the inputs contain Unicode characters? How would you adapt your solution to such a case?

 */

//-------------------------------------------------------------------------------
// 1. Title: Remove outer most paranthesis
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * @brief Removes the outermost parentheses of every primitive valid string.
     * * * 🧠 INTUITION:
     * A valid parentheses string can be split into "primitive" components (e.g.,
     * "(()())(())" -> "(()())" and "(())"). We need to strip the outermost '(' and ')'
     * from each primitive block.
     * By keeping a running `count` (balance) of open parentheses, we can perfectly
     * identify the boundaries of these primitive blocks:
     * - The outermost '(' is always the one that changes the count from 0 to 1.
     * - The outermost ')' is always the one that drops the count from 1 to 0.
     * * * ⚙️ APPROACH (In-Place Two-Pointer):
     * Instead of creating a new string (which costs O(N) space), we use a `read`
     * pointer (`i`) and a `write` pointer (`idx`). We iterate through the string,
     * and if a character is NOT an outermost parenthesis, we write it to the `idx`
     * position and increment `idx`. Finally, we shrink the string to the new size.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N), where N is the length of the string. We iterate
     * through the string exactly once.
     * - Space Complexity: O(1) auxiliary space. We modify the original string
     * in-place without allocating any extra data structures (like a stack or new string).
     */
    string removeOuterParentheses(string s)
    {

        int N = s.length();

        int count = 0; // Tracks the balance of open/closed parentheses
        int idx = 0;   // The "write" pointer for in-place modification

        for (int i = 0; i < N; i++)
        {

            // Update the balance based on the current character
            if (s[i] == '(')
            {
                count++;
            }
            else if (s[i] == ')')
            {
                count--;
            }

            // CHECK FOR OUTERMOST PARENTHESES:
            // 1. (count == 1 && s[i] == '(') -> This is the very first '(' of a primitive block.
            // 2. (count == 0 && s[i] == ')') -> This is the very last ')' of a primitive block.
            if ((count == 1 && s[i] == '(') || (count == 0 && s[i] == ')'))
            {
                // It is an outermost parenthesis, so we skip it (do not write it)
                continue;
            }
            else
            {
                // It is an inner parenthesis, so we keep it by writing it to our current idx
                s[idx++] = s[i];
            }
        }

        // The string now contains the correct characters up to 'idx', but the tail
        // end still contains old garbage characters. We resize to chop off the tail.
        // As noted, in C++ std::string, s[idx] = '\0' doesn't automatically shrink the size property.
        s.resize(idx);

        return s;
    }
};

//-------------------------------------------------------------------------------
// 2. Title: Reverse Words in a String
//-------------------------------------------------------------------------------
class Solution
{
public:
    /**
     * @brief APPROACH 1: StringStream & Stack (The "C++ Idiomatic" Way)
     * * 🧠 INTUITION:
     * A Stack operates on a Last-In-First-Out (LIFO) principle, which naturally
     * reverses the order of elements. Furthermore, `std::stringstream` is a powerful
     * C++ utility that automatically tokenizes strings by spaces, entirely ignoring
     * leading, trailing, and multiple spaces for us.
     * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string.
     * - Space Complexity: O(N) to store the words in the stack and stringstream buffer.
     */
    string reverseWords(string s)
    {

        stack<string> st;

        // stringstream automatically handles all the messy space-parsing
        stringstream ss(s);
        string tmp;

        // Extract words one by one and push them onto the stack
        while (ss >> tmp)
        {
            st.push(tmp);
        }

        string ans = "";

        // Pop words off the stack to build the reversed string
        while (!st.empty())
        {

            // Add a space between words, but avoid adding a leading space
            if (!ans.empty())
            {
                ans.push_back(' ');
            }

            ans.append(st.top());
            st.pop();
        }

        return ans;
    }

    /**
     * @brief APPROACH 2: Manual Right-to-Left Parsing (The "Low-Level" Way)
     * * 🧠 INTUITION:
     * To avoid the memory overhead of a Stack and StringStream, we can parse the string
     * manually starting from the end (right side) and moving to the beginning (left side).
     * As we read characters from right to left, we build a word backwards. When we hit a
     * space, we know the word is finished, so we reverse it to its correct form and
     * append it to our final answer.
     * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N). We visit each character exactly once.
     * - Space Complexity: O(N) for the 'ans' and 'word' strings.
     */
    string reverseWords(string s)
    {

        int n = s.length();

        int si = 0;
        int ei = n - 1;

        // STEP 1: Manually trim leading spaces
        while (si < n && s[si] == ' ')
        {
            ++si;
        }

        // STEP 2: Manually trim trailing spaces
        while (ei >= 0 && s[ei] == ' ')
        {
            --ei;
        }

        string ans = "";
        string word = "";

        // Start reading from the last valid character
        int i = ei;

        // STEP 3: Traverse from Right to Left
        while (si <= i)
        {

            // If we hit a space, our current word is complete
            if (s[i] == ' ')
            {

                // Skip any extra multiple spaces between words
                while (si <= i && s[i] == ' ')
                {
                    --i;
                }

                // Because we read from right-to-left, the word is currently backwards.
                // Reverse it to fix it (e.g., "eulb" -> "blue")
                reverse(word.begin(), word.end());

                // Append space if it's not the first word
                if (!ans.empty())
                {
                    ans.push_back(' ');
                }

                // Add the fixed word to our answer and clear the buffer for the next word
                ans.append(word);
                word.clear();
            }
            else
            {
                // If it's a letter, add it to our temporary word buffer
                word.push_back(s[i]);
                --i;
            }
        }

        // STEP 4: Handle the very last word (which doesn't end with a space)
        if (!word.empty() && word != " ")
        {

            reverse(word.begin(), word.end());

            if (!ans.empty())
            {
                ans.push_back(' ');
            }
            ans.append(word);
        }

        return ans;
    }
};

//-------------------------------------------------------------------------------
// 3. Title: Largest Odd Number in String
//-------------------------------------------------------------------------------

class Solution
{
public:
    /**
     * @brief Finds the largest odd number that is a contiguous substring.
     * * * 🧠 INTUITION:
     * A number is odd if and only if its rightmost (least significant) digit is odd.
     * Because we want the *largest* possible odd number, we want to include as many
     * leading digits as possible. Therefore, the largest odd number will always be
     * the prefix of the string that ends exactly at the rightmost odd digit.
     * * * ⚙️ APPROACH (Greedy Right-to-Left Scan):
     * Instead of generating substrings (which would take O(N^2) time), we simply
     * scan the string backwards starting from the last character. The moment we find
     * an odd digit, we know that everything from index 0 up to this digit forms our
     * answer. We then truncate the string in-place to remove the trailing even digits.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N), where N is the length of the string. In the worst case
     * (e.g., all even numbers like "2468"), we scan the string exactly once.
     * - Space Complexity: O(1) auxiliary space. The string is truncated in-place
     * without allocating any new strings.
     */
    string largestOddNumber(string num)
    {

        int N = num.length();
        int oddIdx = -1;

        // STEP 1: Scan backwards to find the rightmost odd digit
        for (int i = N - 1; i >= 0; i--)
        {

            // Subtracting the ASCII value of '0' converts the char to its integer equivalent.
            // Example: '7' (ASCII 55) - '0' (ASCII 48) = integer 7.
            // 7 % 2 == 1, which means it is an odd number.
            if ((num[i] - '0') % 2 == 1)
            {
                oddIdx = i;
                break; // Stop immediately; we found the largest boundary!
            }
        }

        // STEP 2: Truncate and return
        if (oddIdx == -1)
        {
            // If we never updated oddIdx, the string only contains even numbers.
            return "";
        }
        else
        {
            // IN-PLACE TRUNCATION: Resize the string to cut off the trailing even digits.
            // We use oddIdx + 1 because resize() takes the desired length, not the index.
            num.resize(oddIdx + 1);
            return num;
        }
    }
};

//-------------------------------------------------------------------------------
// 4. Title: Longest Common Prefix in a String array
//-------------------------------------------------------------------------------
class Solution
{
public:
    //-----------------------------------
    // Approach: 1 : Horizontal scanning
    //-----------------------------------
    /**
     * @brief Finds the longest common prefix using Horizontal Scanning.
     * * Time Complexity: O(S) where S is the total number of characters in all strings.
     * Space Complexity: O(1) in-place modification.
     */
    string longestCommonPrefix(vector<string> &strs)
    {

        // Safety check for empty arrays
        if (strs.empty())
            return "";

        int n = strs.size();
        string ans = strs[0];

        for (int i = 1; i < n; ++i)
        {

            // Const reference to prevent expensive string copies
            const string &cur = strs[i];

            int j;
            for (j = 0; j < cur.length(); ++j)
            {

                // Stop if we reach the end of our current prefix, or find a mismatch
                if (j == ans.length() || ans[j] != cur[j])
                {
                    break;
                }
            }

            // Short-circuit: If the prefix is destroyed, stop checking the rest of the array!
            if (j == 0)
            {
                return "";
            }

            // IN-PLACE TRUNCATION: Zero memory allocation overhead!
            ans.resize(j);
        }

        return ans;
    }

    //----------------------------------------------
    // Approach: 2 : Vertical scanning [RECOMMENDED]
    //----------------------------------------------
    /**
     * @brief Finds the longest common prefix using Vertical Scanning.
     * * ⏱️ COMPLEXITY:
     * - Time: O(S) where S is the sum of all characters in all strings.
     * In the best case, it terminates exactly when the first mismatch occurs.
     * - Space: O(1) auxiliary space.
     */
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.empty())
            return "";

        // Iterate through the characters of the very first string
        for (int i = 0; i < strs[0].length(); ++i)
        {
            char currentChar = strs[0][i];

            // Check this exact column (index 'i') across all other strings
            for (int j = 1; j < strs.size(); ++j)
            {

                // If we hit a mismatch, OR if a shorter string just ended,
                // we have found the boundary of our prefix!
                if (i == strs[j].length() || strs[j][i] != currentChar)
                {
                    return strs[0].substr(0, i);
                }
            }
        }

        // If we made it through the entire first string without returning,
        // then the entire first string is the common prefix.
        return strs[0];
    }
};

//-------------------------------------------------------------------------------
// 5. Title: Isomorphic Strings
//-------------------------------------------------------------------------------

class Solution
{
public:
    //-----------------------------------
    // Approach: 1 : Using Map [Slower]
    //-----------------------------------
    /**
     * @brief Determines if two strings are isomorphic using a Map & Set combination.
     * * * 🧠 IDEA & INTUITION:
     * Two strings are isomorphic if there is a strict 1-to-1 mapping (bijection)
     * between their characters.
     * - We need a Dictionary (Map) to enforce the forward rule: If 'a' maps to 'x' once,
     * it must ALWAYS map to 'x'.
     * - We need a Tracker (Set) to enforce the reverse rule: If 'x' is already claimed
     * by 'a', no other letter (like 'b') is allowed to map to 'x'.
     * Using a Set for the reverse rule is highly optimized because we only care about
     * EXISTENCE ("Is this taken?"), not mapping ("Who took it?").
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string. Hash map and hash set
     * lookups take O(1) time on average.
     * - Space Complexity: O(1) auxiliary space. The map and set store ASCII characters.
     * Since there are only 256 unique ASCII characters, the memory used will never exceed
     * a constant boundary of 256, regardless of how long the input string is.
     */
    bool isIsomorphic(string s, string t)
    {

        // Strings of different lengths cannot have a 1-to-1 mapping
        if (s.length() != t.length())
            return false;

        // Tracks the forward mapping: S -> T
        unordered_map<char, char> mapStoT;

        // Tracks which characters in T have already been claimed
        unordered_set<char> claimedT;

        for (int i = 0; i < s.length(); ++i)
        {
            char charS = s[i];
            char charT = t[i];

            // SCENARIO 1: 'charS' has been seen before
            if (mapStoT.find(charS) != mapStoT.end())
            {

                // If it maps to a DIFFERENT character now, the mapping is broken
                if (mapStoT[charS] != charT)
                {
                    return false;
                }
            }
            // SCENARIO 2: 'charS' is a completely new character
            else
            {

                // Since 'charS' wants to map to 'charT', we must first check if
                // 'charT' has already been claimed by a different character.
                if (claimedT.find(charT) != claimedT.end())
                {
                    return false;
                }

                // Both are free! Create the mapping and mark 'charT' as taken.
                mapStoT[charS] = charT;
                claimedT.insert(charT);
            }
        }

        // If we processed the entire string without conflicts, they are isomorphic
        return true;
    }

    //------------------------------------
    // Approach: 2 : Using Array [OPTIMAL]
    //------------------------------------
    /**
     * @brief Determines if two strings are isomorphic using fixed ASCII arrays.
     * * * 🧠 IDEA & INTUITION:
     * Instead of mapping Character -> Character, we map Character -> Last Seen Index.
     * If two strings are isomorphic, the characters at the current position must have
     * been seen at the exact same time in the past.
     * For example, in s="egg" and t="add":
     * - 'g' was last seen at index 1.
     * - 'd' was last seen at index 1.
     * They match! We update both of their "last seen" records to index 2.
     * * * 💡 THE "+1" TRICK:
     * We initialize our arrays with 0 to mean "Unmapped". Therefore, when we record
     * an index, we must store `i + 1`. If we stored `i` (0), the code would confuse
     * the 0th index with the default "Unmapped" state.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string.
     * - Space Complexity: O(1) Absolute space. We use exactly two arrays of 256 integers
     * (2048 bytes total). This memory footprint never changes, whether the string
     * is 10 characters or 10 million characters long.
     */
    bool isIsomorphic(string s, string t)
    {

        // Strings of different lengths can never be isomorphic
        if (s.length() != t.length())
            return false;

        // Two arrays of size 256 (for all ASCII characters), initialized to 0
        int mapStoT[256] = {0};
        int mapTtoS[256] = {0};

        for (int i = 0; i < s.length(); ++i)
        {

            // In C++, chars are automatically implicitly cast to integers
            // when used as array indices.
            char charS = s[i];
            char charT = t[i];

            // If their "last seen" timestamps don't match, the bijection is broken.
            if (mapStoT[charS] != mapTtoS[charT])
            {
                return false;
            }

            // Update their timestamps to the current index + 1 (to avoid the 0 conflict)
            mapStoT[charS] = i + 1;
            mapTtoS[charT] = i + 1;
        }

        return true;
    }
};

//-------------------------------------------------------------------------------
// 6. Title: Rotate String
//-------------------------------------------------------------------------------
class Solution
{
public:
    //-----------------------------------
    // Approach: 1 : Brute force [Slow]
    //-----------------------------------
    //  // Time: O(N^2)
    //  // Space: O(1)
    bool rotateString(string s, string goal)
    {

        int N = s.length();
        int M = goal.length();

        if (N != M)
            return false;

        for (int i = 0; i < N; i++)
        {
            int d = i;
            string shiftedStr = s.substr(d, (N - d)) + s.substr(0, d);

            if (goal == shiftedStr)
                return true;
        }

        return false;
    }

    //--------------------------------------
    // Approach: 2 : Concatenation [OPTIMAL]
    //--------------------------------------
    /**
     * @brief Determines if string 's' can be rotated to match string 'goal'.
     * * * * 🧠 IDEA & INTUITION:
     * A "rotation" moves the leftmost characters to the rightmost positions.
     * If we take a string `s` and concatenate it with itself (`s + s`), the
     * resulting doubled string will mathematically contain EVERY possible
     * valid rotation of `s` as a contiguous substring.
     * * Example: s = "abcde"
     * Doubled: "abcdeabcde"
     * Rotations hidden inside: [abcde], a[bcdea], ab[cdeab], abc[deabc], etc.
     * * Therefore, to check if 'goal' is a valid rotation, we just need to verify
     * two things:
     * 1. They are the exact same length.
     * 2. 'goal' exists anywhere inside `s + s`.
     * * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N), where N is the length of the string.
     * Concatenating `s + s` takes O(N) time. Modern C++ standard libraries
     * implement substring search (`contains` or `find`) in O(N) average time.
     * - Space Complexity: O(N) auxiliary space. We must allocate memory to store
     * the new concatenated string `ns` which is 2N in length.
     */
    bool rotateString(string s, string goal)
    {

        // 1. Length check is mandatory. If lengths differ, rotation is impossible.
        if (s.length() != goal.length())
        {
            return false;
        }

        // 2. The doubling trick: generate all possible rotations in one string
        string ns = s + s;

        // 3. Search for 'goal' inside the doubled string.

        // NOTE: Using C++23 'contains' for peak readability.
        // return ns.contains(goal);

        // NOTE: For older codebases (C++20 or older), the standard is:
        return ns.find(goal) != string::npos;
    }
};

//-------------------------------------------------------------------------------
// 7. Title: Valid Anagram
//-------------------------------------------------------------------------------
class Solution
{
public:
    //--------------------------------------------------
    // Approach: 1 : Using Array for 256 ASCII [OPTIMAL]
    //--------------------------------------------------
    /**
     * @brief Determines if t is an anagram of s using Early-Exit Frequency Counting.
     * * * 🧠 INTUITION & OPTIMIZATION:
     * We use a single 26-bucket array. We populate it with string 's'.
     * Then, we drain it with string 't'.
     * THE TRICK: Because we already know 's' and 't' are the same length, if 't'
     * ever tries to drain a bucket below 0, it means 't' has more of that specific
     * letter than 's' does. If that happens, they cannot be anagrams, and we can
     * abort the function immediately! No final loop required.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N). Best case scenario, it aborts almost instantly
     * during the second loop.
     * - Space Complexity: O(1). Exactly 26 integers allocated.
     */
    bool isAnagram(string s, string t)
    {

        // 1. Length check (This makes the < 0 early-exit mathematically safe!)
        if (s.length() != t.length())
        {
            return false;
        }

        // 2. Strict constraint matching: 26 lowercase English letters
        int mapS[26] = {0};

        // 3. Populate the buckets with string 's'
        for (char c : s)
        {
            ++mapS[c - 'a'];
        }

        // 4. Drain the buckets with string 't'
        for (char c : t)
        {
            --mapS[c - 'a'];

            // 5. THE EARLY EXIT: If 't' demands more of a letter than 's' had, fail instantly.
            if (mapS[c - 'a'] < 0)
            {
                return false;
            }
        }

        return true;
    }

    //-------------------------------------------
    // Approach: 2 : Using Map for Unicode [Slow]
    //-------------------------------------------
    /**
     * @brief Determines if 't' is an anagram of 's' using a Hash Map.
     * * * 🧠 INTUITION & APPROACH:
     * To be an anagram, both strings must have the exact same characters with the
     * exact same frequencies. We can track this using a "bucket balance" system:
     * 1. Add characters from string 's' into the map (incrementing the count).
     * 2. Remove characters from string 't' from the map (decrementing the count).
     * 3. If they are perfect anagrams, every single key in the map will perfectly
     * balance back out to exactly 0.
     * * * 💡 WHY A MAP?
     * Unlike a fixed-size array (which only works if we know the character set is
     * small, like 26 English letters), an `unordered_map` dynamically allocates memory.
     * This makes this specific method robust enough to handle millions of unique
     * Unicode characters.
     * * * ⏱️ COMPLEXITY:
     * - Time Complexity: O(N) where N is the length of the string. We loop through
     * both strings once. Hash map insertions/lookups take O(1) time on average.
     * - Space Complexity: O(U) where U is the number of unique characters in the strings.
     */
    bool isAnagram(string s, string t)
    {

        int n = s.length();
        int m = t.length();

        // 1. If lengths differ, they mathematically cannot be anagrams
        if (n != m)
            return false;

        // Tracks the frequency of each character (implicitly casting char to int)
        unordered_map<int, int> mp;

        // 2. Populate the frequency map using string 's' ( O(N) Time )
        for (int i = 0; i < n; i++)
        {
            mp[s[i]]++;
        }

        // 3. Deplete the frequency map using string 't' ( O(N) Time )
        for (int i = 0; i < n; i++)
        {
            mp[t[i]]--;
        }

        // 4. Verify the balance. If any character frequency isn't exactly 0,
        // they are not perfect anagrams. ( O(U) Time )
        auto it = mp.begin();
        while (it != mp.end())
        {
            if (it->second != 0)
                return false;
            it++;
        }

        return true;
    }
};

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // Ignore trailing newline character

    while (t--)
    {
        string input;
        getline(cin, input);

        int m, n;
        cin >> m >> n;

        vector<vector<int>> matrix(m, vector<int>(n));

        // Read the matrix
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> matrix[i][j];
            }
        }

        Solution ob;
        // cout << ob.removeOuterParentheses(input) << " ";
        //  cout<< ob.reverseWords(input)<<" ";
        //  cout<< ob.isIsomorphic(input1,input2);
        cout << endl;
    }
    return 0;
}