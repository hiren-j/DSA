// Code to count the total number of partitions in which S1 is greater than or equal to S2 and the difference between S1 and S2 is equal to D ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int index, int target) {
        if(index == 0) {
            if(target == 0) 
                return (nums[0] == 0) ? 2 : 1;
            else
                return (nums[0] == target);
        }

        if(target < 0)
            return 0;

        if(dp[index][target] != -1)
            return dp[index][target];

        int currSkip = solveWithMemo(dp, nums, index - 1, target);
        int currTake = solveWithMemo(dp, nums, index - 1, target - nums[index]);

        return dp[index][target] = (currSkip + currTake);
    }

public:
    // O(N*TS) & O(N*TS) : Where TS = totalSum
    int findTargetSumWays(vector<int>& nums, int difference) {
        int n = nums.size();
        int resCount = 0;
        int totalSum = accumulate(begin(nums), end(nums), 0);

        vector<vector<int>> dp(n, vector<int>(totalSum + 1, -1));

        for(int subset1Sum = totalSum/2; subset1Sum <= totalSum; ++subset1Sum) {
            int countSubsets = solveWithMemo(dp, nums, n-1, subset1Sum);
            int subset2Sum   = totalSum - subset1Sum;
            if(subset1Sum >= subset2Sum && subset1Sum - subset2Sum == abs(difference)) {
                resCount += countSubsets;
            }
        }

        return resCount;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*TS) & O(N*TS)
    int findTargetSumWays_V1(vector<int>& nums, int difference) {
        int n = nums.size();
        int resCount = 0;
        int totalSum = accumulate(begin(nums), end(nums), 0);

        vector<vector<int>> dp(n, vector<int>(totalSum + 1, 0));
        dp[0][0] = 1;
        if(nums[0] == 0) dp[0][0] = 2;
        else if(nums[0] <= totalSum) dp[0][nums[0]] = 1;

        for(int index = 1; index < n; ++index) {
            for(int target = 0; target <= totalSum; ++target) {
                int currSkip = dp[index - 1][target];
                int currTake = (target - nums[index] >= 0) ? dp[index - 1][target - nums[index]] : 0;
                dp[index][target] = (currSkip + currTake);
            }
        }

        for(int subset1Sum = totalSum/2; subset1Sum <= totalSum; ++subset1Sum) {
            int subset2Sum = totalSum - subset1Sum;
            if(subset1Sum >= subset2Sum && subset1Sum - subset2Sum == abs(difference)) {
                resCount += dp[n-1][subset1Sum];
            }
        }

        return resCount;
    }

    // O(N*TS) & O(TS)
    int findTargetSumWays_V2(vector<int>& nums, int difference) {
        int n = nums.size();
        int resCount = 0;
        int totalSum = accumulate(begin(nums), end(nums), 0);

        vector<int> prevRow(totalSum + 1, 0), idealRow(totalSum + 1, 0);
        prevRow[0] = 1;
        if(nums[0] == 0) prevRow[0] = 2;
        else if(nums[0] <= totalSum) prevRow[nums[0]] = 1;

        for(int index = 1; index < n; ++index) {
            for(int target = 0; target <= totalSum; ++target) {
                int currSkip = prevRow[target];
                int currTake = (target - nums[index] >= 0) ? prevRow[target - nums[index]] : 0;
                idealRow[target] = (currSkip + currTake);
            }
            prevRow = idealRow;
        }

        for(int subset1Sum = totalSum/2; subset1Sum <= totalSum; ++subset1Sum) {
            int subset2Sum = totalSum - subset1Sum;
            if(subset1Sum >= subset2Sum && subset1Sum - subset2Sum == abs(difference)) {
                resCount += prevRow[subset1Sum];
            }
        }

        return resCount;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Backtracking 
Link  : https://leetcode.com/problems/target-sum/description/?envType=list&envId=50vif4uc
