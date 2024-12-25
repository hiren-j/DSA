// Code to find total number of paths available from top-left corner to bottom-right corner such that the XOR of all the values along the path is divisible by K ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    int N, M;

    // O(2^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C, int pathXOR) {
        // Edge case: If you walk outside of the grid at anytime then return 0
        if(R == N || C == M)
            return 0;

        // Edge case: If reached the bottom-right corner and the XOR of path is equal to K then return 1
        if(R == N-1 && C == M-1)
            return (pathXOR ^ grid[R][C]) == 0;
        
        // There are always two possibilities to perform at each cell
        int moveRight = solveWithoutMemo(grid, R, C+1, pathXOR ^ grid[R][C]); // Is to move right
        int moveDown  = solveWithoutMemo(grid, R+1, C, pathXOR ^ grid[R][C]); // Is to move down

        // Return the total number of paths available from this cell
        return (moveRight + moveDown) % MOD;
    }

    // O(2*N*M*16) & O(N*M*16 + N+M)
    int solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<int>>& grid, int R, int C, int pathXOR) {
        // Edge case: If you walk outside of the grid at anytime then return 0
        if(R == N || C == M)
            return 0;

        // Edge case: If reached the bottom-right corner and the XOR of path is equal to K then return 1
        if(R == N-1 && C == M-1)
            return (pathXOR ^ grid[R][C]) == 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp[R][C][pathXOR] != -1)
            return dp[R][C][pathXOR];
        
        // There are always two possibilities to perform at each cell
        int moveRight = solveWithMemo(dp, grid, R, C+1, pathXOR ^ grid[R][C]); // Is to move right
        int moveDown  = solveWithMemo(dp, grid, R+1, C, pathXOR ^ grid[R][C]); // Is to move down

        // Store the result value to the memoization table and then return it
        return dp[R][C][pathXOR] = (moveRight + moveDown) % MOD;
    }

public:
    // Method to find total number of such paths, using recursion with memoization - O(N*M) & O(N*M)
    int countPathsWithXorValue(vector<vector<int>>& grid, int K) {
        N = grid.size(), M = grid[0].size();
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(M, vector<int>(16, -1)));
        return solveWithMemo(dp, grid, 0, 0, K);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

public:
    // #1 Method to find total number of such paths, using 3D tabulation - O(N*M) & O(N*M)
    int countPathsWithXorValue_V1(vector<vector<int>>& grid, int K) {
        int N = grid.size(), M = grid[0].size(); 
        
        // 3D DP table
        vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(M+1, vector<int>(16, 0)));

        // Initialize the second edge case
        for(int pathXOR = 0; pathXOR < 16; ++pathXOR)
            dp[N-1][M-1][pathXOR] = (pathXOR ^ grid[N-1][M-1]) == 0;

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                for(int pathXOR = 0; pathXOR < 16; ++pathXOR) {
                    if(R == N-1 && C == M-1)
                        continue;
                    int moveRight = dp[R][C+1][pathXOR ^ grid[R][C]];
                    int moveDown  = dp[R+1][C][pathXOR ^ grid[R][C]];
                    dp[R][C][pathXOR] = (moveRight + moveDown) % MOD;
                }
            }
        }

        // Return the result value
        return dp[0][0][K];
    }

    // #2 Method to find the total number of such paths, using 2D tabulation - O(N*M) & O(M)
    int countPathsWithXorValue_V2(vector<vector<int>>& grid, int K) {
        int N = grid.size(), M = grid[0].size(); 

        // 2D DP tables
        vector<vector<int>> nextRow(M+1, vector<int>(16, 0)), idealRow(M+1, vector<int>(16, 0));        

        // Initialize the second edge case
        for(int pathXOR = 0; pathXOR < 16; ++pathXOR)
            idealRow[M-1][pathXOR] = (pathXOR ^ grid[N-1][M-1]) == 0;

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                for(int pathXOR = 0; pathXOR < 16; ++pathXOR) {
                    if(R == N-1 && C == M-1)
                        continue;
                    int moveRight = idealRow[C+1][pathXOR ^ grid[R][C]];
                    int moveDown  = nextRow[C][pathXOR ^ grid[R][C]];
                    idealRow[C][pathXOR] = (moveRight + moveDown) % MOD;
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[0][K];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Matrix | Dynamic Programming  
Link  : https://leetcode.com/problems/count-paths-with-the-given-xor-value/description/