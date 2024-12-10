// Code to check is s2 can be a subsequence of s1 after performing the specifed operation at most once ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
    int n, m;

    // O(2^(N+M)) & O(N)
    bool solveWithoutMemo(string& s1, string& s2, int i, int j) {
        if(j == m)
            return true;

        if(i == n)
            return false;

        bool currSkip = solveWithoutMemo(s1, s2, i+1, j);
        bool currTake = false;

        char nextChar = (s1[i] == 'z') ? 'a' : s1[i] + 1;

        if(s1[i] == s2[j] || nextChar == s2[j])
            currTake = solveWithoutMemo(s1, s2, i+1, j+1);

        return currSkip || currTake;
    }

    // O(2*N*M) & O(N*M + N)
    bool solveWithoutMemo(vector<vector<int>>& dp, string& s1, string& s2, int i, int j) {
        if(j == m)
            return true;

        if(i == n)
            return false;

        if(dp[i][j] != -1)
            return dp[i][j];

        bool currSkip = solveWithoutMemo(dp, s1, s2, i+1, j);
        bool currTake = false;

        char nextChar = (s1[i] == 'z') ? 'a' : s1[i] + 1;

        if(s1[i] == s2[j] || nextChar == s2[j])
            currTake = solveWithoutMemo(dp, s1, s2, i+1, j+1);

        return dp[i][j] = currSkip || currTake;
    }

public:
    // Method to check is s2 can be a subsequence of s1 after performing the specifed operation, using recursion with memoization - O(N*M) & O(N*M) 
    bool canMakeSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithoutMemo(s1, s2, 0, 0);
    }
};
// Note: This solution will lead to memory limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
    int n, m;

    // O(N^N) & O(N)
    bool solveWithoutMemo(string& s1, string& s2, int startIdx, int j) {
        if(j == m)
            return true;

        for(int i = startIdx; i < n; ++i) {
            char nextChar = (s1[i] == 'z') ? 'a' : s1[i] + 1;
            if((s1[i] == s2[j] || nextChar == s2[j]) && solveWithoutMemo(s1, s2, i+1, j+1)) {
                return true;
            }
        }

        return false;
    }

    // O(N*N*M) & O(N*M + N)
    bool solveWithMemo(vector<vector<int>>& dp, string& s1, string& s2, int startIdx, int j) {
        if(j == m)
            return true;

        if(startIdx == n)
            return false;

        if(dp[startIdx][j] != -1)  
            return dp[startIdx][j];

        for(int i = startIdx; i < n; ++i) {
            char nextChar = (s1[i] == 'z') ? 'a' : s1[i] + 1;
            if((s1[i] == s2[j] || nextChar == s2[j]) && solveWithMemo(dp, s1, s2, i+1, j+1)) {
                return dp[i][j] = true;
            }
        }

        return dp[startIdx][j] = false;
    }

public:
    // Method to check is s2 can be subsequence of s1 after performing the specified operation, using recursion with memoization :-
    bool canMakeSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s1, s2, 0, 0);
    }
};
// Note: This solution will lead to memory limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to check is s2 can be a subsequence of s1 after performing the specified operation, using 2D tabulation - O(N*M) & O(N*M)
    bool canMakeSubsequence_V1(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));
        
        // Initialize the first edge case
        for(int i = 0; i <= n; ++i)
            dp[i][m] = true;

        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                bool currSkip = dp[i+1][j];
                bool currTake = false;
                char nextChar = (s1[i] == 'z') ? 'a' : s1[i] + 1;
                if(s1[i] == s2[j] || nextChar == s2[j]) {
                    currTake = dp[i+1][j+1];
                }
                dp[i][j] = (currSkip || currTake);
            }
        }

        return dp[0][0];
    }

    // #2 Method to check is s2 can be a subsequence of s1 after performing the specified operation, using 1D tabulation - O(N*M) & O(M)
    bool canMakeSubsequence_V2(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        vector<bool> nextRow(m+1, false), idealRow(m+1, false);

        // Initialize the first edge case
        nextRow[m] = true;

        for(int i = n-1; i >= 0; --i) {
            idealRow[m] = true; // Initialize the first edge case
            for(int j = m-1; j >= 0; --j) {
                bool currSkip = nextRow[j];
                bool currTake = false;
                char nextChar = (s1[i] == 'z') ? 'a' : s1[i] + 1;
                if(s1[i] == s2[j] || nextChar == s2[j]) {
                    currTake = nextRow[j+1];
                }
                idealRow[j] = (currSkip || currTake);
            }
            nextRow = idealRow;
        }

        return idealRow[0];
    }
};
// Note: This solution will lead to time limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TwoPointers {
public:
    // Method to check is s2 can be a subsequence of s1 after performing the specified operation - O(N+M) & O(1)
    bool canMakeSubsequence(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        int i = 0, j = 0;

        while(i < n && j < m) {
            char nextChar = (s1[i] == 'z') ? 'a' : s1[i] + 1;

            if(s1[i] == s2[j] || nextChar == s2[j]) 
                i++, j++;
            else
                i++;
        }

        return j == m;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String 
Link  : https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/?envType=daily-question&envId=2024-12-04
