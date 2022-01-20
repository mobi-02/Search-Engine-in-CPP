#ifndef LIST_H
#define LIST_H

#include <iostream>
using namespace std;

// SIMPLE LINKED LIST

template<typename T>
class ListNode{
public:
	T data;
	ListNode* next;
	ListNode(){
		next = NULL;
	}
};

template <typename T>
class List{
	ListNode<T>* head;
	ListNode<T>* tail;
	int _size;
public:
	
	List(){
		_size = 0;
		head = tail = NULL;
	}
	
	int size(){
		return _size;
	}
	
	void append(T elm) {
		if(head == NULL) {
			head = new ListNode<T>;
			head->data = elm;
			
			tail = head;
		}
		else{
			ListNode<T>* temp=head;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = new ListNode<T>;
			temp->next->data = elm;
			tail = temp->next;
		}
		++_size;
	}
	
	void print(){
		ListNode<T>* temp=head;
		while(temp != NULL){
			cout << temp->data.getID() << endl;
			temp = temp->next;
		}
	}
	ListNode<T>* getHead(){
		return head;
	}
	ListNode<T>* getTail(){
		return tail;
	}
};

#endif
