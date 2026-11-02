#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    unsigned char character;
    int frequency;
    Node* left;
    Node* right;

    Node(unsigned char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(const Node* first, const Node* second) const {
        return first->frequency > second->frequency; // Min-heap: sabse kam frequency pehle.
    }
};

void buildCodes(Node* root, const string& path, unordered_map<unsigned char, string>& codes) {
    if (root == nullptr) return;

    if (root->left == nullptr && root->right == nullptr) {
        // Ek hi unique character ho to uska code khaali nahi rehna chahiye.
        codes[root->character] = path.empty() ? "0" : path;
        return;
    }
    buildCodes(root->left, path + '0', codes);
    buildCodes(root->right, path + '1', codes);
}

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string text;
    cout << "Enter the text to encode: ";
    getline(cin, text); // getline se spaces wala text bhi read hota hai.

    if (text.empty()) {
        cout << "There is no text to encode.\n";
        return 0;
    }

    unordered_map<unsigned char, int> frequency;
    for (unsigned char ch : text) ++frequency[ch];

    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;
    for (const auto& entry : frequency)
        minHeap.push(new Node(entry.first, entry.second));

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        Node* parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }

    Node* root = minHeap.top();
    unordered_map<unsigned char, string> codes;
    buildCodes(root, "", codes);

    string encoded;
    for (unsigned char ch : text) encoded += codes[ch];

    cout << "\nHuffman codes (character : code):\n";
    for (const auto& entry : codes) {
        if (entry.first == ' ') cout << "[space]";
        else if (entry.first == '\n') cout << "[newline]";
        else cout << entry.first;
        cout << " : " << entry.second << '\n';
    }
    cout << "Encoded bits: " << encoded << '\n';

    // Huffman tree par encoded bits chala kar original text wapas banate hain.
    string decoded;
    if (root->left == nullptr && root->right == nullptr) {
        // Single-character text mein har encoded 0 wahi character represent karta hai.
        decoded.assign(encoded.size(), static_cast<char>(root->character));
    } else {
        Node* current = root;
        for (char bit : encoded) {
            current = (bit == '0') ? current->left : current->right;
            if (current->left == nullptr && current->right == nullptr) {
                decoded += static_cast<char>(current->character);
                current = root;
            }
        }
    }

    cout << "Decoded text: " << decoded << '\n';
    deleteTree(root);
    return 0;
}
