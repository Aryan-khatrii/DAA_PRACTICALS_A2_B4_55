#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of book IDs: ";
    cin >> n;

    vector<int> keys(n);
    cout << "Enter the sorted book IDs: ";
    for (int i = 0; i < n; i++)
        cin >> keys[i];

    vector<double> p(n + 1), q(n + 1);

    cout << "Enter the probabilities of successful searches (P[i]): ";
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    cout << "Enter the probabilities of unsuccessful searches (Q[i]): ";
    for (int i = 0; i <= n; i++)
        cin >> q[i];

    vector<vector<double>> e(n + 2, vector<double>(n + 1, 0.0));
    vector<vector<double>> w(n + 2, vector<double>(n + 1, 0.0));


    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    
    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j])
                    e[i][j] = t;
            }
        }
    }

    cout << fixed << setprecision(4);
    cout << "\nthe minimum expected cost of searching using an Optimal Binary Search Tree :"
         << e[1][n] << endl;

    return 0;
}
