#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Longest Common Subsequence
void LCS(string x, string y) {
    int m = x.size();
    int n = y.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Build DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i - 1] == y[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Backtrack to find LCS
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (x[i - 1] == y[j - 1]) {
            lcs = x[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    cout << "\n--- Longest Common Subsequence (LCS) ---\n";
    cout << "String 1: " << x << "\n";
    cout << "String 2: " << y << "\n";
    cout << "LCS Length: " << dp[m][n] << "\n";
    cout << "LCS: " << lcs << endl;
}

// Longest Repeating Subsequence
void LRS(string s) {
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == s[j - 1] && i != j)
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // Backtrack to find LRS
    string lrs = "";
    int i = n, j = n;
    while (i > 0 && j > 0) {
        if (s[i - 1] == s[j - 1] && i != j) {
            lrs = s[i - 1] + lrs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }

    cout << "\n--- Longest Repeating Subsequence (LRS) ---\n";
    cout << "String: " << s << "\n";
    cout << "LRS Length: " << dp[n][n] << "\n";
    cout << "LRS: " << lrs << endl;
}

int main() {
    int choice;
    cout << "===== DAA Practical 5: LCS & LRS =====\n";
    cout << "1. Longest Common Subsequence (LCS)\n";
    cout << "2. Longest Repeating Subsequence (LRS)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        string X, Y;
        cout << "\nEnter first string: ";
        cin >> X;
        cout << "Enter second string: ";
        cin >> Y;
        LCS(X, Y);
    } else if (choice == 2) {
        string S;
        cout << "\nEnter string: ";
        cin >> S;
        LRS(S);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}