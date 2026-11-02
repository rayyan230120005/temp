#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Item {
    double value;
    double weight;
    int originalNumber;
};

int main() {
    int n;
    double capacity;
    cout << "Enter the number of items and the knapsack capacity: ";
    if (!(cin >> n >> capacity) || n <= 0 || capacity < 0) {
        cerr << "Invalid input.\n";
        return 1;
    }

    vector<Item> items(n);
    cout << "Enter the value and weight of each item:\n";
    for (int i = 0; i < n; ++i) {
        cin >> items[i].value >> items[i].weight;
        items[i].originalNumber = i + 1;
        if (!cin || items[i].value < 0 || items[i].weight <= 0) {
            cerr << "Value must be non-negative and weight must be positive.\n";
            return 1;
        }
    }

    // Greedy choice: pehle sabse zyada value/weight ratio wala item lo.
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.value / a.weight > b.value / b.weight;
    });

    double remaining = capacity;
    double totalValue = 0;
    cout << fixed << setprecision(2);
    cout << "\nFraction taken for each item (item : fraction):\n";
    for (const Item& item : items) {
        if (remaining <= 0) break;
        double fraction = min(1.0, remaining / item.weight);
        totalValue += fraction * item.value;
        remaining -= fraction * item.weight;
        cout << "Item " << item.originalNumber << " : " << fraction << '\n';
    }

    cout << "Maximum total value: " << totalValue << '\n';
    return 0;
}
