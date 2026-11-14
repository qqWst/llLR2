#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
#include "../structs/tree.h"
#include "../structs/flist.h"
#include "Huffman.h"
using namespace std;

int main() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    string inputString;
    cout << "Ввод: ";
    getline(cin, inputString);

    if (inputString.empty()) {
        return 1;
    }

    TreeNode* huffmanTreeRoot = buildHuffmanTree(inputString);

    SingleList codeTable;
    createSList(codeTable);
    generateCodes(huffmanTreeRoot, "", codeTable);

    string encodedStr = encode(inputString, codeTable);
    cout << "Вывод: " << encodedStr << "\n";

    printCodeTable(codeTable);

    string decodedStr = decode(encodedStr, huffmanTreeRoot);
    cout << "Восстановленная строка: " << decodedStr << "\n";

    killSList(codeTable);
    deleteTree(huffmanTreeRoot);

    return 0;
}