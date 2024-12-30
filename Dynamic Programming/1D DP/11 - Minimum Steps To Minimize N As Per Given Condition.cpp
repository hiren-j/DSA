// Code to find the minimum steps required to minimize n to 1 according to the following criteria: If n is divisible by 2 then you may reduce n to n/2. If n is divisible by 3 then you may reduce n to n/3. Otherwise, Decrement n by 1 ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: Starting from the 10th problem, you’ll notice a shift in the approach. The bottom-up solutions will now be direct conversions from the memoized ones. 
                            This change aims to reduce time and avoid the need for pen and paper, making the process more efficient. As you work through the bottom-up solutions, switch tabs to view the memoized solution side-by-side. 
                            This will help you see how the values passed as parameters in the memoized solution correspond to what we calculate and store in the bottom-up approach. 
                            With practice, you’ll be able to create bottom-up solutions within minutes or even seconds, as I have developed the habit of doing. 
                            This conversion technique will be applied to the remaining problems across all DP patterns.
*/    
  
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum steps required to reduce n to 1, using recursion with memoization - O(N) & O(N)
    int minStepsToMakeOne(int n) {
	vector<int> dp(n + 1, -1);
	return solveWithMemo(dp, n);
    } 
	
private:
    // O(2*N) & O(N+N)
    int solveWithMemo(vector<int>& dp, int n) {
        // Edge case: If n becomes 1 then no more operations are required
        if(n == 1)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(dp[n] != -1)
            return dp[n];
        
        // Count the total steps required to reduce n to 1 using decreament operation
        int minSteps = solveWithMemo(dp, n - 1); 
        
        // If n is divisible by 2 then you may reduce n to n/2. Make sure to update the result by the minimum value
        if(n % 2 == 0) 
            minSteps = min(minSteps, solveWithMemo(dp, n / 2));
            
        // If n is divisible by 3 then you may reduce n to n/3. Make sure to update the result by the minimum value
        if(n % 3 == 0) 
            minSteps = min(minSteps, solveWithMemo(dp, n / 3));
        
        // Store the result value to the memoization table and then return it
        return dp[n] = 1 + minSteps;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        // Edge case: If n becomes 1 then no more operations are required
        if(n == 1)
            return 0;
        
        // Count the total steps required to reduce n to 1 using decreament operation
        int minSteps = solveWithoutMemo(n - 1); 
        
        // If n is divisible by 2 then reduce n to n/2. Make sure to update the result by the minimum value
        if(n % 2 == 0) 
            minSteps = min(minSteps, solveWithoutMemo(n / 2));

        // If n is divisible by 3 then reduce n to n/3. Make sure to update the result by the minimum value
        if(n % 3 == 0) 
            minSteps = min(minSteps, solveWithoutMemo(n / 3));
        
        // Return the result value
        return 1 + minSteps;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum steps required to reduce n to 1, using 1D tabulation - O(N) & O(N)
    int minStepsToMakeOne(int n) {
        // 1D DP table: dp[i] represents the minimum steps required to reduce 'i' to 1
	vector<int> dp(n + 1, -1);

        // Initialize the edge case
	dp[1] = 0;     

        // Fill the rest of the table
	for(int num = 2; num <= n; ++num) {
            int minSteps = dp[num - 1];
                    
            if(num % 2 == 0) 
                minSteps = min(minSteps, dp[num / 2]);

            if(num % 3 == 0) 
                minSteps = min(minSteps, dp[num / 3]);
            
            dp[num] = 1 + minSteps;
	}

        // Return the result value
	return dp[n];
    } 
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/discuss/interview-question/538568/google-onsite-min-operations-to-reduce-number-to-1
        https://www.geeksforgeeks.org/problems/minimum-steps-to-minimize-n-as-per-given-condition0618/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
