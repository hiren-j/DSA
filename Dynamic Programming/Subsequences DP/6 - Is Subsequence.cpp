// Code to check whether the string "s" is a subsequence of string "t" or not ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V1 {
    int n, m;

    // O(2^(N+M)) & O(M)
    int solveWithoutMemo(string& s, string& t, int i, int j) {
        // Edge case: If the string "s" is exhausted then return true
        if(i == n)
            return true;

        // Edge case: If the string "t" is exhausted then return false
        if(j == m)
            return false;

        // There are always two possibilites to perform at the jth letter
        bool currSkip = solveWithoutMemo(s, t, i, j+1); // Is to skip it
        bool currTake = false;                          // Is to take it 

        // If the ith and jth letter of both the strings are equal then take the jth letter of "t"
        if(!currSkip && s[i] == t[j])
            currTake = solveWithoutMemo(s, t, i+1, j+1);

        // Return the result value
        return (currSkip || currTake);
    }

    // O(2*N*M) & O(N*M + M)
    int solveWithMemo(vector<vector<int>>& memory, string& s, string& t, int i, int j) {
        // Edge case: If the string "s" is exhausted then return true
        if(i == n)
            return true;

        // Edge case: If the string "t" is exhausted then return false
        if(j == m)
            return false;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)  
            return memory[i][j];

        // If the ith and jth letter of both the strings are equal then take the jth letter of "t"
        bool currSkip = solveWithMemo(memory, s, t, i, j+1); // Is to skip it
        bool currTake = false;                               // Is to take it

        // If the ith and jth letter of both the strings are equal then take the jth letter of "t"
        if(s[i] == t[j])
            currTake = solveWithMemo(memory, s, t, i+1, j+1);

        // Store the result value to the memoization table and then return it
        return memory[i][j] = (currSkip || currTake);
    }

public:
    // Method to check whether string "s" is a subsequence of string "t", using recursion with memoization - O(N*M) & O(N*M)
    bool isSubsequence(string& s, string& t) {
        n = s.size(), m = t.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s, t, 0, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
    int n, m;

    // O(M^M) & O(M)
    int solveWithoutMemo(string& s, string& t, int i, int startIndex) {
        // Edge case: If the string "s" is exhausted then return true
        if(i == n)
            return true;
        
        // Iterate "t" and if the ith and jth letter of both the strings are equal then take the jth letter of "t"
        for(int j = startIndex; j < m; ++j) 
            if(s[i] == t[j]) 
                return solveWithoutMemo(s, t, i+1, j+1);

        // If reached here then return false
        return false;
    }

    // O(M*N*M) & O(N*M + M)
    int solveWithMemo(vector<vector<int>>& memory, string& s, string& t, int i, int startIndex) {
        // Edge case: If the string "s" is exhausted then return true
        if(i == n)
            return true;

        // Edge case: If the string "t" is exhausted then return false
        if(startIndex == m)
            return false;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][startIndex] != -1)
            return memory[i][startIndex];

        // Iterate "t" and if the ith and jth letter of both the strings are equal then take the jth letter of "t"
        for(int j = startIndex; j < m; ++j) 
            if(s[i] == t[j]) 
                return memory[i][startIndex] = solveWithMemo(memory, s, t, i+1, j+1);

        // Store the value to the memoization table and then return it
        return memory[i][startIndex] = false;
    }

public:
    // Method to check whether string "s" is a subsequence of string "t", using recursion with memoization - O(M*N*M) & O(N*M)
    bool isSubsequence(string& s, string& t) {
        n = s.size(), m = t.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s, t, 0, 0);
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to check whether string "s" is a subsequence of string "t", using 2D tabulation - O(N*M) & O(N*M)
    bool isSubsequence_V1(string& s, string& t) {
        int n = s.size(), m = t.size();

        // 2D DP table
        vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));

        // Initialize the first edge case: If the string "s" is exhausted then return true
        for(int j = 0; j <= m; ++j)
            dp[n][j] = true;

        // Fill the rest of the table
        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                bool currSkip = dp[i][j+1];
                bool currTake = false;
                if(s[i] == t[j]) {
                    currTake = dp[i+1][j+1];
                }
                dp[i][j] = (currSkip || currTake); 
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to check whether string "s" is a subsequence of string "t" or not, using 1D tabulation - O(N*M) & O(M)
    bool isSubsequence_V2(string& s, string& t) {
        int n = s.size(), m = t.size();

        // 1D DP tables
        vector<bool> nextRow(m+1, false), idealRow(m+1, false);

        // Initialize the first edge case: If the string "s" is exhausted then return true
        for(int j = 0; j <= m; ++j)
            nextRow[j] = true;

        // Fill the rest of the table
        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                bool currSkip = idealRow[j+1];
                bool currTake = false;
                if(s[i] == t[j]) {
                    currTake = nextRow[j+1];
                }
                idealRow[j] = (currSkip || currTake); 
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TwoPointers {
public:
    // Method to check whether string "s" is a subsequence of string "t", using two pointers technique - O(N+M) & O(1)
    bool isSubsequence(string& s, string& t) {
        int n = s.size(), m = t.size(), i = 0, j = 0;
        
        while(i < n && j < m) {
            if(s[i] == t[j]) {
                i++;
            }
            j++;
        }

        // If the string "s" is exhausted then return true
        return i == n;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String | Dynamic Programming
Link  : https://leetcode.com/problems/is-subsequence/description/
