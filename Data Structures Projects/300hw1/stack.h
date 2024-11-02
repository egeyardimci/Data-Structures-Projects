#ifndef _STACK_
#define _STACK_

template <typename T>
struct Node {
	T val;
	Node* next;

	Node(T val, Node* next);

};

template <typename T>
class Stack {
private:
	Node<T>* head;

public:
	Stack();

	T top();
	void pop();
	void push(T val);

	bool isEmpty();
	void print();

};

#endif