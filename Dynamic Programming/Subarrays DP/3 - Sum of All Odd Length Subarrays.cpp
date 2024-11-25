// Code to find the sum of all odd length subarrays of an array ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int index, bool prevPick, int subarrLen, int subarrSum) {
        // Edge case: If elements are exhausted and previously if you've picked any odd length subarray then return its sum otherwise 0 
        if(index == n)
            return (prevPick && subarrLen % 2 != 0) ? subarrSum : 0;

        if(prevPick) {
            int pickCurrSubarr = solveWithoutMemo(nums, index + 1, true, subarrLen + 1, subarrSum + nums[index]);
            int stopHere = (prevPick && subarrLen % 2 != 0) ? subarrSum : 0;
            return pickCurrSubarr + stopHere;
        }
        else {
            int startNewFromNext = solveWithoutMemo(nums, index + 1, false, subarrLen, subarrSum);
            int startNewFromCurr = solveWithoutMemo(nums, index + 1, true, subarrLen + 1, subarrSum + nums[index]);
            return startNewFromNext + startNewFromCurr;
        }
    }

    // O(2*N*2*N*TS) & O(N*2*N*TS + N)
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, vector<int>& nums, int index, bool prevPick, int subarrLen, int subarrSum) {
        // Edge case: If elements are exhausted and previously if you've picked any odd length subarray then return its sum otherwise 0 
        if(index == n)
            return (prevPick && subarrLen % 2 != 0) ? subarrSum : 0;

        if(dp[index][prevPick][subarrLen][subarrSum] != -1)
            return dp[index][prevPick][subarrLen][subarrSum];

        if(prevPick) {
            int pickCurrSubarr = solveWithMemo(dp, nums, index + 1, true, subarrLen + 1, subarrSum + nums[index]);
            int stopHere = (prevPick && subarrLen % 2 != 0) ? subarrSum : 0;
            return dp[index][prevPick][subarrLen][subarrSum] = pickCurrSubarr + stopHere;
        }
        else {
            int startNewFromNext = solveWithMemo(dp, nums, index + 1, false, subarrLen, subarrSum);
            int startNewFromCurr = solveWithMemo(dp, nums, index + 1, true, subarrLen + 1, subarrSum + nums[index]);
            return dp[index][prevPick][subarrLen][subarrSum] = startNewFromNext + startNewFromCurr;
        }
    }
    // Note: This solution will lead to memory-limit-exceed

public:
    // Method to find the sum of all odd length subarrays, using recursion with memoization - O(N*N*TS) & O(N*N*TS) : Where TS is "totalSum".
    int sumOddLengthSubarrays(vector<int>& nums) {
        n = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(2, vector<vector<int>>(n, vector<int>(totalSum + 1, -1))));
        return solveWithMemo(dp, nums, 0, false, 0, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
public:
    // Method to find the sum of all odd length subarrays, using 4D tabulation - O(N*N*TS) & O(N*N*TS)
    int sumOddLengthSubarrays(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);

        // 4D DP table
        vector<vector<vector<vector<int>>>> dp(n + 1, vector<vector<vector<int>>>(2, vector<vector<int>>(n + 1, vector<int>(totalSum + 1, 0))));
        
        // Initialize the edge case
        for(int subarrLen = 0; subarrLen <= n; ++subarrLen)
            if(subarrLen % 2 != 0)
                for(int subarrSum = 0; subarrSum <= totalSum; ++subarrSum)
                    dp[n][1][subarrLen][subarrSum] = subarrSum;

        // Fill the rest of the table
        for(int idx = n-1; idx >= 0; --idx) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrLen = n-1; subarrLen >= 0; --subarrLen) {
                    for(int subarrSum = totalSum; subarrSum >= 0; --subarrSum) {
                        int newIdx = subarrSum + nums[idx];
                        if(prevPick) {
                            int pickCurrSubarr = (newIdx <= totalSum) ? dp[idx + 1][true][subarrLen + 1][newIdx] : 0;
                            int stopHere = (prevPick && subarrLen % 2 != 0) ? subarrSum : 0;
                            dp[idx][prevPick][subarrLen][subarrSum] = pickCurrSubarr + stopHere;
                        }
                        else {
                            int startNewFromNext = dp[idx + 1][false][subarrLen][subarrSum];
                            int startNewFromCurr = (newIdx <= totalSum) ? dp[idx + 1][true][subarrLen + 1][newIdx] : 0;
                            dp[idx][prevPick][subarrLen][subarrSum] = startNewFromNext + startNewFromCurr;
                        }
                    }
                }
            }
        }

        // Return the result value
        return dp[0][false][0][0];
    }
};
// Note: This solution will lead to memory-limit-exceed

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the sum of all odd length subarrays, using 3D tabulation - O(N*N*TS) & O(N*TS)
    int sumOddLengthSubarrays(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        // 3D DP tables
        vector<vector<vector<int>>> nextRow(2, vector<vector<int>>(n + 1, vector<int>(totalSum + 1, 0)));
        vector<vector<vector<int>>> idealRow(2, vector<vector<int>>(n + 1, vector<int>(totalSum + 1, 0)));

        // Initialize the edge case
        for(int subarrLen = 0; subarrLen <= n; ++subarrLen)
            if(subarrLen % 2 != 0)
                for(int subarrSum = 0; subarrSum <= totalSum; ++subarrSum)
                    nextRow[1][subarrLen][subarrSum] = subarrSum;

        // Fill the rest of the table
        for(int idx = n-1; idx >= 0; --idx) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrLen = n-1; subarrLen >= 0; --subarrLen) {
                    for(int subarrSum = totalSum; subarrSum >= 0; --subarrSum) {
                        int newIdx = subarrSum + nums[idx];
                        if(prevPick) {
                            int pickCurrSubarr = (newIdx <= totalSum) ? nextRow[true][subarrLen + 1][newIdx] : 0;
                            int stopHere = (prevPick && subarrLen % 2 != 0) ? subarrSum : 0;
                            idealRow[prevPick][subarrLen][subarrSum] = pickCurrSubarr + stopHere;
                        }
                        else {
                            int startNewFromNext = nextRow[false][subarrLen][subarrSum];
                            int startNewFromCurr = (newIdx <= totalSum) ? nextRow[true][subarrLen + 1][newIdx] : 0;
                            idealRow[prevPick][subarrLen][subarrSum] = startNewFromNext + startNewFromCurr;
                        }
                    }
                }
            }   
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[false][0][0];
    }
};
// Note: This solution will lead to time-limit-exceed

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BruteForce {
public:
    // Method to find the sum of all odd length subarrays, using brute force approach - O(N*N) & O(1)
    int sumOddLengthSubarrays(vector<int>& nums) {
        int n = nums.size();
        int subarraySum, subarrayLen, result = 0;

        for(int i = 0; i < n; ++i) {
            subarraySum = 0;
            subarrayLen = 0;
            for(int j = i; j < n; ++j) {
                subarraySum += nums[j];
                subarrayLen++;
                if(subarrayLen % 2 != 0) result += subarraySum;
            }
        }

        return result;   
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Math | Prefix Sum
Link  : https://leetcode.com/problems/sum-of-all-odd-length-subarrays/
