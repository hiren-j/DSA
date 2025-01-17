// Code to check whether Alice can win the game or not. Alice play against Bob in an alternating way. Alice and Bob take turns, with Alice starting first. On each player's turn, that player can take 1, 2, or 3 stones from the first remaining stones in the row. The score of each player is the sum of the values of the stones taken. The objective of the game is to end with the highest score, and the winner is the player with the highest score and there could be a tie. The score of each player is 0 initially. Note that both the players are playing optimally ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to check whether Alice can win the game or not, using recursion with memoization - O(N) & O(N)
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<vector<int>> memory(n, vector<int>(2, -1));
        int aliceStones = solveWithMemo(memory, stoneValue, n, 0, true);
        int bobStones   = accumulate(begin(stoneValue), end(stoneValue), 0) - aliceStones;
        return (aliceStones >= bobStones) ? (aliceStones == bobStones ? "Tie" : "Alice") : "Bob";
    }

private:
    // O(3*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& stoneValue, int n, int startIndex, bool aliceTurn) {
        // Edge case: If all the piles are exhausted then Alice can't take more stones
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][aliceTurn] != -1)
            return memory[startIndex][aliceTurn];

        int maxStones  = (aliceTurn) ? INT_MIN : INT_MAX;
        int currStones = 0;

        for(int index = startIndex; index < min(startIndex + 3, n); ++index) {
            currStones += stoneValue[index];

            // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from all the possibility
            if(aliceTurn) {
                int nextStones = solveWithMemo(memory, stoneValue, n, index + 1, false);
                maxStones = max(maxStones, nextStones + currStones);
            }
            // If its Bob's turn then he absolutely wanted alice to lose, So for that he wants Alice to minimize her score, so he will take the minimum value from all the possibility
            else {
                int nextStones = solveWithMemo(memory, stoneValue, n, index + 1, true);
                maxStones = min(maxStones, nextStones);
            }
        }   

        // Store the result value to the memoization table and then return it
        return memory[startIndex][aliceTurn] = maxStones;
    }

    // O(3^N) & O(N)
    int solveWithoutMemo(vector<int>& stoneValue, int n, int startIndex, bool aliceTurn) {
        // Edge case: If all the piles are exhausted then Alice can't take more stones
        if(startIndex == n)
            return 0;

        int maxStones  = (aliceTurn) ? INT_MIN : INT_MAX;
        int currStones = 0;

        for(int index = startIndex; index < min(startIndex + 3, n); ++index) {
            currStones += stoneValue[index];

            // If its Alice's turn then she absolutely wanted to win, So for that she wants to maximize her score, so she will take the maximum value from all the possibility
            if(aliceTurn) {
                int nextStones = solveWithoutMemo(stoneValue, n, index + 1, false);
                maxStones = max(maxStones, nextStones + currStones);
            }
            // If its Bob's turn then he absolutely wanted alice to lose, So for that he wants Alice to minimize her score, so he will take the minimum value from all the possibility
            else {
                int nextStones = solveWithoutMemo(stoneValue, n, index + 1, true);
                maxStones = min(maxStones, nextStones);
            }
        }   

        return maxStones;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to check whether Alice can win the game or not, using 2D tabulation - O(N) & O(N)
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
            
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            for(int aliceTurn = 0; aliceTurn <= 1; ++aliceTurn) {
                int maxStones  = (aliceTurn) ? INT_MIN : INT_MAX;
                int currStones = 0;

                for(int index = startIndex; index < min(startIndex + 3, n); ++index) {
                    currStones += stoneValue[index];

                    if(aliceTurn) {
                        int nextStones = dp[index + 1][false];
                        maxStones = max(maxStones, nextStones + currStones);
                    }
                    else {
                        int nextStones = dp[index + 1][true];
                        maxStones = min(maxStones, nextStones);
                    }
                }

                dp[startIndex][aliceTurn] = maxStones;
            }
        }

        int aliceStones = dp[0][true];
        int bobStones   = accumulate(begin(stoneValue), end(stoneValue), 0) - aliceStones;

        return (aliceStones >= bobStones) ? (aliceStones == bobStones ? "Tie" : "Alice") : "Bob";
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Dynamic Programming | Game Theory
Link  : https://leetcode.com/problems/stone-game-iii/description/?envType=problem-list-v2&envId=game-theory
