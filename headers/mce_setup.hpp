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
 the size of the membership_array. From that point each edge in 
 pairs vector is manipulated and packed into the correct data
 structures
 
 Dictionary of Variables:
 membership_array-
 type: vector <vector <bool> >
 Description: input to function, contains the matrix representation
 of the graph description file - ie what edges are valid
 edge_vector-
 type: vector <vector <int> >
 Description:input to function, contains each edge that is descibed
 in the graph description file
 primal_edge_vector-
 type:vector< pair<int, int> >
 Description: input to function, contains the primal pairs of each edge
 in the graph description file
 vertices-
 type:vector<int>
 Description: input to function, contains the number of vertices 
 i,j,k,l,z,start,x,y -
 type:int 
 Description: local to function, counters in some manner
 num_of_vertices
 type:int
 Description: local to function, contains the int value of the number
 of vertices described in the graph description file
 num_of_tuples
 type:int
 Description: local to function, contains the int value of the number
 of tuples (edges) described in the graph description file
 pair_exists
 type:bool
 Description: local to function, tells weather the inverse of the pair
 exists - prevents duplicates 
 edge-
 type:vector<int>
 Description: local to function, contains the vector of the single edge
 we are working with
 primal_edge_pair
 type:pair<int,int>
 Description: local to function, contains the single pair we are working
 with
 pairs-
 type:vector<string>
 Description: local to function, contains the vector of each edge in the
 file
 readfile(argv[1])-
 type:ifstream
 Description: local to function, used to read in the file data
 convert-
 type:stringstream
 Description: local to function, stringstream variable used as the 
 buffer to convert 
 graph_str-
 type:str
 Description: local to function, used to hold the single string that 
 we are working with
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
    int num_of_vertices=0;
    int num_of_tuples=0;
    bool pair_exists = false;
    set<int>set_of_edge;
    vector<int>edge;
    pair<int, int>primal_edge_pair;
    vector<string>pairs;
    ifstream read_file(argv[1]);
    stringstream convert;
    string graph_str;
    
    //check the number of arguments - if the number is not correct then let 'em know
    //and get out of here
    if (argc != 2) {
        cout<<"Incorrect number of arguments given to program"<<endl;
        exit(1);
    }
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
    
    //get the string that represents the number of vertices
    //stuff it into an int
    convert<<pairs.at(z);
    convert>>num_of_vertices;
    convert.clear();
    //cout<<endl<<"Number of vertices: "<<num_of_vertices<<endl;
    
    //Call CreateSetofVertices from bk.hpp
    CreateSetofVertices(num_of_vertices, vertices);
    
    //resize the array to match the number of vertices and set it all to false
    membership_array.resize(num_of_vertices+1, vector<bool>(num_of_vertices+1, false));
    num_of_tuples = (int)pairs.size();
    
    //as long as we still have tuples
    //z is the index into the vector holding tuples
    //increment to get the next tuple and loop until we are at the end
    while (true) {
        set_of_edge.clear();
        //get the next tuple
        z++;
        i=0;
        //check to see if we are at the end 'z+1' to account for zero index
        if (z>= num_of_tuples) {
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
                if (x>num_of_vertices) {
                    cout<<"The value "<<x<<" for x is invalid"<<endl;
                    cout<<"Check the graph description file for errors"<<endl;
                    exit(1);
                }
                if (y>num_of_vertices) {
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
    
    cout<<endl<<"User Input Cliques"<<endl;
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
    //sort the edges!
    sort(maximal_cliques.begin(), maximal_cliques.end());
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

//nested for loops to print the hyperedges
void print_clique(vector<int> clique){
    vector<int>::iterator it;
    
    cout<<"{";
    for (it=clique.begin(); it!=clique.end(); ++it){
        if (it != clique.begin()){
            cout << ",";
        }
        cout<<*it;
    }
    cout<<"}";
}
#endif /* mce_setup_h */
