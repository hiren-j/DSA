// Code to find the length of the longest common substring of given strings ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the length of the longest common substring, using 2D tabulation - O(N*M) & O(N*M)
    int longestCommonSubstring_V1(string& s1, string& s2, int n, int m) {
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        
        int maxLength = 0;
        
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                // If both the letters match
                if(s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                // Else when both the letters don't match
                else {
                    dp[i][j] = 0;
                }
                maxLength = max(maxLength, dp[i][j]);
            }
        }
        
        return maxLength;
    }

    // #2 Method to find the length of the longest common substring, using 1D tabulation - O(N*M) & O(M)
    int longestCommonSubstring_V2(string& s1, string& s2, int n, int m) {
        // 1D DP tables
        vector<int> prevRow(m + 1), currRow(m + 1);
        
        int maxLength = 0;
        
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                // If both the letters match
                if(s1[i - 1] == s2[j - 1]) {
                    currRow[j] = 1 + prevRow[j - 1];
                }
                // Else when both the letters don't match
                else {
                    currRow[j] = 0;
                }
                maxLength = max(maxLength, currRow[j]);
            }
            prevRow = currRow;
        }
        
        return maxLength;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
