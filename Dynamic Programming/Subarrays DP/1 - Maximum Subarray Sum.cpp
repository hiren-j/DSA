// Code to find the subarray having the largest sum ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int index, bool prevPick) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return 0 else INT_MIN 
        if(index == n)
            return (prevPick) ? 0 : INT_MIN;

        // Previously if you've picked any subarray then you've two possibilities on the index 
        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithoutMemo(nums, index + 1, true); // Pick the index element or current subarray as a part of the previous subarray
            int stopHere = 0;                                                           // Consider the index as an end point for the previous subarray    
            return max(pickCurrSubarr, stopHere);                                       // As we're striving for the maximum sum hence return the maximum value
        }
        // If you haven't picked any subarray till now then you've two possibilities on the index
        else {
            int startNewFromNext = solveWithoutMemo(nums, index + 1, false);              // Start a new subarray from the next index
            int startNewFromCurr = nums[index] + solveWithoutMemo(nums, index + 1, true); // Start a new subarray from the current index
            return max(startNewFromNext, startNewFromCurr);                               // As we're striving for the maximum sum hence return the maximum value
        }
    }

    // O(2*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int index, bool prevPick) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return 0 else INT_MIN 
        if(index == n)
            return (prevPick) ? 0 : INT_MIN;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevPick] != -1)
            return memory[index][prevPick];

        // Previously if you've picked any subarray then you've two possibilities on the index 
        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithMemo(memory, nums, index + 1, true); // Pick the index element or current subarray as a part of the previous subarray
            int stopHere = 0;                                                                // Consider the index as an end point for the previous subarray    
            return memory[index][prevPick] = max(pickCurrSubarr, stopHere);                  // Store the result value to the memoization table and then return it
        }
        // If you haven't picked any subarray till now then you've two possibilities on the index
        else {
            int startNewFromNext = solveWithMemo(memory, nums, index + 1, false);              // Start a new subarray from the next index
            int startNewFromCurr = nums[index] + solveWithMemo(memory, nums, index + 1, true); // Start a new subarray from the current index
            return memory[index][prevPick] = max(startNewFromNext, startNewFromCurr);          // Store the result value to the memoization table and then return it
        }
    }

public:  
    // Method to find the maximum sum of a subarray, using recursion with memoization - O(N) & O(N)
    int maxSubArray(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> memory(n, vector<int>(2, -1));
        return solveWithMemo(memory, nums, 0, false);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum sum of a subarray, using 2D tabulation - O(N*2) & O(N*2)
    int maxSubArray_V1(vector<int>& nums) {
        int n = nums.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));

        // Initialize the edge case
        dp[n][1] = 0;
        dp[n][0] = INT_MIN;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + dp[index + 1][true];
                    int stopHere = 0;
                    dp[index][prevPick] = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = dp[index + 1][false];
                    int startNewFromCurr = nums[index] + dp[index + 1][true];
                    dp[index][prevPick] = max(startNewFromNext, startNewFromCurr);
                }
            }
        }

        // Return the result value
        return dp[0][false];
    }

    // #2 Method to find the maximum sum of a subarray, using 1D tabulation - O(N*2) & O(2*2)
    int maxSubArray_V2(vector<int>& nums) {
        int n = nums.size();

        // 1D DP tables
        vector<int> nextRow(2, -1), idealRow(2, -1); 

        // Initialize the edge case
        nextRow[1] = 0;
        nextRow[0] = INT_MIN;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + nextRow[true];
                    int stopHere = 0;
                    idealRow[prevPick] = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = nextRow[false];
                    int startNewFromCurr = nums[index] + nextRow[true];
                    idealRow[prevPick] = max(startNewFromNext, startNewFromCurr);
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[false];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class KadaneAlgorithm {
public: 
    // Method to find the maximum sum of a subarray - O(N) & O(1)
    int maxSubArray(vector<int>& nums) {
        int maxEnding = 0; // Represents the maximum sum of a subarray among all the subarrays ending at an index
        int result = INT_MIN;

        // Note: If you're on a index then you've two possibilities on it: 
        // 1. To start a new subarray from it
        // 2. Pick the index element as a part of the maximum subarray seen till its previous index

        for(int num : nums) {
            maxEnding = max(maxEnding + num, num);
            result = max(result, maxEnding);     
        }

        return result;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Divide and Conquer | Dynamic Programming 
Link  : https://leetcode.com/problems/maximum-subarray/description/
