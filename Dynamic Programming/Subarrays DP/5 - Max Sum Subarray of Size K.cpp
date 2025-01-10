// Code to find the maximum sum of a subarray among all the subarrays of size k ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N) 
    int solveWithoutMemo(vector<int>& nums, int index, int k, bool prevPick) {
        // Edge case: Previously if you've picked any subarray of size k then return 0 as an indication of it 
        if(prevPick && k == 0)
            return 0;
            
        // Edge case: At this point, It's not possible to pick a k length subarray hence return INT_MIN as an indication of it 
        if(k < 0 || index == n)
            return INT_MIN;
                        
        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithoutMemo(nums, index + 1, k - 1, true);
            int stopHere = (k == 0) ? 0 : INT_MIN;
            return max(pickCurrSubarr, stopHere);
        }
        else {
            int startNewFromNext = solveWithoutMemo(nums, index + 1, k, false);
            int startNewFromCurr = nums[index] + solveWithoutMemo(nums, index + 1, k - 1, true);
            return max(startNewFromNext, startNewFromCurr);
        }
    }

    // O(2*N*K*2) & O(N*K*2 + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, vector<int>& nums, int index, int k, bool prevPick) {
        // Edge case: Previously if you've picked any subarray of size k then return 0 as an indication of it 
        if(prevPick && k == 0)
            return 0;
            
        // Edge case: At this point, It's not possible to pick a k length subarray hence return INT_MIN as an indication of it 
        if(k < 0 || index == n)
            return INT_MIN;
            
        if(dp[index][k][prevPick] != -1)
            return dp[index][k][prevPick];
            
        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithMemo(dp, nums, index + 1, k - 1, true);
            int stopHere = (k == 0) ? 0 : INT_MIN;
            return dp[index][k][prevPick] = max(pickCurrSubarr, stopHere);
        }
        else {
            int startNewFromNext = solveWithMemo(dp, nums, index + 1, k, false);
            int startNewFromCurr = nums[index] + solveWithMemo(dp, nums, index + 1, k - 1, true);
            return dp[index][k][prevPick] = max(startNewFromNext, startNewFromCurr);
        }
    }
    
public:
    // Method to find the maximum sum of a subarray of size k, using recursion with memoization - O(N*K) & O(N*K)
    int maximumSumSubarray(vector<int>& nums, int k) {
        n = nums.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, -1)));
        return solveWithMemo(dp, nums, 0, k, false);
    }
};
// Note: This solution will lead to time limit exceed

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum sum of a subarray of size k, using 3D tabulation - O(N*K) & O(N*K)
    int maximumSumSubarray_V1(vector<int>& nums, int k) {
        int n = nums.size();
        
        // 3D DP table
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(k + 1, vector<int>(2, INT_MIN)));
        
        // Initialize the first edge case
        for(int index = 0; index <= n; ++index)
            dp[index][0][1] = 0;
        
        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int len = 0; len <= k; ++len) {
                for(int prevPick = 1; prevPick >= 0; --prevPick) {
                    if(prevPick) {
                        int pickCurrSubarr = (len-1 >= 0) ? nums[index] + dp[index + 1][len - 1][true] : INT_MIN;
                        int stopHere = (len == 0) ? 0 : INT_MIN;
                        dp[index][len][prevPick] = max(pickCurrSubarr, stopHere);
                    }
                    else {
                        int startNewFromNext = dp[index + 1][len][false];
                        int startNewFromCurr = (len-1 >= 0) ? nums[index] + dp[index + 1][len - 1][true] : INT_MIN;
                        dp[index][len][prevPick] = max(startNewFromNext, startNewFromCurr);
                    }
                }
            }
        }
        
        // Return the result value
        return dp[0][k][false];
    }

    // #2 Method to find the maximum sum of a subarray of size k, using 2D tabulation - O(N*K) & O(K)
    int maximumSumSubarray_V2(vector<int>& nums, int k) {
        int n = nums.size();
        
        // 2D DP tables
        vector<vector<int>> nextRow(k + 1, vector<int>(2, INT_MIN));
        vector<vector<int>> idealRow(k + 1, vector<int>(2, INT_MIN));

        // Initialize the first edge case
        nextRow[0][1] = 0;
        
        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            idealRow[0][1] = 0; // Initialize the first edge case
            for(int len = 0; len <= k; ++len) {
                for(int prevPick = 1; prevPick >= 0; --prevPick) {
                    if(prevPick) {
                        int pickCurrSubarr = (len-1 >= 0) ? nums[index] + nextRow[len - 1][true] : INT_MIN;
                        int stopHere = (len == 0) ? 0 : INT_MIN;
                        idealRow[len][prevPick] = max(pickCurrSubarr, stopHere);
                    }
                    else {
                        int startNewFromNext = nextRow[len][false];
                        int startNewFromCurr = (len-1 >= 0) ? nums[index] + nextRow[len - 1][true] : INT_MIN;
                        idealRow[len][prevPick] = max(startNewFromNext, startNewFromCurr);
                    }
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[k][false];
    }
};
// Note: This solution will lead to time limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BruteForce {
public:
    // Method to find the maximum sum of a subarray of size k, using brute force approach - O(N*K) & O(1)
    int maximumSumSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        int windowSum, maxSum = 0;
        
        for(int i = 0; i <= n-k; ++i) {
            windowSum = 0;
            for(int j = i; j < i+k; ++j) {
                windowSum += nums[j];
            }
            maxSum = max(maxSum, windowSum);
        }
        
        return maxSum;
    }
};
// Note: This approach is taking less than 10^6 iterations in the worst case and that's the reason its getting accepted, else it's not possible. However still looking at the majors we must consider the time complexity to be O(N*K)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class SlidingWindow {
public:
    // Method to find the maximum sum of a subarray of size k, using sliding window technique - O(N*K) & O(1)
    int maximumSumSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        int i = 0, j = 0;
        int windowSum = 0, maxSum = 0;
        
        while(j < n) {
            windowSum += nums[j];
            // If the window size is equal to k then update the result and shrink the window from left
            if(j-i+1 == k) { 
                maxSum = max(maxSum, windowSum);
                windowSum -= nums[i]; 
                i++;
            }
            j++;
        }
        
        return maxSum;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Sliding Window
Link  : https://www.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1
