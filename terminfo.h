#ifndef TERMINFO_H
#define TERMINFO_H

#include "list.h"
#include "docinfo.h"

#include <string>

using namespace std;

// it contains a list of document of a unique word
// it is considered as key of node in AVL tree
class TermInfo{
	List<DocInfo> docs_list;
	string keyTerm;
public:
	TermInfo(){}
	TermInfo(string term, DocInfo doc){
		keyTerm = term;
		docs_list.append(doc);
	}
	void print(){
		docs_list.print();
	}
	void add(DocInfo doc){
		docs_list.append(doc);
	}
	ListNode<DocInfo>* getList(){
		return docs_list.getHead();
	}
	string getKeyTerm(){
		return keyTerm;
	}
	int size(){
		return docs_list.size();
	}
};

#endif
