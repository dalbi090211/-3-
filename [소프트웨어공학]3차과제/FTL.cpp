#define SPARE_BLOCK 20
#define MEGABYTE 1048576
#define BLOCK_COUNT 32
#define SECTOR_BYTE 512

#include<string>
#include<iostream>

#include"FTL.h"

using namespace std;

/*	정적-섹터 매핑
* 
*	1. 입력받은 메가바이트에 맞는 개수의 블록 + 정의해둔 SPARE_BLCOK 만큼 생성
*	2. 생성한 블록만큼 매핑테이블을 생성 및 매핑테이블을 초기화(flashmemory와 매핑테이블과 일치시킴)
* 
*/
void FTL::init(int megabytes) {

	//megabytes + spare_block만큼 플래쉬메모리를 생성
	if (blockMax == 0) {
		blockMax = (megabytes * MEGABYTE) / (SECTOR_BYTE * BLOCK_COUNT);	//1.메가를 1048576바이트로 가정한 경우
		memory.init(blockMax);
		cout << megabytes << " megabytes flash memory ;" << endl;

		//debug
		cout << "blockMax : " << blockMax << endl;
	}
	else {
		cout << "이미 할당된 메모리가 있습니다." << endl;
	}

	//매핑테이블 생성
	mappingTable = new int[(blockMax + SPARE_BLOCK)*BLOCK_COUNT];
	for (int i = 0; i < (blockMax + SPARE_BLOCK) * BLOCK_COUNT; i++) {
		mappingTable[i] = i;
	}

	//스페어영역 초기화
	spareTable = new int[SPARE_BLOCK];
	for (int i = 0; i < SPARE_BLOCK; i++) {
		spareTable[i] = blockMax + i;
	}
}

/*	수정
* 
*	1. 입력받은 sectorNum이 생성된 플래쉬 메모리보다 큰 지 확인
*	2. 매핑테이블과 매핑시켜 flash.read()를 통해 읽기
*	3. 읽어온 값이 존재한다면 리턴, 없으면 오류메세지 출력.
*
*/
void FTL::read(int sectorNum) {
	string temp = "";

	if (blockMax == 0) {
		cout << "할당된 플래시 메모리가 없습니다." << endl;
	}
	else {
		if (sectorNum > blockMax * SECTOR_BYTE) {
			cout << "할당된 메모리 주소보다 큽니다." << endl;
		}
		else {
			temp = memory.read(mappingTable[sectorNum]);
			if (temp.compare("") != 0) {
				cout << sectorNum / SECTOR_BYTE << "-" << sectorNum % 4 << ", data : " << temp << endl;
			}
			else {
				cout << "해당 섹터에 데이터가 없습니다." << endl;
			}
		}
	}
}

/*	쓰기
*	1. 입력받은 sectorNum이 생성된 플래쉬 메모리보다 큰 지 확인
*	2. 데이터가 존재하는지 확인
*   3. 데이터가 존재한다면 스페어영역에 데이터를 집어넣고 가비지영역에 저장
*
*/
void FTL::write(int sectorNum, string data) {

	if(blockMax == 0) {
		cout << "할당된 플래시 메모리가 없습니다." << endl;
	}
	else {
		if (sectorNum > blockMax * SECTOR_BYTE) {
			cout << "할당된 메모리 주소보다 큽니다." << endl;
		}
		else {
			memory.write(sectorNum, data);
		}
	}
}

/*	삭제
*	
*	
*
*/
void FTL::erase(int blockNum) {

	if (blockMax == 0) {
		cout << "할당된 플래시 메모리가 없습니다." << endl;
	}
	else {
		if (blockNum > blockMax) {
			cout << "할당된 메모리 주소보다 큽니다." << endl;
		}
		else {
			memory.erase(blockNum);
		}
	}
}
