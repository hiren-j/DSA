// Code to find the length of the longest strictly increasing subsequence ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the length of the longest strictly increasing subsequence, using recursion with 2D memoization - O(N*N) & O(N*N)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, nums, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't take any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevIndex + 1] != -1)
            return memory[index][prevIndex + 1];

        // There are always two possibilities to perform at each index 
        int currSkip = solveWithMemo(memory, nums, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                    // Is to take the index value

        // If the previous value is lesser than the current value then take the current value
        if(prevIndex == -1 || nums[index] > nums[prevIndex])
            currTake = 1 + solveWithMemo(memory, nums, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[index][prevIndex + 1] = max(currSkip, currTake);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't take any more
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each index 
        int currSkip = solveWithoutMemo(nums, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                               // Is to take the index value

        // If the previous value is lesser than the current value then take the current value
        if(prevIndex == -1 || nums[index] > nums[prevIndex])
            currTake = 1 + solveWithoutMemo(nums, n, index + 1, index);

        // As we're striving for the longest length hence return the maximum value
        return max(currSkip, currTake);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the length of the longest strictly increasing subsequence, using recursion with 1D memoization - O(N*N) & O(N)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, nums, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int n, int index, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't take any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[prevIndex + 1] != -1)
            return memory[prevIndex + 1];

        // There are always two possibilities to perform at each index 
        int currSkip = solveWithMemo(memory, nums, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                    // Is to take the index value

        // There are always two possibilities to perform at each index 
        if(prevIndex == -1 || nums[index] > nums[prevIndex])
            currTake = 1 + solveWithMemo(memory, nums, n, index + 1, index);

        // Store the result value to the memoizationt table and then return it
        return memory[prevIndex + 1] = max(currSkip, currTake);
    }
};
// Note: This solution (TopDown_V2) is the space optimized version of the (TopDown_V1) solution

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #3 Class to implement the Top-down approach:
class TopDown_V3 {
public:
    // Method to find the length of the longest strictly increasing subsequence, using recursion with 2D memoization - O(N^3) & O(N^2)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, nums, n, 0, -1);
    }

private:
    // O(N*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int n, int startIndex, int prevIndex) {
        // Edge case: If all the values are exhausted then you can't take any more
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][prevIndex + 1] != -1)
            return memory[startIndex][prevIndex + 1];

        // Stores the result value 
        int maxLength = 0;

        // Iterate and if the previous value is lesser than the index value then take the index value
        for(int index = startIndex; index < n; ++index) 
            if(prevIndex == -1 || nums[index] > nums[prevIndex]) 
                maxLength = max(maxLength, 1 + solveWithMemo(memory, nums, n, index + 1, index));

        // Store the result value to the memoization table and then return it
        return memory[startIndex][prevIndex + 1] = maxLength;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code
};
// Note: This solution (TopDown_V3) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V3)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #1 Class to implement the Bottom-up approach:
class BottomUp_V1 {
public:
    // #1 Method to find the length of the longest strictly increasing subsequence, using 2D tabulation - O(N*N) & O(N*N)
    int lengthOfLIS_V1(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> dp(n + 1, vector<int>(n + 2, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = dp[index + 1][prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || nums[index] > nums[prevIndex]) {
                    currTake = 1 + dp[index + 1][index + 1];
                }
                dp[index][prevIndex + 1] = max(currSkip, currTake);
            }
        }

        return dp[0][0];
    }
    // Note: This bottom-up solution is created from the memoized solution of (TopDown_V1)

    // #2 Method to find the length of the longest strictly increasing subsequence, using 1D tabulation - O(N*N) & O(N)
    int lengthOfLIS_V2(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> nextRow(n + 2), idealRow(n + 2);

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                int currSkip = nextRow[prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || nums[index] > nums[prevIndex]) {
                    currTake = 1 + nextRow[index + 1];
                }
                idealRow[prevIndex + 1] = max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        return idealRow[0];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Bottom-up approach:
class BottomUp_V2 {
public:
    // Method to find the length of the longest strictly increasing subsequence, using 1D tabulation - O(N*N) & O(N)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), maxLength = 0;
        
        // 1D table: dp[index] represents the length of the LIS ending at the individual index
        vector<int> dp(n, 1);

        // Fill the table
        for(int index = 0; index < n; ++index) {
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(nums[index] > nums[prevIndex]) {
                    dp[index] = max(dp[index], dp[prevIndex] + 1);
                }
            }
            maxLength = max(maxLength, dp[index]);
        }

        // Return the length of the LIS
        return maxLength;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// #3 Class to implement the Bottom-up approach:
class BottomUp_V3 {
public:
    // Method to find the length of the longest strictly increasing subsequence, using binary search - O(NLogN) & O(N)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();

        // This array doesn't necessarily store the values of the LIS in the correct order. This is due to updates made during the binary search. However, it will correctly provide the length of the actual LIS
        vector<int> LIS; 
        LIS.push_back(nums[0]);

        for(int num : nums) {
            // If the last element of the "LIS" array is lesser than the current element of the "nums" array then push the current element to the "LIS" array
            if(LIS.back() < num) {
                LIS.push_back(num);
            }
            // Else then find the index of the just greater element of the current element and then replace the value lying in the "LIS" array by the current element
            else {
                int i  = lower_bound(begin(LIS), end(LIS), num) - begin(LIS);
                LIS[i] = num;
            }
        }

        // Return the length of the LIS
        return LIS.size();
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming
Links : https://leetcode.com/problems/longest-increasing-subsequence/description/
        https://cses.fi/problemset/task/1145
