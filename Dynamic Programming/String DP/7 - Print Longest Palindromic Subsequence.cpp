// Code to find the longest palindromic subsequence of given string ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the LPS of given string, using 2D tabulation - O(N*M) & O(N*M)
    int getLPS(string& s1) {
        int n = s1.size();
        string s2 = s1;
        reverse(begin(s2), end(s2));

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Find the length of the LCS of s1 and s2
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else 
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        
        // Stores the result string
        string LPS;

        int i = n, j = n;

        while(i > 0 && j > 0) {
            // If both the letters match
            if(s1[i - 1] == s2[j - 1]) {
                LPS.push_back(s1[i - 1]);
                i = i - 1;
                j = j - 1;
            }
            // Else when both the letters don't match
            else {
                if(dp[i - 1][j] > dp[i][j - 1]) {
                    i = i - 1;
                }
                else {
                    j = j - 1;
                }
            }
        }

        // Reverse the string to get the actual order of the LPS
        reverse(begin(LPS), end(LPS));

        // Return the result string
        return LPS;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/Longest%20Palindromic%20Subsequence.cpp
