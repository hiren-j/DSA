// Code to find the nCr of given two integers ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    
public:
    // #1 Method to find the nCr of given two integers, using 2D tabulation - O(N^2) & O(N^2) 
    int nCr_V1(int N, int R) {
        if(R > N)
            return 0;
        
        // Stores the values of the pascal's triangle
        vector<vector<int>> pascalTable;

        // In pascal's triangle suppose you're on the 0th row then it will contain 1 column, if on the 1th row then it will contain 2 columns and so on for the rest of the rows
        for(int row = 0; row <= N; row++) {
            pascalTable.emplace_back(vector<int>(row + 1, 1));
            for(int col = 1; col < row; col++) {
                pascalTable[row][col] = (pascalTable[row - 1][col] + pascalTable[row - 1][col - 1]) % MOD;
            }
        }   

        // Return the result row
        return pascalTable[N][R] % MOD;
    }

    // #2 Method to find the nCr of given two integers, using 1D tabulation - O(N^2) & O(N) 
    int nCr_V2(int N, int R) {
        if(R > N)
            return 0;
        
        vector<int> prevRow;

        // In pascal's triangle suppose you're on the 0th row then it will contain 1 column, if on the 1th row then it will contain 2 columns and so on for the rest of the rows
        for(int row = 0; row <= N; row++) {
            vector<int> currRow(row + 1, 1);
            for(int col = 1; col < row; col++) {
                currRow[col] = (prevRow[col] + prevRow[col - 1]) % MOD;
            }
            prevRow = currRow;
        }   

        // Return the result row
        return prevRow[R];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/ncr1019/1
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/Multi%20Dimensional%20DP/Pascal's%20Triangle%20II.cpp
