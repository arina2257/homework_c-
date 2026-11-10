
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> c(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> c[i];
    }

    vector<vector<vector<int>>> dp(
        N + 2,
        vector<vector<int>>(N + 2, vector<int>(M + 1, 0))
    );

    for (int len = 1; len <= N; len++) {
        for (int l = 1; l + len - 1 <= N; l++) {
            int r = l + len - 1;

            for (int x = 0; x <= M; x++) {
                if (c[l] == x) {
                    dp[l][r][x] = dp[l + 1][r][x];
                } else {
                    dp[l][r][x] = N + 1;

                    for (int k = l; k <= r; k++) {
                        if (c[k] == c[l]) {
                            int cost = 1
                                + dp[l + 1][k - 1][c[l]]
                                + dp[k + 1][r][x];

                            dp[l][r][x] =
                                min(dp[l][r][x], cost);
                        }
                    }
                }
            }
        }
    }

    cout << dp[1][N][0];

    return 0;
}

