#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template <typename T> class BSTNode {
private:
  unique_ptr<BSTNode<T>> left;
  unique_ptr<BSTNode<T>> right;
  unique_ptr<T> data;

public:
  BSTNode(T value) {
    data = make_unique<T>(value);
    left = nullptr;
    right = nullptr;
  }

  ~BSTNode() {
    left.reset();
    right.reset();
    data.reset();
  }

  T getData() { return data; }

  BSTNode<T> getLeft() { return *left; }

  BSTNode<T> getRight() { return *right; }

  bool leftIsNull() { return *left == nullptr; }
  bool rightIsNull() { return right == nullptr; }

  void resetLeft() { left.reset(); }
  void resetRight() { right.reset(); }

  void releaseLeft() { left.release(); }
  void relesaeRight() { right.release(); }

  BSTNode<T> setLeft(BSTNode<T> node) {
    left.reset();
    left = make_unique<T>(node);
  }

  BSTNode<T> setRight(BSTNode<T> node) {
    right.reset();
    right = make_unique<T>(node);
  }
};

template <typename T> class BST {
private:
  unique_ptr<BSTNode<T>> trunk;
  int size;

public:
  BST(vector<T> values) {
    for (T value : values) {
      insert(value);
    }
  }

  ~BST() { trunk.reset(); }

  void insert(T value) {
    unique_ptr<BSTNode<T>> node = make_unique<T>(BSTNode<T>(value));

    if (trunk == nullptr) {
      trunk = node;
      size++;
      return;
    }

    BSTNode<T> currentNode = *trunk;

    bool side = value < currentNode.getData();

    while (side ? !currentNode.leftIsNull() : !currentNode.rightIsNull()) {
      currentNode = side ? currentNode.left() : currentNode.right();
      side = value < currentNode.getData();
    }

    if (side) {
      currentNode.setLeft(node);
    } else {
      currentNode.setRight(node);
    }

    size++;
    return;
  }

  void insertNode(T node) {
    T value = node.getData();

    if (trunk == nullptr) {
      trunk = node;
      size++;
      return;
    }

    BSTNode<T> currentNode = *trunk;

    bool side = value < currentNode.getData();

    while (side ? !currentNode.leftIsNull() : !currentNode.rightIsNull()) {
      currentNode = side ? currentNode.left() : currentNode.right();
      side = value < currentNode.getData();
    }

    if (side) {
      currentNode.setLeft(node);
    } else {
      currentNode.setRight(node);
    }

    size++;
    return;
  }

  void remove(T value) {
    if (trunk == nullptr) {
      return;
    }

    bool currentNodeIsRoot = true;
    BSTNode<T> currentNodeBranch = *trunk;
    BSTNode<T> currentNode = *trunk;

    bool side = value < currentNode.getData();

    while (currentNode.getData() != value) {
      currentNodeBranch = currentNode;
      currentNodeIsRoot = false;

      side = value < currentNode.getData();
      if (side ? currentNode.leftIsNull() : currentNode.rightIsNull()) {
        return;
      }

      currentNode = side ? currentNode.left() : currentNode.right();
    }

    if (currentNode.leftIsNull()) {
      if (currentNode.rightIsNull()) {
        if (currentNodeIsRoot) {
          trunk.reset();
        } else {
          if (side) {
            currentNodeBranch.resetLeft();
          } else {
            currentNodeBranch.resetRight();
          }
        }
      } else {
        if (currentNodeIsRoot) {
          BSTNode<T> *newTrunk = trunk.releaseRight();
          delete trunk;
          trunk = make_unique<T>(newTrunk);
        } else {
          BSTNode<T> *node;
          if (side) {
            node = currentNodeBranch.releaseLeft();
          } else {
            node = currentNodeBranch.releaseLeft();
          }

          currentNodeBranch.setRight((*node).getRight());
          delete node;
        }
      }
    } else {
      if (currentNodeIsRoot) {
        BSTNode<T> *newTrunk = trunk.releaseLeft();
        BSTNode<T> right = *trunk.releaseRight();
        delete trunk;
        trunk = make_unique<T>(newTrunk);
        insert(right);
      } else {
        BSTNode<T> *node;
        if (side) {
          node = currentNodeBranch.releaseLeft();
        } else {
          node = currentNodeBranch.releaseLeft();
        }

        currentNodeBranch.setRight((*node).getRight());
        insertNode((*node).releaseRight());
        delete node;
      }
    }

    return;
  }
};

int main() {
  return 0;
}