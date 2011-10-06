#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
using namespace std;

typedef int Vertex; //

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

/*struct DCU
{
	vector <Vertex> parent;
	void Set (Vertex val){
		parent[val] = val;
	}

	Vertex Find (Vertex v) {
		if (v == parent[v])
			return v;
		return Find (parent[v]);
	}

	void UnionSets (Vertex v1, Vertex v2) {
		v1 = Find (v1);
		v2 = Find (v2);
		if (v1 != v2)
			parent[v2] = v1;
	}
};*/

class Graph{
public:
	vector <int> color;
	//0 - not visited 1 - processed 2 - visited
	Graph_data data;
	void AddV (Vertex point) {
		map <Vertex, map <Vertex, int> >::iterator the_iterator;
		if (data.find(point) == data.end()){
			map <Vertex, int> _p;
			data.insert (make_pair (point, _p));
		}
		else{
			cout << "Vertex was added earlier";
		}
	}
	void AddEdge(const Vertex &vertex1,  const Vertex &vertex2, int weight){
		AddV(vertex1);
		AddV(vertex2);
		{
			map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex1);
			map <Vertex, int> &adjList = the_iterator->second;
			adjList.insert(make_pair(vertex2,weight));
		}
	
		/*{
			map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex2);
			map <Vertex, int> &adjList = the_iterator->second;
			adjList.insert(make_pair(vertex1,weight));
		}*/
		//для ориентированного грава
	}
	void DelVertex(const Vertex &vertex1){
		if (data.find(vertex1) == data.end()){
			cout << "Vertex wasn't found";
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

	void DelEdge (const Vertex &vertex1,  const Vertex &vertex2)
	{
		{
			map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex1);
			map <Vertex, int> &adjList = the_iterator->second;
			adjList.erase(vertex2);
		}
		//delete second
		/*{
			map <Vertex, map <Vertex, int> >::iterator the_iterator = data.find(vertex2);
			map <Vertex, int> &adjList = the_iterator->second;
			adjList.erase(vertex1);
		}*/
		//для неориентированного графа
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
			gr.AddEdge(iter -> first, the_iterator -> first, 1);
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