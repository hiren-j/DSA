// Code to find the total number of ways to decode the given string in the specified way. In addition to the specified mapping, an encoded message may contain the '*' character, which can represent any digit from '1' to '9' ('0' is excluded) ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    int n;

    int getLimit(char digit) {
        if(digit == '1')
            return 9;
        if(digit == '2')
            return 6;
        return 0;
    }

    // O(N + 9*N + 9*N) & O(N + N)
    int solveWithMemo(vector<int>& memory, const string& s, int index) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        if(index == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it in the valid way
        if(s[index] == '0')
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index] != -1)
            return memory[index];

        // If you're here then the character could be within '1' to '9' or it could be a '*' which can be decoded hence consider it and move to the next character. Remember when it's a '*' then suppose we're considering it for the digit '1' only
        int numWays = solveWithMemo(memory, s, index + 1) % MOD;

        // If it's confirmly a '*' then consider it for the rest of the digits from '2' to '9'
        if(s[index] == '*') {
            for(int digit = 2; digit <= 9; ++digit) {
                numWays = (numWays + solveWithMemo(memory, s, index + 1)) % MOD;
            }
        }

        // At this point now we will look for the cases when we've to consider both the characters together
        if(index + 1 < n) {
            // When both the characters are '*' then there are two possible ways of decoding: Consider the first character as '1' then for it consider the second character to be within '1' to '9'. If you consider the first character as '2' then for it consider the second character to be within '1' to '6'
            if(s[index] == '*' && s[index + 1] == '*') {
                for(int digit = 1; digit <= 9; ++digit) {
                    numWays = (numWays + solveWithMemo(memory, s, index + 2)) % MOD;
                    if(digit <= 6) {
                        numWays = (numWays + solveWithMemo(memory, s, index + 2)) % MOD;
                    }
                }
            }
            // When the first character is a '*' and the second character is not, then you've two ways to decode, which means is to consider the first character as '1' or to consider it as '2'
            else if(s[index] == '*') {
                numWays = (numWays + solveWithMemo(memory, s, index + 2)) % MOD;
                if(s[index + 1] <= '6') {
                    numWays = (numWays + solveWithMemo(memory, s, index + 2)) % MOD;
                }
            }
            // When the second character is a '*' and the first character is not, then you've two ways to decode, in which if the first character is '1' then you can consider the second character to be within '1' to '9'. If the first character is '2' then you can consider the second character to be within '1' to '6' 
            else if(s[index + 1] == '*') {
                for(int digit = 1; (digit <= getLimit(s[index])); ++digit) {
                    numWays = (numWays + solveWithMemo(memory, s, index + 2)) % MOD;
                }
            }
            // If you're here then there are two possible ways of decoding: When the first character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the first character is '2' then you can only decode when the next character lies within '0' to '6'
            else if((s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                numWays = (numWays + solveWithMemo(memory, s, index + 2)) % MOD;
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[index] = numWays % MOD;
    }

public: 
    // Method to find the total number of ways to decode the given string in the specified way, using recursion with memoization - O(N) & O(N)
    int numDecodings(string& s) {
        n = s.size();
        vector<int> memory(n, -1);
        return solveWithMemo(memory, s, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

    int getLimit(char character) {
        if(character == '1')
            return 9;
        if(character == '2')
            return 6;
        return 0;
    }

public: 
    // #1 Method to find the total number of ways to decode the given string in the specified way, using 1D tabulation - O(N) & O(N)
    int numDecodings_V1(string& s) {
        int n = s.size();

        // 1D table: dp[i] represents the total number of ways to decode the string from index 0 to i
        vector<int> dp(n + 1, 0);

        // Initialize the edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        dp[n] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            if(s[index] == '0')
                continue;

            int numWays = dp[index + 1] % MOD;

            if(s[index] == '*') {
                for(int digit = 2; digit <= 9; ++digit) {
                    numWays = (numWays + dp[index + 1]) % MOD;
                }
            }

            if(index + 1 < n) {
                if(s[index] == '*' && s[index + 1] == '*') {
                    for(int digit = 1; digit <= 9; ++digit) {
                        numWays = (numWays + dp[index + 2]) % MOD;
                        if(digit <= 6) {
                            numWays = (numWays + dp[index + 2]) % MOD;
                        }
                    }
                }
                else if(s[index] == '*') {
                    numWays = (numWays + dp[index + 2]) % MOD;
                    if(s[index + 1] <= '6') {
                        numWays = (numWays + dp[index + 2]) % MOD;
                    }
                }
                else if(s[index + 1] == '*') {
                    for(int digit = 1; (digit <= getLimit(s[index])); ++digit) {
                        numWays = (numWays + dp[index + 2]) % MOD;
                    }
                }
                else if((s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays = (numWays + dp[index + 2]) % MOD;
                }
            }
    
            dp[index] = numWays % MOD;
        }

        // Return the result value
        return dp[0];
    }
    // #2 Method to find the total number of ways to decode the given string in the specified way, using constant auxiliary space - O(N) & O(1)
    int numDecodings_V2(string& s) {
        int n = s.size(), nextWays1 = 1, nextWays2 = 0, result = 0;

        for(int index = n-1; index >= 0; --index) {
            if(s[index] == '0') {
                result    = 0;
                nextWays2 = nextWays1;
                nextWays1 = result;
                continue;
            }

            int numWays = nextWays1 % MOD;

            if(s[index] == '*') {
                for(int digit = 2; digit <= 9; ++digit) {
                    numWays = (numWays + nextWays1) % MOD;
                }
            }

            if(index + 1 < n) {
                if(s[index] == '*' && s[index + 1] == '*') {
                    for(int digit = 1; digit <= 9; ++digit) {
                        numWays = (numWays + nextWays2) % MOD;
                        if(digit <= 6) {
                            numWays = (numWays + nextWays2) % MOD;
                        }
                    }
                }
                else if(s[index] == '*') {
                    numWays = (numWays + nextWays2) % MOD;
                    if(s[index + 1] <= '6') {
                        numWays = (numWays + nextWays2) % MOD;
                    }
                }
                else if(s[index + 1] == '*') {
                    for(int digit = 1; (digit <= getLimit(s[index])); ++digit) {
                        numWays = (numWays + nextWays2) % MOD;
                    }
                }
                else if((s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays = (numWays + nextWays2) % MOD;
                }
            }
            result    = numWays % MOD;
            nextWays2 = nextWays1;
            nextWays1 = result;
        }

        return result;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/decode-ways-ii/description/
