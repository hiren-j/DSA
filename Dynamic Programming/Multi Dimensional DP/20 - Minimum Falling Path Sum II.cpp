// Code to find the minimum sum of a falling path with non-zero shifts ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum sum of a falling path with non zero shifts, using recursion with memoization - O(N^3) & O(N^2)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, grid, n, 0, -1);
    }

private:
    // O(N*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int n, int currRow, int skipColumn) {
        // Edge case: If all the rows are exhausted then you can't pick more elements
        if(currRow == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[currRow][skipColumn + 1] != -1)
            return memory[currRow][skipColumn + 1];

        // Stores the result value
        int resultSum = INT_MAX;

        // Explore all the falling paths of non-zero shifts and update the result by the minimum value 
        for(int currColumn = 0; currColumn < n; ++currColumn) {
            if(currColumn != skipColumn) {
                int pathSum = grid[currRow][currColumn] + solveWithMemo(memory, grid, n, currRow + 1, currColumn);
                resultSum   = min(resultSum, pathSum);
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[currRow][skipColumn + 1] = resultSum;
    }

    // O(N^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int n, int currRow, int skipColumn) {
        // Edge case: If all the rows are exhausted then you can't pick more elements
        if(currRow == n)
            return 0;

        // Stores the result value
        int resultSum = INT_MAX;

        // Explore all the falling paths of non-zero shifts and update the result by the minimum value 
        for(int currColumn = 0; currColumn < n; ++currColumn) {
            if(currColumn != skipColumn) {
                int pathSum = grid[currRow][currColumn] + solveWithoutMemo(grid, n, currRow + 1, currColumn);
                resultSum   = min(resultSum, pathSum);
            }
        }

        // Return the result value
        return resultSum;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // #1 Method to find the minimum sum of a falling path with non zero shifts, using 2D tabulation - O(N^3) & O(N^2)
    int minFallingPathSum_V1(vector<vector<int>>& grid) {
        int n = grid.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));

        // Initialize the edge case: If all the rows are exhausted then you can't pick more elements
        for(int skipColumn = 0; skipColumn <= n; ++skipColumn)
            dp[n][skipColumn] = 0;

        // Fill the rest of the table
        for(int currRow = n-1; currRow >= 0; --currRow) {
            for(int skipColumn = n-1; skipColumn >= -1; --skipColumn) {
                int resultSum = INT_MAX;
                for(int currColumn = 0; currColumn < n; ++currColumn) {
                    if(currColumn != skipColumn) {
                        int pathSum = grid[currRow][currColumn] + dp[currRow + 1][currColumn + 1];
                        resultSum   = min(resultSum, pathSum);
                    }
                }
                dp[currRow][skipColumn + 1] = resultSum;
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the minimum sum of a falling path with non zero shifts, using 1D tabulation - O(N^3) & O(N)
    int minFallingPathSum_V2(vector<vector<int>>& grid) {
        int n = grid.size();

        // 1D DP tables
        vector<int> nextRow(n + 1, INT_MAX), idealRow(n + 1, INT_MAX);

        // Initialize the edge case: If all the rows are exhausted then you can't pick more elements
        for(int skipColumn = 0; skipColumn <= n; ++skipColumn)
            nextRow[skipColumn] = 0;

        // Fill the rest of the table
        for(int currRow = n-1; currRow >= 0; --currRow) {
            for(int skipColumn = n-1; skipColumn >= -1; --skipColumn) {
                int resultSum = INT_MAX;
                for(int currColumn = 0; currColumn < n; ++currColumn) {
                    if(currColumn != skipColumn) {
                        int pathSum = grid[currRow][currColumn] + nextRow[currColumn + 1];
                        resultSum   = min(resultSum, pathSum);
                    }
                }
                idealRow[skipColumn + 1] = resultSum;
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[0];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp_V2 {
public:
    // Method to find the minimum sum of a falling path with non zero shifts, using constant auxiliary space - O(N^3) & O(1)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();

        // Suppose you're on a cell and from it you could move to any non-adjacent cell in the next row. So, i could say that all we need is the minimum element from the non-adjacent columns of the next row
        for(int currRow = n-2; currRow >= 0; --currRow) {
            for(int currColumn = 0; currColumn < n; ++currColumn) {
                int minElement = INT_MAX;
                for(int index = 0; index < n; ++index) {
                    if(index != currColumn) {
                        minElement = min(minElement, grid[currRow + 1][index]);
                    }
                }
                grid[currRow][currColumn] += minElement;
            }
        }

        // Return the result value
        return *min_element(begin(grid[0]), end(grid[0]));
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-falling-path-sum-ii/description/?envType=daily-question&envId=2024-04-26
