// Code to find the maximum number of cherries collected by both the robots by following the mentioned rules ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;

    // O(9^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C1, int C2) {
        // Edge case: When all the cells are exhausted then its not possible to collect more cherries
        if(C1 < 0 || C2 < 0 || C1 == M || C2 == M || R == N)
            return 0;

        // If both the robots are not at same column then collect the cherries from both of them, else collect it from any one robot
        int currCherries = (C1 != C2 ? grid[R][C1] + grid[R][C2] : grid[R][C1]);

        // Stores the maximum number of cherries collected by any one robot
        int maxFromAll = 0;

        // Explore all the 3 possibilities of robot2 from each possibility of robot1
        for(int dir1 = -1; dir1 <= 1; ++dir1) 
            for(int dir2 = -1; dir2 <= 1; ++dir2) 
                maxFromAll = max(maxFromAll, solveWithoutMemo(grid, R + 1, C1 + dir1, C2 + dir2));

        // Return the result value
        return maxFromAll + currCherries;
    }

    // O(9*N*M*M) & O(N*M*M + N+M)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<vector<int>>& grid, int R, int C1, int C2) {
        // Edge case: When all the cells are exhausted then its not possible to collect more cherries
        if(C1 < 0 || C2 < 0 || C1 == M || C2 == M || R == N)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C1][C2] != -1)
            return memory[R][C1][C2];

        // If both the robots are not at same column then collect the cherries from both of them, else collect it from any one robot
        int currCherries = (C1 != C2 ? grid[R][C1] + grid[R][C2] : grid[R][C1]);

        // Stores the maximum number of cherries collected by any one robot
        int maxFromAll = 0;

        // Explore all the 3 possibilities of robot2 from each possibility of robot1
        for(int dir1 = -1; dir1 <= 1; ++dir1) 
            for(int dir2 = -1; dir2 <= 1; ++dir2) 
                maxFromAll = max(maxFromAll, solveWithMemo(memory, grid, R + 1, C1 + dir1, C2 + dir2));

        // Store the result value to the memoization table and then return it
        return memory[R][C1][C2] = maxFromAll + currCherries;
    }


public:
    // Method to find the maximum number of cherries collection, using recursion with memoization - (N*M*M) & O(N*M*M)
    int cherryPickup(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();
        vector<vector<vector<int>>> memory(N, vector<vector<int>>(M, vector<int>(M, -1)));
        return solveWithMemo(memory, grid, 0, 0, M - 1);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum number of cherries collection, using 3D tabulation - (N*M*M) & O(N*M*M)
    int cherryPickup_V1(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();

        // 3D DP table
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(M + 2, vector<int>(M + 2, 0)));

        // Fill the table
        for(int R = N-1; R >= 0; --R) {
            for(int C1 = M; C1 >= 1; --C1) {
                for(int C2 = 1; C2 <= M; ++C2) {
                    int currCherries = (C1 != C2 ? grid[R][C1 - 1] + grid[R][C2 - 1] : grid[R][C1 - 1]);
                    int maxFromAll = 0;
                    for(int dir1 = -1; dir1 <= 1; ++dir1) {
                        for(int dir2 = -1; dir2 <= 1; ++dir2) {
                            maxFromAll = max(maxFromAll, dp[R + 1][C1 + dir1][C2 + dir2]);
                        } 
                    }
                    dp[R][C1][C2] = maxFromAll + currCherries;
                }
            }
        }

        // Return the result value
        return dp[0][1][M];
    }

    // #2 Method to find the maximum number of cherries collection, using 2D tabulation - (N*M*M) & O(M*M)
    int cherryPickup_V2(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();

        // 2D DP tables
        vector<vector<int>> nextRow(M + 2, vector<int>(M + 2, 0)), idealRow(M + 2, vector<int>(M + 2, 0));

        // Fill the table
        for(int R = N-1; R >= 0; --R) {
            for(int C1 = M; C1 >= 1; --C1) {
                for(int C2 = 1; C2 <= M; ++C2) {
                    int currCherries = (C1 != C2 ? grid[R][C1 - 1] + grid[R][C2 - 1] : grid[R][C1 - 1]);
                    int maxFromAll = 0;
                    for(int dir1 = -1; dir1 <= 1; ++dir1) {
                        for(int dir2 = -1; dir2 <= 1; ++dir2) {
                            maxFromAll = max(maxFromAll, nextRow[C1 + dir1][C2 + dir2]);
                        } 
                    }
                    idealRow[C1][C2] = maxFromAll + currCherries;
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[1][M];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/cherry-pickup-ii/description/
