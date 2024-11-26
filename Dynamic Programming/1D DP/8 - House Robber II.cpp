// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum amount of money you can rob, using recursion with memoization - O(N) & O(N)
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        // 1D memoization tables
        std::vector<int> memoryA(N+1, -1), memoryB(N+1, -1);
        
        int startFromZero = solveWithMemo(houses, memoryA, 0, N-1); // Visit all the houses excluding the last house
        int startFromOne  = solveWithMemo(houses, memoryB, 1, N);   // Visit all the houses excluding the first house

        // Return the maximum money get from both the possibilities
        return std::max(startFromZero, startFromOne);
    }

private:
    // O(2*N) & O(N+N)
    int solveWithMemo(std::vector<int>& houses, std::vector<int>& memory, int start, int end) {
        // Edge case: If all the houses are exhausted then it's not possible to rob anymore
        if(start >= end)  
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[start] != -1)
            return memory[start];

        // There are always two possibilities to perform at each house
        int currHouseRob  = houses[start] + solveWithMemo(houses, memory, start+2, end); // Is to rob it and then advance two steps ahead from it
        int currHouseSkip = solveWithMemo(houses, memory, start+1, end);                 // Is to skip it and move to the next house

        // Store the result value to the memoization table and then return it
        return memory[start] = std::max(currHouseRob, currHouseSkip);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(std::vector<int>& houses, int start, int end) {
        // Edge case: If all the houses are exhausted then it's not possible to rob anymore
        if(start >= end)  
            return 0;

        // There are always two possibilities at each house
        int currHouseRob  = houses[start] + solveWithoutMemo(houses, start+2, end); // Is to rob the it and then advance two steps ahead from it
        int currHouseSkip = solveWithoutMemo(houses, start+1, end);                 // Is to skip it and move to the next house

        // As we're striving for the maximum money hence return the maximum value
        return std::max(currHouseRob, currHouseSkip);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // Method to find the maximum amount of money you can rob, using 1D tabulation :-
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        std::vector<int> excLastHouse;  // Stores the houses excluding the last house
        std::vector<int> excFirstHouse; // Stores the houses excluding the first house

        // Iterate and store the houses
        for(int J=0; J<N; J++) {
            if(J < N-1) 
                excLastHouse.push_back(houses[J]);
            if(J > 0)
                excFirstHouse.push_back(houses[J]);
        }

        int maxMoneyA = solveWithoutTable(excLastHouse);  // Visit all the houses excluding the last house
        int maxMoneyB = solveWithoutTable(excFirstHouse); // Visit all the houses excluding the first house

        // Return the maximum money get from both the possibilities
        return std::max(maxMoneyA, maxMoneyB);
    }

private:
    // O(N) & O(1)
    int solveWithoutTable(std::vector<int>& houses) {
        int N = houses.size();
        
        int prevPrevMoney = 0;         // Initially no house at the beginning hence consider the money as zero
        int prevMoney     = houses[0]; // The maximum money for the first house is the money that the house have
        int maxMoney      = prevMoney; // Stores the overall amount (maximum money) that can be robbed

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            maxMoney      = std::max(houses[J-1] + prevPrevMoney, prevMoney),
            prevPrevMoney = prevMoney,
            prevMoney     = maxMoney;

        // Return the overall amount (maximum money) that can be robbed
        return maxMoney;
    }

    // O(N) & O(N)
    int solveWithTable(std::vector<int>& houses) {
        int N = houses.size();

        // 1D table: dp[J] represents the maximum money that can be robbed till the Jth house
        std::vector<int> dp(N+1, 0);
        
        // The maximum money for the first house is the money that the house have
        dp[1] = houses[0]; 

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J=2; J<=N; J++)
            dp[J] = std::max(houses[J-1] + dp[J-2], dp[J-1]);

        // Return the overall amount (maximum money) that can be robbed
        return dp[N];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the maximum amount of money you can rob, using 1D tabulation - O(N) & O(N)
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        // Visit all the houses excluding the last house
            // 1D table: dp1[J] represents the maximum money that can be robbed till the Jth house
            std::vector<int> dp1(N, 0);

            // The maximum money for the first house is the money that the house have
            dp1[1] = houses[0];

            // Iterate and find the maximum money that can be robbed till the Jth house
            for(int J=2; J<N; J++)
                dp1[J] = std::max(houses[J-1] + dp1[J-2], dp1[J-1]);

        // Visit all the houses excluding the first house
            // 1D table: dp2[J] represents the maximum money that can be robbed till the Jth house
            std::vector<int> dp2(N, 0);

            // The maximum money for the first house is the money that the house have
            dp2[1] = houses[1];
            
            // Iterate and find the maximum money that can be robbed till the Jth house
            for(int J=2; J<N; J++)
                dp2[J] = std::max(houses[J] + dp2[J-2], dp2[J-1]);

        // Return the maximum money get from both the possibilities
        return std::max(dp1[N-1], dp2[N-1]);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V3 {
public:
    // Method to find the maximum amount of money you can rob, using constant auxiliary space - O(N) & O(1)
    int robMaxMoney(std::vector<int>& houses) {
        int N = houses.size();

        // Edge case: When there's only a single house then the maximum money you can rob is the money that the house have
        if(N == 1)
            return houses[0];

        int maxMoneyA = solveWithoutTable(houses, N, 0, N-2); // Visit all the houses excluding the last house
        int maxMoneyB = solveWithoutTable(houses, N, 1, N-1); // Visit all the houses excluding the first house

        // Return the maximum money get from both the possibilities
        return std::max(maxMoneyA, maxMoneyB);
    }

private:
    int solveWithoutTable(std::vector<int>& houses, int N, int start, int end) {
        int prevPrevMoney = 0;             // Initially no house at the beginning hence consider the money as zero
        int prevMoney     = houses[start]; // The maximum money for the first house is the money that the house have
        int maxMoney      = prevMoney;     // Stores the overall amount of maximum money that can be robbed

        // Iterate and find the maximum money that can be robbed till the Jth house
        for(int J = start+1; J <= end; ++J) 
            maxMoney      = std::max(houses[J] + prevPrevMoney, prevMoney),
            prevPrevMoney = prevMoney,
            prevMoney     = maxMoney;

        // Return the maximum money that can be robbed
        return maxMoney;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/house-robber-ii/
