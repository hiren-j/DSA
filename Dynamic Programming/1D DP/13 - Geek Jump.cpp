// Code to find the minimum energy that can be used by the Geek to jump from step 0 to step N-1 ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOTE REGARDING THE FIRST SOLUTION (TopDown_V1): You can ignore this solution for now. Consider it as a future test when you'll complete Multi-Dimensional DP pattern and please don't worry i just did this thing in this problem only, you won't find this kind of things in any other problem. Actually i created this solution as a brute force and yeah feel free to ignore it for now.
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the minimum energy, using recursion with memoization - O(N * maxElement) & O(N * maxElement)
    int minimumEnergy(vector<int>& heights, int N) {
        int maxElement = *max_element(begin(heights), end(heights));
        vector<vector<int>> memory(N - 1, vector<int>(maxElement + 1, -1));
        return solveWithMemo(memory, heights, N, 0, heights[0]);
    }
    
private:
    // O(2*N*maxElement) & O(N*maxElement + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& heights, int N, int step, int prevHeight) {
        // Edge case: If we reached the last step then return the energy value as a valid indication of it
        if(step == N-1)
            return abs(prevHeight - heights[step]);
            
        // Edge case: If we're not able to reach the last step then it's not possible to have a valid way
        if(step >= N)
            return INT_MAX;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[step][prevHeight] != -1)
            return memory[step][prevHeight];

        // There are always two possibilities to perform at each step
        int climbOneStep = solveWithMemo(memory, heights, N, step + 1, heights[step]); // Is to advance one step ahead from it
        int climbTwoStep = solveWithMemo(memory, heights, N, step + 2, heights[step]); // Is to advance two steps ahead from it
            
        // Store the result value to the memoization table and then return it
        return memory[step][prevHeight] = abs(prevHeight - heights[step]) + min(climbOneStep, climbTwoStep);
    }
    
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& heights, int N, int step, int prevHeight) {
        // Edge case: If we reached the last step then return the energy value as an valid indication of it
        if(step == N-1)
            return abs(prevHeight - heights[step]);
            
        // Edge case: If we're not able to reach the last step then it's not possible to have a valid way
        if(step >= N)
            return INT_MAX;
            
        // There are always two possibilities to perform at each step
        int climbOneStep = solveWithoutMemo(heights, N, step + 1, heights[step]); // Is to advance one step ahead from it
        int climbTwoStep = solveWithoutMemo(heights, N, step + 2, heights[step]); // Is to advance two steps ahead from it
        
        // As we're striving for the minimum energy hence return the minimum value     
        return abs(prevHeight - heights[step]) + min(climbOneStep, climbTwoStep);
    }
};
// Note: You can ignore this solution for now. Consider it as a future test when you'll complete Multi-Dimensional DP pattern and please don't worry i just did this thing in this problem only, you won't find this kind of things in any other problem. Actually i created this solution as a brute force and yeah feel free to ignore it for now

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the minimum energy, using recursion with memoization - O(N) & O(N)
    int minimumEnergy(vector<int>& heights, int N) {
        vector<int> memory(N - 1, -1);
        return solveWithMemo(memory, heights, N, 0);
    }
    
private:
    // O(2*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& heights, int N, int step) {
        // Edge case: If we reached the last step then we don't have to compute more energy
        if(step == N-1)
            return 0;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[step] != -1)
            return memory[step];
            
        // There are always two possibilities to perform at each step
        int climbOneStep = abs(heights[step] - heights[step + 1]) + solveWithMemo(memory, heights, N, step + 1); // Is to advance one step ahead from it
        int climbTwoStep = INT_MAX;                                                                              // Is to advance two steps ahead from it
                    
        // If it's possible then advance two steps ahead from this step
        if(step + 2 < N)
            climbTwoStep = abs(heights[step] - heights[step + 2]) + solveWithMemo(memory, heights, N, step + 2);
            
        // Store the result value to the memoization table and then return it
        return memory[step] = min(climbOneStep, climbTwoStep);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& heights, int N, int step) {
        // Edge case: If we reached the last step then we don't have to compute more energy
        if(step == N-1)
            return 0;
            
        // There are always two possibilities to perform at each step
        int climbOneStep = abs(heights[step] - heights[step + 1]) + solveWithoutMemo(heights, N, step + 1); // Is to advance one step ahead from it
        int climbTwoStep = INT_MAX;                                                                         // Is to advance two steps ahead from it
                    
        // If it's possible then advance two steps ahead from this step
        if(step + 2 < N)
            climbTwoStep = abs(heights[step] - heights[step + 2]) + solveWithoutMemo(heights, N, step + 2);
            
        // As we're striving for the minimum energy hence return the minimum value
        return min(climbOneStep, climbTwoStep);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the minimum energy, using 1D tabulation - O(N) & O(N)
    int minimumEnergy_V1(vector<int>& heights, int N) {
        // 1D DP table
        vector<int> dp(N, INT_MAX);
        
        // Initialize the edge case: If we reached the last step then we don't have to compute more energy
        dp[N - 1] = 0;
        
        // Fill the rest of the table
        for(int step = N-2; step >= 0; --step) {
            int climbOneStep = abs(heights[step] - heights[step + 1]) + dp[step + 1];
            int climbTwoStep = INT_MAX;                                                                             
            if(step + 2 < N) {
                climbTwoStep = abs(heights[step] - heights[step + 2]) + dp[step + 2];
            }
            dp[step] = min(climbOneStep, climbTwoStep);
        }
        
        // Return the result value
        return dp[0];
    }
    // Note: This bottom-up solution is created from the memoized solution of (TopDown_V2)

    // #2 Method to find the minimum energy, using constant auxiliary space - O(N) & O(1)
    int minimumEnergy_V2(vector<int>& heights, int N) {
        int nextEnergy1 = 0, nextEnergy2 = INT_MAX, minEnergy = 0; 
        
        for(int step = N-2; step >= 0; --step) {
            int climbOneStep = abs(heights[step] - heights[step + 1]) + nextEnergy1;
            int climbTwoStep = INT_MAX;                                                                             
            if(step + 2 < N) {
                climbTwoStep = abs(heights[step] - heights[step + 2]) + nextEnergy2;
            }
            minEnergy   = min(climbOneStep, climbTwoStep);
            nextEnergy2 = nextEnergy1;
            nextEnergy1 = minEnergy;
        }
         
        return minEnergy;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/geek-jump/1 
        https://www.codingninjas.com/studio/problems/frog-jump_3621012
