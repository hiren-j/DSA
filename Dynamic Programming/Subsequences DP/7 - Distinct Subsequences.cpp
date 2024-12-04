// Code to count the total number of subsequences of string "s1" equal to string "s2" ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
    int n, m;

    // O(2^(N+M)) & O(N)
    int solveWithoutMemo(string& s1, string& s2, int i, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
            
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(i == n)
            return 0;
            
        // There are always two possibilites to perform at each index
        int currSkip = solveWithoutMemo(s1, s2, i + 1, j); // Is to skip the ith letter of "s1"
        int currTake = 0;                                  // Is to take the ith letter of "s1"
        
        // If the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        if(s1[i] == s2[j])
            currTake = solveWithoutMemo(s1, s2, i + 1, j + 1);
            
        // Return the result value
        return (currSkip + currTake);
    }
    
    // O(2*N*M) & O(N*M + N)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int i, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
        
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(i == n)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];
        
        // There are always two possibilites to perform at each index
        int currSkip = solveWithMemo(memory, s1, s2, i + 1, j); // Is to skip the ith letter of "s1"
        int currTake = 0;                                       // Is to take the ith letter of "s1"      
        
        // If the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        if(s1[i] == s2[j])
            currTake = solveWithMemo(memory, s1, s2, i + 1, j + 1);
        
        // Store the result value to the memoization table and then return it
        return memory[i][j] = (currSkip + currTake);
    }
    
public:
    // Method to count the total number of subsequences of string "s1" equal to string "s2", using recursion with memoization - O(N*M) & O(N*M)
    int numDistinct(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, 0, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
    int n, m;

    // O(N^N) & O(N)
    int solveWithoutMemo(string& s1, string& s2, int startIndex, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
            
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(startIndex == n)
            return 0;

        // Stores the result value
        int resCount = 0;

        // Iterate "s1" and if the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        for(int i = startIndex; i < n; ++i) 
            if(s1[i] == s2[j]) 
                resCount += solveWithoutMemo(s1, s2, i + 1, j + 1);

        // Return the result value
        return resCount;
    }

    // O(N*N*M) & O(N*M + N)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int startIndex, int j) {
        // Edge case: If all the letters of "s2" are exhausted then you've one valid way 
        if(j == m)
            return 1;
            
        // Edge case: If all the letters of "s1" are exhausted then you've no valid way 
        if(startIndex == n)
            return 0;
        
        // Edge case: If the current state is already computed then return the computed value
        if(memory[startIndex][j] != -1)
            return memory[startIndex][j];

        // Stores the result value
        int resCount = 0;

        // Iterate "s1" and if the ith and jth letter of both the strings are equal then take the ith letter of "s1"
        for(int i = startIndex; i < n; ++i) 
            if(s1[i] == s2[j]) 
                resCount += solveWithMemo(memory, s1, s2, i + 1, j + 1);
        
        // Store the result value to the memoization table and then return it
        return memory[startIndex][j] = resCount;
    }
    
public:
    // Method to count the total number of subsequences of string "s1" equal to string "s2", using recursion with memoization - O(N*N*M) & O(N*M)
    int numDistinct(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, 0, 0);
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // #1 Method to count the total number of subsequences of string "s1" equal to string "s2", using 2D tabulation - O(N*M) & O(N*M)
    int numDistinct_V1(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 2D DP table
        vector<vector<unsigned int>> dp(n + 1, vector<unsigned int>(m + 1, 0));

        // Initialize the first edge case: If all the letters of "s2" are exhausted then you've one valid way 
        for(int i = 0; i <= n; ++i)
            dp[i][m] = 1;

        // Fill the rest of the table
        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                unsigned int currSkip = dp[i + 1][j]; 
                unsigned int currTake = 0;
                if(s1[i] == s2[j]) {
                    currTake = dp[i + 1][j + 1];
                }
                dp[i][j] = (currSkip + currTake);
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to count the total number of subsequences of string "s1" equal to string "s2", using 1D tabulation - O(N*M) & O(M)
    int numDistinct_V2(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 1D DP tables
        vector<unsigned int> nextRow(m + 1, 0), idealRow(m + 1, 0);        
        nextRow[m] = 1;

        // Fill the rest of the table
        for(int i = n-1; i >= 0; --i) {
            idealRow[m] = 1;
            for(int j = m-1; j >= 0; --j) {
                unsigned int currSkip = nextRow[j]; 
                unsigned int currTake = 0;
                if(s1[i] == s2[j]) {
                    currTake = nextRow[j + 1];
                }
                idealRow[j] = (currSkip + currTake);
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/discuss/interview-question/433901/Google-or-Phone-or-Distinct-subsequences
        https://leetcode.com/problems/distinct-subsequences/description/
