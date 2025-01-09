// Code to return true if the array has at least one valid partition. You have to partition the array into one or more contiguous subarrays. We call a partition of the array valid if each of the obtained subarrays satisfies one of the specified conditions ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to check whether the array has at least one valid partition or not, using recursion with memoization - O(N) & O(N)
    bool validPartition(vector<int>& nums) {
        int n = nums.size();
        vector<int> memory(n, -1);
        return solveWithMemo(memory, nums, n, 0);
    }

private:
    // O(3*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int n, int startIndex) {
        // Edge case: If all the elements are exhausted then you've created a valid partition of the array
        if(startIndex == n)
            return true;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];

        int subArrayLength = 1;

        // Iterate and consider the subarrays which satisfies one of the specified conditions. After considering such subarray assume a partition on that index and then move to the next index and do the same thing
        for(int index = startIndex; index < min(startIndex + 3, n); ++index) {
            if(subArrayLength == 2 && isElementsEqual(nums[index], nums[index - 1]) && solveWithMemo(memory, nums, n, index + 1)) {
                return memory[startIndex] = true;
            }
            else if(subArrayLength == 3 
                    && (isElementsEqual(nums[index], nums[index - 1], nums[index - 2]) 
                    || isElementsConsecAndIncreasing(nums[index], nums[index - 1], nums[index - 2])) 
                    && solveWithMemo(memory, nums, n, index + 1)) {
                return memory[startIndex] = true;
            }

            subArrayLength++;
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex] = false;
    }

    // O(3^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int startIndex) {
        // Edge case: If all the elements are exhausted then you've created a valid partition of the array
        if(startIndex == n)
            return true;

        int subArrayLength = 1;

        // Iterate and consider the subarrays which satisfies one of the specified conditions. After considering such subarray assume a partition on that index and then move to the next index and do the same thing
        for(int index = startIndex; index < min(startIndex + 3, n); ++index) {
            if(subArrayLength == 2 && isElementsEqual(nums[index], nums[index - 1]) && solveWithoutMemo(nums, n, index + 1)) {
                return true;
            }
            else if(subArrayLength == 3 
                    && (isElementsEqual(nums[index], nums[index - 1], nums[index - 2]) 
                    || isElementsConsecAndIncreasing(nums[index], nums[index - 1], nums[index - 2])) 
                    && solveWithoutMemo(nums, n, index + 1)) {
                return true;
            }

            subArrayLength++;
        }

        // If reached here then you're not able to create a valid partition hence return false
        return false;
    }

private:
    // O(1) & O(1)
    bool isElementsEqual(int num1, int num2, int num3 = -1) {
        return (num3 == -1 && num1 == num2) || (num1 == num2 && num2 == num3);
    }

    // O(1) & O(1)
    bool isElementsConsecAndIncreasing(int num1, int num2, int num3) {
        return (num1 - num2 == 1 && num2 - num3 == 1);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to check whether the array has at least one valid partition or not, using 1D tabulation - O(N) & O(N) 
    bool validPartition(vector<int>& nums) {
        int n = nums.size();

        // 1D DP table: dp[i] represents whether you can create a valid partition of the array from index i to n-1
        vector<bool> dp(n + 1, false);

        // Initialize the edge case
        dp[n] = true;

        // Fill the rest of the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            int subArrayLength = 1;

            for(int index = startIndex; index < min(startIndex + 3, n); ++index) {
                if(subArrayLength == 2 && isElementsEqual(nums[index], nums[index - 1]) && dp[index + 1]) {
                    dp[startIndex] = true;
                    break;
                }
                else if(subArrayLength == 3 
                        && (isElementsEqual(nums[index], nums[index - 1], nums[index - 2]) 
                        || isElementsConsecAndIncreasing(nums[index], nums[index - 1], nums[index - 2])) 
                        && dp[index + 1]) {
                    dp[startIndex] = true;
                    break;
                }

                subArrayLength++;
            }
        }

        // Return the result value
        return dp[0];
    }

private:
    // O(1) & O(1)
    bool isElementsEqual(int num1, int num2, int num3 = -1) {
        return (num3 == -1 && num1 == num2) || (num1 == num2 && num2 == num3);
    }

    // O(1) & O(1)
    bool isElementsConsecAndIncreasing(int num1, int num2, int num3) {
        return (num1 - num2 == 1 && num2 - num3 == 1);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming 
Link  : https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/description/
