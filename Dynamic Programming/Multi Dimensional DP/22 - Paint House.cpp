// Code to find the minimum cost of painting all the houses such that no adjacent houses are painted with the same color ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum cost, using recursion with memoization - O(N) & O(N)
    int minCostToPaintHouse(vector<vector<int>>& cost) {
	int n = cost.size();
	vector<vector<int>> memory(n, vector<int>(4, -1));
	return solveWithMemo(memory, cost, n, 0, 3);
    }

private:
    // O(2*N*4) & O(N*4 + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& cost, int n, int house, int prevColor) {
	// Edge case: If all the houses are exhausted then there's no more house to paint
	if(house == n)
	    return 0;
    
	// Memoization table: If the current state is already computed then return the computed value 
	if(memory[house][prevColor] != -1)
	    return memory[house][prevColor];

	// Stores the result value
	int minCost = INT_MAX;
    
	// Explore the colors and if the previous house is not painted with the current color then paint the current house with it
	for(int color = 0; color < 3; ++color) 
	    if(color != prevColor) 
	    	minCost = min(minCost, cost[house][color] + solveWithMemo(memory, cost, n, house + 1, color));
                
	// Store the result value to the memoization table and then return it
	return memory[house][prevColor] = minCost;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& cost, int n, int house, int prevColor) {
	// Edge case: If all the houses are exhausted then there's no more house to paint
	if(house == n)
	    return 0;

	// Stores the result value
	int minCost = INT_MAX;
    
	// Explore the colors and if the previous house is not painted with the current color then paint the current house with it
	for(int color = 0; color < 3; ++color) 
	    if(color != prevColor) 
	    	minCost = min(minCost, cost[house][color] + solveWithoutMemo(cost, n, house + 1, color));

        // Return the result value
	return minCost;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the minimum cost, using 2D tabulation - O(N*4*3) & O(N*4)
    int minCostToPaintHouse_V1(vector<vector<int>>& cost) {
	int n = cost.size();

	// 2D DP table
	vector<vector<int>> dp(n + 1, vector<int>(4, INT_MAX));

	// Initialize the edge case: If all the houses are exhausted then there's no more house to paint
        for(int color = 0; color < 3; ++color) 
            dp[n][color] = 0;

	// Fill the rest of the table
        for(int house = n-1; house >= 0; --house) {
            for(int prevColor = 0; prevColor < 4; ++prevColor) {
	        int minCost = INT_MAX;
	        for(int color = 0; color < 3; ++color) {
	            if(color != prevColor) {
	            	minCost = min(minCost, cost[house][color] + dp[house + 1][color]);
		    }
                }
		dp[house][prevColor] = minCost;
	    }   
        }

	// Return the result value
	return dp[0][3];
    }

    // #2 Method to find the minimum cost, using 1D tabulation - O(N*4*3) & O(2*4)
    int minCostToPaintHouse_V2(vector<vector<int>>& cost) {
	int n = cost.size();

	// 1D DP tables
        vector<int> nextRow(4, INT_MAX), currRow(4, INT_MAX);

	// Initialize the edge case: If all the houses are exhausted then there's no more house to paint
        for(int color = 0; color < 3; ++color) 
            nextRow[color] = 0;

	// Fill the rest of the table
        for(int house = n-1; house >= 0; --house) {
            for(int prevColor = 0; prevColor < 4; ++prevColor) {
	        int minCost = INT_MAX;
	        for(int color = 0; color < 3; ++color) {
	            if(color != prevColor) {
	            	minCost = min(minCost, cost[house][color] + nextRow[color]);
                    }
                }
		currRow[prevColor] = minCost;
            }   
            nextRow = currRow;
	}

	// Return the result value
	return nextRow[3];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.naukri.com/code360/problems/paint-house_1460385
	https://leetcode.com/problems/paint-house/description/
