// Code to check whether Alice can win the game or not. Alice and Bob take turns playing a game, with Alice starting first. Initially, there are 'n' stones in a pile. On each player's turn, that player makes a move consisting of removing any non-zero square number of stones in the pile. Also, if a player cannot make a move, he/she loses the game. Assume that both the players are playing optimally ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<int> perfectSquares;
    
    // O(sqrt(N) ^ N) & O(N)
    bool solveWithoutMemo(int n, bool aliceTurn) {
        // Edge case: If there are no stones and if its Bob's turn then he can't make a move so Alice wins the game
        if(n <= 0)
            return !aliceTurn;

        // Tracks Alice can win or not
        bool canWin = false;

        for(int sq : perfectSquares) {
            if(sq > n)
                break;

            // If its Alice's turn then she absolutely wanted to win, so if Alice can win the game by any of the possibility then return true
            if(aliceTurn) {
                canWin = solveWithoutMemo(n - sq, false);
                if(canWin) break;
            }
            // If its Bob's turn then he absolutely wanted Alice to lose, so if she lose the game by any of the possibility then Bob will return false
            else {
                canWin = solveWithoutMemo(n - sq, true);
                if(!canWin) break;
            }
        }
        
        return canWin;
    }

    // O(sqrt(N) * N*2) & O(sqrt(N) + N*2 + N)
    bool solveWithMemo(vector<vector<int>>& memory, int n, bool aliceTurn) {
        // Edge case: If there are no stones and if its Bob's turn then he can't make a move so Alice wins the game
        if(n <= 0)
            return !aliceTurn;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n][aliceTurn] != -1)
            return memory[n][aliceTurn];

        // Tracks Alice can win or not
        bool canWin = false;

        for(int sq : perfectSquares) {
            if(sq > n)
                break;

            // If its Alice's turn then she absolutely wanted to win, so if Alice can win the game by any of the possibility then return true
            if(aliceTurn) {
                canWin = solveWithMemo(memory, n - sq, false);
                if(canWin) break;
            }
            // If its Bob's turn then he absolutely wanted Alice to lose, so if she lose the game by any of the possibility then Bob will return false
            else {
                canWin = solveWithMemo(memory, n - sq, true);
                if(!canWin) break;
            }
        }
        
        // Store the result value to the memoization table and then return it
        return memory[n][aliceTurn] = canWin;
    }

public:
    // Method to check whether Alice can win the game or not, using recursion with memoization - O(N*sqrt(N)) & O(N)
    bool winnerSquareGame(int n) {
        // Store all the perfect square numbers lying within 1 to n
        for(int num = 1; num * num <= n; ++num)
            perfectSquares.push_back(num * num);
        
        // 2D memoization table
        vector<vector<int>> memory(n + 1, vector<int>(2, -1));

        // Find and return the result value
        return solveWithMemo(memory, n, true);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to check whether Alice can win the game or not, using 2D tabulation - O(N*sqrt(N)) & O(N)
    bool winnerSquareGame(int n) {
        vector<int> perfectSquares;

        // Store all the perfect square numbers lying within 1 to n
        for(int num = 1; num * num <= n; ++num)
            perfectSquares.push_back(num * num);
        
        // 2D DP table
        vector<vector<bool>> dp(n + 1, vector<bool>(2, false));

        // Fill the table
        for(int num = 1; num <= n; ++num) {
            for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                bool canWin = false;

                for(int sq : perfectSquares) {
                    if(sq > num)
                        break;

                    if(aliceTurn) {
                        canWin = (num - sq > 0) ? dp[num - sq][false] : true;
                        if(canWin) break;
                    }
                    else {
                        canWin = (num - sq > 0) ? dp[num - sq][true] : false;
                        if(!canWin) break;
                    }
                }

                dp[num][aliceTurn] = canWin;
            }
        }

        // Return the result value
        return dp[n][true];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Game Theory
Link  : https://leetcode.com/problems/stone-game-iv/description/
