# Points to note

1. We must be careful that we will not manipulate the given data. A company may use the same data for different purposes. So, we will never manipulate the given data i.e. the inputs until the interviewer specifically says so.

2.  In CP or in the platforms like Leetcode and GeeksforGeeks, we generally run our codes on online servers. Most of these servers execute roughly **10<sup>8</sup>** (i.e. 1 crore) operations in approximately **1_second** i.e. 1s. 

     - We must be careful that if the time limit is given as **2s** the operations in our code must be roughly **2 * 10<sup>8</sup>**, not 10<sup>16</sup>. 
     
     - Simply, if we want our code to be run in **1s**, the time complexity of our code must be around **O(10<sup>8</sup>)** avoiding the constants and the lower values.

3. 10<sup>8</sup> operations take 1 second to get executed. So, 10<sup>10</sup> operations will take around 100 seconds(10<sup>10</sup>/10<sup>8</sup>). Code will get TLE if it takes 100 seconds to get executed.

4. C++ `Data-types` ref: https://www.programiz.com/cpp-programming/data-types

5. **Switch statementsS:** 

    A switch statement necessitates that its expression results in a **constant** value. This can include constants and arithmetic operations. 

    Ensure that the expression provides values of type `int` or `char` or `enum`. Switch statements in *C* or *C++* are exclusively designed to handle integer, character or enum values only.
 
6. The rate at which the time, required to run a code, changes with respect to the input size, is considered the time complexity. Time complexity of a particular code depends on the given input size, not on the machine used to run the code.

    ![Time complexity](./img/time_complexity.png)

7. <span style="color: violet; font-size: 18px;">**Libraries:**</span>
     - **#include <bits/stdc++.h> :** Includes all popular library at once. But not available in all compilers.
     - `std::swap()` : swaps 2 pointers in the argument
     - `#include<climits>` : INT_MAX, INT_MIN
     - For long long use: `LLONG_MAX` and `LLONG_MIN`.
     - in c++ to get absolute value:
          ```cpp
               #include <cstdlib> // For int abs()
               #include <cmath>   // For float/double/long double

               int main() {
                    int int_num = -10;
                    double double_num = -5.5;

                    int abs_int = std::abs(int_num);

                    double abs_double = std::abs(double_num);
               }
          ```
     - **std::queue**

          **Concept:**  
          `std::queue` is a container adaptor that provides a First-In, First-Out (FIFO) behavior, similar to a real-world queue or line.

          **Operations:**  
          It offers a limited set of operations:
          - `push()`: Adds an element to the back (enqueue).
          - `pop()`: Removes an element from the front (dequeue).
          - `front()`: Accesses the front element without removing it.
          - `back()`: Accesses the back element without removing it.
          - `empty()`: Checks if the queue is empty.
          - `size()`: Returns the number of elements.

          **Underlying Container:**  
          By default, `std::queue` uses `std::deque` as its underlying container, but it can also be adapted to use `std::list` or `std::vector` (with some limitations for `std::vector`).

          **Purpose:**  
          Ideal for scenarios where strict FIFO order is required and direct access or manipulation of elements other than at the ends is not needed.
     
     - **std::deque**

       **Concept:**  
       `std::deque` (double-ended queue) is a sequence container that allows efficient insertion and deletion of elements at both the front and the back.

       **Operations:**  
       It provides a richer set of operations compared to `std::queue`:
       - `push_front()`, `push_back()`: Adds elements to the front or back.
       - `pop_front()`, `pop_back()`: Removes elements from the front or back.
       - `front()`, `back()`: Accesses elements at the ends.
       - `operator[]`, `at()`: Allows random access to elements by index, similar to `std::vector`.
       - `insert()`, `erase()`: Allows insertion and deletion at arbitrary positions (though less efficient than at the ends).
       - `empty()`, `size()`: Checks if the deque is empty and returns the number of elements.

       **Underlying Implementation:**  
       `std::deque` is typically implemented as a collection of fixed-size blocks of memory, providing efficient growth and contraction at both ends while also enabling random access.

       **Purpose:**  
       Suitable when you need a dynamic array-like structure that requires efficient insertions/deletions at both ends and potentially random access to elements.

     - In c++ use random number:
          ```cpp
               #include<cstdlib> // for rand() and srand()
               #include<ctime>  // for time()

               int main(){
                    srand(time(0)); // Seed the random number generator
                                   // w/o this get same sequence each run
                    int randomInt = rand(); // Random number between 0 and RAND_MAX where RAND_MAX= 32k.
                    int range = 100;
                    int boundInt = randomInt % range; // Random number between 0 and 99
               }
          ```
     - In c++ how to erase map entry while traversing:
          ```cpp
               for (auto it = myMap.begin(); it != myMap.end(); ) {
                    if (it->second == 0) {
                         it = myMap.erase(it); // erase and move to next
                    } else {
                         ++it;
                    }
               }
          ```
     - In c++ map to check two consecutive keys in a map while iterating:
          ```cpp
               for (auto it = mp.begin(); it != mp.end(); ++it) {
                    auto nextIt = next(it);  // gives the nest iterator

                    if (nextIt == mp.end()) break;     // safety check

                    if ((nextIt->first - it->first) != 1)
                         return false;
               }
          ```
     - When you declare: ```cpp priority_queue<pair<int, int>> maxHeap;``` It compares pair<int, int> based on lexicographical order. First by .first. If .first is equal, then by .second
     - How to use tuples in c++:
     ```cpp
          // C++17: structured bindings:
          tuple<int, string, double> person = {25, "Alice", 5.9};
          auto [age, name, height] = person;
          cout << "Name: " << name << ", Age: " << age << ", Height: " << height << endl;

          // Earlier C++ (C++11 / C++14):
          tuple<int, string, double> person = make_tuple(25, "Alice", 5.9);
          int age = get<0>(person);
          string name = get<1>(person);
          double height = get<2>(person);
          cout << "Name: " << name << ", Age: " << age << ", Height: " << height << endl;
     ```
     - Initializing array filled with default values: int hash[13] = {0};
     - To print as Booleans:
          ```c
               cout << std::boolalpha; 
               cout << true << endl;
               cout << std::noboolalpha;
          ```
     - To find max element in an array: {    int maxE= *max_element(arr.begin(),arr.end());   }
     - To create heap from array in O(N):
          ```cpp
               #include <algorithm>
               std::make_heap(arr.begin(), arr.end());
          ```
     - c++ priority_queue by default is max heap:
          ```cpp
               #include <queue>
               std::priority_queue<int> pq;
               // Add elements to the priority queue
               pq.push(30);
               pq.push(100);

               // Remove elements from the priority queue
               while (!pq.empty()) {
                    std::cout << "Popping: " << pq.top() << std::endl;
                    pq.pop();
               }
          ```
     -  To use it as min_heap:
          ```cpp
               #include <queue>
               std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
               minHeap.push(30);
               minHeap.push(10);
               minHeap.push(50);
               minHeap.push(20);

               while (!minHeap.empty()) {
                    std::cout << minHeap.top() << " ";
                    minHeap.pop();
               }
          ```
     - To write **exponent** like 10^-6:
          ```c
               double diff = 1e-6;
          ```
     - proper alternative for (l+r)/2 :
          ```c
          int mid = l + (r - l) / 2;
          ```
          or
          ```c
          int mid = r - (r - l) / 2;
          ```

     > NOTE: While using ceil DO NOT FORGET to cast to double: ceil((`double`)N / 2);

 
   - If you want to pass always the longer array into the 1st argument, just check which one is longer and swap arguments based upon that: 
     ```c
     if (m > n)
            return findMedianSortedArrays(nums2, nums1);
     ```
   - To initialize data structures in Constructor init:
     ```cpp
          vector<int> heap;
          int size;

          minHeap(): heap(vector<int>()) {
               size = 0;
          }

          minHeap(int capacity): heap(vector<int>(capacity)) {
               size = 0;
          }
     ```
   - The C++ Standard Library provides the std::swap() function (from the <utility> header):
     ```cpp
          #include <utility> // Required for std::swap
          // Swap using std::swap()
          std::swap(arr[index1], arr[index2]);
     ```
   - Comparison between `struct` and `class` in c++: 

     | Feature                      | `struct`                    | `class`                  |
     | ---------------------------- | --------------------------- | ------------------------ |
     | Default access               | `public`                    | `private`                |
     | Default inheritance          | `public`                    | `private`                |
     | Functions, inheritance, etc. | ✅ Supported                | ✅ Supported             |
     | Style convention             | C-style or simple POD types | Full-fledged OOP classes |
     |  When to Use?                | You want everything public  | building full OOP components |
     -  Historical Background:
          - In `C`, struct could only contain `data` (no `functions`).
          - `C++` extended `struct` to support full object-oriented features.
          - `class` was introduced to emphasize `encapsulation` and `access control`.
   - 📝 When to Use `new` in C++

          ✅ Use stack (e.g., DTO dto;) when:
          - Object is local to the function.
          - No need for manual memory management.
          - Cleaner and auto destroyed.

          ❌ Use `new` (e.g., DTO* dto = new DTO();) only if:
          - You need the object beyond current scope.
          - You're storing pointers in a data structure.
          - Polymorphism or dynamic lifetime needed.

          💡 Your code is correct:
          - Stack use is cleaner and safer.
          - No need for `new` since object is used and returned locally.
   - Efficient way to merge a `string` and a `vector<string>` into `vector<vector<string>>`:
     - **Problem:**  
       Given a `string name` and a `vector<string> emails`, insert them together into a `vector<vector<string>> ans` in the form:  
          ```cpp
       { name, email1, email2, ... }
          ``` 
     - **Approach:**  
          ```cpp
          vector<string> entry;
          entry.push_back(name);                                    // add name
          entry.insert(entry.end(), emails.begin(), emails.end());  // append all emails
          ans.push_back(move(entry));                               // move into ans
          ```
       - **push_back** → adds single element at end.  
       - **insert** → appends a range of elements (like extend).  
       - **move** → transfers ownership, avoids deep copy.  
     - **Result in `ans`:**  
          ```cpp
          { name, email1, email2, ... }
          ```
   - z
   - x
   - y

---
<span style="color: violet; font-size: 18px;">**Miscs:**</span>

1. Array size limitations: 
     ![Max array size we can initialize with](./img/max_array_size.png)
     
2.  If the string contains both uppercase and lowercase letters: We have 256 characters in total in this case. So, we will create a hash array of size **256**. Otherwise we can use hash[s[i]-’a’] OR hash[s[i]-’A’] and keep the hash array of 26 elements only.

3.  In the map data structure, the data type of key can be anything like int, double, pair<int, int>, etc. But for unordered_map the data type is limited to integer, double, string, etc. We cannot have an unordered_map whose key is pair<int, int>. 

4.  How to traverse map from end to start?
     Ans: 

     ```c++
          for(auto it=freq.rbegin(); it!=freq.rend(); it++){
            cout<<it->first<<endl;
          }
     ```

5.  XOR properties:
     - XOR of two same numbers is always 0 i.e. a ^ a = 0. ←Property 1.
     - XOR of a number with 0 will result in the number itself i.e. 0 ^ a = a.  ←Property 2

6.  Sub-array vs sub-sequence:
    - A subarray is a **contiguous** (consecutive) portion of an array.
    - A subsequence is a sequence of elements derived from the original array by deleting some elements **without changing the order** of the remaining elements.

7.  When input array is given as sorted, then try to use Binary search.
8.  When we have to find the <b>minimum</b> number which is greater than or equal to something, try to use Binary search. And vice-versa for largest number less than equals to something. And also perform the binary search on the range of that asked value only from its min to max range.
9.  How to rotate an array or a string? (`O(N)`)
     - Use built-in function rotate(first,middle, last) where
       - first: fist iterator in the range of elements to rotate
       - last: last iterator in the range of elements to rotate
       - middle: Iterator pointing to the element that should apprear at the begining of the rotated range
     - Example to left-rotate a string ("abcde") by 3 positions. Output: "deabc"
     ```cpp
          string s = "abcde";
          int d=3;
          rotate(s.begin(), (s.begin()+d) , s.end());
          cout<<s<<endl;
     ```
     - Example to right-rotate a string ("abcde") by 3 positions. Output: "cdeab"
     
     ```cpp
          string s = "abcde";
          int d=3;  int N=s.length();
          rotate(s.begin(), (s.begin()+(N-d)) , s.end());
          cout<<s<<endl;
     ```

10. string substr (size_t pos = 0, size_t len = npos) const;
     - pos: Position of the first character to be copied as a substring.
     - len: Number of characters to include in the substring
     - Example: 
     ```cpp
          // left rotate by i places each at a time
          // abcde -> bcdea -> cdeab -> deabc -> eabcd -> abcde
          for(int i=0; i<N; i++){
            int d = i;
            string leftShiftedStr = s.substr(d,(N-d)) + s.substr(0, d);
            cout<<leftShiftedStr;
          }

          // Right rotate by i places each at a time
          // abcde -> eabcd -> deabc -> cdeab -> bcdea -> abcde
          for(int i=0; i<N; i++){
            int d = i;
            string rightShiftedStr = s.substr(N-d, d) + s.substr(0, (N-d));
            cout<<rightShiftedStr;
          }
     ```

11.  DO NOT concat strings in loops with '`+`' operator as each time it creates new string. Instead use **append()** or **push_back()** and **pop_back()** methods:
     ```cpp
          string ans;
          for(int i=255; i>=0; i--){
               int frequency = freq[i].first;
               char thisChar = freq[i].second;
               ans.append(frequency,thisChar);  // Appends char N times
          }
     ```
     OR
     ```cpp
          s.push_back('0');
          findStringsRecursively(s);
          s.pop_back();
     ```
     - To insert before the current string use `insert()`:
     ```cpp
          int N = s.size();
          string ans="";
          ans.reserve(N);     // **Pre reserve the size of string.

          stringstream ss(s);
          string inp;

          while(ss >> inp){
            if(ans=="") ans=inp;
            else {ans.insert(0," "); ans.insert(0,inp);}    // Use insert
          }
     ```

12. DO NOT pass strings **w/o** reference operator in method call from inside a loop. It creates new stirng in each method call and will give space limit reached error. Pass like below:
     ```cpp
          bool isPal(string& str){
               cout<< str[s];          
          }

          // Calling the above method
          string s = "madam";
	     cout<<isPal(s);
     ```
     - Also instead of saving strings in each iteration, try to save the index. Ex:
     ```cpp
          for(int i=0; i<N; i++){
            for(int j=i; j<N; j++){
                if(isPal(s,i,j)){
                    if((j-i+1)>maxLen){
                        maxLen = j-i+1;
                        ansL = i;  // instead of doing ans = s.substr(i, j-i+1) here
                        ansR = j;  // save the index
                    }
                }
            }
        }

        return s.substr(ansL, ansR-ansL+1);
     ```

13. How to detect integer overflow using only int variable? Below code is the answer:
    ```cpp
    bool isOverflow = (ans>INT_MAX/10) || (ans==INT_MAX/10 && curDigit>7);
    ```   

14. Note: c++ string method to check digit is: `isdigit(s[i])` not isDigit.
15. Note: In c++ string checking s[i] == NULL (or '\0') won’t work reliably to detect the end of the string. Correct usage: `if (i == s.length()) return;` where i is 0 based index over string chars.
16. Below is an example of how to use **Lambda xfunctions** in c++:

     > Note: Below `quickmul` is the labmda function which is using var `mod` from class attributes. [Ref: https://leetcode.com/problems/count-good-numbers/]

     ```cpp
          class Solution {
          private:
               static constexpr int mod = 1000000007;

          public:
               int countGoodNumbers(long long n) {

                    // use fast exponentiation to calculate x^y % mod
                    auto quickmul = [](int x, long long y) -> int {
                         int ret = 1, mul = x;
                         while (y > 0) {
                              if (y % 2 == 1) {
                                   ret = (long long)ret * mul % mod;
                              }
                              mul = (long long)mul * mul % mod;
                              y /= 2;
                         }
                         return ret;
                    };

                    return (long long)quickmul(5, (n + 1) / 2) * quickmul(4, n / 2) % mod;
               }
          };
     ```

17. Temporarily removes each element from set s, processes the rest via funcA, then restores the removed element safely.  
     ```cpp
          for (auto it = s.begin(); it != s.end(); ) {
               int val = *it;
               it++;                // Move iterator forward first
               s.erase(val);        // Temporarily remove the element

               funcA(s);            // Do something with the modified set

               s.insert(val);       // Re-insert the removed element
          }
     ```

18. For questions like printing *combinations* or *subsequences*, the first thing that should strike your mind is **recursion**.
Whenever the problem is related to picking up elements from an array to form a combination, start thinking about the “pick and non-pick” approach.
1.   Below is a way to get the next valid index while traversing a 2-D matrix:
     ```cpp
               int curFlatIndex = curRowIdx * N + curColIdx; // Flatten to 1D index
               curFlatIndex++;                       // Move to next
               int nextRowIdx = curFlatIndex / totalCols;
               int nextColIdx = curFlatIndex % totalCols;
     ```
     OR

     ```cpp
          // Compute next cell's indices for 2D matrix
          int nextRowIdx = (curColIdx == N - 1) ? (curRowIdx + 1) : curRowIdx;
          int nextColIdx = (curColIdx == N - 1) ? 0 : (curColIdx + 1);
     ```

2.   A often big mistake is attempting tp *break* recursive loops with break, which is not possible. The way out is either *flag*, *goto* or *method* call. goto example:

     ```cpp
          for(int i=0; i<N; i++){
               for(int j=0; j<N; j++){
                    if(board[i][j] == '.'){
                         goto endLoop;  // breaks to loops together
                    }
               }
          }
          endLoop:;
     ```
3.   Way to iterate over a **m*m** sub-matrix inside a **N*N** matrix:

    <img src="img/sudoku.png" alt="alt text" style="display: block; margin: auto; width: 250px;">

    ```cpp
          int matrixSize = N;
          int subMatrixSize = sqrt(matrixSize);

          // Iterates over the same sub-matrix as curRow-curCol cell belongs to
          for (int k = 0; k < N; k++)
          {
               int subMatrixStartRow = subMatrixSize * (curRowIdx / subMatrixSize);
               int subMatrixStartCol = subMatrixSize * (curColIdx / subMatrixSize);

               int subMatrixRowIdx =  subMatrixStartRow + ( k / subMatrixSize );
               int subMatrixColIdx =  subMatrixStartCol + ( k % subMatrixSize );

               if (board[subMatrixRowIdx][subMatrixColIdx] == curCellChar)
                    return false;
          }
    ```
4.   How to push back and pop back a **string** to a **string**?
     ```cpp
          string cur = "test";
          size_t oldSize = expression.size();
          expression.append(cur);
          expression.resize(oldSize);
     ```
5.   How to push back and pop back a **char** to a **string**?
     ```cpp
          char cur = 'x';
          expression.push_back(cur);
          expression.pop_back();
     ```
6.  Convert char/string to int and vice-versa: 
     ```cpp 
          int c =  'x' - 'a';
     ```
     Convert digit to char:
     ```cpp 
          char dig =  5 + '0';
     ```
     Convert number to string of digits:
     ```cpp 
          #include <string>
          int num = 245;
          string num =  to_string(num);
     ```
     Convert string of digits to num:
     ```cpp
          #include <string>
          string str_num = "123";
          int num = stoi(str_num);
     ```
7.  How to parse comma:
    ```cpp
          stringstream ss(data);
          string s;
          // here ',' seperator is used
          while (getline(ss, s, ',')) {
               cout << s << endl;
          }
     ```
8.  Floor and Ceil:
  - Floor of a x is the greatest integer less than or equal to x.
  - Ceil of x is the least integer greater than or equal to x.
---
<span style="color: violet; font-size: 18px;">**Bit manipulation:**</span>

1.  -ve numbers are stored as 2's complement format.
2.  Not(~) operator: 
     ```cpp
          int x = 6; // originally stored as 32 bits: 0000 .. 0000 0110 
          cout<< ~(x)<< endl; // After negetaion:   [1]111 .. 1111 1001
                              // becomes -ve
                              // So interpreted as 2's completed
                              // [1]111 .. 1111 1001->[1]000 .. 0000 0110
                              //                                     +1
                              //                      -------------------
                              //                   -> [1]000 .. 0000 0111->-7



          int y = -6; // originally stored as 32 bits: 1111 .. 1111 1010
                    // After negetaion:              0000 .. 0000 0101->+5

          cout<< ~(y) << endl;
     ```
34. Xor of consecutive numbers starting from 1 shows cyclic behaviour:
     <img src="img/xor-in-given-range.png" alt="xor-in-given-range" style="display: block; margin: auto; width: 250px;">

---
<span style="color: violet; font-size: 18px;">**Miscs continues:**</span>


1.  In c, once array is passed through method calling, then it is becomes a pointer and it's size can not be calculated with sizeof() op.
    ```c
          void reverse(char arr[]){
          // int len = sizeof(arr)/sizeof(arr[0]); // Wrong because arr is a pointer here, and sizeof(arr) returns size of pointer i.e. 4 or 8 always. 
          int len = strlen(arr); // correct
          }
    ```
2.  Convert char to string in-line:
     ```cpp  
          stack<string> st; // stack of string
          for (char c : postfix) {
               if (isalnum(c)) {
                    st.push(string(1, c));   // convert char to string in-line
               }
          }
     ```
3.  Best waysto declare a 2D vector in C++:
    ```cpp
          vector<vector<int>> matrix(M, vector<int>(N, initial_value));
     ```
4.  Whenever we need `greatest` or `smallest` elements in linear time complexity, think of using `Monotonic stack`.

---
<span style="color: violet; font-size: 18px;">**Binary tree:**</span>

39. Theory of BT:
    - Links:
      - [TUF theory blog](https://takeuforward.org/binary-tree/introduction-to-trees/)
      - [TUF+ theory blog](https://takeuforward.org/plus/dsa/binary-trees/theory-and-traversals/introduction-)
      - [Binary Tree Representation in C++](https://takeuforward.org/binary-tree/binary-tree-representation-in-c/)
      - [Tree traversals](https://takeuforward.org/binary-tree/binary-tree-traversal-inorder-preorder-postorder/)
    - *Full/Strict Binary Tree*: 
      - every node has either 0 or 2 children — no node has only one child, no matter how the tree is growing. 
      - contributes significantly to the tree’s balance, making traversal, searching, and insertion options more predictable and efficient.
    - *Complete binary tree*: 
       -  All levels are completely filled, all internal nodes having 2 children except possibly the last.
       -  The last level is filled from left to right, with no gaps.
       -  aids in achieving balanced structures, making it easier to implement algorithms and ensuring reasonably consistent performance.
       -  useful for storing data in structures like heaps
       -  at level h, #nodes = 2^h
    - *Almost complete binary tree*: 
        - The term "Almost Complete" is not strictly standardized
        - A tree that's very close to being complete, but may have small deviations.
    - *Perfect binary tree*: 
       -  Every level is completely filled.
       -  Every internal node (non-leaf node) has exactly two children
       -  all leaf nodes are at the same level.
       -  0-indexed Height = h, number of nodes = 2^(h+1) - 1  
    - *Balanced Binary Tree*: 
       -  height difference between the left and right subtrees of every node is at most 1.
       -  `abs(height(left subtree) - height(right subtree)) <= 1`
       - O(log n) max height
       -  Efficient operations like search, insert, delete in AVL/Red-Black/BSTs.
    - *Degenerate Tree*:
       -  each parent node has only one child.
       -  This makes the tree essentially behave like a linked list.
       -  tree is called skewed
       -  max height O(n)
    - Diameter of tree: Length of the longest path (every node can be traversed only once) between any two nodes in the tree. It may or may not pass through the root.
    - LCA: Lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).
    - 

---

<span style="color: violet; font-size: 18px;">**Binary search tree:**</span>

1. Link: 
   - [TUF+ theory](https://takeuforward.org/plus/dsa/problems/introduction-to-bst)
   - [TUF theory](https://takeuforward.org/binary-search-tree/introduction-to-binary-search-trees/) 
2. Whst is BST?
  -  Each node in a BST follows the binary tree property: having at most two children.
  -  The left child of a node holds values less than the node’s value, while the right child holds values greater than the node’s value. 
  -  (Left Child < Node < Right Child)
  -  Each subtree of a BST is also a BST. This means that every node in the left subtree is less than the root node, and every node in the right subtree is greater.
  -  Typically Binary Search Trees, duplicate node values are not permitted. If allowed then 
     -  either frequency is maintained per node
     -  or (Left Child <= Node < Right Child)
  -  Balanced Variants of BST
     -  AVL Tree: : A self-balancing BST where the height difference between left and right subtrees (balance factor) of any node is at most 1.
     -  Red-Black Tree:: A self-balancing BST where each node has an extra bit for color (red or black).
  -  Practical Applications
     -  Database Indexing: quickly locate records based on keys.
     -  Symbol Tables: Used in compilers 
     -  Memory Management: Implementing data structures like heaps
  -  `In-order` traversal of BST always gives elements in `sorted` order.
  -  

---
<span style="color: violet; font-size: 18px;">**Heap:**</span>


1.  In c++ **priority queue** is the implementation of **heap**. By default it creates *max* heap. Example:
    ```cpp
          #include <queue>

          priority_queue<int> max_heap; // Default: max heap
          max_heap.push(10);
          max_heap.push(5);
          max_heap.push(20);
          cout << "Max heap top: " << max_heap.top() << endl; // Output: 20
    ```
    ```cpp
          #include <queue>
          #include <functional> // For std::greater

          // Min heap: specify std::greater<int> as the comparator
          priority_queue<int, vector<int>, greater<int>> min_heap; 
          min_heap.push(10);
          min_heap.push(5);
          min_heap.push(20);
          cout << "Min heap top: " << min_heap.top() << endl; // Output: 5
    ```
2.  Heap Theory:
    1.  Priority queue is basically *almost complete binary tree* where all operations take time **O(Log N)**
    2.  Heap is stored in form of *Array*.
    3.  For 0-based indexing for element `i`
        -   left child is at: `2*i +1`
        -   right child is at: `2*i +2`
        -   Parent is at: `ceil( (float)i /2) - 1`; Correct version: `(i-1)/2`
        -   #total nodes = #internal nodes + #leaf nodes
        -   For Complete Binary tree: 
            -   #leaf nodes = #internal nodes + 1;
        -   For Almost complete Binary tree:
            -   Leaf nodes lie from `(N/2)` to `(N-1)`
            -   Internal nodes lie from `0` to `(N/2 - 1)`
    4.  

---
<span style="color: violet; font-size: 18px;">**DP:**</span>

1. In case of problems related to `subsequence`, when characters from both string matches, just consider it into answer, and move pointers for both the strings. 
Basically, in case of subsequence if characters from both strings are matching at any index, on that index no need to apply other options like `take` `noTake`. 

---
<span style="color: violet; font-size: 18px;">**Graph:**</span>

1.  A `path` in a graph is a sequence of vertices where each adjacent pair of vertices is connected by an edge. A path always contain unique nodes, i.e., a node cannot appear twice in a path.
It can be of two types:
    - Simple Path: A path where no vertex is repeated.
    - Closed Path (Cycle): A path that **starts and ends at the same vertex**, with no other repetitions of vertices and edges.

2. For un-directed graphs, 
   - `degree of a node = #edges connected to it`.
3. For directed graphs,
   - `in-degree of a node = #edges in-coming to the node`.
   - `out-degree of a node = #edges out-going from the node`.
4. `total degree of a graph = 2 * total #edges` (because every edge is associated/connected to two nodes.)
5. Space needed for representing Graphs 
   - As Adjacency matris : O(V^2). Declared as: 
     ```cpp 
          int adjM[v+1][v+1]; 
     ```
   - As Adjacency list: O(E). Declared as: 
     ```cpp 
          vector<int> adjL[v+1]; 
     ```
   - As Adjacency list with weighted edges: 
     ```cpp 
          vector< pair<int,int> > adjWL[v+1]; 
     ```
6. Bipartite graph: 
   - two adjascent nodes can not have same color. Graph will be 2 colored.
   - Can have cycle of even length.
   - Can not have cycle of odd length.
7. Find shortest path from source node:
   - For DAG -> always do topo sort -> then BFS/DFS -> calculates predecssor nodes before a node -> in turn saves time
   - For undirected graph with unit weights -> Use plain BFS
   - For undirected graph with weighted edge - use Dijkstra -> Queue [Slow]-> Priority_queue -> Set [OPTIMAL]
   - The original Dijkstra algo works for undirected graphs only having non-ngetives edges.
   - We have modified `Dijkstra` incorporating priority_queue, so it can now handle negetive edges or non-negetive weight cycles only if graph is having directed edges. (Because undirected graph with a single negetive weight creates a negetive weight cycle.)
   - `Bellman-ford` algo can detect negetive weight cycles(a cycle where sum of all weights is negative). 
   - `Floyd warshall` can be used for for Directed and undirected graphs. 
   - If you need **all-pairs shortest paths**, running `Dijkstra` from every node is usually faster on **sparse graphs with non-negative weights** (≈ O(V·E log V)), while `Floyd–Warshall` is better for **dense graphs** (≈ O(V³)) or when there are **negative weights** (but no negative cycles). In short: use **Dijkstra-all-nodes** for large sparse graphs, and **Floyd–Warshall** for dense or negative-weighted graphs.
   - A `spanning tree` is a subset of a weighted graph in which there are N nodes(i.e. all the nodes present in the original graph) and N-1 edges and all nodes are reachable from each other. 
   - Any edge in a component of a graph is called a `bridge` when the component is divided into 2 or more components if that particular edge is removed. 
   - An `articulation point` or `cut-vertex` is a vertex whose removal, along with all its connected edges, increases the number of connected components in the graph.
   - A `back edge` is an edge in a graph that connects a vertex to one of its ancestors in a Depth-First Search (DFS) tree.
   - A component is called a `Strongly Connected Component(SCC)` only if for every possible pair of vertices (u, v) inside that component, u is reachable from v and vice-versa. Note: Strongly connected components(SCC) are only valid for **directed graphs**.
   - `Trie` is an advanced information retrieval data structure. Ability to quickly find all strings that start with a given prefix makes Tries particularly useful for applications like autocomplete and predictive text. 
   - 



---
### Some tricky problems to revise:

1. 074-Minimize Max Distance to Gas Station
2. 075-Median of 2 sorted arrays
3. 078-Find Peak Element in 2D Matrix
4. 079-Median of Row Wise Sorted Matrix
5. Is there any optimized version possible instead of O(N^2 * 26): https://leetcode.com/problems/sum-of-beauty-of-all-substrings/submissions/1653682726/
6. **DP** not used till now. Do later: 
   - https://leetcode.com/problems/longest-palindromic-substring/
   - 109-Word Searches: 
   - 
7. 110=N-Queens: Formula for upper and lower diagonal check in 2D matrix: https://takeuforward.org/data-structure/n-queen-problem-return-all-distinct-solutions-to-the-n-queens-puzzle/
8. 114-Expression Add Operators: **Hard**: [Expression Add Operators](https://leetcode.com/problems/expression-add-operators/) <- *could not complete.* getting **TLE**. Need to calculate the result on the go, instead of calculating it at the end. Follow Editorial.
9. 115-basic bit manipulation: Hard: [Title: Count the set bits](https://www.naukri.com/code360/problems/count-set-bits_1112627?leftPanelTabValue=PROBLEM) <- *could not complete.* getting **TLE**. Check later.
10. 119- Single number in array: Single number II: could n't grasp the 4th optimal solution mentioned in the video: [youtube](https://www.youtube.com/watch?v=5Bb2nqA40JY&t=77s).
11. Sliding window: Hard: Minimum Window Subsequence -> need DP to solve. Check after DP. [Problem link](https://www.naukri.com/code360/problems/minimum-window-subsequence_2181133) [Editorial](https://takeuforward.org/plus/dsa/problems/minimum-window-subsequence?tab=editorial)
12. 155-Check for heap: Need to try for linkedlist tree also. Check after tree: [Unsolved problem](https://www.geeksforgeeks.org/problems/is-binary-tree-heap/1)
13. 168-DFS traversal for Binary tree: [L12. Iterative Postorder Traversal using 1 Stack](https://www.youtube.com/watch?v=NzIGLLwZBS8&list=PLkjdNRgDmcc0Pom5erUBU4ZayeU9AyRRu&index=12) -> Logic is complex though alternate easy approach is available. Check later.
14. Binary tree question try later: [GFG](https://www.geeksforgeeks.org/problems/postorder-traversal-from-given-inorder-and-preorder-traversals/1)
15. In BST try this later: [ninja](https://www.naukri.com/code360/problems/maximum-node-in-between_920450)
16. Solve later: Merge 2 BST's: [leetcode](https://leetcode.com/problems/merge-bsts-to-create-single-bst/description/) [youtube](https://www.youtube.com/watch?v=AiKZjCuy2k4&t=4s&ab_channel=ShradhaKhapra)
17. Do after DP: Jump Game II: [leetcode](https://leetcode.com/problems/jump-game-ii/description/) [youtube](https://www.youtube.com/watch?v=7SBVnw7GSTk&t=1s)
18. [Meet in the middle approach](https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/description/) Complete: 225-Partition Set Into 2 Subsets With Min Absolute Sum Diff.cpp
19. [Graph Leetcode TLE](https://leetcode.com/problems/word-ladder-ii/submissions/1747769329/) : 258-Word ladder.cpp TUF+ approach:2
20. To do: [leetcode](https://leetcode.com/problems/course-schedule-ii/)