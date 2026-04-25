#include <iostream>
#include <cmath>   // for abs()
using namespace std;

// ── CONCEPT 1: Booleans & if/else ───────────────────────────
// Use when: true/false decisions, or comparing ranges.
void roboticArm() {
    double l1, l2, d;
    cout << "\n-- Robotic Arm (booleans & if/else) --\n";
    cout << "Enter arm segment 1 length: "; cin >> l1;
    cout << "Enter arm segment 2 length: "; cin >> l2;
    cout << "Enter object distance: ";      cin >> d;
    bool reach = (l1 + l2 > d);   // boolean expression
    if (reach)
        cout << "Can reach!\n";
    else
        cout << "Cannot reach.\n";
}

// ── CONCEPT 2: Switch statement ──────────────────────────────
// Use when: matching one variable to many exact int/char values.
// break prevents fall-through to next case (usually unwanted).
// Grouping cases (1: 3: 5:) is intentional fall-through — useful!
void daysInMonth() {
    int month;
    cout << "\n-- Days in Month (switch) --\n";
    cout << "Enter month (1-12): "; cin >> month;
    switch (month) {
        case 1: case 3: case 5: case 7:
        case 8: case 10: case 12:
            cout << "31 days\n"; break;
        case 4: case 6: case 9: case 11:
            cout << "30 days\n"; break;
        case 2:
            cout << "28 days\n"; break;
        default:
            cout << "Not a valid month\n";
    }
}

// ── CONCEPT 3: For loop + alternating series ─────────────────
// Use when: you know the iteration count ahead of time.
// FIX 1: changed int → double so 1/check isn't integer division.
// FIX 2: moved the +/- logic inside the loop correctly.
// This approximates π/4 (Leibniz formula).
void leibnizSeries() {
    cout << "\n-- Leibniz Series (for loop) --\n";
    double sum = 0.0;
    double denom = 1.0;
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 == 0)
            sum -= (1.0 / denom);  // even terms subtract
        else
            sum += (1.0 / denom);  // odd terms add
        denom += 2;
    }
    cout << "Sum (approx pi/4): " << sum << endl;
}

// ── CONCEPT 4: While loop + factorial ────────────────────────
// Use when: you loop until a condition changes, count unknown.
// FIX: removed illegal 'break' outside loop — use return instead.
void factorial() {
    int n;
    cout << "\n-- Factorial (while loop) --\n";
    cout << "Enter n: "; cin >> n;
    if (n == 0) { cout << "0! = 1\n"; return; }  // base case
    int result = n, an = n;
    while (an > 1) {
        result *= (an - 1);
        --an;
    }
    cout << n << "! = " << result << endl;
}

// ── CONCEPT 5: For loop + power ──────────────────────────────
// Use when: repeated multiplication a fixed number of times.
void power() {
    int a, n;
    cout << "\n-- Power (for loop) --\n";
    cout << "Enter base a: ";     cin >> a;
    cout << "Enter exponent n: "; cin >> n;
    if (n == 0) { cout << a << "^0 = 1\n"; return; }
    int result = a;
    for (int i = 2; i <= n; ++i)
        result *= a;
    cout << a << "^" << n << " = " << result << endl;
}

// ── CONCEPT 6: Infinite loop + break + running max ───────────
// Use when: user drives how many inputs — exit on condition.
// FIX: initialize max with first input, not -1 (handles negatives).
void runningMax() {
    int num, max;
    char answer;
    cout << "\n-- Running Maximum (infinite loop + break) --\n";
    for (int i = 1; ; ++i) {
        cout << "Enter a number: "; cin >> num;
        if (i == 1)          max = num;   // first input sets max
        else if (num > max)  max = num;   // update if bigger
        cout << "Enter more? (y/n): "; cin >> answer;
        if (answer != 'y') break;
    }
    cout << "Max: " << max << endl;
}

// ── CONCEPT 7: Nested loops ───────────────────────────────────
// Use when: you need a grid or pattern — outer=rows, inner=cols.
// FIX: the original nested loop was computing a garbled product.
//      Replaced with a clear triangle pattern to show the concept.
void starTriangle() {
    int height;
    cout << "\n-- Star Triangle (nested loops) --\n";
    cout << "Enter height: "; cin >> height;
    for (int row = 1; row <= height; ++row) {     // outer: each row
        for (int col = 1; col <= row; ++col)      // inner: stars per row
            cout << "* ";
        cout << endl;
    }
}

// ── CONCEPT 8: Float comparison gotcha ───────────────────────
// Never use == with doubles. Use abs(a-b) < small tolerance.
void floatGotcha() {
    cout << "\n-- Float Comparison Gotcha --\n";
    double f = 0.1;
    double lhs = f + f + f + 0.3;
    double rhs = 3 * (f + 0.1);
    // BAD:  if (lhs == rhs)  ← unreliable for doubles
    if (abs(lhs - rhs) < 1e-9)   // GOOD: tolerance check
        cout << "Equal (within tolerance)\n";
    else
        cout << "Not equal — floating point error!\n";
}

// ── MAIN ──────────────────────────────────────────────────────
int main() {
    roboticArm();    // booleans & if/else
    daysInMonth();   // switch statement
    leibnizSeries(); // for loop — series sum
    factorial();     // while loop
    power();         // for loop — repeated multiply
    runningMax();    // infinite loop + break
    starTriangle();  // nested loops
    floatGotcha();   // float comparison warning
    return 0;
}