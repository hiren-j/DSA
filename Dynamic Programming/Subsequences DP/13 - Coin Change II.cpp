// Code to find the total number of combinations that make up the given amount ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the number of combinations that make up the given amount, using recursion with memoization - O(N*A) & O(N*A) : Where A let be the amount
    int countWaysToMakeAmount(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> memory(n, vector<int>(amount + 1, -1));
        return solveWithMemo(memory, coins, n, 0, amount);
    }

private:
    // O(2*N*A) & O(N*A + A)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& coins, int n, int index, int amount) {
        // Edge case: If the amount becomes zero then there exists one valid combination
        if(amount == 0)
            return 1;

        // Edge case: If all the elements are exhausted then there's no combination
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][amount] != -1)
            return memory[index][amount];   

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, coins, n, index + 1, amount); // Is to skip the index value 
        int currTake = 0;                                                  // Is to take the index value

        // If possible then take the index value
        if(coins[index] <= amount)   
            currTake = solveWithMemo(memory, coins, n, index, amount - coins[index]);

        // Store the result value to the memoization table and then return it
        return memory[index][amount] = currTake + currSkip;
    }

    // O(2^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int n, int index, int amount) {
        // Edge case: If the amount becomes zero then there exists one valid combination
        if(amount == 0)
            return 1;

        // Edge case: If all the elements are exhausted then there's no combination
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(coins, n, index + 1, amount); // Is to skip the index value 
        int currTake = 0;                                             // Is to take the index value

        // If possible then take the index value
        if(coins[index] <= amount)   
            currTake = solveWithoutMemo(coins, n, index, amount - coins[index]);

        // Return the result value
        return currTake + currSkip;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the number of combinations that make up the given amount, using recursion with memoization - O(N*N*A) & O(N*A)
    int countWaysToMakeAmount(int amount, vector<int>& coins) {
        int n = coins.size();
        vector<vector<int>> memory(n, vector<int>(amount + 1, -1));
        return solveWithMemo(memory, coins, n, 0, amount);
    }

private:
    // O(N*N*A) & O(N*A + A)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& coins, int n, int startIndex, int amount) {
        // Edge case: If the amount becomes zero then there exists one valid combination
        if(amount == 0)
            return 1;

        // Edge case: If all the elements are exhausted then there's no combination
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][amount] != -1)
            return memory[startIndex][amount];

        // Stores the result value
        int countWays = 0;

        // Iterate and if possible then take the index value and try to make up the amount from it
        for(int index = startIndex; index < n; ++index) 
            if(coins[index] <= amount) 
                countWays += solveWithMemo(memory, coins, n, index, amount - coins[index]);

        // Store the result value to the memoization table and then return it 
        return memory[startIndex][amount] = countWays;
    }

    // O(N^A) & O(A)
    int solveWithoutMemo(vector<int>& coins, int n, int startIndex, int amount) {
        // Edge case: If the amount becomes zero then there exists one valid combination
        if(amount == 0)
            return 1;

        // Stores the result value
        int countWays = 0;

        // Iterate and if possible then take the index value and try to make up the amount from it
        for(int index = startIndex; index < n; ++index) 
            if(coins[index] <= amount) 
                countWays += solveWithoutMemo(coins, n, index, amount - coins[index]);

        // Return the result value
        return countWays;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the number of combinations that make up the given amount, using 2D tabulation - O(N*A) & O(N*A)
    int countWaysToMakeAmount_V1(int amount, vector<int>& coins) {
        int n = coins.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));

        // Initialize the first edge case: If the amount becomes zero then there exists one valid combination
        for(int index = 0; index <= n; ++index)
            dp[index][0] = 1;        

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int currAmount = 1; currAmount <= amount; ++currAmount) {
                int currSkip = dp[index + 1][currAmount]; 
                int currTake = 0;                                                 
                if(coins[index] <= currAmount) {
                    currTake = dp[index][currAmount - coins[index]];
                }
                dp[index][currAmount] = currTake + currSkip;  
            }
        }

        // Return the result value 
        return dp[0][amount];
    }

    // #2 Method to find the number of combinations that make up the given amount, using 1D tabulation - O(N*A) & O(A)
    int countWaysToMakeAmount_V2(int amount, vector<int>& coins) {
        int n = coins.size();

        // 1D DP tables
        vector<int> nextRow(amount + 1, 0), idealRow(amount + 1, 0);
        nextRow[0] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            idealRow[0] = 1;
            for(int currAmount = 1; currAmount <= amount; ++currAmount) {
                int currSkip = nextRow[currAmount]; 
                int currTake = 0;                                                 
                if(coins[index] <= currAmount) {
                    currTake = idealRow[currAmount - coins[index]];
                }
                idealRow[currAmount] = currTake + currSkip;  
            }
            nextRow = idealRow;
        }

        // Return the result value 
        return nextRow[amount];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/coin-change-ii/description/
        https://cses.fi/problemset/task/1636
