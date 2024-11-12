// Code to find the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted. A string "s" is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<char> vowels = {'a','e','i','o','u'};

public:
    // Method to find the number of such strings of length n, using recursion with memoization - O(N) & O(N)
    int countVowelStrings(int n) {
        vector<vector<int>> memory(n + 1, vector<int>(26, -1));
        return solveWithMemo(memory, n, 'w');
    }

private:
    // O(5*N*26) & O(N*26 + N)
    int solveWithMemo(vector<vector<int>>& memory, int n, int prevLetter) {
        // Edge case: If you've created such string of length n then return 1
        if(n == 0)
            return 1;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n][prevLetter - 'a'] != -1)
            return memory[n][prevLetter - 'a'];
        
        // Stores the result value
        int count = 0;

        // Explore all the ways of creating such string from the vowels
        for(char v : vowels) 
            if(prevLetter == 'w' || prevLetter <= v) 
                count += solveWithMemo(memory, n - 1, v);

        // Store the result value to the memoization table and then return it
        return memory[n][prevLetter - 'a'] = count;
    }

    // O(5^N) & O(N)
    int solveWithoutMemo(int n, int prevLetter) {
        // Edge case: If you've created such string of length n then return 1
        if(n == 0)
            return 1;
        
        // Stores the result value
        int count = 0;

        // Explore all the ways of creating such string from the vowels
        for(char v : vowels) 
            if(prevLetter == 'w' || prevLetter <= v) 
                count += solveWithoutMemo(n - 1, v);

        // Return the result value
        return count;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<char> vowels = {'a','e','i','o','u'};

public:
    // #1 Method to find the number of such strings of length n, using 2D tabulation - O(N*23*5) & O(N*26)
    int countVowelStrings_V1(int n) {
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(26, 0));

        // Initialize the edge case: If you've created such string of length n then return 1
        for(int ch = 0; ch < 26; ++ch)
            dp[0][ch] = 1;

        // Fill the rest of the table
        for(int steps = 1; steps <= n; ++steps) {
            for(char prevLetter = 'a'; prevLetter <= 'w'; ++prevLetter) {
                int count = 0;
                for(char v : vowels) {
                    if(prevLetter == 'w' || prevLetter <= v) {
                        count += dp[steps - 1][v - 'a'];
                    }
                }
                dp[steps][prevLetter - 'a'] = count;
            }
        }

        // Return the result value
        return dp[n]['w' - 'a'];
    }

    // #2 Method to find the number of such strings of length n, using 1D tabulation - O(N*23*5) & O(2*26)
    int countVowelStrings_V2(int n) {
        // 1D DP tables
        vector<int> prevRow(26, 0), idealRow(26, 0);

        // Initialize the edge case: If you've created such string of length n then return 1
        for(int ch = 0; ch < 26; ++ch)
            prevRow[ch] = 1;

        // Fill the rest of the table
        for(int steps = 1; steps <= n; ++steps) {
            for(char prevLetter = 'a'; prevLetter <= 'w'; ++prevLetter) {
                int count = 0;
                for(char v : vowels) {
                    if(prevLetter == 'w' || prevLetter <= v) {
                        count += prevRow[v - 'a'];
                    }
                }
                idealRow[prevLetter - 'a'] = count;
            }
            prevRow = idealRow;
        }

        // Return the result value
        return prevRow['w' - 'a'];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Combinatorics
Link  : https://leetcode.com/problems/count-sorted-vowel-strings/description/
