#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>

using namespace std;

class listNode{
	
	friend class LinkedList;
	
	private:
		string data; 
		listNode *next;
		int count;
		
	public:
		listNode(){
			data = "dummy";
			next = NULL;
			count = 0;
		}		
		listNode(string d, listNode *n){
			data = d;
			next = n;
			count++;
		}
		string getData(){
			return data;
		}
		listNode* getNext(){
			return next;
		}
		
};

class LinkedList{
	
	private:
		listNode *head;
		listNode *spot;
		listNode *next;

	public:
		LinkedList(void);
		~LinkedList(void);
		
		void listInsert(listNode *spot, listNode *newNode);
		listNode* findSpot(string d);
		bool isCommonWord(LinkedList list, string d);
		void debugPrint(ofstream& outFile, LinkedList list);
		void printSortedList(ofstream& outFile2, LinkedList list);
};


LinkedList::LinkedList(){
	head = new listNode();
}
LinkedList::~LinkedList(){
	
}

void LinkedList::listInsert(listNode* spot, listNode *newNode){
	
	newNode->next = spot->next;
	spot->next = newNode;
	
}

listNode* LinkedList::findSpot(string d){
	
	spot = head;
	while(spot->next != NULL && spot->next->data < d){
		spot = spot->next;
	}
	next = spot->next;
	if(next != NULL && next->data == d){
		next->count++;
		return NULL;
	}
	else{
		return spot;
	}
}

bool LinkedList::isCommonWord(LinkedList list, string d){
	
	spot = list.head;
	while(spot->next != NULL){
		
		if(spot->data == d){
			return true;
		}
		spot = spot->next;
	}
	return false;
}

void LinkedList::debugPrint(ofstream& outFile, LinkedList list){
	
	spot = list.head;
	int insertionCount = 0;
	
	outFile << "listHead --> ";
	
	while(spot->next != NULL){
		
		outFile << "(" << spot->data << ", " << spot->next->data << ") --> ";
		spot = spot->next;
		insertionCount++;
		if(insertionCount >= 5){
			outFile << endl;
			insertionCount = 0;
		}
		
		if(spot->next == NULL){
			outFile << "(" << spot->data << ", null)";
			break;
		}
		
	}
	
	outFile.close();
	
}

void LinkedList::printSortedList(ofstream& outFile, LinkedList list){
	
	spot = list.head;
	while(spot->next != NULL){
		outFile << "Word Count(" << spot->data << "): ";
		outFile << spot->count <<endl;
		spot = spot->next;
	}
	outFile.close();
}


int main(int argc, char** argv) {
	
	
	ifstream inFile1 (argv[1]);
	ifstream inFile2 (argv[2]);
	ofstream outFile1(argv[3]);
	ofstream outFile2(argv[4]);

	
	LinkedList CwordlistHead;
	
	string commonWord;
	
	while(inFile1 >> commonWord){
		
		listNode *spot = CwordlistHead.findSpot(commonWord);
		listNode *newNode = new listNode(commonWord, NULL);
		CwordlistHead.listInsert(spot, newNode);
		
	}
	inFile1.close();
	
	
	LinkedList textListHead;
	
	string textWord;
	
	while(inFile2 >> textWord){
		
		if(textListHead.isCommonWord(CwordlistHead, textWord) == false){
			
			listNode *spot = textListHead.findSpot(textWord);
			
			if(spot == NULL){
				continue;
			}
			else{
				listNode *newNode = new listNode(textWord, NULL);
				textListHead.listInsert(spot, newNode);
			}
			
		}
		

		
	}
	
		textListHead.debugPrint(outFile1, textListHead);
		textListHead.printSortedList(outFile2, textListHead);
	
	return 0;
}
