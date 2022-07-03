class Solution {
public:
    long long mod = 1000000007;
    int xy[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int countPaths(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<long long>> dp(m, vector<long long>(n, 1));
        
        vector<vector<int>> vis(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j)
                dfs(i, j, vis, dp, grid);
        }
        
        long long res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res += dp[i][j];
                res %= mod;
            }
        }
        return res;
    }
    
    long long dfs(int i , int j, vector<vector<int>>& vis, vector<vector<long long>>& dp, vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        if (vis[i][j] == 1) return dp[i][j];
        for (int k = 0; k < 4; ++k) {
            int nx = i + xy[k][0];
            int ny = j + xy[k][1];
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[i][j] > grid[nx][ny])
                dp[i][j] += dfs(nx, ny, vis, dp, grid);
            dp[i][j] %= mod;
        }
        vis[i][j] = 1;
        return dp[i][j];
    }
};
