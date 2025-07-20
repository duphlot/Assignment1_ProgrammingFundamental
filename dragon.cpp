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

// Task 1
int readFile(const string filename, Dragon dragons[], int (&dragonDamages)[5], int &N)
{
    if (filename.substr(filename.find_last_of(".") + 1) != "txt") {
        return 2; // File doesn't have .txt extension
    }

    ifstream ifs(filename);
    if (!ifs.is_open()){
        return 3; // File not found
    }

    string line;
    
    // First line: Read dragon names line: ["Toothless", "Stormfly", ...]
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

    // Second line: read dragon types line: ["Night Fury", "Deadly Nadder", ...]
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

    // Third line: read temperament values: [9; 8; 7; 7; 6]
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
    
    // Fourth line: read ammo counts: [3; 2; 5; 1; 4]
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

    // Fiveth line: read dragon damages: [100; 80; 90; 70; 95] 
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
    

    
    // Sixth line: read rider names: ["Hiccup", "Astrid", ...]
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
        return 4; // No line for N
    }

    N = stoi(line);
    ifs.close();

    if (dragonCount != N) return 5; // dragon count mismatch
    if (typeCount != N) return 6; // dragon type count mismatch
    if (tempCount != N) return 7; // dragon temperament count mismatch
    if (ammoCount != N) return 8; // dragon ammo count mismatch
    if (damageCount != 5) return 9; // dragon damage count mismatch
    if (riderCount != N) return 10; // dragon rider count mismatch
    
    // check invalid dragon names
    for (int i = 0; i < N; i++) 
        if (countSpecialCharacters(dragons[i].dragonNames)!=0) return (100 + i); 
    
    // check invalid type names
    for (int i=0; i < N; i++){
        int count = countSpecialCharacters(typeNames[i]);
        if (count != 0) return (500 + count);
    }

    // if valid type names, convert them to types
    for (int i = 0; i < N;i++){
        dragons[i].dragonTypes = typeNameToType(typeNames[i]);
    } 

    // check invalid rider names
    for (int i = 0; i < N; i++) {
        if (countBlankSpaces(dragons[i].riderNames) > 0) return (900 + i);
    }

    // check blank spaces in dragon names
    int countBlankInNames = 0;
    for (int i = 0; i < N; i++) {
        countBlankInNames += countBlankSpaces(dragons[i].dragonNames);
        if (countBlankInNames > 1) return (1000 + countBlankInNames);
    }

    // debug output
    for (int i = 0; i < dragonCount; i++) {
    cout << "Dragon " << i + 1 << ": " << dragons[i].dragonNames 
        << ", Type: " << dragons[i].dragonTypes 
        << ", Temperament: " << dragons[i].dragonTemperament 
        << ", Ammo: " << dragons[i].ammoCounts 
        << ", Rider: " << dragons[i].riderNames 
        << ", Damage: " << dragonDamages[i] << "\n";
    }

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
float calculateCompatibility(int warriorSkill, Dragon& dragon){
    return (float)(10 - abs(dragon.dragonTemperament - warriorSkill)) / 2.0f;
}

void compatibilityCheck(Dragon dragons[], string warriorName, int warriorSkill){
    for (int i = 0; i < N; i++) {
        float compatibility = calculateCompatibility(warriorSkill, dragons[i]);
        printCompatibilityTable(warriorName, dragons[i].dragonNames, compatibility);
    }
}

void printCompatibilityTable(string fighterName, string dragonName, float compatibility){
    static bool headerPrinted = false;
    if (!headerPrinted) {
        cout << "Warrior      Dragon        Compatibility    Review" << "\n";
        headerPrinted = true;
    }

    string result = (compatibility > 4) ? "Compatible" : "Not Compatible";

    cout << left << setw(13) << fighterName << setw(14) << dragonName
        << setw(17) << fixed << setprecision(2) << compatibility
        << result << "\n";
}

// Task 3.2
void buddyMatching(Dragon dragons[], string warriors[][3]){
    bool dragonUsed[MAX_DRAGONS];

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
    // TODO: Implement this function
}

// Task 5.1
int findriderSkill(string name,string warriors[][3]){
    for (int i = 0; i < N; i++) {
        if (warriors[i][0] == name) {
            return stoi(warriors[i][1]);
        }
    }
    return -1; // Not found
}

void fighterDamage(Dragon dragons[], string warriors[][3], int (&teamsDamage)[]){
    int temp = 0;
    for (int i = 0; i < N;i++){
        int ridersSkill = findriderSkill(warriors[i][0], warriors);
        
        int damage = (dragons[i].ammoCounts * dragons[i].dragonTemperament) + (ridersSkill * 5);
        dragonDamages[i] = damage;
        cout<<dragons[i].riderNames<<"-"<<dragons[i].dragonNames<<": damage = "<<damage<<"\n";
    }
}

// Task 5.2
void findHeritageLocation(int  map[10][10], int &heritageX, int &heritageY) {
    for (int i=0;i<10;i++){
        pair<int,int> minInRow = {map[i][0],0}, maxInCol = {map[0][i],0};
        for (int j=1;j<10;j++) minInRow = min(minInRow, {map[i][j],j});

        for (int j=0;j<10;j++) maxInCol = max(maxInCol, {map[j][minInRow.second],j});

        if (minInRow.first == maxInCol.first) {
            heritageX = i;
            heritageY = minInRow.second;
            return; 
        }
    }
}
void findKeyLocation(int map[10][10], int &keyX, int &keyY) {
    int prefixSum[11][11] = {0};

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            prefixSum[i][j] = map[i-1][j-1] + prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1];
        }
    }

    int maxSum = INT_MIN;
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            int currentSum = prefixSum[i+3][j+3] - prefixSum[i][j+3] - prefixSum[i+3][j] + prefixSum[i][j];
            if (currentSum > maxSum) {
                maxSum = currentSum;
                keyX = i + 1; 
                keyY = j + 1; 
            }
        }
    }
}

bool checkTimeIllusionDragon(int x,int y, int map[10][10]) {
    if (x != 9 && y != 9 && x != 0 && y != 0)  return 0;
    if (x == 9 || x == 0){
        for (int i = 0; i < 10; i++) 
            if (map[x][i] > map[x][y]) return 0;
    } else {
        for (int i = 0; i < 10; i++) 
            if (map[i][y] > map[x][y]) return 0;
    }
    return 1; 
}

bool checkChaosReversingDragon(int x,int y, int map[10][10]) {
    if (x == 0 || y == 0) return 0; 
    if (x == 9 || y == 9) return 0; 

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10) {
            if (map[nx][ny] > map[x][y]) return 0;
        }
    }
    return 1; 
}

int computeCost(int &x, int &y, int (*map)[10], int warriorDamage, int &HP){
    if (map[x][y] == 0) return 2;

    if (checkTimeIllusionDragon(x, y, map)) {
        if (warriorDamage < map[x][y]){
            HP-=2;
            map[x][y] = 0;
            cout<< "Time Illusion Dragon at (" << x << ", " << y << ")\n";
            if (x!=0) x--;
            else y = 0;
        } else map[x][y] = 0;
        return 10;
    }

    if (checkChaosReversingDragon(x, y, map)) {
        if (warriorDamage < map[x][y]){
            HP-=2;
            cout<< "Chaos Reversing Dragon at (" << x << ", " << y << ")\n";
            map[x][y] = 0;
            swap(x,y);
        } else map[x][y] = 0;
        return 10;
    }

    if (warriorDamage < map[x][y]){
        cout<< "Tiny Dragon at (" << x << ", " << y << ")\n";
        HP--;
    } 
    map[x][y] = 0;
    return 5;
}

void totalTime(int map[10][10], int warriorDamage, int HP) {
    int heritageX, heritageY, keyX, keyY;
    findHeritageLocation(map, heritageX, heritageY);
    findKeyLocation(map, keyX, keyY);

    cout<< "Heritage Location: (" << heritageX << ", " << heritageY << ")\n";
    cout<< "Key Location: (" << keyX << ", " << keyY << ")\n";
    
    int startX = 0, startY = 0, totalTime = 0;
    cout<<"Current position: ("<<startX<<","<<startY<<")\n";
    cout<<"Current total time: "<<totalTime<<"\n";
    totalTime = computeCost(startX, startY, map, warriorDamage, HP);

    int path[200][2];
    path[0][0] = startX;
    path[0][1] = startY;
    int temp = 0;
    int dir = 1; 
    while (startX != keyX || startY != keyY) {
        dir = (startX % 2 == 0) ? 1 : -1;
        if ((dir == 1 && startY < 9) || (dir == -1 && startY > 0)) startY += dir;
        else startX++;
        path[++temp][0] = startX;
        path[temp][1] = startY;
        cout << "Current position: (" << startX << "," << startY << ")\n";
        cout << "Current total time: " << totalTime << "\n";
        totalTime += computeCost(startX, startY, map, warriorDamage, HP);
    }

    if (heritageX < keyX) {
        totalTime += ((keyY + heritageX) + (keyX - heritageX) * 9) * 2;
        int curX = keyX, curY = keyY;
        while (curX != heritageX || curY != heritageY) {
            dir = (startX % 2 == 0) ? 1 : -1;
            if ((dir == 1 && startY < 9) || (dir == -1 && startY > 0)) startY += dir;
            else startX++;
            path[++temp][0] = curX;
            path[temp][1] = curY;
            if (curX == heritageX && curY == heritageY) break;
        }

    }
    else if (heritageX == keyX && heritageY < keyY) {
        totalTime += (keyY - heritageY) * 2;
        int curX = keyX, curY = keyY;
        while (curX != heritageX || curY != heritageY) {
            dir = (startX % 2 == 0) ? 1 : -1;
            if ((dir == 1 && startY < 9) || (dir == -1 && startY > 0)) startY += dir;
            else startX++;
            path[++temp][0] = curX;
            path[temp][1] = curY;
            if (curX == heritageX && curY == heritageY) break;
        }
    } else {
        while (startX != heritageX || startY != heritageY) {
            dir = (startX % 2 == 0) ? 1 : -1;
            if ((dir == 1 && startY < 9) || (dir == -1 && startY > 0)) startY += dir;
            else startX++;
            path[++temp][0] = startX;
            path[temp][1] = startY;
            totalTime += computeCost(startX, startY, map, warriorDamage, HP);
        }
    }

    cout<<"Total time: "<<totalTime<<"\n";
    cout<<"Remaining HP: "<<HP<<"\n";
    cout<<"Path: \n";
    for (int i = 0; i <= temp; i++) {
        cout<<"("<<path[i][0]<<","<<path[i][1]<<") ";
    }
    cout<<"\n";
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////