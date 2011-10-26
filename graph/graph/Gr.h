#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
using namespace std;

const int INF = 100000000; // бесконечность

typedef int Vertex;

typedef	map <Vertex, map <Vertex, int> > Graph_data;

struct DFSCallBack
{
	vector <Vertex> stack;
	void OnBlack (Vertex val){
		stack.push_back(val);
	}
	void Print(){
		while(!stack.empty()){
			cout << stack.back() << endl;
			stack.pop_back();
		}
	}
};

class Graph{
public:
	vector <int> color;
	//0 - not visited 1 - processed 2 - visited
	Graph_data data;
	void AddV (Vertex &point) {
		map <Vertex, map <Vertex, int> >::iterator the_iterator;
		if (data.find(point) == data.end()){
			map <Vertex, int> _p;
			data.insert (make_pair (point, _p));
		}
	}
	void PrintGr(){
		map <Vertex, map <Vertex, int> >::iterator the_iterator;
		for (map <Vertex, map <Vertex, int> >::iterator the_iterator = data.begin();the_iterator != data.end(); ++the_iterator){
			Vertex v = the_iterator->first;
			map <Vertex, int> &adjList = the_iterator->second;
		    for (map <Vertex, int>::iterator iter = adjList.begin();iter != adjList.end(); ++iter){
				Vertex v1 = iter->first;
				cout << v << "->" << v1<< endl;
		}
		}
	}

	void AddEdge(Vertex &vertex1, Vertex &vertex2, int weight){
		AddV(vertex1);
		AddV(vertex2);
		{
			map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex1);
			map <Vertex, int> &adjList = the_iterator->second;
			adjList.insert(make_pair(vertex2,weight));
		}

	}
	
	void DelVertex(Vertex &vertex1){
		if (data.find(vertex1) == data.end()){
			cout << "Vertex wasn't found" << endl;
		}
		else {
			map <Vertex, map <Vertex, int> >::iterator the_iterator;
			map <Vertex, map <Vertex, int> >::iterator it1;
			the_iterator = data.find(vertex1);
			map <Vertex, int> &adjList = the_iterator->second; 
			map <Vertex, int>::iterator iter = adjList.begin();    
			while(iter != adjList.end()){
				it1 = data.find(iter->first);
				map <Vertex, int> adjVert = it1->second;
				adjVert.erase(vertex1);
				iter++;
			}
			data.erase(vertex1);
		}
	}

	void DelEdge (Vertex &vertex1, Vertex &vertex2)
	{
		if ((data.find(vertex1) == data.end())||(data.find(vertex2) == data.end())){
			cout << "Vertex wasn't found" << endl;
		}
		else{
			map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex1);
			map <Vertex, int> &adjList = the_iterator->second;
			adjList.erase(vertex2);
		}
		
	}

	
template <typename Cb> 
	void DFS_iter (const Vertex &vertex1, Cb &cb){
		int n = data.size();
		color[vertex1] = 1;
		map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex1);
		map <Vertex, int> &adjList = the_iterator->second;
		for (map <Vertex, int>::iterator iter = adjList.begin();iter != adjList.end(); ++iter){
			if (color[(*iter).first] == 0)
				DFS_iter((*iter).first, cb);
		}
		color[vertex1] = 2;
		cb.OnBlack(vertex1);
	}
	template <typename Cb> 
	void DFS (Cb &cb){
		for(int i = 0; i < data.size();i++){
			color[i] = 0;
		}
		for (int i = 0; i < data.size();i++){
			if (color[i] == 0){
				DFS_iter(i, cb);
			}
		}
	}
	template <typename Cb> 
	void DFS_iter2 (const Vertex &vertex1, Cb &cb){
		int n = data.size();
		color[vertex1] = 1;
		cb.OnBlack(vertex1);  // changing
		map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex1);
		map <Vertex, int> &adjList = the_iterator->second;
		for (map <Vertex, int>::iterator iter = adjList.begin();iter != adjList.end(); ++iter){
			if (color[(*iter).first] == 0)
				DFS_iter((*iter).first, cb);
		}
		color[vertex1] = 2;

	}

	template <typename Cb> 
	void DFS2 (Cb &cb){
		for(int i = 0; i < data.size();i++){
			color[i] = 0;
		}
		for (int i = 0; i < data.size();i++){
			if (color[i] == 0){
				DFS_iter(i, cb);
			}
		}
	}

	DFSCallBack TopologySort(){
		DFSCallBack cb;
		DFS(cb);
		return cb;
	}
	DFSCallBack TopologySort2(){
		DFSCallBack cb;
		DFS2(cb);
		return cb;
	}
	void BFS (const Vertex &vertex1){
		queue<int> q;
		q.push(vertex1);
		int n = data.size();
		vector <bool> us (n);
		vector <int> d(n), p(n);
		us[vertex1] = true;
		p[vertex1] = -1;
		// p - parent d - distance
		while(!q.empty()){
			Vertex v = q.front();
			q.pop();
			map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(v);
			map <Vertex, int> &adjList = the_iterator->second;
			for (map <Vertex, int>::iterator iter = adjList.begin();iter != adjList.end(); ++iter){
				Vertex w = iter->first;
				while(!us[w]){
					us[w] = true;
					q.push(w);
					d[w] = d[v] + 1;
					p[w] = v;
				}
			}
		}
	}

	void Prim (){
		int n = data.size();
		vector <int> min;
		for (int i = 0; i < n; ++i){
			min[i] = INF;
		}
		vector <Vertex> sel;
		for (int i = 0; i < n; ++i){
			sel[i] = -1;
		}
		min[0] = 0;
		multimap <int, Vertex> q;
		q.insert(make_pair (0,0));	
		for (map <Vertex, map <Vertex, int> >::iterator the_iterator = data.begin();the_iterator != data.end(); ++the_iterator){
			if(q.empty()){
				cout<<"No MST";
			}
			Vertex v = q.begin()->second;
			q.erase(q.begin());
			if (sel[v] != -1){
				cout<< v << " " << sel[v] << endl;
			}
			map <Vertex, int> &adjList = the_iterator->second;
			for (map<Vertex, int>::iterator iter = adjList.begin();iter != adjList.end(); ++iter){
				Vertex t = iter->second;
				int cost = iter->first;
				if (cost < min[t]) {
					q.erase (min[t]);
					min[t] = cost;
					sel[t] = v;
					q.insert(min[t]);
				}
			}
		}
	}

	void Dijkstr(Vertex s){
		vector<int> d;
		//distances
		for (int i = 0; i < data.size(); ++i){
			d[i] = INF;
		}
		vector <bool> u;
		vector <int> p;
		//parents
		d[s] = 0;
		for (map <Vertex, map <Vertex, int> >::iterator the_iterator = data.begin();the_iterator != data.end(); ++the_iterator){
			Vertex v = -1;
			for (map <Vertex, map <Vertex, int> >::iterator the_iterator1 = data.begin();the_iterator1 != data.end(); ++the_iterator1){
				if(!u[the_iterator1->first] && ((v == -1)||(d[the_iterator1->first] < d[the_iterator->first])))
					v = the_iterator1->first;
				if (d[v] = INF)
					break;
				u[v] = true;
			}
			map <Vertex, int> &adjList = the_iterator->second;
			for (map<Vertex, int>::iterator iter = adjList.begin();iter != adjList.end(); ++iter){
				Vertex t = iter->first;
				int l = iter->second;
				if((d[v] + l)<d[t]){
					d[t] = d[v] + l;
					p[t] = v;
				}
			}
		}
	}
};


void Strongly_Connected_Components (Graph g)
{
	DFSCallBack order;
	order = g.TopologySort();
	Graph gr;
	for (map <Vertex, map <Vertex, int> >::iterator the_iterator = g.data.begin();the_iterator != g.data.end();++the_iterator){
		map <Vertex, int> &adjList = the_iterator->second;
		for (map <Vertex, int>::iterator iter = adjList.begin();iter != adjList.end(); ++iter){
			gr.AddEdge(iter->first, the_iterator->first, 1);
		}

	}
	DFSCallBack component;
	component = gr.TopologySort2();
	for (int i = 0; i < g.data.size();i++){
		g.color[i] = 0;
	}
	for (int i=0; i < g.data.size(); ++i)
		if (g.color[i] != 0)
			g.DFS(i);
	for(int i = 0; i < g.data.size();i++){
		gr.color[i] = 0;
	}
	for (int i=0; i < gr.data.size(); ++i) {
		int v = order.stack[g.data.size()-1-i];
		if (gr.color[i] != 0){
			gr.DFS2(i);
			component.stack.clear();
		}
	}
}