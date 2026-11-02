#include <iostream>
using namespace std;

// Fibonacci ko loop se nikalne ka iterative tareeka.
long long fibonacciIterative(int n) {
    if (n <= 1) return n;

    long long previous = 0, current = 1;
    for (int i = 2; i <= n; ++i) {
        long long next = previous + current;
        previous = current;
        current = next;
    }
    return current;
}

// Fibonacci ko function calls ke through nikalne ka recursive tareeka.
long long fibonacciRecursive(int n) {
    if (n <= 1) return n; // Base case recursion ko rokta hai.
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// n disks ko source se destination tak auxiliary rod ki madad se le jao.
void towerOfHanoi(int n, char source, char auxiliary, char destination) {
    if (n == 0) return;

    towerOfHanoi(n - 1, source, destination, auxiliary);
    cout << "Disk " << n << ": " << source << " -> " << destination << '\n';
    towerOfHanoi(n - 1, auxiliary, source, destination);
}

int main() {
    int n;
    cout << "Enter n for Fibonacci (0 to 35): ";
    if (!(cin >> n) || n < 0 || n > 35) {
        cerr << "Please enter a valid n between 0 and 35.\n";
        return 1;
    }

    cout << "Iterative Fibonacci: " << fibonacciIterative(n) << '\n';
    cout << "Recursive Fibonacci: " << fibonacciRecursive(n) << '\n';

    int disks;
    cout << "Enter the number of disks for Tower of Hanoi (1 to 20): ";
    if (!(cin >> disks) || disks < 1 || disks > 20) {
        cerr << "Please enter a valid number of disks between 1 and 20.\n";
        return 1;
    }

    cout << "Tower of Hanoi moves:\n";
    towerOfHanoi(disks, 'A', 'B', 'C');
    return 0;
}
