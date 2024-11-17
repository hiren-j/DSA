// Code to find the maximum sum subsequence of the given array such that the integers in the subsequence are sorted in strictly increasing order (i.e. a strictly increasing subsequence) ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int idx, int prevIdx) {
        if(idx == n)
            return 0;

        int currSkip = solveWithoutMemo(nums, idx + 1, idx);
        int currTake = 0;

        if(prevIdx == -1 || nums[prevIdx] < nums[idx])
            currTake = nums[idx] + solveWithoutMemo(nums, idx + 1, idx);

        return max(currSkip, currTake);
    }

    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int idx, int prevIdx) {
        if(idx == n)
            return 0;

        if(dp[idx][prevIdx + 1] != -1)
            return dp[idx][prevIdx + 1];

        int currSkip = solveWithMemo(dp, nums, idx + 1, idx);
        int currTake = 0;

        if(prevIdx == -1 || nums[prevIdx] < nums[idx])
            currTake = nums[idx] + solveWithMemo(dp, nums, idx + 1, idx);

        return dp[idx][prevIdx + 1] = max(currSkip, currTake);
    }

public:
    // Method to find the maximum sum of any strictly increasing subsequence, using recursion with 2D memoization - O(N^2) & O(N^2)
    int maxSumIncreasingSubseq(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solveWithMemo(dp, nums, 0, -1);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
    int n;

    // O(2*N*N) & O(N+N)
    int solveWithMemo(vector<int>& dp, vector<int>& nums, int idx, int prevIdx) {
        if(idx == n)
            return 0;

        if(dp[prevIdx + 1] != -1)
            return dp[prevIdx + 1];

        int currSkip = solveWithMemo(dp, nums, idx + 1, prevIdx);
        int currTake = 0;

        if(prevIdx == -1 || nums[prevIdx] < nums[idx])
            currTake = nums[idx] + solveWithMemo(dp, nums, idx + 1, idx);

        return dp[prevIdx + 1] = max(currSkip, currTake);
    }

public:
    // Method to find the maximum sum of any strictly increasing subsequence, using recursion with 1D memoization - O(N^2) & O(N)
    int maxSumIncreasingSubseq(vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, nums, 0, -1);
    }
};
// Note: This solution (TopDown_V2) is the space optimized version of the (TopDown_V1) solution

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V3 {
    int n;

    // O(N*N*N) & (N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int startIdx, int prevIdx) {
        if(startIdx == n)
            return 0;

        if(dp[startIdx][prevIdx + 1] != -1)
            return dp[startIdx][prevIdx + 1];

        int maxLength = 0;

        for(int idx = startIdx; idx < n; ++idx)
            if(prevIdx == -1 || nums[prevIdx] < nums[idx])
                maxLength = max(maxLength, nums[idx] + solveWithMemo(dp, nums, idx + 1, idx));

        return dp[startIdx][prevIdx + 1] = maxLength;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code

public:
    // Method to find the maximum sum of any strictly increasing subsequence, using recursion with 2D memoization - O(N^3) & O(N^2)
    int maxSumIncreasingSubseq(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solveWithMemo(dp, nums, 0, -1);
    }
};
// Note: This solution (TopDown_V3) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V3)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // #1 Method to find the maximum sum of any strictly increasing subsequence, using 2D tabulation - O(N^2) & O(N^2)
    int maxSumIncreasingSubseq_V1(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int idx = n-1; idx >= 0; --idx) {
            for(int prevIdx = n-1; prevIdx >= -1; --prevIdx) {
                int currSkip = dp[idx + 1][prevIdx + 1];
                int currTake = 0;
                if(prevIdx == -1 || nums[prevIdx] < nums[idx]) {
                    currTake = nums[idx] + dp[idx + 1][idx + 1];
                }
                dp[idx][prevIdx + 1] = max(currSkip, currTake);
            }
        }

        return dp[0][0];
    }
    // Note: This bottom-up solution is created from the memoized solution of (TopDown_V1)

    // #2 Method to find the maximum sum of any strictly increasing subsequence, using 1D tabulation - O(N^2) & O(N)
    int maxSumIncreasingSubseq_V2(vector<int>& nums) {
        int n = nums.size();

        vector<int> nextRow(n + 1), idealRow(n + 1);

        for(int idx = n-1; idx >= 0; --idx) {
            for(int prevIdx = n-1; prevIdx >= -1; --prevIdx) {
                int currSkip = nextRow[prevIdx + 1];
                int currTake = 0;
                if(prevIdx == -1 || nums[prevIdx] < nums[idx]) {
                    currTake = nums[idx] + nextRow[idx + 1];
                }
                idealRow[prevIdx + 1] = max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        return idealRow[0];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the maximum sum of any strictly increasing subsequence, using 1D tabulation - O(N^2) & O(N)
    int maxSumIncreasingSubseq(vector<int>& nums) {
        int n = nums.size(), maxSum = 0;

        vector<int> dp(n);

        for(int idx = 0; idx < n; ++idx) {
            dp[idx] = nums[idx];
            for(int prevIdx = 0; prevIdx < idx; ++prevIdx) {
                if(nums[prevIdx] < nums[idx]) {
                    dp[idx] = max(dp[idx], dp[prevIdx] + nums[idx]);
                }
            }
            maxSum = max(maxSum, dp[idx]);
        }

        return maxSum;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/maximum-sum-increasing-subsequence4749/1
