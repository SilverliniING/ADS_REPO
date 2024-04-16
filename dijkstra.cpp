#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
	int from;
	int to;
	float weight;
	Edge(int _to, int _from, float val)
	{
		to = _to;
		from = _from;
		weight = val;
	}
	Edge()
	{
		to = -1;
		from = -1;
		weight = 0;
	}
	void display()
	{
		printf("From:%d\tTo:%d\tWeight:%f\n", from, to, weight);
	}
};
class Node
{
public:
	Edge e;
	vector<Node *> children;
	int degree;
	Node *parent;
	Node(Edge new_edge)
	{
		e = new_edge;
		children = {};
		degree = 0;
		parent = NULL;
	}
};
class BHeap
{
public:
	vector<Node *> heads;
	Node *mini;
	BHeap()
	{
		mini = NULL;
		heads = {};
	}
	Node *merge_trees(Node *h1, Node *h2)
	{
		if (h1->e.weight > h2->e.weight)
		{
			return merge_trees(h2, h1);
		}
		// cout<<"Pushing: ";
		// h2->e.display();
		// cout<<"Into parent: ";
		// h1->e.display();
		// cout<<"---------"<<endl;
		h1->children.push_back(h2);
		h2->parent = h1;
		h1->degree += 1;
		return h1;
	}
	void push(Edge edge)
	{
		Node *nn = new Node(edge);
		BHeap *heap = new BHeap();
		heap->heads.push_back(nn);
		merge(heap);
	}
	void setMin()
	{
		mini = NULL;
		for (Node *n : heads)
		{
			if (mini == NULL || mini->e.weight > n->e.weight)
			{
				mini = n;
			}
		}
	}
	bool isEmpty()
	{
		return mini == NULL;
	}
	Edge getMin()
	{
		if (!isEmpty())
		{
			return mini->e;
		}
		Edge e;
		return e;
	}
	void merge(BHeap *heap2)
	{
		map<int, vector<Node *>> degree_to_head;
		for (Node *h : heads)
		{
			degree_to_head[h->degree].push_back(h);
		}
		for (Node *h : heap2->heads)
		{
			degree_to_head[h->degree].push_back(h);
		}
		map<int, vector<Node *>>::iterator itr;
		for (itr = degree_to_head.begin(); itr != degree_to_head.end(); itr++)
		{
			while (itr->second.size() >= 2)
			{
				Node *h2 = itr->second.back();
				itr->second.pop_back();
				Node *h1 = itr->second.back();
				itr->second.pop_back();
				Node *h3 = merge_trees(h1, h2);
				degree_to_head[h3->degree].push_back(h3);
			}
		}
		heads = {};
		for (itr = degree_to_head.begin(); itr != degree_to_head.end(); itr++)
		{

			// printf("Degree:%d\n",itr->first);
			// for(auto it:itr->second){
			// 	it->e.display();
			// }
			if (itr->second.size() > 0)
			{
				heads.push_back(itr->second[0]);
			}
		}
		setMin();
	}
	Node *pop()
	{
		vector<Node *> heads_after_extract;
		Node *min_ele = mini;
		for (Node *n : heads)
		{
			if (n != mini)
			{
				heads_after_extract.push_back(n);
			}
		}
		heads = heads_after_extract;
		BHeap *new_bheap = new BHeap();
		new_bheap->heads = mini->children;
		// cout<<"Children of "<<mini<<endl;
		// for(auto child : mini->children){
		// 	cout<<child<<" ";
		// 	child->e.display();
		// 	cout<<endl;
		// }
		merge(new_bheap);
		return min_ele;
	}
};

vector<float> dijkstra(vector<vector<vector<int>>> adj, int V,int src)
{
	BHeap *pq = new BHeap();
	// for (int i = 0; i < V; i++)
	// {
	// 	for(vector<int> edge : adj[i]){
	// 		Edge e(edge[0], i, (float)edge[1]);
	// 		pq->push(e);
	// 	}
	// }
	vector<float> dist(V,1e9);
	dist[src]=0;
	
	pq->push(Edge(src,src,0));
	while (!pq->isEmpty())
	{
		Edge e=pq->pop()->e;
		int to=e.to;
		int dist_from_src=e.weight;
		for(vector<int> edge : adj[to]){
			float dist_to_adj_node=edge[1];
			int adj_node=edge[0];
			if(dist_from_src+dist_to_adj_node<dist[adj_node]){
				dist[adj_node]=dist_from_src+dist_to_adj_node;
				pq->push(Edge(adj_node,to,dist[adj_node]));
			}
		}
	}
	return dist;
}
int main()
{
	// Edge e1(1, 2, 1);
	// Edge e2(2, 5, 10);
	// Edge e3(3, 7, 1.5);
	// BHeap *h = new BHeap;
	// h->push(e3);
	// h->getMin().display();
	// h->push(e1);
	// h->getMin().display();
	// h->push(e2);
	// h->getMin().display();
	// h->pop();
	// h->getMin().display();
	// h->pop();
	// h->getMin().display();
	// Creating the Graph:
	int V = 6;
	vector<vector<vector<int>>> adj(V);
	// pushing {to,dist}
	adj[0].push_back({1, 1});
	adj[0].push_back({2, 3});
	adj[0].push_back({3, 1});

	adj[1].push_back({0, 1});
	adj[1].push_back({4, 2});

	adj[2].push_back({0, 3});
	adj[2].push_back({4, 4});

	adj[3].push_back({0, 1});
	adj[3].push_back({5, 11});

	adj[4].push_back({1, 2});
	adj[4].push_back({2, 4});
	adj[4].push_back({5, 3});

	adj[5].push_back({4, 3});
	adj[5].push_back({3, 11});

	int src=0;
	vector<float> ans=dijkstra(adj,V,src);
	for(int i=0;i<V;i++){
		cout<<"The shortest path from "<<src<<" to "<<i<<"is "<<ans[i]<<endl;
	}
	return 0;
}
