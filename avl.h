#ifndef AVL_H
#define AVL_H


#include<iostream>
#include<string>
using namespace std;

template<typename T>
class node {
public:
    T data;
    int height;
    node<T>* left;
    node<T>* right;
    node(T dt) {
        data = dt;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
class AVL {
private:
    node<T>* root;
    int total_elements;
public: 
	//constructor and copy constructor, just for requirements
    AVL(){
    	root = NULL;
    	total_elements = 0;
    }
    AVL(AVL& other){
    	root = other.root;
    	total_elements = other.total_elements;
    }
    
    int height(node<T>* head) {
        if (head == NULL) return 0;
        return head->height;
    }
    
    // next 4 functions are for inserting data into AVL trees
    void insert(T data) {
        root = insertUtil(root, data);
    }
    
    // performaing right rotaion
    node<T>* rightRotation(node<T>* head) {
        node<T>* newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }
    // performaing right rotaion
    node<T>* leftRotation(node<T>* head) {
        node<T>* newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }
    // inserting data and calculting new root if imbalanced
	node<T>* insertUtil(node<T>* head, T data) {
        if(head == NULL) {
            total_elements += 1;
            node<T>* temp = new node<T>(data);
            return temp;
        }
        if((data.getKeyTerm())[0] < (head->data.getKeyTerm())[0]){
        	head->left = insertUtil(head->left, data);
        }
        else if((data.getKeyTerm())[0] > (head->data.getKeyTerm())[0]){
        	head->right = insertUtil(head->right, data);
        }
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if(bal > 1) {
            if((data.getKeyTerm())[0] < (head->left->data.getKeyTerm())[0]) {
                return rightRotation(head);
            }
            else{
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }
        else if(bal < -1) {
            if((data.getKeyTerm())[0] > (head->right->data.getKeyTerm())[0]) {
                return leftRotation(head);
            }
            else{
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
	//priting tree in preorder
	void print() {
        preorder(root);
        cout << endl;
    }
    void preorder(node<T>* head) {
        if(head == NULL){
        	return;
        }
        cout << head->data.getKeyTerm() << " " << head->data.size() << endl;
        head->data.print();
        cout << endl;
        
        preorder(head->left);
        preorder(head->right);
    }
    // searching from tree
    node<T>* search(string x) {
        return searchUtil(root, x);
    }
    node<T>* searchUtil(node<T>* head, string x) {
        if(head == NULL){
        	return NULL;
        }
        string k = head->data.getKeyTerm();
        if(k == x){
        	return head;
        }
        else if(k[0] > x[0]){
        	return searchUtil(head->left, x);
        }
        else{
        	return searchUtil(head->right, x);
    	}
    }
    //Destructor
    void DestroyRecursive(node<T>* r){
    	if(r != NULL){
      		DestroyRecursive(r->left);
    	    DestroyRecursive(r->right);
    	    delete r;
    	}
	}
    ~AVL(){
    	DestroyRecursive(root);
	}
};

#endif
