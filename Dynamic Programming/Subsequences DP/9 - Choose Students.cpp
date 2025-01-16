// Code to find the number of ways you can choose `chooseLimit` students from a class of `totalStudents` students ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V1 {
public:
    // O(TS*CL) & O(TS*CL) : Where TS = totalStudents, CL = chooseLimit
    int numWays(int totalStudents, int chooseLimit) {
    	vector<vector<int>> dp(totalStudents + 1, vector<int>(chooseLimit + 1, -1));
    	return solveWithMemo(dp, totalStudents, 0, chooseLimit);
    }

private:
    // O(2*TS*CL) & O(TS*CL + TS)
    int solveWithMemo(vector<vector<int>>& dp, int totalStudents, int student, int chooseLimit) {
    	if(chooseLimit == 0) 
    	    return 1; // Edge case when you've chosen students with specified limit then return 1
    
    	if(student == totalStudents)
    	    return 0; // Edge case when all the students are exhausted then return 0

    	if(dp[student][chooseLimit] != -1)
    	    return dp[student][chooseLimit];

        // There are always two possibilities at each student
    	int currSkip   = solveWithMemo(dp, totalStudents, student + 1, chooseLimit);     // Is to skip it
    	int currChoose = solveWithMemo(dp, totalStudents, student + 1, chooseLimit - 1); // Is to choose it
    
    	return dp[student][chooseLimit] = (currSkip + currChoose);
    }

    // O(2^TS) & O(TS)
    int solveWithoutMemo(int totalStudents, int student, int chooseLimit) {
    	if(chooseLimit == 0) 
    	    return 1; // Edge case when you've chosen students with specified limit then return 1
    
    	if(student == totalStudents)
    	    return 0; // Edge case when all the students are exhausted then return 0

        // There are always two possibilities at each student
    	int currSkip   = solveWithoutMemo(totalStudents, student + 1, chooseLimit);     // Is to skip it
    	int currChoose = solveWithoutMemo(totalStudents, student + 1, chooseLimit - 1); // Is to choose it
    
    	return (currSkip + currChoose);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown_V2 {
public:
    // O(TS*TS*CL) & O(TS*CL)
    int numWays(int totalStudents, int chooseLimit) {
    	vector<vector<int>> dp(totalStudents + 1, vector<int>(chooseLimit + 1, -1));
    	return solveWithMemo(dp, totalStudents, 0, chooseLimit);
    }

private:
    // O(TS*TS*CL) & O(TS*CL + TS)
    int solveWithMemo(vector<vector<int>>& dp, int totalStudents, int startStudent, int chooseLimit) {
    	if(chooseLimit == 0) 
    	    return 1; // Edge case when you've chosen students with specified limit then return 1
    
    	if(startStudent == totalStudents)
    	    return 0; // Edge case when all the students are exhausted then return 0

    	if(dp[startStudent][chooseLimit] != -1)
    	    return dp[startStudent][chooseLimit];

        int count = 0;

        for(int student = startStudent; student < totalStudents; ++student)
            count += solveWithMemo(dp, totalStudents, student + 1, chooseLimit - 1);
    
    	return dp[startStudent][chooseLimit] = count;
    }

    // O(TS^TS) & O(TS)
    int solveWithoutMemo(int totalStudents, int startStudent, int chooseLimit) {
    	if(chooseLimit == 0) 
    	    return 1; // Edge case when you've chosen students with specified limit then return 1
    
        int count = 0;

        for(int student = startStudent; student < totalStudents; ++student)
            count += solveWithoutMemo(totalStudents, student + 1, chooseLimit - 1);
    
    	return count;
    }
};
// Note: This solution (TopDown_V2) is the loop conversion of the first solution (TopDown_V1) and you could see that the time complexity increases in this (TopDown_V2)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(TS*CL) & O(TS*CL)
    int numWays_V1(int totalStudents, int chooseLimit) {
    	vector<vector<int>> dp(totalStudents + 1, vector<int>(chooseLimit + 1, 0));

        for(int student = 0; student <= totalStudents; ++student)
            dp[student][0] = 1; // Initialize the first edge case

        for(int student = totalStudents-1; student >= 0; --student) {
            for(int limit = 1; limit <= chooseLimit; ++limit) {
    	        int currSkip   = dp[student + 1][limit];
    	        int currChoose = dp[student + 1][limit - 1];
    	        dp[student][limit] = (currSkip + currChoose);
            }
        }

    	return dp[0][chooseLimit];
    }

    // O(TS*CL) & O(CL)
    int numWays_V2(int totalStudents, int chooseLimit) {
        vector<int> nextRow(chooseLimit + 1, 0), idealRow(chooseLimit + 1, 0);
        nextRow[0] = 1; // Initialize the first edge case

        for(int student = totalStudents-1; student >= 0; --student) {
            idealRow[0] = 1; // Initialize the first edge case
            for(int limit = 1; limit <= chooseLimit; ++limit) {
    	        int currSkip   = nextRow[limit];
    	        int currChoose = nextRow[limit - 1];
    	        idealRow[limit] = (currSkip + currChoose);
            }
            nextRow = idealRow;
        }

    	return nextRow[chooseLimit];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.naukri.com/code360/problems/choose-students_1062724?topList=top-dynamic-programming-questions&problemListRedirection=true&page=4&leftPanelTabValue=PROBLEM
