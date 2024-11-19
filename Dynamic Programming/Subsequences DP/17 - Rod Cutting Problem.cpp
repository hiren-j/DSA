// Code to find the maximum value obtainable by cutting up the rod and selling the pieces ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // Method to find the maximum obtainable value, using recursion with memoization - O(N*N) & O(N*N)
    int cutRod(vector<int>& price, int n) {
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, price, n, 1, n);
    }
    
private:
    // O(2*N*N) & O(N*N + rodLength)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& price, int n, int cutLength, int rodLength) {
        // Edge case: If you can cut the whole rod then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;

        // Edge case: If all the lengths are exhausted then you can't cut the rod into more pieces
        if(cutLength - 1 == n)
            return INT_MIN;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[cutLength - 1][rodLength] != -1)
            return memory[cutLength - 1][rodLength];
        
        // There are always two possibilities to perform at each length
        int currSkip = solveWithMemo(memory, price, n, cutLength + 1, rodLength); // Is to skip the rod-cut in the current length and move to the next length
        int currTake = INT_MIN;                                                   // Is to cut the rod in the current length and then stay on the same length 
        
        // If possible then take the length value
        if(cutLength <= rodLength) {
            int nextValue = solveWithMemo(memory, price, n, cutLength, rodLength - cutLength);
            currTake = (nextValue != INT_MIN) ? price[cutLength - 1] + nextValue : INT_MIN;
        }
        
        // Store the result value to the memoization table and then return it
        return memory[cutLength - 1][rodLength] = max(currSkip, currTake);    
    }

    // O(2^rodLength) & O(rodLength)
    int solveWithoutMemo(vector<int>& price, int n, int cutLength, int rodLength) {
        // Edge case: If you can cut the whole rod then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;

        // Edge case: If all the lengths are exhausted then you can't cut the rod into more pieces
        if(cutLength - 1 == n)
            return INT_MIN;

        // There are always two possibilities to perform at each length
        int currSkip = solveWithoutMemo(price, n, cutLength + 1, rodLength); // Is to skip the rod-cut in the current length and move to the next length
        int currTake = INT_MIN;                                              // Is to cut the rod in the current length and then stay on the same length 
        
        // If possible then take the length value
        if(cutLength <= rodLength) {
            int nextValue = solveWithoutMemo(price, n, cutLength, rodLength - cutLength);
            currTake = (nextValue != INT_MIN) ? price[cutLength - 1] + nextValue : INT_MIN;
        }
        
        // As we're striving for the maximum value hence return the maximum one                
        return max(currSkip, currTake);    
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the maximum obtainable value, using recursion with memoization - O(N*N*N) & O(N*N)
    int cutRod(vector<int>& price, int n) {
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, price, n, 1, n);
    }
    
private:
    // O(N*N*N) & O(N*N + rodLength)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& price, int n, int startLength, int rodLength) {
        // Edge case: If you can cut the whole rod then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;

        // Edge case: If all the lengths are exhausted then you can't cut the rod into more pieces
        if(startLength - 1 == n)
            return INT_MIN;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startLength - 1][rodLength] != -1)
            return memory[startLength - 1][rodLength];
        
        // Stores the result value        
        int maxValue = INT_MIN;
        
        // Iterate and if possible then take the length value and update the maximum value each time
        for(int cutLength = startLength; cutLength <= n; ++cutLength) {
            if(cutLength <= rodLength) {
                int nextValue = solveWithMemo(memory, price, n, cutLength, rodLength - cutLength);
                nextValue = (nextValue != INT_MIN) ? price[cutLength - 1] + nextValue : INT_MIN;
                maxValue = max(maxValue, nextValue);
            }    
        }

        // Stores the result value to the memoization table and then return it 
        return memory[startLength - 1][rodLength] = maxValue;    
    }

    // O(N^rodLength) & O(rodLength)
    int solveWithoutMemo(vector<int>& price, int n, int startLength, int rodLength) {
        // Edge case: If you can cut the whole rod then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;
        
        // Stores the result value        
        int maxValue = INT_MIN;
        
        // Iterate and if possible then take the length value and update the maximum value each time
        for(int cutLength = startLength; cutLength <= n; ++cutLength) {
            if(cutLength <= rodLength) {
                int nextValue = solveWithoutMemo(price, n, cutLength, rodLength - cutLength);
                nextValue = (nextValue != INT_MIN) ? price[cutLength - 1] + nextValue : INT_MIN;
                maxValue = max(maxValue, nextValue);
            }    
        }

        // Return the result value
        return maxValue;    
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum obtainable value, using 2D tabulation - O(N*N) & O(N*N)
    int cutRod_V1(vector<int>& price, int n) {
        // 2D DP table
        vector<vector<int>> dp(n + 2, vector<int>(n + 1, INT_MIN));

        // Initialize the first edge case: If you can cut the whole rod then return 0 as a valid indication of it 
        for(int cutLength = 0; cutLength <= n+1; ++cutLength)
            dp[cutLength][0] = 0;

        // Fill the rest of the table
        for(int cutLength = n; cutLength >= 1; --cutLength) {
            for(int rodLength = 1; rodLength <= n; ++rodLength) {
                int currSkip = dp[cutLength + 1][rodLength];
                int currTake = INT_MIN;
                if(cutLength <= rodLength) {
                    int nextValue = dp[cutLength][rodLength - cutLength];
                    currTake = (nextValue != INT_MIN) ? price[cutLength - 1] + nextValue : INT_MIN;
                }
                dp[cutLength][rodLength] = max(currSkip, currTake);    
            } 
        }

        // Return the result value
        return dp[1][n];
    }

    // #2 Method to find the maximum obtainable value, using 1D tabulation - O(N*N) & O(N)
    int cutRod_V2(vector<int>& price, int n) {
        // 1D DP tables
        vector<int> nextRow(n + 1, INT_MIN), idealRow(n + 1, INT_MIN);
        nextRow[0] = 0;

        // Fill the rest of the table
        for(int cutLength = n; cutLength >= 1; --cutLength) {
            idealRow[0] = 0;
            for(int rodLength = 1; rodLength <= n; ++rodLength) {
                int currSkip = nextRow[rodLength];
                int currTake = INT_MIN;
                if(cutLength <= rodLength) {
                    int nextValue = idealRow[rodLength - cutLength];
                    currTake = (nextValue != INT_MIN) ? price[cutLength - 1] + nextValue : INT_MIN;
                }
                idealRow[rodLength] = max(currSkip, currTake);    
            } 
            nextRow = idealRow;
        }

        // Return the result value
        return nextRow[n];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/rod-cutting0840/1
