// Code to check if you can win the game by assuming both you and your friend play optimally, if you can't then return false ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to check if you can win the game or not, using recursion with memoization - O(N) & O(N)
    bool canWinNim(int n) {
        vector<vector<int>> memory(n + 1, vector<int>(2, -1));
        return solveWithMemo(memory, n, true);
    }

private:
    // O(3*N*2) & O(N*2 + N)
    bool solveWithMemo(vector<vector<int>>& memory, int n, bool myTurn) {
        // Edge case: If there are no stones in the heap and if its your friend's turn then you've win the game as previously you've picked the last stone
        if(n <= 0)
            return !myTurn;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n][myTurn] != -1)
            return memory[n][myTurn];

        // If its your turn then you've three posibilities to perform
        if(myTurn) {
            bool remove1Stone = solveWithMemo(memory, n - 1, false); // Is to remove exactly 1 stone from the heap
            bool remove2Stone = solveWithMemo(memory, n - 2, false); // Is to remove exactly 2 stone from the heap
            bool remove3Stone = solveWithMemo(memory, n - 3, false); // Is to remove exactly 3 stone from the heap
            return memory[n][myTurn] = (remove1Stone || remove2Stone || remove3Stone); // If its your turn then you absolutely wanted to win, so if you can win the game by any of the possibility then return true
        } 
        // If its your friend's turn then he also have three posibilities to perform
        else {
            bool remove1Stone = solveWithMemo(memory, n - 1, true); // Is to remove exactly 1 stone from the heap
            bool remove2Stone = solveWithMemo(memory, n - 2, true); // Is to remove exactly 2 stone from the heap
            bool remove3Stone = solveWithMemo(memory, n - 3, true); // Is to remove exactly 3 stone from the heap
            return memory[n][myTurn] = !(!remove1Stone || !remove2Stone || !remove3Stone); // If its your friend's turn then he absolutely wanted you to lose, so if you lose the game by any of the possibility then the friend will return false
        }
    }

    // O(3^N) & O(N)
    bool solveWithoutMemo(int n, bool myTurn) {
        // Edge case: If there are no stones in the heap and if its your friend's turn then you've win the game as previously you've picked the last stone
        if(n <= 0)
            return !myTurn;

        // If its your turn then you've three posibilities to perform
        if(myTurn) {
            bool remove1Stone = solveWithoutMemo(n - 1, false); // Is to remove exactly 1 stone from the heap
            bool remove2Stone = solveWithoutMemo(n - 2, false); // Is to remove exactly 2 stone from the heap
            bool remove3Stone = solveWithoutMemo(n - 3, false); // Is to remove exactly 3 stone from the heap
            return (remove1Stone || remove2Stone || remove3Stone); // If its your turn then you absolutely wanted to win, so if you can win the game by any of the possibility then return true
        } 
        // If its your friend's turn then he also have three posibilities to perform
        else {
            bool remove1Stone = solveWithoutMemo(n - 1, true); // Is to remove exactly 1 stone from the heap
            bool remove2Stone = solveWithoutMemo(n - 2, true); // Is to remove exactly 2 stone from the heap
            bool remove3Stone = solveWithoutMemo(n - 3, true); // Is to remove exactly 3 stone from the heap
            return !(!remove1Stone || !remove2Stone || !remove3Stone); // If its your friend's turn then he absolutely wanted you to lose, so if you lose the game by any of the possibility then the friend will return false
        }
    }
};
// Note: This solution can lead to memory exhaustion due to the memoization table. It's because the value of N could be very high

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to check if you can win the game or not, using 2D tabulation - O(N) & O(N)
    bool canWinNim_V1(int n) {
        // 2D DP table
        vector<vector<bool>> dp(n + 1, vector<bool>(2, false));

        // Fill the table
        for(int heap = 1; heap <= n; ++heap) {
            for(int myTurn = 0; myTurn <= 1; ++myTurn) {
                if(myTurn) {
                    bool remove1Stone = (heap - 1 >= 1 ? dp[heap - 1][false] : true);
                    bool remove2Stone = (heap - 2 >= 1 ? dp[heap - 2][false] : true);
                    bool remove3Stone = (heap - 3 >= 1 ? dp[heap - 3][false] : true);
                    dp[heap][myTurn]  = (remove1Stone || remove2Stone || remove3Stone);
                }
                else {
                    bool remove1Stone = (heap - 1 >= 1) ? dp[heap - 1][true] : false;
                    bool remove2Stone = (heap - 2 >= 1) ? dp[heap - 2][true] : false;
                    bool remove3Stone = (heap - 3 >= 1) ? dp[heap - 3][true] : false;
                    dp[heap][myTurn]  = !(!remove1Stone || !remove2Stone || !remove3Stone);
                }
            }
        }

        // Return the result value
        return dp[n][true];
    }
    // Note: This solution can lead to memory exhaustion due to the dp table. It's because the value of N could be very high

    // #2 Method to check if you can win the game or not, using 1D tabulation - O(N) & O(1)
    bool canWinNim_V2(int n) {
        // 1D DP tables
        vector<bool> currRow(2, false), row_1(2, false), row_2(2, false), row_3(2, false);

        // Fill the table
        for(int heap = 1; heap <= n; ++heap) {
            for(int myTurn = 0; myTurn <= 1; ++myTurn) {
                if(myTurn) {
                    bool remove1Stone = (heap - 1 >= 1 ? row_1[false] : true);
                    bool remove2Stone = (heap - 2 >= 1 ? row_2[false] : true);
                    bool remove3Stone = (heap - 3 >= 1 ? row_3[false] : true);
                    currRow[myTurn]   = (remove1Stone || remove2Stone || remove3Stone);
                }
                else {
                    bool remove1Stone = (heap - 1 >= 1) ? row_1[true] : false;
                    bool remove2Stone = (heap - 2 >= 1) ? row_2[true] : false;
                    bool remove3Stone = (heap - 3 >= 1) ? row_3[true] : false;
                    currRow[myTurn]   = !(!remove1Stone || !remove2Stone || !remove3Stone);
                }
            }
            row_3 = row_2;
            row_2 = row_1;
            row_1 = currRow;
        }

        // Return the result value
        return currRow[true];
    }
    // Note: This solution can lead to time-limit-exceed. It's because the value of N could be very high
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Maths {
public:
    // Method to check if you can win the game or not, using brain and math - O(1) & O(1)
    bool canWinNim(int n) {
        /*
            To determine if you can win the Nim game, consider the following:
    
            - For small numbers of stones (1 to 3), you can always win by taking all stones.
            - With exactly 4 stones, you will lose no matter how many stones you take (1, 2, or 3). Your opponent will always be left with a number of stones that eventually results in your loss.
            - With 5 to 7 stones, you can win. For example, with 5 stones, take 1 stone (you're playing optimally) then no matter how many stones the opponent will take (1, 2, or 3), as your turn comes in you'll win by taking the rest of all the stones.
            - The pattern continues with every set of 4 stones. For any number of stones that is a multiple of 4 (like 4, 8, 12, 16, ...), you are guaranteed to lose if both players play optimally.
            - So, if the number of stones is not a multiple of 4, you can force the game into a situation where your opponent could not win.
    
            Therefore, you can win if the number of stones is not a multiple of 4.
        */

        return n % 4 != 0;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Brainteaser | Game Theory | Dynamic Programming
Link  : https://leetcode.com/problems/nim-game/description/?envType=problem-list-v2&envId=game-theory
