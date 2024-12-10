// Code to find the length of the longest subsequence of the array that sums up to target. If no such subsequence exists then return -1 ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the length of the longest subsequence which sums to target, using recursion with memoization - O(N*T) & O(N*T) : Where T let be the target
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(target + 1, -1));
        int maxLength = solveWithMemo(memory, nums, n, 0, target);
        return (maxLength == INT_MIN) ? -1 : maxLength;
    }

private:
    // O(2*N*T) & O(N*T + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int index, int target) {
        // Edge case: If the target becomes 0 then return 0 as a valid indication of it
        if(target == 0)
            return 0;
            
        // Edge case: If all the elements are exhausted then you can't take more
        if(index == n)
            return INT_MIN;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][target] != -1)
            return memory[index][target];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, nums, n, index + 1, target); // Is to skip the index value
        int currTake = INT_MIN;                                           // Is to take the index value                                          

        // If possible then take the index value
        if(nums[index] <= target) {
            int nextLength = solveWithMemo(memory, nums, n, index + 1, target - nums[index]);
            currTake = (nextLength != INT_MIN) ? 1 + nextLength : INT_MIN;
        }

        // Store the result value value to the memoization table and then return it
        return memory[index][target] = max(currTake, currSkip);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int index, int target) {
        // Edge case: If the target becomes 0 then return 0 as a valid indication of it
        if(target == 0)
            return 0;
            
        // Edge case: If all the elements are exhausted then you can't take more
        if(index == n)
            return INT_MIN;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(nums, n, index + 1, target); // Is to skip the index value
        int currTake = INT_MIN;                                      // Is to take the index value                                            

        // If possible then take the index value
        if(nums[index] <= target) {
            int nextLength = solveWithoutMemo(nums, n, index + 1, target - nums[index]);
            currTake = (nextLength != INT_MIN) ? 1 + nextLength : INT_MIN;
        }

        // As we're striving for the longest length hence return the maximum value
        return max(currTake, currSkip);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the length of the longest subsequence which sums to target, using recursion with memoization - O(N*N*T) & O(N*T)
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(target + 1, -1));
        int maxLength = solveWithoutMemo(nums, n, 0, target);
        return (maxLength == INT_MIN) ? -1 : maxLength;
    }

private:
    // O(N*N*T) & O(N*T + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int startIndex, int target) {
        // Edge case: If the target becomes 0 then return the value 0 as a valid indication of it
        if(target == 0)
            return 0;

        // Edge case: If all the elements are exhausted then you can't take more
        if(startIndex == n)
            return INT_MIN;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][target] != -1)
            return memory[startIndex][target];
        
        // Stores the result value        
        int maxLength = INT_MIN;

        // Iterate and if possible then take the index value
        for(int index = startIndex; index < n; ++index) {
            if(nums[index] <= target) {
                int nextLength = solveWithMemo(memory, nums, n, index + 1, target - nums[index]);
                if(nextLength != INT_MIN) {
                    maxLength = max(maxLength, 1 + nextLength);
                }
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex][target] = maxLength;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int startIndex, int target) {
        // Edge case: If the target becomes 0 then return the value 0 as a valid indication of it
        if(target == 0)
            return 0;

        // Stores the result value
        int maxLength = INT_MIN;

        // Iterate and if possible then take the index value
        for(int index = startIndex; index < n; ++index) {
            if(nums[index] <= target) {
                int nextLength = solveWithoutMemo(nums, n, index + 1, target - nums[index]);
                if(nextLength != INT_MIN) {
                    maxLength = max(maxLength, 1 + nextLength);
                }
            }
        }

        // Return the result value
        return maxLength;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the length of the longest subsequence which sums to target, using 2D tabulation - O(N*T) & O(N*T)
    int lengthOfLongestSubsequence_V1(vector<int>& nums, int target) {
        int n = nums.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, INT_MIN));

        // Initialize the first edge case: If the target becomes 0 then return 0 as a valid indication of it
        for(int index = 0; index <= n; ++index)
            dp[index][0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int currTarget = 1; currTarget <= target; ++currTarget) {
                int currSkip = dp[index + 1][currTarget]; 
                int currTake = INT_MIN;                                            
                if(nums[index] <= currTarget) {
                    int nextLength = dp[index + 1][currTarget - nums[index]];
                    currTake = (nextLength != INT_MIN) ? 1 + nextLength : INT_MIN;
                }
                dp[index][currTarget] = max(currTake, currSkip);
            }
        }

        // Return the result value
        return (dp[0][target] == INT_MIN) ? -1 : dp[0][target];
    }

    // #2 Method to find the length of the longest subsequence which sums to target, using 1D tabulation - O(N*T) & O(T)
    int lengthOfLongestSubsequence_V2(vector<int>& nums, int target) {
        int n = nums.size();

        // 1D DP tables
        vector<int> nextRow(target + 1, INT_MIN), idealRow(target + 1, INT_MIN);
        nextRow[0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            idealRow[0] = 0;
            for(int currTarget = 1; currTarget <= target; ++currTarget) {
                int currSkip = nextRow[currTarget]; 
                int currTake = INT_MIN;                                            
                if(nums[index] <= currTarget) {
                    int nextLength = nextRow[currTarget - nums[index]];
                    currTake = (nextLength != INT_MIN) ? 1 + nextLength : INT_MIN;
                }
                idealRow[currTarget] = max(currTake, currSkip);
            }
            nextRow = idealRow;
        }

        // Return the result value
        return (nextRow[target] == INT_MIN) ? -1 : nextRow[target];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/description/
