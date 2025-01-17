// Code to find the minimum path sum from top to bottom in a triangle ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum path sum from top to bottom, using recursion with memoization - O(N*N) & O(N*N)
    int minimumTotal(vector<vector<int>>& triangle) {
        int N = triangle.size();
        vector<vector<int>> memory(N-1, vector<int>(N-1, -1));
        return solveWithMemo(memory, triangle, N, 0, 0);
    }

private:
    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& triangle, int N, int R, int C) {
        // Edge case: If you reached the last row then return the value of the cell you are on
        if(R == N-1)
            return triangle[R][C];

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];

        // There are always two possibilities to perform at each cell
        int moveToSameColumn = solveWithMemo(memory, triangle, N, R+1, C);   // Is to move to the same column in the next row
        int moveToNextColumn = solveWithMemo(memory, triangle, N, R+1, C+1); // Is to move to the next column in the next row

        // Store the result value to the memoization table and then return it
        return memory[R][C] = triangle[R][C] + min(moveToSameColumn, moveToNextColumn);
    }
    
    // O(2^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& triangle, int N, int R, int C) {
        // Edge case: If you reached the last row then return the value of the cell you are on
        if(R == N-1)
            return triangle[R][C];

        // There are always two possibilities to perform at each cell
        int moveToSameColumn = solveWithoutMemo(triangle, N, R+1, C);   // Is to move to the same column in the next row
        int moveToNextColumn = solveWithoutMemo(triangle, N, R+1, C+1); // Is to move to the next column in the next row

        // As we're striving for the minimum sum thus add the minimum element from both the possibilities
        return triangle[R][C] + min(moveToSameColumn, moveToNextColumn);
    }
};  

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // #1 Method to find the minimum path sum from top to bottom, using 2D tabulation - O(N*N) & O(N*N)
    int minimumTotal_V1(vector<vector<int>>& triangle) {
        int N = triangle.size();

        // 2D DP table
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // Initialize the edge case: If you reached the last row then return the value of the cell you are on
        for(int C = 0; C < N; ++C)
            dp[N-1][C] = triangle[N-1][C];

        // Fill the rest of the table
        for(int R = N-2; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameColumn = dp[R+1][C];   
                int moveToNextColumn = dp[R+1][C+1]; 
                dp[R][C] = triangle[R][C] + min(moveToSameColumn, moveToNextColumn);
            }
        }

        // Return the result value
        return dp[0][0];    
    }
    // Note: This solution is using additional memory blocks which results in a memory waste

    // #2 Method to find the minimum path sum from top to bottom, using 2D tabulation - O(N*N) & O(N*N)
    int minimumTotal_V2(vector<vector<int>>& triangle) {
        int N = triangle.size();

        // 2D DP table
        vector<vector<int>> dp(N); 

        // Initialize the last row
        dp[N-1] = triangle[N-1];

        // Fill the rest of the table
        for(int R = N-2; R >= 0; --R) {
            dp[R].resize(R+1);
            for(int C = R; C >= 0; --C) {
                int moveToSameColumn = dp[R+1][C];   
                int moveToNextColumn = dp[R+1][C+1]; 
                dp[R][C] = triangle[R][C] + min(moveToSameColumn, moveToNextColumn);
            }
        }

        // Return the result value
        return dp[0][0];    
    }

    // #3 Method to find the minimum path sum from top to bottom, using 1D tabulation - O(N*N) & O(N)
    int minimumTotal_V3(vector<vector<int>>& triangle) {
        int N = triangle.size();

        vector<int> nextRow(N, 0);
        nextRow = triangle[N-1];

        for(int R = N-2; R >= 0; --R) {
            vector<int> currRow(R+1);
            for(int C = R; C >= 0; --C) {
                int moveToSameColumn = nextRow[C];   
                int moveToNextColumn = nextRow[C+1]; 
                currRow[C] = triangle[R][C] + min(moveToSameColumn, moveToNextColumn);
            }
            nextRow = currRow;
        }

        return nextRow[0];    
    }

    // #4 Method to find the minimum path sum from top to bottom, using constant auxiliary space - O(N*N) & O(1)
    int minimumTotal_V4(vector<vector<int>>& triangle) {
        int N = triangle.size();

        for(int R = N-2; R >= 0; --R) {
            for(int C = R; C >= 0; --C) {
                int moveToSameColumn = triangle[R+1][C];   
                int moveToNextColumn = triangle[R+1][C+1]; 
                triangle[R][C] += min(moveToSameColumn, moveToNextColumn);
            }
        }

        return triangle[0][0];    
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/triangle/
