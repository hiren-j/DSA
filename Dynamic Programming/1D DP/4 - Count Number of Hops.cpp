// Code to find the total number of ways the frog can take to reach the top of the Nth step, a frog can jump either 1, 2, or 3 steps to go to the top ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {    
    #define MOD 1000000007
    typedef long long ll;

public:
    // Method to find the total number of ways, using recursion with memoization - O(N) & O(N)
    ll countWays(int N) {
        vector<ll> memory(N+1, -1);
        return solveWithMemo(N, memory);
    }

private:
    // O(3*N) & O(N+N)
    ll solveWithMemo(int N, vector<ll>& memory) {
        // Edge case: If the frog reaches the top then you've one valid way
        if(N == 0)
            return 1;
        
        // Edge case: If the frog misses the top then you've no valid way
        if(N < 0)
            return 0;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N] != -1)
            return memory[N];
        
        // There are always three posibilities to reach the Nth step
        ll jumpOneStep   = solveWithMemo(N-1, memory) % MOD; // Is to jump from the immediate 1st step below the Nth step  
        ll jumpTwoStep   = solveWithMemo(N-2, memory) % MOD; // Is to jump from the immediate 2nd step below the Nth step     
        ll jumpThreeStep = solveWithMemo(N-3, memory) % MOD; // Is to jump from the immediate 3rd step below the Nth step   

        // Store the result value to the memoization table and then return it 
        return memory[N] = (jumpOneStep + jumpTwoStep + jumpThreeStep) % MOD;   
    }

    // O(3^N) & O(N)
    ll solveWithoutMemo(int N) {
        // Edge case: If the frog reaches the top then you've one valid way
        if(N == 0)
            return 1;
        
        // Edge case: If the frog misses the top then you've no valid way
        if(N < 0)
            return 0;
            
        // There are always three posibilities to reach the Nth step
        ll jumpOneStep   = solveWithoutMemo(N-1) % MOD; // Is to jump from the immediate 1st step below the Nth step  
        ll jumpTwoStep   = solveWithoutMemo(N-2) % MOD; // Is to jump from the immediate 2nd step below the Nth step     
        ll jumpThreeStep = solveWithoutMemo(N-3) % MOD; // Is to jump from the immediate 3rd step below the Nth step   
            
        // Return the number of ways the frog can take to reach the Nth step
        return (jumpOneStep + jumpTwoStep + jumpThreeStep) % MOD;   
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    #define MOD 1000000007
    typedef long long ll;

public:
    // #1 Method to find the total number of ways, using 1D tabulation - O(N) & O(N)
    ll countWays_V1(int N) {
        // Edge case: If N is negative, then no valid steps exist, as because there can't be negative steps
        if(N < 0)
            return 0;
                    
        // 1D table: dp[J] represents the number of ways the frog can take to reach the Jth step
        vector<ll> dp(N+1, -1);
        
        dp[0] = 1;               // Stores the number of ways the frog can take to reach the 0th step
        dp[1] = 1;               // Stores the number of ways the frog can take to reach the 1th step
        dp[2] = (N > 1) ? 2 : 0; // Stores the number of ways the frog can take to reach the top (considering the first two steps only)
        
        for(int J=3; J<=N; ++J) {
            ll jumpOneStep   = dp[J-1] % MOD; 
            ll jumpTwoStep   = dp[J-2] % MOD; 
            ll jumpThreeStep = dp[J-3] % MOD; 
            dp[J] = (jumpOneStep + jumpTwoStep + jumpThreeStep) % MOD;
        }
        
        // Return the number of ways the frog can take to reach the Nth step
        return dp[N];
    }

    // #2 Method to find the total number of ways, using constant auxiliary space - O(N) & O(1)
    ll countWays_V2(int N) {
        // Edge case: If N is negative, then no valid steps exist, as because there can't be negative steps
        if(N < 0)
            return 0;
            
        ll jumpThreeStep = 0;  
        ll jumpTwoStep   = 0; 
        ll jumpOneStep   = 1; 
        ll numWays       = 0; // Stores the result value
        
        for(int J=1; J<=N; ++J) {
            numWays       = (jumpThreeStep + jumpTwoStep + jumpOneStep) % MOD;
            jumpThreeStep = jumpTwoStep % MOD; 
            jumpTwoStep   = jumpOneStep % MOD; 
            jumpOneStep   = numWays % MOD;     
        }
            
        // Return the total number of ways the frog can take to reach the Nth step
        return numWays;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/count-number-of-hops-1587115620/1
