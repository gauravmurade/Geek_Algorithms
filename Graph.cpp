#include <iostream>
#include <stdio.h>
#include <list>
#include <queue>
#include <stack>
#include <limits.h>
using namespace std;
//#define V 4 				// FloyedWarshall
#define V 9				// Dijkstra and Prim
#define INF INT_MAX
#define MINF INT_MIN

void printStack(stack<int> s) {
    while(!s.empty()) {
    	cout << s.top() << " ";
    	s.pop();
    }
    cout << endl;
    cout << endl;
}

typedef struct node {
	int dest;
	int weight;
	node (int d, int w) {
		dest = d;
		weight = w;
	}
}node;

class Graph {
	void BFSUtil(int, bool[]);
	void DFSUtil(int, bool[]);
	public:
		int v;
		list<node>* adjList;
		Graph(int v) {
			this->v = v;
			this->adjList = new list<node>[v];
		}
		void printGraph();
		void BFS();
		void DFS();
};

class DirectedGraph : public Graph {
	bool isCyclicUtil(int, bool[], bool[]);
	public:
		DirectedGraph(int v) : Graph(v) {
		}
		void addEdge(int, int, int);
		void isCyclic();
		void pathExistsBFS(int, int);
};

class DirectedAcyclicGraph : public DirectedGraph {
	void topologicalSortUtil(int, bool[], stack<int>&);
	public:
		DirectedAcyclicGraph(int v) : DirectedGraph(v) {
		}
		stack<int> topologicalSort();
		void shortestPath(int );
		void longestPath(int );
};

class UndirectedGraph : public Graph {
	bool isCyclicUtil(int, bool[], int);
	public:
		UndirectedGraph(int v) : Graph(v) {
		}
		void addEdge(int, int, int);
		void isCyclic();
};

void DirectedGraph::addEdge(int source, int dest, int weight) {
	node newNode(dest, weight);
	this->adjList[source].push_back(newNode);
}

void UndirectedGraph::addEdge(int source, int dest, int weight) {
	node newNode1(dest, weight);
	node newNode2(source, weight);

	this->adjList[source].push_back(newNode1);
	this->adjList[dest].push_back(newNode2);
}

void Graph::printGraph() {
	list<node>::iterator listIter;
	for(int i=0; i < this->v; i++) {
		cout << "Adjecency List of vertex " << i <<" is : ";
		for(listIter = adjList[i].begin(); listIter != adjList[i].end(); listIter++) {
			cout << listIter->dest << " ";
		}
		cout<<"\n";
	}
}

void Graph::BFSUtil(int source, bool visited[]) {

	int temp;
	queue<int> tobeVisited;
	visited[source] = true;
	tobeVisited.push(source);
	list<node>::iterator listIter;
	printf("Breadth First Traversal (starting from vertex %d) is: ", source);

	while(!tobeVisited.empty()) {
		temp = tobeVisited.front();
		tobeVisited.pop();
		cout << temp << " ";
		for(listIter = adjList[temp].begin(); listIter != adjList[temp].end(); listIter++) {
			if(!visited[listIter->dest]) {
				visited[listIter->dest] = true;
				tobeVisited.push(listIter->dest);
			}
		}
	}
	cout << endl;
}

void Graph::BFS() {

	bool visited[this->v];
	for(int i=0; i < this->v; i++) {
		visited[i] = false;
	}

   	printf("Breadth First Traversal is: ");
	for(int i = 0; i < this->v; i++) {
        if(!visited[i])	{
            BFSUtil(i, visited);
        }
		cout << endl;
    }
}


void Graph::DFSUtil(int source, bool visited[]) {
	visited[source] = true;
	cout << source << " ";
	list<node>::iterator listIter;
	for(listIter = adjList[source].begin(); listIter != adjList[source].end(); listIter++) {
		if(!visited[listIter->dest]) {
			DFSUtil(listIter->dest, visited);
		}
	}
}

void Graph::DFS() {

	bool visited[this->v];
	for(int i=0; i < this->v; i++) {
		visited[i] = false;
	}

   	printf("Depth First Traversal is: ");
	for(int i = 0; i < this->v; i++) {
        if(!visited[i])	{
            DFSUtil(i, visited);
        }
		cout << endl;
    }
}

bool DirectedGraph::isCyclicUtil(int source, bool visited[], bool visitedForComponent[]) {
	visited[source] = true;
	visitedForComponent[source] = true;
	list<node>::iterator listIter;
	for(listIter = adjList[source].begin(); listIter != adjList[source].end(); listIter++) {
		if(!visited[listIter->dest]) {
			if(isCyclicUtil(listIter->dest, visited, visitedForComponent)) {
				return true;
			}
		}
		else if(visitedForComponent[listIter->dest]) {
			return true;
		}
	}
	visitedForComponent[source] = false;
	return false;
}

void DirectedGraph::isCyclic() {

	bool visited[this->v];
	bool visitedForComponent[this->v];
	for(int i=0; i < this->v; i++) {
		visited[i] = false;
		visitedForComponent[i] = false;
	}

	for(int i = 0; i < this->v; i++) {
        if(!visited[i])	{
            if(isCyclicUtil(i, visited, visitedForComponent)) {
            	cout << "Cycle exists!" << endl;
            	return;
            }
        }
    }
    cout << "Cycle does not exist!" << endl;
}

bool UndirectedGraph::isCyclicUtil(int source, bool visited[], int parent) {
	visited[source] = true;
	list<node>::iterator listIter;
	for(listIter = adjList[source].begin(); listIter != adjList[source].end(); listIter++) {
		if(!visited[listIter->dest]) {
			if(isCyclicUtil(listIter->dest, visited, source)) {
				return true;
			}
		}
		else if(parent != (listIter->dest)) {
			return true;
		}
	}
	return false;
}

void UndirectedGraph::isCyclic() {

	bool visited[this->v];
	int parent = -1;
	for(int i=0; i < this->v; i++) {
		visited[i] = false;
	}

	for(int i = 0; i < this->v; i++) {
        if(!visited[i])	{
            if(isCyclicUtil(i, visited, parent)) {
            	cout << "Cycle exists!" << endl;
            	return;
            }
        }
    }
    cout << "Cycle does not exist!" << endl;
}

void DirectedAcyclicGraph::topologicalSortUtil(int source, bool visited[], stack<int>& holdSortedElements) {
	visited[source] = true;
	list<node>::iterator listIter;
	for(listIter = adjList[source].begin(); listIter != adjList[source].end(); listIter++) {
		if(!visited[listIter->dest]) {
			topologicalSortUtil(listIter->dest, visited, holdSortedElements);
		}
	}
	holdSortedElements.push(source);
}	

stack<int> DirectedAcyclicGraph::topologicalSort() {

	bool visited[this->v];
	for(int i=0; i < this->v; i++) {
		visited[i] = false;
	}

	stack<int> holdSortedElements;
   	printf("Topological Sort of the given graph is \n");
	for(int i = 0; i < this->v; i++) {
        if(!visited[i])	{
            topologicalSortUtil(i, visited, holdSortedElements);
        }
    }
//  Use this return wehn you need to top sort the DAG before proceeding with some other 
    return holdSortedElements;
    printStack(holdSortedElements);
}

void DirectedGraph::pathExistsBFS(int source, int dest) {

	if(source == dest) {
		cout << "Path exists" << endl;
		return;
	}

	bool visited[this->v];
	for(int i=0; i < this->v; i++) {
		visited[i] = false;
	}

	int temp;
	queue<int> tobeVisited;
	visited[source] = true;
	tobeVisited.push(source);
	list<node>::iterator listIter;

	while(!tobeVisited.empty()) {
		temp = tobeVisited.front();
		tobeVisited.pop();
		for(listIter = adjList[temp].begin(); listIter != adjList[temp].end(); listIter++) {
			if(listIter->dest == dest) {
				cout << "Path exists" << endl;
				return;
			}
			if(!visited[listIter->dest]) {
				visited[listIter->dest] = true;
				tobeVisited.push(listIter->dest);
			}
		}
	}
	cout << "Path does not exist" << endl;
}

void printMatrix(int matrix[][V]) {

	for(int i=0; i < V; i++) {
		for(int j=0; j < V; j++) {
			if(matrix[i][j] == INF) {
				printf("%7s", "INF");
			}
			else {
				printf("%7d", matrix[i][j]);
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printPathMatrixUtil(int storePredecessor[][V], int source, int dest) {

	if(storePredecessor[source][dest] == source) {
		cout << source << " ";
	}
	else {
		printPathMatrixUtil(storePredecessor, source, storePredecessor[source][dest]);
		cout << storePredecessor[source][dest] << " ";
	}
}

void printPathMatrix(int storePredecessor[][V], int source, int dest) {

	cout << "The shortest path from " << source << " to " << dest << " is : ";	
	printPathMatrixUtil(storePredecessor, source, dest);
	cout << dest << endl;
}

void floydWarshell(int GraphMatrix[][V]) {

	int minDist[V][V];
	int storePredecessor[V][V];
	int i;
	int j;
	int k;

	for(i=0; i < V; i++) {
		for(j=0; j < V; j++) {
			minDist[i][j] = GraphMatrix[i][j];
			if(minDist[i][j] == 0 || minDist[i][j] == INF) {
				storePredecessor[i][j] = -1;
			}
			else {
				storePredecessor[i][j] = i;
			}
		}
	}	

	int dist1;
	int dist2;	

	for(k=0; k < V; k++) {
		for(i=0; i < V; i++) {
			for(j=0; j < V; j++) {
				dist1 = minDist[i][k];
				dist2 = minDist[k][j];
				if((dist1 != INF) && (dist2 != INF) && (dist1 + dist2 < minDist[i][j])) {
					minDist[i][j] = dist1 + dist2;	
					storePredecessor[i][j] = k;
				}
			}
		}
	}
	printMatrix(minDist);
	printMatrix(storePredecessor);
	printPathMatrix(storePredecessor, 1, 3);
}

void printList(int list[], int listLength) {

	for(int i=0; i < listLength; i++) {
		if(list[i] == INF) {
			printf("%7s", "INF");
		}
		else if(list[i] == MINF) {
			printf("%7s", "MINF");
		}
		else {
			printf("%7d", list[i]);
		}
	}
	cout << endl;
	cout << endl;
}

void printPathListUtil(int storePredecessor[], int source, int dest) {

	if(storePredecessor[dest] == source) {
		cout << source << " ";
	}
	else {
		printPathListUtil(storePredecessor, source, storePredecessor[dest]);
		cout << storePredecessor[dest] << " ";
	}
}

void printPathList(int storePredecessor[], int source, int dest) {

	cout << "The shortest path from " << source << " to " << dest << " is : ";	
	printPathListUtil(storePredecessor, source, dest);
	cout << dest << endl;;
}

int extractMin(int minDist[], bool visitedVertices[]) {
	int minValue = INF;
	int minIndex = -1;

	for(int i=0; i < V; i++) {
		if(!visitedVertices[i] && minDist[i] <= minValue) {
			minValue = minDist[i];
			minIndex = i;
		}
	}
	return minIndex;
}

void dijkstra(int GraphMatrix[][V], int source) {

	int minDist[V];
    bool visitedVertices[V];
    int storePredecessor[V];
    int minDistVertex;
    int i;
    int j;

    for(i=0; i < V; i++) {
    	minDist[i] = INF;    		
    	visitedVertices[i] = false;
	 	storePredecessor[i] = -1;
    }
	minDist[source] = 0;

//	minDist already holds the minimum distance for the vertex furthest from our source
//	Hence, we can run the loop v-1 times
    for(i=0; i < V-1; i++) {
    	minDistVertex = extractMin(minDist, visitedVertices);
    	visitedVertices[minDistVertex] = true;
	    for(j=0; j < V; j++) {
	    	if( !visitedVertices[j] 
	    		&& GraphMatrix[minDistVertex][j] != INF
	    		&& minDist[minDistVertex] != INF 
	    		&& minDist[j] > minDist[minDistVertex] + GraphMatrix[minDistVertex][j]) {

	    		minDist[j] = minDist[minDistVertex] + GraphMatrix[minDistVertex][j];
			 	storePredecessor[j] = minDistVertex;
	    	}
    	}
	}
	printList(minDist, V);
	printPathList(storePredecessor, 0, 8);
}

void DirectedAcyclicGraph::shortestPath(int source) {

	list<node>::iterator listIter;
	int topElement = -1;
	int minDist[this->v];

	for(int i = 0; i < this->v; i++) {
		minDist[i] = INF;
	}	
	minDist[source] = 0;

	stack<int> holdSortedElements = topologicalSort();
	while(topElement != source) {
		topElement = holdSortedElements.top();
		holdSortedElements.pop();
	}
	holdSortedElements.push(source);

	while(!holdSortedElements.empty()) {
		topElement = holdSortedElements.top();
		holdSortedElements.pop();
		for(listIter = adjList[topElement].begin(); listIter != adjList[topElement].end(); listIter++) {
			if(	minDist[topElement] != INF &&
				listIter->weight != INF &&
				minDist[listIter->dest] > minDist[topElement] + listIter->weight) {

				minDist[listIter->dest] = minDist[topElement] + listIter->weight;
			}
		}	
	}
	printList(minDist, this->v);
}

void DirectedAcyclicGraph::longestPath(int source) {

	list<node>::iterator listIter;
	int topElement = -1;
	int maxDist[this->v];

	for(int i = 0; i < this->v; i++) {
		maxDist[i] = MINF;
	}	
	maxDist[source] = 0;

	stack<int> holdSortedElements = topologicalSort();
	while(topElement != source) {
		topElement = holdSortedElements.top();
		holdSortedElements.pop();
	}
	holdSortedElements.push(source);

	while(!holdSortedElements.empty()) {
		topElement = holdSortedElements.top();
		holdSortedElements.pop();
		for(listIter = adjList[topElement].begin(); listIter != adjList[topElement].end(); listIter++) {
			if(	maxDist[topElement] != MINF &&
				listIter->weight != MINF &&
				maxDist[listIter->dest] < maxDist[topElement] + listIter->weight) {

				maxDist[listIter->dest] = maxDist[topElement] + listIter->weight;
			}
		}	
	}
	printList(maxDist, this->v);
}

void printMST(int parent[], int key[]) {
	for(int i = 1; i < V; i++) {
		printf("Edge %d - %d 	Weight %d\n", parent[i], i, key[i]);
	}	
	printf("\n");
	printf("\n");
}

void primMST(int GraphMatrix[][V]) {

	bool visited[V];	
	int  key[V];
	int  parent[V];
	int min;

	for(int i = 0; i < V; i++) {
		visited[i] = false;
		key[i] = INF;
	}
	key[0] = 0;
	parent[0] = -1;

	for(int i = 0; i < V-1; i++) {
		min = extractMin(key, visited);
		visited[min] = true;
		for(int j = 0; j < V; j++) {
			if(!visited[j] && 
				GraphMatrix[min][j] != INF &&
				key[j] > GraphMatrix[min][j]) {

				key[j] = GraphMatrix[min][j];
				parent[j] = min;
			}
		}
	}
	printMST(parent, key);
}

int main() {

	// Directed Cyclic Graph
	DirectedGraph DCG(5);
	DCG.addEdge(0, 1, 1);
    DCG.addEdge(0, 2, 1);
	DCG.addEdge(0, 4, 1);
    DCG.addEdge(1, 2, 1);
    DCG.addEdge(2, 0, 1);
    DCG.addEdge(2, 3, 1);
    DCG.addEdge(3, 3, 1);
//	DCG.printGraph();
//  DCG.BFS();
//  DCG.DFS();
//  DCG.isCyclic();
//	DCG.pathExistsBFS(1, 3);
//	DCG.pathExistsBFS(3, 1);

	// Directed Acyclic Graph
	DirectedAcyclicGraph DAG(6);
	DAG.addEdge(0, 1, 5);
    DAG.addEdge(0, 2, 3);
    DAG.addEdge(1, 3, 6);
    DAG.addEdge(1, 2, 2);
    DAG.addEdge(2, 3, 7);
    DAG.addEdge(2, 4, 4);
    DAG.addEdge(2, 5, 2);
    DAG.addEdge(3, 4, -1);
    DAG.addEdge(3, 5, 1);
    DAG.addEdge(4, 5, -2);
//	DAG.isCyclic();
//	DAG.topologicalSort();
//	DAG.longestPath(1);
//	DAG.shortestPath(1);

	// Undirected Cyclic Graph
	UndirectedGraph UCG(5);
	UCG.addEdge(0, 1, 1);
    UCG.addEdge(0, 2, 1);
	UCG.addEdge(0, 4, 1);
    UCG.addEdge(1, 2, 1);
    UCG.addEdge(2, 0, 1);
    UCG.addEdge(2, 3, 1);
    UCG.addEdge(3, 3, 1);
//  UCG.isCyclic();

	// Undirected Acyclic Graph
	UndirectedGraph UAG(3);
	UAG.addEdge(0, 1, 1);
    UAG.addEdge(1, 2, 1);
//  UAG.isCyclic();

/*
	int GraphMatrix[V][V] = { {0,     5, INF,  10},
                       		  {INF,   0,   3, INF},
                        	  {INF, INF,   0,   1},
                       	      {INF, INF, INF,   0}
                     	    };

	printMatrix(GraphMatrix);
	floydWarshell(GraphMatrix);

*/
	int GraphMatrix[V][V] = { {  0,   4, INF, INF, INF, INF, INF,   8, INF},
                      		  {  4,   0,   8, INF, INF, INF, INF,  11, INF},
                      		  {INF,   8,   0,   7, INF,   4, INF, INF,   2},
                      		  {INF, INF,   7,   0,   9,  14, INF, INF, INF},
                      		  {INF, INF, INF,   9,   0,  10, INF, INF, INF},
                      		  {INF, INF,   4, INF,  10,   0,   2, INF, INF},
                      		  {INF, INF, INF,  14, INF,   2,   0,   1,   6},
                      		  {  8,  11, INF, INF, INF, INF,   1,   0,   7},
                      		  {INF, INF,   2, INF, INF, INF,   6,   7,   0}
                     		};	

	printMatrix(GraphMatrix);
	dijkstra(GraphMatrix, 0);

	printMatrix(GraphMatrix);
	primMST(GraphMatrix);
    return 0;
}