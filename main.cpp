#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

//read in the included file and parse it into data structures
void read_file(vector< vector<bool> > &membership_array, int argc, const char *argv[]){
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
    cout<<"Number of verticies: "<<num_of_verticies<<endl;
    
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
            //make a substing of the number
            convert<<graph_str.substr(i,k-i);
            convert>>x;
            convert.clear();
            //since k was incremented to the end - bring i to k
            i=k;
            //set j to the start of the {}
            j=start;
            while (graph_str.at(j) != '}'&&graph_str.at(j) != '\n') {
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
                }
                //add it to the membership
                membership_array[x][y] = true;
                //since l was incremented to the end - bring j to l
                j=l;
                if (graph_str.at(j) == ',') {
                    j++;
                }
            }
        }
    }
}

//nested for loops to print the membership array
void print_matrix(vector< vector<bool> > &membership_array){
    for (int i = 1; i < membership_array.size(); i++){
        cout<<endl;
        for (int j = 1; j < membership_array.size(); j++){
            cout << membership_array[i][j]<<" ";
        }
    }
    cout<<"\n"<<endl;
}

int main(int argc, const char * argv[]) {
    //the 2d vector that will be used to hold the membership array of the graph
    vector<vector<bool> > membership_array;
    
    //call read_file - read in the description file and update membership array
    read_file(membership_array, argc, argv);
    //call print_matrix - print the membership array in matrix form
    print_matrix(membership_array);
}
