// Code to find out the maximum amount of gold which the miner can collect until he can no longer move in the grid ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
/*
    DON'T IGNORE MUST READ (NOTE ON TIME COMPLEXITY CALCULATION):
    
    As you’ve noticed, for this problem, the time complexity of the solveWithMemo function is O(N + 3*N*M) I want to clarify that the N comes from the loop that calls the recursive function, it's not from the function's auxiliary time. Specifically:

        For solveWithMemo, in O(N + 3*N*M), the term 3*N*M represents the auxiliary time of the function itself, while N reflects the time from the loop that invokes the function.
        For solveWithoutMemo, in O(N * 3^(N*M)), the term 3^(N*M) represents the auxiliary time of the function itself, while N indicates the number of times the loop calls the function.
    
    So for future problems, be sure to identify any loops from which the function is called. This is crucial for providing a complete time complexity analysis, so I can’t ignore these terms.
*/  
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum amount of gold the miner can collect, using recursion with memoization - O(N*M) & O(N*M)
    int collectMaximumGold(int N, int M, vector<vector<int>>& grid) {
        // Stores the result value
        int maxGold = 0;
        
        // 2D memoization table
        vector<vector<int>> memory(N, vector<int>(M, -1));
        
        // Iterate the start points of the miner and get the maximum gold he can collect from it and then update the result by the maximum value
        for(int R = 0; R < N; ++R) {
            maxGold = max(maxGold, solveWithMemo(memory, grid, N, M, R, 0));
        }

        // Return the result value
        return maxGold;
    }
    
private:
    // O(N + 3*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If the miner walks out of the grid then he can't get gold
        if(R < 0 || R == N || C == M)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];
        
        // There are always three posibilities to perform at each cell
        int moveRight     = solveWithMemo(memory, grid, N, M, R, C+1);   // Move to the right cell
        int moveUpRight   = solveWithMemo(memory, grid, N, M, R-1, C+1); // Move to the cell which is diagonally up towards the right
        int moveDownRight = solveWithMemo(memory, grid, N, M, R+1, C+1); // Move to the cell which is diagonally down towards the right
        
        // Store the result value to the memoization table and then return it
        return memory[R][C] = grid[R][C] + max({moveUpRight, moveRight, moveDownRight});
    }

    // O(N * 3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If the miner walks out of the grid then he can't get gold
        if(R < 0 || R == N || C == M)
            return 0;
        
        // There are always three posibilities to perform at each cell
        int moveRight     = solveWithoutMemo(memory, grid, N, M, R, C+1);   // Move to the right cell
        int moveUpRight   = solveWithoutMemo(memory, grid, N, M, R-1, C+1); // Move to the cell which is diagonally up towards the right
        int moveDownRight = solveWithoutMemo(memory, grid, N, M, R+1, C+1); // Move to the cell which is diagonally down towards the right
        
        // Return the result value 
        return grid[R][C] + max({moveUpRight, moveRight, moveDownRight});
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum amount of gold the miner can collect, using 2D tabulation - O(N*M) & O(N*M)
    int collectMaximumGold_V1(int N, int M, vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+2, vector<int>(M+1, 0));

        for(int C = M-1; C >= 0; --C) {
            for(int R = N; R >= 1; --R) {
                int moveRight     = dp[R][C+1];  
                int moveUpRight   = dp[R-1][C+1]; 
                int moveDownRight = dp[R+1][C+1]; 
                dp[R][C] = grid[R-1][C] + max({moveUpRight, moveRight, moveDownRight});
            }
        }

        int maxGold = 0;

        for(int R = 0; R < N; ++R) {
            maxGold = max(maxGold, dp[R+1][0]);
        }

        return maxGold;
    }

    // #2 Method to find the maximum amount of gold the miner can collect, using constant auxiliary space - O(N*M) & O(1)
    int collectMaximumGold_V2(int N, int M, vector<vector<int>>& grid) {        
        for(int C = M-1; C >= 0; --C) {
            for(int R = N-1; R >= 0; --R) {
                int moveRight     = (C+1 < M) ? grid[R][C+1] : 0;
                int moveUpRight   = (R-1 >= 0 && C+1 < M) ? grid[R-1][C+1] : 0;
                int moveDownRight = (R+1 < N && C+1 < M) ? grid[R+1][C+1] : 0; 
                grid[R][C] += max({moveUpRight, moveRight, moveDownRight});
            }
        }
        
        int maxGold = 0;
        
        for(int R = 0; R < N; ++R) {
            maxGold = max(maxGold, grid[R][0]);
        }
        
        return maxGold;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix
Link  : https://www.geeksforgeeks.org/problems/gold-mine-problem2608/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
