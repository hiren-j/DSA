// Code to find the minimum number of coins to make the change for given cents. Suppose you've infinite supply of each type of coin ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the minimum number of coins to make the change for given cents, using recursion with memoization - O(N*C) & O(N*C) : Where C let be the cents
    int minCoinsToMakeChange(vector<int>& coins, int n, int cents) { 
        vector<vector<int>> memory(n, vector<int>(cents + 1, -1));
        int minCoins = solveWithMemo(memory, coins, n, 0, cents);
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
    
private:
    // O(2*N*C) & O(N*C + C)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& coins, int n, int index, int cents) {
        // Edge case: If the cents becomes zero then you've make the change hence return 0 as a valid indication of it
        if(cents == 0)
            return 0;

        // Edge case: At this point if all the coins are exhausted then you can't make the change hence return INT_MAX as a indication of it
        if(index == n) 
            return INT_MAX;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][cents] != -1)
            return memory[index][cents];
            
        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, coins, n, index + 1, cents); // Is to skip the index value 
        int currTake = INT_MAX;                                           // Is to take the index value
        
        // If possible then take the index value and then stay on the same index
        if(cents - coins[index] >= 0) {
            int nextCoins = solveWithMemo(memory, coins, n, index, cents - coins[index]);
            currTake = (nextCoins != INT_MAX) ? nextCoins + 1 : INT_MAX;
        }

        // Store the result value to the memoization table and then return it
        return memory[index][cents] = min(currTake, currSkip);
    }
    
    // O(2^C) & O(C)
    int solveWithoutMemo(vector<int>& coins, int n, int index, int cents) {
        // Edge case: If the cents becomes zero then you've make the change hence return 0 as a valid indication of it
        if(cents == 0)
            return 0;

        // Edge case: At this point if all the coins are exhausted then you can't make the change hence return INT_MAX as a indication of it
        if(index == n) 
            return INT_MAX;
            
        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(coins, n, index + 1, cents); // Is to skip the index value 
        int currTake = INT_MAX;                                      // Is to take the index value
        
        // If possible then take the index value and then stay on the same index
        if(cents - coins[index] >= 0) {
            int nextCoins = solveWithoutMemo(coins, n, index, cents - coins[index]);
            currTake = (nextCoins != INT_MAX) ? nextCoins + 1 : INT_MAX;
        }

        // As we're striving for the minimum number of coins hence return the minimum value
        return min(currTake, currSkip);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the minimum number of coins to make the change for given cents, using recursion with memoization - O(N*N*C) & O(N*C)
    int minCoinsToMakeChange(vector<int>& coins, int n, int cents) { 
        vector<vector<int>> memory(n, vector<int>(cents + 1, -1));
        int minCoins = solveWithMemo(memory, coins, n, 0, cents);
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
    
private:
    // O(N*N*C) & O(N*C + C)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& coins, int n, int startIndex, int cents) {
        // Edge case: If the cents becomes zero then you've make the change hence return 0 as a valid indication of it
        if(cents == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][cents] != -1)
            return memory[startIndex][cents];

        // Stores the result value
        int minCoins = INT_MAX;

	// Iterate and if possible then take the index value and then stay on the same index
        for(int index = startIndex; index < n; ++index) {
            if(cents - coins[index] >= 0) {
                int nextCoins = solveWithMemo(memory, coins, n, index, cents - coins[index]);
                if(nextCoins != INT_MAX) {
                    minCoins = min(minCoins, nextCoins + 1);
                }
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex][cents] = minCoins;
    }

    // O(N^C) & O(C)
    int solveWithoutMemo(vector<int>& coins, int n, int startIndex, int cents) {
        // Edge case: If the cents becomes zero then you've make the change hence return 0 as a valid indication of it
        if(cents == 0)
            return 0;

        // Stores the result value
        int minCoins = INT_MAX;
	    
	// Iterate and if possible then take the index value and then stay on the same index
        for(int index = startIndex; index < n; ++index) {
            if(cents - coins[index] >= 0) {
                int nextCoins = solveWithoutMemo(coins, n, index, cents - coins[index]);
                if(nextCoins != INT_MAX) {
                    minCoins = min(minCoins, nextCoins + 1);
                }
            }
        }

        // Return the result value
        return minCoins;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the minimum number of coins to make the change for given cents, using 2D tabulation - O(N*C) & O(N*C)
    int minCoinsToMakeChange_V1(vector<int>& coins, int n, int cents) { 
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(cents + 1, INT_MAX));

        // Initialize the first edge case: If the cents becomes zero then you've make the change hence return 0 as a valid indication of it
        for(int index = 0; index <= n; ++index)
            dp[index][0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int cent = 1; cent <= cents; ++cent) {
                int currSkip = dp[index + 1][cent];
                int currTake = INT_MAX;        
                if(cent - coins[index] >= 0) {
                    int nextCoins = dp[index][cent - coins[index]];
                    currTake = (nextCoins != INT_MAX) ? nextCoins + 1 : INT_MAX;
                }
                dp[index][cent] = min(currTake, currSkip);
            }
        }

        int minCoins = dp[0][cents];

        // Return the result value
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }

    // #2 Method to find the minimum number of coins to make the change for given cents, using 1D tabulation - O(N*C) & O(C)
    int minCoinsToMakeChange_V2(vector<int>& coins, int n, int cents) { 
        // 1D DP tables
        vector<int> nextRow(cents + 1, INT_MAX), idealRow(cents + 1, INT_MAX);
        nextRow[0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            idealRow[0] = 0;
            for(int cent = 1; cent <= cents; ++cent) {
                int currSkip = nextRow[cent];
                int currTake = INT_MAX;        
                if(cent - coins[index] >= 0) {
                    int nextCoins = idealRow[cent - coins[index]];
                    currTake = (nextCoins != INT_MAX) ? nextCoins + 1 : INT_MAX;
                }
                idealRow[cent] = min(currTake, currSkip);
            }
            nextRow = idealRow;
        }

        int minCoins = nextRow[cents];

        // Return the result value
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/number-of-coins1824/1
        https://leetcode.com/problems/coin-change/description/
