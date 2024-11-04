// Code to find the length of the longest square streak in an array. A subsequence of an array is called a square streak if: The length of the subsequence is at least 2, and after sorting the subsequence, each element (except the first element) is the square of the previous number ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
    typedef long long LL;
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int index, int prevIndex) {
        if(index == n)
            return 0;

        int currSkip = solveWithoutMemo(nums, index + 1, prevIndex);
        int currTake = 0;

        if(prevIndex == -1 || (LL)nums[prevIndex] * (LL)nums[prevIndex] == nums[index])
            currTake = 1 + solveWithoutMemo(nums, index + 1, index);

        return max(currSkip, currTake);
    }

    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int index, int prevIndex) {
        if(index == n)
            return 0;

        if(dp[index][prevIndex + 1] != -1)
            return dp[index][prevIndex + 1];

        int currSkip = solveWithMemo(dp, nums, index + 1, prevIndex);
        int currTake = 0;

        if(prevIndex == -1 || (LL)nums[prevIndex] * (LL)nums[prevIndex] == nums[index])
            currTake = 1 + solveWithMemo(dp, nums, index + 1, index);

        return dp[index][prevIndex + 1] = max(currSkip, currTake);
    }

public:
    // Method to find the length of the longest square streak, using recursion with 2D memoization - O(N^2) & O(N^2)
    int longestSquareStreak(vector<int>& nums) {
        n = nums.size();
        sort(begin(nums), end(nums));
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        int maxLength = solveWithMemo(dp, nums, 0, -1);
        return (maxLength < 2) ? -1 : maxLength;
    }
};
// Note: This solution will lead to memory limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class TopDown_V2 {
    typedef long long LL;
    int n;

    // O(2*N*N) & O(N+N)
    int solveWithMemo(vector<int>& dp, vector<int>& nums, int index, int prevIndex) {
        if(index == n)
            return 0;

        if(dp[prevIndex + 1] != -1)
            return dp[prevIndex + 1];

        int currSkip = solveWithMemo(dp, nums, index + 1, prevIndex);
        int currTake = 0;

        if(prevIndex == -1 || (LL)nums[prevIndex] * (LL)nums[prevIndex] == nums[index])
            currTake = 1 + solveWithMemo(dp, nums, index + 1, index);

        return dp[prevIndex + 1] = max(currSkip, currTake);
    }

public:
    // Method to find the length of the longest square streak, using recursion with 1D memoization - O(N^2) & O(N)
    int longestSquareStreak(vector<int>& nums) {
        n = nums.size();
        sort(begin(nums), end(nums));
        vector<int> dp(n + 1, -1);
        int maxLength = solveWithMemo(dp, nums, 0, -1);
        return (maxLength < 2) ? -1 : maxLength;
    }
};
// Note: This solution (TopDown_V2) is the space optimized version of the (TopDown_V1) solution. It will lead to time limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V3 {
    typedef long long LL;
    int n;

    // O(N*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int startIndex, int prevIndex) {
        if(startIndex == n)
            return 0;

        if(dp[startIndex][prevIndex + 1] != -1)
            return dp[startIndex][prevIndex + 1];

        int maxLength = 0;

        for(int index = startIndex; index < n; ++index)
            if(prevIndex == -1 || (LL)nums[prevIndex] * (LL)nums[prevIndex] == nums[index])
                maxLength = max(maxLength, 1 + solveWithMemo(dp, nums, index + 1, index));

        return dp[startIndex][prevIndex + 1] = maxLength;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code

public:
    // Method to find the length of the longest square streak, using recursion with 2D memoization - O(N^3) & O(N)
    int longestSquareStreak(vector<int>& nums) {
        n = nums.size();
        sort(begin(nums), end(nums));
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        int maxLength = solveWithMemo(dp, nums, 0, -1);
        return (maxLength < 2) ? -1 : maxLength;
    }
};
// Note: This solution (TopDown_V3) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V3). It will lead to memory limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V1 {
    typedef long long LL;

public:
    // #1 Method to find the length of the longest square streak, using 2D tabulation - O(N^2) & O(N^2)
    int longestSquareStreak_V1(vector<int>& nums) {
        int n = nums.size();
        sort(begin(nums), end(nums));

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = dp[index + 1][prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || (LL)nums[prevIndex] * (LL)nums[prevIndex] == nums[index]) {
                    currTake = 1 + dp[index + 1][index + 1];
                }
                dp[index][prevIndex + 1] = max(currSkip, currTake);
            }
        }

        int maxLength = dp[0][0];

        return (maxLength < 2) ? -1 : maxLength;
    }
    // Note: This bottom-up solution is created from the memoized solution of (TopDown_V1). It will give memory limit exceed

    // #2 Method to find the length of the longest square streak, using 1D tabulation - O(N^2) & O(N)
    int longestSquareStreak_V1(vector<int>& nums) {
        int n = nums.size();
        sort(begin(nums), end(nums));

        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = nextRow[prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || (LL)nums[prevIndex] * (LL)nums[prevIndex] == nums[index]) {
                    currTake = 1 + nextRow[index + 1];
                }
                idealRow[prevIndex + 1] = max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        int maxLength = idealRow[0];

        return (maxLength < 2) ? -1 : maxLength;
    }
    // Note: This solution will lead to time limit exceed
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
    typedef long long LL;

public:
    // Method to find the length of the longest square streak, using 1D tabulation - O(N^2) & O(N)
    int longestSquareStreak(vector<int>& nums) {
        int n = nums.size(), maxLength = 0;
        sort(begin(nums), end(nums));

        vector<int> dp(n, 1);

        for(int index = 0; index < n; ++index) {
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if((LL)nums[prevIndex] * (LL)nums[prevIndex] == nums[index]) {
                    dp[index] = max(dp[index], dp[prevIndex] + 1);
                } 
            }
            maxLength = max(maxLength, dp[index]);
        } 

        return (maxLength < 2) ? -1 : maxLength;
    }
};
// Note: This solution will lead to time limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V3 {
public:
    // Method to find the length of the longest square streak, using 1D tabulation - O(NLogN + N*sqrt(num)) & O(N)
    int longestSquareStreak(vector<int>& nums) {
        sort(begin(nums), end(nums));

        unordered_map<int, int> dp;
        int maxLength = 0;

        for(int num : nums) {
            int prevVal = sqrt(num);

            if(prevVal * prevVal == num && dp.count(prevVal)) 
                dp[num] = dp[prevVal] + 1;
            else 
                dp[num] = 1;
            
            maxLength = max(maxLength, dp[num]);
        }

        return (maxLength < 2) ? -1 : maxLength;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | Binary Search | Dynamic Programming | Sorting
Link  : https://leetcode.com/problems/longest-square-streak-in-an-array/description/
