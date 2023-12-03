#include<string>
#include<iostream>

#include"FlashMemory.h"

using namespace std;

class FTL {
private:
	flashMemory memory;
	int* mappingTable;
	int* spareTable;
	int* garbageTable;
	int blockMax = 0;

public:
	void init(int megabytes);
	void read(int sectorNum);
	void write(int sectorNum, string data);
	void erase(int blockNum);

};
