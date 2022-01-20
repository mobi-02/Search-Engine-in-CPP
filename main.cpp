#include "searchengine.h"

int main(){
	string docs[5] = {"doc1.txt", "doc2.txt", "doc3.txt", "doc4.txt", "doc5.txt"};
	SearchEngine se;
	se.Create_Index(5, docs);

	cout << "\t\t\tSEARCH ENGINE\n\n";
	while(1){
		string query = "";
		cout << "Press \'!\' 3 times to exit search engine" << endl;
		cout << "NOTE: press enter to seach by default query: drug schizophrenia" << endl;
		cout << "Enter a query to search: ";
		getline(cin, query);
		if(query == "!!!")
			break;
	
		// user query
		if(query.size() > 0){
			for(int i=0; i<query.size(); ++i){
				if(query[i]>='A' && query[i]<='Z'){
					query[i] += 32;
				}
			}
			se.Search_Documents(query);
		}
		//default query
		else
			se.Search_Documents();
	}
	cout << "\nGOOD  BYE!!!" << endl;
	return 0;
}
