#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <iterator>

using namespace std;

class n_node { //stand for neighbor_node
public:
	int id;  //neighbor id
	int weight; //edge weight
	
    n_node(){}
};

class rt_node {
public:
	bool is_visited; //true if visited; else false
	int cost; //path cost
	int from; //from node
	int h_pos;//the positon of this node in heap
    
    rt_node()
    {
        is_visited = false;
        cost = 9999;
        from = -1;
    }
};

class h_node {
public:
	int id;//node id
	int cost; //cost to this node from source
	
    h_node() 
    {
        id = -1;
        cost = 9999;
    }
};

// The Routing_Table & Heap is passed by reference and changes 
void forming_rt(vector <rt_node> &Routing_Table, vector <h_node> &Heap, int &startingNode);
void heap_operation(vector<vector<n_node>* > &Graph, vector<rt_node> &Routing_Table, vector<h_node> &Heap);
void heapify_up(vector<rt_node> &Routing_Table, vector<h_node> &Heap, int &n);
void satisfy_min_heap_property(vector<rt_node> & rt, vector<h_node> & heap);
void swapnode(vector<rt_node> &Routing_Table, h_node parent_node, h_node childnode,int &current_position,int leftOrRightOrParent);

int main()
{
    ifstream in("graph.txt"); //input is read from this file...Make sure proper path is mentioned
    int startingNode;
    in>>startingNode;
    int n,e;
    in>>n>>e;
    vector < vector<n_node>* > Graph;
    vector<n_node> *p =NULL;
    n_node e1;
    for(int i=0; i<=n; i++){
        p = new vector<n_node>;
        Graph.push_back(p);}
    int n1,n2,w;
    for(int i=0;i<e;i++)
    {
        in>>n1>>n2>>w;
        e1.id=n2;
        e1.weight=w;
        Graph[n1]->push_back(e1);       
    }

    in.close();
	vector <rt_node> Routing_Table;
    Routing_Table.resize(n);
	vector <h_node> Heap;
    Heap.resize(n);
    
    forming_rt(Routing_Table, Heap, startingNode);
    heap_operation(Graph,Routing_Table,Heap);
	
    for (int j = 0; j < n; j++) {

		cout << "The cost from " << startingNode << " to " << j << " is  " << Routing_Table[j].cost << " ; from node is " << Routing_Table[j].from << endl;
	}
	
	return 0;
    
}

void swapnode(vector<rt_node> &rt, h_node parent_node, h_node childnode,int &current_position,int leftOrRight, vector<h_node> &heap)
{
    h_node tempnode = parent_node;
	heap[current_position] = childnode;
    int left_Or_Right;
    if(leftOrRight == 0)
    {
        left_Or_Right = (2 * current_position) +1;
    } 
    else if(leftOrRight == 1)
    {
        left_Or_Right = (2 * current_position) +2;
    }
	heap[left_Or_Right] = tempnode;
	rt[(parent_node).id].h_pos = left_Or_Right;
	rt[(childnode).id].h_pos = current_position;
    current_position = left_Or_Right;				
}

void heapify_up(vector<rt_node> &Routing_Table, vector<h_node> &Heap, int &n)
{
    int currentnode = n;

    while(Heap[currentnode].cost < Heap[(currentnode-1)/2].cost)
    {
        h_node temp = Heap[currentnode];
        Heap[currentnode] = Heap[(currentnode-1)/2];
        Heap[(currentnode-1)/2] = temp;
        Routing_Table[Heap[currentnode].id].h_pos = currentnode;
        Routing_Table[Heap[(currentnode -1)/2].id].h_pos = (currentnode -1)/2; 
        currentnode = (currentnode -1)/2;

    }
}

void satisfy_min_heap_property(vector<rt_node> & rt, vector<h_node> & heap)
{
    int NewHeap_length = heap.size();
    int a =0;
    if(NewHeap_length == 1 || NewHeap_length == 0 )
    {
        return;
    }

    while (((2 * a) +1 ) < NewHeap_length)
    {
        h_node parent_node = heap[a];
        h_node left_child_node = heap[(2 * a) + 1];
        int left_swap = 0;
        int right_swap = 1;
        if(NewHeap_length > (2 * a)+2)
        {
            h_node right_child_node = heap[(2 * a) + 2];
            if (parent_node.cost > left_child_node.cost || parent_node.cost > right_child_node.cost)
            {
                if (left_child_node.cost > right_child_node.cost)
                {
                    swapnode(rt,parent_node,right_child_node,a,right_swap,heap);
                }
                else
                {
                    swapnode(rt,parent_node,left_child_node,a,left_swap,heap);
                }
                
            }
            else return;
        }
        else
        {
            if(left_child_node.cost < parent_node.cost)
            {
                swapnode(rt,parent_node,left_child_node,a,left_swap,heap);
            }  
            else
            {
                return;
            }
             
        }
        
    }

}

void forming_rt(vector <rt_node> &Routing_Table, vector <h_node> &Heap, int &startingNode)
{
    Routing_Table[startingNode].cost = 0;
    Routing_Table[startingNode].from = startingNode;
    Routing_Table[startingNode].is_visited = true;
    for(int i=0; i<Heap.size();i++)
    {
        Heap[i].id=i;
        Routing_Table[i].h_pos=i;
    }
    Routing_Table[0].h_pos = startingNode;  
    Routing_Table[startingNode].h_pos=0;
    Heap[startingNode].id = 0;
    Heap[0].id =startingNode; 
    Heap[0].cost =0; 
    
}


void heap_operation(vector<vector<n_node>* > &Graph, vector<rt_node> &Routing_Table, vector<h_node> &Heap)
{
    int rt_size = Routing_Table.size()-1;
    int count =0;
    
    while(count < rt_size)
    {
        int current_Graph_size = 0;
        int graphindex = Heap[0].id;
        vector<n_node> graph = *Graph[graphindex];
        while(current_Graph_size < graph.size())
        {
            int node_id = graph[current_Graph_size].id;
            int node_weight = graph[current_Graph_size].weight;
            if(node_weight + Routing_Table[graphindex].cost < Routing_Table[node_id].cost)
            {
                Routing_Table[node_id].cost = node_weight + Routing_Table[graphindex].cost;
                Routing_Table[node_id].from = graphindex;
                Heap[Routing_Table[node_id].h_pos].cost = Routing_Table[node_id].cost;
                heapify_up(Routing_Table, Heap, Routing_Table[node_id].h_pos);
            }
            current_Graph_size++;
        }
        int s = Heap.size();
        
        Heap[0] = Heap[s-1];
        Heap.pop_back();
        satisfy_min_heap_property(Routing_Table,Heap);
        count++;
    }
}

   
