// Code to find the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the shortest common supersequence, using 2D tabulation - O(N*M) & O(N*M)
    string shortestCommonSupersequence(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Find the length of the longest common subsequence of both the strings
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }

        string answer;

        int i = n, j = m;

        while(i > 0 && j > 0) {
            // If both the letters match
            if(s1[i - 1] == s2[j - 1]) {
                // Take only 1 letter
                answer.push_back(s1[i - 1]);
                i--;
                j--;
            }
            // Else when both the letters don't match
            else {
                // If it's maximum then string1 will shrink by size 1. So before shrink take that dropped letter of string1
                if(dp[i - 1][j] > dp[i][j - 1]) {
                    answer.push_back(s1[i - 1]);
                    i--;
                }   
                // Else if it's maximum then string2 will shrink by size 1. So before shrink take that dropped letter of string2
                else {
                    answer.push_back(s2[j - 1]);
                    j--;
                }
            }
        }

        // Store the remaining letters of string1 to the answer
        while(i > 0) {
            answer.push_back(s1[i - 1]);
            i--;
        }

        // Store the remaining letters of string2 to the answer
        while(j > 0) {
            answer.push_back(s2[j - 1]);
            j--;
        }

        // Reverse the answer array to get the actual order
        reverse(begin(answer), end(answer));

        return answer;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/shortest-common-supersequence/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/Longest%20Common%20Subsequence.cpp
