// Code to check if Alice can win the game by assuming both Alice and Bob play optimally, if Alice can't then return false ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to check if Alice can win the game or not, using recursion with memoization - O(N^2) & O(N^2)
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<vector<int>>> memory(n, vector<vector<int>>(n, vector<int>(2, -1)));
        int aliceStones = solveWithMemo(memory, piles, 0, n-1, true);
        int bobStones   = accumulate(begin(piles), end(piles), 0) - aliceStones;
        return (aliceStones >= bobStones);
    }

private:
    // O(2*N*N*2) & O(N*N*2 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& piles, int i, int j, bool aliceTurn) {
        // Edge case: If all the piles are exhausted then Alice can't take more stones 
        if(i > j)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j][aliceTurn] != -1)
            return memory[i][j][aliceTurn];

        // If its Alice's turn then she have two posibilities to perform 
        if(aliceTurn) {
            int takeFromStart = piles[i] + solveWithMemo(memory, piles, i+1, j, false); // Is to take ith element
            int takeFromEnd   = piles[j] + solveWithMemo(memory, piles, i, j-1, false); // Is to take jth element
            return memory[i][j][aliceTurn] = max(takeFromStart, takeFromEnd); // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from both the possibility
        }
        // If its Bob's turn then he have two posibilities to perform 
        else {
            int takeFromStart = solveWithMemo(memory, piles, i+1, j, true); // Is to take ith element
            int takeFromEnd   = solveWithMemo(memory, piles, i, j-1, true); // Is to take jth element
            return memory[i][j][aliceTurn] = min(takeFromStart, takeFromEnd); // If its Bob's turn then he absolutely wanted Alice to lose, So for that he wants Alice to minimize her score, so Bob will take the minimum value from both the possibility
        }
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& piles, int i, int j, bool aliceTurn) {
        // Edge case: If all the piles are exhausted then Alice can't take more stones 
        if(i > j)
            return 0;

        // If its Alice's turn then she have two posibilities to perform 
        if(aliceTurn) {
            int takeFromStart = piles[i] + solveWithoutMemo(piles, i+1, j, false); // Is to take ith element
            int takeFromEnd   = piles[j] + solveWithoutMemo(piles, i, j-1, false); // Is to take jth element
            return max(takeFromStart, takeFromEnd); // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from both the possibility
        }
        // If its Bob's turn then he have two posibilities to perform 
        else {
            int takeFromStart = solveWithoutMemo(piles, i+1, j, true); // Is to take ith element
            int takeFromEnd   = solveWithoutMemo(piles, i, j-1, true); // Is to take jth element
            return min(takeFromStart, takeFromEnd); // If its Bob's turn then he absolutely wanted Alice to lose, So for that he wants Alice to minimize her score, so Bob will take the minimum value from both the possibility
        }
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to check if Alice can win the game or not, using tabulation :-
    bool stoneGame(vector<int>& piles) {
        return solveUsing2DTable(piles, piles.size());
    }

private:
    // O(N^2) & O(N)
    bool solveUsing2DTable(vector<int>& piles, int n) {
        vector<vector<int>> nextRow(n, vector<int>(2, 0)), currRow(n, vector<int>(2, 0));

        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                    if(i > j) 
                        continue;
                    
                    if(aliceTurn) {
                        int takeFromStart = piles[i] + (i+1 < n ? nextRow[j][false] : 0);
                        int takeFromEnd   = piles[j] + (j-1 >= 0 ? currRow[j-1][false] : 0);
                        currRow[j][aliceTurn] = max(takeFromStart, takeFromEnd);
                    }
                    else {
                        int takeFromStart = (i+1 < n ? nextRow[j][true] : 0);
                        int takeFromEnd   = (j-1 >= 0 ? currRow[j-1][true] : 0);
                        currRow[j][aliceTurn] = min(takeFromStart, takeFromEnd);
                    }
                }
            }
            nextRow = currRow;
        }

        int aliceStones = currRow[n-1][true];
        int bobStones   = accumulate(begin(piles), end(piles), 0) - aliceStones;

        return (aliceStones >= bobStones);
    }

    // O(N^2) & O(N^2)
    bool solveUsing3DTable(vector<int>& piles, int n) {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, 0)));
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                if(i > j)
                    continue;
                    
                for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                    if(aliceTurn) {
                        int takeFromStart = piles[i] + (i+1 < n ? dp[i+1][j][false] : 0);
                        int takeFromEnd   = piles[j] + (j-1 >= 0 ? dp[i][j-1][false] : 0);
                        dp[i][j][aliceTurn] = max(takeFromStart, takeFromEnd);
                    }
                    else {
                        int takeFromStart = (i+1 < n ? dp[i+1][j][true] : 0);
                        int takeFromEnd   = (j-1 >= 0 ? dp[i][j-1][true] : 0);
                        dp[i][j][aliceTurn] = min(takeFromStart, takeFromEnd);
                    }
                }
            }
        }

        int aliceStones = dp[0][n-1][true];
        int bobStones   = accumulate(begin(piles), end(piles), 0) - aliceStones;

        return (aliceStones >= bobStones);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Maths {
public:
    // Method to check if Alice can win the game or not, using brain - O(1) & O(1)
    bool stoneGame(vector<int>& piles) {
        /* 
            Alice always wins the game : Read the reason with below example

            1. We know both Alice and Bob have two possibility - Is that the player with its turn can take the entire pile of stones either from the beginning or from the end of the row

            2. If you notice the player who starts the game have two possibilities:-
                - If he chooses the possibility of taking the entire piles from extreme left then this player will absolutely be moving in odd fashion (1-based indexing)
                - If he chooses the possibility of taking the entire piles from extreme right then this player will absolutely be moving in even fashion (1-based indexing)

            3. So, Lets understand with the Example : [5, 2, 3, 3]
                                            Position - 1  2  3  4

                -> We know Alice always starts the game, then the odd fashion result of Alice will be :-
                        Alice Stones - [5, 3] (Maximum is 8)
                        Bob Stones   - [2, 3] (Maximum is 5)

                -> We know Alice always starts the game, then the even fashion result of Alice will be :-
                        Alice Stones - [3, 2] (Maximum is 5) 
                        Bob Stones   - [3, 5] (Maximum is 8)


            Imp: If you notice, you can see both the players have choosen all positions from both the possibility,
                 that means Alice and Bob both got the maximum results, So both are going to Win? No, Its not like that. Both the players are playing optimally and we know that Alice will start the game, so Alice knows at any point of time to consider which pile of stone and which not. So if she's getting maximum stones by starting from the extreme left then she will choose this possibility or if she's getting maximum from the extreme right then she will choose this possibility. 
                 In conclusion, Alice will always pick the possibility which will lead to the maximum stones or could say Alice will always start the game from the possibility which will lead to the maximum stones. So this how Alice always win the game
        */

        return true;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Dynamic Programming | Game Theory
Link  : https://leetcode.com/problems/stone-game/
