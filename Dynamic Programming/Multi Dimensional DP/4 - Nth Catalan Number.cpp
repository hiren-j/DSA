// Code to find the Nth number of the catalan's sequence ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUP {
    const int MOD = 1e9+7;

public:
    // #1 Method to find the Nth catalan number, using 2D tabulation - O(N^2) & O(N^2)
    int getNthCatalan_V1(int N) {
        // Stores the values of the catalan's triangle
        vector<vector<int>> dp;
        
        for(int R = 0; R <= N; ++R) {
            dp.emplace_back(R + 1, 0);
            for(int C = 0; C <= R; ++C) {
                // If its the first column then fill it by 1 
                if(C == 0)
                    dp[R][C] = 1;

                // Else if its the last column then store the value lying at the previous column in the same row
                else if(C == R)
                    dp[R][C] = dp[R][C - 1] % MOD;

                // Else then add the value lying at the same column in the previous row with the value lying at the previous column in the same row
                else
                    dp[R][C] = (dp[R - 1][C] + dp[R][C - 1]) % MOD;
            }
        }
        
        // Return the Nth number of the catalan's sequence
        return dp[N][N] % MOD;
    }

    // #2 Method to find the Nth catalan number, using 1D tabulation - O(N^2) & O(N)
    int getNthCatalan_V2(int N) {
        vector<int> prevRow;
        
        for(int R = 0; R <= N; ++R) {
            vector<int> currRow(R + 1, 0);
            for(int C = 0; C <= R; ++C) {
                // If its the first column then fill it by 1 
                if(C == 0)
                    currRow[C] = 1;

                // Else if its the last column then store the value lying at the previous column in the same row
                else if(C == R)
                    currRow[C] = currRow[C - 1] % MOD;

                // Else then add the value lying at the same column in the previous row with the value lying at the previous column in the same row
                else
                    currRow[C] = (prevRow[C] + currRow[C - 1]) % MOD;
            }
            prevRow = currRow;
        }
        
        // Return the Nth number of the catalan's sequence
        return prevRow[N] % MOD;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://archive.lib.msu.edu/crcmath/math/math/c/c099.htm
        https://www.geeksforgeeks.org/problems/nth-catalan-number0817/1
