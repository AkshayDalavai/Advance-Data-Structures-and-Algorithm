#include <iostream>


using namespace std;


class Node {
public:
	int value;
	Node* next;
	Node(int i) { value = i; next = nullptr; }
	Node() { next = nullptr; }
};

class LinkedList {
public:
	int numNodes;
	Node* head;
	LinkedList() { numNodes = 0; head = nullptr; }
	void makeRandomList(int m, int n);
	void printList();



	//Recursively merge sort i numbers starting at node pointed by p
	void mergeSort(Node*& p, int i);//in-place recursive merge sort


	//Merge i1 numbers starting at node pointed by p1 with i2 numbers
	//starting at node pointed by p2
	void merge(Node*& p1, int i1, Node* p2, int i2);
};

//Begin added by Akshay Dalavai 237728854
void LinkedList::mergeSort(Node*& p, int i)
{
	


	int l = i / 2;
	int r = i - l;

	//Base code
	if (i == 1)
		return;
	Node* s = p;
	Node* f = p;
	//Splitting
	int j = 0;
	while (j < l) {
		j++;
		s = s->next;
	}

	//Calling recursively
	if (l >= 1 || r >= 1)
	{
		//Left split
		mergeSort(p, l);

		//right split
		mergeSort(s, r);

		//merge
		merge(p, l, s, r);
	}

}

void LinkedList::merge(Node*& p1, int i1, Node* p2, int i2)
{
	if (p1 == NULL) {
		p1 = p2;
	}
	if (p2 == NULL) {
		return;
	}
	Node* temp;
	if (p1->value <= p2->value) {
		temp = p1;
		p1 = p1->next;
		i1--;
	}
	else {
		temp = p2;
		p2 = p2->next;
		i2--;
	}
	Node* result = temp;
	while (i1 > 0 && i2 > 0) {
		if (p1->value <= p2->value) {
			temp->next = p1;
			p1 = p1->next;
			i1--;
		}
		else {
			temp->next = p2;
			p2 = p2->next;
			i2--;
		}
		temp = temp->next;
	}

	while (i2 > 0) {
		temp->next = p2;
		temp = temp->next;
		p2 = p2->next;
		i2--;
	}

	while (i1 > 0) {
		temp->next = p1;
		temp = temp->next;
		p1 = p1->next;
		i1--;
	}
	temp->next = NULL;
	p1 = result;
}
//End added by Akshay Dalavai 237728854

void LinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->next = head;
		head = p1;
		numNodes++;
	}
}

void LinkedList::printList() {
	cout << endl;
	Node* p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}


int main() {

	LinkedList d1;


	d1.makeRandomList(40, 20);
	d1.printList();

	d1.mergeSort(d1.head, d1.numNodes);
	d1.printList();

	getchar();
	getchar();
	return 0;

}
