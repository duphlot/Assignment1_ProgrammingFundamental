#include "dragon.h"

// ***
// If you don't want to lose a LOT of points, please don't add any libraries here. T_T
// ***

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

Dragon dragons[MAX_DRAGONS];
int dragonDamages[5] = {0, 0, 0, 0, 0};
int N = 0;

int typeNameToType(const string typeName) {
    if (typeName == "Night Fury") return 1;
    if (typeName == "Deadly Nadder") return 2;
    if (typeName == "Monstrous Nightmare") return 3;
    if (typeName == "Gronckle") return 4;
    if (typeName == "Hideous Zippleback") return 5;
    if (typeName == "1") return 1;
    if (typeName == "2") return 2;
    if (typeName == "3") return 3;
    if (typeName == "4") return 4;
    if (typeName == "5") return 5;

    return 0;
}

bool countSpecialCharacters(string name){
    int count = 0;
    for (char c : name) {
        if (!isalnum(c) && c != ' ' && c != '-' && c != '_') {
            count++;
        }
    }
    return count;
}

int countBlankSpaces(string name) {
    int count = 0;
    // Count over spaces
    for (int i=1;i<name.length();i++) {
        if (name[i] == ' ' && name[i-1] == ' ') {
            count++;
        }
    }
    return count;
}

// Helper function to parse quoted strings
int parseQuotedStrings(const string& line, string results[], int maxCount) {
    int count = 0;
    size_t start = line.find('"');
    while (start != string::npos && count < maxCount) {
        size_t end = line.find('"', start + 1);
        if (end != string::npos) {
            results[count] = line.substr(start + 1, end - start - 1);
            count++;
            start = line.find('"', end + 1);
        } else {
            break;
        }
    }
    return count;
}

// Helper function to parse array values
int parseArrayValues(const string& line, int results[], int maxCount) {
    int count = 0;
    size_t start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        string token;
        while (getline(valStream, token, ';') && count < maxCount) {
            results[count] = stoi(token);
            count++;
        }
    }
    return count;
}

// Task 1
int readFile(const string filename, Dragon dragons[], int dragonDamages[5], int &N)
{
    // Check file extension first
    if (filename.substr(filename.find_last_of(".") + 1) != "txt") {
        return 2; // File doesn't have .txt extension
    }

    ifstream ifs(filename);
    if (!ifs.is_open()){
        return 3; // File not found
    }

    string line;
    
    // Read dragon names line: ["Toothless", "Stormfly", ...]
    if (!getline(ifs, line)) {
        ifs.close();
        return 4;
    }
    
    int dragonCount = 0;
    size_t start = line.find('"');
    while (start != string::npos && dragonCount < MAX_DRAGONS) {
        size_t end = line.find('"', start + 1);
        if (end != string::npos) {
            dragons[dragonCount].dragonNames = line.substr(start + 1, end - start - 1);
            dragonCount++;
            start = line.find('"', end + 1);
        } else {
            break;
        }
    }

    // Read dragon types line: ["Night Fury", "Deadly Nadder", ...]
    if (!getline(ifs, line)) {
        ifs.close();
        return 4;
    }

    string typeNames[MAX_DRAGONS];
    int typeCount = 0;
    start = line.find('"');
    while (start != string::npos && typeCount < MAX_DRAGONS) {
        size_t end = line.find('"', start + 1);
        if (end != string::npos) {
            string typeName = line.substr(start + 1, end - start - 1);
            typeNames[typeCount] = typeName;
            typeCount++;
            start = line.find('"', end + 1);
        } else {
            break;
        }
    }

    // Read temperament values: [9; 8; 7; 7; 6]
    if (!getline(ifs, line)) {
        ifs.close();
        return 4; 
    }
    
    int tempCount = 0;
    start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        string token;
        while (getline(valStream, token, ';') && tempCount < MAX_DRAGONS) {
            if (tempCount < dragonCount) {
                dragons[tempCount].dragonTemperament = stoi(token);
            }
            tempCount++;
        }
    }
    
    // Read ammo counts: [3; 2; 5; 1; 4]
    if (!getline(ifs, line)) {
        ifs.close();
        return 4; 
    }
    
    int ammoCount = 0;
    start = line.find('[');
    end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        string token;
        while (getline(valStream, token, ';') && ammoCount < MAX_DRAGONS) {
            if (ammoCount < dragonCount) {
                dragons[ammoCount].ammoCounts = stoi(token);
            }
            ammoCount++;
        }
    }

    // Read dragon damages: [100; 80; 90; 70; 95] 
    if (!getline(ifs, line)) {
        ifs.close();
        return 4;
    }
    
    int damageCount = 0;
    start = line.find('[');
    end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        string token;
        while (getline(valStream, token, ';') && damageCount < 5) {
            dragonDamages[damageCount] = stoi(token);
            damageCount++;
        }
    }
    

    
    // Read rider names: ["Hiccup", "Astrid", ...]
    if (!getline(ifs, line)) {
        ifs.close();
        return 4;
    }
    
    int riderCount = 0;
    start = line.find('"');
    while (start != string::npos && riderCount < MAX_DRAGONS) {
        size_t nameEnd = line.find('"', start + 1);
        if (nameEnd != string::npos) {
            if (riderCount < dragonCount) {
                dragons[riderCount].riderNames = line.substr(start + 1, nameEnd - start - 1);
            }
            riderCount++;
            start = line.find('"', nameEnd + 1);
        } else {
            break;
        }
    }

    if (!getline(ifs, line)) {
        ifs.close();
        return 4; 
    }
    N = stoi(line);
    
    if (N != dragonCount) {
        ifs.close();
        return 5; 
    }

    if (typeCount != N) {
        ifs.close();
        return 6; 
    }
    if (tempCount != N) {
        ifs.close();
        return 7;
    }
    if (ammoCount != N) {
        ifs.close();
        return 8;
    }

    // Check if dragonDamages array has exactly 5 elements
    if (damageCount != 5) {
        ifs.close();
        return 9;
    }

    if (riderCount != N) {
        ifs.close();
        return 10; 
    }

    // check invalid dragon names
    for (int i = 0; i < N; i++) {
        if (countSpecialCharacters(dragons[i].dragonNames)!=0) {
            return (100 + i); 
        }
    }
    for (int i=0; i < N; i++){
        int count = countSpecialCharacters(typeNames[i]);
        if (count != 0) {
            return (500 + count);
        }
    }
    for (int i = 0; i < N;i++){
        dragons[i].dragonTypes = typeNameToType(typeNames[i]);
    } 

    for (int i = 0; i < N; i++) {
        if (countBlankSpaces(dragons[i].riderNames) > 0) {
            return (900 + i);
        }
    }
    int countBlankInNames = 0;
    for (int i = 0; i < N; i++) {
        countBlankInNames += countBlankSpaces(dragons[i].dragonNames);
        if (countBlankInNames > 1) {
            return (1000 + countBlankInNames);
        }
    }

    for (int i = 0; i < dragonCount; i++) {
    cout << "Dragon " << i + 1 << ": " << dragons[i].dragonNames 
         << ", Type: " << dragons[i].dragonTypes 
         << ", Temperament: " << dragons[i].dragonTemperament 
         << ", Ammo: " << dragons[i].ammoCounts 
         << ", Rider: " << dragons[i].riderNames 
         << ", Damage: " << dragonDamages[i] << endl;
    }

    ifs.close();
    return 1; // Success
}

// Task 2
string findKthStrongestDragon(Dragon dragons[], int dragonDamages[5], int N, int T){
    int maxPower = 0, answer = 0;

    double coefficient1[] = {1,1,1,1,0.9};
    double coefficient2[] = {3,2,1,0.5,1.5};

    for (int i = 0; i < N; i++){
        int types = dragons[i].dragonTypes;
        if (dragons[i].dragonTemperament >= T){
            int temp = (dragons[i].ammoCounts * dragonDamages[types - 1] * coefficient1[types - 1]) + dragons[i].dragonTemperament * coefficient2[types - 1];
            if (temp > maxPower) {
                maxPower = temp;
                answer = i; 
            }
        }
    }
    return (answer == 0) ? "None" : dragons[answer].dragonNames;
}

// Task 3.1
void compatibilityCheck(Dragon dragons[], string warriorName, int warriorSkill)
{
    for (int i = 0; i < N; i++) {
        float compatibility = calculateCompatibility(warriorSkill, dragons[i]);
        printCompatibilityTable(warriorName, dragons[i].dragonNames, compatibility);
    }
}

void printCompatibilityTable(string fighterName, string dragonName, float compatibility)
{
    static bool headerPrinted = false;
    if (!headerPrinted) {
        cout << "Warrior      Dragon        Compatibility    Review" << endl;
        headerPrinted = true;
    }

    string result = (compatibility > 4) ? "Compatible" : "Not Compatible";

    cout << left << setw(13) << fighterName
         << setw(14) << dragonName
         << setw(17) << fixed << setprecision(2) << compatibility
         << result << endl;
}

// Task 3.2
void buddyMatching(Dragon dragons[], string warriors[][3])
{
    bool dragonUsed[MAX_DRAGONS] = {false};
    
    for (int i = 0; i < N; i++) {
        string warriorName = warriors[i][0];
        int warriorSkill = stoi(warriors[i][1]);
        
        int bestDragonIndex = -1;
        float bestCompatibility = 0;
        
        // Find the best available dragon for this warrior
        for (int j = 0; j < N; j++) {
            if (!dragonUsed[j]) {
                float compatibility = calculateCompatibility(warriorSkill, dragons[j]);
                if (compatibility > bestCompatibility) {
                    bestCompatibility = compatibility;
                    bestDragonIndex = j;
                }
            }
        }
        
        if (bestDragonIndex != -1) {
            dragonUsed[bestDragonIndex] = true;
            printCompatibilityTable(warriorName, dragons[bestDragonIndex].dragonNames, bestCompatibility);
        }
    }
}

// Task 4
void computeChallengeTime(string warriors[][3], string map[10][10])
{
    for (int w = 0; w < N; w++) {
        string warriorName = warriors[w][0];
        int startX = stoi(warriors[w][1]);
        int startY = stoi(warriors[w][2]);
        
        // Find shortest path using BFS or dynamic programming
        int dp[10][10];
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                dp[i][j] = INT_MAX;
            }
        }
        
        dp[startX][startY] = 0;
        
        // Simple path finding - assuming we can move in 4 directions
        for (int dist = 0; dist < 100; dist++) {
            bool updated = false;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (dp[i][j] == dist) {
                        // Try moving in 4 directions
                        int dx[] = {-1, 1, 0, 0};
                        int dy[] = {0, 0, -1, 1};
                        
                        for (int d = 0; d < 4; d++) {
                            int nx = i + dx[d];
                            int ny = j + dy[d];
                            
                            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10) {
                                int moveCost = 1;
                                if (map[nx][ny] == "1") moveCost = 2; // Obstacle cost
                                else if (map[nx][ny] == "2") moveCost = 3; // Heavy obstacle
                                
                                if (dp[nx][ny] > dp[i][j] + moveCost) {
                                    dp[nx][ny] = dp[i][j] + moveCost;
                                    updated = true;
                                }
                            }
                        }
                    }
                }
            }
            if (!updated) break;
        }
        
        // Find minimum time to any edge (challenge completion)
        int minTime = INT_MAX;
        for (int i = 0; i < 10; i++) {
            minTime = min(minTime, dp[i][0]); // Left edge
            minTime = min(minTime, dp[i][9]); // Right edge
            minTime = min(minTime, dp[0][i]); // Top edge
            minTime = min(minTime, dp[9][i]); // Bottom edge
        }
        
        cout << "Warrior " << warriorName << " challenge time: " << minTime << " units" << endl;
    }
}

// Task 5.1
void fighterDamage(Dragon dragons[], string warriors[][3], int teamsDamage[])
{
    for (int i = 0; i < N; i++) {
        string warriorName = warriors[i][0];
        int warriorSkill = stoi(warriors[i][1]);
        int warriorExperience = stoi(warriors[i][2]);
        
        // Find the warrior's matched dragon
        int dragonIndex = i; // Assume 1-to-1 matching by index
        
        // Calculate damage: (warriorSkill + experience) * dragonDamage * compatibility / scalingFactor
        float compatibility = calculateCompatibility(warriorSkill, dragons[dragonIndex]);
        
        int baseDamage = warriorSkill + warriorExperience;
        int totalDamage = (int)((baseDamage * dragonDamages[dragonIndex] * compatibility) / 100.0);
        
        teamsDamage[i] = totalDamage;
        
        cout << "Warrior " << warriorName << " with " << dragons[dragonIndex].dragonNames 
             << " deals " << totalDamage << " damage" << endl;
    }
}

// Task 5.2
int calculateTeamDamage(int teamsDamage[], int teamSize)
{
    int totalDamage = 0;
    for (int i = 0; i < teamSize; i++) {
        totalDamage += teamsDamage[i];
    }
    return totalDamage;
}

// Additional helper function for team battle simulation
void teamBattle(Dragon dragons[], string warriors[][3], int teamsDamage[])
{
    cout << "=== TEAM BATTLE SIMULATION ===" << endl;
    
    // Calculate individual fighter damages first
    fighterDamage(dragons, warriors, teamsDamage);
    
    // Calculate total team damage
    int totalTeamDamage = calculateTeamDamage(teamsDamage, N);
    
    cout << "\nTeam Summary:" << endl;
    cout << "Total Team Damage: " << totalTeamDamage << endl;
    cout << "Average Damage per Fighter: " << (float)totalTeamDamage / N << endl;
    
    // Determine team effectiveness
    if (totalTeamDamage > 1000) {
        cout << "Team Status: ELITE FORCE" << endl;
    } else if (totalTeamDamage > 500) {
        cout << "Team Status: STRONG TEAM" << endl;
    } else {
        cout << "Team Status: NEEDS TRAINING" << endl;
    }
}

// Utility functions
void displayDragonStats(Dragon dragons[], int dragonDamages[], int N)
{
    cout << "\n=== DETAILED DRAGON STATISTICS ===" << endl;
    cout << left << setw(15) << "Dragon Name" 
         << setw(12) << "Type" 
         << setw(12) << "Temperament" 
         << setw(8) << "Ammo" 
         << setw(8) << "Damage" 
         << setw(15) << "Rider" << endl;
    cout << string(80, '-') << endl;
    
    for (int i = 0; i < N; i++) {
        cout << left << setw(15) << dragons[i].dragonNames
             << setw(12) << dragons[i].dragonTypes
             << setw(12) << dragons[i].dragonTemperament
             << setw(8) << dragons[i].ammoCounts
             << setw(8) << dragonDamages[i]
             << setw(15) << dragons[i].riderNames << endl;
    }
}

float calculateCompatibility(int warriorSkill, Dragon& dragon)
{
    return sqrt((float)(warriorSkill * dragon.dragonTemperament) + dragon.dragonTypes);
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
