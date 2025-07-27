/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Summer 2025
* Date: 13.07.2025
*/

// The library here is concretely set, students are not allowed to include any other libraries.

#include "dragon.h"
#include <iostream>

void sampleTest(string filename = "tnc_tc_01_input.txt", string outputFile = "tnc_tc_01_output.txt") {
    // freopen(outputFile.c_str(), "w", stdout); 
    const string inputFile = filename;

    int result = readFile(inputFile, dragons, dragonDamages, N);
    if (result != 1) {
        cout << "Error code: " << result << endl;
        return;
    }

    cout << "File read successfully." << endl;
    cout << "Number of dragons: " << N << endl;
    
    // Display detailed dragon statistics
    // displayDragonStats(dragons, dragonDamages, N);
}

void testAllFunctions() {
    cout << "\n=== TESTING ALL FUNCTIONS ===" << endl;
    
    // Test Task 2: Find strongest dragons
    cout << "\n--- Task 2: Strongest Dragons ---" << endl;
    int testDamages[] = {100, 80, 90, 70, 95};
    cout << "Task 2 answer: " << findKthStrongestDragon(dragons, testDamages, N, 6) << endl;
    
    // Test Task 3.1: Compatibility Check
    cout << "\n--- Task 3.1: Compatibility Check ---" << endl;
    compatibilityCheck(dragons, "TestWarrior", 8);
    
    // Test Task 3.2: Buddy Matching with sample warriors
    cout << "\n--- Task 3.2: Buddy Matching ---" << endl;
    string sampleWarriors[4][3] = {
        {"Hiccup", "9", "1"},
        {"Astrid", "8", "3"},
        {"Snotlout", "6", "4"},
        {"Fishlegs", "7", "2"}
    };
    buddyMatching(dragons, sampleWarriors);
    
    // Test Task 4: Challenge Time (with sample map)
    cout << "\n--- Task 4: Challenge Time ---" << endl;
    int sampleMap[10][10] = {
        {0, 1, 2, 3, 4, 0, 1, 2, 3, 4},
        {1, 2, 3, 4, 0, 1, 2, 3, 4, 0},
        {2, 3, 4, 0, 1, 2, 3, 4, 0, 1},
        {3, 4, 0, 1, 2, 3, 4, 0, 1, 2},
        {4, 0, 1, 2, 3, 4, 0, 1, 2, 3},
        {0, 1, 2, 3, 4, 0, 1, 2, 3, 4},
        {1, 2, 3, 4, 0, 1, 2, 3, 4, 0},
        {2, 3, 4, 0, 1, 2, 3, 4, 0, 1},
        {3, 4, 0, 1, 2, 3, 4, 0, 1, 2},
        {4, 0, 1, 2, 3, 4, 0, 1, 2, 3}
    };

    computeChallengeTime(sampleWarriors, sampleMap);
    
    // Test totalTime function
    cout << "\n--- Testing totalTime Function ---" << endl;
    int testMap[10][10] = {
        { 10,  20,  30,  40,  50,  60,  70,  80,  90, 100 },
        { 15,  25,  35,  45,  55,  65,  75,  85,  95, 105 },
        { 12,  22,  32,  42,  52,  62,  72,  82,  92, 175 },
        {118, 128, 138,  50,  58,  68,  78,  88,  98, 108 },
        { 14,  24,  34,  44,  54,  64,  74,  84,  94, 104 },
        { 19,  29,  39,  49,  59,  69,  79,  89,  99, 109 },
        { 11,  21,  31,  41,  51,  61,  71,  81,  91, 101 },
        { 16,  26,  36,  46,  56,  66,  76, 186,  96, 106 },
        { 17,  27,  37,  47,  57,  67, 196,  87,  90, 107 },
        { 13,  23,  33,  43,  53,  63,  73, 153,  93, 170 }
    };
    
    // Test với chiến binh có sát thương = 150 và HP = 20 như ví dụ
    totalTime(testMap, 150, 20);
}
int main() {
    sampleTest();
    testAllFunctions();
    return 0;
}
