// Code to find the total number of paths you can take from the points (X, Y) to reach the origin (0, 0) ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

public:
    // Method to find the total number of paths from points to the origin, using recursion with memoization - O(X*Y) & O(X*Y)
    int numPaths(int X, int Y) {
        vector<vector<int>> memory(X + 1, vector<int>(Y + 1, -1));
        return solveWithMemo(memory, X, Y);
    }

private:    
    // O(2*X*Y) & O(X*Y + X+Y)
    int solveWithMemo(vector<vector<int>>& memory, int X, int Y) {
        // Edge case: If the points reaches the origin (0, 0) then you've one valid path
        if(X == 0 && Y == 0)
            return 1;
        
        // Edge case: If any of the point becomes negative then you've no valid path
        if(X < 0 || Y < 0)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[X][Y] != -1)
            return memory[X][Y];

        // There are always two possibilites to perform at each step
        int numPathsFromX = solveWithMemo(memory, X - 1, Y); // Is to move one-step to the up-side 
        int numPathsFromY = solveWithMemo(memory, X, Y - 1); // Is to move one-step to the left-side 

        // Store the result value to the memoization table and then return it
        return memory[X][Y] = (numPathsFromX + numPathsFromY) % MOD;
    }
    
    // O(2^(X*Y)) & O(X+Y)
    int solveWithoutMemo(int X, int Y) {
        // Edge case: If the points reaches the origin (0, 0) then you've one valid path
        if(X == 0 && Y == 0)
            return 1;
        
        // Edge case: If any of the point becomes negative then you've no valid path
        if(X < 0 || Y < 0)
            return 0;

        // There are always two possibilites to perform at each step
        int numPathsFromX = solveWithoutMemo(X - 1, Y); // Is to move one-step to the up-side 
        int numPathsFromY = solveWithoutMemo(X, Y - 1); // Is to move one-step to the left-side 

        // Return the result value
        return (numPathsFromX + numPathsFromY) % MOD;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
    const int MOD = 1e9+7;

public:
    // #1 Method to find the total number of paths from points to the origin, using 2D tabulation - O(X*Y) & O(X*Y)
    int numPaths_V1(int X, int Y) {
        // 2D DP table
        vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

        // Logically when the value of X is zero then for any value of Y you've only one valid path
        for(int stepY = 0; stepY <= Y; ++stepY)
            dp[0][stepY] = 1;

        // Logically when the value of Y is zero then for any value of X you've only one valid path
        for(int stepX = 0; stepX <= X; ++stepX)
            dp[stepX][0] = 1;

        // Fill the rest of the table
        for(int stepX = 1; stepX <= X; ++stepX) {
            for(int stepY = 1; stepY <= Y; ++stepY) {
                int numPathsFromX = dp[stepX - 1][stepY];  
                int numPathsFromY = dp[stepX][stepY - 1];  
                dp[stepX][stepY]  = (numPathsFromX + numPathsFromY) % MOD;
            }
        }

        // Return the result value
        return dp[X][Y];
    }

    // #2 Method to find the total number of paths from points to the origin, using 2D tabulation - O(X*Y) & O(X*Y)
    int numPaths_V2(int X, int Y) {
        // 2D DP table: Suppose you're on a cell and that cell is also a destination cell then you've only one valid path it's because you're already on the cell. So, initially fill all the cells by value one
        vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 1));

        // Fill the rest of the table
        for(int stepX = 1; stepX <= X; ++stepX) {
            for(int stepY = 1; stepY <= Y; ++stepY) {
                int numPathsFromX = dp[stepX - 1][stepY];  
                int numPathsFromY = dp[stepX][stepY - 1];  
                dp[stepX][stepY]  = (numPathsFromX + numPathsFromY) % MOD;
            }
        }

        // Return the result value
        return dp[X][Y];
    }

    // #3 Method to find the total number of paths from points to the origin, using 1D tabulation - O(X*Y) & O(Y)
    int numPaths_V3(int X, int Y) {
        vector<int> prevRow(Y + 1, 1), currRow(Y + 1, 1);

        for(int stepX = 1; stepX <= X; ++stepX) {
            for(int stepY = 1; stepY <= Y; ++stepY) {
                int numPathsFromX = prevRow[stepY];  
                int numPathsFromY = currRow[stepY - 1];  
                currRow[stepY] = (numPathsFromX + numPathsFromY) % MOD;
            }
            prevRow = currRow;
        }

        return currRow[Y];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming | Matrix
Link  : https://www.geeksforgeeks.org/problems/paths-to-reach-origin3850/1
