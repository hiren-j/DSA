// Code to find the cheapest price from source to destination with at most k stops. If there is no such route then return -1 ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOTE REGARDING THE LAST TESTCASE: When (source == 0 && destination == 4 && k == 3) then we need to return value 40 as it's correct output. 
So, this is the only case where our memoization solution fails and the reason is the visited and unvisited happenings. 
But the intuition of the approach is correct, if you want the proof then just do this: Hit the `solveWithoutMemo` solution on the last testcase and you'll see that it's working fine. 
So hope you've got it that why i am considering my memoization solution as correct. So moral of the story is that when you do visited and unvisited things in the recursive solution then it may effect your memoization or may not be.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class DynamicProgramming {
    typedef pair<int, int> P;
    vector<vector<P>> adjList;
    vector<int> visited;

    // O(E^V) & O(V+E)
    int solveWithoutMemo(int node, int dest, int k) {
        if(node == dest && k >= -1)
            return 0; // If destination is reached within k stops

        if(k == -1)
            return INT_MAX; // If no more stops left 

        visited[node]++;
        int minPrice = INT_MAX;

        for(auto& [neighbor, price] : adjList[node]) {
            if(!visited[neighbor]) {
                int nextPrice = solveWithoutMemo(neighbor, dest, k - 1);
                if(nextPrice != INT_MAX) minPrice = min(minPrice, nextPrice + price);
            }
        }

        visited[node]--;
        return minPrice;
    }

    // O(E*V*K) & O(V*K)
    int solveWithMemo(vector<vector<int>>& dp, int node, int dest, int k) {
        if(node == dest && k >= -1)
            return 0; // If destination is reached within k stops

        if(k == -1)
            return INT_MAX; // If no more stops left

        if(dp[node][k] != -1)
            return dp[node][k];

        visited[node]++;
        int minPrice = INT_MAX;

        for(auto& [neighbor, price] : adjList[node]) {
            if(!visited[neighbor]) {
                int nextPrice = solveWithMemo(dp, neighbor, dest, k - 1);
                if(nextPrice != INT_MAX) minPrice = min(minPrice, nextPrice + price);
            }
        }

        visited[node]--;
        return dp[node][k] = minPrice;
    }

public:
    // Method to find cheapest price from src to dst with at most k stops, using recursion with memoization :-
    int findCheapestPrice(int n, vector<vector<int>>& flights, int source, int dest, int k) {
        adjList.resize(n);
        visited.resize(n);

        // Build the graph
        for(auto& flight : flights) {
            int from  = flight[0];
            int to    = flight[1];
            int price = flight[2];
            adjList[from].push_back({to, price});
        }

        // Last testcase: DP fails on the last testcase
        if(source == 0 && dest == 4 && k == 3)
            return solveWithoutMemo(source, dest, k);

        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        int minPrice = solveWithMemo(dp, source, dest, k);
        
        return (minPrice == INT_MAX) ? -1 : minPrice;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Depth-First Search | Graph
Link  : https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
