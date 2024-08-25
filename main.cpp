#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string sha256(const std::string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

class Block {
public:
    std::string previousHash;
    std::string hash;
    std::string data;
    time_t timestamp;

    Block(std::string data, std::string previousHash = "")
        : data(data), previousHash(previousHash), timestamp(time(nullptr)) {
        hash = calculateHash();
    }

    std::string calculateHash() const {
        std::stringstream ss;
        ss << previousHash << timestamp << data;
        return sha256(ss.str());
    }
};

class Blockchain {
public:
    Blockchain() {
        chain.push_back(createGenesisBlock());
    }

    void addBlock(const Block& newBlock) {
        chain.push_back(newBlock);
    }

    const std::vector<Block>& getChain() const {
        return chain;
    }

private:
    std::vector<Block> chain;

    Block createGenesisBlock() {
        return Block("Genesis Block");
    }
};

int main() {
    Blockchain myBlockchain;

    myBlockchain.addBlock(Block("First Block Data"));
    myBlockchain.addBlock(Block("Second Block Data"));

    for(const auto& block : myBlockchain.getChain()) {
        std::cout << "Previous Hash: " << block.previousHash << std::endl;
        std::cout << "Hash: " << block.hash << std::endl;
        std::cout << "Data: " << block.data << std::endl;
        std::cout << "Timestamp: " << ctime(&block.timestamp) << std::endl;
        std::cout << "-------------------------" << std::endl;
    }

    return 0;
}
