// Code to find the minimum number of substrings such that partition the string into one or more substrings in which each substring is beautiful. If it is impossible to do such partition then return -1 ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum number of substrings in such partition, using recursion with memoization - O(N^3) & O(N)
    int minimumBeautifulSubstrings(string& s) {
        int n = s.size();
        vector<int> memory(n, -1);
        int minCount = solveWithMemo(memory, s, n, 0); 
        return (minCount == INT_MAX) ? -1 : minCount;
    }

private:
    // O(N^3) & O(N+N)
    int solveWithMemo(vector<int>& memory, string& s, int n, int startIndex) {
        // Edge case: If all the elements are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];

        // Stores the result value
        int minCount = INT_MAX;

        // Perform all the partitions one by one and update the result value by the minimum value
        for(int index = startIndex; index < n; ++index) {
            if(isBeautiful(s, startIndex, index)) {
                int nextCount = solveWithMemo(memory, s, n, index + 1);
                if(nextCount != INT_MAX) {
                    minCount = min(minCount, nextCount + 1);
                }
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex] = minCount;
    }

    // O(N^N * N) & O(N)
    int solveWithoutMemo(string& s, int n, int startIndex) {
        // Edge case: If all the elements are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        // Stores the result value
        int minCount = INT_MAX;

        // Perform all the partitions one by one and update the result value by the minimum value
        for(int index = startIndex; index < n; ++index) {
            if(isBeautiful(s, startIndex, index)) {
                int nextCount = solveWithoutMemo(s, n, index + 1);
                if(nextCount != INT_MAX) {
                    minCount = min(minCount, nextCount + 1);
                }
            }
        }

        // As we're striving for the minimum value hence return the minimum count 
        return minCount;
    }

private:    
    // Method to check whether a string is beautiful or not - O(N) & O(1)
    bool isBeautiful(string& s, int start, int end) {
        // Early exit: A string is beautiful if it doesn't contain leading zeros
        if(s[start] == '0')
            return false;
    
        int index        = 0;
        long long number = 0;
    
        while(end >= start) {
            if(s[end] == '1')
                number = number + pow(2, index);
            index++;
            end--;
        }
    
        int val = logBase5(number);
    
        return number == pow(5, val);
    }

    // Method to find the log value of any base - O(LogX) & O(1)
    int logBase5(int x) {
        return log(x) / log(5);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum number of substrings in such partition, using 1D tabulation - O(N^3) & O(N)
    int minimumBeautifulSubstrings(string& s) {
        int n = s.size();

        // DP Table: dp[startIndex] represents the minimum number of substrings that you can partition "s" into such that by considering the string of index "n-1" to "startIndex"
        vector<int> dp(n + 1, INT_MAX);

        // Initialize the edge case: If all the elements are exhausted then you can't do more partitions
        dp[n] = 0;

        // Fill the rest of the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            int minCount = INT_MAX;

            for(int index = startIndex; index < n; ++index) {
                if(isBeautiful(s, startIndex, index)) {
                    int nextCount = dp[index + 1];
                    if(nextCount != INT_MAX) {
                        minCount = min(minCount, nextCount + 1);
                    }
                }
            }

            dp[startIndex] = minCount;
        }
        
        int minCount = dp[0]; 

        // Return the result value
        return (minCount == INT_MAX) ? -1 : minCount;
    }

private:
    // Method to check whether a string is beautiful or not - O(N) & O(1)
    bool isBeautiful(string& s, int start, int end) {
        // Early exit: A string is beautiful if it doesn't contain leading zeros
        if(s[start] == '0')
            return false;
    
        int index        = 0;
        long long number = 0;
    
        while(end >= start) {
            if(s[end] == '1')
                number = number + pow(2, index);
            index++;
            end--;
        }
    
        int val = logBase5(number);
    
        return number == pow(5, val);
    }

    // Method to find the log value of any base - O(LogX) & O(1) : Where X let be the given value
    int logBase5(int x) {
        return log(x) / log(5);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Hash Table | String | Dynamic Programming | Backtracking
Link  : https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/description/
