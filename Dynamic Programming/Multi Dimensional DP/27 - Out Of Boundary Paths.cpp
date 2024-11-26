// Code to find the total number of paths to move the ball out of the grid boundary from the cell (startRow, startColumn) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    const int MOD = 1e9+7;
    int M, N;

    // O(4^maxMove) & O(M+N)
    int solveWithoutMemo(int maxMove, int R, int C) {
        // Edge case: If the ball moves out of the grid boundary then you've one valid way
        if(R < 0 || C < 0 || R == M || C == N)
            return 1;

        // Edge case: If all the moves are exhausted then it's not possible to move the ball anymore
        if(maxMove == 0)
            return 0;

        // Stores the result value
        int numPaths = 0;

        // Explore all the 4 directions from the cell and update the result value each time
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            numPaths     = ((numPaths  % MOD) + solveWithoutMemo(maxMove - 1, reachRow, reachCol) % MOD);
        }

        // Return the result value
        return numPaths % MOD;
    }

    // O(4 * maxMove*M*N) & O(maxMove*M*N + M+N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int maxMove, int R, int C) {
        // Edge case: If the ball moves out of the grid boundary then you've one valid way
        if(R < 0 || C < 0 || R == M || C == N)
            return 1;

        // Edge case: If all the moves are exhausted then it's not possible to move the ball anymore
        if(maxMove == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[maxMove][R][C] != -1)
            return memory[maxMove][R][C];

        // Stores the result value
        int numPaths = 0;

        // Explore all the 4 directions from the cell and update the result value each time
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            numPaths     = ((numPaths  % MOD) + solveWithMemo(memory, maxMove - 1, reachRow, reachCol) % MOD);
        }

        // Store the result value to the memoization table and then return it
        return memory[maxMove][R][C] = numPaths % MOD;
    }

public:
    // Method to find the number of paths, using recursion with memoization - O(maxMove*M*N) & (maxMove*M*N)
    int findPaths(int m, int n, int maxMove, int startRow, int startCol) {
        M = m, N = n;
        vector<vector<vector<int>>> memory(maxMove + 1, vector<vector<int>>(M, vector<int>(N, -1)));
        return solveWithMemo(memory, maxMove, startRow, startCol);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    const int MOD = 1e9+7;

public:
    // Method to find the number of paths, using 3D tabulation - O(maxMove*M*N) & O(maxMove*M*N)
    int findPaths(int M, int N, int maxMove, int startRow, int startCol) {
        // 3D DP table
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M + 2, vector<int>(N + 2, 0)));

        /*
            dp[move][0][C]     - we're assuming index 0 as negative index
            dp[move][R][0]     - we're assuming index 0 as negative index
            dp[move][M + 1][C] - we're assuming index M+1 as Mth index 
            dp[move][R][N + 1] - we're assuming index N+1 as Nth index 
        */

        // Initialize the edge case: (R < 0 || R == M) If the ball moves out of the grid boundary then you've one valid way
        for(int move = 0; move <= maxMove; ++move) {
            for(int C = 0; C <= N+1; ++C) {
                dp[move][0][C]     = 1;
                dp[move][M + 1][C] = 1;
            }
        }

        // Initialize the edge case: (C < 0 || C == N) If the ball moves out of the grid boundary then you've one valid way
        for(int move = 0; move <= maxMove; ++move) {
            for(int R = 0; R <= M+1; ++R) {
                dp[move][R][0]     = 1;
                dp[move][R][N + 1] = 1;
            }
        }

        // Fill the rest of the table
        for(int move = 1; move <= maxMove; ++move) {
            for(int R = 1; R <= M; ++R) {
                for(int C = 1; C <= N; ++C) {
                    int numPaths = 0;
                    for(auto& dir : directions) {
                        int reachRow = R + dir[0];
                        int reachCol = C + dir[1];
                        if(reachRow >= 0 && reachCol >= 0 && reachRow <= M+1 && reachCol <= N+1) {
                            numPaths = ((numPaths % MOD) + dp[move - 1][reachRow][reachCol] % MOD);
                        }
                    }
                    dp[move][R][C] = numPaths % MOD;
                }
            }
        }

        // Return the result value
        return dp[maxMove][startRow + 1][startCol + 1];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix 
Link  : https://leetcode.com/problems/out-of-boundary-paths/description/
