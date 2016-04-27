#ifndef mce_setup_h
#define mce_setup_h

#include "bk.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

/**************************************************************
 Function: read_file
 Description: This function is used to read in a user provided
 file that will be passed in argv[1]. The function expects the 
 file to be laid out in a manner that the first line is the 
 number of vertices in graph and every line after that is an 
 edge in the graph. The function reads the given file in, 
 line by line, and then pushes each line onto the pairs vector.
 The first element of the vector is popped off and used to create
 the size of the membership_array.
 
 
 Dictionary of Variables:
 user_input_edges-
 type: vector <vector <int> >
 Description: input to function, contains edges given by user in
 initial input.
 bk_cstructure-
 type: vector <vector <int> >
 Description:input to function, actual c-structure a user may want
 to compare their input to.
 is_cstructure-
 type: boolean
 Description: Intialized to false, stays false if vectors input
 by user are different, changes to true if they are the same.
 *********************************************************************/

//read in the included file and parse it into data structures
void read_file(vector< vector<bool> > &membership_array, vector< vector<int> > &edge_vector, vector< pair<int, int> > &primal_edge_vector, vector<int>&vertices, int argc, const char *argv[]){
    int i=0;
    int j=0;
    int k=0;
    int l=0;
    int z=0;
    int start=0;
    int x=0;
    int y=0;
    int num_of_verticies=0;
    int num_of_tuples=0;
    bool pair_exists = false;
    vector<int>edge;
    pair<int, int>primal_edge_pair;
    vector<string>pairs;
    ifstream read_file(argv[1]);
    stringstream convert;
    string graph_str;
    
    //read the graph description file
    //push it back onto a vector
    if (read_file){
        while (!read_file.eof()) {
            getline (read_file,graph_str);
            pairs.push_back(graph_str);
        }
    }
    else{
        cout << "Couldn't open file\n";
        read_file.close();
        exit(1);
    }
    
    //get the string that represents the number of verticies
    //stuff it into an int
    convert<<pairs.at(z);
    convert>>num_of_verticies;
    convert.clear();
    //cout<<endl<<"Number of verticies: "<<num_of_verticies<<endl;
    
    //Call CreateSetofVertices from bk.hpp
    CreateSetofVertices(num_of_verticies, vertices);

    //resize the array to match the number of verticies and set it all to false
    membership_array.resize(num_of_verticies+1, vector<bool>(num_of_verticies+1, false));
    num_of_tuples = (int)pairs.size();
    
    //as long as we still have tuples
    //z is the index into the vector holding tuples
    //increment to get the next tuple and loop until we are at the end
    while (true) {
        //get the next tuple
        z++;
        i=0;
        //check to see if we are at the end 'z+1' to account for zero index
        if (z+1 >= num_of_tuples) {
            break;
        }
        //take the tuple and put it into a sting to work with
        graph_str = pairs.at(z);
        //move past new lines and brackets
        if(graph_str.at(i) == '{') {
            i++;
        }
        j=i;
        start=i;
        while (graph_str.at(i) != '}') {
            //check to see if we are sitting on a comma
            if (graph_str.at(i) == ',') {
                i++;
            }
            //set the pointer to where we are sitting
            k=i;
            //as long as it isnt a comma or } loop
            while (graph_str.at(k)!=','&&graph_str.at(k)!='}') {
                k++;
            }
            //make a substring of the number
            convert<<graph_str.substr(i,k-i);
            convert>>x;
            convert.clear();
            //since k was incremented to the end - bring i to k
            i=k;
            //set j to the start of the {}
            j=start;
            while (graph_str.at(j) != '}'&&graph_str.at(j) != '\n') {
                //reset our flag
                pair_exists = false;
                //set everything to the start of {}
                l=j;
                //move past the comma
                while (graph_str.at(l)!=','&&graph_str.at(l)!='}') {
                    l++;
                }
                //make a substring of the number
                convert<<graph_str.substr(j,l-j);
                convert>>y;
                convert.clear();
                //check to make sure these places exist
                if (x>num_of_verticies) {
                    cout<<"The value "<<x<<" for x is invalid"<<endl;
                    cout<<"Check the graph description file for errors"<<endl;
                    exit(1);
                }
                if (y>num_of_verticies) {
                    cout<<"The value "<<y<<" for y is invalid"<<endl;
                    cout<<"Check the graph description file for errors"<<endl;
                    exit(1);
                }
                //check to see if the values are the same
                //if they are then dont add the pair to keep out loops
                //else add it
                if (x != y) {
                    membership_array[x][y] = true;
                    //insert each value into the edge - if it is already there is wont show up
                    edge.push_back(x);
                    edge.push_back(y);
                    
                    //check to make sure the (x,y) and (y,x) never show up
                    for (int q=0 ; q<primal_edge_vector.size(); q++) {
                        if (membership_array[y][x] == true) {
                            pair_exists = true;
                        }
                    }
                    //if (y,x) is not in the membership array then put it in as an edge
                    if (!pair_exists) {
                        primal_edge_pair = make_pair(x, y);
                        primal_edge_vector.push_back(primal_edge_pair);
                    }
                }
                else if (x ==y){
                    edge.push_back(x);
                    edge.push_back(y);
                }
                //since l was incremented to the end - bring j to l
                j=l;
                if (graph_str.at(j) == ',') {
                    j++;
                }
            }
        }
        sort( edge.begin(), edge.end() );
        edge.erase( unique( edge.begin(), edge.end() ), edge.end() ); 
       //before we start the next iteration push the new edge onto the vector
        edge_vector.push_back(edge);
        //empty the edge for the next loop
        edge.clear();
    }
}

//nested for loops to print the membership array
void print_matrix(vector< vector<bool> > &membership_array){
    
    cout<<endl<<"Membership Array:";
    for (int i = 1; i < membership_array.size(); i++){
        cout<<endl;
        for (int j = 1; j < membership_array.size(); j++){
            cout << membership_array[i][j]<<" ";
        }
    }
    cout<<endl;
}

//nested for loops to print the hyperedges
void print_edge_vector(vector< vector<int> > &edge_vector){
    vector<int>::iterator it;
    vector<int>edge;
    
    cout<<endl<<"Hyperedges"<<endl;
    //print the hyperedges we found!
    for (int i=0; i<edge_vector.size(); i++) {
        edge = edge_vector[i];
        cout<<"{";
        for (it=edge.begin(); it!=edge.end(); ++it){
            if (it != edge.begin()){
                cout << ",";
            }
            cout<<*it;
        }
        cout<<"}"<<endl;
    }
}

//nested for loops to print the primal edges of the membership array
void print_primal_edge_vector(vector< pair<int, int> > &primal_edge_vector){
    pair<int, int>pair;
    
    cout<<endl<<"Primal Edges:"<<endl;
    //print the hyperedges we found!
    for (int i=0; i<primal_edge_vector.size(); i++) {
        pair = primal_edge_vector.at(i);
        cout<<"{";
        cout<<pair.first <<","<<pair.second;
        cout<<"}"<<endl;
    }
}

//nested for loops to print the hyperedges
void print_maximal_cliques(vector< vector<int> > &maximal_cliques){
    vector<int>::iterator it;
    vector<int>edge;
    
    cout<<endl<<"Maximal Cliques in Graph"<<endl;
    //print the hyperedges we found!
    for (int i=0; i<maximal_cliques.size(); i++) {
        edge = maximal_cliques[i];
        cout<<"{";
        for (it=edge.begin(); it!=edge.end(); ++it){
            if (it != edge.begin()){
                cout << ",";
            }
            cout<<*it;
        }
        cout<<"}"<<endl;
    }
}
#endif /* mce_setup_h */
