/*
 * File: gen.cpp
 * Author: vididvidid 
 * Created: 2026-04-15 02:31:22
 */
#include <iostream>
#include <random>

using namespace std;

int main() {
    random_device rd;
    mt19937_64 gen(rd());
    
    // MICRO-TEST: Keep N between 2 and 6 so you can trace it by hand
    uniform_int_distribution<int> dist_n(2, 6);
    int n = dist_n(gen);
    
    // MICRO-TEST: Keep step lengths between 1 and 10
    uniform_int_distribution<long long> dist_l(1, 10);
    
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        cout << dist_l(gen) << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
    
    return 0;
}
