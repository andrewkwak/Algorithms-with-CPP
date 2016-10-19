#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class PQSort{
		
	private:
		
		int* PQAry;
		int pqSize;
		int root;
			
	public:
		
		PQSort(int size);
		~PQSort();
		int size();
		int parent(int index);
		int leftChild(int index);
		int rightChild(int index);
		bool isPQAryEmpty();
		bool isPQAryFull();
		void printPQAry(PQSort pq, ofstream& outFile);
		void buildPQAry(PQSort pq, ifstream& inFile, ofstream& outFile);
		void insertOneDataItem(int data);
		void upBubble(int index);
		int deleteRoot();
		void bubbleDown(int index);
		void deletePQAry(PQSort pq, ofstream& outFile2);
		
	};
	
	PQSort::PQSort(int size){
		
		PQAry = new int[size];
		pqSize = size;
		PQAry[0] = 0;

	}	
	PQSort::~PQSort(){
		
	}
	int PQSort::size(){
		return PQAry[0];
	}
	int PQSort::parent(int index){
		return (index/2);
	}
	int PQSort::leftChild(int index){
		return (2+index);
	}
	int PQSort::rightChild(int index){
		return (2*index + 1);
	}
	bool PQSort::isPQAryFull(){
		return (pqSize == PQAry[0]+1);
	}
	bool PQSort::isPQAryEmpty(){
		return (size() == 0);
	}
	void PQSort::insertOneDataItem(int data){
		if(isPQAryFull()){
			cout<<"Heap is full!";
			exit(0);
		}
		PQAry[PQAry[0]+1] = data;
		upBubble(PQAry[0]+1);
		PQAry[0]++;
	}
	void PQSort::upBubble(int index){
		int parentIndex, upBubbleValue;
		upBubbleValue = PQAry[index];
		while(index > 1){
			parentIndex = parent(index);
			if(upBubbleValue >= PQAry[parentIndex]) break;
			PQAry[index] = PQAry[parentIndex];
			index = parentIndex;
		}
		PQAry[index] = upBubbleValue;
	}
	void PQSort::printPQAry(PQSort pq, ofstream& outFile){
		
		for(int i = 0; i <= PQAry[0]; i++){
			outFile<<PQAry[i]<<" ";
		}
		outFile << endl;
		if(PQAry[0] == 10){
			outFile.close();
		}
	}
	
	void PQSort::buildPQAry(PQSort pq, ifstream& inFile, ofstream& outFile){
		int counter = 0;
		int data;
		while(inFile >> data){
			if(counter < 10){
				printPQAry(pq, outFile);
			}
			pq.insertOneDataItem(data);
			counter++;

		}
	}
	int PQSort::deleteRoot(){
		root = PQAry[1];
		PQAry[1] = PQAry[size()];
		PQAry[size()] = 0;
		PQAry[0]--;
		bubbleDown(1);
		
		return root;
	}
	void PQSort::bubbleDown(int index){	
	    int leftChildIndex, rightChildIndex, smallestChildIndex;
	    int temp; 
		int downBubbleValue;

	    
	    while (leftChild(index) <= size())
	    {
		  downBubbleValue = PQAry[index];
	      leftChildIndex = leftChild(index);
	      smallestChildIndex = leftChildIndex;
	      if (rightChild(index) <= size())
	      {
	        rightChildIndex = rightChild(index);
	        if (PQAry[leftChildIndex] > PQAry[rightChildIndex]){
	          smallestChildIndex = rightChildIndex;
	      	}
	      }
	      if (PQAry[smallestChildIndex] >= downBubbleValue) break;
	      
	      temp = PQAry[index];
		  PQAry[index] = PQAry[smallestChildIndex];
		  PQAry[smallestChildIndex] = temp;
	      index = smallestChildIndex;
	      
	    }
	    PQAry[index] = downBubbleValue;
	}

	void PQSort::deletePQAry(PQSort pq, ofstream& outFile2){
		
		while(!pq.isPQAryEmpty()){
		
			int root = pq.deleteRoot();
			outFile2 << root << " ";
			pq.printPQAry(pq, outFile);
			
		}
		outFile2.close();
		
	}
	
int main(int argc, char** argv) {
	
	ifstream inFile (argv[1]);
	ofstream outFile1 (argv[2]);
	ofstream outFile2 (argv[3]);
	
	int data;
	int counter = 0;
	
	while(inFile >> data){
		
		counter++;
		
	}
	inFile.close();
	PQSort pqSort(counter+1);
	inFile.open(argv[1]);
	pqSort.buildPQAry(pqSort, inFile, outFile1);
	pqSort.deletePQAry(pqSort, outFile2);
	
	return 0;
}
