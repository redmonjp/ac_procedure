#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>
#include "bk.hpp"
int main(void){
	int numVertices = 100;

	vector<int> vertices;
	vector< pair<int, int> > edges;
	vector< vector <int> > maximalCliques;
	pair <int,int> edge1(1,2);
	pair <int,int> edgetest (99,100);
	/*pair <int, int> edge2(1,3);
	pair <int, int> edge3 (2,3);
	pair <int, int> edge4 (1,4);*/
	edges.push_back(edge1);
	edges.push_back(edgetest);
	/*edges.push_back(edge2);
	edges.push_back(edge3);
	edges.push_back(edge4);*/
	createSetofVertices(numVertices, vertices);
	vector < int > R;
	vector < int > X;
/*	for(int i=0;i<numVertices;i++){
		printf("%d", vertices[i]);
	}
	printf("\n");*/
	cout<<"Maximal Cliques in graph: "<<endl;
	getAllMaxCliques(edges, maximalCliques, R,vertices, X );
	//cout<<maximalCliques.size();
	for(int j=0;j<maximalCliques.size();j++){
		cout<<"{";
		for(int i=0;i<maximalCliques[j].size();i++){
			cout<<maximalCliques[j][i]<<" ";
		}
		cout<<"}"<<endl;
	}
	cout<<endl;
	//printf(" %d", edges[3].second);
	return 0;

}
