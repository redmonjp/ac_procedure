#ifndef ac_h
#define ac_h
#include "mce_setup.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>

using namespace std;

void ac_procedure(vector<pair<int, int> >primal_edge_vector,vector< vector <int> > maximal_cliques, vector<vector<bool> > membership_array){
    int iterations = 0;
    pair<int,int>new_edge;
    vector<int>x_edge;
    vector<int>y_edge;
    vector<int>edge;
    vector<int>::iterator it;
    //create a copy of the membership array 
    vector<vector<bool> > membership_array_copy;
    //resize it and set it all to false
    membership_array_copy.resize(membership_array.size(), vector<bool>(membership_array.size(), false));
    
    cout<<endl<<"Starting ac_procedure";
    for (int i=1; i<membership_array.size(); i++) {
        for (int j=1; j<membership_array.size(); j++) {
            //where is it false
            if (membership_array[i][j] == false && i!=j && membership_array_copy[j][i]!=true) {
                iterations++;
                cout<<endl<<"Edge #"<<iterations<<" will add edge ("<<i<<","<<j<<")";
                //keep the (x,y) coordinate that is being added so it can be taken out
                new_edge = make_pair(i, j);
                //set the new edge to true
                membership_array[new_edge.first][new_edge.second] = true;
                membership_array_copy[new_edge.first][new_edge.second] = true;
                
                print_matrix(membership_array);
                
                //get each edge from the list
                for (int k=0; k<maximal_cliques.size(); k++) {
                    //set it to the local edge so we can see if 
                    edge = maximal_cliques.at(k);
                    
                }
                
                membership_array[new_edge.first][new_edge.second] = false;
            }
        }
    }
    
}

#endif
