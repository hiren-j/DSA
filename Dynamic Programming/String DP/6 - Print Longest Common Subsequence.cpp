// Code to find the longest common subsequence of s1 and s2 ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the LCS of given strings, using 2D tabulation - O(N*M) & O(N*M)
    string getLCS(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Find the length of the LCS of s1 and s2
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(s1[i - 1] == s2[j - 1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else 
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        
        // Stores the result string
        string LCS;

        int i = n, j = m;

        while(i > 0 && j > 0) {
            // If both the letters match
            if(s1[i - 1] == s2[j - 1]) {
                LCS.push_back(s1[i - 1]);
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

        // Reverse the string to get the actual order of the LCS
        reverse(begin(LCS), end(LCS));

        // Return the result string
        return LCS;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-common-subsequence/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/Longest%20Common%20Subsequence.cpp
