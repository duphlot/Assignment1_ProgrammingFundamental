/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Summer 2025
* Date: 13.07.2025
*/

// The library here is concretely set, students are not allowed to include any other libraries.

#include "dragon.h"

void sampleTest() {
    const string inputFile = "tnc_tc_01_input.txt";

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
    string sampleWarriors[5][3] = {
        {"Hiccup", "9", "5"},
        {"Astrid", "8", "4"},
        {"Snotlout", "6", "3"},
        {"Fishlegs", "7", "6"},
        {"Tuffnut", "5", "2"}
    };
    buddyMatching(dragons, sampleWarriors);
    
    // // Test Task 4: Challenge Time (with sample map)
    // cout << "\n--- Task 4: Challenge Time ---" << endl;
    // string sampleMap[10][10];
    // for (int i = 0; i < 10; i++) {
    //     for (int j = 0; j < 10; j++) {
    //         sampleMap[i][j] = "0"; // Default empty terrain
    //     }
    // }
    // // Add some obstacles
    // sampleMap[2][3] = "1";
    // sampleMap[4][5] = "2";
    // sampleMap[6][7] = "1";
    
    // computeChallengeTime(sampleWarriors, sampleMap);
    
    // // Test Task 5: Fighter Damage
    // cout << "\n--- Task 5: Team Battle ---" << endl;
    // int teamsDamage[5];
    // teamBattle(dragons, sampleWarriors, teamsDamage);
}

int main() {
    sampleTest();
    testAllFunctions();
    return 0;
}
