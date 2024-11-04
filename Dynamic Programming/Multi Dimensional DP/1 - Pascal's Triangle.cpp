// Code to find the first "numRows" of Pascal's triangle ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the first "numRows" of pascal's triangle, using 2D tabulation - O(numRows^2) & O(numRows^2) 
    vector<vector<int>> generateTable(int numRows) {
        // Stores the values of the pascal's triangle
        vector<vector<int>> pascalTable;

        // In pascal's triangle suppose you're on the 0th row then it will contain 1 column, if on the 1th row then it will contain 2 columns and so on for the rest of the rows
        for(int R = 0; R < numRows; R++) {
            pascalTable.emplace_back(vector<int>(R + 1, 1));
            for(int C = 1; C < R; C++) {
                pascalTable[R][C] = pascalTable[R - 1][C] + pascalTable[R - 1][C - 1];
            }
        }   

        return pascalTable;
    }
};
// Note: The auxiliary space is considered because even if its not the user's demand but still we have to create the pascalTable to get the output

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/pascals-triangle/description/
