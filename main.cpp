#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// A tree node for the Huffman Tree
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode *left;
    HuffmanNode *right;

    // Constructor
    HuffmanNode(char d, unsigned f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// A custom comparator to make a min-heap based on frequency
struct Compare {
    bool operator()(const HuffmanNode* left, const HuffmanNode* right) {
        return (left->freq > right->freq);
    }
};

// Preorder traversal to print Huffman codes
void printCodesPreorder(HuffmanNode* root, const string &code) {
    if (!root) return;

    // If this is a leaf node, print the code
    // A leaf node has no children
    if (!root->left && !root->right) {
        cout << code << " ";
        return;
    }
    // Traverse left
    printCodesPreorder(root->left,  code + "0");
    // Traverse right
    printCodesPreorder(root->right, code + "1");
}

// Build Huffman Tree and return its root
HuffmanNode* buildHuffmanTree(const string &S, const vector<unsigned> &freq) {
    // Create a min heap to hold tree nodes
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minHeap;

    // Create a leaf node for each character and push into heap
    for (size_t i = 0; i < S.size(); i++) {
        HuffmanNode* node = new HuffmanNode(S[i], freq[i]);
        minHeap.push(node);
    }

    // Repeat until only one node remains in the heap
    while (minHeap.size() > 1) {
        // Extract the two nodes with the smallest frequency
        HuffmanNode* leftNode  = minHeap.top();
        minHeap.pop();
        HuffmanNode* rightNode = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency = sum of the two
        HuffmanNode* internalNode = new HuffmanNode('$', leftNode->freq + rightNode->freq);
        internalNode->left  = leftNode;
        internalNode->right = rightNode;

        // Push the new node back into the min-heap
        minHeap.push(internalNode);
    }

    // The remaining node is the root of the Huffman Tree
    return minHeap.top();
}

int main() {
    int N_distict;
    cout << "Enter the number of distinct characters: ";
    cin >> N_distict;

    // Read the characters
    cout << "Enter the string of " << N_distict << " distinct characters: ";
    string S_string;
    cin >> S_string;

    // Read frequencies
    cout << "Enter the frequencies for each character in order:\n";
    vector<unsigned> freq(N_distict);
    for (int i = 0; i < N_distict; i++) {
        cin >> freq[i];
    }

    // Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(S_string, freq);

    // Print codes in Preorder
    cout << "Huffman Codes in Preorder:\n";
    printCodesPreorder(root, "");

    cout << endl;
    return 0;
}
