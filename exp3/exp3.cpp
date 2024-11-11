#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>
#include <cctype>

struct BinTreeNode {
    char data;
    int frequency;
    BinTreeNode* left;
    BinTreeNode* right;

    BinTreeNode(char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}
    ~BinTreeNode() {
        delete left;
        delete right;
    }
};

class BinTree {
public:
    BinTree(char d, int f) : root(new BinTreeNode(d, f)) {}
    ~BinTree() {
        delete root;
    }

    BinTreeNode* getRoot() const {
        return root;
    }

private:
    BinTreeNode* root;
};

class HuffTree {
public:
    HuffTree(const std::string& filename) {
        std::vector<int> frequencies(256, 0);
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "无法打开文件：" << filename << std::endl;
            return;
        }
        char c;
        while (file.get(c)) {
            if (isalpha(c)) {
                frequencies[tolower(c)]++;
            }
        }
        file.close();

        std::priority_queue<BinTree*, std::vector<BinTree*>, CompareTrees> trees;
        for (int i = 0; i < frequencies.size(); ++i) {
            if (frequencies[i] > 0) {
                trees.push(new BinTree(i, frequencies[i]));
            }
        }

        while (trees.size() > 1) {
            BinTree* tree1 = trees.top();
            trees.pop();
            BinTree* tree2 = trees.top();
            trees.pop();

            BinTreeNode* newRoot = new BinTreeNode('\0', tree1->getRoot()->frequency + tree2->getRoot()->frequency);
            newRoot->left = tree1->getRoot();
            newRoot->right = tree2->getRoot();

            trees.push(new BinTree('\0', newRoot->frequency));
        }

        if (!trees.empty()) {
            huffmanTree = trees.top();
            trees.pop();
        }
    }

    ~HuffTree() {
        delete huffmanTree;
    }

    BinTreeNode* getRoot() const {
        return huffmanTree->getRoot();
    }

private:
    BinTree* huffmanTree;

    struct CompareTrees {
        bool operator()(const BinTree* lhs, const BinTree* rhs) const {
            return lhs->getRoot()->frequency > rhs->getRoot()->frequency;
        }
    };
};

typedef std::string HuffCode;

void generateCodes(BinTreeNode* node, const std::string& prefix, std::map<char, HuffCode>& codes) {
    if (node == nullptr) {
        return;
    }

    if (node->data!= '\0') {
        codes[node->data] = prefix;
        std::cout << "字符 " << node->data << " 的编码为：" << prefix << std::endl;
    }

    generateCodes(node->left, prefix + "0", codes);
    generateCodes(node->right, prefix + "1", codes);
}

int main() {
    std::string filename = "C:\\Users\\20915\\Desktop\\exp3\\word.txt";
    HuffTree huffTree(filename);
    std::map<char, HuffCode> codes;
    generateCodes(huffTree.getRoot(), "", codes);

    // 对单词"dream"进行编码
    std::string word = "dream";
    for (char c : word) {
        if (isalpha(c)) {
            std::cout << codes[tolower(c)];
        }
    }
    std::cout << std::endl;

    return 0;
}
