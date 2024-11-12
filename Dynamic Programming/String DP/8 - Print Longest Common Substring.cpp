// Code to find the longest common substring of given two strings ~ coded by Hiren 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // #1 Method to find the longest common substring, using 2D tabulation - O(N*M) & O(N*M)
    string getLongestCommonSubstr_V1(string& s1, string& s2) {
        int n = s1.size(), m = s2.size(), maxLength = 0, endIndex = 0;

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                // If both the letters match
                if(s1[i - 1] == s2[j - 1]) { 
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    if(dp[i][j] > maxLength) {
                        maxLength = dp[i][j];
                        endIndex  = i;
                    }
                }
                // Else when both the letters don't match
                else {
                    dp[i][j] = 0;
                }
            }
        }

        // Return the result string
        return s1.substr(endIndex - maxLength, maxLength);
    }

    // #2 Method to find the longest common substring, using 1D tabulation - O(N*M) & O(M)
    string getLongestCommonSubstr_V2(string& s1, string& s2) {
        int n = s1.size(), m = s2.size(), maxLength = 0, endIndex = 0;

        // 1D DP tables
        vector<int> prevRow(m + 1, 0), currRow(m + 1, 0);

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                // If both the letters match
                if(s1[i - 1] == s2[j - 1]) { 
                    currRow[j] = 1 + prevRow[j - 1];
                    if(currRow[j] > maxLength) {
                        maxLength = currRow[j];
                        endIndex  = i;
                    }
                }
                // Else when both the letters don't match
                else {
                    currRow[j] = 0;
                }
            }
            prevRow = currRow;
        }

        // Return the result string
        return s1.substr(endIndex - maxLength, maxLength);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming 
Link  : https://www.geeksforgeeks.org/print-longest-common-substring/
