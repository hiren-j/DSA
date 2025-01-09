// Code to find the count of all `n` digit numbers whose sum of digits is `sum`. Leading 0’s are not counted as digits ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
    REGARDING MY REASONING ON THE LIMIT OF 901 :-
        -> Constraints:
            1 <= n <= 100
            str[i] ∈ {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

        -> In the worst case, the size could be 100 and the maximum digit could be 9.
           Considering this the maximum sum could be 100*9 = 900, 
           Due to 0-based indexing of the array, To fit 900 in the dp array the size must be 901.
*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    // O(N^N) & O(N)
    int solveWithoutMemo(string& str, int startIndex, int prevSum) {
        if(startIndex == n) // Edge case: If no values are left, then you've created one valid grouping
            return 1;  
                    
        int count = 0, currentSum = 0;
        
        for(int index = startIndex; index < n; ++index) {
            currentSum += str[index] - '0';
            if(prevSum <= currentSum) {
                count += solveWithoutMemo(str, index + 1, currentSum);
            }
        }

        return count;
    }

    // O(N*N*901) & O(N*901 + N)
    int solveWithMemo(vector<vector<int>>& dp, string& str, int startIndex, int prevSum) {
        if(startIndex == n) // Edge case: If no values are left, then you've created one valid grouping
            return 1;  
            
        if(dp[startIndex][prevSum] != -1)
            return dp[startIndex][prevSum]; 
        
        int count = 0, currentSum = 0;
        
        for(int index = startIndex; index < n; ++index) {
            currentSum += str[index] - '0';
            if(prevSum <= currentSum) {
                count += solveWithMemo(dp, str, index + 1, currentSum);
            }
        }

        return dp[startIndex][prevSum] = count;
    }
    
public:
    // Method to count total number of valid groupings, using recursion with memoization - O(N*N*901) & O(N*901) 
    int countValidGroupings(string& str) {
	n = str.size();
	vector<vector<int>> dp(n, vector<int>(901, -1));
	return solveWithMemo(dp, str, 0, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to count total number of valid groupings, using 2D tabulation - O(N*N*901) & O(N*901)
    int countValidGroupings(string& str) {
	int n = str.size();
	    
	vector<vector<int>> dp(n + 1, vector<int>(901, 0));
	    
        // Initialize the edge case
	for(int prevSum = 0; prevSum <= 900; ++prevSum)
	    dp[n][prevSum] = 1;
	        
	for(int startIndex = n-1; startIndex >= 0; --startIndex) {
	    for(int prevSum = 900; prevSum >= 0; --prevSum) {
                 int count = 0, currentSum = 0;
        	 for(int index = startIndex; index < n; ++index) {
                     currentSum += str[index] - '0';
                     if(prevSum <= currentSum) {
                         count += dp[index + 1][currentSum];
                     }
		 }
                 dp[startIndex][prevSum] = count;
	    }
	}
	    
	return dp[0][0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming 
Link  : https://www.geeksforgeeks.org/problems/count-digit-groupings-of-a-number1520/1
