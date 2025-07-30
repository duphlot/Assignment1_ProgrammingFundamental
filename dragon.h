#ifndef _DRAGON_H_
#define _DRAGON_H_

#include "main.h"
// ***
// If you don't want to lose a LOT of points, please don't add any libraries here. T_T
// ***

#define MAX_DRAGONS 10

struct Dragon {
    string dragonNames;
    int dragonTypes;
    int dragonTemperament;
    int ammoCounts;
    string riderNames;
};

extern Dragon dragons[MAX_DRAGONS];
extern int dragonDamages[5];
extern int N;
extern int path[200][2];
extern int pathLen;

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Task 1
int readFile(const string filename, Dragon dragons[], int (&dragonDamages)[5], int &N);

// Task 2
string findKthStrongestDragon(Dragon dragons[], int dragonDamages[5], int N, int T);

// Task 3.1
void compatibilityCheck(Dragon dragons[], string warriorName, int warriorSkill);
void printCompatibilityTable(string fighterName, string dragonName, float compatibility);

// Task 3.2
void buddyMatching(Dragon dragons[], string warriors[][3]);

// Task 4
void computeChallengeTime(string warriors[][3], int map[10][10]);

// Task 5.1
void fighterDamage(Dragon dragons[], string warriors[][3], int teamsDamage[]);

// Task 5.2
void findHeritageLocation(int  map[10][10], int &heritageX, int &heritageY);
void findKeyLocation(int map[10][10], int &keyX, int &keyY);
void totalTime(int map[10][10], int warriorDamage, int HP);


////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////

#endif /* _DRAGON_H_ */
