#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() 
{
    int a, b, c;
    cin>> a >> b >> c;

     double D;
    D = (b * b) - 4 * a * c;

    if (D<0){
        cout<< 0;
    } else if (D == 0){
         double x = (-b) / (2*a);
        cout<< 1 << endl << fixed << setprecision(6) << x;
    }else{
         double D_sqrt = sqrt(D);
         double x1, x2;
        x1 = ((-b) + D_sqrt) / (2*a);
        x2 = ((-b) - D_sqrt) / (2*a);
        cout<< 2 << endl << fixed << setprecision(6) << x2 << " " << x1;
    }

    return 0;
}