// Code to find the length of the longest subsequence in array which is an arithmetic sequence such that the difference between adjacent elements in the subsequence is equal to the given difference ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the length of the longest arithmetic subsequence of given difference, using recursion with 2D memoization - O(N*N) & O(N*N)
    int longestSubsequence(vector<int>& nums, int difference) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, nums, difference, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int difference, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevIndex + 1] != -1)
            return memory[index][prevIndex + 1];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, nums, difference, n, index + 1, prevIndex); // Is to skip the index value 
        int currTake = 0;                                                                // Is to pick the index value 

        // If the difference between current and the previous value is equal to the given difference then pick the current value
        if(prevIndex == -1 || nums[index] - nums[prevIndex] == difference)
            currTake = 1 + solveWithMemo(memory, nums, difference, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[index][prevIndex + 1] = max(currSkip, currTake);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int difference, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(nums, difference, n, index + 1, prevIndex); // Is to skip the index value 
        int currTake = 0;                                                                // Is to pick the index value 

        // If the difference between current and the previous value is equal to the given difference then pick the current value
        if(prevIndex == -1 || nums[index] - nums[prevIndex] == difference)
            currTake = 1 + solveWithoutMemo(nums, difference, n, index + 1, index);

        // As we're striving for the longest length hence return the maximum value
        return max(currSkip, currTake);
    }
};
// Note: This solution can lead to the memory-limit-exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V2 {
public:
    // Method to find the length of the longest arithmetic subsequence of given difference, using recursion with 1D memoization - O(N*N) & O(N)
    int longestSubsequence(vector<int>& nums, int difference) {
        int n = nums.size();
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, nums, difference, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int difference, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[prevIndex + 1] != -1)
            return memory[prevIndex + 1];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, nums, difference, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                                // Is to pick the index value    

        // If the difference between current and the previous value is equal to the given difference then pick the current value
        if(prevIndex == -1 || nums[index] - nums[prevIndex] == difference)
            currTake = 1 + solveWithMemo(memory, nums, difference, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[prevIndex + 1] = max(currSkip, currTake);
    }
};
// Note: This solution (TopDown_V2) is the space optimized version of the (TopDown_V1) solution but it will lead to the time-limit-exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V3 {
public:
    // Method to find the length of the longest arithmetic subsequence of given difference, using recursion with 2D memoization - O(N^3) & O(N^2)
    int longestSubsequence(vector<int>& nums, int difference) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, nums, difference, n, 0, -1);
    }

private:
    // O(N*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int difference, int n, int startIndex, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't pick any more
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][prevIndex + 1] != -1)
            return memory[startIndex][prevIndex + 1];

        // Stores the result value
        int maxLength = 0;

        // Iterate and if the difference between previous and the index value is equal to the given difference then pick the index value
        for(int index = startIndex; index < n; ++index) 
            if(prevIndex == -1 || nums[index] - nums[prevIndex] == difference)
                maxLength = max(maxLength, 1 + solveWithMemo(memory, nums, difference, n, index + 1, index));

        // Store the result value to the memoization table and then return it
        return memory[startIndex][prevIndex + 1] = maxLength;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code
};
// Note: This solution (TopDown_V3) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V3). It will give memory-limit-exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // #1 Method to find the length of the longest arithmetic subsequence of given difference, using 2D tabulation - O(N*N) & O(N*N)
    int longestSubsequence_V1(vector<int>& nums, int difference) {
        int n = nums.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = index-1; prevIndex >= -1; --prevIndex) {
                int currSkip = dp[index + 1][prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || nums[index] - nums[prevIndex] == difference) {
                    currTake = 1 + dp[index + 1][index + 1];
                }
                dp[index][prevIndex + 1] = max(currSkip, currTake);
            }
        }

        return dp[0][0];
    }
    // Note: This bottom-up solution is created from the memoized solution of (TopDown_V1). It will lead to the memory-limit-exceed

    // #2 Method to find the length of the longest arithmetic subsequence of given difference, using 1D tabulation - O(N*N) & O(N)
    int longestSubsequence_V2(vector<int>& nums, int difference) {
        int n = nums.size();

        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = index-1; prevIndex >= -1; --prevIndex) {
                int currSkip = nextRow[prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || nums[index] - nums[prevIndex] == difference) {
                    currTake = 1 + nextRow[index + 1];
                }
                idealRow[prevIndex + 1] = max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        return idealRow[0];
    }
    // Note: This solution can lead to the time-limit-exceed
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the length of the longest arithmetic subsequence of given difference, using 1D tabulation - O(N*N) & O(N)
    int longestSubsequence(vector<int>& nums, int difference) {
        int n = nums.size();

        // 1D table: dp[index] represents the length of the longest subsequence ending at the individual index
        vector<int> dp(n, 1);

        // Fill the table
        for(int index = 0; index < n; ++index) 
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) 
                if(nums[index] - nums[prevIndex] == difference)
                    dp[index] = max(dp[index], 1 + dp[prevIndex]);

        // Return the result value
        return *max_element(begin(dp), end(dp));
    }
};
// Note: This solution can lead to the time-limit-exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V3 {
public:
    // Method to find the length of the longest arithmetic subsequence of given difference, using unordered map - O(N) & O(N)
    int longestSubsequence(vector<int>& nums, int difference) {
        int n = nums.size(), maxLength = 0;

        // Stores the length of the longest arithmetic subsequence which can be seen till an index value 
        unordered_map<int, int> mp;

        for(int currNum : nums) {
            int prevNum        = currNum - difference;
            int lengthTillPrev = mp[prevNum];
            mp[currNum]        = lengthTillPrev + 1;
            maxLength          = max(maxLength, mp[currNum]);
        }

        return maxLength;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | Dynamic Programming 
Link  : https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/description/
