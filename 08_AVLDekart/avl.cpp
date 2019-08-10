#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <cmath>


template<typename T>
struct node {
    explicit node(T item) : val(item) {};
    T val;
    std::shared_ptr<node<T>> left;
    std::shared_ptr<node<T>> right;
    std::shared_ptr<node<T>> parent;

    bool updateLevel() {
        size_t newLevel;
        if (!left && !right) {
            newLevel = 0;
        } else if (!left) {
            newLevel = right->level + 1;
        } else if (!right) {
            newLevel = left->level + 1;
        } else {
            newLevel = std::max(left->level, right->level) + 1;
        }
        if (newLevel != level) {
            level = newLevel;
            return true;
        }
        return false;
    }

    size_t level = 0;
};

template<typename T>
struct tree {
    void add(T item) {
        if (!root) {
            root = std::make_shared<node<T>>(item);
            root->updateLevel();
        } else {
            add(root, std::make_shared<node<T>>(item));
        }
    }

    void add(std::shared_ptr<node<T>> parent, std::shared_ptr<node<T>> child) {
        auto nodeToIns = parent;
        while (true) {
            if (child->val < nodeToIns->val) {
                if (!nodeToIns->left) {
                    nodeToIns->left = child;
                    nodeToIns->left->parent = nodeToIns;
                    break;
                } else {
                    nodeToIns = nodeToIns->left;
                }
            } else {
                if (!nodeToIns->right) {
                    nodeToIns->right = child;
                    nodeToIns->right->parent = nodeToIns;
                    break;
                } else {
                    nodeToIns = nodeToIns->right;
                }
            }
        }
        while (nodeToIns) {
            if (nodeToIns->updateLevel()) {
                nodeToIns = nodeToIns->parent;
            } else {
                break;
            }
        }
    }

    std::shared_ptr<node<T>> find(T item) {
        auto itemNode = root;
        while (itemNode && itemNode->val != item) {
            if (itemNode->val > item) {
                itemNode = itemNode->left;
            } else {
                itemNode = itemNode->right;
            }
        }
        return itemNode;
    }

    void del(std::shared_ptr<node<T>> item) {
        if (item->parent) {
            if (item->parent->val > item->val) {
                item->parent->left.reset();
            } else {
                item->parent->right.reset();
            }

            if (item->left) {
                add(item->parent, item->left);
            }
            if (item->right) {
                add(item->parent, item->right);
            }
        } else {
            root.reset();
            if (item->left) {
                root = item->left;
                root->parent.reset();
            }
            if (item->right) {
                if (root) {
                    add(root, item->right);
                } else {
                    root = item->right;
                    root->parent.reset();
                }
            }
        }
        item->parent.reset();
        item->left.reset();
        item->right.reset();
    }

    void print() {
        if (!root)
            return;
        std::vector<std::shared_ptr<node<T>>> currentLevel;
        currentLevel.push_back(root);
        size_t level = root->level;
        while (std::any_of(currentLevel.begin(), currentLevel.end(), [](auto ptr) { return ptr; })) {

            for (size_t offset = 0; offset < std::pow(2, level) - 1; ++offset) {
                std::cout << ' ';
            }
            std::vector<std::shared_ptr<node<T>>> nextLevel;
            for (auto &item:currentLevel) {
                if (!item) {
                    std::cout << ' ';
                    nextLevel.push_back(std::shared_ptr<node<T>>());
                    nextLevel.push_back(std::shared_ptr<node<T>>());
                } else {
                    std::cout << item->val;
                    nextLevel.push_back(item->left);
                    nextLevel.push_back(item->right);
                }
                for (size_t offset = 0; offset < (std::pow(2, level) - 1) * 2 + 1; ++offset) {
                    std::cout << ' ';
                }
            }
            --level;
            std::cout << std::endl;
            currentLevel = nextLevel;
        }
    }

    std::shared_ptr<node<T>> root;
};

int main() {
    std::vector<char> chars;
    size_t len = 10;
    for (char c = 'A'; c < 'A' + len; ++c) {
        chars.push_back(c);
    }
    std::random_shuffle(chars.begin(), chars.end());
    tree<char> tree;
    for (char c:chars) {
        std::cout << "Adding " << c << std::endl;
        tree.add(c);
        tree.print();
        std::cout << "----" << std::endl;
    }
    std::random_shuffle(chars.begin(), chars.end());
    for (char c:chars) {
        std::cout << "Removing " << c << std::endl;
        tree.del(tree.find(c));
        tree.print();
        std::cout << "----" << std::endl;
    }

    return 0;
}