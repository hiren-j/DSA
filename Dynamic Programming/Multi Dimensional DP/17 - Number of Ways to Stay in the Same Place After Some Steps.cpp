// Code to find the number of ways such that your pointer is still at index 0 after exactly "steps" steps ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {        
    #define MOD 1000000007

public:
    // Method to find the total number of ways, using recursion with memoization - O(steps * min(arrLen, steps)) & O(steps * min(arrLen, steps))
    int numWays(int steps, int arrLen) {
        arrLen = min(arrLen, steps);
        vector<vector<int>> memory(steps + 1, vector<int>(arrLen, -1));
        return solveWithMemo(memory, steps, arrLen, 0);
    }

private:
    // O(3 * steps * min(arrLen, steps)) & O(steps * min(arrLen, steps) + steps)
    int solveWithMemo(vector<vector<int>>& memory, int steps, int arrLen, int pointer) {
        // Edge case: If the pointer is still at index 0 after exactly "steps" steps then you've one valid way
        if(steps == 0)
            return (pointer == 0);

        // Edge case: If the steps becomes negative or the pointer is placed outside of the array at any time then you've no valid way
        if(pointer < 0 || pointer == arrLen)
            return 0;

        // Memoization memory: If the current state is already computed then return the computed value
        if(memory[steps][pointer] != -1)
            return memory[steps][pointer];

        // There are always three posibilities to perform at each step
        int moveToLeft  = solveWithMemo(memory, steps - 1, arrLen, pointer - 1); // Is to move 1 position to the left  
        int moveToRight = solveWithMemo(memory, steps - 1, arrLen, pointer + 1); // Is to move 1 position to the right 
        int stayAtSame  = solveWithMemo(memory, steps - 1, arrLen, pointer);     // Is to stay at the same place      

        // Store the result value to the memoization memory and then return it
        return memory[steps][pointer] = ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
    }
    
    // O(3^steps) & O(steps)
    int solveWithoutMemo(int steps, int arrLen, int pointer) {
        // Edge case: If the pointer is still at index 0 after exactly "steps" steps then you've one valid way
        if(steps == 0)
            return (pointer == 0);

        // Edge case: If the steps becomes negative or the pointer is placed outside of the array at any time then you've no valid way
        if(pointer < 0 || pointer == arrLen)
            return 0;

        // There are always three posibilities to perform at each step
        int moveToLeft  = solveWithoutMemo(steps - 1, arrLen, pointer - 1); // Is to move 1 position to the left 
        int moveToRight = solveWithoutMemo(steps - 1, arrLen, pointer + 1); // Is to move 1 position to the right
        int stayAtSame  = solveWithoutMemo(steps - 1, arrLen, pointer);     // Is to stay at the same place      

        // Return the result value
        return ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    #define MOD 1000000007

public:
    // #1 Method to find the total number of ways, using 2D tabulation - O(steps * min(arrLen, steps)) & O(steps * min(arrLen, steps))
    int numWays_V1(int steps, int arrLen) {
        // Pointer movements are dependent on both steps and the array length hence it's better to choose the minimum one to fit in the memory        
        arrLen = min(arrLen, steps);

        // 2D DP table
        vector<vector<int>> dp(steps + 1, vector<int>(arrLen + 2, 0));

        // Initialize the first edge case: If the pointer is still at index 0 after exactly "steps" steps then you've one valid way
        dp[0][1] = 1;

        // Fill the rest of the table
        for(int index = 1; index <= steps; ++index) {   
            for(int pointer = 1; pointer <= arrLen; ++pointer) {
                int moveToLeft  = dp[index - 1][pointer - 1]; 
                int moveToRight = dp[index - 1][pointer + 1]; 
                int stayAtSame  = dp[index - 1][pointer];     
                dp[index][pointer] = ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;  
            }
        }

        // Return the result value
        return dp[steps][1];
    }

    // #2 Method to find the total number of ways, using 1D tabulation - O(steps * min(arrLen, steps)) & O(min(arrLen, steps))
    int numWays_V2(int steps, int arrLen) {
        // Pointer movements are dependent on both steps and the array length hence it's better to choose the minimum one to fit in the memory        
        arrLen = min(arrLen, steps);

        // 1D DP tables
        vector<int> prevRow(arrLen + 2, 0), currRow(arrLen + 2, 0);

        // Initialize the first edge case: If the pointer is still at index 0 after exactly "steps" steps then you've one valid way
        prevRow[1] = 1;

        // Fill the rest of the table
        for(int index = 1; index <= steps; ++index) {
            for(int pointer = 1; pointer <= arrLen; ++pointer) {
                int moveToLeft   = prevRow[pointer - 1]; 
                int moveToRight  = prevRow[pointer + 1]; 
                int stayAtSame   = prevRow[pointer];     
                currRow[pointer] = ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;  
            }
            prevRow = currRow;
        }

        // Return the result value
        return prevRow[1];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/description/
