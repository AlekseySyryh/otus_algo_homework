#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <cmath>
#include <sstream>


template<typename T>
struct node {
    explicit node(T item) : val(item) {};
    T val;
    std::shared_ptr<node<T>> left;
    std::shared_ptr<node<T>> right;
    std::shared_ptr<node<T>> parent;

    bool updateLevel() {
        int newLevel;
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

    int level = 0;
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

    void checkBalance(std::shared_ptr<node<T>> node) {
        while (node) {
            node->updateLevel();
                if (doTurns) {
                    int left = node->left ? node->left->level : -1;
                    int right = node->right ? node->right->level : -1;
                    if (left - right >= 2) {
                        int ll;
                        if (!node->left || !node->left->left) {
                            ll = 0;
                        } else {
                            ll = node->left->left->level;
                        }
                        int lr;
                        if (!node->left || !node->left->right) {
                            lr = 0;
                        } else {
                            lr = node->left->right->level;
                        }
                        if (ll >= lr) {
                            smallRightTurn(node);
                            node = node->parent;
                        } else {
                            bigRightTurn(node);
                            node = node->parent;
                        }
                    } else if (left - right <= -2) {
                        int rr;
                        if (!node->right || !node->right->right) {
                            rr = 0;
                        } else {
                            rr = node->right->right->level;
                        }
                        int rl;
                        if (!node->right || !node->right->left) {
                            rl = 0;
                        } else {
                            rl = node->right->left->level;
                        }
                        if (rr >= rl) {
                            smallLeftTurn(node);
                            node = node->parent;
                        } else {
                            bigLeftTurn(node);
                            node = node->parent;
                        }
                    }
                }
            if (node)
                node = node->parent;
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
        checkBalance(child);
    }

    void smallLeftTurn(std::shared_ptr<node<T>> a) {
        auto b = a->right;
        auto c = b->left;
        a->right = c;
        b->left = a;
        b->parent = a->parent;
        a->parent = b;
        if (c)
            c->parent = a;
        a->updateLevel();
        b->updateLevel();
        if (a == root) {
            root = b;
        } else {
            if (b->parent->left == a)
                b->parent->left = b;
            else
                b->parent->right = b;
        }
    }

    void smallRightTurn(std::shared_ptr<node<T>> a) {
        auto b = a->left;
        auto c = b->right;
        a->left = c;
        b->right = a;
        b->parent = a->parent;
        a->parent = b;
        if (c)
            c->parent = a;
        a->updateLevel();
        b->updateLevel();
        if (a == root) {
            root = b;
        } else {
            if (b->parent->left == a)
                b->parent->left = b;
            else
                b->parent->right = b;
        }
    }

    void bigLeftTurn(std::shared_ptr<node<T>> a) {
        auto b = a->right;
        smallLeftTurn(a);
        smallLeftTurn(a);
        smallRightTurn(b);
    }

    void bigRightTurn(std::shared_ptr<node<T>> a) {
        auto b = a->left;
        smallRightTurn(a);
        smallRightTurn(a);
        smallLeftTurn(b);
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
        checkBalance(item->parent);
        item->parent.reset();
        item->left.reset();
        item->right.reset();

    }

    std::string print() {
        std::ostringstream oss;
        if (!root)
            return oss.str();
        std::vector<std::shared_ptr<node<T>>> currentLevel;
        currentLevel.push_back(root);
        size_t level = root->level;
        while (std::any_of(currentLevel.begin(), currentLevel.end(), [](auto ptr) { return ptr; })) {

            for (size_t offset = 0; offset < std::pow(2, level) - 1; ++offset) {
                oss << ' ';
            }
            std::vector<std::shared_ptr<node<T>>> nextLevel;
            for (auto &item:currentLevel) {
                if (!item) {
                    oss << ' ';
                    nextLevel.push_back(std::shared_ptr<node<T>>());
                    nextLevel.push_back(std::shared_ptr<node<T>>());
                } else {
                    oss << item->val;
                    nextLevel.push_back(item->left);
                    nextLevel.push_back(item->right);
                }
                for (size_t offset = 0; offset < (std::pow(2, level) - 1) * 2 + 1; ++offset) {
                    oss << ' ';
                }
            }
            --level;
            oss << std::endl;
            currentLevel = nextLevel;
        }
        return oss.str();
    }

    std::shared_ptr<node<T>> root;

    //Возможность отключить повороты для тестов
    bool doTurns = true;
};

void smallLeftTurnTest() {
/* Например:
       B                         F
   A       F             ->    B   H
         E   H                A E G Z
            G Z                           */
    tree<char> srt;
    //Без поворота
    srt.doTurns = false;
    srt.add('B');
    srt.add('A');
    srt.add('F');
    srt.add('E');
    srt.add('H');
    srt.add('G');
    srt.add('Z');
    std::string result = srt.print();
    std::string before = result;
    result = std::string(result.begin(),
                         std::remove(result.begin(), result.end(), ' '));//Удаляем пробелы, что-бы было проще сравнивать
    if (result != "B\nAF\nEH\nGZ\n") {
        std::cerr << "Small left turn pre check fail";
        exit(EXIT_FAILURE);
    }
    //Поворачиваем вручную
    srt.smallLeftTurn(srt.root);
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "F\nBH\nAEGZ\n") {
        std::cerr << "Small left turn turn check fail";
        exit(EXIT_FAILURE);
    }
    //А теперь - пусть сам вертит!
    srt = {};
    srt.add('B');
    srt.add('A');
    srt.add('F');
    srt.add('E');
    srt.add('H');
    srt.add('G');
    srt.add('Z');
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "F\nBH\nAEGZ\n") {
        std::cerr << "Small left turn auto turn check fail";
        exit(EXIT_FAILURE);
    }
    std::cout << "Small left turn check complete" << std::endl << "Before: " << std::endl << before << "After: "
              << std::endl << srt.print() << std::endl;
}

void smallRightTurnTest() {
/* Например:
             H                         D
         D       Z                   B   H
       B   F               ->       A C F Z
      A C                                             */
    tree<char> srt;
    //Без поворота
    srt.doTurns = false;
    srt.add('H');
    srt.add('D');
    srt.add('B');
    srt.add('F');
    srt.add('A');
    srt.add('C');
    srt.add('Z');
    std::string result = srt.print();
    std::string before = result;
    result = std::string(result.begin(),
                         std::remove(result.begin(), result.end(), ' '));//Удаляем пробелы, что-бы было проще сравнивать
    if (result != "H\nDZ\nBF\nAC\n") {
        std::cerr << "Small right turn pre check fail";
        exit(EXIT_FAILURE);
    }
    //Поворачиваем вручную
    srt.smallRightTurn(srt.root);
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "D\nBH\nACFZ\n") {
        std::cerr << "Small right turn turn check fail";
        exit(EXIT_FAILURE);
    }
    //А теперь - пусть сам вертит!
    srt = {};
    srt.add('H');
    srt.add('D');
    srt.add('B');
    srt.add('F');
    srt.add('A');
    srt.add('C');
    srt.add('Z');
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "D\nBH\nACFZ\n") {
        std::cerr << "Small right turn auto turn check fail";
        exit(EXIT_FAILURE);
    }
    std::cout << "Small right turn check complete" << std::endl << "Before: " << std::endl << before << "After: "
              << std::endl << srt.print() << std::endl;
}

void bigLeftTurnTest() {
/* Например:
       B                         F
   A       H             ->    B   H
         F   Z                A E G Z
        E G                            */
    tree<char> srt;
    //Без поворота
    srt.doTurns = false;
    srt.add('B');
    srt.add('A');
    srt.add('H');
    srt.add('F');
    srt.add('Z');
    srt.add('E');
    srt.add('G');
    std::string result = srt.print();
    std::string before = result;
    result = std::string(result.begin(),
                         std::remove(result.begin(), result.end(), ' '));//Удаляем пробелы, что-бы было проще сравнивать
    if (result != "B\nAH\nFZ\nEG\n") {
        std::cerr << "Big left turn pre check fail";
        exit(EXIT_FAILURE);
    }
    //Поворачиваем вручную
    srt.bigLeftTurn(srt.root);
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "F\nBH\nAEGZ\n") {
        std::cerr << "Big left turn turn check fail";
        exit(EXIT_FAILURE);
    }
    //А теперь - пусть сам вертит!
    srt = {};
    srt.add('B');
    srt.add('A');
    srt.add('H');
    srt.add('F');
    srt.add('Z');
    srt.add('E');
    srt.add('G');
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "F\nBH\nAEGZ\n") {
        std::cerr << "Big left turn auto turn check fail";
        exit(EXIT_FAILURE);
    }
    std::cout << "Big left turn check complete" << std::endl << "Before: " << std::endl << before << "After: "
              << std::endl << srt.print() << std::endl;
}

void bigRightTurnTest() {
/* Например:
             H                         D
         B       Z                   B   H
       A   D               ->       A C F Z
          C F                                         */
    tree<char> srt;
    //Без поворота
    srt.doTurns = false;
    srt.add('H');
    srt.add('B');
    srt.add('Z');
    srt.add('A');
    srt.add('D');
    srt.add('C');
    srt.add('F');
    std::string result = srt.print();
    std::string before = result;
    result = std::string(result.begin(),
                         std::remove(result.begin(), result.end(), ' '));//Удаляем пробелы, что-бы было проще сравнивать

    if (result != "H\nBZ\nAD\nCF\n") {
        std::cerr << "Big right turn pre check fail";
        exit(EXIT_FAILURE);
    }
    //Поворачиваем вручную
    srt.bigRightTurn(srt.root);
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "D\nBH\nACFZ\n") {
        std::cerr << "Big right turn turn check fail";
        exit(EXIT_FAILURE);
    }
    //А теперь - пусть сам вертит!
    srt = {};
    srt.add('H');
    srt.add('B');
    srt.add('Z');
    srt.add('A');
    srt.add('D');
    srt.add('C');
    srt.add('F');
    result = srt.print();
    result = std::string(result.begin(), std::remove(result.begin(), result.end(), ' '));
    if (result != "D\nBH\nACFZ\n") {
        std::cerr << "Big right turn auto turn check fail";
        exit(EXIT_FAILURE);
    }
    std::cout << "Big right turn check complete" << std::endl << "Before: " << std::endl << before << "After: "
              << std::endl << srt.print() << std::endl;
}

void test(bool seq) {
    std::vector<char> chars;
    for (char c = '0'; c <= '9'; ++c) {
        chars.push_back(c);
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        chars.push_back(c);
    }
    if (!seq)
        std::random_shuffle(chars.begin(), chars.end());
    tree<char> tree;
    for (char c:chars) {
        std::cout << "Adding " << c << std::endl;
        tree.add(c);
        std::cout << tree.print() << std::endl;
        std::cout << "----" << std::endl;
    }
    if (!seq)
        std::random_shuffle(chars.begin(), chars.end());
    for (char c:chars) {
        std::cout << "Removing " << c << std::endl;
        tree.del(tree.find(c));
        std::cout << tree.print() << std::endl;
        std::cout << "----" << std::endl;
    }
}

int main() {
    smallLeftTurnTest();
    smallRightTurnTest();
    bigRightTurnTest();
    bigLeftTurnTest();
    std::cout << "Sequencial test" << std::endl;
    test(true);
    std::cout << "Random test" << std::endl;
    test(false);

    return 0;
}