#ifndef DOCINFO_H
#define DOCINFO_H

#include <string>

using namespace std;

// it contains the document inforamtion
// name and frequency of a particular term
class DocInfo{
	string ID;
	int FT;
public:
	DocInfo(){
		ID = "";
		FT = 0;
	}
	void setData(string i, int f){
		ID = i;
		FT = f;
	}
	void setID(string i) {
		ID = i;
	}
	void setFT(int f) {
		FT = f;
	}
	string getID() {
		return ID;
	}
	int getFT() {
		return FT;
	}
};

#endif
