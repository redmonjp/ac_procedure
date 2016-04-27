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
    vector<int>clique;
    vector<int>edge;
    vector<int>final_edge;
    vector<int>buffer;
    vector<int>::iterator it;
    //hold aggregate data of new cliques
    vector< vector <int> > aggregates;
    //create a copy of the membership array
    vector<vector<bool> > membership_array_copy;
    //resize it and set it all to false
    membership_array_copy.resize(membership_array.size(), vector<bool>(membership_array.size(), false));
    
    cout<<endl<<"Starting ac_procedure";
    for (int i=1; i<membership_array.size(); i++) {
        for (int j=1; j<membership_array.size(); j++) {
            //clear the clique and the edge for the new loop
            clique.clear();
            edge.clear();
            final_edge.clear();
            aggregates.clear();
            aggregates = maximal_cliques;
            //where is it false
            if (membership_array[i][j] == false && i!=j && membership_array_copy[j][i]!=true) {
                iterations++;
                cout<<endl<<"Edge #"<<iterations<<" will add edge ("<<i<<","<<j<<")";
                //keep the (x,y) coordinate that is being added so it can be taken out
                new_edge = make_pair(i, j);
                //push the two numbers onto the vector
                edge.push_back(i);
                edge.push_back(j);
                sort(edge.begin(), edge.end());
                //set the new edge to true
                membership_array[new_edge.first][new_edge.second] = true;
                //add the edge into the copy of the array so we can see if it has been tested yet
                membership_array_copy[new_edge.first][new_edge.second] = true;
                //print out the modified array
                print_matrix(membership_array);
                
                //get each edge from the list
                for (int k=0; k<maximal_cliques.size(); k++) {
                    //clear the buffer that is holding results from the intersection
                    buffer.clear();
                    //set it to the local edge so we can see if
                    clique = maximal_cliques.at(k);
                    sort(clique.begin(), clique.end());
                    set_intersection(edge.begin(), edge.end(), clique.begin(), clique.end(), back_inserter(buffer));
                    if (!(buffer.empty())) {
                        cout<<"There is something in the intersection - '";
                        print_clique(buffer);
                        cout<<"'"<<endl;
                        //print the clique that is involved in this intersection
                        cout<<"The solution will involve clique:'";
                        print_clique(clique);
                        cout<<"'"<<endl;
                        //if there is nothing in the final edge yet we can just set the final
                        //edge to the first clique that is involved in the aggregate
                        if (final_edge.empty()) {
                            final_edge = clique;
                            cout<<"Final edge is empty - lets put '";
                            print_clique(final_edge);
                            cout<<"' in there!"<<endl;
                        }
                        //if there is something is the edge we need to take the intersection
                        //of what is already there with whatever we have as a clique
                        else if (!(final_edge.empty())){
                            //find some space to keep what we have as our work-in-progress final edge
                            buffer.clear();
                            buffer = final_edge;
                            //clear what was in final edge so we can fill it with new stuff
                            final_edge.clear();
                            //sort what we have
                            sort(buffer.begin(), buffer.end());
                            set_intersection(clique.begin(), clique.end(), buffer.begin(), buffer.end(), back_inserter(final_edge));
                            cout<<"So we took the intersection and now we are left with - '";
                            print_clique(final_edge);
                            cout<<"' as our final intersection"<<endl;
                        }
                    }
                }
                
                //clear the buffer so we can do the same swap we did above
                buffer.clear();
                clique.clear();
                buffer = final_edge;
                //clear what was in the final edge so we can fill it with the real thing
                final_edge.clear();
                //sort what we have
                sort(buffer.begin(), buffer.end());
                //find the union of our edge and the intersection of each edge involved
                set_union(edge.begin(), edge.end(), buffer.begin(), buffer.end(), back_inserter(final_edge));
                cout<<"We took the union, what is the new edge we have? - '";
                print_clique(final_edge);
                cout<<"'"<<endl;
                //sort the final edge
                sort(final_edge.begin(), final_edge.end());
                //check to see if any of the old edges are a subset of the old
                for (int k=0; k<maximal_cliques.size(); k++) {
                    clique = maximal_cliques.at(k);
                    if (includes(final_edge.begin(), final_edge.end(), clique.begin(), clique.end())) {
                        cout<<"The edge '";
                        print_clique(clique);
                        cout<<"' is a subset of '";
                        print_clique(final_edge);
                        cout<<"' so, exclude it"<<endl;
                        aggregates.erase(aggregates.begin()+k);
                    }
                    clique.clear();
                }
                //push the new edge onto the set of maximal cliques
                aggregates.push_back(final_edge);
                //print out the new set
                cout<<"The new aggregate set of maximal cliques when adding in the edge {";
                cout<<new_edge.first<<","<<new_edge.second<<"} is - ";
                print_maximal_cliques(aggregates);
                //remove the edge that we added so we can start fresh on the next loop
                membership_array[new_edge.first][new_edge.second] = false;
            }
        }
    }
}

#endif
