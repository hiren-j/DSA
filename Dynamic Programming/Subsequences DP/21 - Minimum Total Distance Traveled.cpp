// Code to find the minimum total distance traveled by all the robots ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long LL;
    int n, m;

    // O(2^N) & O(N+M)
    LL solveWithoutMemo(vector<int>& robot, vector<int>& position, int i, int j) {
        // Edge case: If all the robots are successfully repaired then return 0 as an indication of it 
        if(i == n)
            return 0;

        // Edge case: If its not possible to repair all the robots then return LLONG_MAX as an indication of it
        if(j == m)
            return LLONG_MAX;

        // There are always two possibilities to perform for the ith robot
        LL currSkip = solveWithoutMemo(robot, position, i, j+1);   // Is to skip its repair at the jth factory
        LL currTake = solveWithoutMemo(robot, position, i+1, j+1); // Is to repair it at the jth factory

        // If all the robots are successfully repaired then consider the distance travelled by the ith robot
        if(currTake != LLONG_MAX)
            currTake += abs(position[j] - robot[i]);

        // As we're striving for the minimum distane travelled by all the robots hence return the minimum value
        return min(currSkip, currTake);
    }

    // O(2*N*M) & O(N*M + N+M)
    LL solveWithMemo(vector<vector<LL>>& dp, vector<int>& robot, vector<int>& position, int i, int j) {
        // Edge case: If all the robots are successfully repaired then return 0 as an indication of it 
        if(i == n)
            return 0;

        // Edge case: If its not possible to repair all the robots then return LLONG_MAX as an indication of it
        if(j == m)
            return LLONG_MAX;

        // Memoization table: If the current state is already computed then return the copmuted value
        if(dp[i][j] != -1)
            return dp[i][j];

        // There are always two possibilities to perform for the ith robot
        LL currSkip = solveWithMemo(dp, robot, position, i, j+1);   // Is to skip its repair at the jth factory
        LL currTake = solveWithMemo(dp, robot, position, i+1, j+1); // Is to repair it at the jth factory

        // If all the robots are successfully repaired then consider the distance travelled by the ith robot
        if(currTake != LLONG_MAX)
            currTake += abs(position[j] - robot[i]);

        // Store the result value to the memoization table and then return it
        return dp[i][j] = min(currSkip, currTake);
    }

public:
    // Method to find the minimum distance travelled by all the robots, using recursion with memoization :-
    LL minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Sorting helps to easily find the nearest factory of all the robots
        sort(begin(robot), end(robot));
        sort(begin(factory), end(factory));  

        // Stores the position of factories
        vector<int> position;
        for(auto& info : factory) {
            int f_pos   = info[0];
            int f_limit = info[1];
            while(f_limit--) position.push_back(f_pos);
        }
        
        n = robot.size(), m = position.size();
        
        // 2D memoization table
        vector<vector<LL>> dp(n, vector<LL>(m, -1));

        return solveWithMemo(dp, robot, position, 0, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long LL;

    // O(N*M) & O(N*M)
    LL solveUsing2DTable(vector<int>& robot, vector<int>& position) {
        int n = robot.size(), m = position.size();

        // 2D DP table
        vector<vector<LL>> dp(n+1, vector<LL>(m+1, LLONG_MAX));

        // Initialize the first edge case
        for(int j = 0; j <= m; ++j)
            dp[n][j] = 0;

        // Fill the rest of the table
        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                LL currSkip = dp[i][j+1];
                LL currTake = dp[i+1][j+1];
                if(currTake != LLONG_MAX) {
                    currTake += abs(position[j] - robot[i]);
                }
                dp[i][j] = min(currSkip, currTake);
            }
        }

        // Return teh result value
        return dp[0][0];
    }

    // O(N*M) & O(M)
    LL solveUsing1DTable(vector<int>& robot, vector<int>& position) {
        int n = robot.size(), m = position.size();

        vector<LL> nextRow(m+1, 0);

        for(int i = n-1; i >= 0; --i) {
            vector<LL> idealRow(m+1, LLONG_MAX);

            for(int j = m-1; j >= 0; --j) {
                LL currSkip = idealRow[j+1];
                LL currTake = nextRow[j+1];
                if(currTake != LLONG_MAX) {
                    currTake += abs(position[j] - robot[i]);
                }
                idealRow[j] = min(currSkip, currTake);
            }

            nextRow = idealRow;
        }

        return nextRow[0];
    }

public:
    // Method to find the minimum distance travelled by all the robots, using tabulation :-
    LL minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        // Sorting helps to easily find the nearest factory of all the robots
        sort(begin(robot), end(robot));
        sort(begin(factory), end(factory));  

        // Stores the position of factories
        vector<int> position;
        for(auto& info : factory) {
            int f_pos   = info[0];
            int f_limit = info[1];
            while(f_limit--) position.push_back(f_pos);
        }

        return solveUsing1DTable(robot, position);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Sorting 
Link  : https://leetcode.com/problems/minimum-total-distance-traveled/
