#include "Huffman.h"
#include <iostream>

static std::string ptrToStr(TreeNode* node) {
    return std::to_string(reinterpret_cast<uint64_t>(node));
}

static TreeNode* strToPtr(const std::string& str) {
    if (str.empty()) return nullptr;
    uint64_t val = 0;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] < '0' || str[i] > '9') return nullptr;
        val = val * 10 + (str[i] - '0');
    }
    return reinterpret_cast<TreeNode*>(val);
}

static void pushNode(SingleList& list, const std::string& val) {
    if (list.head == nullptr) {
        list.head = new SNode{val, nullptr};
    } else if (list.head->data.empty() && list.head->next == nullptr) {
        list.head->data = val;
    } else {
        push_backSList(list, val);
    }
}

static size_t countValidNodes(const SingleList& list) {
    size_t count = 0;
    SNode* curr = list.head;
    while (curr != nullptr) {
        if (strToPtr(curr->data) != nullptr) {
            count++;
        }
        curr = curr->next;
    }
    return count;
}

static TreeNode* extractMin(SingleList& list) {
    SNode* minPre = nullptr;
    SNode* minCurr = nullptr;
    TreeNode* minNode = nullptr;

    SNode* pre = nullptr;
    SNode* curr = list.head;

    while (curr != nullptr) {
        TreeNode* node = strToPtr(curr->data);
        if (node != nullptr) {
            if (minNode == nullptr || node->weight < minNode->weight) {
                minNode = node;
                minCurr = curr;
                minPre = pre;
            }
        }
        pre = curr;
        curr = curr->next;
    }

    if (minCurr == nullptr) return nullptr;

    if (minPre == nullptr) {
        list.head = minCurr->next;
    } else {
        minPre->next = minCurr->next;
    }
    delete minCurr;
    return minNode;
}

TreeNode* buildHuffmanTree(const std::string& text) {
    if (text.empty()) return nullptr;

    SingleList freeNodes;
    createSList(freeNodes);

    for (size_t i = 0; i < text.length(); ++i) {
        char s = text[i];
        SNode* curr = freeNodes.head;
        bool found = false;
        while (curr != nullptr) {
            TreeNode* node = strToPtr(curr->data);
            if (node != nullptr && node->symbol == s) {
                node->weight++;
                found = true;
                break;
            }
            curr = curr->next;
        }
        if (!found) {
            TreeNode* newNode = new TreeNode(s, 1);
            pushNode(freeNodes, ptrToStr(newNode));
        }
    }

    if (countValidNodes(freeNodes) >= 2) {
        bool swapped;
        do {
            swapped = false;
            SNode* curr = freeNodes.head;
            while (curr != nullptr && curr->next != nullptr) {
                TreeNode* n1 = strToPtr(curr->data);
                TreeNode* n2 = strToPtr(curr->next->data);
                if (n1 != nullptr && n2 != nullptr && n1->weight < n2->weight) {
                    std::string temp = curr->data;
                    curr->data = curr->next->data;
                    curr->next->data = temp;
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
    }

    while (countValidNodes(freeNodes) > 1) {
        TreeNode* leftChild = extractMin(freeNodes);
        TreeNode* rightChild = extractMin(freeNodes);

        int parentWeight = leftChild->weight + rightChild->weight;
        TreeNode* parent = new TreeNode(parentWeight, leftChild, rightChild);

        pushNode(freeNodes, ptrToStr(parent));
    }

    TreeNode* root = extractMin(freeNodes);
    killSList(freeNodes);
    return root;
}

void generateCodes(TreeNode* root, const std::string& currentCode, SingleList& table) {
    if (!root) return;

    if (!root->left && !root->right) {
        std::string code = currentCode.empty() ? "0" : currentCode;
        std::string entry = "";
        entry += root->symbol;
        entry += code;
        pushNode(table, entry);
        return;
    }

    generateCodes(root->left, currentCode + "0", table);
    generateCodes(root->right, currentCode + "1", table);
}

std::string encode(const std::string& text, const SingleList& table) {
    std::string encodedString = "";
    for (size_t i = 0; i < text.length(); ++i) {
        SNode* curr = table.head;
        while (curr != nullptr) {
            if (curr->data.length() >= 2 && curr->data[0] == text[i]) {
                encodedString += curr->data.substr(1);
                break;
            }
            curr = curr->next;
        }
    }
    return encodedString;
}

std::string decode(const std::string& binaryCode, TreeNode* root) {
    if (!root) return "";

    std::string decodedString = "";

    if (!root->left && !root->right) {
        for (size_t i = 0; i < binaryCode.length(); ++i) {
            decodedString += root->symbol;
        }
        return decodedString;
    }

    TreeNode* current = root;
    for (size_t i = 0; i < binaryCode.length(); ++i) {
        if (binaryCode[i] == '0') {
            current = current->left;
        } else if (binaryCode[i] == '1') {
            current = current->right;
        }

        if (!current->left && !current->right) {
            decodedString += current->symbol;
            current = root;
        }
    }

    return decodedString;
}

void printCodeTable(const SingleList& table) {
    std::cout << "Таблица:\n";
    SNode* curr = table.head;
    while (curr != nullptr) {
        if (curr->data.length() >= 2) {
            std::cout << curr->data[0] << " : " << curr->data.substr(1) << "\n";
        }
        curr = curr->next;
    }
}