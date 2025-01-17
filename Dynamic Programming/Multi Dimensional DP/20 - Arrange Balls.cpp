// Code to find total number of possible arrangements. There are p balls of type P, q balls of type Q and r balls of type R. Using the balls we want to create a straight line such that no two balls of same type are adjacent ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
    DON'T IGNORE MUST READ :-
        We'll use 1 to represent the ball of type P
        We'll use 2 to represent the ball of type Q
        We'll use 3 to represent the ball of type R
*/
  -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

    // O(3^(P*Q*R)) & O(P+Q+R)
    int solveWithoutMemo(int P, int Q, int R, int prevType) {
        // Edge case: If you've created a valid arrangement by picking all the type of balls then return 1
        if(P == 0 && Q == 0 && R == 0)
            return 1;

        // Edge case: If its not possible to pick all type of balls then return 0
        if(P < 0 || Q < 0 || R < 0)
            return 0;

        int count = 0;

        // There are three possibilities to take care before picking any type of ball
        if(prevType != 1) count = solveWithoutMemo(P-1, Q, R, 1);                 // If previously not picked then pick a ball of type P
        if(prevType != 2) count = (count + solveWithoutMemo(P, Q-1, R, 2)) % MOD; // If previously not picked then pick a ball of type Q
        if(prevType != 3) count = (count + solveWithoutMemo(P, Q, R-1, 3)) % MOD; // If previously not picked then pick a ball of type R

        return count;
    }

    // O(3*P*Q*R*4) & O(P*Q*R*4 + P+Q+R)
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, int P, int Q, int R, int prevType) {
        // Edge case: If you've created a valid arrangement by picking all the type of balls then return 1
        if(P == 0 && Q == 0 && R == 0)
            return 1;

        // Edge case: If its not possible to pick all type of balls then return 0
        if(P < 0 || Q < 0 || R < 0)
            return 0;

        if(dp[P][Q][R][prevType] != -1)
            return dp[P][Q][R][prevType]; 
            
        int count = 0;

        // There are three possibilities to take care before picking any type of ball
        if(prevType != 1) count = solveWithMemo(dp, P-1, Q, R, 1);                 // If previously not picked then pick a ball of type P
        if(prevType != 2) count = (count + solveWithMemo(dp, P, Q-1, R, 2)) % MOD; // If previously not picked then pick a ball of type Q
        if(prevType != 3) count = (count + solveWithMemo(dp, P, Q, R-1, 3)) % MOD; // If previously not picked then pick a ball of type R

        return dp[P][Q][R][prevType] = count;
    }

public:
    // Method to find total number of possible arrangements, using recursion with memoization - O(PQR) & O(PQR)
    int countTotalArrangements(int P, int Q, int R) {
        vector<vector<vector<vector<int>>>> dp(P + 1, vector<vector<vector<int>>>(Q + 1, vector<vector<int>>(R + 1, vector<int>(4, -1))));
        return solveWithMemo(dp, P, Q, R, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    
public:
    // #1 Method to find the total number of possible arrangements, using 4D tabulation - O(PQR) & O(PQR)
    int countTotalArrangements_V1(int given_P, int given_Q, int given_R) {
        vector<vector<vector<vector<int>>>> dp(given_P + 1, vector<vector<vector<int>>>(given_Q + 1, vector<vector<int>>(given_R + 1, vector<int>(4, 0))));

        // Initialize the first edge case
        for(int prevType = 0; prevType <= 3; ++prevType)
            dp[0][0][0][prevType] = 1;
        
        for(int P = 0; P <= given_P; ++P) {
            for(int Q = 0; Q <= given_Q; ++Q) {
                for(int R = 0; R <= given_R; ++R) {
                    if(P == 0 && Q == 0 && R == 0) // Handle the first edge case
                        continue;
                    for(int prevType = 3; prevType >= 0; --prevType) {
                        int count = 0;
                        if(prevType != 1) count = (P-1 >= 0 ? dp[P-1][Q][R][1] : 0);
                        if(prevType != 2) count = (count + (Q-1 >= 0 ? dp[P][Q-1][R][2] : 0)) % MOD;
                        if(prevType != 3) count = (count + (R-1 >= 0 ? dp[P][Q][R-1][3] : 0)) % MOD;
                        dp[P][Q][R][prevType] = count;                   
                    }
                }
            }
        }
        
        return dp[given_P][given_Q][given_R][0];
    }

    // #2 Method to find the total number of possible arrangements, using 3D tabulation - O(PQR) & O(QR)
    int countTotalArrangements_V2(int given_P, int given_Q, int given_R) {
        vector<vector<vector<int>>> prevRow(given_Q + 1, vector<vector<int>>(given_R + 1, vector<int>(4, 0)));
        vector<vector<vector<int>>> idealRow(given_Q + 1, vector<vector<int>>(given_R + 1, vector<int>(4, 0)));
        
        for(int P = 0; P <= given_P; ++P) {
            for(int prevType = 0; prevType <= 3; ++prevType) // Initialize the first edge case
                idealRow[0][0][prevType] = 1; 
            for(int Q = 0; Q <= given_Q; ++Q) {
                for(int R = 0; R <= given_R; ++R) {
                    if(P == 0 && Q == 0 && R == 0) // Handle the first edge case
                        continue;
                    for(int prevType = 3; prevType >= 0; --prevType) {
                        int count = 0;
                        if(prevType != 1) count = (P-1 >= 0 ? prevRow[Q][R][1] : 0);
                        if(prevType != 2) count = (count + (Q-1 >= 0 ? idealRow[Q-1][R][2] : 0)) % MOD;
                        if(prevType != 3) count = (count + (R-1 >= 0 ? idealRow[Q][R-1][3] : 0)) % MOD;
                        idealRow[Q][R][prevType] = count;                   
                    }
                }
            }
            prevRow = idealRow;
        }
        
        return prevRow[given_Q][given_R][0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          
Topics: Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/arrange-balls0052/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
