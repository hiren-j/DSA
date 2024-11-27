// Code to find the sum of minimum element of all the subarrays of an array ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int index, bool prevPick, int subarrMin) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return its minimum element otherwise 0 
        if(index == n)
            return (prevPick) ? subarrMin : 0;

        if(prevPick) {
            int pickCurrSubarr = solveWithoutMemo(nums, index + 1, true, min(subarrMin, nums[index]));
            int stopHere = subarrMin;
            return (pickCurrSubarr + stopHere) % MOD;
        }
        else {
            int startNewFromNext = solveWithoutMemo(nums, index + 1, false, subarrMin);
            int startNewFromCurr = solveWithoutMemo(nums, index + 1, true, min(subarrMin, nums[index]));
            return (startNewFromNext + startNewFromCurr) % MOD;
        }
    }
    // Note: This solution will lead to time-limit-exceed

    // O(2*N*2*M) & O(N*2*M + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, vector<int>& nums, int index, bool prevPick, int subarrMin) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return its minimum element otherwise 0 
        if(index == n)
            return (prevPick) ? subarrMin : 0;

        if(dp[index][prevPick][subarrMin] != -1)
            return dp[index][prevPick][subarrMin];

        if(prevPick) {
            int pickCurrSubarr = solveWithMemo(dp, nums, index + 1, true, min(subarrMin, nums[index]));
            int stopHere = subarrMin;
            return dp[index][prevPick][subarrMin] = (pickCurrSubarr + stopHere) % MOD;
        }
        else {
            int startNewFromNext = solveWithMemo(dp, nums, index + 1, false, subarrMin);
            int startNewFromCurr = solveWithMemo(dp, nums, index + 1, true, min(subarrMin, nums[index]));
            return dp[index][prevPick][subarrMin] = (startNewFromNext + startNewFromCurr) % MOD;
        }
    }
    // Note: This solution will lead to memory-limit-exceed

public:
    // Method to find the sum of minimum element of all the subarrays, using recursion with memoization - O(N*M) & O(N*M) : Where M is "maxElement".
    int sumSubarrayMins(vector<int>& nums) {
        n = nums.size();
        int maxElement = *max_element(begin(nums), end(nums));
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(maxElement + 2, -1)));
        return solveWithMemo(dp, nums, false, 0, maxElement + 1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

public:
    // #1 Method to find the sum of minimum element of all the subarrays, using 3D tabulation - O(N*M) & O(N*M)
    int sumSubarrayMins_V1(vector<int>& nums) {
        int n = nums.size();
        int maxElement = *max_element(begin(nums), end(nums));

        // 3D DP table
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(maxElement + 2, -1)));

        // Initialize the edge case (prevPick ? subarrMin)
        for(int subarrMin = 1; subarrMin <= maxElement+1; ++subarrMin)
            dp[n][1][subarrMin] = subarrMin;

        // Initialize the edge case (prevPick : 0)
        for(int subarrMin = 1; subarrMin <= maxElement+1; ++subarrMin)
            dp[n][0][subarrMin] = 0;
            
        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrMin = 0; subarrMin <= maxElement+1; ++subarrMin) {
                    if(prevPick) {
                        int pickCurrSubarr = dp[index + 1][true][min(subarrMin, nums[index])];
                        int stopHere = subarrMin;
                        dp[index][prevPick][subarrMin] = (pickCurrSubarr + stopHere) % MOD;
                    }
                    else {
                        int startNewFromNext = dp[index + 1][false][subarrMin];
                        int startNewFromCurr = dp[index + 1][true][min(subarrMin, nums[index])];
                        dp[index][prevPick][subarrMin] = (startNewFromNext + startNewFromCurr) % MOD;
                    }
                }
            }
        }

        // Return the result value
        return dp[0][false][maxElement + 1];
    }

    // #2 Method to find the sum of minimum element of all the subarrays, using 2D tabulation - O(N*M) & O(M)
    int sumSubarrayMins_V2(vector<int>& nums) {
        int n = nums.size();
        int maxElement = *max_element(begin(nums), end(nums));

        // 2D DP tables
        vector<vector<int>> nextRow(2, vector<int>(maxElement + 2, -1));
        vector<vector<int>> idealRow(2, vector<int>(maxElement + 2, -1));

        // Initialize the edge case (prevPick ? subarrMin)
        for(int subarrMin = 1; subarrMin <= maxElement+1; ++subarrMin)
            nextRow[1][subarrMin] = subarrMin;

        // Initialize the edge case (prevPick : 0)
        for(int subarrMin = 1; subarrMin <= maxElement+1; ++subarrMin)
            nextRow[0][subarrMin] = 0;
        
        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrMin = 0; subarrMin <= maxElement+1; ++subarrMin) {
                    if(prevPick) {
                        int pickCurrSubarr = nextRow[true][min(subarrMin, nums[index])];
                        int stopHere = subarrMin;
                        idealRow[prevPick][subarrMin] = (pickCurrSubarr + stopHere) % MOD;
                    }
                    else {
                        int startNewFromNext = nextRow[false][subarrMin];
                        int startNewFromCurr = nextRow[true][min(subarrMin, nums[index])];
                        idealRow[prevPick][subarrMin] = (startNewFromNext + startNewFromCurr) % MOD;
                    }
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[false][maxElement + 1];
    }
};
// Note: This solution will lead to time-limit-exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class MonotonicStack {
public:
    int sumSubarrayMins(vector<int>& nums) {}
};
// Note: Will upload this solution soon 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Stack | Monotonic Stack
Link  : https://leetcode.com/problems/sum-of-subarray-minimums/description/
