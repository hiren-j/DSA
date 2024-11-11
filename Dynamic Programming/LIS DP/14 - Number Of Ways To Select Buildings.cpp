// Code to find the number of valid ways to select 3 buildings ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
    typedef long long LL;

public:
    // Method to find the number of valid ways to select 3 buildings, using recursion with memoization - O(N) & O(N)
    LL numberOfWays(string& s) {
        int n = s.size();
        vector<vector<vector<LL>>> memory(n, vector<vector<LL>>(3, vector<LL>(4, -1)));
        return solveWithMemo(memory, s, n, 0, '2', 3);
    }

private:
    // O(2*N*3*4) & O(N*3*4 + N)
    LL solveWithMemo(vector<vector<vector<LL>>>& memory, const string& s, int n, int index, char prevBuilding, int k) {
        // Edge case: If you've selected 3 buildings then you've got one valid way
        if(k == 0)
            return 1;

        // Edge case: If all the buildings are exhausted then you've no valid way
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevBuilding - '0'][k] != -1)
            return memory[index][prevBuilding - '0'][k];

        // There are always two possibilities to perform at each building
        LL currSkip   = solveWithMemo(memory, s, n, index + 1, prevBuilding, k); // Is to skip it
        LL currSelect = 0;                                                       // Is to select it 

        // If the previous and current building is not same then select the current building
        if(prevBuilding == '2' || prevBuilding != s[index])
            currSelect = solveWithMemo(memory, s, n, index + 1, s[index], k - 1);

        // Store the result value to the memoization table and then return it
        return memory[index][prevBuilding - '0'][k] = (currSkip + currSelect);
    }

    // O(2^N) & O(N)
    LL solveWithoutMemo(const string& s, int n, int index, char prevBuilding, int k) {
        // Edge case: If you've selected 3 buildings then you've got one valid way
        if(k == 0)
            return 1;

        // Edge case: If all the buildings are exhausted then you've no valid way
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each building
        LL currSkip   = solveWithoutMemo(s, n, index + 1, prevBuilding, k); // Is to skip it
        LL currSelect = 0;                                                  // Is to select it

        // If the previous and current building is not same then select the current building
        if(prevBuilding == '2' || prevBuilding != s[index])
            currSelect = solveWithoutMemo(s, n, index + 1, s[index], k - 1);

        // Return the result value
        return (currSkip + currSelect);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
    typedef long long LL;

public:
    // Method to find the number of valid ways to select 3 buildings, using recursion with memoization - O(N*N) & O(N)
    LL numberOfWays(string& s) {
        int n = s.size();
        vector<vector<vector<LL>>> memory(n, vector<vector<LL>>(3, vector<LL>(4, -1)));
        return solveWithMemo(memory, s, n, 0, '2', 3);
    }

private:
    // O(N*N*3*4) & O(N*3*4 + N)
    LL solveWithMemo(vector<vector<vector<LL>>>& memory, const string& s, int n, int startIndex, char prevBuilding, int k) {
        // Edge case: If you've selected 3 buildings then you've got one valid way
        if(k == 0)
            return 1;

        // Edge case: If all the buildings are exhausted then you've no valid way
        if(startIndex == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex][prevBuilding - '0'][k] != -1)
            return memory[startIndex][prevBuilding - '0'][k];

        // Stores the result value
        LL count = 0;

        // Iterate and if the previous and index building is not same then select the index building
        for(int index = startIndex; index < n; ++index)
            if(prevBuilding == '2' || prevBuilding != s[index])
                count += solveWithMemo(memory, s, n, index + 1, s[index], k - 1);

        // Store the result value to the memoization table and then return it
        return memory[startIndex][prevBuilding - '0'][k] = count;
    }
    // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2). It will lead to time-limit-exceed

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long LL;

public:
    // #1 Method to find the number of valid ways to select 3 buildings, using 3D tabulation - O(N*3*3) & O(N*3*4)
    LL numberOfWays_V1(const string& s) {
        int n = s.size();

        // 3D DP table
        vector<vector<vector<LL>>> dp(n + 1, vector<vector<LL>>(3, vector<LL>(4, 0)));

        // Initialize the first edge case: If you've selected 3 buildings then you've got one valid way
        for(int index = 0; index <= n; ++index)
            for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding)
                dp[index][prevBuilding - '0'][0] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding) {
                for(int k = 1; k <= 3; ++k) {
                    LL currSkip   = dp[index + 1][prevBuilding - '0'][k];
                    LL currSelect = 0;
                    if(prevBuilding == '2' || prevBuilding != s[index]) {
                        currSelect = dp[index + 1][s[index] - '0'][k - 1];
                    }
                    dp[index][prevBuilding - '0'][k] = (currSkip + currSelect);
                }
            }
        }

        // Return the result value
        return dp[0]['2' - '0'][3];
    }

    // #2 Method to find the number of valid ways to select 3 buildings, using 2D tabulation - O(N*3*3) & O(2*3*4)
    LL numberOfWays_V2(const string& s) {
        int n = s.size();

        // 2D DP tables
        vector<vector<LL>> nextRow(3, vector<LL>(4, 0)), idealRow(3, vector<LL>(4, 0));

        // Initialize the edge case: If you've selected 3 buildings then you've got one valid way
        for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding)
            nextRow[prevBuilding - '0'][0] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding) {
                idealRow[prevBuilding - '0'][0] = 1;
                for(int k = 1; k <= 3; ++k) {
                    LL currSkip   = nextRow[prevBuilding - '0'][k];
                    LL currSelect = 0;
                    if(prevBuilding == '2' || prevBuilding != s[index]) {
                        currSelect = nextRow[s[index] - '0'][k - 1];
                    }
                    idealRow[prevBuilding - '0'][k] = (currSkip + currSelect);
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow['2' - '0'][3];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming | Prefix Sum
Link  : https://leetcode.com/problems/number-of-ways-to-select-buildings/description/
