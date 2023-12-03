#define SPARE_BLOCK 20
#define MEGABYTE 1048576
#define BLOCK_COUNT 32
#define SECTOR_BYTE 512

#include<string>
#include<iostream>

#include"FTL.h"

using namespace std;

/*	����-���� ����
* 
*	1. �Է¹��� �ް�����Ʈ�� �´� ������ ��� + �����ص� SPARE_BLCOK ��ŭ ����
*	2. ������ ��ϸ�ŭ �������̺��� ���� �� �������̺��� �ʱ�ȭ(flashmemory�� �������̺�� ��ġ��Ŵ)
* 
*/
void FTL::init(int megabytes) {

	//megabytes + spare_block��ŭ �÷����޸𸮸� ����
	if (blockMax == 0) {
		blockMax = (megabytes * MEGABYTE) / (SECTOR_BYTE * BLOCK_COUNT);	//1.�ް��� 1048576����Ʈ�� ������ ���
		memory.init(blockMax);
		cout << megabytes << " megabytes flash memory ;" << endl;

		//debug
		cout << "blockMax : " << blockMax << endl;
	}
	else {
		cout << "�̹� �Ҵ�� �޸𸮰� �ֽ��ϴ�." << endl;
	}

	//�������̺� ����
	mappingTable = new int[(blockMax + SPARE_BLOCK)*BLOCK_COUNT];
	for (int i = 0; i < (blockMax + SPARE_BLOCK) * BLOCK_COUNT; i++) {
		mappingTable[i] = i;
	}

	//������ �ʱ�ȭ
	spareTable = new int[SPARE_BLOCK];
	for (int i = 0; i < SPARE_BLOCK; i++) {
		spareTable[i] = blockMax + i;
	}
}

/*	����
* 
*	1. �Է¹��� sectorNum�� ������ �÷��� �޸𸮺��� ū �� Ȯ��
*	2. �������̺�� ���ν��� flash.read()�� ���� �б�
*	3. �о�� ���� �����Ѵٸ� ����, ������ �����޼��� ���.
*
*/
void FTL::read(int sectorNum) {
	string temp = "";

	if (blockMax == 0) {
		cout << "�Ҵ�� �÷��� �޸𸮰� �����ϴ�." << endl;
	}
	else {
		if (sectorNum > blockMax * SECTOR_BYTE) {
			cout << "�Ҵ�� �޸� �ּҺ��� Ů�ϴ�." << endl;
		}
		else {
			temp = memory.read(mappingTable[sectorNum]);
			if (temp.compare("") != 0) {
				cout << sectorNum / SECTOR_BYTE << "-" << sectorNum % 4 << ", data : " << temp << endl;
			}
			else {
				cout << "�ش� ���Ϳ� �����Ͱ� �����ϴ�." << endl;
			}
		}
	}
}

/*	����
*	1. �Է¹��� sectorNum�� ������ �÷��� �޸𸮺��� ū �� Ȯ��
*	2. �����Ͱ� �����ϴ��� Ȯ��
*   3. �����Ͱ� �����Ѵٸ� �������� �����͸� ����ְ� ������������ ����
*
*/
void FTL::write(int sectorNum, string data) {

	if(blockMax == 0) {
		cout << "�Ҵ�� �÷��� �޸𸮰� �����ϴ�." << endl;
	}
	else {
		if (sectorNum > blockMax * SECTOR_BYTE) {
			cout << "�Ҵ�� �޸� �ּҺ��� Ů�ϴ�." << endl;
		}
		else {
			memory.write(sectorNum, data);
		}
	}
}

/*	����
*	
*	
*
*/
void FTL::erase(int blockNum) {

	if (blockMax == 0) {
		cout << "�Ҵ�� �÷��� �޸𸮰� �����ϴ�." << endl;
	}
	else {
		if (blockNum > blockMax) {
			cout << "�Ҵ�� �޸� �ּҺ��� Ů�ϴ�." << endl;
		}
		else {
			memory.erase(blockNum);
		}
	}
}
