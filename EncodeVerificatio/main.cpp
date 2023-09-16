#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>
#include <ctime>

// Define a structure for Huffman Tree Node
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

// Custom comparator for priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->frequency > right->frequency;
    }
};

// Create a Huffman Tree from given character frequencies
HuffmanNode* buildHuffmanTree(std::unordered_map<char, int>& frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> minHeap;

    for (auto pair : frequencies) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        minHeap.push(newNode);
    }

    return minHeap.top();
}

// Generate Huffman codes for characters
void generateHuffmanCodes(HuffmanNode* root, std::string code, std::unordered_map<char, std::string>& huffmanCodes) {
    if (!root)
        return;

    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Encode the input file and write to the output file
void encodeFile(std::string inputFile, std::string outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    std::unordered_map<char, int> frequencies;
    char ch;

    while (inFile.get(ch)) {
        frequencies[ch]++;
    }

    HuffmanNode* root = buildHuffmanTree(frequencies);
    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Write Huffman codes to the output file
    for (auto pair : huffmanCodes) {
        outFile << pair.first << " " << pair.second << std::endl;
    }

    // Reset file pointer and encode the file content
    inFile.clear();
    inFile.seekg(0);

    std::string encodedData = "";

    while (inFile.get(ch)) {
        encodedData += huffmanCodes[ch];
    }

    // Pad the encoded data to a multiple of 8
    int paddingBits = 8 - (encodedData.length() % 8);

    for (int i = 0; i < paddingBits; i++) {
        encodedData += '0';
    }

    // Write the number of padding bits to the output file
    outFile << paddingBits << std::endl;

    // Write the encoded data to the output file as bytes
    for (size_t i = 0; i < encodedData.length(); i += 8) {
        std::bitset<8> byte(encodedData.substr(i, 8));
        outFile.put(static_cast<char>(byte.to_ulong()));
    }

    // Free memory
    delete root;
}

// Decode the input file and write to the output file
void decodeFile(std::string inputFile, std::string outputFile) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    std::unordered_map<std::string, char> reverseHuffmanCodes;

    int paddingBits;
    inFile >> paddingBits;
    inFile.get(); // Read newline character after paddingBits

    char ch;
    std::string code;

    // Read and parse Huffman codes from the input file
    while (inFile >> code >> ch) {
        reverseHuffmanCodes[code] = ch;
    }

    std::string encodedData;
    while (inFile.get(ch)) {
        encodedData += std::bitset<8>(ch).to_string();
    }

    // Remove the padding bits
    encodedData = encodedData.substr(0, encodedData.length() - paddingBits);

    std::string currentCode;
    for (char bit : encodedData) {
        currentCode += bit;
        if (reverseHuffmanCodes.find(currentCode) != reverseHuffmanCodes.end()) {
            outFile << reverseHuffmanCodes[currentCode];
            currentCode.clear();
        }
    }
}

// Generates random text of a specified size
std::string generateRandomText(std::size_t sizeInBytes) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::string randomText;
    randomText.reserve(sizeInBytes);

    for (std::size_t i = 0; i < sizeInBytes; ++i) {
        randomText.push_back(characters[std::rand() % characters.length()]);
    }

    return randomText;
}

int main() {

    std::size_t fileSizeInBytes = 10 * 1024 * 1024; // 10MB

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::ofstream outFile("input.txt");

    if (!outFile) {
        std::cerr << "Error: Could not create the file." << std::endl;
        return 1;
    }

    std::string randomText = generateRandomText(fileSizeInBytes);

    outFile << randomText;
    outFile.close();

    std::cout << "Generated input.txt with a size of 10MB." << std::endl;

    std::string inputFile = "input.txt";
    std::string compressedFile = "compressed.bin";
    std::string decompressedFile = "decompressed.txt";

    // Encode the input file
    encodeFile(inputFile, compressedFile);

    // Decode the compressed file
    decodeFile(compressedFile, decompressedFile);

    std::cout << "File compression and decompression completed." << std::endl;

    return 0;
}