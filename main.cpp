#include "mce_setup.hpp"
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
    print_primal_edge_vector(primal_edge_vector);
    //call print_edge_vector - print the vector containing each hyperedge line by line
    print_edge_vector(edge_vector);
    cout<<"Maximal Cliques in graph: "<<endl;
    GetAllMaxCliques(primal_edge_vector, maximal_cliques, R,vertices, X );
    for(int j=0;j<maximal_cliques.size();j++){
	cout<<"{";
	for(int i=0;i<maximal_cliques[j].size();i++){
		cout<<maximal_cliques[j][i]<<" ";
	}
	cout<<"}"<<endl;
    }
    bool same_cstructure = CheckCStructure(edge_vector, maximal_cliques);
	cout<<same_cstructure<<endl;
}
