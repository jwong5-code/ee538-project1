// ═══════════════════════════════════════════════════════════════
// EXAM CHEAT SHEET: Pointers, Linked Lists, Stacks, Queues
// ═══════════════════════════════════════════════════════════════

#include <iostream>
using namespace std;

// ── QUICK REFERENCE: * and & ─────────────────────────────────
// int  j       → regular variable, holds a value
// int* p       → pointer, holds an ADDRESS (p = &j)
// int& r = j   → reference, alias for j (same memory, different name)
// *p           → dereference: get VALUE at address p holds
// &j           → address-of: get ADDRESS of variable j
// node* elem   → elem is a pointer to a node (most common in lists)
// node *elem   → identical, just different spacing convention
//
// -> vs .
// obj.field    → access field via object directly
// ptr->field   → access field via pointer (same as (*ptr).field)
//
// Global vs local:
// node* start = NULL  declared outside main = global, visible everywhere
// node* start = NULL  declared inside main  = local, only in that scope
// Global is convenient for linked lists so helper functions see it,
// but risky in large programs (any function can accidentally change it)

// ── CONCEPT 28: Linked list — struct definition ───────────────
// Always need two fields: value + pointer to next node.
// Default values (= 0, = NULL) prevent garbage data bugs.
// node* next = NULL is critical — always assume next is NULL
// unless you have proof it points somewhere valid.
// Can we use node instead of node*?
//   NO — a node containing a node would be infinitely large.
//   node* next is a fixed-size pointer (8 bytes), not a full node.
struct node {
    int val = 0;
    node* next = NULL;
};

// ── CONCEPT 29: Insert at end ─────────────────────────────────
// Use when: building a list in order (first inserted = first in list).
// Returns new last so caller can keep track of the tail.
// First insertion: start and last both point to the only node.
// Subsequent: attach to last->next, advance last.
// start is global here — visible inside insertNode without passing it.
node* start = NULL;

node* insertNode(node* last, int num) {
    node* new_node = new node;
    new_node->val = num;
    if (start == NULL) {       // first node ever
        start = new_node;
        last = new_node;
    } else {
        last->next = new_node; // attach to end
        last = last->next;     // advance last
    }
    return last;               // caller must save this
}

// ── CONCEPT 30: Insert at start ──────────────────────────────
// Use when: you want newest element at the front (like a stack push).
// Steps:
//   1. Create new node
//   2. new_node->next = current start  (link to old list)
//   3. start = new_node               (new node is now the front)
// Returns new start — caller must save it.
// Visualized:
//   Before: start → [2] → [3] → NULL
//   Insert 1 at start:
//   new_node → [1], new_node->next = [2]
//   After:  start → [1] → [2] → [3] → NULL
node* insertNodeStart(node* start, int num) {
    node* new_node = new node;
    new_node->val = num;
    new_node->next = start;    // point to old first node
    start = new_node;          // new node is now first
    return start;
}

// ── CONCEPT 31: Delete at start ──────────────────────────────
// Use when: removing the front element (like a stack pop or queue dequeue).
// Steps:
//   1. Save start in temp (so we can delete it)
//   2. Advance start to start->next
//   3. Delete temp
// Always check NULL first — deleting from empty list crashes.
node* deleteNodeStart(node* start) {
    if (start == NULL) return NULL;
    node* temp = start;        // remember old start
    start = start->next;       // move start forward
    delete temp;               // free memory
    return start;
}

// ── CONCEPT 32: Delete at end ────────────────────────────────
// Use when: removing the last element.
// Harder than delete at start — must find the second-to-last node.
// Walk until temp->next->next == NULL (temp is then second-to-last).
// Three cases:
//   1. Empty list → return NULL
//   2. One node   → delete it, return NULL
//   3. Multiple   → walk to second-to-last, delete last
// BUG in original code: deletes temp (second-to-last) instead of last.
// Fixed below.
node* deleteNodeEnd(node* start) {
    if (start == NULL) return NULL;
    if (start->next == NULL) {     // only one node
        delete start;
        return NULL;
    }
    node* temp = start;
    while (temp->next->next != NULL)
        temp = temp->next;         // stop at second-to-last
    delete temp->next;             // FIX: delete LAST node, not temp
    temp->next = NULL;             // second-to-last now points to NULL
    return start;
}

// ── CONCEPT 33: Search and delete ────────────────────────────
// Use when: removing a specific value from anywhere in the list.
// Key idea: you need PREV (the node before the one to delete).
// Why? To relink: prev->next = toDel->next, then delete toDel.
// Draw this out — always:
//   Before: [prev] → [toDel] → [next]
//   After:  [prev] → [next]   (toDel removed)
//
// Three cases to handle:
//   1. Empty list
//   2. Match is at start (use deleteNodeStart)
//   3. Match is in middle/end (walk with prev tracker)
//
// BUG in original: while loop never advances temp → infinite loop.
// Fixed: temp = temp->next added to while loop.
// BUG in original: temp->next->val crashes if temp->next is NULL.
// Fixed: check temp->next != NULL before accessing its val.
node* searchDeleteNode(node* start, int num) {
    if (start == NULL) return NULL;
    if (start->val == num)             // case 2: match at front
        return deleteNodeStart(start);

    node* prev = NULL;
    node* temp = start;
    while (temp->next != NULL) {       // FIX: guard against NULL->val
        if (temp->next->val == num) {
            prev = temp;
            break;
        }
        temp = temp->next;             // FIX: must advance or infinite loop
    }
    if (prev != NULL) {
        node* toDel = prev->next;
        prev->next = toDel->next;      // relink around deleted node
        delete toDel;
    }
    return start;
}

// ── CONCEPT 34: Print list ────────────────────────────────────
// Standard traversal pattern — use this for ANY walk through a list.
// temp = start keeps start safe (never move start itself).
// Print NULL at end to show where list terminates.
void printList(node* start) {
    node* temp = start;
    while (temp != NULL) {
        cout << temp->val << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

// ── CONCEPT 35: Stack (LIFO) ──────────────────────────────────
// Last In First Out — like a stack of plates.
// Push = insert at start.  Pop = delete from start.
// Use a linked list where front = top of stack.
// peek() returns top value without removing it.
// isEmpty() always check before pop/peek to avoid crash.
//
// Visualized — push 1, push 2, push 3:
//   After push 1:  top → [1] → NULL
//   After push 2:  top → [2] → [1] → NULL
//   After push 3:  top → [3] → [2] → [1] → NULL
//   pop():         top → [2] → [1] → NULL  returns 3

node* stackTop = NULL;

void push(int val) {
    stackTop = insertNodeStart(stackTop, val);
}

int pop() {
    if (stackTop == NULL) { cout << "Stack empty\n"; return -1; }
    int val = stackTop->val;
    stackTop = deleteNodeStart(stackTop);
    return val;
}

int peek() {
    if (stackTop == NULL) { cout << "Stack empty\n"; return -1; }
    return stackTop->val;
}

// ── CONCEPT 36: Queue (FIFO) ──────────────────────────────────
// First In First Out — like a line at a store.
// Enqueue = insert at end.  Dequeue = delete from start.
// Need to track both front AND back for efficiency.
// (If you only track front, finding the end requires walking whole list.)
//
// Visualized — enqueue 1, 2, 3:
//   front → [1] → [2] → [3] ← back
//   dequeue(): removes 1, returns 1
//   front → [2] → [3] ← back

node* qFront = NULL;
node* qBack  = NULL;

void enqueue(int val) {
    node* new_node = new node;
    new_node->val = val;
    if (qBack == NULL) {           // empty queue
        qFront = new_node;
        qBack  = new_node;
    } else {
        qBack->next = new_node;    // attach to end
        qBack = new_node;          // advance back
    }
}

int dequeue() {
    if (qFront == NULL) { cout << "Queue empty\n"; return -1; }
    int val = qFront->val;
    node* temp = qFront;
    qFront = qFront->next;
    if (qFront == NULL) qBack = NULL;  // queue now empty
    delete temp;
    return val;
}

// ── SUMMARY TABLE ─────────────────────────────────────────────
// Structure   | Order     | Insert    | Remove    | Use case
// ------------|-----------|-----------|-----------|------------------
// Linked list | any       | any pos   | any pos   | general flexible list
// Stack       | LIFO      | front     | front     | undo, recursion
// Queue       | FIFO      | back      | front     | scheduling, BFS
//
// All three share the same node struct — difference is only in
// which end you insert/remove from.

int main() {
    // Linked list demo
    cout << "=== Linked List ===\n";
    int sz; cout << "How many nodes: "; cin >> sz;
    for (int i = 0; i < sz; i++) {
        int num; cin >> num;
        start = insertNodeStart(start, num);
        printList(start);
    }
    start = deleteNodeEnd(start);
    cout << "After delete end: "; printList(start);

    // Stack demo
    cout << "\n=== Stack (LIFO) ===\n";
    push(1); push(2); push(3);
    printList(stackTop);
    cout << "Pop: " << pop() << endl;
    cout << "Peek: " << peek() << endl;
    printList(stackTop);

    // Queue demo
    cout << "\n=== Queue (FIFO) ===\n";
    enqueue(1); enqueue(2); enqueue(3);
    printList(qFront);
    cout << "Dequeue: " << dequeue() << endl;
    printList(qFront);

    return 0;
}