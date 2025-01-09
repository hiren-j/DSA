// Code to partition the array into (contiguous) subarrays of length at most K. After partitioning, each subarray has their values changed to become the maximum value of that subarray. The aim is to find the largest sum of the given array after partitioning ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the largest sum of the array after partitioning, using recursion with memoization - O(N*K) & O(N)
    int maxSumAfterPartitioning(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> memory(n, -1);
        return solveWithMemo(memory, nums, k, n, 0);
    }

private:
    // O(K*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int k, int n, int startIndex) {
        // Edge case: If all the elements are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];

        int maximumSum = 0; // Stores the result value
        int maxElement = 0; // Stores the maximum element of an individual partition

        // Perform all the K partitions and choose the partition with the maximum sum
        for(int index = startIndex; index < min(startIndex + k, n); ++index) {
            maxElement       = max(maxElement, nums[index]);
            int partitionSum = ((index - startIndex + 1) * maxElement) + solveWithMemo(memory, nums, k, n, index + 1);
            maximumSum       = max(maximumSum, partitionSum);
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex] = maximumSum;
    }

    // O(K^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int k, int n, int startIndex) {
        // Edge case: If all the elements are exhausted then you can't do more partitions
        if(startIndex == n)
            return 0;

        int maximumSum = 0; // Stores the result value
        int maxElement = 0; // Stores the maximum element of an individual partition

        // Perform all the K partitions and choose the partition with the maximum sum
        for(int index = startIndex; index < min(startIndex + k, n); ++index) {
            maxElement       = max(maxElement, nums[index]);
            int partitionSum = ((index - startIndex + 1) * maxElement) + solveWithoutMemo(nums, k, n, index + 1);
            maximumSum       = max(maximumSum, partitionSum);
        }

        // As we're striving for the largest sum hence return the maximum sum
        return maximumSum;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the largest sum of the array after partitioning, using 1D tabulation - O(N*K) & O(N)
    int maxSumAfterPartitioning(vector<int>& nums, int k) {
        int n = nums.size();

        // 1D DP table
        vector<int> dp(n + 1, 0);

        // Fill the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            int maximumSum = 0, maxElement = 0;

            for(int index = startIndex; index < min(startIndex + k, n); ++index) {
                maxElement       = max(maxElement, nums[index]);
                int partitionSum = ((index - startIndex + 1) * maxElement) + dp[index + 1];
                maximumSum       = max(maximumSum, partitionSum);
            }
            
            dp[startIndex] = maximumSum;
        }

        // Return the result value
        return dp[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/partition-array-for-maximum-sum/description/
