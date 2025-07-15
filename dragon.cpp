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

// Task 1
int readFile(const string filename, Dragon dragons[], int dragonDamages[5], int &N)
{
    ifstream ifs(filename);
    if (!ifs.is_open())
    {
        return 3; // File not found
    }

    string line;
    
    // Read dragon names line: ["Toothless", "Stormfly", ...]
    if (!getline(ifs, line)) return 2;
    stringstream ss1(line);
    string name;
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
    
    // Skip dragon type names line
    if (!getline(ifs, line)) return 2;
    
    // Read temperament values: [9; 8; 7; 7; 6]
    if (!getline(ifs, line)) return 2;
    stringstream ss3(line);
    string token;
    int index = 0;
    start = line.find('[');
    size_t end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        while (getline(valStream, token, ';') && index < dragonCount) {
            dragons[index].dragonTemperament = stoi(token);
            index++;
        }
    }
    
    // Read dragon types: [3; 2; 5; 1; 4]
    if (!getline(ifs, line)) return 2;
    index = 0;
    start = line.find('[');
    end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        while (getline(valStream, token, ';') && index < dragonCount) {
            dragons[index].dragonTypes = stoi(token);
            index++;
        }
    }
    
    // Read ammo counts: [100; 80; 90; 70; 95]
    if (!getline(ifs, line)) return 2;
    index = 0;
    start = line.find('[');
    end = line.find(']');
    if (start != string::npos && end != string::npos) {
        string values = line.substr(start + 1, end - start - 1);
        stringstream valStream(values);
        while (getline(valStream, token, ';') && index < dragonCount) {
            dragons[index].ammoCounts = stoi(token);
            index++;
        }
    }
    
    // Read rider names: ["Hiccup", "Astrid", ...]
    if (!getline(ifs, line)) return 2;
    index = 0;
    start = line.find('"');
    while (start != string::npos && index < dragonCount) {
        size_t nameEnd = line.find('"', start + 1);
        if (nameEnd != string::npos) {
            dragons[index].riderNames = line.substr(start + 1, nameEnd - start - 1);
            index++;
            start = line.find('"', nameEnd + 1);
        } else {
            break;
        }
    }
    
    // Read number of dragons
    if (!getline(ifs, line)) return 2;
    N = stoi(line);
    
    // Validate input
    validateInput(N);
    
    // Calculate dragon damages based on temperament and ammo
    for (int i = 0; i < N; i++) {
        dragonDamages[i] = dragons[i].dragonTemperament * dragons[i].ammoCounts / 10;
    }
    
    ifs.close();
    return 1; // Success
}

// Task 2
string findKthStrongestDragon(Dragon dragons[], int dragonDamages[5], int N, int T)
{
    if (T < 1 || T > N) {
        return "None";
    }
    
    // Create array of indices to sort by damage
    int indices[MAX_DRAGONS];
    for (int i = 0; i < N; i++) {
        indices[i] = i;
    }
    
    // Sort indices by damage in descending order (bubble sort)
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (dragonDamages[indices[j]] < dragonDamages[indices[j + 1]]) {
                int temp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = temp;
            }
        }
    }
    
    // Return the T-th strongest dragon (T is 1-indexed)
    return dragons[indices[T - 1]].dragonNames;
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

void validateInput(int N)
{
    if (N <= 0 || N > MAX_DRAGONS) {
        cout << "Warning: Invalid number of dragons (" << N << ")" << endl;
    }
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
