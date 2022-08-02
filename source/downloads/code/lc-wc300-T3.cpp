class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        vector<long long> dp(n+1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            // dp[i] = dp[i-1];
            // if (i > forget) dp[i] -= dp[i-forget];
            for (int j = delay; j < forget && i - j >= 1; j++)
                dp[i] += dp[i-j];
            dp[i] %= 1000000007;
        }
        long long res = 0;
        for (int i = n; i >= 1 && i > n - forget; --i)
            res = (res + dp[i]) % 1000000007;
        return res;
    }
};