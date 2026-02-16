#include <iostream>
using namespace std;

// 1
//  struct complex {
//     double real;
//     double image;
// } c_num;

// void testStruct(){
//      struct complex c={11,20};
//     cout<<c.real<<endl;
//     c.real=33;
//     cout<<c.real<<endl;

//     c_num.real =10;
//     c_num.image = 20;

//     cout<< c_num.real<<" "<<c_num.image<<endl;
// }

// int main(){
//    testStruct();
// }

// 2
// enum {S=0, B=1} X;


// 3
// void checkMem()
// {
//     cout<<sizeof(int)<<endl;
//     cout<<sizeof(char)<<endl;

//     int *p = (int *)malloc(2*sizeof(int));

//     p[0] = 0x8F7E1A2B;
//     // std::cout<< (*p) << std::endl;
//     printf("%X\n", *p);

//     unsigned char *c;
//     c = (unsigned char *)p;

//     cout << "----" << endl;
//     // std::cout<< (*c) << std::endl;
//     printf("%X\n", *c);

//     cout << "----" << endl;
//     c++;
//     // std::cout<< (*c) << std::endl;
//     printf("%X\n", *c);

//     cout << "----" << endl;
//     c++;
//     // std::cout<< (*c) << std::endl;
//     printf("%X\n", *c);

//     cout << "----" << endl;
//     c++;
//     // std::cout<< (*c) << std::endl;
//     printf("%X\n", *c);
// }

// int main()
// {
//     checkMem();
// }

// 4
double area(int a, int b=10){
    cout<<1<<endl;
    return a*b;
}
double area(double c, double d){
    cout<<2<<endl;
    return c*d;
}
int main(){
    double x=10.11;
    int y=12;

    //cout<< area(x,y) <<endl; //both methodss have 50-50 chance
    cin>>x;
    cout<<x<<endl;
    cout<<"Hi";
}
