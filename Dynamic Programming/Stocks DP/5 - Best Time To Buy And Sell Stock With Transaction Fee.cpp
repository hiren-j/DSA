// Code to find the maximum profit you can achieve by completing as many transactions as you like, but you need to pay the transaction fee for each transaction ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum profit you can achieve, using recursion with memoization - O(N) & O(N)
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<vector<int>> memory(n, vector<int>(2, -1));
        return solveWithMemo(memory, prices, fee, n, 0, true);
    }

private:
    // O(2*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& prices, int fee, int n, int day, bool canBuy) {
        // Base case: If all the days are exhausted then you can't achieve any profit
        if(day == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[day][canBuy] != -1)
            return memory[day][canBuy];

        // If it's possible to buy the share then we have two possibilities on the day
        if(canBuy) {
            int currBuy  = solveWithMemo(memory, prices, fee, n, day + 1, false) - prices[day] - fee; // Is to buy the share at the current price
            int currSkip = solveWithMemo(memory, prices, fee, n, day + 1, true);                      // Is to skip the buy at the current price 
            return memory[day][canBuy] = max(currBuy, currSkip);                                      // Store the maximum profit to the memoization table and then return it
        }
        // Else when it's possible to sell the share then we have two possibilities on the day
        else {
            int currSell = prices[day] + solveWithMemo(memory, prices, fee, n, day + 1, true); // Is to sell the share at the current price
            int currSkip = solveWithMemo(memory, prices, fee, n, day + 1, false);              // Is to skip the sell at the current price
            return memory[day][canBuy] = max(currSell, currSkip);                              // Store the maximum profit to the memoization table and then return it
        }
    }

    // O(2^N) & O(N) 
    int solveWithoutMemo(vector<int>& prices, int fee, int n, int day, bool canBuy) {
        // Base case: If all the days are exhausted then you can't achieve any profit
        if(day == n)
            return 0;

        // If it's possible to buy the share then we have two possibilities on the day
        if(canBuy) {
            int currBuy  = solveWithoutMemo(prices, fee, n, day + 1, false) - prices[day] - fee; // Is to buy the share at the current price
            int currSkip = solveWithoutMemo(prices, fee, n, day + 1, true);                      // Is to skip the buy at the current price 
            return max(currBuy, currSkip);                                                       // As we're striving for the maximum profit hence return the maximum value
        }
        // Else when it's possible to sell the share then we have two possibilities on the day
        else {
            int currSell = prices[day] + solveWithoutMemo(prices, fee, n, day + 1, true); // Is to sell the share at the current price
            int currSkip = solveWithoutMemo(prices, fee, n, day + 1, false);              // Is to skip the sell at the current price
            return max(currSell, currSkip);                                               // As we're striving for the maximum profit hence return the maximum value
        }
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum profit you can achieve, using 2D tabulation - O(N*2) & O(N*2)
    int maxProfit_V1(vector<int>& prices, int fee) {
        int n = prices.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        // Fill the table
        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int currBuy  = dp[day + 1][false] - prices[day] - fee;
                    int currSkip = dp[day + 1][true];
                    dp[day][canBuy] = max(currBuy, currSkip);
                }
                else {
                    int currSell = prices[day] + dp[day + 1][true];
                    int currSkip = dp[day + 1][false];
                    dp[day][canBuy] = max(currSell, currSkip);
                }
            }
        }

        // Return the result value
        return dp[0][true];
    }

    // #2 Method to find the maximum profit you can achieve, using 1D tabulation - O(N*2) & O(1)
    int maxProfit_V2(vector<int>& prices, int fee) {
        int n = prices.size();

        // 1D DP tables
        vector<int> nextRow(2, 0), idealRow(2, 0);

        // Fill the table
        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int currBuy  = nextRow[false] - prices[day] - fee;
                    int currSkip = nextRow[true];
                    idealRow[canBuy] = max(currBuy, currSkip);
                }
                else {
                    int currSell = prices[day] + nextRow[true];
                    int currSkip = nextRow[false];
                    idealRow[canBuy] = max(currSell, currSkip);
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[true];
    }

    // #3 Method to find the maximum profit you can achieve, using constant auxiliary space - O(N*2) & O(1)
    int maxProfit_V3(vector<int>& prices, int fee) {
        int n = prices.size();

        int nextSell = 0, nextBuy   = 0;
        int idealBuy = 0, idealSell = 0;

        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int currBuy  = nextSell - prices[day] - fee;
                    int currSkip = nextBuy;
                    idealBuy = max(currBuy, currSkip);
                }
                else {
                    int currSell = prices[day] + nextBuy;
                    int currSkip = nextSell;
                    idealSell = max(currSell, currSkip);
                }
            }
            nextBuy  = idealBuy;
            nextSell = idealSell;
        }

        return idealBuy;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
