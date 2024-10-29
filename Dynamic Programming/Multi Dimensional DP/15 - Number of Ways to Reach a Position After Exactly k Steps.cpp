// Code to find the number of different ways to reach the position "endPos" starting from "startPos", such that you perform exactly k steps. Initially, you are standing at position "startPos" on an infinite number line. With one step, you can move either one position to the left, or one position to the right. Note that the number line includes negative integers ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DON'T IGNORE MUST READ: As you work on this problem, you'll notice that there isn't a bottom-up solution provided. 
                        This is one of the two problems in the multi-dimensional folder where I couldn't get the bottom-up approach to pass all the test cases. 
                        The issue wasn't with time limits but with incorrect results. So, I've only included the top-down (memoized) solution for this problem. 
                        There are only two problems in the entire DP series without bottom-up solutions. These three lies in this folder.
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ (REGARDING THE INTUITION BEHIND THE LINE): int offset = (startPos - k) + k*2 + 1

    -> Range of Points
        With startPos = 1 and k = 5, you can move to points from:
            Furthest Left Point: 1 - 5 = -4
            Furthest Right Point: 1 + 5 = 6
        So, the range of points you need to handle is from -4 to 6.

    -> Handling Negative Points
        To map these points into an array:
        Calculate Offset: int offset = (startPos - k) + k*2 + 1

        Explanation:
            (startPos - k): Determines the furthest left point, which could be negative.

            + k*2 = (k+k):
                    First k: Moves negative points into positive index space.
                    Second k: Ensures there’s enough space for already existing positive points as well, this excludes the positive indeces of negative points.

            + 1: Adds space for the initial value of k itself.

        Example Calculation:
            (startPos - k): 1 - 5 = -4
            Offset: (-4) + (5*2) + 1 = -4 + 10 + 1 = 7

        Convert Points:
            Add the offset to any point to get a valid array index.
            For point -4: -4 + 7 = 3
            For point 6: 6 + 7 = 13

    -> This approach ensures that the array has space for both negative and positive points, including the value of k itself. This way, you can use an array without dealing with negative indices.
*/

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

    // O(2^k) & O(k)
    int solveWithoutMemo(int k, int startPos, int endPos) {
        // Edge case: If you reached the end position in exactly k steps then you've one valid way
        if(k == 0)
            return startPos == endPos;

        // Edge case: If the total steps are less such that you can never reach the end position then you've no way
        if(k < endPos - startPos)
            return 0;
            
        // There are always to possibilities to perform at each step
        int moveLeft  = solveWithoutMemo(k - 1, startPos - 1, endPos) % MOD; // Is to move one position to left
        int moveRight = solveWithoutMemo(k - 1, startPos + 1, endPos) % MOD; // Is to move one position to right

        // Return the result value
        return (moveLeft + moveRight) % MOD;
    }

    // O(2*k*offset) & O(k*offset + k)
    int solveWithMemo(vector<vector<int>>& memory, int k, int startPos, int endPos) {
        // Edge case: If you reached the end position in exactly k steps then you've one valid way
        if(k == 0)
            return startPos == endPos;

        // Edge case: If the total steps are less such that you can never reach the end position then you've no way
        if(k < endPos - startPos)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[k][startPos + k] != -1)
            return memory[k][startPos + k];

        // There are always to possibilities to perform at each step
        int moveLeft  = solveWithMemo(memory, k - 1, startPos - 1, endPos) % MOD; // Is to move one position to left
        int moveRight = solveWithMemo(memory, k - 1, startPos + 1, endPos) % MOD; // Is to move one position to right

        // Store the result value to the memoization table and then return it
        return memory[k][startPos + k] = (moveLeft + moveRight) % MOD;
    }

public:
    // Method to find the number of different ways, using recursion with memoization - O(k * offset) & O(k * offset)
    int numberOfWays(int startPos, int endPos, int k) {
        int offset = (startPos - k) + k*2 + 1;
        vector<vector<int>> memory(k + 1, vector<int>(offset, -1));
        return solveWithMemo(memory, k, startPos, endPos);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Combinatorics
Link  : https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/description/
