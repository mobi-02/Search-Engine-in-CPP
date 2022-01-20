#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include "avl.h"
#include "terminfo.h"

#include <map>
#include <fstream>
#include <sstream>

//used for ranking
template<typename T1, typename T2>
class Pair{
public:
	T1 first;
	T2 second;
	Pair(){}
	Pair(T1 d1, T2 d2) {
		first = d1;
		second = d2;
	}
};

//used for ranking
template<typename T1, typename T2, typename T3>
class Trio{
public:
	T1 first;
	T2 second;
	T3 third;
	Trio(){}
	Trio(T1 d1, T2 d2, T3 d3) {
		first = d1;
		second = d2;
		third = d3;
	}
};



class SearchEngine{
	AVL<TermInfo> root;
	List<string> docs;
	int total_docs;
public:
	SearchEngine(){
		total_docs = 0;
	}
	void Create_Index(int size, string documents[]) {
		for(int i = 0; i < size; ++i) {
			Add_Doc_to_Index(documents[i]);
		}
		cout << "\t\t\tTree result:\n";
		root.print();
	}
	
	void Add_Doc_to_Index(string fileName) {
		docs.append(fileName);
		++total_docs;
		
		map<string, int> freq_counter;
		ifstream file(fileName);
		string data, word;
		
		while(getline(file, data)){
			stringstream stream(data);
		// checking frequency of each word in file
			while(getline(stream, word, ' ')) {
				if(freq_counter.find(word) == freq_counter.end()){ 
					freq_counter[word] = 0;
				}
				else{
					freq_counter[word] += 1;
				}
			}
		}
		file.close();
		
		// inserting data into AVL trees
		for (map<string, int>::iterator itr = freq_counter.begin(); itr != freq_counter.end(); ++itr) {
    		DocInfo dInfo;
    		dInfo.setData(fileName, itr->second);
    		node<TermInfo>* res = root.search(itr->first);
    		// check if node is present in tree or not, if not make a node
    		// else append data into node's list
    		if(res == NULL) {
    			TermInfo tInfo(itr->first, dInfo);
    			root.insert(tInfo);
    		}
    		else{
    			res->data.add(dInfo);
    		}
    	}
	}
	
	void Search_Documents(string query="drug schizophrenia"){
		map<string, Pair<int, int>> ranker;
		string word;
		stringstream stream(query);
		bool flag = false;
		
		// breaking sentence into word to check into tree
		while(getline(stream, word, ' ')){
			node<TermInfo>* res = root.search(word);
			if(res != NULL) {
				// if word is found in tree, get that word's list
				ListNode<DocInfo>* tInfo = res->data.getList();
				// iterate over list (list has multiple Documents information)
				while(tInfo != NULL) {
					DocInfo dInfo = tInfo->data;
					//getting information of document
					string ID = dInfo.getID();
					int FT = dInfo.getFT();
					
					//check if document is not present then make a node in mapp
					//else update the existing node
					if(ranker.find(ID) == ranker.end()){
						ranker[ID] = Pair<int,int>(1, FT);
					}
					else{
						Pair<int, int> p = ranker[ID];
						p.first  = p.first + 1;
						p.second = p.second + FT;
						ranker[ID] = p;
					}
					tInfo = tInfo->next;
				}
				flag = true;
			}
		}
		
		// check if atleast one word of your query is present in data
		if(flag) {
			//making Trio of each documnet i.e DocName, #of query term, #of collective frequency term
			List<Trio<string, int, int>> data;
			for(map<string, Pair<int, int>>::iterator it=ranker.begin(); it!=ranker.end(); ++it){
				string ID = it->first;
				int qTerm = it->second.first;
				int fTerm = it->second.second;
				data.append(Trio<string, int, int>(ID, qTerm, fTerm));
			}
			// ranking based on rules(actually sorting)
			ranked(data);
			cout << "\t\tRanked Documents are: \n";
			ListNode<Trio<string,int, int>>* it = data.getHead();
			while(it != NULL) {
				cout << it->data.first << endl;
				it = it->next;
			}
			cout << endl;
		}
		
		else {
			cout << "No document found related to you query" << endl << endl;;
		}
	}
	
	template<typename T1, typename T2, typename T3>
	void ranked(List<Trio<T1, T2, T3>> &data){
		// bubble sorting on retrieved data
		ListNode<Trio<T1,T2, T3>>* outer = data.getHead();
		while(outer->next != NULL) {
			ListNode<Trio<T1,T2, T3>>* inner = outer->next;
			while(inner != NULL) {
				// swapped for query terms
				if(outer->data.second < inner->data.second){
					swap(outer->data, inner->data);
				}
				else if(outer->data.second == inner->data.second){
					//swap for collective frequency term if query terms are same
					if(outer->data.third < inner->data.third){
						swap(outer->data, inner->data);
					}
					else if(outer->data.third == inner->data.third){
						//swap for alphabetical order if collective frequency term are same
						if(outer->data.first > inner->data.first){
							swap(outer->data, inner->data);
						}
					}
				}
				inner = inner->next;
			}
			outer = outer->next;
		}
	}
};
#endif
