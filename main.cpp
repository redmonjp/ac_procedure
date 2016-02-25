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
    int start=0;
    int x=NULL;
    int y=NULL;
    int num_of_verticies=0;
    int length_of_file=0;
    char ch=NULL;
    ifstream read_file(argv[1]);
    stringstream convert;
    string graph_str;
    
    //read the graph description file
    if (read_file){
        read_file.get(ch);
        while (!read_file.eof()) {
            graph_str.insert(i,1,ch);
            i++;
            read_file.get(ch);
        }
    }
    else{
        cout << "Couldn't open file\n";
        read_file.close();
        exit(1);
    }
    graph_str.insert(i,1,'\n');
    
    //lets start to parse this string
    //get the length of the string
    //set the pointer to the start
    length_of_file = i+1;
    i=0;
    
    while (graph_str.at(j)!= '\n') {
        j++;
        graph_str.at(j);
    }
    
    //get the string that represents the number of verticies
    //stuff it into an int
    convert<<graph_str.substr(i,j-i);
    convert>>num_of_verticies;
    convert.clear();
    cout<<"Number of verticies: "<<num_of_verticies<<endl;
    
    //resize the array to match the number of verticies and set it all to false
    membership_array.resize(num_of_verticies+1, vector<bool>(num_of_verticies+1, false));
    
    //as long as we still have tuples
    while (i <= length_of_file) {
        //if we are close to the end - break
        if (i+2 >= length_of_file||i>= length_of_file) {
            break;
        }
        //move past new lines and brackets
        if (graph_str.at(i) == '\n') {
            i++;
        }
        while (graph_str.at(i) != '{') {
            i++;
        }
        i++;
        j=i;
        start=i;
        while (graph_str.at(i) != '}'&&graph_str.at(i) != '\n') {
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
            //then move to the next spot
            i++;
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
