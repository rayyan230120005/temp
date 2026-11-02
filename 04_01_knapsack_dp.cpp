#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, capacity;
    cout << "Enter the number of items and the knapsack capacity: ";
    if (!(cin >> n >> capacity) || n <= 0 || capacity < 0) {
        cerr << "Invalid input.\n";
        return 1;
    }

    vector<int> weights(n + 1), values(n + 1);
    cout << "Enter the integer weight and value of each item:\n";
    for (int i = 1; i <= n; ++i) {
        cin >> weights[i] >> values[i];
        if (!cin || weights[i] <= 0 || values[i] < 0) {
            cerr << "Weight must be positive and value must be non-negative.\n";
            return 1;
        }
    }

    // dp[i][w] = pehle i items se capacity w tak ka maximum value.
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            dp[i][w] = dp[i - 1][w]; // Item skip karne ka option.
            if (weights[i] <= w) {
                dp[i][w] = max(dp[i][w], values[i] + dp[i - 1][w - weights[i]]);
            }
        }
    }

    cout << "Maximum value: " << dp[n][capacity] << '\n';

    // DP table se peeche jaakar pata lagate hain kaunse items select hue.
    vector<int> selected;
    int w = capacity;
    for (int i = n; i >= 1; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i);
            w -= weights[i];
        }
    }

    cout << "Selected items: ";
    if (selected.empty()) cout << "no items";
    else {
        reverse(selected.begin(), selected.end());
        for (int item : selected) cout << item << ' ';
    }
    cout << '\n';
    return 0;
}
