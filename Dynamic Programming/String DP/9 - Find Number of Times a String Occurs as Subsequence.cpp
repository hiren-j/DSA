// Code to count the number of subsequences of string s1 which are equal to string s2 ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to count the number of subsequences of string s1 which are equal to string s2, using recursion with memoization - O(N*M) & O(N*M)
    int countWays(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, n-1, m-1);
    }
    
private:
    const int MOD = 1e9+7;
    
    // O(2*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int i, int j) {
        // Edge case: If all the letters of s2 are exhausted then you've got 1 occurence of s2 in s1
        if(j < 0)
            return 1;
        
        // Edge case: If all the letters of s1 are exhausted but not of s2 then there's no occurence of s2 in s1
        if(i < 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];

        // If both the letters match then move to the left side in both the strings to look for other matches and it's also possible that the jth letter could be found at the left side of the ith letter hence explore that possibility too
        if(s1[i] == s2[j])
            return memory[i][j] = (solveWithMemo(memory, s1, s2, i-1, j-1) + solveWithMemo(memory, s1, s2, i-1, j)) % MOD;
        
        // Else when the letter's doesn't match then it's possible that the jth letter could be found at the left side of the ith letter hence explore the possibility and then store the result value to the memoization table and then return it
        return memory[i][j] = solveWithMemo(memory, s1, s2, i-1, j) % MOD;
    }

    // O(2^(N+M)) & O(N+M)
    int solveWithoutMemo(string& s1, string& s2, int i, int j) {
        // Edge case: If all the letters of s2 are exhausted then you've got 1 occurence of s2 in s1
        if(j < 0)
            return 1;
        
        // Edge case: If all the letters of s1 are exhausted but not of s2 then there's no occurence of s2 in s1
        if(i < 0)
            return 0;

        // If both the letters match then move to the left side in both the strings to look for other matches and it's also possible that the jth letter could be found at the left side of the ith letter hence explore that possibility too
        if(s1[i] == s2[j])
            return (solveWithoutMemo(s1, s2, i-1, j-1) + solveWithoutMemo(s1, s2, i-1, j)) % MOD;
        
        // Else when the letter's doesn't match then it's possible that the jth letter could be found at the left side of the ith letter hence explore the possibility
        return solveWithoutMemo(s1, s2, i-1, j) % MOD;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    
public:
    // #1 Method to count the number of subsequences of string s1 which are equal to string s2, using 2D tabulation - O(N*M) & O(N*M)
    int countWays_V1(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 2D DP table
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        // Initialize the first edge case: If all the letters of s2 are exhausted then you've got 1 occurence of s2 in s1
        for(int i = 0; i <= n; ++i)
            dp[i][0] = 1;

        // Fill the rest of the table
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(s1[i-1] == s2[j-1])
                    dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % MOD;
                else
                    dp[i][j] = dp[i-1][j] % MOD;
            }
        }

        // Return the result value
        return dp[n][m];
    }

    // #2 Method to count the number of subsequences of string s1 which are equal to string s2, using 1D tabulation - O(N*M) & O(M)
    int countWays_V2(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 1D DP tables
        vector<int> prevRow(m+1), currRow(m+1);
        
        // Initialize the first edge case: If all the letters of s2 are exhausted then you've got 1 occurence of s2 in s1 
        prevRow[0] = 1;

        for(int i = 1; i <= n; ++i) {
            currRow[0] = 1; // Initialize the first edge case
            for(int j = 1; j <= m; ++j) {
                if(s1[i-1] == s2[j-1])
                    currRow[j] = (prevRow[j-1] + prevRow[j]) % MOD;
                else
                    currRow[j] = prevRow[j] % MOD;
            }
            prevRow = currRow;
        }

        // Return the result value
        return prevRow[m];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/find-number-of-times-a-string-occurs-as-a-subsequence3020/1
