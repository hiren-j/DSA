// Code to find the minimum number of coins needed to acquire all the fruits. The fruit market has the following reward for each fruit: If you purchase the ith fruit at prices[i] coins, you can get any number of the next (i + 1) fruits for free. Note that even if you can take fruit j for free, you can still purchase it for prices[j] coins to receive its reward ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum number of coins needed to acquire all the fruits, using recursion with memoization - O(N*N) & O(N)
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        vector<int> memory(n, -1);
        return solveWithMemo(memory, prices, n, 0);
    }

private:
    // O(N + N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& prices, int n, int i) {
        // Edge case: If all the fruits are exhausted then you can't buy more
        if(i >= n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value 
        if(memory[i] != -1)
            return memory[i];

        // Buy the ith fruit and take the next (i+1) fruits for free
        int minCoins = solveWithMemo(memory, prices, n, i+i+2);

        // Even if you can take the fruits for free, explore the possibility of purchasing each of them and then update the result by the minimum value
        for(int j = i+1; (j <= i+i+1 && j < n); ++j)
            minCoins = min(minCoins, solveWithMemo(memory, prices, n, j));       

        // Store the result value to the memoization table and then return it
        return memory[i] = prices[i] + minCoins;
    }

    // O(N + N^N) & O(N)
    int solveWithoutMemo(vector<int>& prices, int n, int i) {
        // Edge case: If all the fruits are exhausted then you can't buy more
        if(i >= n)
            return 0;

        // Buy the ith fruit and take the next (i+1) fruits for free
        int minCoins = solveWithoutMemo(prices, n, i+i+2);

        // Even if you can take the fruits for free, explore the possibility of purchasing each of them and then update the result by the minimum value
        for(int j = i+1; (j <= i+i+1 && j < n); ++j)
            minCoins = min(minCoins, solveWithoutMemo(prices, n, j));       

        // Return the result value
        return prices[i] + minCoins;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum number of coins needed to acquire all the fruits, using 1D tabulation - O(N*N) & O(N)
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();

        // 1D DP table: dp[i] represents the minimum coins required to buy all the fruits lying within index i to n-1
        vector<int> dp(n, 0);

        // Fill the table
        for(int i = n-1; i >= 0; --i) {
            int minCoins = (i+i+2 < n) ? dp[i+i+2] : 0;

            for(int j = i+1; (j <= i+i+1 && j < n); ++j)
                minCoins = min(minCoins, dp[j]);       

            dp[i] = prices[i] + minCoins;
        }

        // Return the result value
        return dp[0];   
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Queue | Heap (Priority Queue) | Monotonic Queue
Link  : https://leetcode.com/problems/minimum-number-of-coins-for-fruits/description/
