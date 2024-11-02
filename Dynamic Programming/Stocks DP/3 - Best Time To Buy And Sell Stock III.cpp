// Code to find the maximum profit you can achieve by completing at most two transactions ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum profit you can achieve, using recursion with memoization - O(N) & O(N)
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> memory(n, vector<vector<int>>(2, vector<int>(3, -1)));
        return solveWithMemo(memory, prices, n, 0, true, 2);
    }

private:
    // O(2*N*2*3) & O(N*2*3 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& prices, int n, int day, bool canBuy, int k) {
        // Edge case: If all the days are exhausted or you've done two transactions then you can't achieve any profit
        if(day == n || k == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[day][canBuy][k] != -1)
            return memory[day][canBuy][k];

        // If it's possible to buy the share then we have two possibilities on the day
        if(canBuy) {
            int currBuy  = solveWithMemo(memory, prices, n, day + 1, false, k) - prices[day]; // Is to buy the share at the current price
            int currSkip = solveWithMemo(memory, prices, n, day + 1, true, k);                // Is to skip the buy at the current price 
            return memory[day][canBuy][k] = max(currBuy, currSkip);                           // Store the maximum profit to the memoization table and then return it
        }
        // Else when it's possible to sell the share then we have two possibilities on the day
        else {
            int currSell = prices[day] + solveWithMemo(memory, prices, n, day + 1, true, k - 1); // Is to sell the share at the current price
            int currSkip = solveWithMemo(memory, prices, n, day + 1, false, k);                  // Is to skip the sell at the current price
            return memory[day][canBuy][k] = max(currSell, currSkip);                             // Store the maximum profit to the memoization table and then return it
        }
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& prices, int n, int day, bool canBuy, int k) {
        // Edge case: If all the days are exhausted or you've done two transactions then you can't achieve any profit
        if(day == n || k == 0)
            return 0;

        // If it's possible to buy the share then we have two possibilities on the day
        if(canBuy) {
            int currBuy  = solveWithoutMemo(prices, n, day + 1, false, k) - prices[day]; // Is to buy the share at the current price
            int currSkip = solveWithoutMemo(prices, n, day + 1, true, k);                // Is to skip the buy at the current price 
            return max(currBuy, currSkip);                                               // As we're striving for the maximum profit hence return the maximum value
        }
        // Else when it's possible to sell the share then we have two possibilities on the day
        else {
            int currSell = prices[day] + solveWithoutMemo(prices, n, day + 1, true, k - 1); // Is to sell the share at the current price
            int currSkip = solveWithoutMemo(prices, n, day + 1, false, k);                  // Is to skip the sell at the current price
            return max(currSell, currSkip);                                                 // As we're striving for the maximum profit hence return the maximum value
        }
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum profit you can achieve, using 3D tabulation - O(N*2*3) & O(N*2*3)
    int maxProfit_V1(vector<int>& prices) {
        int n = prices.size();

        // 3D DP table
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        // Fill the table
        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                for(int k = 1; k <= 2; ++k) {
                    if(canBuy) {
                        int currBuy  = dp[day + 1][false][k] - prices[day];
                        int currSkip = dp[day + 1][true][k];
                        dp[day][canBuy][k] = max(currBuy, currSkip);
                    }
                    else {
                        int currSell = prices[day] + dp[day + 1][true][k - 1];
                        int currSkip = dp[day + 1][false][k];
                        dp[day][canBuy][k] = max(currSell, currSkip);
                    }
                }
            }
        }

        // Return the result value
        return dp[0][1][2];
    }

    // #2 Method to find the maximum profit you can achieve, using 2D tabulation - O(N*2*3) & O(2*3)
    int maxProfit_V2(vector<int>& prices) {
        int n = prices.size();

        // 2D DP tables
        vector<vector<int>> nextRow(2, vector<int>(3, 0)), idealRow(2, vector<int>(3, 0));

        // Fill the table
        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                for(int k = 1; k <= 2; ++k) {
                    if(canBuy) {
                        int currBuy  = nextRow[false][k] - prices[day];
                        int currSkip = nextRow[true][k];
                        idealRow[canBuy][k] = max(currBuy, currSkip);
                    }
                    else {
                        int currSell = prices[day] + nextRow[true][k - 1];
                        int currSkip = nextRow[false][k];
                        idealRow[canBuy][k] = max(currSell, currSkip);
                    }
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[1][2];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
