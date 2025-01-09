// Code to find the minimum number of substrings such that you can partition the string "s" into one or more balanced substrings ~ coded by Hiren
 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum number of substrings that you can partition "s" into, using recursion with memoization - O(N*N) & O(N)
    int minimumSubstringsInPartition(string& s) {
        int n = s.size();
        vector<int> memory(n, -1);
        return solveWithMemo(memory, s, 0, n);
    }

private:
    // O(N*N*26) & O(N + N*26)
    int solveWithMemo(vector<int>& memory, string& s, int startIndex, int n) {
        // Base case: If all the letters are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];

        // Stores the result value
        int minPartitions = INT_MAX;

        // Tracks the frequency of letters of a particular partition
        vector<int> count(26);

        // Perform all the partitions one by one and update the result value by the minimum value
        for(int index = startIndex; index < n; ++index) {
            count[s[index] - 'a']++;
            if(isBalanced(count)) {
                int currPartitions = 1 + solveWithMemo(memory, s, index + 1, n);
                minPartitions = min(minPartitions, currPartitions);
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex] = minPartitions;
    }

    // O(N^N * 26) & O(N*26)
    int solveWithoutMemo(string& s, int startIndex, int n) {
        // Base case: If all the letters are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        // Stores the result value
        int minPartitions = INT_MAX;

        // Tracks the frequency of letters of a particular partition
        vector<int> count(26);

        // Perform all the partitions one by one and update the result value by the minimum value
        for(int index = startIndex; index < n; ++index) {
            count[s[index] - 'a']++;
            if(isBalanced(count)) {
                int currPartitions = 1 + solveWithoutMemo(s, index + 1, n);
                minPartitions = min(minPartitions, currPartitions);
            }
        }

        // Return the result value
        return minPartitions;
    }

private:
    // Method to check whether a substring is balanced or not - O(26) & O(1)
    bool isBalanced(vector<int>& count) {
        int prevCount = -1;

        // If the frequency of each letter is not same then the string is not balanced
        for(int ch = 0; ch < 26; ++ch) {
            if(count[ch] > 0) {
                if(prevCount != -1 && count[ch] != prevCount) {
                    return false;
                }
                prevCount = count[ch];
            }
        }
    
        return true;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum number of substrings that you can partition "s" into, using 1D tabulation - O(N*N*26) & O(N+26)
    int minimumSubstringsInPartition(string& s) {
        int n = s.size();

        // DP Table: dp[startIndex] represents the minimum number of substrings that you can partition "s" into such that by considering the string of index "n-1" to "startIndex"
        vector<int> dp(n + 1, INT_MAX);

        // Initialize the base case: If all the letters are exhausted then you can't do any partitions
        dp[n] = 0;

        // Fill the rest of the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            int minPartitions = INT_MAX;           
            vector<int> count(26);

            for(int index = startIndex; index < n; ++index) {
                count[s[index] - 'a']++;
                if(isBalanced(count)) {
                    int currPartitions = 1 + dp[index + 1];
                    minPartitions = min(minPartitions, currPartitions);
                }
            }

            dp[startIndex] = minPartitions;
        }

        // Return the result value
        return dp[0];
    }

private:
    // Method to check whether a substring is balanced or not - O(26) & O(1)
    bool isBalanced(vector<int>& count) {
        int prevCount = -1;

        // If the frequency of each letter is not same then the string is not balanced
        for(int ch = 0; ch < 26; ++ch) {
            if(count[ch] > 0) {
                if(prevCount != -1 && count[ch] != prevCount) {
                    return false;
                }
                prevCount = count[ch];
            }
        }

        return true;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Hash Table | String | Dynamic Programming | Counting
Link  : https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/description/
