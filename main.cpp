//test a commit from xcode
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, const char * argv[]) {
    int i=0;
    int j=0;
    int start=0;
    int x=NULL;
    int y=NULL;
    int num_of_verticies=0;
    int length_of_file=0;
    char ch=NULL;
    stringstream convert;
    ifstream read_file(argv[1]);
    string graph_str;
    vector<vector<bool> > membership_array;
    
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
    
    convert<<graph_str.at(i);
    convert>>num_of_verticies;
    convert.clear();
    cout<<"Number of verticies: "<<num_of_verticies<<endl;
    
    //resize the array to match the number of verticies and set it all to false
    membership_array.resize(num_of_verticies+1, vector<bool>(num_of_verticies+1, false));
    
    while (i <= length_of_file) {
        if (i+2 >= length_of_file) {
            break;
        }
        if (graph_str.at(i) == '\n') {
            i++;
        }
        while (graph_str.at(i) != '{') {
            i++;
        }
        i++;
        j=i;
        start=i;
        while (graph_str.at(i) != '}') {
            if (graph_str.at(i) == ',') {
                i++;
            }
            convert<<graph_str.at(i);
            convert>>x;
            convert.clear();
            i++;
            j=start;
            while (graph_str.at(j) != '}') {
                convert<<graph_str.at(j);
                convert>>y;
                convert.clear();
                membership_array[x][y] = true;
                j++;
                if (graph_str.at(j) == ',') {
                    j++;
                }
            }
        }
    }
    
    //print that all out
    for (int i = 1; i < membership_array.size(); i++){
        cout<<endl;
        for (int j = 1; j < membership_array.size(); j++){
            cout << membership_array[i][j]<<" ";
        }
    }
    cout<<"\n"<<endl;
}