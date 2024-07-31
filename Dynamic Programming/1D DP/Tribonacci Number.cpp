// Program to find the Nth number of the tribonacci sequence ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the Nth number of the tribonacci sequence, using recursion with memoization - O(N) & O(N)
    int getNthTribonacci(int N) {
        vector<int> memory(N+1, -1);
        return solveWithMemo(N, memory);
    }

private:
    // O(3*N) & O(N+N)
    int solveWithMemo(int N, vector<int>& memory) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N] != -1)
            return memory[N];

        // Store the result value to the memoization table and then return it
        return memory[N] = solveWithMemo(N-1, memory) + solveWithMemo(N-2, memory) + solveWithMemo(N-3, memory);
    }
    
    // O(3^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        // Recursively compute and return the sum of the three preceding values of N
        return solveWithoutMemo(N-1) + solveWithoutMemo(N-2) + solveWithoutMemo(N-3);
    };
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the Nth number of the sequence, using 1D tabulation - O(N) & O(N)
    int getNthTribonacci_V1(int N) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        // 1D table: dp[J] stores the Jth number of the tribonacci sequence
        vector<int> dp(N+1, 0);
        dp[1] = 1;
        dp[2] = 1;

        // Iterate and store the sum of the three preceding values
        for(int J=3; J<=N; J++)
            dp[J] = dp[J-3] + dp[J-2] + dp[J-1];

        // Return the Nth number of the sequence
        return dp[N];
    }

    // #2 Method to find the Nth number of the sequence, using constant auxiliary space - O(N) & O(1)
    int getNthTribonacci_V2(int N) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        int prevA = 0, prevB = 1, prevC = 1;
        int currNum;

        // Iterate and store the sum of the three preceding values
        for(int J=3; J<=N; J++) {
            currNum = prevA + prevB + prevC;
            prevA = prevB;
            prevB = prevC;
            prevC = currNum;
        }

        // Return the Nth number of the sequence
        return currNum;
    }
};

// Driver code
int main() {
    cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

    int testCases;
    cout<<"Enter the total number of testcases: ";
    cin>>testCases;

    while(testCases--) {
        int N;
        cout<<"\nEnter a value: ";
        cin>>N;

        // Check the given value is lying within the problem constraints or not
        if(N < 0 || N > 37) {
            cout<<"Enter a value which lies between 0 and 37!\n";
        }
        else {
            BottomUp bottomUp;
            cout<<"The "<<N<<"th number of the tribonacci sequence is: "<<bottomUp.getNthTribonacci_V2(N)<<'\n';
        }
    }

    return 0;
};
/*
        
    Topics: Dynamic Programming | Math | Memoization
    Link  : https://leetcode.com/problems/N-th-tribonacci-number/description/
*/
