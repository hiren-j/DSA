// Code to maximize the number of coins collected by player X. Two players X and Y are playing a game in which there are pots of gold arranged in a line, each containing some gold coins. They get alternating turns in which the player can pick a pot from one of the ends of the line. The winner is the player who has a higher number of coins at the end. Note that both the players are playing optimally ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the maximum amount of money player X can get, using recursion with memoization - O(N^2) & O(N^2)
    int maxCoins(vector<int>& coins, int n) {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -1)));
        return solveWithMemo(dp, coins, 0, n-1, true);
    }
    
private:
    // O(2*N*N*2) & O(N*N*2 + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, vector<int>& coins, int i, int j, bool isXTurn) {
        if(i > j)
            return 0;
            
        if(dp[i][j][isXTurn] != -1)
            return dp[i][j][isXTurn];
        
        if(isXTurn) {
            int pickFromStart = coins[i] + solveWithMemo(dp, coins, i+1, j, false);
            int pickFromEnd   = coins[j] + solveWithMemo(dp, coins, i, j-1, false);
            return dp[i][j][isXTurn] = max(pickFromStart, pickFromEnd);
        }
        else {
            int pickFromStart = solveWithMemo(dp, coins, i+1, j, true);
            int pickFromEnd   = solveWithMemo(dp, coins, i, j-1, true);
            return dp[i][j][isXTurn] = min(pickFromStart, pickFromEnd);
        }
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& coins, int i, int j, bool isXTurn) {
        if(i > j)
            return 0;
                    
        if(isXTurn) {
            int pickFromStart = coins[i] + solveWithoutMemo(coins, i+1, j, false);
            int pickFromEnd   = coins[j] + solveWithoutMemo(coins, i, j-1, false);
            return max(pickFromStart, pickFromEnd);
        }
        else {
            int pickFromStart = solveWithoutMemo(coins, i+1, j, true);
            int pickFromEnd   = solveWithoutMemo(coins, i, j-1, true);
            return min(pickFromStart, pickFromEnd);
        }
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the maximum amount of money player X can get, using tabulation :-
    int maxCoins(vector<int>& coins, int n) {
        return solveUsing2DTable(coins, n);
    }

private:
    // O(N^2) & O(N)
    int solveUsing2DTable(vector<int>& coins, int n) {
        vector<vector<int>> nextRow(n, vector<int>(2, 0)), idealRow(n, vector<int>(2, 0));
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                if(i > j)
                    continue;
                
                for(int isXTurn = 0; isXTurn <= 1; ++isXTurn) {
                    if(isXTurn) {
                        int pickFromStart = coins[i] + (i+1 < n ? nextRow[j][false] : 0);
                        int pickFromEnd   = coins[j] + (j-1 >= 0 ? idealRow[j-1][false] : 0);
                        idealRow[j][isXTurn] = max(pickFromStart, pickFromEnd);
                    }
                    else {
                        int pickFromStart = (i+1 < n ? nextRow[j][true] : 0);
                        int pickFromEnd   = (j-1 >= 0 ? idealRow[j-1][true] : 0);
                        idealRow[j][isXTurn] = min(pickFromStart, pickFromEnd);
                    }   
                }
            }
            nextRow = idealRow;
        }
        
        return idealRow[n-1][true];
    }

    // O(N^2) & O(N^2)
    int solveUsing3DTable(vector<int>& coins, int n) {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                if(i > j)
                    continue;

                for(int isXTurn = 0; isXTurn <= 1; ++isXTurn) {
                    if(isXTurn) {
                        int pickFromStart = coins[i] + (i+1 < n ? dp[i+1][j][false] : 0);
                        int pickFromEnd   = coins[j] + (j-1 >= 0 ? dp[i][j-1][false] : 0);
                        dp[i][j][isXTurn] = max(pickFromStart, pickFromEnd);
                    }
                    else {
                        int pickFromStart = (i+1 < n ? dp[i+1][j][true] : 0);
                        int pickFromEnd   = (j-1 >= 0 ? dp[i][j-1][true] : 0);
                        dp[i][j][isXTurn] = min(pickFromStart, pickFromEnd);
                    }   
                }
            }
        }
        
        return dp[0][n-1][true];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Game Theory
Links : https://www.geeksforgeeks.org/problems/pots-of-gold-game/1
        https://cses.fi/problemset/task/1097
