// Code to find the minimum sum of any falling path through the matrix ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public: 
    // Method to find the minimum sum of any falling path, using recursion with memoization - O(N*N) & O(N*N)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();

        // Stores the result value
        int minPathSum = INT_MAX;

        // 2D memoization table
        vector<vector<int>> memory(N, vector<int>(N, INT_MIN));
        
        // Explore the falling path of minimum sum from each column of the first row
        for(int C = 0; C < N; ++C) {
            minPathSum = min(minPathSum, solveWithMemo(memory, grid, N, 0, C));
        }

        // Return the result value
        return minPathSum;
    }

private:
    // O(N + 3*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(C < 0 || C == N || R == N)
            return INT_MAX;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != INT_MIN)
            return memory[R][C];

        // There are always three possibilities to perform at each cell
        int moveToSameColumn = solveWithMemo(memory, grid, N, R+1, C);   // Is to move to the same column in the next row
        int moveToPrevColumn = solveWithMemo(memory, grid, N, R+1, C-1); // Is to move to the left column in the next row
        int moveToNextColumn = solveWithMemo(memory, grid, N, R+1, C+1); // Is to move to the right column in the next row

        // As we're striving for the minimum sum thus store the minimum element from all the possibilities
        int minElement = min({moveToSameColumn, moveToPrevColumn, moveToNextColumn});

        // Store the result value to the memoization table and then return it
        return memory[R][C] = grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }


    // O(N * 3^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(C < 0 || C == N || R == N)
            return INT_MAX;

        // There are always three possibilities to perform at each cell
        int moveToSameColumn = solveWithoutMemo(grid, N, R+1, C);   // Is to move to the same column in the next row
        int moveToPrevColumn = solveWithoutMemo(grid, N, R+1, C-1); // Is to move to the left column in the next row
        int moveToNextColumn = solveWithoutMemo(grid, N, R+1, C+1); // Is to move to the right column in the next row

        // As we're striving for the minimum sum thus store the minimum element from all the possibilities
        int minElement = min({moveToSameColumn, moveToPrevColumn, moveToNextColumn});
        
        // Return the result value
        return grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public: 
    // #1 Method to find the minimum sum of any falling path, using 2D tabulation - O(N*N) & O(N*N)
    int minFallingPathSum_V1(vector<vector<int>>& grid) {
        int N = grid.size();

        vector<vector<int>> dp(N+1, vector<int>(N+2, INT_MAX));
        
        for(int R = N-1; R >= 0; --R) {
            for(int C = N; C >= 1; --C) {
                int moveToSameColumn = dp[R+1][C];   
                int moveToPrevColumn = dp[R+1][C-1]; 
                int moveToNextColumn = dp[R+1][C+1]; 
                int minElement = min({moveToSameColumn, moveToPrevColumn, moveToNextColumn});
                dp[R][C] = grid[R][C-1] + (minElement == INT_MAX ? 0 : minElement);
            }
        }

        int minPathSum = INT_MAX;

        for(int C = 0; C < N; ++C) {
            minPathSum = min(minPathSum, dp[0][C+1]);
        }

        return minPathSum;
    }

    // #2 Method to find the minimum sum of any falling path, using 1D tabulation - O(N*N) & O(N)
    int minFallingPathSum_V2(vector<vector<int>>& grid) {
        int N = grid.size();

        vector<int> nextRow(N+2, INT_MAX), currRow(N+2, INT_MAX);
        
        for(int R = N-1; R >= 0; --R) {
            for(int C = N; C >= 1; --C) {
                int moveToSameColumn = nextRow[C];   
                int moveToPrevColumn = nextRow[C-1]; 
                int moveToNextColumn = nextRow[C+1]; 
                int minElement = min({moveToSameColumn, moveToPrevColumn, moveToNextColumn});
                currRow[C] = grid[R][C-1] + (minElement == INT_MAX ? 0 : minElement);
            }
            nextRow = currRow;
        }

        int minPathSum = INT_MAX;

        for(int C = 0; C < N; ++C) {
            minPathSum = min(minPathSum, currRow[C+1]);
        }

        return minPathSum;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the minimum sum of any falling path, using constant auxiliary space - O(N*N) & O(1)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();
        
        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveToSameColumn = grid[R+1][C];   
                int moveToPrevColumn = (C-1 >= 0) ? grid[R+1][C-1] : INT_MAX; 
                int moveToNextColumn = (C+1 < N) ? grid[R+1][C+1] : INT_MAX; 
                grid[R][C] += min({moveToSameColumn, moveToPrevColumn, moveToNextColumn});
            }
        }

        return *min_element(begin(grid[0]), end(grid[0]));
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-falling-path-sum/description/
