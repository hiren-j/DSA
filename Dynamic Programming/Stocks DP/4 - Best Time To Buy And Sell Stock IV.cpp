// Code to find the maximum profit you can achieve by completing at most k transactions ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum profit you can achieve, using recursion with memoization - O(N*K) & O(N*K)
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> memory(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return solveWithMemo(memory, k, prices, n, 0, true);
    }
    
private:
    // O(2*N*2*K) & O(N*2*K + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int k, vector<int>& prices, int n, int day, bool canBuy) {
        // Edge case: If all the days are exhausted or you've done total transactions then you can't achieve any profit
        if(day == n || k == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[day][canBuy][k] != -1)
            return memory[day][canBuy][k];

        // If it's possible to buy the share then we have two possibilities on the day
        if(canBuy) {
            int currBuy  = solveWithMemo(memory, k, prices, n, day + 1, false) - prices[day]; // Is to buy the share at the current price
            int currSkip = solveWithMemo(memory, k, prices, n, day + 1, true);                // Is to skip the buy at the current price
            return memory[day][canBuy][k] = max(currBuy, currSkip);                           // Store the maximum profit to the memoization table and then return it
        }
        // Else when it's possible to sell the share then we have two possibilities on the day
        else {
            int currSell = prices[day] + solveWithMemo(memory, k - 1, prices, n, day + 1, true); // Is to sell the share at the current price
            int currSkip = solveWithMemo(memory, k, prices, n, day + 1, false);                  // Is to skip the sell at the current price
            return memory[day][canBuy][k] = max(currSell, currSkip);                             // Store the maximum profit to the memoization table and then return it
        }
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(int k, vector<int>& prices, int n, int day, bool canBuy) {
        // Edge case: If all the days are exhausted or you've done total transactions then you can't achieve any profit
        if(day == n || k == 0)
            return 0;

        // If it's possible to buy the share then we have two possibilities on the day
        if(canBuy) {
            int currBuy  = solveWithoutMemo(k, prices, n, day + 1, false) - prices[day]; // Is to buy the share at the current price
            int currSkip = solveWithoutMemo(k, prices, n, day + 1, true);                // Is to skip the buy at the current price
            return max(currBuy, currSkip);                                               // As we're striving for maximum profit hence return the maximum value
        }
        // Else when it's possible to sell the share then we have two possibilities on the day
        else {
            int currSell = prices[day] + solveWithoutMemo(k - 1, prices, n, day + 1, true); // Is to sell the share at the current price
            int currSkip = solveWithoutMemo(k, prices, n, day + 1, false);                  // Is to skip the sell at the current price
            return max(currSell, currSkip);                                                 // As we're striving for maximum profit hence return the maximum value
        }
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum profit you can achieve, using 3D tabulation - O(N*2*K) & O(N*2*K)
    int maxProfit_V1(int k, vector<int>& prices) {
        int n = prices.size();

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                for(int limit = 1; limit <= k; ++limit) {
                    if(canBuy) {
                        int currBuy  = dp[day + 1][false][limit] - prices[day];
                        int currSkip = dp[day + 1][true][limit];
                        dp[day][canBuy][limit] = max(currBuy, currSkip);
                    }
                    else {
                        int currSell = prices[day] + dp[day + 1][true][limit - 1];
                        int currSkip = dp[day + 1][false][limit];
                        dp[day][canBuy][limit] = max(currSell, currSkip);
                    }   
                }
            }
        }

        return dp[0][true][k];
    }

    // #2 Method to find the maximum profit you can achieve, using 2D tabulation - O(N*2*K) & O(2*K)
    int maxProfit_V2(int k, vector<int>& prices) {
        int n = prices.size();

        vector<vector<int>> nextRow(2, vector<int>(k + 1, 0)), idealRow(2, vector<int>(k + 1, 0));

        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                for(int limit = 1; limit <= k; ++limit) {
                    if(canBuy) {
                        int currBuy  = nextRow[false][limit] - prices[day];
                        int currSkip = nextRow[true][limit];
                        idealRow[canBuy][limit] = max(currBuy, currSkip);
                    }
                    else {
                        int currSell = prices[day] + nextRow[true][limit - 1];
                        int currSkip = nextRow[false][limit];
                        idealRow[canBuy][limit] = max(currSell, currSkip);
                    }   
                }
            }
            nextRow = idealRow;
        }

        return idealRow[true][k];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/
