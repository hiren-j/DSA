// Code to find the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset (A set x is a subset of a set y if all elements of x are also elements of y) ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

DON'T IGNORE MUST READ : This question's top-down solutions can be converted into a loop-based recursive solution. However, due to the extensive lines of code (LOC) involved, I’ve decided not to include the loop-based version here. 
                         If you're up for it, you can try converting it yourself!
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the brute force approach:
class BruteForce_DP {
public:
    // Subclass to implement the Top-down approach:
    class TopDown {
    public:
        // Method to find the size of the largest subset, using recursion with memoization :-
        int findMaxForm(vector<string>& strs, int m, int n) {
            int size = strs.size();
            vector<vector<vector<int>>> memory(size, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
            return solveWithMemo(strs, m, n, 0, size, memory);
        }

    private:
        // O(2*size*m*n * 100) & O(size*m*n + size)
        int solveWithMemo(vector<string>& strs, int m, int n, int index, int size, vector<vector<vector<int>>>& memory) {
            // Base case: If all the strings are exhausted and you've found a subset such that there are at most m 0's and n 1's in it then return 0 as a valid indication of it
            if(index == size) 
                return (m >= 0 && n >= 0) ? 0 : INT_MIN;

            // Base case: If all the strings are exhausted and you still not found a subset which have at most m 0's and n 1's in it then return INT_MIN as a indication
            if(m < 0 || n < 0)
                return INT_MIN;

            // Memoization table: If the current state is already comptued then return the computed value
            if(memory[index][m][n] != -1)
                return memory[index][m][n];

            // There are always two possibilities to perform at each string
            int currSkip = solveWithMemo(strs, m, n, index + 1, size, memory); // Is to skip it
            int currTake = INT_MIN;                                            // Is to consider it

            // Count the total number of 1's and 0's of the string and further complete the consideration process 
            int countOnes = 0, countZeros = 0;
            for(char bit : strs[index]) (bit == '1') ? countOnes++ : countZeros++;   
            int nextLength = solveWithMemo(strs, m - countZeros, n - countOnes, index + 1, size, memory);
            if(nextLength != INT_MIN) currTake = 1 + nextLength;

            // Store the result value to the memoization table and then return it
            return memory[index][m][n] = max(currSkip, currTake);
        }

        // O(2^size * 100) & O(size)
        int solveWithoutMemo(vector<string>& strs, int m, int n, int index, int size) {
            // Base case: If all the strings are exhausted and you've found a subset such that there are at most m 0's and n 1's in it then return 0 as a valid indication of it
            if(index == size) 
                return (m >= 0 && n >= 0) ? 0 : INT_MIN;

            // Base case: If all the strings are exhausted and you still not found a subset which have at most m 0's and n 1's in it then return INT_MIN as a indication
            if(m < 0 || n < 0)
                return INT_MIN;

            // There are always two possibilities to perform at each string
            int currSkip = solveWithoutMemo(strs, m, n, index + 1, size); // Is to skip it
            int currTake = INT_MIN;                                       // Is to consider it      

            // Count the total number of 1's and 0's of the string and further complete the consideration process 
            int countOnes = 0, countZeros = 0;
            for(char bit : strs[index]) (bit == '1') ? countOnes++ : countZeros++;   
            int nextLength = solveWithoutMemo(strs, m - countZeros, n - countOnes, index + 1, size);
            if(nextLength != INT_MIN) currTake = 1 + nextLength;

            // As we're striving for the largest subset hence return the maximum value
            return max(currSkip, currTake);
        }
    };

    // Subclass to implement the Bottom-up approach:
    class BottomUp {
    public:
        // #1 Method to find the size of the largest subset, using 3D tabulation - O(size*m*n * 100) & O(size*m*n)
        int findMaxForm_V1(vector<string>& strs, int m, int n) {
            int size = strs.size();

            // 3D DP table
            vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(m + 2, vector<int>(n + 2, INT_MIN)));

            // Initialize the first base case: If all the strings are exhausted and you've found a subset such that there are at most m 0's and n 1's in it then return 0 as a valid indication of it
            for(int zeros = 0; zeros <= m+1; ++zeros) 
                for(int ones = 0; ones <= n+1; ++ones) 
                    dp[size][zeros][ones] = 0;

            // Fill the rest of the table
            for(int index = size-1; index >= 0; --index) {
                for(int zeros = 0; zeros <= m; ++zeros) {
                    for(int ones = 0; ones <= n; ++ones) {
                        int currSkip = dp[index + 1][zeros][ones];
                        int currTake = INT_MIN, countOnes = 0, countZeros = 0;
    
                        for(char bit : strs[index]) 
                            (bit == '1') ? countOnes++ : countZeros++; 
                        
                        if(zeros - countZeros >= 0 && ones - countOnes >= 0) {
                            int nextLength = dp[index + 1][zeros - countZeros][ones - countOnes];
                            if(nextLength != INT_MIN) currTake = 1 + nextLength;
                        }  
    
                        dp[index][zeros][ones] = max(currSkip, currTake);
                    }
                }
            }

            // Return the result value
            return dp[0][m][n];
        }
    
        // #2 Method to find the size of the largest subset, using 2D tabulation - O(size*m*n * 100) & O(m*n)
        int findMaxForm_V2(vector<string>& strs, int m, int n) {
            int size = strs.size();

            // 2D DP tables
            vector<vector<int>> nextRow(m + 2, vector<int>(n + 2, INT_MIN)), idealRow(m + 2, vector<int>(n + 2, INT_MIN));

            // Initialize the first base case: If all the strings are exhausted and you've found a subset such that there are at most m 0's and n 1's in it then return 0 as a valid indication of it
            for(int zeros = 0; zeros <= m+1; ++zeros) 
                for(int ones = 0; ones <= n+1; ++ones) 
                    nextRow[zeros][ones] = 0;

            // Fill the rest of the table
            for(int index = size-1; index >= 0; --index) {
                for(int zeros = 0; zeros <= m; ++zeros) {
                    for(int ones = 0; ones <= n; ++ones) {
                        int currSkip = nextRow[zeros][ones];
                        int currTake = INT_MIN, countOnes = 0, countZeros = 0;
    
                        for(char bit : strs[index]) 
                            (bit == '1') ? countOnes++ : countZeros++; 
    
                        if(zeros - countZeros >= 0 && ones - countOnes >= 0) {
                            int nextLength = nextRow[zeros - countZeros][ones - countOnes];
                            currTake = (nextLength != INT_MIN ? 1 + nextLength : INT_MIN);
                        }
    
                        idealRow[zeros][ones] = max(currSkip, currTake);
                    }
                }
                nextRow = idealRow;
            }

            // Return the result value
            return idealRow[m][n];
        }
    };
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
// Class to implement the optimized approach:
class Optimized_DP {
public:
    // Subclass to implement the Top-down approach:
    class TopDown {
        vector<pair<int, int>> countZerosOnes; // Stores the count of 0's and 1's of each string of "strs"
        int size;

        // O(2^size) & O(size)
        int solveWithoutMemo(vector<string>& strs, int m, int n, int index) {
            // Base case: If all the strings are exhausted and you've found a subset such that there are at most m 0's and n 1's in it then return 0 as a valid indication of it
            if(index == size) 
                return (m >= 0 && n >= 0) ? 0 : INT_MIN;

            // Base case: If all the strings are exhausted and you still not found a subset which have at most m 0's and n 1's in it then return INT_MIN as a indication
            if(m < 0 || n < 0)
                return INT_MIN;

            // There are always two possibilities to perform at each string
            int currSkip = solveWithoutMemo(strs, m, n, index + 1); // Is to skip it
            int currTake = INT_MIN;                                 // Is to consider it

            // Get the count of total number of 1's and 0's of the string and further complete the consideration process 
            int nextLength = solveWithoutMemo(strs, m - countZerosOnes[index].first, n - countZerosOnes[index].second, index + 1);
            currTake = (nextLength != INT_MIN ? 1 + nextLength : INT_MIN);

            // As we're striving for the largest subset hence return the maximum value
            return max(currSkip, currTake);
        }

        // O(2*size*m*n) & O(size*m*n + size)
        int solveWithMemo(vector<string>& strs, int m, int n, int index, vector<vector<vector<int>>>& memory) {
            // Base case: If all the strings are exhausted and you've found a subset such that there are at most m 0's and n 1's in it then return 0 as a valid indication of it
            if(index == size) 
                return (m >= 0 && n >= 0) ? 0 : INT_MIN;

            // Base case: If all the strings are exhausted and you still not found a subset which have at most m 0's and n 1's in it then return INT_MIN as a indication
            if(m < 0 || n < 0)
                return INT_MIN;

            // Memoization table: If the current state is already computed then return the computed value
            if(memory[index][m][n] != -1)
                return memory[index][m][n];

            // There are always two possibilities to perform at each string
            int currSkip = solveWithMemo(strs, m, n, index + 1, memory); // Is to skip it
            int currTake = INT_MIN;                                      // Is to consider it   

            // Get the count of total number of 1's and 0's of the string and further complete the consideration process 
            int nextLength = solveWithMemo(strs, m - countZerosOnes[index].first, n - countZerosOnes[index].second, index + 1, memory);
            currTake = (nextLength != INT_MIN ? 1 + nextLength : INT_MIN);

            // Stores the result value to the memoization table and then return it
            return memory[index][m][n] = max(currSkip, currTake);
        }

    public:
        // Method to find the size of the largest subset, using recursion with memoization :-
        int findMaxForm(vector<string>& strs, int m, int n) {
            size = strs.size();
            countZerosOnes.resize(size);

            // Iterate and store the count of total number of 0's and 1's of each string
            for(int index = 0; index < size; ++index) {
                int countZeros = 0, countOnes = 0;
                for(char bit : strs[index]) {
                    (bit == '0') ? countZeros++ : countOnes++; 
                }
                countZerosOnes[index] = {countZeros, countOnes};
            }

            // 3D memoization table
            vector<vector<vector<int>>> memory(size, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));

            // Find and return the result value
            return solveWithMemo(strs, m, n, 0, memory);
        }
    };

    // Subclass to implement the Bottom-up approach:
    class BottomUp {
    public:
        // #1 Method to find the size of the largest subset, using 3D tabulation - O(size*m*n) & O(size*m*n)
        int findMaxcForm_V1(vector<string>& strs, int m, int n) {
            int size = strs.size();

            // Stores the count of 0's and 1's of each string of "strs"
            vector<pair<int, int>> countZerosOnes(size);

            // Iterate and store the count of total number of 0's and 1's of each string
            for(int index = 0; index < size; ++index) {
                int countZeros = 0, countOnes = 0;
                for(char bit : strs[index]) {
                    (bit == '0') ? countZeros++ : countOnes++; 
                }
                countZerosOnes[index] = {countZeros, countOnes};
            }

            // 3D DP table
            vector<vector<vector<int>>> dp(size + 1, vector<vector<int>>(m + 2, vector<int>(n + 2, INT_MIN)));
            
            // Initialize the first base case: If all the strings are exhausted and you've found a subset such that there are at most zeros 0's and ones 1's in it then return 0 as a valid indication of it
            for(int zeros = 0; zeros <= m+1; ++zeros)
                for(int ones = 0; ones <= n+1; ++ones)
                    dp[size][zeros][ones] = 0;

            // Fill the rest of the table
            for(int index = size-1; index >= 0; --index) {
                for(int zeros = 0; zeros <= m; ++zeros) {
                    for(int ones = 0; ones <= n; ++ones) {
                        int currSkip = dp[index + 1][zeros][ones];
                        int currTake = INT_MIN;
                        int newRow   = zeros - countZerosOnes[index].first; 
                        int newCol   = ones - countZerosOnes[index].second; 

                        if(newRow >= 0 && newCol >= 0) {
                            int nextLength = dp[index + 1][newRow][newCol];
                            currTake = (nextLength != INT_MIN ? 1 + nextLength : INT_MIN);
                        }

                        dp[index][zeros][ones] = max(currSkip, currTake); 
                    }
                }
            }

            // Return the result value
            return dp[0][m][n];
        }

        // #2 Method to find the size of the largest subset, using 2D tabulation - O(size*m*n) & O(m*n)
        int findMaxForm_V2(vector<string>& strs, int m, int n) {
            int size = strs.size();

            // Stores the count of 0's and 1's of each string of "strs"
            vector<pair<int, int>> countZerosOnes(size);

            // Iterate and store the count of total number of 0's and 1's of each string
            for(int index = 0; index < size; ++index) {
                int countZeros = 0, countOnes = 0;
                for(char bit : strs[index]) {
                    (bit == '0') ? countZeros++ : countOnes++; 
                }
                countZerosOnes[index] = {countZeros, countOnes};
            }

            // 2D DP tables
            vector<vector<int>> nextRow(m + 2, vector<int>(n + 2, INT_MIN)), idealRow(m + 2, vector<int>(n + 2, INT_MIN));

            // Initialize the first base case: If all the strings are exhausted and you've found a subset such that there are at most zeros 0's and ones 1's in it then return 0 as a valid indication of it
            for(int zeros = 0; zeros <= m+1; ++zeros)
                for(int ones = 0; ones <= n+1; ++ones)
                    nextRow[zeros][ones] = 0;

            // Fill the rest of the table
            for(int index = size-1; index >= 0; --index) {
                for(int zeros = 0; zeros <= m; ++zeros) {
                    for(int ones = 0; ones <= n; ++ones) {
                        int currSkip = nextRow[zeros][ones];
                        int currTake = INT_MIN;
                        int newRow   = zeros - countZerosOnes[index].first; 
                        int newCol   = ones - countZerosOnes[index].second; 

                        if(newRow >= 0 && newCol >= 0) {
                            int nextLength = nextRow[newRow][newCol];
                            currTake = (nextLength != INT_MIN ? 1 + nextLength : INT_MIN);
                        }

                        idealRow[zeros][ones] = max(currSkip, currTake); 
                    }
                }
                nextRow = idealRow;
            }

            // Return the result value
            return idealRow[m][n];
        }
    };
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
Topics: Array | String | Dynamic Programming
Link  : https://leetcode.com/problems/ones-and-zeroes/description/
