// Code to find the maximum possible amount of money alice can win if she go first. Alice play against Bob in an alternating way. In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the value of the coin. Note that both the players are playing optimally ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long LL;
    
public:
    // Method to find the maximum amount of money alice can win, using recursion with memoization - O(N^2) & O(N^2)
    LL maximumAmount(int n, vector<int>& coins) {
        vector<vector<vector<LL>>> dp(n, vector<vector<LL>>(n, vector<LL>(2, -1)));
        return solveWithMemo(dp, coins, 0, n-1, true);
    }
    
private:
    // O(2*N*N*2) & O(N*N*2 + N)
    LL solveWithMemo(vector<vector<vector<LL>>>& dp, vector<int>& coins, int i, int j, bool aliceTurn) {
        // Edge case: If all the coins are exhausted then Alice can't take more
        if(i > j)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(dp[i][j][aliceTurn] != -1)
            return dp[i][j][aliceTurn];
        
        // If its Alice's turn then she have two posibilities to perform
        if(aliceTurn) {
            LL takeFirst = coins[i] + solveWithMemo(dp, coins, i+1, j, false); // Is to take ith coin
            LL takeLast  = coins[j] + solveWithMemo(dp, coins, i, j-1, false); // Is to take jth coin
            return dp[i][j][aliceTurn] = max(takeFirst, takeLast); // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from both the possibility
        }
        // If its Bob's turn then he have two posibilities to perform
        else {
            LL takeFirst = solveWithMemo(dp, coins, i+1, j, true); // Is to take ith coin
            LL takeLast  = solveWithMemo(dp, coins, i, j-1, true); // Is to take jth coin
            return dp[i][j][aliceTurn] = min(takeFirst, takeLast); // If its Bob's turn then he absolutely wanted Alice to lose, So for that he wants Alice to minimize her score, so Bob will take the minimum value from both the possibility 
        }
    }

    // O(2^N) & O(N)
    LL solveWithoutMemo(vector<int>& coins, int i, int j, bool aliceTurn) {
        // Edge case: If all the coins are exhausted then Alice can't take more
        if(i > j)
            return 0;
        
        // If its Alice's turn then she have two posibilities to perform
        if(aliceTurn) {
            LL takeFirst = coins[i] + solveWithoutMemo(coins, i+1, j, false); // Is to take ith coin
            LL takeLast  = coins[j] + solveWithoutMemo(coins, i, j-1, false); // Is to take jth coin
            return max(takeFirst, takeLast); // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from both the possibility
        }
        // If its Bob's turn then he have two posibilities to perform
        else {
            LL takeFirst = solveWithoutMemo(coins, i+1, j, true); // Is to take ith coin
            LL takeLast  = solveWithoutMemo(coins, i, j-1, true); // Is to take jth coin
            return min(takeFirst, takeLast); // If its Bob's turn then he absolutely wanted Alice to lose, So for that he wants Alice to minimize her score, so Bob will take the minimum value from both the possibility 
        }
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long LL;
    
public:
    // #1 Method to find the maximum amount of money alice can win, using 3D tabulation - O(N^2) & O(N^2)
    LL maximumAmount_V1(int n, vector<int>& coins) {
        vector<vector<vector<LL>>> dp(n, vector<vector<LL>>(n, vector<LL>(2, 0)));
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                if(i > j)
                    continue;
                
                for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {                        
                    if(aliceTurn) {
                        LL takeFirst = coins[i] + (i+1 < n ? dp[i+1][j][false] : 0);
                        LL takeLast  = coins[j] + (j-1 >= 0 ? dp[i][j-1][false] : 0);
                        dp[i][j][aliceTurn] = max(takeFirst, takeLast);
                    }
                    else {
                        LL takeFirst = (i+1 < n ? dp[i+1][j][true] : 0);
                        LL takeLast  = (j-1 >= 0 ? dp[i][j-1][true] : 0);
                        dp[i][j][aliceTurn] = min(takeFirst, takeLast);
                    }
                }
            }
        }
        
        return dp[0][n-1][true];
    }

    // #2 Method to find the maximum amount of money alice can win, using 2D tabulation - O(N^2) & O(N)
    LL maximumAmount_V2(int n, vector<int>& coins) {
        vector<vector<LL>> nextRow(n, vector<LL>(2, 0)), currRow(n, vector<LL>(2, 0));
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                    if(i > j) 
                        continue;
                        
                    if(aliceTurn) {
                        LL takeFirst = coins[i] + (i+1 < n ? nextRow[j][false] : 0);
                        LL takeLast  = coins[j] + (j-1 >= 0 ? currRow[j-1][false] : 0);
                        currRow[j][aliceTurn] = max(takeFirst, takeLast);
                    }
                    else {
                        LL takeFirst = (i+1 < n ? nextRow[j][true] : 0);
                        LL takeLast  = (j-1 >= 0 ? currRow[j-1][true] : 0);
                        currRow[j][aliceTurn] = min(takeFirst, takeLast);
                    }
                }
            }
            nextRow = currRow;
        }
        
        return currRow[n-1][true];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Game Theory
Links : https://www.geeksforgeeks.org/problems/optimal-strategy-for-a-game-1587115620/1
        https://cses.fi/problemset/task/1097
