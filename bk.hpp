#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

void createSetofVertices(int numVertices, vector<int> &vertices){
	for(int i=0; i<numVertices; i++){
		vertices.push_back(i+1);
	}	
}



int getPivot(vector < pair <int,int> > &edges, vector <int> U,vector <int> P){
	int u;
	int highest_num_neighbors=0;
	int best_vertex;
	//cout<<"U.size(): "<<U.size()<<endl;
	//cout<<"Size of U: "<<U.size();
	/*cout<<"U: { ";
	for(int h=0;h<U.size();h++){	
		cout<<U[h];
	}
	cout<<"}"<<endl;*/
	best_vertex = U[0];
	for (int i = 0; i<U.size(); i++){
		int neighbor_count = 0;
		for (int j = 0; j<edges.size(); j++){
			if (edges[j].first == U[i]||edges[j].second == U[i]){
				for(int v=0;v<P.size();v++){						
					if((edges[j].first != U[i] && edges[j].first == P[v])||(edges[j].second != U[i] && edges[j].second == P[v])){
						neighbor_count++;
					}
				}
					
			}				

		}	
		if (neighbor_count > highest_num_neighbors){
			highest_num_neighbors = neighbor_count;
			best_vertex = U[i];

		}

	}
	//cout<<"pivot:"<<best_vertex<<endl;
	//cout << highest_num_neighbors<<endl;
	//printf("%d", edges[0].first);
	return best_vertex;

}

//void get_neighbors(int v,vector < pair <int,int> > &edges, vector <int> &neighbors 

void get_neighbors(int u, vector < pair <int,int> > &edges, vector <int> &neighbors){
	//for each edge in edges:	
	for (int j = 0; j<edges.size(); j++){
		if (edges[j].first == u){
			neighbors.push_back(edges[j].second);					
			
		}				
		else if(edges[j].second == u){
			neighbors.push_back(edges[j].first);
		}
		else{}
			
	}	
	
	//cout<<edges.size()<<endl;
}

void getAllMaxCliques(vector< pair <int,int> > &edges, vector< vector <int> > &maximalCliques, vector <int> R, vector <int> P, vector <int> X){
	vector<int> U(100);                      // 0  0  0  0  0  0  0  0  0  0
 	vector<int>::iterator it;
	vector <int> neighbors;
	vector <int> p_union_x(100);
	it = set_union(P.begin(),P.end(), X.begin(), X.end(), p_union_x.begin());
	p_union_x.resize(it-p_union_x.begin());
	//cout<<p_union_x.size()<<endl;
	/*cout<<"P={";
		for(int o=0; o<P.size();o++){
			cout<<P[o]<<" ";
		}
		cout<<"}"<<endl;
	cout<<"R={";
		for (int t=0; t<R.size();t++){
			cout<<R[t]<<" ";
		}
	cout<<"}"<<endl;
	cout<<"X={";
		for(int p=0;p<X.size();p++){
			cout<<X[p]<<" ";
		}
	cout<<"}"<<endl;*/
	if (p_union_x.size() == 0){
		maximalCliques.push_back(R);
		return;
	}
	else{	 
		
		
		/*for(int m=0; m<p_union_x.size();m++){
			cout<<p_union_x[m]<<endl;
		}*/
		it = set_union(P.begin(), P.end(), X.begin(), X.end(), U.begin());
		U.resize(it-U.begin());
		/*cout<<"U={ ";
		for(int d=0;d<U.size();d++){
			cout<<U[d]<<" ";
		}
		cout<<"}";*/
		//for(int i=0; i<U.size(); i++)
		int pivot = getPivot(edges, U,P);
		//cout<<"Pivot: "<<pivot<<endl;
		//printf("%d", pivot);
  		//std::cout << '\n';
		get_neighbors(pivot, edges, neighbors);
		vector <int> P_minus_nbrs(100);
		it = set_difference(P.begin(),P.end(), neighbors.begin(), neighbors.end(), P_minus_nbrs.begin());
		P_minus_nbrs.resize(it-P_minus_nbrs.begin());		
		/*cout<<"P_minus_nbrs: ";
		for(int l=0; l<P_minus_nbrs.size(); l++){
			cout<<P_minus_nbrs[l]<<" ";
		}
		cout<<endl;*/
		/*for(int k = 0; k < neighbors.size();k++){
			cout<<neighbors[k]<<endl;
		}*/
		for(int y=0;y<P_minus_nbrs.size();y++){
			//cout<<"P_minus_nbrs[y]: "<<P_minus_nbrs[y]<<endl;
			vector <int> new_P(100);
			vector <int> new_R;
			vector <int> new_X;
			vector <int> neighbors_of_v;
			get_neighbors(P_minus_nbrs[y],edges, neighbors_of_v);
			for(int f=0;f<R.size();f++)
			{
				new_R.push_back(R[f]);
			}
			for(int g=0;g<X.size();g++){
				new_X.push_back(X[g]);
			}
			it = set_intersection(P.begin(),P.end(),neighbors_of_v.begin(),neighbors_of_v.end(), new_P.begin());
			new_P.resize(it-new_P.begin());
			new_R.push_back(P_minus_nbrs[y]);
			it = set_intersection(X.begin(), X.end(), neighbors_of_v.begin(),neighbors_of_v.end(), new_X.begin());
			new_X.resize(it-new_X.begin());
			getAllMaxCliques(edges, maximalCliques, new_R, new_P, new_X);
			for(int r = 0; r<P.size();r++){
				if (P[r] == P_minus_nbrs[y]){
					P.erase(P.begin()+r);
				}
			}
			X.push_back(P_minus_nbrs[y]);
			
		}

	/*cout<<"X={";
	for(int p=0;p<X.size();p++){
		cout<<X[p]<<" ";
	}
	cout<<"}"<<endl;*/
	}
	return;
}
	



