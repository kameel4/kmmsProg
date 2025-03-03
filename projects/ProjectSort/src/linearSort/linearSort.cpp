#include "linearSort/linearSort.hpp"

// void compare_time(vector<long long> unsorted);
// vector <long long> random_vector(int N);
// void check_sort();
// void countingSort(vector<long long>& arr, long long exp, int basis);
// void radixSort(vector<long long>& arr, int basis);

using namespace std;
using namespace chrono;



void countingSort(vector<long long>& arr, long long exp, int basis) {
    int n = arr.size();
    vector<long long> output(n);
    vector<int> count(basis);

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % basis]++;

    for (int i = 1; i < basis; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % basis] - 1] = arr[i];
        count[(arr[i] / exp) % basis]--;
    }

    arr = output;
}

void radixSort(vector<long long>& arr, int basis) {
    long long max = *max_element(arr.begin(), arr.end());
    long long exp = 1;

    while (max / exp > 0) {
        countingSort(arr, exp, basis);
        exp *= basis;
    }
}




// void compare_time(vector<long long> unsorted){
//    //Замер времени модифицированной сортировки
//    vector<long long> rVector1 = unsorted;
//    vector<long long> rVector2 = unsorted;
//    int N = log10(unsorted.size());

//    // rVector1.reserve(rVector1.size()*2);

//    auto start1 = steady_clock :: now ();
//    radixSort(rVector1, 1020);
//    auto end1 = steady_clock :: now ();
//    duration <double> elapsed_seconds1 = end1 - start1;



//    auto start2 = steady_clock :: now ();
//    sort(begin(rVector2), end(rVector2));
//    auto end2 = steady_clock :: now ();
//    duration <double> elapsed_seconds2 = end2 - start2;

//    cout<<"Elapsed time for LSD Radix Sort with 10e"<<N<<" elements: "<<elapsed_seconds1.count()<<endl;
//    cout<<"Elapsed time for standart Sort with 10e"<<N<<" elements: "<<elapsed_seconds2.count()<<endl<<endl;
// }

vector <long long> random_vector(int N){
   random_device rd;
   mt19937 dev(rd());
   vector <long long> listick;
   uniform_int_distribution<long long> distribution(1, pow(N, 3)-1);

   for (int i =0; i<N; i++){listick.push_back(distribution(dev) );}
   return listick;
 }

//  void check_sort(){
//     vector<long long> v = random_vector(1000000);
//     vector<long long> v1 = v;

//     // for (long long elem: v){cout<<elem<<" ";}
//     // cout<<endl;
//     //     for (long long elem: v1){cout<<elem<<" ";}
//     // cout<<endl;


//     radixSort(v, 10200);
//     sort(v1.begin(), v1.end());

//     if (v == v1)
//         {cout<<"sort is ok  ˙ᵕ˙\n";}
//     else 
//         {cout<<"sort is not ok   • ᴖ • \n";};
// }