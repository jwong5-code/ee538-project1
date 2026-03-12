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
std::vector<std::vector<int>> adj;

// edge list: each row contains {source, target}
// Edge - connection
// Vertice - Points
std::vector<std::vector<int>> edge_list;

void build_adj_matrix()
{
    // Adjancy matrix is initialized to 0's by default or switched to 1's if edge exists.
    adj.resize(total_nodes, std::vector<int>(total_nodes, 0));


    // Go through each edge in the edge list
    for (int i = 0; i < edge_list.size(); i++) {
        int source = edge_list[i][0];
        int target = edge_list[i][1];
        adj[source][target] = 1; 
    }
    
}

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

// For a given node, count majority opinion among its neighbours. Tie -> 0.
// Look at all neighbors within adj matrix
// Count how many have opinion 1 vs 0
int get_majority_friend_opinions(int node)
{
    int one = 0;
    int zero = 0;

    for (int j = 0; j < total_nodes; j++) {
        if (adj[j][node] == 1) {
            if (opinions[j] == 1) {
                one++;
            } else {
                zero++;
            }
        }
    }

    if (one > zero) return 1;
    else return 0; // Tie or more zeros
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

    // convert edge list into adjacency matrix once we know total_nodes
    build_adj_matrix();
    
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

// Read edge list from file and update total nodes as needed.
void read_edges(string filename)
{
    ifstream file(filename);
    int source, target;
    
    while(file >> source >> target)
    {
        edge_list.push_back({source, target});
        if(source >= total_nodes) total_nodes = source+1;
        if(target >= total_nodes) total_nodes = target+1;
    }
    file.close();
}

/********************************************************************** */