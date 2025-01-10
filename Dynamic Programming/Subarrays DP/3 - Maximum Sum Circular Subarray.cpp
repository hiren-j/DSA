// Code to find the maximum possible sum of a non-empty subarray of the given circular array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N) 
    int solveWithoutMemo(vector<int>& nums, int index, bool prevPick, bool findMaxSum) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return 0 otherwise if you've to find maximum sum subarray the return INT_MIN or if you've to find minimum sum subarray then return INT_MAX
        if(index == n)
            return (prevPick) ? 0 : (findMaxSum ? INT_MIN : INT_MAX);

        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithoutMemo(nums, index + 1, true, findMaxSum);
            int stopHere = 0;
            return (findMaxSum ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere));
        }
        else {
            int startNewFromNext = solveWithoutMemo(nums, index + 1, false, findMaxSum);
            int startNewFromCurr = nums[index] + solveWithoutMemo(nums, index + 1, true, findMaxSum);
            return (findMaxSum ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr));
        }
    }

    // O(2*N*2) & O(N*2 + N) 
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int index, bool prevPick, bool findMaxSum) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return 0 otherwise if you've to find maximum sum subarray the return INT_MIN or if you've to find minimum sum subarray then return INT_MAX
        if(index == n)
            return (prevPick) ? 0 : (findMaxSum ? INT_MIN : INT_MAX);

        if(dp[index][prevPick] != -1)
            return dp[index][prevPick];

        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithMemo(dp, nums, index + 1, true, findMaxSum);
            int stopHere = 0;
            return dp[index][prevPick] = (findMaxSum ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere));
        }
        else {
            int startNewFromNext = solveWithMemo(dp, nums, index + 1, false, findMaxSum);
            int startNewFromCurr = nums[index] + solveWithMemo(dp, nums, index + 1, true, findMaxSum);
            return dp[index][prevPick] = (findMaxSum ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr));
        }
    }

public:
    // Method to find the maximum sum of any subarray, using recursion with memoization - O(N) & O(N)
    int maxSubarraySumCircular(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp1(n, vector<int>(2, -1));
        int maxSum = solveWithMemo(dp1, nums, 0, false, true);
        if(maxSum <= 0) return maxSum; // If all the numbers are negative or 0 then return the maximum sum you've got
        vector<vector<int>> dp2(n, vector<int>(2, -1)); 
        int minSum   = solveWithMemo(dp2, nums, 0, false, false);
        int totalSum = accumulate(begin(nums), end(nums), 0);
        return max(maxSum, totalSum - minSum);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*2) & O(N*2)
    int solveUsing2DTable(vector<int>& nums, bool findMaxSum) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][1] = 0;
        dp[n][0] = (findMaxSum ? INT_MIN : INT_MAX);

        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + dp[index + 1][true];
                    int stopHere = 0;
                    dp[index][prevPick] = (findMaxSum ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere));
                }
                else {
                    int startNewFromNext = dp[index + 1][false];
                    int startNewFromCurr = nums[index] + dp[index + 1][true];
                    dp[index][prevPick] = (findMaxSum ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr));
                }
            }
        }

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveUsing1DTable(vector<int>& nums, bool findMaxSum) {
        vector<int> nextRow(2, -1), idealRow(2, -1);
        nextRow[1] = 0;
        nextRow[0] = (findMaxSum ? INT_MIN : INT_MAX);

        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + nextRow[true];
                    int stopHere = 0;
                    idealRow[prevPick] = (findMaxSum ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere));
                }
                else {
                    int startNewFromNext = nextRow[false];
                    int startNewFromCurr = nums[index] + nextRow[true];
                    idealRow[prevPick] = (findMaxSum ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr));
                }
            }
            nextRow = idealRow;
        }

        return nextRow[false];
    }

    // O(N*2) & O(1)
    int solveInPlace(vector<int>& nums, bool findMaxSum) {
        int nextRow_1 = 0;
        int nextRow_0 = (findMaxSum ? INT_MIN : INT_MAX);

        for(int index = n-1; index >= 0; --index) {
            int idealRow_1 = -1;
            int idealRow_0 = -1;
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + nextRow_1;
                    int stopHere = 0;
                    idealRow_1 = (findMaxSum ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere));
                }
                else {
                    int startNewFromNext = nextRow_0;
                    int startNewFromCurr = nums[index] + nextRow_1;
                    idealRow_0 = (findMaxSum ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr));
                }
            }
            nextRow_1 = idealRow_1;
            nextRow_0 = idealRow_0;
        }

        return nextRow_0;
    }

public:
    // Method to find the maximum sum of any subarray, using tabulation :-
    int maxSubarraySumCircular(vector<int>& nums) {
        n = nums.size();
        int maxSum = solveInPlace(nums, true);
        if(maxSum <= 0) return maxSum; // If all the numbers are negative or 0 then return the maximum sum you've got
        int minSum   = solveInPlace(nums, false);
        int totalSum = accumulate(begin(nums), end(nums), 0);
        return max(maxSum, totalSum - minSum);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class KadaneAlgorithm {
public:
    // Method to find the maximum sum of any subarray - O(N) & O(1)
    int maxSubarraySumCircular(vector<int>& nums) {
        int totalSum = 0;
        int maxSum = INT_MIN, maxEnding = 0; // Tracks maximum sum of a subarray among all the subarrays ending at an index
        int minSum = INT_MAX, minEnding = 0; // Tracks minimum sum of a subarray among all the subarrays ending at an index

        // Note: If you're on a index then you've two possibilities on it: 
        // 1. To start a new subarray from it
        // 2. Pick the index element as a part of the "maximum sum subarray/minimum sum subarray" seen till its previous index

        for(int num : nums) {
            totalSum += num;

            // Calculate maximum subarray sum (Kadane's algorithm for maximum sum subarray)
            maxEnding = max(maxEnding + num, num);
            maxSum    = max(maxSum, maxEnding);

            // Calculate minimum subarray sum (Kadane's algorithm for minimum sum subarray)
            minEnding = min(minEnding + num, num);
            minSum    = min(minSum, minEnding);
        }

        // If all the numbers are negative or 0 then return the maximum sum you've got
        if(maxSum <= 0) return maxSum;
        
        return max(maxSum, totalSum - minSum);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Divide and Conquer | Dynamic Programming | Queue | Monotonic Queue
Link  : https://leetcode.com/problems/maximum-sum-circular-subarray/description/
