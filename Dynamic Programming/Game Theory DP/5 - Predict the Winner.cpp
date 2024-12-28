// Code to check if player1 can win the game by assuming both player1 and player2 play optimally, if player1 can't then return false ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to check if player1 can win the game or not, using recursion with memoization - O(N^2) & O(N^2)
    bool predictTheWinner(vector<int>& piles) {
        int n = piles.size();
        vector<vector<vector<int>>> memory(n, vector<vector<int>>(n, vector<int>(2, -1)));
        int p1Score = solveWithMemo(memory, piles, 0, n-1, true);
        int p2Score = accumulate(begin(piles), end(piles), 0) - p1Score;
        return (p1Score >= p2Score);
    }

private:
    // O(2*N*N*2) & O(N*N*2 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& piles, int i, int j, bool p1Turn) {
        // Edge case: If all the piles are exhausted then player1 can't take more stones 
        if(i > j)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j][p1Turn] != -1)
            return memory[i][j][p1Turn];

        // If its player1's turn then he have two posibilities to perform 
        if(p1Turn) {
            int takeFromStart = piles[i] + solveWithMemo(memory, piles, i+1, j, false); // Is to take ith element
            int takeFromEnd   = piles[j] + solveWithMemo(memory, piles, i, j-1, false); // Is to take jth element
            return memory[i][j][p1Turn] = max(takeFromStart, takeFromEnd); // If its player1's turn then he absolutely wanted to win, So for that he wants to maximize his score, so he will take the maximum value from both the possibility
        }
        // If its player2's turn then he have two posibilities to perform 
        else {
            int takeFromStart = solveWithMemo(memory, piles, i+1, j, true); // Is to take ith element
            int takeFromEnd   = solveWithMemo(memory, piles, i, j-1, true); // Is to take jth element
            return memory[i][j][p1Turn] = min(takeFromStart, takeFromEnd); // If its player2's turn then he absolutely wanted player1 to lose, So for that he wants player1 to minimize his score, so player2 will take the minimum value from both the possibility
        }
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& piles, int i, int j, bool p1Turn) {
        // Edge case: If all the piles are exhausted then player1 can't take more stones 
        if(i > j)
            return 0;

        // If its player1's turn then he have two posibilities to perform 
        if(p1Turn) {
            int takeFromStart = piles[i] + solveWithoutMemo(piles, i+1, j, false); // Is to take ith element
            int takeFromEnd   = piles[j] + solveWithoutMemo(piles, i, j-1, false); // Is to take jth element
            return max(takeFromStart, takeFromEnd); // If its player1's turn then he absolutely wanted to win, So for that he wants to maximize his score, so he will take the maximum value from both the possibility
        }
        // If its player2's turn then he have two posibilities to perform 
        else {
            int takeFromStart = solveWithoutMemo(piles, i+1, j, true); // Is to take ith element
            int takeFromEnd   = solveWithoutMemo(piles, i, j-1, true); // Is to take jth element
            return min(takeFromStart, takeFromEnd); // If its player2's turn then he absolutely wanted player1 to lose, So for that he wants player1 to minimize his score, so player2 will take the minimum value from both the possibility
        }
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
public:
    // #1 Method to check if player1 can win the game or not, using 3D tabulation - O(N^2) & O(N^2)
    bool predictTheWinner_V1(vector<int>& piles) {
        int n = piles.size();

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                if(i > j)
                    continue;
                    
                for(int p1Turn = 0; p1Turn <= 1; ++p1Turn) {
                    if(p1Turn) {
                        int takeFromStart = piles[i] + (i+1 < n ? dp[i+1][j][false] : 0);
                        int takeFromEnd   = piles[j] + (j-1 >= 0 ? dp[i][j-1][false] : 0);
                        dp[i][j][p1Turn] = max(takeFromStart, takeFromEnd);
                    }
                    else {
                        int takeFromStart = (i+1 < n ? dp[i+1][j][true] : 0);
                        int takeFromEnd   = (j-1 >= 0 ? dp[i][j-1][true] : 0);
                        dp[i][j][p1Turn] = min(takeFromStart, takeFromEnd);
                    }
                }
            }
        }

        int p1Score = dp[0][n-1][true];
        int p2Score = accumulate(begin(piles), end(piles), 0) - p1Score;

        return (p1Score >= p2Score);
    }

    // #2 Method to check if player1 can win the game or not, using 2D tabulation - O(N^2) & O(N)
    bool predictTheWinner_V2(vector<int>& piles) {
        int n = piles.size();

        vector<vector<int>> nextRow(n, vector<int>(2, 0));

        for(int i = n-1; i >= 0; --i) {
            vector<vector<int>> currRow(n, vector<int>(2, 0));
            for(int j = 0; j <= n-1; ++j) {
                if(i > j)
                    continue;
                    
                for(int p1Turn = 0; p1Turn <= 1; ++p1Turn) {
                    if(p1Turn) {
                        int takeFromStart = piles[i] + (i+1 < n ? nextRow[j][false] : 0);
                        int takeFromEnd   = piles[j] + (j-1 >= 0 ? currRow[j-1][false] : 0);
                        currRow[j][p1Turn] = max(takeFromStart, takeFromEnd);
                    }
                    else {
                        int takeFromStart = (i+1 < n ? nextRow[j][true] : 0);
                        int takeFromEnd   = (j-1 >= 0 ? currRow[j-1][true] : 0);
                        currRow[j][p1Turn] = min(takeFromStart, takeFromEnd);
                    }
                }
            }
            nextRow = currRow;
        }

        int p1Score = nextRow[n-1][true];
        int p2Score = accumulate(begin(piles), end(piles), 0) - p1Score;

        return (p1Score >= p2Score);
    }
};
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Dynamic Programming | Recursion | Game Theory
Link  : https://leetcode.com/problems/predict-the-winner/
