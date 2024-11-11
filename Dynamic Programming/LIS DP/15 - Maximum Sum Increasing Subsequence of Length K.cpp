// Code to find the maximum possible sum of an increasing subsequence of length k. Note that it's not necessary for the subsequence to be strictly increasing ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the maximum sum of an increasing subsequence of length k, using recursion with memoization - O(N^2 * K) & O(N^2 * K)
    int maxSumSubseqLengthK(vector<int>& nums, int k) {
	int n = nums.size();
	vector<vector<vector<int>>> memory(n, vector<vector<int>>(n + 1, vector<int>(k + 1, -1)));
	int maxSum = solveWithMemo(memory, nums, n, 0, -1, k);
	return (maxSum == INT_MIN) ? -1 : maxSum;
    }
	
private:
    // O(2*N*N*K) & O(N*N*K + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& nums, int n, int index, int prevIndex, int k) {
        // Edge case: If you've created an increasing subsequence of length k then no need to pick more elements hence return 0 as a valid indication of it
        if(k == 0)
            return 0;

        // Edge case: At this point if all the elements are exhausted and you can't create such subsequence of length k then return INT_MIN as a indication of it
        if(index == n)
            return INT_MIN;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevIndex + 1][k] != -1)
            return memory[index][prevIndex + 1][k]; 

        // There are always two possibilities to perform at each index value
        int currSkip = solveWithMemo(memory, nums, n, index + 1, prevIndex, k); // Is to skip it
        int currTake = INT_MIN;                                                 // Is to pick it
        
        // If possible then pick the index value
        if(prevIndex == -1 || nums[prevIndex] <= nums[index]) {
            int nextSum = solveWithMemo(memory, nums, n, index + 1, index, k - 1);
            currTake = (nextSum != INT_MIN) ? nums[index] + nextSum : INT_MIN;
        }
        
        // Store the result value to the memoization table and then return it
        return memory[index][prevIndex + 1][k] = max(currSkip, currTake);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int n, int index, int prevIndex, int k) {
        // Edge case: If you've created an increasing subsequence of length k then no need to pick more elements hence return 0 as a valid indication of it
        if(k == 0)
            return 0;

        // Edge case: At this point if all the elements are exhausted and you can't create such subsequence of length k then return INT_MIN as a indication of it
        if(index == n)
            return INT_MIN;

        // There are always two possibilities to perform at each index value
        int currSkip = solveWithoutMemo(nums, n, index + 1, prevIndex, k); // Is to skip it
        int currTake = INT_MIN;                                                 // Is to pick it
        
        // If possible then pick the index value
        if(prevIndex == -1 || nums[prevIndex] <= nums[index]) {
            int nextSum = solveWithoutMemo(nums, n, index + 1, index, k - 1);
            currTake = (nextSum != INT_MIN) ? nums[index] + nextSum : INT_MIN;
        }

        // As we're striving for the maximum possible sum hence return the maximum value 
        return max(currSkip, currTake);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the maximum sum of an increasing subsequence of length k, using recursion with memoization - O(N^3 * K) & O(N^2 * K)
    int maxSumSubseqLengthK(vector<int>& nums, int k) {
	int n = nums.size();
	vector<vector<vector<int>>> memory(n, vector<vector<int>>(n + 1, vector<int>(k + 1, -1)));
	int maxSum = solveWithMemo(memory, nums, n, 0, -1, k);
	return (maxSum == INT_MIN) ? -1 : maxSum;
    }
	
private:
    // O(N*N*N*K) & O(N*N*K + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, vector<int>& nums, int n, int startIndex, int prevIndex, int k) {
        // Edge case: If you've created an increasing subsequence of length k then no need to pick more elements hence return 0 as a valid indication of it
        if(k == 0)
            return 0;

        // Edge case: At this point if all the elements are exhausted and you can't create such subsequence of length k then return INT_MIN as a indication of it
        if(startIndex == n)
            return INT_MIN;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][prevIndex + 1][k] != -1)
            return memory[startIndex][prevIndex + 1][k]; 

        // Stores the result value
        int maxSum = INT_MIN;

        // Iterate and if possible then pick the index value
        for(int index = startIndex; index < n; ++index) 
            if(prevIndex == -1 || nums[prevIndex] <= nums[index]) {
                int nextSum = solveWithMemo(memory, nums, n, index + 1, index, k - 1);
                if(nextSum != INT_MIN) {
                    maxSum = max(maxSum, nums[index] + nextSum);
                }
            }
        
        // Store the result value to the memoization table and then return it
        return memory[startIndex][prevIndex + 1][k] = maxSum;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum sum of an increasing subsequence of length k, using 3D tabulation - O(N^2 * K) & O(N^2 * K)
    int maxSumSubseqLengthK_V1(vector<int>& nums, int k) {
	int n = nums.size();

        // 3D DP table
	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n + 1, vector<int>(k + 1, INT_MIN)));

        // Initialize the first edge case
        for(int index = 0; index <= n; ++index) 
            for(int prevIndex = 0; prevIndex <= n; ++prevIndex)
                dp[index][prevIndex][0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                for(int length = 1; length <= k; ++length) {
                    int currSkip = dp[index + 1][prevIndex + 1][length];
                    int currTake = INT_MIN;
                    if(prevIndex == -1 || nums[prevIndex] <= nums[index]) {
                        int nextSum = dp[index + 1][index + 1][length - 1];
                        currTake = (nextSum != INT_MIN) ? nums[index] + nextSum : INT_MIN;
                    }
                    dp[index][prevIndex + 1][length] = max(currSkip, currTake);
                }
            }
        }

	int maxSum = dp[0][0][k];

        // Return the result value
	return (maxSum == INT_MIN) ? -1 : maxSum;
    }

    // #2 Method to find the maximum sum of an increasing subsequence of length k, using 2D tabulation - O(N^2 * K) & O(N*K)
    int maxSumSubseqLengthK_V2(vector<int>& nums, int k) {
	int n = nums.size();

        // 2D DP tables
        vector<vector<int>> nextRow(n + 1, vector<int>(k + 1, INT_MIN)), idealRow(n + 1, vector<int>(k + 1, INT_MIN));
        
        // Initialize the first edge case
        for(int prevIndex = 0; prevIndex <= n; ++prevIndex) 
            nextRow[prevIndex][0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = n-1; prevIndex >= -1; --prevIndex) {
                idealRow[prevIndex + 1][0] = 0; // Initialize the first edge case
                for(int length = 1; length <= k; ++length) {
                    int currSkip = nextRow[prevIndex + 1][length];
                    int currTake = INT_MIN;
                    if(prevIndex == -1 || nums[prevIndex] <= nums[index]) {
                        int nextSum = nextRow[index + 1][length - 1];
                        currTake = (nextSum != INT_MIN) ? nums[index] + nextSum : INT_MIN;
                    }
                    idealRow[prevIndex + 1][length] = max(currSkip, currTake);
                }
            }
            nextRow = idealRow;
        }

	int maxSum = nextRow[0][k];

        // Return the result value
	return (maxSum == INT_MIN) ? -1 : maxSum;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming  
Link  : https://www.geeksforgeeks.org/problems/maximum-sum-subsequence-of-length-k3053/1?page=6&difficulty%5B%5D=1&category%5B%5D=Dynamic%2520Programming&sortBy=submissions
