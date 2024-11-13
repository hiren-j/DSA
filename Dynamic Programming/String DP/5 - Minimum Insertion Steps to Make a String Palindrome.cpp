// Code to find the minimum number of steps to make string "s" palindrome ~ coded by Hiren 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum number of steps to make string "s" palindrome :-
    int minInsertions(string& s) {
        int n = s.size();
        return n - longestPalindromeSubseq(s, n);
    }

private:
    // Method to find the length of the longest palindromic subsequence, using recursion with memoization - O(N*N) & O(N*N)
    int longestPalindromeSubseq(string& s1, int n) {
        string s2(n, ' ');

        // Create the reverse of string s1
        for(int i = 0; i < n; ++i)
            s2[i] = s1[n - i - 1];

        // 2D memoization table
        vector<vector<int>> memory(n, vector<int>(n, -1));

        // Find and return the length of the LCS of the strings
        return solveWithMemo(memory, s1, s2, n-1, n-1);
    }

    // O(2*N*N) & O(N*N + N+N)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int i, int j) {
        // Edge case: If any of the string gets exhausted then we've found a common subsequence
        if(i < 0 || j < 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];

        // If the letters of both the string matches then we've got a common subsequence of length 1 
        if(s1[i] == s2[j])
            return memory[i][j] = 1 + solveWithMemo(memory, s1, s2, i-1, j-1);
        
        // Else when the letters doesn't match then it's possible that the jth letter could be found at the left side of the ith letter and vice versa. So, that's why explore both the possibilities and as we're striving for the LCS hence store the maximum value to the memoization table and then return it
        return memory[i][j] = max(solveWithMemo(memory, s1, s2, i-1, j), solveWithMemo(memory, s1, s2, i, j-1));
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum number of steps to make string "s" palindrome :-
    int minInsertions(string& s) {
        int n = s.size();
        return n - longestPalindromeSubseq_V2(s, n);
    }

private:
    // #1 Method to find the length of the longest palindromic subsequence, using 2D tabulation - O(N*N) & O(N*N)
    int longestPalindromeSubseq_V1(string& s1, int n) {
        string s2(n, ' ');

        // Create the reverse of string s1
        for(int i = 0; i < n; ++i)
            s2[i] = s1[n - i - 1];

        // 2D DP table
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        
        // Find the length of the LCS of s1 and s2
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }

        // Return the length of the LCS
        return dp[n][n];
    }

    // #2 Method to find the length of the longest palindromic subsequence, using 1D tabulation - O(N*N) & O(N)
    int longestPalindromeSubseq_V2(string& s1, int n) {
        string s2(n, ' ');

        // Create the reverse of string s1
        for(int i = 0; i < n; ++i)
            s2[i] = s1[n - i - 1];
            
        // 1D DP tables
        vector<int> prevRow(n+1), currRow(n+1);

        // Find the length of the LCS of s1 and s2
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(s1[i - 1] == s2[j - 1])
                    currRow[j] = 1 + prevRow[j-1];
                else
                    currRow[j] = max(prevRow[j], currRow[j-1]);
            }
            prevRow = currRow;
        }

        // Return the length of the LCS
        return prevRow[n];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/Longest%20Palindromic%20Subsequence.cpp
