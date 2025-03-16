# Points to note

1. We must be careful that we will not manipulate the given data. A company may use the same data for different purposes. So, we will never manipulate the given data i.e. the inputs until the interviewer specifically says so.

2.  In CP or in the platforms like Leetcode and GeeksforGeeks, we generally run our codes on online servers. Most of these servers execute roughly **10<sup>8</sup>** (i.e. 1 crore) operations in approximately **1_second** i.e. 1s. 

     We must be careful that if the time limit is given as **2s** the operations in our code must be roughly **2 * 10<sup>8</sup>**, not 10<sup>16</sup>. 
     
     Simply, if we want our code to be run in **1s**, the time complexity of our code must be around **O(10<sup>8</sup>)** avoiding the constants and the lower values.

3. 10<sup>8</sup> operations take 1 second to get executed. So, 10<sup>10</sup> operations will take around 100 seconds(10<sup>10</sup>/10<sup>8</sup>). Code will get TLE if it takes 100 seconds to get executed.

4. C++ `Data-types` ref: https://www.programiz.com/cpp-programming/data-types

5. **Switch statementsS:** 

    A switch statement necessitates that its expression results in a **constant** value. This can include constants and arithmetic operations. 

    Ensure that the expression provides values of type `int` or `char` or `enum`. Switch statements in *C* or *C++* are exclusively designed to handle integer, character or enum values only.
 
 6. The rate at which the time, required to run a code, changes with respect to the input size, is considered the time complexity. Time complexity of a particular code depends on the given input size, not on the machine used to run the code.

    ![Time complexity](./img/time_complexity.png)

7. Libraries:
     - **#include <bits/stdc++.h> :** Includes all popular library at once. But not available in all compilers.
     - std::swap() : swaps 2 pointers in the argument
     - #include<climits> : INT_MAX, INT_MIN

8. Shortcuts:
     - Initializing array filled with default values: int hash[13] = {0};
     - To print as Booleans:
     ```
          cout << std::boolalpha; 
          cout << true << endl;
          cout << std::noboolalpha;
     ```
     - 
     -
     -
     -


9. 
![Max array size we can initialize with](./img/max_array_size.png)

10. If the string contains both uppercase and lowercase letters: We have 256 characters in total in this case. So, we will create a hash array of size **256**. Otherwise we can use hash[s[i]-’a’] OR hash[s[i]-’A’] and keep the hash array of 26 elements only.

11. In the map data structure, the data type of key can be anything like int, double, pair<int, int>, etc. But for unordered_map the data type is limited to integer, double, string, etc. We cannot have an unordered_map whose key is pair<int, int>. 

12. How to traverse map from end to start?
     Ans: 

     ```c++
          for(auto it=freq.rbegin(); it!=freq.rend(); it++){
            cout<<it->first<<endl;
          }
     ```

13. XOR properties:
     - XOR of two same numbers is always 0 i.e. a ^ a = 0. ←Property 1.
     - XOR of a number with 0 will result in the number itself i.e. 0 ^ a = a.  ←Property 2

14. Sub-array vs sub-sequence:
    - A subarray is a contiguous (consecutive) portion of an array.
    - A subsequence is a sequence of elements derived from the original array by deleting some elements without changing the order of the remaining elements.

15. 