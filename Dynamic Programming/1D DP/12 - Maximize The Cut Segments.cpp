// Code to find the maximum number of cut segments possible. Given an integer n denoting the Length of a line segment. You need to cut the line segment in such a way that the cut length of a line segment each time is either x , y or z. Here x, y, and z are integers. After performing all the cut operations, your total number of cut segments must be maximum ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
public:
    // Method to find the maximum number of cut segments, using recursion with memoization - O(N) & O(N)
    int maximizeTheCuts(int n, int x, int y, int z) {
        vector<int> memory(n + 1, -1);
        int maxCutSegments = solveWithMemo(memory, n, x, y, z);
        return (maxCutSegments == INT_MIN) ? 0 : maxCutSegments;
    }
    
private:
    // O(3*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, int n, int x, int y, int z) {
        // Edge case: If you've cut the whole line segment then return 0 as a valid indication of it
        if(n == 0)
            return 0;

        // Edge case: If you've can't cut the whole line segment then return INT_MIN as an indication of it
        if(n < 0)
            return INT_MIN;

        // Memoization table: If the current state is already computed then return the computed value  
        if(memory[n] != -1)
            return memory[n];

        // There are always three cut operations to perform on each length 
        int cutFromX = solveWithMemo(memory, n - x, x, y, z); // Is to cut it in length x
        int cutFromY = solveWithMemo(memory, n - y, x, y, z); // Is to cut it in length y
        int cutFromZ = solveWithMemo(memory, n - z, x, y, z); // Is to cut it in length z
        
        // As we're striving for the maximimum cut segments hence store the maximum one
        int maxCuts = max({cutFromX, cutFromY, cutFromZ});
                
        // Store the result value to the memoization table and then return it
        return memory[n] = (maxCuts != INT_MIN) ? maxCuts + 1 : INT_MIN;
    }

    // O(3^N) & O(N)
    int solveWithoutMemo(int n, int x, int y, int z) {
        // Edge case: If you've cut the whole line segment then return 0 as a valid indication of it
        if(n == 0)
            return 0;

        // Edge case: If you've can't cut the whole line segment then return INT_MIN as an indication of it
        if(n < 0)
            return INT_MIN;

        // There are always three cut operations to perform on each length 
        int cutFromX = solveWithoutMemo(n - x, x, y, z); // Is to cut it in length x
        int cutFromY = solveWithoutMemo(n - y, x, y, z); // Is to cut it in length y
        int cutFromZ = solveWithoutMemo(n - z, x, y, z); // Is to cut it in length z
        
        // As we're striving for the maximum cut segments hence store the maximum one
        int maxCuts = max({cutFromX, cutFromY, cutFromZ});

        // Return the result value 
        return (maxCuts != INT_MIN) ? maxCuts + 1 : INT_MIN;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the maximum number of cut segments, using 1D tabulation - O(N) & O(N)
    int maximizeTheCuts(int n, int x, int y, int z) {
        // 1D DP table: dp[i] represents the maximum cuts required to cut the whole line segment from index 0 to i
        vector<int> dp(n + 1, INT_MIN);

        // Initialize the first edge case
        dp[0] = 0;
        
        // Fill the rest of the table
        for(int length = 1; length <= n; ++length) {
            int cutFromX = (length - x >= 0) ? dp[length - x] : INT_MIN;
            int cutFromY = (length - y >= 0) ? dp[length - y] : INT_MIN;
            int cutFromZ = (length - z >= 0) ? dp[length - z] : INT_MIN;
            int maxCuts  = max({cutFromX, cutFromY, cutFromZ});    
            dp[length]   = (maxCuts != INT_MIN) ? maxCuts + 1 : INT_MIN;
        }
        
        int maxCutSegments = dp[n];
        
        // Return the result value
        return (maxCutSegments == INT_MIN) ? 0 : maxCutSegments;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/cutted-segments1642/1   
