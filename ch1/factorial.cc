#include <iostream>
using namespace std;

int factorial(int x);


int main(){
    
    cout << factorial(5) << endl;
}

int factorial(int x){
    if (x == 1){
        return 1;
    }
    else{
        return x * factorial(x-1);
    }
}