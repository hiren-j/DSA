// Code to find the minimum number of dollars you need to travel every day in the given list of days ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int getNextStartDay(vector<int>& days, int target, int start) {
        for(int day = start; day < n; ++day)
            if(days[day] > target)
                return day;
        return n;
    } 

    // O(3^N * N) & O(N)
    int solveWithoutMemo(vector<int>& days, vector<int>& costs, int day) {
        // Edge case: If no more days left, then you no need to travel anymore
        if(day == n)
            return 0;

        // There are always three posibilities to perform at each day
        int oneDayPass    = costs[0] + solveWithoutMemo(days, costs, getNextStartDay(days, days[day] + 1-1, day+1));  // To buy 1-day pass
        int sevenDayPass  = costs[1] + solveWithoutMemo(days, costs, getNextStartDay(days, days[day] + 7-1, day+1));  // To buy 7-day pass
        int thirtyDayPass = costs[2] + solveWithoutMemo(days, costs, getNextStartDay(days, days[day] + 30-1, day+1)); // To buy 30-day pass

        // As we're striving for minimum dollars hence return the minimum among all
        return min({oneDayPass, sevenDayPass, thirtyDayPass}); 
    }

    // O(3*N*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, vector<int>& days, vector<int>& costs, int day) {
        // Edge case: If no more days left, then you no need to travel anymore
        if(day == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp[day] != -1)
            return dp[day];

        // There are three possibilities to perform at each day
        int oneDayPass    = costs[0] + solveWithMemo(dp, days, costs, getNextStartDay(days, days[day] + 1-1, day+1));  // To buy 1-day pass
        int sevenDayPass  = costs[1] + solveWithMemo(dp, days, costs, getNextStartDay(days, days[day] + 7-1, day+1));  // To buy 7-day pass
        int thirtyDayPass = costs[2] + solveWithMemo(dp, days, costs, getNextStartDay(days, days[day] + 30-1, day+1)); // To buy 30-day pass

        // Store the result value to the memoization table and then return it
        return dp[day] = min({oneDayPass, sevenDayPass, thirtyDayPass}); 
    }

public:
    // Method to find the minimum numbe of dollars, using recursion with memoization - O(N*N) & O(N)
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, days, costs, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int getNextStartDay(vector<int>& days, int target, int start) {
        for(int day = start; day < n; ++day)
            if(days[day] > target)
                return day;
        return n;
    } 

public:
    // Method to find the minimum number of dollars, using 1D tabulation - O(N*N) & O(N)
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        n = days.size();

        vector<int> dp(n + 1, 0);

        for(int day = n-1; day >= 0; --day) {
            int oneDayPass    = costs[0] + dp[getNextStartDay(days, days[day] + 1-1, day+1)];
            int sevenDayPass  = costs[1] + dp[getNextStartDay(days, days[day] + 7-1, day+1)];
            int thirtyDayPass = costs[2] + dp[getNextStartDay(days, days[day] + 30-1, day+1)];
            dp[day] = min({oneDayPass, sevenDayPass, thirtyDayPass}); 
        }

        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/minimum-cost-for-tickets/description/
