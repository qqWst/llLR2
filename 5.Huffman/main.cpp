#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include "structs/tree.h"
#include "structs/flist.h"
#include "Huffman.h"

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::string inputString;
    std::cout << "Ввод: ";
    std::getline(std::cin, inputString);

    if (inputString.empty()) {
        return 1;
    }

    TreeNode* huffmanTreeRoot = buildHuffmanTree(inputString);

    SingleList codeTable;
    createSList(codeTable);
    generateCodes(huffmanTreeRoot, "", codeTable);

    std::string encodedStr = encode(inputString, codeTable);
    std::cout << "Вывод: " << encodedStr << "\n";

    printCodeTable(codeTable);

    std::string decodedStr = decode(encodedStr, huffmanTreeRoot);
    std::cout << "Восстановленная строка: " << decodedStr << "\n";

    killSList(codeTable);
    deleteTree(huffmanTreeRoot);

    return 0;
}