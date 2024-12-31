// Code to break the given n into the sum of k positive integers, where k >= 2, and maximize the product of those integers ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum product you can get, using recursion with memoization - O(N*N) & O(N)
    int integerBreak(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, n);
    }

private:
    // O(N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, int n) {
        // Edge case: If n is less than or equal to 2 then the maximum product you can get is 1
        if(n <= 2)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n] != -1)
            return memory[n];

        // Stores the result value
        int maxProduct = INT_MIN;

        // Explore all the possibilities of breaking the n and update the result by the maximum value
        for(int num = 1; num <= n-1; ++num) {
            int nextProduct = max(n - num, solveWithMemo(memory, n - num));
            maxProduct      = max(maxProduct, num * nextProduct);
        }

        // Store the result value to the memoization table and then return it
        return memory[n] = maxProduct;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(int n) {
        // Edge case: If n is less than or equal to 2 then the maximum product you can get is 1
        if(n <= 2)
            return 1;

        // Stores the result value
        int maxProduct = INT_MIN;

        // Explore all the possibilities of breaking the n and update the result by the maximum value
        for(int num = 1; num <= n-1; ++num) {
            int nextProduct = max(n - num, solveWithoutMemo(n - num));
            maxProduct      = max(maxProduct, num * nextProduct);
        }

        // Return the result value
        return maxProduct;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the maximum product you can get, using 1D tabulation - O(N*N) & O(N)
    int integerBreak(int n) {    
        // 1D DP table
        vector<int> dp(n + 1, INT_MIN);

        // Initialize the edge case: If n is less than or equal to 2 then the maximum product you can get is 1
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 1;
        
        // Fill the rest of the table
        for(int index = 3; index <= n; ++index) {
            int maxProduct = INT_MIN;
            for(int num = 1; num <= n-1; ++num) {
                if(index - num >= 0) {
                    int nextProduct = max(index - num, dp[index - num]);
                    maxProduct      = max(maxProduct, num * nextProduct);
                }
            }
            dp[index] = maxProduct;
        } 

        // Return the result value
        return dp[n];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming
Link  : https://leetcode.com/problems/integer-break/description/
