#define _CRT_SECURE_NO_WARNINGS
#define SECTOR_SIZE 512 // 512 byte
#define SPARE_SIZE 16 // 16 byte
#define BLOCK_SIZE 32 // �̰��� byte�� �ƴ϶� ��� �ȿ� �ִ� ��(sectors + spare) ������ �ǹ�

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
    std::cout << megabytes << " megabytes �÷��� �޸𸮰� �ʱ�ȭ�� �Ϸ�Ǿ����ϴ�.\n";
}

void P_R(int PSN) {
    int Block_location = PSN / BLOCK_SIZE;
    int Cell_location = PSN % BLOCK_SIZE;

    if (Block_location < blocks.size()) {
        std::cout << "PSN�� ������ " << PSN << ": " << blocks[Block_location].cells[Cell_location].sector << "\n";
    }
    else {
        std::cout << "PSN�� ��ȿ���� �ʽ��ϴ�.\n";
        return;
    }
}

void P_W(int PSN, std::string& data) {
    int Block_location = PSN / BLOCK_SIZE;
    int Cell_location = PSN % BLOCK_SIZE;

    if (data.length() > SECTOR_SIZE) {
        std::cout << "������ ũ�Ⱑ �ʹ� Ů�ϴ�." << std::endl;
        return;
    }
    else {
        std::copy(data.begin(), data.end(), blocks[Block_location].cells[Cell_location].sector);
        std::cout << "������ �Ϸ�Ǿ����ϴ�." << std::endl;
    }
}

void P_E(int PBN) {
    if (PBN < blocks.size()) {
        blocks.erase(blocks.begin() + PBN);
        std::cout << "Block " << PBN << "�� ���ŵǾ����ϴ�.\n";
    }
    else {
        std::cout << "PSN�� ��ȿ���� �ʽ��ϴ�.\n";
        return;
    }
}

/*
int main() {

    std::cout << "init, P_R, P_W, P_E �� �ϳ��� �Է�(����� exit�Է�): " << std::endl;
    std::string insert;
    while (std::getline(std::cin, insert)) {
        if (insert == "init") {
            int megabytes;.
            std::cout << "�뷮 �Է�: " << std::endl;
            std::cin >> megabytes;
            init(megabytes);
        }
        else if (insert == "P_R") {
            int PSN;
            std::cout << "PSN ��ġ �Է�: " << std::endl;
            std::cin >> PSN;
            P_R(PSN);
        }
        else if (insert == "P_W") {
            int PSN;
            std::string data;
            std::cout << "����� PSN ��ġ�� ������ �Է�(�������� �����ؼ� �Է�): " << std::endl;
            std::cin >> PSN >> data;
            P_W(PSN, data);
        }
        else if (insert == "P_E") {
            int PBN;
            std::cout << "������ PBN ��ġ �Է�: " << std::endl;
            std::cin >> PBN;
            P_E(PBN);
        }
        else if (insert == "exit") {
            break;
        }
        else {
            std::cout << "�ȹٷ� �Է��Ͻÿ�." << std::endl;
            continue;
        }
    }
    return 0;
}

*/