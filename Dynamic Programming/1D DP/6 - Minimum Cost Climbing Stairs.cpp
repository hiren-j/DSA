// Code to find the minimum cost to reach the top of the floor ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum cost, using recursion with memoization - O(N) & O(N)
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();

        // 1D memoization tables
        vector<int> memory1(n + 1, -1), memory2(n + 1, -1);

        int startFromZero = solveWithMemo(cost, memory1, n, 0); // Start movements from the 0th step
        int startFromOne  = solveWithMemo(cost, memory2, n, 1); // Start movements from the 1th step

        // Return the result value
        return min(startFromZero, startFromOne);
    }

private:
    // O(2*N) & O(N+N)
    int solveWithMemo(vector<int>& cost, vector<int>& memory, int n, int step) {
        // Edge case: If we reached the top of the floor then we don't need any cost
        if(step >= n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[step] != -1)
            return memory[step];
        
        // There are always two possibilities to perform at each step
        int climbOneStep = solveWithMemo(cost, memory, n, step + 1); // Is to jump and advance one step ahead from it
        int climbTwoStep = solveWithMemo(cost, memory, n, step + 2); // Is to jump and advance two steps ahead from it

        // Store the result value to the memoization table and then return it
        return memory[step] = cost[step] + min(climbOneStep, climbTwoStep);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& cost, int n, int step) {
        // Edge case: If we reached the top of the floor then we don't need any cost
        if(step >= n)
            return 0;

        // There are always two possibilities to perform at each step
        int climbOneStep = solveWithoutMemo(cost, n, step + 1); // Is to jump and advance one step ahead from it
        int climbTwoStep = solveWithoutMemo(cost, n, step + 2); // Is to jump and advance two steps ahead from it

        // As we're striving for the minimum cost hence return the minimum value
        return cost[step] + min(climbOneStep, climbTwoStep);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the minimum cost, using 1D tabulation - O(N) & O(N)
    int minCostClimbingStairs_V1(vector<int>& cost) {
        int n = cost.size();

        // 1D table: dp[step] represents the minimum cost needed to reach the individual step by considering the movements starting from 0th and 1th step
        vector<int> dp(n, 0);
        
        dp[0] = cost[0]; // For the 0th step the minimum cost needed to reach it is the cost that the step have
        dp[1] = cost[1]; // For the 1th step the minimum cost needed to reach it is the cost that the step have

        // Iterate and compute the minimum cost needed to reach the individual step
        for(int step = 2; step < n; ++step)
            dp[step] = cost[step] + min(dp[step - 1], dp[step - 2]);

        // Return the result value
        return min(dp[n - 1], dp[n - 2]);
    }

    // #2 Method to find the minimum cost, using constant auxiliary space - O(N) & O(1)
    int minCostClimbingStairs_V2(vector<int>& cost) {
        int n = cost.size();

        int prevPrevCost = cost[0];               // For the 0th step the minimum cost needed to reach it is the cost that the step have
        int prevCost     = cost[1];               // For the 1th step the minimum cost needed to reach it is the cost that the step have            
        int currCost     = min(cost[0], cost[1]); // Compute and store the minimum cost needed to reach the top (considering the first two steps only)

        // Iterate and compute the minimum cost needed to reach the individual step
        for(int step = 2; step < n; ++step)
            currCost     = cost[step] + min(prevPrevCost, prevCost),
            prevPrevCost = prevCost,
            prevCost     = currCost;

        // Return the result value
        return min(currCost, prevPrevCost);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/min-cost-climbing-stairs/description/
