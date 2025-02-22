#include<iostream>
#include "linearSort.hpp"

using namespace std;

int main(){
    for(int  n = 10; n<20; n+=3){  
        vector<long long> arr = random_vector(n);
        // printing the vector
        for (long long elem: arr){cout<<elem<<" ";}
        cout<<endl;

        radixSort(arr, 10);
        // printing the sorted vector
        for (long long elem: arr){cout<<elem<<" ";}
        cout<<endl<<endl;

        }
}
