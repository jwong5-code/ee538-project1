#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/********************DO NOT EDIT**********************/
// Function prototype. Defined later.
void read_opinions(string filename); // reads file into opinions vector and updates total_nodes as needed
void read_edges(string filename); // reads file into edge_list, defined later
void build_adj_matrix(); // convert edge_list to adjacency matrix

int total_nodes = 0; // We keep track of the total number of nodes based on largest node id.


/****************************************************************/

/******** Create adjacency matrix and vector of opinions */
// simple vector to hold each node's opinion (0 or 1)
std::vector<int> opinions;

// global adjacency matrix initialized later


// NEW
// Adjacency list: adj_list[i] stores all nodes that influence node i.
// More space-efficient than a matrix for sparse graphs: O(n+e) vs O(n^2)
std::vector<std::vector<int>> adj_list;

double calculate_fraction_of_ones()
{
   double count = 0;
    for(int i = 0; i < opinions.size(); i++)
    {
         if(opinions[i] == 1) {
            count++;
         } 
    }
    return count / (opinions.size() * 1.0); 
}

// NEW
// Only iterates over actual neighbors, not all nodes. O(degree) vs O(n).
int get_majority_friend_opinions(int node)
{
    int one = 0;
    int zero = 0;

    for (int j = 0; j < adj_list[node].size(); j++) {
        int neighbor = adj_list[node][j];
        if (opinions[neighbor] == 1) {
            one++;
        }
            else {
                zero++;
            }
    }

    if (one > zero) {
        return 1;
    } 
    else {
        return 0;
    }
}

// Calculate new opinions for all voters and return if anyone's opinion changed
bool update_opinions()
{
    bool changed = false;
    vector<int> new_opinions = opinions;

    for (int i = 0; i < total_nodes; i++) {

        int new_op = get_majority_friend_opinions(i);
        new_opinions[i] = new_op;

        if (new_op != opinions[i]) {
            changed = true;
        }
    }

    opinions = new_opinions;
    return changed;
}

int main() {
    // no preallocation; vectors grow on demand

    // Read input files
    read_opinions("opinions.txt"); 
    read_edges("edge_list.txt");

    
    cout << "Total nodes: " << total_nodes << endl;
    
    // Run simulation
    int max_iterations = 30;
    int iteration = 0;
    bool opinions_changed = true;
    
    // Print initial state
    cout << "Iteration " << iteration << ": fraction of 1's = " 
         << calculate_fraction_of_ones() << endl;
    
    /// (6)  //////////////////////////////////////////////
    while(opinions_changed && iteration < max_iterations)
        {
            iteration++;
            opinions_changed = update_opinions();
            cout << "Iteration " << iteration << ": fraction of 1's = " 
         << calculate_fraction_of_ones() << endl;
        }
    

    ////////////////////////////////////////////////////////
    // Print final result
    double final_fraction = calculate_fraction_of_ones();
    cout << "Iteration " << iteration << ": fraction of 1's = " 
         << final_fraction << endl;
    
    if(final_fraction == 1.0)
        cout << "Consensus reached: all 1's" << endl;
    else if(final_fraction == 0.0)
        cout << "Consensus reached: all 0's" << endl;
    else
        cout << "No consensus reached after " << iteration << " iterations" << endl;
    
    return 0;
}


/*********** Functions to read files **************************/ 

// Read opinion vector from file.
void read_opinions(string filename)
{
    ifstream file(filename);
    int id, opinion;
    while(file >> id >> opinion)
    {
        opinions.push_back(opinion);
        if(id >= total_nodes) total_nodes = id+1;
    }
    file.close();
}

// NEW
// Builds adjacency list directly from file, eliminating need for edge_list
// and build_adj_matrix. For sparse networks this avoids O(n^2) space overhead.
void read_edges(string filename)
{
    ifstream file(filename);
    int source, target;
    
    
    while(file >> source >> target)
    {
        if (target >= adj_list.size()) {
            adj_list.resize(target + 1);
        }
        adj_list[target].push_back(source);
    }
    file.close();
}

/********************************************************************** */