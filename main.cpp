#include "headers/mce_setup.hpp"
#include "headers/ac.hpp"
#include "headers/rc.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

int main(int argc, const char * argv[]) {
	vector< vector <vector <int> > > refinements;
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
	char y_or_n;
    //call read_file - read in the description file and update membership array
    read_file(membership_array, edge_vector, primal_edge_vector, vertices, argc, argv);
    //call print_matrix - print the membership array in matrix form
	cout<<"Do you want to print out the adjacency matrix for the graph data you input? (Y or N): ";
	cin>>y_or_n;
	if(y_or_n == 'Y' ||y_or_n == 'y'){		
		print_matrix(membership_array);
	}
    //call print_primal_edge_vector - print the vector containing the edges in the primal graph
	cout<<"Would you like to print out the set of primal edges for the graph data you input? (Y or N): ";
	cin>>y_or_n;
	if(y_or_n == 'Y' ||y_or_n == 'y')		
	{
		print_primal_edge_vector(primal_edge_vector);
	}
    //call print_edge_vector - print the vector containing each hyperedge line by line
	cout<<"Would you like to print out the set of edges as they were in the input file? (Y or N): ";
	cin>>y_or_n;
	if(y_or_n == 'Y' ||y_or_n == 'y')		
	{
		print_edge_vector(edge_vector);
    }
	cout<<"Would you like to find the maximal cliques for the graph you input? (Y or N): ";
	cin>>y_or_n;
	if(y_or_n == 'Y' ||y_or_n == 'y')		
	{
		//get all the maximal cliques for the given graph
		GetAllMaxCliques(primal_edge_vector, maximal_cliques, R,vertices, X );
		//print maximal cliques
		print_maximal_cliques(maximal_cliques);
	cout<<"Would you like to compare the cliques you input with the set of maximal cliques? (Y or N): ";
	cin>>y_or_n;
	if(y_or_n == 'Y' ||y_or_n == 'y')		
	{
	//check to see if they are the same
		bool same_cstructure = CheckCStructure(edge_vector, maximal_cliques);
		if (same_cstructure) {
			cout<<endl<<"The bk_algorithm has returned that the set of maximal cliques provided ";
			cout<<"is correct for this graph."<<endl;
		}
		else if (!same_cstructure){
			cout<<endl<<"The bk_algorithm has returned that the set of maximal cliques provided ";
			cout<<"is NOT correct for this graph."<<endl;
			edge_vector = maximal_cliques;
		}
	}
	}	
	cout<<"Would you like to find all immediate aggregates of the graph? (Y or N): ";
	cin>>y_or_n;
	if(y_or_n == 'Y' ||y_or_n == 'y')		
	{
		//call the ac_procedure
		ac_procedure(edge_vector, membership_array);
	}
	cout<<"Would you like to find all refinements of the graph? (Y or N): ";
	cin>>y_or_n;
	if(y_or_n == 'Y' ||y_or_n == 'y')		
	{
		GetRefinements(membership_array, edge_vector, refinements);
	}
}
