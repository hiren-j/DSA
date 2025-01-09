// Code to find the minimum number of substrings in a partition. You've to partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class TopDown {
public:
    // Method to find the minimum number of substrings in such partition, using recursion with memoization - O(N*N) & O(N)
    int partitionString(string& s) {
        int n = s.size();
        vector<int> memory(n, -1);
        return solveWithMemo(memory, s, n, 0);
    }

private:
    // O(N*N) & (N + N*26)
    int solveWithMemo(vector<int>& memory, const string& s, int n, int startIndex) {
        // Edge case: If all the letters are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];

        // Tracks the frequency of letters
        vector<int> count(26);

        // Stores the result value
        int minCount = INT_MAX;

        // Consider each substring starting from the `startIndex`. Make sure to consider those in which all the letters are unique, After considering a substring assume a partition on that index and then do the same from the next index. Among all the partitions store the value which gives the minimum one
        for(int index = startIndex; index < n; ++index) {
            int ch = s[index] - 'a';
            count[ch]++;
            if(count[ch] > 1) 
                break;
            int nextCount = solveWithMemo(memory, s, n, index + 1);
            minCount = min(minCount, nextCount + 1);
        }
        
        // Store the result value to the memoization table and then return it
        return memory[startIndex] = minCount;
    }

    // O(N^N) & (N*26)
    int solveWithoutMemo(const string& s, int n, int startIndex) {
        // Edge case: If all the letters are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        // Tracks the frequency of letters
        vector<int> count(26);

        // Stores the result value
        int minCount = INT_MAX;

        // Consider each substring starting from the `startIndex`. Make sure to consider those in which all the letters are unique, After considering a substring assume a partition on that index and then do the same from the next index. Among all the partitions store the value which gives the minimum one
        for(int index = startIndex; index < n; ++index) {
            int ch = s[index] - 'a';
            count[ch]++;
            if(count[ch] > 1) 
                break;
            int nextCount = solveWithoutMemo(s, n, index + 1);
            minCount = min(minCount, nextCount + 1);
        }
        
        // Return the result value
        return minCount;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum number of substrings in such partition, using 1D tabulation - O(N*N) & O(N)
    int partitionString(string& s) {
        int n = s.size();

        // 1D DP table: dp[i] represents the minimum number of substrings needed to partition the substring s[i : n-1] such that each substring contains unique letters
        vector<int> dp(n + 1, INT_MAX);

        // Initialize the edge case
        dp[n] = 0;

        // Fill the rest of the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            vector<int> count(26); 
            int minCount = INT_MAX;

            for(int index = startIndex; index < n; ++index) {
                int ch = s[index] - 'a';
                count[ch]++;
                if(count[ch] > 1) 
                    break;
                int nextCount = dp[index + 1];
                minCount = min(minCount, nextCount + 1);
            }

            dp[startIndex] = minCount;
        }

        // Return the result value
        return dp[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/optimal-partition-of-string/description/
