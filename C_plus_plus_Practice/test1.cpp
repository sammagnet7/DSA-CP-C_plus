#include<iostream>
using namespace std;

void* operator new (size_t s){

    cout<<"howl"<<endl; 
    void* p=malloc(s);
    return p;
}

int main(){
 int *p = new int(7);
 //*p = 5;

 cout<<*p<<endl;   
}