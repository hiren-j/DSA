// Code to find the maximum cost among all substrings of the string `s` ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<int> values;
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const string& s, int index, bool prevPick) {
        if(index == n)  
            return 0;

        if(prevPick) {
            int pickCurrSubarr = values[s[index] - 'a'] + solveWithoutMemo(s, index + 1, true);
            int stopHere = 0;
            return max(pickCurrSubarr, stopHere);
        }
        else {
            int startNewFromNext = solveWithoutMemo(s, index + 1, false);
            int startNewFromCurr = values[s[index] - 'a'] + solveWithoutMemo(s, index + 1, true);
            return max(startNewFromNext, startNewFromCurr);
        }
    }

    // O(2*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& dp, const string& s, int index, bool prevPick) {
        if(index == n)  
            return 0;

        if(dp[index][prevPick] != -1)
            return dp[index][prevPick];

        if(prevPick) {
            int pickCurrSubarr = values[s[index] - 'a'] + solveWithMemo(dp, s, index + 1, true);
            int stopHere = 0;
            return dp[index][prevPick] = max(pickCurrSubarr, stopHere);
        }
        else {
            int startNewFromNext = solveWithMemo(dp, s, index + 1, false);
            int startNewFromCurr = values[s[index] - 'a'] + solveWithMemo(dp, s, index + 1, true);
            return dp[index][prevPick] = max(startNewFromNext, startNewFromCurr);
        }
    }

public:
    // Method to find the maximum cost among all substrings, using recursion with memoization - O(N) & O(N) 
    int maximumCostSubstring(string& s, string& chars, vector<int>& vals) {
        values.resize(26);

        for(int i = 0; i < 26; ++i) {
            values[i] = i + 1;
        }
        for(int i = 0; i < chars.size(); ++i) {
            int char_idx = chars[i] - 'a';
            values[char_idx] = vals[i];
        }
        
        n = s.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveWithMemo(dp, s, 0, false);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<int> values;
    int n;

    // O(N*2) & O(N*2)
    int solveUsing2DTable(const string& s) {
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = values[s[index] - 'a'] + dp[index + 1][true];
                    int stopHere = 0;
                    dp[index][prevPick] = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = dp[index + 1][false];
                    int startNewFromCurr = values[s[index] - 'a'] + dp[index + 1][true];
                    dp[index][prevPick]  = max(startNewFromNext, startNewFromCurr);
                }
            }
        }

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveUsing1DTable(const string& s) {
        vector<int> nextRow(2, 0), idealRow(2, 0);

        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = values[s[index] - 'a'] + nextRow[true];
                    int stopHere = 0;
                    idealRow[prevPick] = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = nextRow[false];
                    int startNewFromCurr = values[s[index] - 'a'] + nextRow[true];
                    idealRow[prevPick] = max(startNewFromNext, startNewFromCurr);
                }
            }
            nextRow = idealRow;
        }

        return idealRow[false];
    }

    // O(N*2) & O(1)
    int solveInPlace(const string& s) {
        int nextFalse  = 0, nextTrue  = 0;
        int idealFalse = 0, idealTrue = 0;

        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = values[s[index] - 'a'] + nextTrue;
                    int stopHere = 0;
                    idealTrue = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = nextFalse;
                    int startNewFromCurr = values[s[index] - 'a'] + nextTrue;
                    idealFalse = max(startNewFromNext, startNewFromCurr);
                }
            }
            nextFalse = idealFalse;
            nextTrue  = idealTrue;
        }

        return idealFalse;
    }

public:
    // Method to find the maximum cost among all substrings, using tabulation :- 
    int maximumCostSubstring(string& s, string& chars, vector<int>& vals) {
        values.resize(26);

        for(int i = 0; i < 26; ++i) {
            values[i] = i + 1;
        }
        for(int i = 0; i < chars.size(); ++i) {
            int char_idx = chars[i] - 'a';
            values[char_idx] = vals[i];
        }
        
        n = s.size();
        return solveInPlace(s);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/find-the-substring-with-maximum-cost/description/?envType=problem-list-v2&envId=dynamic-programming
