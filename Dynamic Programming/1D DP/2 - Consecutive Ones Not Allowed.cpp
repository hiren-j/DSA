// Code to count all the possible distinct binary strings of length N such that there are no consecutive 1’s ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOTE: This problem is totally same as the previous one (Fibonacci Number). The edge case in the only change.

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long ll;
    const int MOD = 1e9+7;

public:
    // Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using recursion with memoization - O(N) & O(N)
    ll countStrings(int N) {
	vector<ll> memory(N + 1, -1);
	return solveWithMemo(memory, N);
    }

private:
    // O(2*N) & O(N+N)
    ll solveWithMemo(vector<ll>& memory, int N) {
    	// Edge case: When the value of N is less than 2 then return it by adding one to it
	if(N < 2)
	    return N + 1;
    
    	// Memoization table: If the current state is already computed then return the computed value
	if(memory[N] != -1)
	    return memory[N];
    
    	// Recursively find the two preceding values of N
	ll count1 = solveWithMemo(memory, N - 1);
	ll count2 = solveWithMemo(memory, N - 2);
    
    	// Store the result value to the memoizationt table and then return it
	return memory[N] = (count1 + count2) % MOD;
    }

    // O(2^N) & O(N)
    ll solveWithoutMemo(int N) {
    	// Edge case: When the value of N is less than 2 then return it by adding one to it
	if(N < 2)
	    return N + 1;

    	// Recursively find the two preceding values of N
	ll count1 = solveWithoutMemo(N - 1);
	ll count2 = solveWithoutMemo(N - 2);
    
    	// Add the values and then return it
	return (count1 + count2) % MOD;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long ll;
    const int MOD = 1e9+7;

public:
    // #1 Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using 1D tabulation - O(N) & O(N)
    ll countStrings_V1(int N) {
	vector<ll> dp(N + 1, -1);
	dp[0] = 1;
	dp[1] = 2;
    
	for(int num = 2; num <= N; ++num) {
	    ll count1 = dp[num - 1];
	    ll count2 = dp[num - 2];
	    dp[num]   = (count1 + count2) % MOD;
	}
    
	return dp[N];
    }

    // #2 Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using constant auxiliary space - O(N) & O(1)
    ll countStrings_V2(int N) {
	ll count1 = 1, count2 = 2;
	ll resultCount = count2;
    
	for(int num = 2; num <= N; ++num) {
	    resultCount = (count1 + count2) % MOD;
	    count1      = count2;
	    count2      = resultCount;
	} 
	    
	return resultCount;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/consecutive-1s-not-allowed1912/1
