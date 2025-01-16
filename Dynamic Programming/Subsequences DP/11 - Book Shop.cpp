// Code to find the maximum number of pages you can buy. You are in a book shop which sells n different books. You know the price and number of pages of each book. You can buy each book at most once ~ Coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& prices, vector<int>& pages, int index, int x) {
        // Edge case: If all the books are exhausted then you can't buy more
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each book
        int currSkip = solveWithoutMemo(prices, pages, index + 1, x); // Is to skip it
        int currBuy = 0;                                              // Is to buy it  

        // If you have enough money to buy then you can buy the book
        if(x - prices[index] >= 0) 
            currBuy = pages[index] + solveWithoutMemo(prices, pages, index + 1, x - prices[index]);

        // As we're striving for the maximum pages hence return the maximum value
        return max(currSkip, currBuy);
    }

    // O(2*N*X) & O(N*X + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& prices, vector<int>& pages, int index, int x) {
        // Edge case: If all the books are exhausted then you can't buy more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][x] != -1)
            return memory[index][x];

        // There are always two possibilities to perform at each book
        int currSkip = solveWithMemo(memory, prices, pages, index + 1, x); // Is to skip it
        int currBuy = 0;                                                   // Is to buy it  

        // If you have enough money to buy then you can buy the book
        if(x - prices[index] >= 0) 
            currBuy = pages[index] + solveWithMemo(memory, prices, pages, index + 1, x - prices[index]);

        // Store the result value to the memoization table and then return it
        return memory[index][x] = max(currSkip, currBuy);
    }

public:
    // Method to find the maximum number of pages you can buy, using recursion with memoization - O(N*X) & O(N*X)
    int buyMaximumPages(vector<int>& prices, vector<int>& pages, int x) {
        n = prices.size();
        vector<vector<int>> memory(n, vector<int>(x + 1, -1));
        return solveWithMemo(memory, prices, pages, 0, x);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
    int n;

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& prices, vector<int>& pages, int startIndex, int x) {
        // Edge case: If all the books are exhausted then you can't buy more
        if(startIndex == n)
            return 0;

        int maxPages = 0;

        // Try to buy the book at each index and compute the maximum pages
        for(int index = startIndex; index < n; ++index)
            if(x - prices[startIndex] >= 0) 
                maxPages = max(maxPages, pages[startIndex] + solveWithoutMemo(prices, pages, index + 1, x - prices[startIndex]));

        return maxPages;
    }
    
    // O(N*N*X) & O(N*X + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& prices, vector<int>& pages, int startIndex, int x) {
        // Edge case: If all the books are exhausted then you can't buy more
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][x] != -1)
            return memory[startIndex][x];

        int maxPages = 0;

        // Try to buy the book at each index and compute the maximum pages
        for(int index = startIndex; index < n; ++index)
            if(x - prices[startIndex] >= 0) 
                maxPages = max(maxPages, pages[startIndex] + solveWithMemo(memory, prices, pages, index + 1, x - prices[startIndex]));

        // Store the result value to the memoization table and then return it
        return memory[startIndex][x] = maxPages;
    }

public:
    // Method to find the maximum number of pages you can buy, using recursion with memoization - O(N*N*X) & O(N*X)
    int buyMaximumPages(vector<int>& prices, vector<int>& pages, int x) {
        n = prices.size();
        vector<vector<int>> memory(n, vector<int>(x + 1, -1));
        return solveWithMemo(memory, prices, pages, 0, x);
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum number of pages you can buy, using 2D tabulation - O(N*X) & O(N*X)
    int buyMaximumPages_V1(vector<int>& prices, vector<int>& pages, int x) {
        int n = prices.size();

        vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int target = 0; target <= x; ++target) {
                int currSkip = dp[index + 1][target];
                int currBuy = 0;
                if(target - prices[index] >= 0) {
                    currBuy = pages[index] + dp[index + 1][target - prices[index]];
                }
                dp[index][target] = max(currSkip, currBuy);
            }
        }

        return dp[0][x];
    }
    
    // #2 Method to find the maximum number of pages you can buy, using 1D tabulation - O(N*X) & O(X)
    int buyMaximumPages_V2(vector<int>& prices, vector<int>& pages, int x) {
        int n = prices.size();

        vector<int> nextRow(x + 1, 0), idealRow(x + 1, 0);        

        for(int index = n-1; index >= 0; --index) {
            for(int target = 0; target <= x; ++target) {
                int currSkip = nextRow[target];
                int currBuy = 0;
                if(target - prices[index] >= 0) {
                    currBuy = pages[index] + nextRow[target - prices[index]];
                }
                idealRow[target] = max(currSkip, currBuy);
            }
            nextRow = idealRow;
        }

        return idealRow[x];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://cses.fi/problemset/task/1158
