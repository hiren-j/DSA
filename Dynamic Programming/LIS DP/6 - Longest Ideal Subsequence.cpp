// Code to find the length of the longest ideal string ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V1 {
public:
    // Method to find the length of the longest ideal string, using recursion with memoization - O(N) & O(N)
    int longestIdealString(const std::string& s, int k) {
        int n = s.size();
        std::vector<std::vector<int>> memory(n, std::vector<int>(123, -1));
        return solveWithMemo(memory, s, k, n, 0, '\0');
    }

private:
    // O(2*N*123) & O(N*123 + N)
    int solveWithMemo(std::vector<std::vector<int>>& memory, const std::string& s, int k, int n, int index, char prevLetter) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(index == n)  
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevLetter] != -1)
            return memory[index][prevLetter];

        // There are always two possibilities to perform at each letter
        int currSkip = solveWithMemo(memory, s, k, n, index + 1, prevLetter); // Is to skip the letter 
        int currTake = 0;                                                     // Is to pick the letter 

        // If the absolute difference between the previous and the current letter is valid then pick the current letter into the subsequence and then move on
        if(prevLetter == '\0' || abs(s[index] - prevLetter) <= k)
            currTake = 1 + solveWithMemo(memory, s, k, n, index + 1, s[index]);

        // Store the result value to the memoization table and then return it
        return memory[index][prevLetter] = std::max(currSkip, currTake);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(const std::string& s, int k, int n, int index, char prevLetter) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each letter
        int currSkip = solveWithoutMemo(s, k, n, index + 1, prevLetter); // Is to skip the letter 
        int currTake = 0;                                                // Is to pick the letter 

        // If the absolute difference between the previous and the current letter is valid then pick the current letter into the subsequence and then move on
        if(prevLetter == '\0' || abs(s[index] - prevLetter) <= k)
            currTake = 1 + solveWithoutMemo(s, k, n, index + 1, s[index]);

        // As we're striving for the maximum length hence return the maximum value
        return std::max(currSkip, currTake);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V2 {
public:
    // Method to find the length of the longest ideal string, using recursion with memoization - O(N*N) & O(N)
    int longestIdealString(const std::string& s, int k) {
        int n = s.size();
        std::vector<std::vector<int>> memory(n, std::vector<int>(123, -1));
        return solveWithMemo(memory, s, k, n, 0, '\0');
    }

private:
    // O(N*N*123) & O(N*123 + N)
    int solveWithMemo(std::vector<std::vector<int>>& memory, const std::string& s, int k, int n, int startIndex, char prevLetter) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][prevLetter] != -1)
            return memory[startIndex][prevLetter];

        // Stores the result value
        int maxLength = 0;

        // Find the length of all the longest ideal strings and update the result by the maximum value
        for(int index = startIndex; index < n; ++index) 
            if(prevLetter == '\0' || abs(s[index] - prevLetter) <= k)        
                maxLength = std::max(maxLength, 1 + solveWithMemo(memory, s, k, n, index + 1, s[index]));
        
        // Store the result value to the memoization table and then return it
        return memory[startIndex][prevLetter] = maxLength;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(const std::string& s, int k, int n, int startIndex, char prevLetter) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(startIndex == n)
            return 0;
        
        // Stores the result value
        int maxLength = 0;

        // Find the length of all the longest ideal strings and update the result by the maximum value
        for(int index = startIndex; index < n; ++index) 
            if(prevLetter == '\0' || abs(s[index] - prevLetter) <= k)          
                maxLength = std::max(maxLength, 1 + solveWithoutMemo(s, k, n, index + 1, s[index]));
        
        // Return the result value                
        return maxLength;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2). It will lead to the time-limit-exceed

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // #1 Method to find the length of the longest ideal string, using 2D tabulation - O(N*123) & O(N*123)
    int longestIdealString_V1(const std::string& s, int k) {
        int n = s.size();

        // 2D DP table
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(123, 0));

        // Fill the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevLetter = 122; prevLetter >= 0; --prevLetter) {
                int currSkip = dp[index + 1][prevLetter];
                int currTake = 0;
                if(prevLetter == '\0' || abs(s[index] - prevLetter) <= k) {
                    currTake = 1 + dp[index + 1][s[index]];
                }
                dp[index][prevLetter] = std::max(currSkip, currTake);
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the length of the longest ideal string, using 1D tabulation - O(N*123) & O(2*123)
    int longestIdealString_V2(const std::string& s, int k) {
        int n = s.size();

        // 1D DP tables
        std::vector<int> nextRow(123, 0), idealRow(123, 0);

        // Fill the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevLetter = 122; prevLetter >= 0; --prevLetter) {
                int currSkip = nextRow[prevLetter];
                int currTake = 0;
                if(prevLetter == '\0' || abs(s[index] - prevLetter) <= k) {
                    currTake = 1 + nextRow[s[index]];
                }
                idealRow[prevLetter] = std::max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[0];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Hash Table | String | Dynamic Programming 
Link  : https://leetcode.com/problems/longest-ideal-subsequence/description/
