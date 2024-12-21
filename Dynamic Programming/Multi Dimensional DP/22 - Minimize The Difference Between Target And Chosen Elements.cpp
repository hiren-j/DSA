// Code to find the minimum absolute difference, The absolute difference between two numbers a and b is the absolute value of a - b. We could Choose one integer from each row in the matrix such that the absolute difference between target and the pathSum of the chosen elements is minimized ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*

NOTE: 1 <= grid[i][j] <= 70
NOTE: 1 <= N, M <= 70
NOTE: So, In the worst case the highest value of pathSum could be 70*70 = 4900. 
      Didn't understand? Imagine the worst case when there will be 70 rows and 70 columns and all the cells contains value 70. 
      So, based on my logic you could see we're looking for the result value by moving from the first row to the last row.
      So, If you add the value 70 of the chosen cells across the path then you'll end up having the pathSum of 4900 at max or when you end up reaching all the rows.
      So, I measured it through the problem constraints. Hope you've got it!
      
*/
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
      
NOTE: In the bottom-up approach, the sum iterations start from 2500 and go down to 0. Initially, I started with a larger value, around 4089, and then experimented with different values to avoid extra iterations. 
      After several adjustments, 2500 emerged as the most fitting value based on my intuition. This adjustment is necessary to ensure we cover all relevant sum values. 
      Starting from 4089 works, but starting from 4900 or higher can lead to segmentation faults due to out-of-bounds accesses. 
      Starting from 2500 ensures we cover all possible sums more efficiently and avoids such issues, requiring only 2500 iterations. 
      This approach helps to effectively explore all possible sums and capture the minimum absolute difference within the problem's context.

*/
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
      
class TopDown {
    int N, M;

    // O(M^(N*M)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int target, int startRow, int pathSum) {
        // Edge case: If all the rows are exhausted then return the absolute difference of the current path
        if(startRow == N)
            return abs(target - pathSum);

        // Stores the result value
        int minAbsDiff = INT_MAX;
        
        // Explore all the possible paths of choosing elements from the cell and update the result by the minimum value
        for(int C = 0; C < M; ++C) 
            minAbsDiff = min(minAbsDiff, solveWithoutMemo(grid, target, startRow + 1, pathSum + grid[startRow][C]));

        // Return the result vlaue  
        return minAbsDiff;
    } 

    // O(M*N*4901) & O(N*4901 + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int target, int startRow, int pathSum) {
        // Edge case: If all the rows are exhausted then return the absolute difference of the current path
        if(startRow == N)
            return abs(target - pathSum);

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startRow][pathSum] != -1)
            return memory[startRow][pathSum];

        // Stores the result value
        int minAbsDiff = INT_MAX;

        // Explore all the possible paths of choosing elements from the cell and update the result by the minimum value
        for(int C = 0; C < M; ++C) 
            minAbsDiff = min(minAbsDiff, solveWithMemo(memory, grid, target, startRow + 1, pathSum + grid[startRow][C]));

        // Store the result value to the memoization table and then return it
        return memory[startRow][pathSum] = minAbsDiff;
    } 

public:
    // Method to find the minimum absolute difference, using recursion with memoization :-
    int minimizeTheDifference(vector<vector<int>>& grid, int target) {
        N = grid.size(), M = grid[0].size();
        vector<vector<int>> memory(N, vector<int>(4901, -1));
        return solveWithMemo(memory, grid, target, 0, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum absolute difference, using 2D tabulation - O(N*2501*M) & O(N*4901)
    int minimizeTheDifference_V1(vector<vector<int>>& grid, int target) {
        int N = grid.size(), M = grid[0].size();

        // 2D DP table
        vector<vector<int>> dp(N + 1, vector<int>(4901, INT_MAX));

        // Initialize the edge case: If all the rows are exhausted then return the absolute difference of the current path
        for(int pathSum = 0; pathSum <= 2500; ++pathSum)
            dp[N][pathSum] = abs(target - pathSum);

        // Fill the rest of the table
        for(int startRow = N-1; startRow >= 0; --startRow) {
            for(int pathSum = 2500; pathSum >= 0; --pathSum) {
                int minAbsDiff = INT_MAX;
                for(int C = 0; C < M; ++C) {
                    minAbsDiff = min(minAbsDiff, dp[startRow + 1][pathSum + grid[startRow][C]]);
                }
                dp[startRow][pathSum] = minAbsDiff;            
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // Method to find the minimum absolute difference, using 1D tabulation - O(N*2501*M) & O(2*4901)
    int minimizeTheDifference_V2(vector<vector<int>>& grid, int target) {
        int N = grid.size(), M = grid[0].size();

        // 1D DP tables
        vector<int> nextRow(4901, INT_MAX), currRow(4901, INT_MAX);

        // Initialize the edge case: If all the rows are exhausted then return the absolute difference of the current path
        for(int pathSum = 0; pathSum <= 2500; ++pathSum)
            nextRow[pathSum] = abs(target - pathSum);

        // Fill the rest of the table
        for(int startRow = N-1; startRow >= 0; --startRow) {
            for(int pathSum = 2500; pathSum >= 0; --pathSum) {
                int minAbsDiff = INT_MAX;
                for(int C = 0; C < M; ++C) {
                    minAbsDiff = min(minAbsDiff, nextRow[pathSum + grid[startRow][C]]);
                }
                currRow[pathSum] = minAbsDiff;            
            }
            nextRow = currRow;
        }

        // Return the result value
        return currRow[0];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/description/
