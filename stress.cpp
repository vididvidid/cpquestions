/*
 * File: stress.cpp
 * Author: vididvidid 
 * Created: 2026-04-15 02:31:33
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

// Function to compare two output files ignoring whitespace
// Function to compare two output files ignoring whitespace
bool compareFiles(const string& file1, const string& file2) {
    ifstream f1(file1), f2(file2);
    string token1, token2;
    while (f1 >> token1 && f2 >> token2) {
        if (token1 != token2) return false;
    }
    // Explicitly cast the stream states to bool to compare them safely
    return bool(f1 >> token1) == bool(f2 >> token2); 
}

int main() {
    cout << "Compiling files...\n";
    // Compile the generator and the original C++ solution
    // Adjust "orig.cpp" to whatever you named the C++ solution file
    system("g++ gen.cpp -o gen");
    system("g++ orig.cpp -o orig");
    cout << "Compilation finished. Starting stress test...\n";

    int tests_passed = 0;
    while (true) {
        // 1. Generate random input
        system("./gen > input.txt"); // Use "gen > input.txt" on Windows

        // 2. Run both solutions with the generated input
        system("./orig < input.txt > out_orig.txt"); // Use "orig < ..." on Windows
        
        // Ensure you have python installed and in your PATH. 
        // Use "python" instead of "python3" if you are on Windows.
        system("python3 friend.py < input.txt > out_friend.txt"); 

        // 3. Compare the outputs
        if (!compareFiles("out_orig.txt", "out_friend.txt")) {
            cout << "\n====================================\n";
            cout << "WA FOUND! MISMATCH DETECTED!\n";
            cout << "====================================\n\n";
            
            cout << "--- INPUT ---\n";
            ifstream in("input.txt");
            cout << in.rdbuf() << "\n";

            cout << "\n--- ORIGINAL (CORRECT) OUTPUT ---\n";
            ifstream out1("out_orig.txt");
            cout << out1.rdbuf() << "\n";

            cout << "\n--- FRIEND'S OUTPUT ---\n";
            ifstream out2("out_friend.txt");
            cout << out2.rdbuf() << "\n";
            
            break; // Stop testing so you can debug
        }
        
        tests_passed++;
        if (tests_passed % 10 == 0) {
            cout << "Passed " << tests_passed << " random tests...\n";
        }
    }

    return 0;
}
