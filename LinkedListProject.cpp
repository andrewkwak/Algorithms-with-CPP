#include <iostream>
#include <fstream>
using namespace std;

class listNode{
	
	friend class LinkedList;
	
	private:
		string data;
		listNode* next;
		
	public:
		listNode(){
			next = NULL;
			data = "dummy";
		}
		listNode(string d, listNode* n){
			data = d;
			next = n;
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
		listNode* head;
		listNode* spot;
		int count;
		
	public:
		LinkedList();
		~LinkedList();
		void listInsert(listNode* spot, listNode* newNode);
		listNode* findSpot(string d);
		void printList(listNode* inserted, ofstream& outFile);
};

LinkedList::LinkedList(){
	head = new listNode();
}
LinkedList::~LinkedList(){
	//destructor
}
void LinkedList::listInsert(listNode* spot, listNode* newNode){
	newNode -> next = spot -> next;
	spot -> next = newNode;
	count++;
}
listNode* LinkedList::findSpot(string d){
	spot = head;
	while(spot->next != NULL && spot->next->data < d){
		spot = spot->next;
	}
	return spot;
}
void LinkedList::printList(listNode* inserted, ofstream& outFile){
	listNode* temp = head;
	outFile << "Inserted Data(" << inserted->data <<"):\n"; 
	while(temp->next != NULL){
		outFile <<"("<<temp->data<<", "<<temp->next->data<<") --> ";
		temp = temp->next;
		if(temp->next == NULL){
			outFile <<"(" << temp->data<<", null)\n\n";
			break;
		}
	}

	
}



int main(int argc, char** argv) {
	
	ifstream inFile1 (argv[1]);
	ofstream outFile1 (argv[2]);
	string commonWord;
	LinkedList CwordlistHead;

	
	while(inFile1 >> commonWord){

		listNode* spot = CwordlistHead.findSpot(commonWord);
		listNode* newNode = new listNode(commonWord, NULL);
		CwordlistHead.listInsert(spot, newNode);
		CwordlistHead.printList(newNode, outFile1);
		
		
	}
	
	inFile1.close();
	outFile1.close();
	
	
	
	return 0;
}
