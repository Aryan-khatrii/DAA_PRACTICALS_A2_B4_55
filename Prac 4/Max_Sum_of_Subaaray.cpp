#include <bits/stdc++.h>
using namespace std;

struct Result {
    long long sum;
    vector<int> subarray;
};

// Function to compute maximum crossing subarray
Result maxCrossingSubarray(vector<int>& arr, int low, int mid, int high, long long constraint) {
    long long leftSum = LLONG_MIN, sum = 0;
    int maxLeft = mid;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum <= constraint && sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }

    long long rightSum = LLONG_MIN;
    sum = 0;
    int maxRight = mid + 1;
    for (int j = mid + 1; j <= high; j++) {
        sum += arr[j];
        long long total = (leftSum == LLONG_MIN ? sum : leftSum + sum);
        if (total <= constraint && total > rightSum) {
            rightSum = total;
            maxRight = j;
        }
    }

    Result res;
    res.sum = LLONG_MIN;
    if (leftSum != LLONG_MIN && leftSum > res.sum) {
        res.sum = leftSum;
        res.subarray = vector<int>(arr.begin() + maxLeft, arr.begin() + mid + 1);
    }
    if (rightSum != LLONG_MIN && rightSum > res.sum) {
        res.sum = rightSum;
        res.subarray = vector<int>(arr.begin() + maxLeft, arr.begin() + maxRight + 1);
    }
    return res;
}

// Divide & conquer function
Result maxSubarray(vector<int>& arr, int low, int high, long long constraint) {
    if (low > high) return {LLONG_MIN, {}};
    if (low == high) {
        Result res;
        if (arr[low] <= constraint) {
            res.sum = arr[low];
            res.subarray = {arr[low]};
        } else {
            res.sum = LLONG_MIN;
        }
        return res;
    }

    int mid = (low + high) / 2;
    Result left = maxSubarray(arr, low, mid, constraint);
    Result right = maxSubarray(arr, mid + 1, high, constraint);
    Result cross = maxCrossingSubarray(arr, low, mid, high, constraint);

    Result best = left;
    if (right.sum > best.sum) best = right;
    if (cross.sum > best.sum) best = cross;
    return best;
}

// Function to run a single test case
void runTest(vector<int> resources, long long constraint, string caseName) {
    cout << "Test Case: " << caseName << "\n";

    if (resources.empty() || constraint <= 0) {
        cout << "No subarray is possible\n\n";
        return;
    }

    Result ans = maxSubarray(resources, 0, resources.size() - 1, constraint);

    if (ans.sum == LLONG_MIN) {
        cout << "No subarray is possible\n\n";
    } else {
        cout << "Maximum subarray sum under constraint: " << ans.sum << "\n";
        cout << "Subarray: ";
        for (int x : ans.subarray) cout << x << " ";
        cout << "\n\n";
    }
}

int main() {
    // 1. Basic small array
    runTest({2, 1, 3, 4}, 5, "Basic small array");

    // 2. Exact match to constraint
    runTest({2, 2, 2, 2}, 4, "Exact match to constraint");

    // 3. Single element equals constraint
    runTest({1, 5, 2, 3}, 5, "Single element equals constraint");

    // 4. All elements smaller but no combination fits
    runTest({6, 7, 8}, 5, "All elements too large");

    // 5. Multiple optimal subarrays
    runTest({1, 2, 3, 2, 1}, 5, "Multiple optimal subarrays");

    // 6. Large window valid
    runTest({1, 1, 1, 1, 1}, 4, "Large window valid");

    // 7. Sliding window shrink needed
    runTest({4, 2, 3, 1}, 5, "Sliding window shrink needed");

    // 8. Empty array
    runTest({}, 10, "Empty array");

    // 9. Constraint = 0
    runTest({1, 2, 3}, 0, "Constraint zero");

    // 10. Very large input (stress test)
    vector<int> largeInput(100000);
    iota(largeInput.begin(), largeInput.end(), 1); // Fill 1..100000
    runTest(largeInput, 1000000000, "Very large input (stress test)");

    return 0;
}
