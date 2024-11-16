// Code to find the maximum total value you can collect for the knapsack, you cannot break an item, either pick the complete item or dont pick it (0-1 property) ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown_V1 {
public:
    // Method to find the maximum total value you can collect for the knapsack, using recursion with memoization - O(N*C) & O(N*C) : Where C let be the capacity
    int knapSack(int capacity, vector<int>& weights, vector<int>& values, int n) {
        vector<vector<int>> memory(n, vector<int>(capacity + 1, -1));
        return solveWithMemo(memory, weights, values, n, 0, capacity);
    }
    
private:
    // O(2*N*C) & O(N*C + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& weights, vector<int>& values, int n, int index, int capacity) {
        // Edge case: If all the values are exhausted or if the capacity becomes zero then you can't fill any more value to the knapsack
        if(index == n || capacity == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][capacity] != -1)
            return memory[index][capacity];
        
        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, weights, values, n, index + 1, capacity); // Is to skip the index value
        int currTake = 0;                                                              // Is to take the index value
        
        // If possible then take the index value
        if(capacity - weights[index] >= 0)
            currTake = values[index] + solveWithMemo(memory, weights, values, n, index + 1, capacity - weights[index]);

        // Store the result value to the memoization table and then return it
        return memory[index][capacity] = max(currTake, currSkip);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& weights, vector<int>& values, int n, int index, int capacity) {
        // Edge case: If all the values are exhausted or if the capacity becomes zero then you can't fill any more value to the knapsack
        if(index == n || capacity == 0)
            return 0;
            
        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(weights, values, n, index + 1, capacity); // Is to skip the index value
        int currTake = 0;                                                         // Is to take the index value
        
        // If possible then take the index value
        if(capacity - weights[index] >= 0)
            currTake = values[index] + solveWithoutMemo(weights, values, n, index + 1, capacity - weights[index]);

        // As we're striving for the maximum value hence return the maximum one 
        return max(currTake, currSkip);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // Method to find the maximum total value you can collect for the knapsack, using recursion with memoization - O(N*N*C) & O(N*C)
    int knapSack(int capacity, vector<int>& weights, vector<int>& values, int n) {
        vector<vector<int>> memory(n, vector<int>(capacity + 1, -1));
        return solveWithMemo(memory, weights, values, n, 0, capacity);
    }
    
private:
    // O(N*N*C) & O(N*C + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& weights, vector<int>& values, int n, int startIndex, int capacity) {        
        // Edge case: If all the values are exhausted or if the capacity becomes zero then you can't fill any more value to the knapsack
        if(startIndex == n || capacity == 0)
            return 0;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][capacity] != -1)
            return memory[startIndex][capacity];

        // Stores the result value 
        int maxValue = 0;
        
        // Iterate and if possible then take the index value and update the result by the maximum value 
        for(int index = startIndex; index < n; ++index) 
            if(capacity - weights[index] >= 0) 
                maxValue = max(maxValue, values[index] + solveWithMemo(memory, weights, values, n, index + 1, capacity - weights[index]));
            
        // Store the result value to the memoization table and then return it
        return memory[startIndex][capacity] = maxValue;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& weights, vector<int>& values, int n, int startIndex, int capacity) {
        // Edge case: If all the values are exhausted or if the capacity becomes zero then you can't fill any more value to the knapsack
        if(startIndex == n || capacity == 0)
            return 0;

        // Stores the result value 
        int maxValue = 0;
            
        // Iterate and if possible then take the index value and update the result by the maximum value 
        for(int index = startIndex; index < n; ++index)
            if(capacity - weights[index] >= 0) 
                maxValue = max(maxValue, values[index] + solveWithoutMemo(weights, values, n, index + 1, capacity - weights[index]));
            
        // Return the result value
        return maxValue;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the maximum total value you can collect for the knapsack, using 2D tabulation - O(N*C) & O(N*C)
    int knapSack_V1(int capacity, vector<int>& weights, vector<int>& values, int n) {
        vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int currCapacity = 1; currCapacity <= capacity; ++currCapacity) {
                int currSkip = dp[index + 1][currCapacity]; 
                int currTake = 0;
                if(currCapacity - weights[index] >= 0) {
                    currTake = values[index] + dp[index + 1][currCapacity - weights[index]];
                }
                dp[index][currCapacity] = max(currTake, currSkip);
            }
        }

        return dp[0][capacity];
    }

    // #2 Method to find the maximum total value you can collect for the knapsack, using 1D tabulation - O(N*C) & O(C)
    int knapSack_V2(int capacity, vector<int>& weights, vector<int>& values, int n) {
        vector<int> nextRow(capacity + 1, 0), idealRow(capacity + 1, 0);

        for(int index = n-1; index >= 0; --index) {
            for(int currCapacity = 1; currCapacity <= capacity; ++currCapacity) {
                int currSkip = nextRow[currCapacity]; 
                int currTake = 0;
                if(currCapacity - weights[index] >= 0) {
                    currTake = values[index] + nextRow[currCapacity - weights[index]];
                }
                idealRow[currCapacity] = max(currTake, currSkip);
            }
            nextRow = idealRow;
        }

        return idealRow[capacity];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1
