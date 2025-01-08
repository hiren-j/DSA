// Code to determine if you can partition the array into two subsets such that the sum of the elements in both the subsets is equal ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    bool solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int index, int sum) {
        if(sum == 0)
            return true;
            
        if(sum < 0 || index == n)
            return false;
            
        if(dp[index][sum] != -1)
            return dp[index][sum];
            
        bool currSkip = solveWithMemo(dp, nums, index + 1, sum);
        bool currTake = solveWithMemo(dp, nums, index + 1, sum - nums[index]);
        
        return dp[index][sum] = (currSkip || currTake); 
    }
    
public:
    // O(N*TS) & O(N*TS) : Where TS = totalSum
    bool canPartition(vector<int>& nums) {
        n = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        vector<vector<int>> dp(n, vector<int>(totalSum + 1, -1));
        
        for(int subset1Sum = 1; subset1Sum <= totalSum; ++subset1Sum) {
            bool isSubsetExist = solveWithMemo(dp, nums, 0, subset1Sum);
            if(!isSubsetExist) continue;
            int subset2Sum = totalSum - subset1Sum;
            if(subset1Sum == subset2Sum) return true;
        }
    
        return false;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*TS) & O(N*TS)
    bool canPartition_V1(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        vector<vector<bool>> dp(n + 1, vector<bool>(totalSum + 1, false));
        
        for(int index = 0; index <= n; ++index)
            dp[index][0] = true;
            
        for(int index = n-1; index >= 0; --index) {
            for(int sum = 1; sum <= totalSum; ++sum) {
                bool currSkip = dp[index + 1][sum];
                bool currTake = (sum - nums[index] >= 0) ? dp[index + 1][sum - nums[index]] : false;
                dp[index][sum] = (currSkip || currTake); 
            }
        }
        
        for(int subset1Sum = totalSum/2; subset1Sum <= totalSum; ++subset1Sum) {
            bool isSubsetExist = dp[0][subset1Sum];
            if(!isSubsetExist) continue;
            int subset2Sum = totalSum - subset1Sum;
            if(subset1Sum == subset2Sum) return true;
        }
    
        return false;
    }

    // O(N*TS) & O(TS)
    bool canPartition_V2(vector<int>& nums) {
        int n = nums.size();
        int totalSum = accumulate(begin(nums), end(nums), 0);
        
        vector<bool> nextRow(totalSum + 1, false);
        nextRow[0] = true;
            
        for(int index = n-1; index >= 0; --index) {
            vector<bool> idealRow(totalSum + 1, false);
            idealRow[0] = true;
            for(int sum = 1; sum <= totalSum; ++sum) {
                bool currSkip = nextRow[sum];
                bool currTake = (sum - nums[index] >= 0) ? nextRow[sum - nums[index]] : false;
                idealRow[sum] = (currSkip || currTake); 
            }
            nextRow = idealRow;
        }
        
        for(int subset1Sum = totalSum/2; subset1Sum <= totalSum; ++subset1Sum) {
            bool isSubsetExist = nextRow[subset1Sum];
            if(!isSubsetExist) continue;
            int subset2Sum = totalSum - subset1Sum;
            if(subset1Sum == subset2Sum) return true;
        }
    
        return false;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/partition-equal-subset-sum/description/
