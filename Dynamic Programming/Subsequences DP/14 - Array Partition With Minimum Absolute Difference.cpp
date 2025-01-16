// Code to divide the array into two sets S1 and S2 such that the absolute difference between their sums is as minimum as possible. So, the task is to find the minimum absolute difference ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum absolute difference, using recursion with memoization - O(N*T) & O(N*T) : Where T let be the total sum
    int minSubsetSumDifference(vector<int>& nums, int n) {
	int totalSum = accumulate(begin(nums), end(nums), 0);       
        
        // 2D DP table
	vector<vector<int>> dp(n, vector<int>(totalSum + 1, -1));
    
	// If a single subset exists then the another subset can easily be identified, hence look for the existence of all the possible subsets through their sum value
	for(int subset1Sum = 0; subset1Sum <= totalSum; ++subset1Sum) {
	    solveWithMemo(dp, nums, n, n - 1, subset1Sum);
	}

        // Stores the result value 
	int minAbsDiff = INT_MAX;
    
	// Check the existence of the subsets of the array and if a subset exists then it's a valid partition hence update the result by the minimum value
	for(int subset1Sum = 0; subset1Sum <= totalSum/2; ++subset1Sum) {
	    if(dp[n - 1][subset1Sum] == 1) {
	        int subset2Sum = totalSum - subset1Sum;
	        minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
	    }
	}
    
	// Return the result value
	return minAbsDiff;
    }

private:
    // O(2*N*T) & O(N*T + N)
    bool solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int N, int index, int sum) {
        // Edge case: If the sum becomes zero then there exists a subset with given sum 
        if(sum == 0)
            return dp[index][sum] = true;        
    
	// Edge case: If you're at the 0th index and the value is equal to the sum then there exists a subset with given sum
        if(index == 0)
            return dp[index][sum] = (nums[index] == sum);

	    // Memoization table: If the current state is already computed then return the computed value
        if(dp[index][sum] != -1)
            return dp[index][sum];

	// There are always two possibilties to perform at each index
        bool currSkip = solveWithMemo(dp, nums, N, index - 1, sum); // Is to skip the index value
        bool currTake = false;				            // Is to take the index value	

	// If possible then take the index value
        if(nums[index] <= sum) 
            currTake = solveWithMemo(dp, nums, N, index - 1, sum - nums[index]);

        // Store the result value to the memoization table and then return it
        return dp[index][sum] = (currTake || currSkip);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the minimum absolute difference, using 2D tabulation - O(N*T) & O(N*T)
    int minSubsetSumDifference_V1(vector<int>& nums, int n) {
	int totalSum = accumulate(begin(nums), end(nums), 0);

        // 2D DP table
	vector<vector<bool>> dp(n, vector<bool>(totalSum + 1, false));

        // Initialize the first edge case: If the sum becomes zero then there exists a subset with given sum 
        for(int index = 0; index < n; ++index)
            dp[index][0] = true;        

        // Initialize the second edge case: If you're at the 0th index and the value is equal to the sum then there exists a subset with given sum
        if(nums[0] <= totalSum)
            dp[0][nums[0]] = true;

        // Fill the rest of the table
        for(int index = 1; index < n; ++index) {
            for(int sum = 1; sum <= totalSum; ++sum) {
                bool currSkip = dp[index - 1][sum]; 
                bool currTake = false;				              	
                if(nums[index] <= sum) {
                    currTake = dp[index - 1][sum - nums[index]];
                }
                dp[index][sum] = (currTake || currSkip);
            }
        }

        // Stores the result value 
	int minAbsDiff = INT_MAX;
    
	// Check the existence of the subsets of the array and if a subset exists then it's a valid partition hence update the result by the minimum value
	for(int subset1Sum = 0; subset1Sum <= totalSum/2; ++subset1Sum) {
	    if(dp[n - 1][subset1Sum]) {
	        int subset2Sum = totalSum - subset1Sum;
	        minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
	    }
	}
    
	// Return the result value
	return minAbsDiff;
    }

    // #2 Method to find the minimum absolute difference, using 1D tabulation - O(N*T) & O(T)
    int minSubsetSumDifference_V2(vector<int>& nums, int n) {
	int totalSum = accumulate(begin(nums), end(nums), 0);

        // 1D DP tables
        vector<bool> prevRow(totalSum + 1, false), idealRow(totalSum + 1, false);
        prevRow[0] = true;        

        if(nums[0] <= totalSum)
            prevRow[nums[0]] = true;

        // Fill the rest of the table
        for(int index = 1; index < n; ++index) {
            idealRow[0] = true;
            for(int sum = 1; sum <= totalSum; ++sum) {
                bool currSkip = prevRow[sum]; 
                bool currTake = false;				              	
                if(nums[index] <= sum) {
                    currTake = prevRow[sum - nums[index]];
                }
                idealRow[sum] = (currTake || currSkip);
            }
            prevRow = idealRow;
        }

        // Stores the result value 
	int minAbsDiff = INT_MAX;
    
	// Check the existence of the subsets of the array and if a subset exists then it's a valid partition hence update the result by the minimum value
	for(int subset1Sum = 0; subset1Sum <= totalSum/2; ++subset1Sum) {
	    if(prevRow[subset1Sum]) {
	        int subset2Sum = totalSum - subset1Sum;
	        minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
	    }
	}

	// Return the result value
	return minAbsDiff;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/minimum-sum-partition3317/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
