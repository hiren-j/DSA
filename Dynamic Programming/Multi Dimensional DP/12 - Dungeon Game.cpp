// Code to find the knight's minimum initial health so that he can rescue the princess ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the knight's minimum initial health, using recursion with memoization - O(N*M) & O(N*M)
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int N = dungeon.size(), M = dungeon[0].size();
        vector<vector<int>> memory(N, vector<int>(M, -1));
        return solveWithMemo(memory, dungeon, N, M, 0, 0);
    }
    
private:
    // O(2*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& dungeon, int N, int M, int R, int C) {
        // Edge case: If all the cells are exhausted then its not possible to play the game anymore
        if(R == N || C == M)
            // Requires to handle the minimum health correctly
            return INT_MAX;

        // Edge case: If reached the bottom-right corner then rescue the princess. Calcuate and return the minimum health required for the knight to defeat the demon of the current room or not a demon then he requires minimum of single health to live
        if(R == N-1 && C == M-1)
            return (dungeon[R][C] <= 0) ? -dungeon[R][C] + 1 : 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];

        // There are always two possibilities the knight can perform at each room
        int moveRight = solveWithMemo(memory, dungeon, N, M, R, C+1); // Is to move right
        int moveDown  = solveWithMemo(memory, dungeon, N, M, R+1, C); // Is to move down

        // Stores the minimum health required for the knight to live at the current room
        int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];

        // Ensure the knight dies or not, if dies then he must need single health to live at the current room 
        return memory[R][C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;
    }

    // O(2^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& dungeon, int N, int M, int R, int C) {
        // Edge case: If all the cells are exhausted then its not possible to play the game anymore
        if(R == N || C == M)
            // Requires to handle the minimum health correctly
            return INT_MAX;

        // Edge case: If reached the bottom-right corner then rescue the princess. Calcuate and return the minimum health required for the knight to defeat the demon of the current room or not a demon then he requires minimum of single health to live
        if(R == N-1 && C == M-1)
            return (dungeon[R][C] <= 0) ? -dungeon[R][C] + 1 : 1;

        // There are always two possibilities the knight can perform at each room
        int moveRight = solveWithoutMemo(dungeon, N, M, R, C+1); // Is to move right
        int moveDown  = solveWithoutMemo(dungeon, N, M, R+1, C); // Is to move down

        // Stores the minimum health required for the knight to live at the current room
        int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];

        // Ensure the knight dies or not, if dies then he must need single health to live at the current room 
        return (minHealthToLive <= 0) ? 1 : minHealthToLive;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the knight's minimum initial health, using 2D tabulation - O(N*M) & O(N*M)
    int calculateMinimumHP_V1(vector<vector<int>>& dungeon) {
        int N = dungeon.size(), M = dungeon[0].size();

        // 2D DP table
        vector<vector<int>> dp(N+1, vector<int>(M+1, INT_MAX));

        // Initialize the second edge case
        dp[N-1][M-1] = (dungeon[N-1][M-1] <= 0) ? -dungeon[N-1][M-1] + 1 : 1;

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(R == N-1 && C == M-1)
                    continue;
                int moveRight = dp[R][C+1]; 
                int moveDown  = dp[R+1][C]; 
                int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];
                dp[R][C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;   
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the knight's minimum initial health, using 1D tabulation - O(N*M) & O(M)
    int calculateMinimumHP_V2(vector<vector<int>>& dungeon) {
        int N = dungeon.size(), M = dungeon[0].size();

        // 1D DP tables
        vector<int> nextRow(M+1, INT_MAX), currRow(M+1, INT_MAX);

        // Initialize the second edge case
        currRow[M-1] = (dungeon[N-1][M-1] <= 0) ? -dungeon[N-1][M-1] + 1 : 1;

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(R == N-1 && C == M-1)
                    continue;
                int moveRight = currRow[C+1]; 
                int moveDown  = nextRow[C]; 
                int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];
                currRow[C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;   
            }
            nextRow = currRow;
        }

        // Return the result value
        return nextRow[0];
    }

    // #3 Method to find the knight's minimum initial health, using constant auxiliary space - O(N*M) & O(1)
    int calculateMinimumHP_V3(vector<vector<int>>& dungeon) {
        int N = dungeon.size(), M = dungeon[0].size();

        // Initialize the second edge case
        dungeon[N-1][M-1] = (dungeon[N-1][M-1] <= 0) ? -dungeon[N-1][M-1] + 1 : 1;

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(R == N-1 && C == M-1)
                    continue;
                int moveRight = (C+1 < M) ? dungeon[R][C+1] : INT_MAX; 
                int moveDown  = (R+1 < N) ? dungeon[R+1][C] : INT_MAX; 
                int minHealthToLive = min(moveRight, moveDown) - dungeon[R][C];
                dungeon[R][C] = (minHealthToLive <= 0) ? 1 : minHealthToLive;   
            }
        }

        // Return the result value
        return dungeon[0][0];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/dungeon-game/description/
