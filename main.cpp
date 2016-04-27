#include "headers/mce_setup.hpp"
#include "headers/ac.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

int main(int argc, const char * argv[]) {
    //vector that will hold the edges in the hypergraph
    vector<vector <int> >edge_vector;
    //vector to hold the pairs of the primal graph
    vector<pair<int, int> >primal_edge_vector;
    //the 2d vector that will be used to hold the membership array of the graph
    vector<vector<bool> > membership_array;
    //vector to hold vertices
    vector<int> vertices;
    vector < int > R;
    vector < int > X;
    vector< vector <int> > maximal_cliques;
    //call read_file - read in the description file and update membership array
    read_file(membership_array, edge_vector, primal_edge_vector, vertices, argc, argv);
    //call print_matrix - print the membership array in matrix form
    print_matrix(membership_array);
    //call print_primal_edge_vector - print the vector containing the edges in the primal graph
    //print_primal_edge_vector(primal_edge_vector);
    //call print_edge_vector - print the vector containing each hyperedge line by line
    print_edge_vector(edge_vector);
    //get all the maximal cliques for the given graph
    GetAllMaxCliques(primal_edge_vector, maximal_cliques, R,vertices, X );
    //check to see if they are the same
    bool same_cstructure = CheckCStructure(edge_vector, maximal_cliques);
    //print maximal cliques
    print_maximal_cliques(maximal_cliques);
    if (same_cstructure) {
        cout<<endl<<"The bk_algorithm has returned that the set of maximal cliques provided ";
        cout<<"is correct for this graph."<<endl;
    }
    else if (!same_cstructure){
        cout<<endl<<"The bk_algorithm has returned that the set of maximal cliques provided ";
        cout<<"is NOT correct for this graph."<<endl;
    }
    //call the ac_procedure
    ac_procedure(maximal_cliques, membership_array);
    
}
