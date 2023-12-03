#define _CRT_SECURE_NO_WARNINGS
#define SECTOR_SIZE 512 // 512 byte
#define SPARE_SIZE 16 // 16 byte
#define BLOCK_SIZE 32 // 이것은 byte가 아니라 블록 안에 있는 셀(sectors + spare) 개수를 의미

#include <iostream>
#include <string>
#include <vector>


struct Cell {
    char sector[SECTOR_SIZE];
    char spare[SPARE_SIZE];
};


struct Block {
    std::vector<Cell> cells;
    Block() : cells(BLOCK_SIZE) {}
};


std::vector<Block> blocks;

void init(int megabytes) {
    int totalsize = megabytes * 1024 * 1024;
    int sector_spare_size = SECTOR_SIZE + 16;
    int blocksize = sector_spare_size * BLOCK_SIZE;
    int blockcount = totalsize / blocksize;

    blocks = std::vector<Block>(blockcount);
    std::cout << megabytes << " megabytes 플래시 메모리가 초기화가 완료되었습니다.\n";
}

void P_R(int PSN) {
    int Block_location = PSN / BLOCK_SIZE;
    int Cell_location = PSN % BLOCK_SIZE;

    if (Block_location < blocks.size()) {
        std::cout << "PSN의 데이터 " << PSN << ": " << blocks[Block_location].cells[Cell_location].sector << "\n";
    }
    else {
        std::cout << "PSN이 유효하지 않습니다.\n";
        return;
    }
}

void P_W(int PSN, std::string& data) {
    int Block_location = PSN / BLOCK_SIZE;
    int Cell_location = PSN % BLOCK_SIZE;

    if (data.length() > SECTOR_SIZE) {
        std::cout << "데이터 크기가 너무 큽니다." << std::endl;
        return;
    }
    else {
        std::copy(data.begin(), data.end(), blocks[Block_location].cells[Cell_location].sector);
        std::cout << "저장이 완료되었습니다." << std::endl;
    }
}

void P_E(int PBN) {
    if (PBN < blocks.size()) {
        blocks.erase(blocks.begin() + PBN);
        std::cout << "Block " << PBN << "이 제거되었습니다.\n";
    }
    else {
        std::cout << "PSN이 유효하지 않습니다.\n";
        return;
    }
}

/*
int main() {

    std::cout << "init, P_R, P_W, P_E 중 하나를 입력(종료는 exit입력): " << std::endl;
    std::string insert;
    while (std::getline(std::cin, insert)) {
        if (insert == "init") {
            int megabytes;.
            std::cout << "용량 입력: " << std::endl;
            std::cin >> megabytes;
            init(megabytes);
        }
        else if (insert == "P_R") {
            int PSN;
            std::cout << "PSN 위치 입력: " << std::endl;
            std::cin >> PSN;
            P_R(PSN);
        }
        else if (insert == "P_W") {
            int PSN;
            std::string data;
            std::cout << "기록할 PSN 위치와 데이터 입력(공백으로 구분해서 입력): " << std::endl;
            std::cin >> PSN >> data;
            P_W(PSN, data);
        }
        else if (insert == "P_E") {
            int PBN;
            std::cout << "삭제할 PBN 위치 입력: " << std::endl;
            std::cin >> PBN;
            P_E(PBN);
        }
        else if (insert == "exit") {
            break;
        }
        else {
            std::cout << "똑바로 입력하시오." << std::endl;
            continue;
        }
    }
    return 0;
}

*/