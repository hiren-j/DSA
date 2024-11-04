// Code to find the "rowIndex" row of the Pascal's triangle ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // #1 Method to find the "rowIndex" row of the pascal's triangle, using 2D tabulation - O(rowIndex^2) & O(rowIndex^2) 
    vector<int> getRow_V1(int rowIndex) {
        // Stores the values of the pascal's triangle
        vector<vector<int>> pascalTable;

        // In pascal's triangle suppose you're on the 0th row then it will contain 1 column, if on the 1th row then it will contain 2 columns and so on for the rest of the rows
        for(int row = 0; row <= rowIndex; row++) {
            pascalTable.emplace_back(vector<int>(row + 1, 1));
            for(int col = 1; col < row; col++) {
                pascalTable[row][col] = pascalTable[row - 1][col] + pascalTable[row - 1][col - 1];
            }
        }   

        // Return the result row
        return pascalTable[rowIndex];
    }

    // #2 Method to find the "rowIndex" row of the pascal's triangle, using 1D tabulation - O(rowIndex^2) & O(rowIndex) 
    vector<int> getRow_V2(int rowIndex) {
        vector<int> prevRow;

        // In pascal's triangle suppose you're on the 0th row then it will contain 1 column, if on the 1th row then it will contain 2 columns and so on for the rest of the rows
        for(int row = 0; row <= rowIndex; row++) {
            vector<int> currRow(row + 1, 1);
            for(int col = 1; col < row; col++) {
                currRow[col] = prevRow[col] + prevRow[col - 1];
            }
            prevRow = currRow;
        }   

        // Return the result row
        return prevRow;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/pascals-triangle-ii/
