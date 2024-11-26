// Code to find the fewest number of coins that you need to make up the amount. If that amount of money cannot be made up by any combination of the coins then return -1. You may assume that you have an infinite number of each kind of coin ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the fewest number of coins, using recursion with memoization - O(N*A) & O(A) : Where A let be the amount
    int coinChange(vector<int>& coins, int amount) {
        vector<int> memory(amount + 1, -1);
        int minCoins = solveWithMemo(memory, coins, amount, coins.size());
        return (minCoins == INT_MAX ? -1 : minCoins);
    }

private:
    // O(N*A) & O(A+A)
    int solveWithMemo(vector<int>& memory, vector<int>& coins, int amount, int n) {
        // Edge case: If the amount becomes zero then it's not possible to pick more coins
        if(amount == 0)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[amount] != -1)
            return memory[amount];

        // Stores the result value
        int minCoins = INT_MAX;

        // Pick each coin and try to make up the amount from it
        for(int index = 0; index < n; ++index) {
            if(coins[index] <= amount) {
                int nextCoins = solveWithMemo(memory, coins, amount - coins[index], n);
                if(nextCoins != INT_MAX) {
                    minCoins = min(minCoins, 1 + nextCoins);
                }
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[amount] = minCoins;
    }

    // O(N^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int amount, int n) {
        // Edge case: If the amount becomes zero then it's not possible to pick more coins
        if(amount == 0)
            return 0;
        
        // Stores the result value
        int minCoins = INT_MAX;

        // Pick each coin and try to make up the amount from it
        for(int index = 0; index < n; ++index) {
            if(coins[index] <= amount) {
                int nextCoins = solveWithoutMemo(coins, amount - coins[index], n);
                if(nextCoins != INT_MAX) {
                    minCoins = min(minCoins, 1 + nextCoins);
                }
            }
        }

        // Return the result value
        return minCoins;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the fewest number of coins, using recursion with memoization - O(N*A) & O(A)
    int coinChange(vector<int>& coins, int amount) {
        sort(begin(coins), end(coins));
        vector<int> memory(amount + 1, -1);
        int minCoins = solveWithMemo(memory, coins, amount, coins.size());
        return (minCoins == INT_MAX ? -1 : minCoins);
    }

private:
    // O(N*A) & O(A+A)
    int solveWithMemo(vector<int>& memory, vector<int>& coins, int amount, int n) {
        // Edge case: If the amount becomes zero then it's not possible to pick more coins
        if(amount == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[amount] != -1)
            return memory[amount];

        // Stores the result value
        int minCoins = INT_MAX;

        // Pick the coins and make up the amount from it
        for(int index = 0; (index < n && coins[index] <= amount); ++index) {
            int nextCoins = solveWithMemo(memory, coins, amount - coins[index], n);
            if(nextCoins != INT_MAX) {   
                minCoins = min(minCoins, 1 + nextCoins);
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[amount] = minCoins;
    }

    // O(N^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int amount, int n) {
        // Edge case: If the amount becomes zero then it's not possible to pick more coins
        if(amount == 0)
            return 0;

        // Stores the result value
        int minCoins = INT_MAX;

        // Pick the coins and make up the amount from it
        for(int index = 0; (index < n && coins[index] <= amount); ++index) {
            int nextCoins = solveWithoutMemo(coins, amount - coins[index], n);
            if(nextCoins != INT_MAX) {   
                minCoins = min(minCoins, 1 + nextCoins);
            }
        }

        // Return the result value
        return minCoins;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the fewest number of coins, using 1D tabulation - O(N*A) & O(A)
    int coinChange_V1(vector<int>& coins, int amount) {
        int n = coins.size();

        // 1D table: dp[amount] represents the fewest number of coins needed to make up the amount 
        vector<int> dp(amount + 1, INT_MAX);

        // Initialize the edge case: If the amount becomes zero then it's not possible to pick more coins
        dp[0] = 0;

        // Treat each individual amount and find the fewest number of coins needed to make it
        for(int currAmount = 1; currAmount <= amount; ++currAmount) {
            for(int index = 0; index < n; ++index) {
                if(coins[index] <= currAmount) {
                    int nextCoins = dp[currAmount - coins[index]];
                    if(nextCoins != INT_MAX) {
                        dp[currAmount] = min(dp[currAmount], 1 + nextCoins);
                    }
                }
            }
        }

        // Return the result value 
        return (dp[amount] == INT_MAX) ? -1 : dp[amount];
    }

    // #2 Method to find the fewest number of coins, using 1D tabulation - O(N*A) & O(A)
    int coinChange_V2(vector<int>& coins, int amount) {
        int n = coins.size();
        sort(begin(coins), end(coins));

        // 1D table: dp[amount] represents the fewest number of coins needed to make up the amount 
        vector<int> dp(amount + 1, INT_MAX);

        // Initialize the edge case: If the amount becomes zero then it's not possible to pick more coins
        dp[0] = 0;

        // Treat each individual amount and find the fewest number of coins needed to make it
        for(int currAmount = 1; currAmount <= amount; ++currAmount) {
            for(int index = 0; (index < n && coins[index] <= currAmount); ++index) {
                int nextCoins = dp[currAmount - coins[index]];
                if(nextCoins != INT_MAX) {
                    dp[currAmount] = min(dp[currAmount], 1 + nextCoins);
                }
            }
        }

        // Return the result value
        return (dp[amount] == INT_MAX ? -1 : dp[amount]);  
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/coin-change/description/
        https://cses.fi/problemset/task/1634
