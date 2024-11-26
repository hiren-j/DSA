// Code to find the maximum points the geek can earn by performing the aforementioned activites ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public: 
    // Method to find the maximum points the geek can earn, using recursion with memoization - O(N) & O(N)
    int maximumPoints(vector<vector<int>>& points, int n) {
        vector<vector<int>> memory(n, vector<int>(4, -1));
        return solveWithMemo(memory, points, n, 0, -1);
    }
    
private:
    // O(2*N*4) & O(N*4 + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& points, int n, int day, int skipActivity) {
        // Edge case: If all the days are exhausted then it's not possible to perform more activities
        if(day == n)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[day][skipActivity + 1] != -1)
            return memory[day][skipActivity + 1]; 
        
        // Stores the result value
        int maxPoints = 0;
        
        // Perform each activity once and update the maximum points the geek can earn
        for(int activity = 0; activity < 3; ++activity) {
            if(activity != skipActivity) {
                int nextPoints = solveWithMemo(memory, points, n, day + 1, activity);
                maxPoints = max(maxPoints, nextPoints + points[day][activity]);
            }
        }
        
        // Store the result value to the memoization table and then return it
        return memory[day][skipActivity + 1] = maxPoints;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& points, int n, int day, int skipActivity) {
        // Edge case: If all the days are exhausted then it's not possible to perform more activities
        if(day == n)
            return 0;
                
        // Stores the result value
        int maxPoints = 0;
        
        // Perform each activity once and update the maximum points the geek can earn
        for(int activity = 0; activity < 3; ++activity) {
            if(activity != skipActivity) {
                int nextPoints = solveWithoutMemo(points, n, day + 1, activity);
                maxPoints = max(maxPoints, nextPoints + points[day][activity]);
            }
        }
                
        // Return the result value
        return maxPoints;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp_V1 {
public: 
    // #1 Method to find the maximum points the geek can earn, using 2D tabulation - O(N*5*3) & O(N*5)
    int maximumPoints_V1(vector<vector<int>>& points, int n) {
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(5, 0));

        // Fill the rest of the table
        for(int day = n-1; day >= 0; --day) {
            for(int skipActivity = 3; skipActivity >= -1; --skipActivity) {
                int maxPoints = 0;
                for(int activity = 0; activity < 3; ++activity) {
                    if(activity != skipActivity) {
                        int nextPoints = dp[day + 1][activity + 1];
                        maxPoints = max(maxPoints, nextPoints + points[day][activity]);
                    }
                }
                dp[day][skipActivity + 1] = maxPoints;
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the maximum points the geek can earn, using 1D tabulation - O(N*5*3) & O(2*5)
    int maximumPoints_V2(vector<vector<int>>& points, int n) {
        // 1D DP tables
        vector<int> nextRow(5, 0), currRow(5, 0);

        // Fill the rest of the table
        for(int day = n-1; day >= 0; --day) {
            for(int skipActivity = 3; skipActivity >= -1; --skipActivity) {
                int maxPoints = 0;
                for(int activity = 0; activity < 3; ++activity) {
                    if(activity != skipActivity) {
                        int nextPoints = nextRow[activity + 1];
                        maxPoints = max(maxPoints, nextPoints + points[day][activity]);
                    }
                }
                currRow[skipActivity + 1] = maxPoints;
            }
            nextRow = currRow;
        }

        // Return the result value
        return currRow[0];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the maximum points the geek can earn, using constant auxiliary space - O(N*3) & O(1)
    int maximumPoints(vector<vector<int>>& points, int n) {
        // Suppose you're on a cell so to earn the maximum points the only cell which you shouldn't consider is the same cell from the previous row
        for(int day = 1; day < n; ++day) {
            for(int activity = 0; activity < 3; ++activity) {
                if(activity == 0)
                    points[day][activity] += max(points[day - 1][activity + 1], points[day - 1][activity + 2]);

                else if(activity == 1)
                    points[day][activity] += max(points[day - 1][activity - 1], points[day - 1][activity + 1]);

                else
                    points[day][activity] += max(points[day - 1][activity - 1], points[day - 1][activity - 2]);
            }
        }

        // Return the result value
        return *max_element(begin(points[n - 1]), end(points[n - 1]));
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Matrix | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/geeks-training/1
