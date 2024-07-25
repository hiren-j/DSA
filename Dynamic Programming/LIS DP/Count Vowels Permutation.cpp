// Code to count how many strings of length n can be formed under the mentioned rules ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
    vector<char> vowels = {'a','e','i','o','u'};

public:
    // Method to count how many such strings of length n that can be formed, using recursion with memoization - O(N) & O(N)
    int countVowelPermutation(int n) {
        vector<vector<int>> memory(n + 1, vector<int>(26, -1));
        return solveWithMemo(memory, n, 'w');
    }

private:
    // O(5*N*26) & O(N*26 + N)
    int solveWithMemo(vector<vector<int>>& memory, int n, char prevLetter) {
        // Edge case: If you've created such string of length n then return 1
        if(n == 0)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n][prevLetter - 'a'] != -1)
            return memory[n][prevLetter - 'a'];

        // Stores the result value 
        int count = 0;
        
        // Explore all the ways of creating such string from the vowels
        for(char v : vowels) {
            if(prevLetter == 'w' || (prevLetter == 'a' && v == 'e') || (prevLetter == 'e' && (v == 'a' || v == 'i')) || (prevLetter == 'i' && v != 'i') || (prevLetter == 'o' && (v == 'i' || v == 'u')) || (prevLetter == 'u' && v == 'a')) {
                count = count % MOD + solveWithMemo(memory, n - 1, v) % MOD;
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[n][prevLetter - 'a'] = count % MOD;
    }

    // O(5^N) & O(N)
    int solveWithoutMemo(int n, char prevLetter) {
        // Edge case: If you've created such string of length n then return 1
        if(n == 0)
            return 1;

        // Stores the result value
        int count = 0;
        
        // Explore all the ways of creating such string from the vowels
        for(char v : vowels) {
            if(prevLetter == 'w' || (prevLetter == 'a' && v == 'e') || (prevLetter == 'e' && (v == 'a' || v == 'i')) || (prevLetter == 'i' && v != 'i') || (prevLetter == 'o' && (v == 'i' || v == 'u')) || (prevLetter == 'u' && v == 'a')) {
                count = count % MOD + solveWithoutMemo(n - 1, v) % MOD;
            }
        }

        // Return the result value
        return count % MOD;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Bottom-up approach:
class BottomUp {
    vector<char> vowels = {'a','e','i','o','u'};

public:
    // #1 Method to count how many such strings of length n that can be formed, using 2D tabulation - O(N*23*5) & O(N*26)
    int countVowelPermutation_V1(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(26, 0));
        
        for(int ch = 0; ch < 26; ++ch)
            dp[0][ch] = 1;

        for(int n = 1; n <= n; ++n) {
            for(char prevLetter = 'a'; prevLetter <= 'w'; ++prevLetter) {
                int count = 0;
                for(char v : vowels) {
                    if(prevLetter == 'w' || (prevLetter == 'a' && v == 'e') || (prevLetter == 'e' && (v == 'a' || v == 'i')) || (prevLetter == 'i' && v != 'i') || (prevLetter == 'o' && (v == 'i' || v == 'u')) || (prevLetter == 'u' && v == 'a')) {
                        count = count % MOD + dp[n - 1][v - 'a'] % MOD;
                    }
                }
                dp[n][prevLetter - 'a'] = count % MOD;
            }
        }

        return dp[n]['w' - 'a'];
    }

    // #2 Method to count how many such strings of length n that can be formed, using 1D tabulation - O(N*23*5) & O(2*26)
    int countVowelPermutation_V2(int n) {
        vector<int> prevRow(26, 0), currRow(26, 0);

        for(int ch = 0; ch < 26; ++ch)
            prevRow[ch] = 1;

        for(int n = 1; n <= n; ++n) {
            for(char prevLetter = 'a'; prevLetter <= 'w'; ++prevLetter) {
                int count = 0;
                for(char v : vowels) {
                    if(prevLetter == 'w' || (prevLetter == 'a' && v == 'e') || (prevLetter == 'e' && (v == 'a' || v == 'i')) || (prevLetter == 'i' && v != 'i') || (prevLetter == 'o' && (v == 'i' || v == 'u')) || (prevLetter == 'u' && v == 'a')) {
                        count = count % MOD + prevRow[v - 'a'] % MOD;
                    }
                }
                currRow[prevLetter - 'a'] = count % MOD;
            }
            prevRow = currRow;
        }

        return prevRow['w' - 'a'];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://leetcode.com/problems/count-vowels-permutation/
