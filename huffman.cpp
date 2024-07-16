#include<bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

void printCodes(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

void HuffmanCoding(const string& text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (auto pair : freq) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() != 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        int sum = left->freq + right->freq;
        Node* top = new Node('\0', sum);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    Node* root = minHeap.top();

    unordered_map<char, string> huffmanCode;
    printCodes(root, "", huffmanCode);

    cout << "Huffman Codes are:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << "\n";
    }

    cout << "\nOriginal string: " << text << "\n";

    string str = "";
    for (char ch : text) {
        str += huffmanCode[ch];
    }

    cout << "Encoded string: " << str << "\n";
}

int main() {
    string text = "Huffman coding is a data compression algorithm.";
    HuffmanCoding(text);
    return 0;
}