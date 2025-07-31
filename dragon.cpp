#include "dragon.h"

// ***
// If you don't want to lose a LOT of points, please don't add any libraries here. T_T
// ***

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// hong duyen

Dragon dragons[MAX_DRAGONS];
int dragonDamages[5] = {0, 0, 0, 0, 0};
int N = 0;
int path[200][2];
int pathLen = 0;

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
    for (char c : name)
        if (!isalnum(c) && c != ' ' && c != '-' && c != '_') count++;
    return count;
}

int countBlankSpaces(string name) {
    int count = 0;
    for (int i=1;i<name.length();i++)
        if (name[i] == ' ' && name[i-1] == ' ') count++;
    return count;
}

bool checkMissLine(ifstream &ifs, string &line) {
    if (!getline(ifs, line)){
        ifs.close();
        return true;
    } 
    return false;
}

// Task 1
int readFile(const string filename, Dragon dragons[], int (&dragonDamages)[5], int &N){
    if (filename.substr(filename.find_last_of(".") + 1) != "txt") return 2; 

    ifstream ifs(filename);
    int dragonCount = 0;
    string line;
    string typeNames[MAX_DRAGONS];
    int typeCount = 0;
    int tempCount = 0;
    int ammoCount = 0;
    int damageCount = 0;
    int riderCount = 0;
    if (!ifs.is_open()) return 3;

    checkMissLine(ifs, line);
    
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
    if (checkMissLine(ifs, line)) return 4;

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

    if (checkMissLine(ifs, line)) return 4;

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
    
    if (checkMissLine(ifs, line)) return 4;
    
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

    if (checkMissLine(ifs, line)) return 4;

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
    
    if (checkMissLine(ifs, line)) return 4;

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

    if (checkMissLine(ifs, line)) return 4;

    N = stoi(line);
    ifs.close();

    if (dragonCount != N) return 5;
    if (typeCount != N) return 6; 
    if (tempCount != N) return 7; 
    if (ammoCount != N) return 8; 
    if (damageCount != 5) return 9; 
    if (riderCount != N) return 10; 

    for (int i = 0; i < N; i++) 
        if (countSpecialCharacters(dragons[i].dragonNames)!=0) return (100 + i); 
    
    int count = 0;
    for (int i=0; i < N; i++){
        count += countSpecialCharacters(typeNames[i]);
    } if (count != 0) return (500 + count);

    for (int i = 0; i < N;i++){
        dragons[i].dragonTypes = typeNameToType(typeNames[i]);
    } 

    for (int i = 0; i < N; i++) {
        if (countBlankSpaces(dragons[i].riderNames) > 0) return (900 + i);
    }

    int countBlankInNames = 0;
    for (int i = 0; i < N; i++) {
        countBlankInNames += countBlankSpaces(dragons[i].dragonNames);
    }if (countBlankInNames > 1) return (1000 + countBlankInNames);
    return 1; 
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
    return (10 - abs(dragon.dragonTemperament - warriorSkill)) / 2.0;
}

void compatibilityCheck(Dragon dragons[], string warriorName, int warriorSkill){
    cout << "Warrior      Dragon        Compatibility    Review" << endl;

    for (int i = 0; i < N; i++) {
        float compatibility = calculateCompatibility(warriorSkill, dragons[i]);
        printCompatibilityTable(warriorName, dragons[i].dragonNames, compatibility);
    }
}

void printCompatibilityTable(string fighterName, string dragonName, float compatibility){
    string result = (compatibility > 4) ? "Compatible" : "Not Compatible";

    cout << left << setw(13) << fighterName << setw(14) << dragonName
        << setw(17) << fixed << setprecision(2) << compatibility
        << result << "\n";
}

// Task 3.2
void buddyMatching(Dragon dragons[], string warriors[][3]){
    cout << "Warrior      Dragon        Compatibility    Review" << endl;
    bool dragonUsed[MAX_DRAGONS];

    for (int i = 0; i < N; i++) {
        string warriorName = warriors[i][0];
        int warriorSkill = stoi(warriors[i][1]);
        
        int bestDragonIndex = -1;
        float bestCompatibility = 0;
        
        for (int j = 0; j < N; j++) {
            if (!dragonUsed[j]) {
                float compatibility = calculateCompatibility(warriorSkill, dragons[j]);
                if (compatibility > bestCompatibility && compatibility > 4) {
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
int getAreaID(int rows,int cols){
    return (rows + cols) % 5;
}

int timeFromStartToArea(int x,int y){
    return (1 + (x + y * 2)) * 5;
}

int timeFromAreaToStart(int x,int y){
    return abs((x + y * 2) -1) * 5;
}

int computeTime(int map[10][10], int warriorID){
    int time = 0;
    int temp = 0;
    int dir = 1; 
    int finalAnswer = 0, tempAnswer = 0;

    int currentX = 0, currentY = 0;
    bool checkStart = false;

    while (currentX != 9 || currentY != 0) {
        if (checkStart) {
            tempAnswer +=  timeFromAreaToStart(currentX,currentY);
            checkStart = false;
        }

        dir = (currentX % 2 == 0) ? 1 : -1;
        if (dir == 1) { 
            if (currentY < 9) currentY++;
            else currentX++;
        } else { 
            if (currentY > 0) currentY--;
            else currentX++;
        }

        if (map[currentX][currentY] == warriorID && warriorID != getAreaID(currentX, currentY)) {
            tempAnswer += timeFromAreaToStart(currentX, currentY) + 5;
            checkStart = true;
        } else tempAnswer += 5;
    }

    return tempAnswer;
}

void computeChallengeTime(string warriors[][3], int map[10][10]){
    N = 5;
    cout << left << setw(15) << "Warrior" << "Total time (secs)" << endl;
    pair<int,int> arrayTime[20];
    for (int i=0;i<N;i++){
        string warriorName = warriors[i][0];
        int warriorID = stoi(warriors[i][2]);
        int time = computeTime(map, warriorID) + 5;
        arrayTime[i] = {time, i};
    }

    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (arrayTime[i].first < arrayTime[j].first){
                swap(arrayTime[i], arrayTime[j]);
            }
        }
    }
    int temp = min(4, N);
    for (int i=0;i<temp;i++){
        cout << left << setw(15) << warriors[arrayTime[i].second][0] << arrayTime[i].first << endl;
    }

}

// Task 5.1
void fighterDamage(Dragon dragons[], string warriors[][3], int teamsDamage[]){
    int temp = 0;
    for (int i = 0; i < N;i++){
        int ridersSkill = stoi(warriors[i][1]);
        int damage = (dragons[i].ammoCounts * dragonDamages[dragons[i].dragonTypes-1]) + (ridersSkill * 5);
        teamsDamage[i] = damage;
        cout<<warriors[i][0]<<"-"<<dragons[i].dragonNames<<": damage = "<<damage<<"\n";
    }
}

// Task 5.2
void findHeritageLocation(int map[10][10], int &heritageX, int &heritageY) {
    for (int i = 0; i < 10; ++i) {
        int minCol = 0;
        for (int j = 1; j < 10; ++j) {
            if (map[i][j] < map[i][minCol]) minCol = j;
        }
        int maxRow = 0;
        for (int k = 1; k < 10; ++k) {
            if (map[k][minCol] > map[maxRow][minCol]) maxRow = k;
        }
        if (i == maxRow) {
            heritageX = i;
            heritageY = minCol;
            return;
        }
    }
}

void findKeyLocation(int map[10][10], int &keyX, int &keyY) {
    int prefixSum[11][11] = {};
    for (int i = 1; i <= 10; ++i)
        for (int j = 1; j <= 10; ++j)
            prefixSum[i][j] = map[i-1][j-1] + prefixSum[i-1][j] + prefixSum[i][j-1] - prefixSum[i-1][j-1];
    int maxSum = INT_MIN;
    for (int i = 0; i <= 7; ++i) {
        for (int j = 0; j <= 7; ++j) {
            int sum = prefixSum[i+3][j+3] - prefixSum[i][j+3] - prefixSum[i+3][j] + prefixSum[i][j];
            if (sum > maxSum) {
                maxSum = sum;
                keyX = i + 1;
                keyY = j + 1;
            }
        }
    }
}

bool checkTimeIllusionDragon(int x, int y, int map[10][10]) {
    if (!(x == 0 || x == 9 || y == 0 || y == 9)) return false;
    int val = map[x][y];
    for (int i = 0; i < 10; ++i)
        if (map[0][i] > val || map[9][i] > val || map[i][0] > val || map[i][9] > val)
            return false;
    return true;
}

bool checkChaosReversingDragon(int x, int y, int map[10][10]) {
    if (x == 0 || y == 0 || x == 9 || y == 9) return false;
    static const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && map[nx][ny] > map[x][y])
            return false;
    }
    return true;
}

int computeCost(int &x, int &y, int map[10][10], int warriorDamage, int &HP, int originalMap[10][10], int reversingDragonX, int reversingDragonY, int keyX, int keyY, int heritageX, int heritageY) {
    if (map[x][y] == 0) return 2;
    if (checkTimeIllusionDragon(x, y, originalMap)) {
        if (warriorDamage < map[x][y]) {
            HP -= 2;
            map[x][y] = 0;
            // cout << "Time Illusion Dragon at (" << x << ", " << y << ")\n";
            if (x != 0) --x;
            else y = 0;
            path[++pathLen][0] = x;
            path[pathLen][1] = y;
        } else {
            map[x][y] = 0;
        }
        return 10;
    }
    if (x == reversingDragonX && y == reversingDragonY) {
        if (warriorDamage < map[x][y]) {
            HP -= 2;
            map[x][y] = 0;
            swap(x, y);
            path[++pathLen][0] = x;
            path[pathLen][1] = y;
        } else {
            map[x][y] = 0;
        }
        return 10;
    }
    if (warriorDamage < map[x][y]) {
        --HP;
    }
    map[x][y] = 0;
    if ((x == keyX && y == keyY) || (x == heritageX && y == heritageY)) return 2;
    return 5;
}

void findReversingDragonLocation(int map[10][10], int &x, int &y) {
    int curX = x, curY = y;
    while (curX != 9 || curY != 9) {
        int dir = (curX % 2 == 0) ? 1 : -1;
        if (dir == 1) {
            if (curY < 9) ++curY;
            else ++curX;
        } else {
            if (curY > 0) --curY;
            else ++curX;
        }
        if (checkChaosReversingDragon(curX, curY, map)) {
            x = curX;
            y = curY;
        }
    }
}

void totalTime(int map[10][10], int warriorDamage, int HP) {
    int heritageX, heritageY, keyX, keyY;
    int originalMap[10][10];
    memcpy(originalMap, map, sizeof(originalMap));
    findHeritageLocation(map, heritageX, heritageY);
    findKeyLocation(map, keyX, keyY);
    int reversingDragonX = 0, reversingDragonY = 0;
    findReversingDragonLocation(map, reversingDragonX, reversingDragonY);
    pathLen = 0;
    int startX = 0, startY = 0;
    int total = computeCost(startX, startY, map, warriorDamage, HP, originalMap, reversingDragonX, reversingDragonY, keyX, keyY, heritageX, heritageY);
    path[0][0] = startX;
    path[0][1] = startY;

    while (startX != keyX || startY != keyY) {
        int dir = (startX % 2 == 0) ? 1 : -1;
        bool goingForward = (dir == 1)
            ? (startX < keyX || (startX == keyX && startY < keyY))
            : (startX < keyX || (startX == keyX && startY > keyY));
        if (goingForward) {
            if ((dir == 1 && startY < 9) || (dir == -1 && startY > 0)) startY += dir;
            else ++startX;
        } else {
            if ((dir == -1 && startY < 9) || (dir == 1 && startY > 0)) startY -= dir;
            else --startX;
            
        }
        path[++pathLen][0] = startX;
        path[pathLen][1] = startY;
        total += computeCost(startX, startY, map, warriorDamage, HP, originalMap, reversingDragonX, reversingDragonY, keyX, keyY, heritageX, heritageY);
        if (startX == keyX && startY == keyY) break;
    }

    while (startX != heritageX || startY != heritageY) {
        int dir = (startX % 2 == 0) ? 1 : -1;
        bool goingForward = (dir == 1)
            ? (startX < heritageX || (startX == heritageX && startY < heritageY))
            : (startX < heritageX || (startX == heritageX && startY > heritageY));
        if (goingForward) {
            if ((dir == 1 && startY < 9) || (dir == -1 && startY > 0)) startY += dir;
            else ++startX;
        } else {
            if ((dir == -1 && startY < 9) || (dir == 1 && startY > 0)) startY -= dir;
            else --startX;
            
        }
        path[++pathLen][0] = startX;
        path[pathLen][1] = startY;
        total += computeCost(startX, startY, map, warriorDamage, HP, originalMap, reversingDragonX, reversingDragonY, keyX, keyY, heritageX, heritageY);
        if (startX == heritageX && startY == heritageY) break;
    }

    cout << "Total time: " << total << " (sec)" << "\n";
    cout << "Remaining HP: " << HP << "\n";
    cout << "Path: ";
    for (int i = 0; i <= pathLen; ++i) {
        cout << "(" << path[i][0] << "," << path[i][1] << ")";
    }
    cout << "\n";
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
