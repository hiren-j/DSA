// Code to find the total number of ways to decode the given string in the specified way ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the total number of ways to decode the string in the specified way, using recursion with memoization - O(N) & O(N)
    int numDecodings(string& s) {
        int n = s.size();
        vector<int> memory(n, -1);
        return solveWithMemo(memory, s, n, 0);
    }

private:
    // O(2*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, const string& s, int n, int index) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        if(index == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it in the valid way
        if(s[index] == '0')
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index] != -1)
            return memory[index];

        // If you're here then it's guaranteed that the character lies within '1' to '9' which can be decoded hence consider it and move to the next character
        int numWays = solveWithMemo(memory, s, n, index + 1);

        // If you're here then there are two possible ways of decoding: When the current character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the current character is '2' then you can only decode when the next character lies within '0' to '6'
        if(index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6')))
            numWays += solveWithMemo(memory, s, n, index + 2);
        
        // Store the result value to the memoization table and then return it
        return memory[index] = numWays;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(const string& s, int n, int index) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        if(index == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it in the valid way
        if(s[index] == '0')
            return 0;

        // If you're here then it's guaranteed that the character lies within '1' to '9' which can be decoded hence consider it and move to the next character
        int numWays = solveWithoutMemo(s, n, index + 1);

        // If you're here then there are two possible ways of decoding: When the current character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the current character is '2' then you can only decode when the next character lies within '0' to '6'
        if(index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6')))
            numWays += solveWithoutMemo(s, n, index + 2);

        // Return the result value 
        return numWays;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the total number of ways to decode the string in the specified way, using 1D tabulation - O(N) & O(N)
    int numDecodings_V1(string& s) {
        int n = s.size();

        // 1D table: dp[i] represents the total number of ways to decode the string from index 0 to i-1
        vector<int> dp(n + 1, 0);

        // Initialize the edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        dp[n] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            if(s[index] != '0') {
                int numWays = dp[index + 1];
                if(index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays += dp[index + 2];
                }
                dp[index] = numWays;
            }
        }

        // Return the result value
        return dp[0];
    }

    // #2 Method to find the total number of ways to decode the string in the specified way, using constant auxiliary space - O(N) & O(1)
    int numDecodings_V2(string& s) {
        int n = s.size(), nextWays1 = 1, nextWays2 = 0, result = 0; 

        for(int index = n-1; index >= 0; --index) {
            if(s[index] != '0') {
                int numWays = nextWays1;
                if(index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays += nextWays2;
                }
                result = numWays;
            }
            else {
                result = 0;
            }
            nextWays2 = nextWays1;
            nextWays1 = result;
        }

        return result;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/decode-ways/description/
