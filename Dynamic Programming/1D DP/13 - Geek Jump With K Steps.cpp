// Code to find the minimum possible total cost incurred before the Geek reaches the Nth stone, the Geek can jump to any one of the following, stone + 1, stone + 2, ... stone + K stone and cost will be [hi - hj] is incurred, where jump is the stone to land on ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum possible total cost, using recursion with memoization - O(N*K) & O(N)
    int minimizeCost(vector<int>& height, int N, int K) {
        vector<int> memory(N-1, -1);
        return solveWithMemo(memory, height, N, K, 0);
    }
    
private:
    // O(K*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& height, int N, int K, int startStone) {
        // Edge case: If Geek reached the last stone then there's no need to compute more cost
        if(startStone == N-1)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startStone] != -1)
            return memory[startStone];
        
        // Stores the result value 
        int minCost = INT_MAX;
        
        // Try each possible jump from the current stone and look for the minimum cost
        for(int jump = 1; (jump <= K && startStone + jump < N); jump++) {
            int nextCost = solveWithMemo(memory, height, N, K, startStone + jump);
            minCost      = min(minCost, nextCost + abs(height[startStone] - height[startStone + jump]));
        }
        
        // Store the result value to the memoization table and then return it
        return memory[startStone] = minCost;
    }

    // O(K^N) & O(N)
    int solveWithoutMemo(vector<int>& height, int N, int K, int startStone) {
        // Edge case: If Geek reached the last stone then there's no need to compute more cost
        if(startStone == N-1)
            return 0;

        // Stores the result value 
        int minCost = INT_MAX;
        
        // Try each possible jump from the current stone and look for the minimum cost
        for(int jump = 1; (jump <= K && startStone + jump < N); jump++) {
            int nextCost = solveWithoutMemo(height, N, K, startStone + jump);
            minCost      = min(minCost, nextCost + abs(height[startStone] - height[startStone + jump]));
        }
        
        // Return the result value            
        return minCost;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum possible total cost, using 1D tabulation - O(N*K) & O(N)
    int minimizeCost(vector<int>& height, int N, int K) {
        // 1D table: dp[stone] represents the minimum cost required to reach the individual stone
        vector<int> dp(N, INT_MAX); 

        // Initialize the edge case: If Geek reached the last stone then there's no need to compute more cost
        dp[N - 1] = 0;                 

        // Fill the rest of the table
        for(int startStone = N-2; startStone >= 0; --startStone) {  
            int minCost = INT_MAX;
            for(int jump = 1; (jump <= K && startStone + jump < N); jump++) {
                int nextCost = dp[startStone + jump];
                minCost      = min(minCost, nextCost + abs(height[startStone] - height[startStone + jump]));
            }
            dp[startStone] = minCost; 
        }

        // Return the result value
        return dp[0];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/minimal-cost/1
