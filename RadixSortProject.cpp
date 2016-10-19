#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class listNode{

    friend class linkedListStack;
    friend class linkedListQueue;
    friend class RadixSort;

private:

    string data;
    listNode* next;

public:

    listNode();
    ~listNode();
    listNode(string d, listNode* n);
    listNode(string d);

    string getData();
    void setData(string d);
    listNode* getNext();
    void setNext(listNode* n);

};

listNode::listNode(){
    setData("dummy");
    setNext(NULL);
}
listNode::~listNode(){
    //destructor
}

listNode::listNode(string d, listNode* n){
    setData(d);
    setNext(n);
}

listNode::listNode(string d){
    setData(d);
    setNext(NULL);
}

string listNode::getData(){
    return data;
}

void listNode::setData(string d){
    data = d;
}

listNode* listNode::getNext(){
    return next;
}

void listNode::setNext(listNode* n){
    next = n;
}

//Start of Linked List Stack Class

class linkedListStack{

private:

    listNode* top;
    int theSize = 0;

public:

    linkedListStack();
    listNode* getTop();
    void setTop(listNode* top);
    int size();
    void push(listNode* newNode);
    listNode* pop();
    bool isEmpty();
    void printStack(ofstream& outFile);

};

linkedListStack::linkedListStack(){
    setTop(NULL);
}
listNode* linkedListStack::getTop(){
    return top;
}
void linkedListStack::setTop(listNode* t){
    top = t;
}
int linkedListStack::size(){
    return theSize;
}
void linkedListStack::push(listNode* newNode){
    if(isEmpty()){
        newNode->next = NULL;
    }
    else{
        newNode->next = top;
    }
    top = newNode;
    theSize++;
}
listNode* linkedListStack::pop(){
    listNode* temp = NULL;
    if(isEmpty()){

	    cout<<"Stack is empty";

    }
    else{

        temp = top;
        top = top->next;
        theSize--;

    }
    return temp;
}
bool linkedListStack::isEmpty(){
    if(top == NULL){
        return true;
    }
    return false;
}
void linkedListStack::printStack(ofstream& outFile){
    listNode* temp = top;
    while(temp != NULL){
        outFile<<temp->data<<endl;
        temp = temp->next;
    }
    outFile<<endl<<endl;
}

//Start of Linked List Queue Class

class linkedListQueue{

    friend class RadixSort;

private:
    listNode* head;
    listNode* tail;
    int theSize;

public:
    linkedListQueue();
    void addTail(listNode* newNode);
    listNode* deleteHead();
    bool isEmpty();
    void printQueue(ofstream& outFile);
    string removeSpace(string word);
};

linkedListQueue::linkedListQueue(){
    listNode* dummy = new listNode();
    head = dummy;
    tail = dummy;
    theSize = 0;
}

void linkedListQueue::addTail(listNode* newNode){
    if(isEmpty()){
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = tail->next;
    }
    theSize++;

}
listNode* linkedListQueue::deleteHead(){
    listNode* temp = NULL;
    if(isEmpty()){

	    cout<<"Queue is empty."<<endl;

    }
    else if(theSize == 1){
        temp = head;
        head = NULL;
        tail = NULL;
        theSize--;
    }
    else{
        temp = head;
        head = head->next;
        theSize--;
    }
    return temp;
}

bool linkedListQueue::isEmpty(){
    if(theSize == 0){
        return true;
    }
    return false;
}

string linkedListQueue::removeSpace(string word) {
 while (1){
   int letter = word.find(' ');
   if (letter == -1 ){
     break;
   }
   word = word.erase(letter, 1);
 }
 return word;
}

void linkedListQueue::printQueue(ofstream& outFile){
    listNode* temp = head;
	int i = 0;
    while(i < theSize){
        outFile<<removeSpace(temp->data)<<" ";
        temp = temp->next;
        i++;
    }
}

//Start of Radix Sort Class

class RadixSort{

private:
    int tableSize = 256;
    linkedListQueue** hashTable;

public:
    RadixSort();
    void padString(listNode* node, int length);
	char getVal(listNode* node, int currentDigit);
	int hashIndex(char data);
	void addTail(listNode* node, int currentTable, int hashIndex);
	void printTable(ofstream& outFile, int currentTable);
	int currentTable(int table);
	listNode* deleteHead(int table, int currentQueue);
	bool isCurrentQueueEmpty(int table, int queue);

};

RadixSort::RadixSort(){

	hashTable = new linkedListQueue*[2];
	for(int row = 0; row < 2; row++){
		hashTable[row] = new linkedListQueue[256];
	}

}

void RadixSort::padString(listNode* node, int length){

	string space = " ";
	string word;

	for(int i = node->data.length(); i<10; i++){
		word = node->data.append(space);
	}
	//cout<<node->data<<endl;
}

char RadixSort::getVal(listNode* node, int currentDigit){

	int index = node->data.length() - 1;
	return node->data[index - currentDigit];

}

int RadixSort::hashIndex(char data){

	int index = (int)data;
	return index;

}

void RadixSort::addTail(listNode* node, int currentTable, int hashIndex){

	hashTable[currentTable][hashIndex].addTail(node);
	//cout<<hashIndex<<" "<<node->data<<endl;

}

void RadixSort::printTable(ofstream& outFile, int currentTable){

	for(int col = 0; col < 256; col++){

		if(!hashTable[currentTable][col].isEmpty()){

			outFile<<"Table "<<"["<<currentTable<<"]"<<"["<<col<<"]: ";
			hashTable[currentTable][col].printQueue(outFile);
			outFile<<endl;

		}

	}
	outFile<<endl<<endl;
}

int RadixSort::currentTable(int table){

	for(int i = 0; i < 256; i++){

		if(!hashTable[table][i].isEmpty()){

			return i;

		}

	}

}

listNode* RadixSort::deleteHead(int table, int currentQueue){

	return hashTable[table][currentQueue].deleteHead();

}

bool RadixSort::isCurrentQueueEmpty(int table, int queue){

	if(hashTable[table][queue].isEmpty()){

		return true;

	}

	return false;

}

//Start of Main

int main(int argc, char **argv){

	ifstream inFile(argv[1]);
	ofstream outFile(argv[2]);

	int tableSize = 256;
	int currentDigit;
    int currentTable;
    int previousTable;
    int currentQueue;
	int temp;
	int hashIndex;
	int longestStringLength = 0;

    linkedListStack top;
	string inputWord;
	


    while(inFile >> inputWord){

    	if(inputWord.length() > longestStringLength){

    		longestStringLength = inputWord.length();
	outFile<<"huh"<<endl;
		}

    	listNode* newNode = new listNode(inputWord);
    	top.push(newNode);
    	

	}

	inFile.close();
	top.printStack(outFile);

    RadixSort radix;
    currentDigit = 0;
    currentTable = 0;

    while(!top.isEmpty()){

    	listNode* node = top.pop();
    	radix.padString(node, longestStringLength);
    	hashIndex = radix.hashIndex(radix.getVal(node, currentDigit));
    	radix.addTail(node, currentTable, hashIndex);

	}

	radix.printTable(outFile, currentTable);

	currentDigit++;
	currentTable = 1;
	previousTable = 0;
	currentQueue = 0;

	while(currentDigit < longestStringLength){

		while(currentQueue <= tableSize - 1){

			while(!radix.isCurrentQueueEmpty(previousTable, currentQueue)){

				listNode* node2 = radix.deleteHead(previousTable, currentQueue);
				hashIndex = radix.hashIndex(radix.getVal(node2, currentDigit));
				radix.addTail(node2, currentTable, hashIndex);

			}

			currentQueue++;

		}

		temp = currentTable;
		currentTable = previousTable;
		previousTable = temp;
		currentQueue = 0;
		currentDigit++;
	}

	radix.printTable(outFile, previousTable);
	outFile.close();

	return 0;
}

