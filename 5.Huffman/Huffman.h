#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <string>
#include "../structs/tree.h"
#include "../structs/flist.h"

TreeNode* buildHuffmanTree(const std::string& text);
void generateCodes(TreeNode* root, const std::string& currentCode, SingleList& table);
std::string encode(const std::string& text, const SingleList& table);
std::string decode(const std::string& binaryCode, TreeNode* root);
void printCodeTable(const SingleList& table);

#endif