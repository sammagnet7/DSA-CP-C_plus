#include<iostream>
/*
By adding using namespace std; at the beginning of your program, you're telling the compiler 
that you want to use all the names from the std namespace without explicitly specifying std:: each time.
However, as your programming projects grow in complexity, consider using it sparingly to avoid potential naming conflicts.
*/
using namespace std;

/*
Using \n for line breaks in C++ is a common and efficient way to achieve the desired output. 
It's typically faster than other methods for adding line breaks, such as using std::endl.
The reason for this is that \n is a low-level operation that directly moves the cursor to the beginning of the next line in the output. 
On the other hand, std::endl not only adds a newline character but also flushes the output buffer. Flushing the buffer can be a more costly.
*/
int main(){
    string fname, lname;
    cout<< "Input your first name and second name: "<<endl;
    cin >> fname;
    cin >> lname;
    cout<< "Welcome "<<fname<<" "<<lname<<"!!" <<endl;
    return 0;
}