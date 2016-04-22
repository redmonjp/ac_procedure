/********************************************
Program: bk_test.cpp
Description: This program is meant to test basic
             functionality of bk algorihtm 
             implementation.

********************************************/
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include "bk.hpp"
int main(void){
	int num_vertices = 4;
	vector<vector <int> > user_cstructure;
	vector<int> vertices;
	vector< pair<int, int> > edges;
	vector< vector <int> > maximal_cliques;
	vector< vector <int> > usercliques;
	pair <int,int> edge1(1,2);
	//pair <int,int> edgetest (99,100);
	pair <int, int> edge2(1,3);
	pair <int, int> edge3 (2,3);
	pair <int, int> edge4 (1,4);
	pair <int, int> edge5 (2,4);
	//pair <int, int> edge6 (3,4);
	edges.push_back(edge1);
	//edges.push_back(edgetest);
	edges.push_back(edge2);
	edges.push_back(edge3);
	edges.push_back(edge4);
	edges.push_back(edge5);
	//edges.push_back(edge6);
	CreateSetofVertices(num_vertices, vertices);
	vector < int > R;
	vector < int > X;
/*	for(int i=0;i<numVertices;i++){
		printf("%d", vertices[i]);
	}
	printf("\n");*/
	cout<<"Maximal Cliques in graph: "<<endl;
	GetAllMaxCliques(edges, maximal_cliques, R,vertices, X );
	//cout<<maximalCliques.size();
	for(int j=0;j<maximal_cliques.size();j++){
		cout<<"{";
		for(int i=0;i<maximal_cliques[j].size();i++){
			cout<<maximal_cliques[j][i]<<" ";
		}
		cout<<"}"<<endl;
	}
	cout<<endl;
	bool same_cstructure = CheckCStructure(maximal_cliques, maximal_cliques);
	cout<<same_cstructure;
	//printf(" %d", edges[3].second);
	return 0;

}
