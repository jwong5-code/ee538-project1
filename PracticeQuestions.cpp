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

// ── CONCEPT 9: Variance ───────────────────────────────────────
// Use when: measuring how spread out a set of numbers is.
// Formula: variance = sum of (each value - mean)^2 / n
// Requires two passes: first to get the mean, then to get variance.
// Step by step for values 2, 4, 4, 4, 5, 5, 7, 9:
//   mean = (2+4+4+4+5+5+7+9)/8 = 5.0
//   variance = ((2-5)^2 + (4-5)^2 + ... + (9-5)^2) / 8 = 4.0
void variance() {
    int n;
    cout << "\n-- Variance --\n";
    cout << "How many numbers? "; cin >> n;
    double arr[100];
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        cout << "Enter value " << i+1 << ": "; cin >> arr[i];
        sum += arr[i];
    }
    double mean = sum / n;
    double varSum = 0;
    for (int i = 0; i < n; ++i)
        varSum += (arr[i] - mean) * (arr[i] - mean);
    cout << "Mean: " << mean << endl;
    cout << "Variance: " << varSum / n << endl;
}

// ── CONCEPT 10: Unanimous vote check ─────────────────────────
// Use when: checking if all values in a sequence are the same.
// Strategy: save the first vote, then compare every other to it.
// If any differs, set a flag and break early.
// bool flag pattern: start true, flip to false on any mismatch.
void unanimousVote() {
    int n;
    cout << "\n-- Unanimous Vote Check --\n";
    cout << "How many voters? "; cin >> n;
    int firstVote;
    cout << "Voter 1 vote (0 or 1): "; cin >> firstVote;
    bool unanimous = true;           // assume unanimous until proven otherwise
    for (int i = 2; i <= n; ++i) {
        int vote;
        cout << "Voter " << i << " vote (0 or 1): "; cin >> vote;
        if (vote != firstVote) {
            unanimous = false;       // mismatch found
            break;                   // no need to keep checking
        }
    }
    if (unanimous)
        cout << "Vote is unanimous!\n";
    else
        cout << "Vote is NOT unanimous.\n";
}

// ── CONCEPT 11: Least significant digit ──────────────────────
// Use when: you need to extract or work with digits one at a time.
// The least significant digit (LSD) is the rightmost digit.
// Extract with modulo: n % 10 always gives the last digit.
//   e.g. 347 % 10 = 7
// Remove the last digit with integer division: n / 10
//   e.g. 347 / 10 = 34
// Loop both together to process every digit of a number.
void leastSignificantDigit() {
    int n;
    cout << "\n-- Least Significant Digit --\n";
    cout << "Enter a number: "; cin >> n;
    cout << "Digits from right to left: ";
    while (n > 0) {
        cout << n % 10 << " ";   // extract last digit
        n /= 10;                 // remove last digit
    }
    cout << endl;
}


// ── CONCEPT 12: return 0 ─────────────────────────────────────
// return 0 at the end of main() tells the OS the program finished
// successfully. 0 = no error. 1 = something went wrong.
// Java and Python handle this automatically — C++ requires it manually.

// ── CONCEPT 13: Functions with return values ──────────────────
// Use when: a function needs to compute and send a value back.
// Return type goes before the function name (int, double, bool, etc.)
// void = returns nothing (just does something)
// int  = returns an integer
// Always need a matching return statement at the end.
int factorial(int n) {
    int term1 = 1;
    for (int i = 1; i <= n; i++) {
        term1 = term1 * i;   // builds up: 1*1*2*3*...*n
    }
    return term1;            // sends result back to caller
}

// ── CONCEPT 14: Function call stack ──────────────────────────
// When one function calls another, C++ pauses the current function,
// runs the called one, then resumes. Each call gets its own memory.
// Stack order for nchoosek(5,3):
//   main → nchoosek → factorial(5) → returns 120
//                   → factorial(3) → returns 6
//                   → factorial(2) → returns 2
//          nchoosek returns 120 / (6 * 2) = 10
//   main finishes
// NOTE: formula is term2 * term3, not term2 + term3 (bug in notes)
int nchoosek(int n, int k) {
    int term1 = factorial(n);
    int term2 = factorial(k);
    int term3 = factorial(n - k);
    return term1 / (term2 * term3);  // FIX: * not +
}

// ── CONCEPT 15: Bisection method ─────────────────────────────
// Use when: solving equations like e^-x - x = 0 that have no
// clean algebraic solution. Closes in on answer by narrowing a range.
// Margin of error (tolx): we can never get the EXACT answer with
// floating point, so we stop when range is small enough (e.g. 1e-7).
//
// How it works visually for f(x) = e^-x - x, range [0,1]:
//   f(0) = +1.0  (positive)
//   f(1) = -0.63 (negative)
//   Start: l=0[+]        h=1[-]       range=1.0
//   Step1: m=0.5  f(+) → l=0.5
//   Step2: m=0.75 f(-) → h=0.75
//   Step3: keeps narrowing until range < 0.0000001
//   Answer: ~0.5671
//
// Key idea: if f(m) and f(l) have the same sign, the crossing point
// is NOT between l and m — so we move l up to m.
// If opposite signs, the crossing IS between l and m — move h down.

// FIX 1: f() must be declared BEFORE bisection() calls it
double f(double x) {
    return exp(-x) - x;
}

// FIX 2: "l l= m" typo → should be "l = m"
// FIX 3: return m was inside the while loop → moved outside
double bisection(double l, double h) {
    double tolx = 1e-7;
    double m;
    while (abs(h - l) > tolx) {
        m = (l + h) / 2;
        if (f(m) * f(l) > 0)  // same sign: solution not between l and m
            l = m;             // move left boundary up
        else
            h = m;             // move right boundary down
    }
    return m;                  // FIX: outside the loop
}

// ── CONCEPT 16: Pass by value vs pass by reference ────────────
// C++ passes copies by default (pass by value).
// The original variables are NOT changed — swap below does nothing.
// This is different from Java/Python where objects are always refs.
void swapBroken(int x, int y) {
    int temp = x;   // x and y are copies — originals unchanged
    x = y;
    y = temp;
}                   // changes are thrown away when function ends

// FIX: use & to pass by reference — works on the real variables
void swapFixed(int &x, int &y) {
    int temp = x;   // & means "the actual variable, not a copy"
    x = y;
    y = temp;
}                   // originals are now actually swapped

// ── CONCEPT 17: Arrays ───────────────────────────────────────
// Use when: storing multiple values of the same type under one name.
// Size must be fixed at compile time (unlike vectors).
// Declaration: type name[size];
// Index starts at 0, ends at size-1.
// int hw[20] = {0}  initializes ALL elements to 0.
// int hw[20] = {5}  sets first to 5, rest to 0 (not all to 5!).
// hw[2] accesses the 3rd element (0-indexed).

void arrayMax() {
    cout << "\n-- Array Max (arrays + for loop) --\n";
    int temps[5];
    for (int i = 0; i <= 4; i++)
        cin >> temps[i];
    int maxval = temps[0];          // start max at first element, not -1
    for (int i = 1; i < 5; i++) {
        if (maxval < temps[i])
            maxval = temps[i];
    }
    cout << "Highest temp is: " << maxval << endl;
}

// ── CONCEPT 18: Arrays + strings + linear search ─────────────
// Use when: searching for a value by scanning every element.
// Returns index if found, -1 if not found (-1 = standard "not found").
// string type needs #include <string>.
// Arrays passed to functions decay to pointers — size must be
// passed separately (arrays don't know their own size).
#include <string>

int find_name(string arr[], int size, string s) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == s)
            return i;    // found — return index
    }
    return -1;           // not found
}

void print_names(string names[], int num_st) {
    for (int i = 0; i < num_st; i++)
        cout << names[i] << endl;
}

// ── CONCEPT 19: Sorted insert into array ─────────────────────
// Use when: keeping an array in sorted order as you add elements.
// Two steps:
//   1. Find where the new name belongs (first spot where new < current)
//   2. Shift everything from that spot rightward to make room
//   3. Insert at the found spot, increment size
// int &size means pass by reference — size++ actually updates the caller.
// Without &, size++ would be thrown away (pass by value).
void insert_name(string names[], int &size, string new_name) {
    int loc = size;                      // default: insert at end
    for (int i = 0; i < size; i++) {
        if (new_name < names[i]) {       // alphabetically before names[i]?
            loc = i;
            break;
        }
    }
    for (int i = size - 1; i > loc; i--)  // shift right to make room
        names[i+1] = names[i];
    names[loc] = new_name;
    size++;                              // updates caller because of &
}

// ── CONCEPT 20: Delete from array ────────────────────────────
// Use when: removing an element and closing the gap.
// Strategy: shift everything left starting from loc.
//   Before: [A, B, C, D, E]  delete index 1 (B)
//   After:  [A, C, D, E, E]  then num_st-- hides last slot
// int &num_st — must be reference so the size decrease sticks.
void delete_first(string names[], int &num_st, int loc) {
    for (int i = loc; i <= num_st - 2; i++)
        names[i] = names[i+1];   // shift left
    num_st--;                    // shrink logical size
}

// ── CONCEPT 21: Vectors ───────────────────────────────────────
// Use when: you need an array but don't know the size at compile time.
// Vectors are resizable arrays — the key advantage over plain arrays.
// Two types to know:
//   Static array:  int arr[20]       size fixed at compile time
//   Vector:        vector<int> b     size can grow/shrink at runtime
//
// Needs #include <vector>
// vector<int> b;           empty vector, size 0
// vector<int> b(n);        vector of n elements (uninitialized)
// vector<int> b(n, 0);     vector of n elements all set to 0
// b.push_back(x);          add x to the end, size grows by 1
// b.size();                returns current number of elements
// b[i];                    access element at index i (same as array)
#include <vector>

// Pass by reference (&v) — avoids copying the whole vector.
// Without &, C++ copies every element into the function (slow + wasteful).
// This applies to arrays too but vectors make it more obvious.
// using namespace std means you don't have to write std::cout,
// std::vector, std::cin etc. — std is the standard library namespace,
// a namespace is just a named container that groups related code
// to avoid name conflicts.
void print_vec(vector<int> &v) {
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
    cout << endl;
}

void vectorDemo() {
    cout << "\n-- Vector Demo --\n";
    int n;
    cout << "Enter vector length: "; cin >> n;
    vector<int> b;
    cout << "Size before: " << b.size() << endl;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b.push_back(x);   // grows automatically
    }
    cout << "Size after: " << b.size() << endl;
    print_vec(b);
}

// ── CONCEPT 22: Vector of vectors (2D / matrix) ───────────────
// Use when: you need a grid, table, or matrix.
// vector<vector<int>> A   is a vector where each element is itself a vector.
// Think of it as: A[row][col]
//
// Three ways to declare and initialize:
//   Option 1 — declare + initialize in one line:
//     vector<vector<int>> A(n, vector<int>(n, 0));
//   Option 2 — declare first, then resize with loops (clearest):
//     vector<vector<int>> A;
//     A.resize(n);
//     for (int i = 0; i < n; i++) A[i].resize(n);
//   Option 3 — declare first, resize in one line:
//     A.resize(n, vector<int>(n, 0));

void print_matrix(vector<vector<int>> &A) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++)
            cout << A[i][j] << " ";
        cout << endl;   // newline after each row
    }
}

void matrixDemo() {
    cout << "\n-- Matrix Demo (vector of vectors) --\n";
    int n; cout << "Enter n: "; cin >> n;
    vector<int> b(n);
    vector<vector<int>> A(n, vector<int>(n, 0));
    cout << "Enter vector: ";
    for (int i = 0; i < n; i++) cin >> b[i];
    cout << "Enter matrix row by row: ";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> A[i][j];
    print_vec(b);
    print_matrix(A);
}

// ── CONCEPT 23: Adjacency matrix (graphs) ────────────────────
// Use when: representing a graph (network of nodes and edges).
// Graph = set of nodes (vertices) + set of connections (edges).
// Adjacency matrix: A[i][j] = 1 if edge exists between node i and j,
//                             0 if no connection.
// For Opinion Diffusion project:
//   Each node = a voter with opinion 0 or 1
//   Each edge = friendship/connection between voters
//   Each step: voter adopts majority opinion of neighbors,
//              OR randomly picks one friend and copies their opinion.
//   Stop when: no changes occur, one opinion dominates, or time runs out.
//
// Example 4-node graph:
//   Node 0 connects to 1 and 2
//   Node 1 connects to 0 and 3
//   Adjacency matrix:
//     [0][1][2][3]
//  0 [ 0, 1, 1, 0 ]
//  1 [ 1, 0, 0, 1 ]
//  2 [ 1, 0, 0, 0 ]
//  3 [ 0, 1, 0, 0 ]
//
// vector<vector<int>> adj(n, vector<int>(n, 0));
// adj[0][1] = 1; adj[1][0] = 1;  // undirected: set both directions

// ── CONCEPT 24: Pointers ─────────────────────────────────────
// A variable has two things: a VALUE and an ADDRESS in memory.
// int j = 5       → value is 5, stored at some address e.g. 0x77
// &j              → gives the ADDRESS of j (same & as pass by reference)
// int* p          → p is a POINTER: a variable that stores an address
// p = &j          → p now holds the address of j (p "points to" j)
// *p              → dereference: get the VALUE at the address p holds
// *p = 10         → go to that address and change the value there
//
// int* p   → pointer (holds address, can be reassigned)
// int& r   → reference (alias for existing variable, set once at init)
// int  j   → regular variable (holds value directly)
//
// For arrays:
//   int b[10]  → b is already a pointer to b[0]
//   *b         → same as b[0] (value at first element)
//   &b         → address of the whole array
//   int** q    → pointer to a pointer (used for 2D arrays)

// ── CONCEPT 25: Dynamic memory allocation ────────────────────
// Use when: you don't know the size of an array until runtime.
// Normal array:   int freq[100]        size fixed at compile time
// Dynamic array:  int* freq = new int[num_sym]   size set at runtime
//
// new allocates memory on the HEAP (persists until you delete it).
// Static arrays live on the STACK (auto-cleaned when scope ends).
// Always delete[] when done to avoid memory leaks.
//
// *(freq + i) is identical to freq[i] — pointer arithmetic.
// freq + i moves the pointer i slots forward in memory.

void dynamicArrayDemo() {
    cout << "\n-- Dynamic Allocation --\n";
    int* freq = NULL;
    int num_sym;
    cout << "Enter number of symbols: "; cin >> num_sym;
    freq = new int[num_sym];               // allocate at runtime
    for (int i = 0; i < num_sym; i++)
        cin >> *(freq + i);                // same as freq[i]
    for (int i = 0; i < num_sym; i++)
        cout << freq[i] << " ";
    cout << endl;
    delete[] freq;                         // free memory — always do this
}

// ── CONCEPT 26: Structs ───────────────────────────────────────
// Use when: grouping related variables of different types together.
// Like a class in Java/Python but with no methods (just data).
// Access fields with dot notation: MyAddress.city
// Access via pointer with arrow: z->city (same as (*z).city)

struct addr {
    int house_num;
    string street;
    string city;
};

struct GB {
    string name;
    int scores[5];
};

// ── CONCEPT 27: Linked list using pointers + structs ─────────
// Use when: you need a list that grows/shrinks without shifting elements.
// Each node holds a value AND a pointer to the next node.
// Last node's next = NULL (marks the end).
//
// Tradeoff vs array/vector:
//   Array/vector: fast index access (b[i]), slow insert/delete (shifting)
//   Linked list:  slow index access (must walk), fast insert/delete
//   "Cost of entry" = you must traverse from the start to reach any node
//
// new node  → allocates a node on the heap
// ->        → arrow operator: access field through a pointer
//             temp->val  is same as  (*temp).val
//
// How the list 1 → 2 → 4 is built below:
//   Step 1: temp=new node, val=1, first=temp, last=temp
//   Step 2: temp=new node, val=2, first->next=temp, last=temp
//   Step 3: temp=new node, val=4, last->next=temp, last=temp
//   Result: first → [1|next] → [2|next] → [4|NULL]

struct node {
    int val;
    node* next = NULL;   // NULL means no next node (end of list)
};

void linkedListDemo() {
    cout << "\n-- Linked List --\n";
    node *first, *temp, *last;

    // Node 1
    temp = new node;
    temp->val = 1;
    first = temp;
    last = temp;

    // Node 2
    temp = new node;
    temp->val = 2;
    last->next = temp;   // link previous last to new node
    last = temp;

    // Node 4
    temp = new node;
    temp->val = 4;
    last->next = temp;
    last = temp;

    // Direct access (only works if you know structure ahead of time)
    cout << first->val << endl;            // 1
    cout << first->next->val << endl;      // 2
    cout << first->next->next->val << endl;// 4

    // Walk the list with a while loop (standard traversal pattern)
    // NOTE: temp is currently at last node (val=4), rewind to first
    temp = first;
    while (temp != NULL) {
        cout << temp->val << endl;
        temp = temp->next;   // advance to next node
    }

    // Cleanup — delete each node to avoid memory leak
    temp = first;
    while (temp != NULL) {
        node* next = temp->next;
        delete temp;
        temp = next;
    }
}

void structDemo() {
    cout << "\n-- Structs --\n";

    // Gradebook struct
    GB grades[3];
    grades[0].name = "Mohammad";
    grades[0].scores[0] = 23;
    grades[0].scores[1] = 33;
    grades[1].name = "Adam";
    grades[1].scores[0] = 30;
    grades[1].scores[1] = 38;

    // Address struct + pointer to struct
    addr MyAddress;
    MyAddress.house_num = 1256;
    MyAddress.street = "37th Street";
    MyAddress.city = "Los Angeles";
    cout << MyAddress.house_num << ", " << MyAddress.street << endl;
    cout << "Address of object: " << &MyAddress << endl;

    addr* z = &MyAddress;
    cout << "z (pointer): " << z << endl;          // address
    cout << "z->city: " << z->city << endl;         // arrow operator
    cout << "(*z).city: " << (*z).city << endl;     // same thing
    cout << "Address of field: " << &(MyAddress.street) << endl;
}

void pointerDemo() {
    cout << "\n-- Pointer Basics --\n";
    int j = 5;
    double a[5] = {0, 1, 2, 3, 4};

    // Array name IS a pointer to first element
    cout << "a        = " << a        << endl; // address of a[0]
    cout << "a[0]     = " << a[0]     << endl; // value 0
    cout << "&a[0]    = " << &a[0]    << endl; // address of a[0]
    cout << "&a[1]    = " << &a[1]    << endl; // 8 bytes later (double=8)
    cout << "*a       = " << *a       << endl; // same as a[0]

    // Pointer arithmetic
    double* g = a;
    cout << "g+3      = " << g+3      << endl; // address 3 slots forward
    cout << "*(g+3)   = " << *(g+3)   << endl; // same as g[3] = 3
    cout << "g[3]     = " << g[3]     << endl; // same as *(g+3)
    cout << "*(g)+3   = " << *(g)+3   << endl; // value at g, then +3 = 3

    // Basic pointer to int
    int* p = &j;
    cout << "j        = " << j        << endl; // 5
    cout << "&j       = " << &j       << endl; // address
    cout << "p        = " << p        << endl; // same address as &j
    cout << "*p       = " << *p       << endl; // 5
    *p = 10;
    cout << "j after *p=10: " << j    << endl; // 10 — j itself changed!
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
    cout << f(0) << endl;      // 1.0    (positive — above zero)
    cout << f(0.5) << endl;    // 0.107  (positive — getting close)
    cout << f(0.555) << endl;  // ~0.02  (very close to zero)
    cout << "nchoosek(5,3) = " << nchoosek(5, 3) << endl;  // 10
    cout << "Solution: " << bisection(0, 1) << endl;        // ~0.5671
    return 0;   
    return 0;
}