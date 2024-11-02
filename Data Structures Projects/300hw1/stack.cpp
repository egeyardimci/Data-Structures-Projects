#pragma once
#include "stack.h"
#include <iostream>

using namespace std;

template<typename T>
Node<T>::Node(T val, Node* next)
{
	this->next = next;
	this->val = val;
}

template<typename T>
Stack<T>::Stack() 
{
	this->head = nullptr;
}

template<typename T>
void Stack<T>::pop()
{
	if (!this->isEmpty()) {
		Node<T> *temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename T>
T Stack<T>::top()
{
	return head->val;
}

template<typename T>
void Stack<T>::push(T val)
{
	Node<T> *newNode = new Node<T>(val, head);
	head = newNode;
}

template<typename T>
bool Stack<T>::isEmpty()
{
	if (!head) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
void Stack<T>::print()
{
	Node<T>* headptr = head;
	while (headptr) {
		cout << headptr->val << endl;
		headptr = headptr->next;
	}
}