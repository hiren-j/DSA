// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
public:
    // Method to find the maximum amount of money you can rob, using recursion with memoization - O(N) & O(N)
    int getMaxMoney(std::vector<int>& houses) {
        int N = houses.size();
        std::vector<int> memory(N+1, -1);
        return solveWithMemo(memory, houses, N, 0);
    }

private:
    // O(2*N) & O(N+N)
    int solveWithMemo(std::vector<int>& memory, std::vector<int>& houses, int N, int J) {
        // Edge case: If all the houses are exhausted then it's not possible to rob anymore
        if(J >= N)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[J] != -1)
            return memory[J];

        // There are always two possibilities to perform at each house 
        int currHouseRob  = houses[J] + solveWithMemo(memory, houses, N, J+2); // Is to rob it and then advance two steps ahead from it
        int currHouseSkip = solveWithMemo(memory, houses, N, J+1);             // Is to skip it and move to the next house

        // Store the result value to the memoization table and then return it
        return memory[J] = std::max(currHouseRob, currHouseSkip);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(std::vector<int>& houses, int N, int J) {
        // Edge case: If all the houses are exhausted, then it's not possible to rob anymore
        if(J >= N)
            return 0;

        // There are always two possibilities to perform at each house 
        int currHouseRob  = houses[J] + solveWithoutMemo(houses, N, J+2); // Is to rob it and then advance two steps ahead from it
        int currHouseSkip = solveWithoutMemo(houses, N, J+1);             // Is to skip it and move to the next house

        // As we're striving for the maximum money hence return the maximum value
        return std::max(currHouseRob, currHouseSkip);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum amount of money you can rob, using 1D tabulation - O(N) & O(N)
    int getMaxMoney_V1(std::vector<int>& houses) {
        int N = houses.size();

        // 1D table: dp[J] represents the maximum money that can be robbed till the Jth house
        std::vector<int> dp(N+1);
        
        dp[0] = 0;         // Initially no house at the beginning hence consider the money as zero
        dp[1] = houses[0]; // The maximum money for the first house is the money that the house have

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            dp[J] = std::max(houses[J-1] + dp[J-2], dp[J-1]);

        // Return the result value
        return dp[N];
    }

    // #2 Method to find the maximum amount of money we can rob, using constant auxiliary space - O(N) & O(1)
    int getMaxMoney_V2(std::vector<int>& houses) {
        int N = houses.size();
        
        int prevPrevMoney = 0;          // Initially no house at the beginning hence consider the money as zero
        int prevMoney     = houses[0];  // The maximum money for the first house is the money that the house have
        int maxMoney      = prevMoney;  // Stores the overall amount of maximum money that can be robbed

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            maxMoney      = std::max(houses[J-1] + prevPrevMoney, prevMoney),
            prevPrevMoney = prevMoney,
            prevMoney     = maxMoney;

        // Return the result value
        return maxMoney;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/house-robber/description/?envType=daily-question&envId=2024-01-21
        https://www.codingninjas.com/studio/problems/maximum-sum-of-non-adjacent-elements_843261 
        https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
