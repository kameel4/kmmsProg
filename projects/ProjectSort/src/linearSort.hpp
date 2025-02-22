#ifndef LINEAR_SORT_HPP
#define LINEAR_SORT_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

// void compare_time(vector<long long> unsorted);
vector <long long> random_vector(int N);
// void check_sort();
void countingSort(vector<long long>& arr, long long exp, int basis);
void radixSort(vector<long long>& arr, int basis);

#endif
