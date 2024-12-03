#pragma once

#include "String.h"
#include "Hashing.h"
#include <filesystem>

namespace fs = std::filesystem;

#define FOR_FAST(start, end, step) for (int i = (start); i < (end); i += (step))
#define FOR(start, end) for (int i = (start); i < (end); i++)

template <typename T>
struct TreeNode {

	// States:
	T key;
	String data;
	int numOfChildren;
	static int count;
	fs::path nodeName;
	// Hashes:
	int hashType;
	int instructorHash;
	unsigned char shaHash[SHA256_DIGEST_LENGTH];

	// Number of children by default is 2 because that will be the minimum number of children in our implementation
	TreeNode() : numOfChildren(2) { 
		count++;
		nodeName = generateNodeName();
	}

	TreeNode(T key, String data, int hashType, int numOfChildren = 2)
		: key(key), data(data), numOfChildren(2), hashType(hashType) {
		nodeName = generateNodeName();
		count++;
	}
	~TreeNode() { count--; }
	virtual TreeNode<T>* getChild(int index) = 0;
	virtual TreeNode<T>* getParent() = 0;

private:
	fs::path generateNodeName() {
		std::ostringstream oss;
		oss << "Node_" << count << ".txt";
		return oss.str();
	}
}; 

template <typename T>
int TreeNode<T>::count = 0;  // Initialize static count to 0

template<typename T>
struct AVLNode : public TreeNode<T> {

	// States:
	AVLNode* parent;
	AVLNode* descendants[2];
	int height;


	// Constructors:
	AVLNode() : height(0), parent(nullptr) { this->nullAllDescendants(); }
	AVLNode(T key, String data,int hashType) : height(0), TreeNode<T>(key, data,hashType), parent(nullptr) { this->nullAllDescendants(); }


	// Sets both descendants to nullptr:
	void nullAllDescendants() { FOR(0, this->numOfChildren) this->descendants[i] = nullptr; }
	TreeNode<T>* getChild(int index) override { return this->descendants[index]; }
	TreeNode<T>* getParent() override { return this->parent; }
};

template <typename T>
class RBNode : public TreeNode<T> {
public:
	int color; // 0:Red, 1:Black
	RBNode* parent;
	RBNode* descendants[2];

	RBNode() : color(0), parent(nullptr) { this->nullAllDescendants(); }
	RBNode(T key, String data, int hashType, RBNode* parent = nullptr)
		: color(0), TreeNode<T>(key, data, hashType), parent(parent) { this->nullAllDescendants(); }

	void nullAllDescendants() { FOR(0, this->numOfChildren) this->descendants[i] = nullptr; }
	TreeNode<T>* getChild(int index) override { return this->descendants[index]; }
	TreeNode<T>* getParent() override { return this->parent; }
};