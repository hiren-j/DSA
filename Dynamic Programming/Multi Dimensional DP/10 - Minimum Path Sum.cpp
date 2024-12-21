// Code to find a path from top left to bottom right, which minimizes the sum of all numbers along its path ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the path having the minimized sum to reach the bottom-right cell, using recursion with memoization - O(N*M) & O(N*M)
    int minPathSum(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();
        vector<vector<int>> memory(N, vector<int>(M, -1));
        return solveWithMemo(memory, grid, N, M, 0, 0);
    }

private:
    // O(2*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If all the cells are exhausted then you can't reach the bottom-right corner hence return INT_MAX as a indication of it
        if(R == N || C == M)
            return INT_MAX;

        // Edge case: If reached the bottom-right corner then return the value of the cell as a valid indication of it
        if(R == N-1 && C == M-1)
            return grid[R][C];

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];

        // There are always two possibilities to perform at each cell
        int moveDown  = solveWithMemo(memory, grid, N, M, R+1, C); // Is to go down from it
        int moveRight = solveWithMemo(memory, grid, N, M, R, C+1); // Is to go right from it

        // As we're striving for the minimum sum thus store the minimum element from both the possibilities
        int minElement = min(moveDown, moveRight);

        // Store the result value to the memoization table and then return it
        return memory[R][C] = (minElement != INT_MAX) ? minElement + grid[R][C] : INT_MAX; 
    }

    // O(2^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If all the cells are exhausted then you can't reach the bottom-right corner hence return INT_MAX as a indication of it
        if(R == N || C == M)
            return INT_MAX;

        // Edge case: If reached the bottom-right corner then return the value of the cell as a valid indication of it
        if(R == N-1 && C == M-1)
            return grid[R][C];

        // There are always two possibilities to perform at each cell
        int moveDown  = solveWithoutMemo(grid, N, M, R+1, C); // Is to go down from it
        int moveRight = solveWithoutMemo(grid, N, M, R, C+1); // Is to go right from it

        // As we're striving for the minimum sum thus store the minimum element from both the possibilities
        int minElement = min(moveDown, moveRight);

        // Return the result value
        return (minElement != INT_MAX) ? minElement + grid[R][C] : INT_MAX; 
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #1 Class to implement the Bottom-up approach:
class BottomUp_V1 {
public:
    // #1 Method to find the path having the minimized sum to reach the bottom-right cell, using 2D tabulation - O(N*M) & O(N*M)
    int minPathSum_V1(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();

        // 2D DP table
        vector<vector<int>> dp(N+1, vector<int>(M+1, INT_MAX));

        // Initialize the edge case: If reached the bottom-right corner then return the value of the cell as a valid indication of it
        dp[N-1][M-1] = grid[N-1][M-1];

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                int moveDown   = dp[R+1][C]; 
                int moveRight  = dp[R][C+1]; 
                int minElement = min(moveDown, moveRight);                
                dp[R][C] = (minElement != INT_MAX) ? minElement + grid[R][C] : dp[R][C]; 
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the path having the minimized sum to reach the bottom-right cell, using 1D tabulation - O(N*M) & O(M)
    int minPathSum_V2(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();

        // 1D DP tables
        vector<int> nextRow(M+1, INT_MAX), currRow(M+1, INT_MAX);

        // Initialize the edge case: If reached the bottom-right corner then return the value of the cell as a valid indication of it
        currRow[M-1] = grid[N-1][M-1];

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                int moveDown   = nextRow[C]; 
                int moveRight  = currRow[C+1]; 
                int minElement = min(moveDown, moveRight);                
                currRow[C] = (minElement != INT_MAX) ? minElement + grid[R][C] : currRow[C]; 
            }
            nextRow = currRow;
        }

        // Return the result value
        return currRow[0];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Bottom-up approach:
class BottomUp_V2 {
    // Method to find the path having the minimized sum to reach the bottom-right cell, using constant auxiliary space - O(N*M) & O(1)
    int minPathSum(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();

        // When there's only one column in the grid then you can reach any cell through it's previous row only
        for(int R = 1; R < N; ++R) 
            grid[R][0] += grid[R-1][0];

        // When there's only one row in the grid then you can reach any cell through it's previous column only
        for(int C = 1; C < M; ++C) 
            grid[0][C] += grid[0][C-1];

        // When there are multiple rows and columns in the grid then you can reach any cell through it's previous row and previous column
        for(int R = 1; R < N; ++R) {
            for(int C = 1; C < M; ++C) {
                int moveDown  = grid[R-1][C]; 
                int moveRight = grid[R][C-1]; 
                grid[R][C] += min(moveDown, moveRight);
            }
        }

        // Return the result value
        return grid[N-1][M-1];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-path-sum/description/
