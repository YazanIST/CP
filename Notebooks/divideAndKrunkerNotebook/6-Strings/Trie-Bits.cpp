struct Node {
    bool bit;
    int count;
    vector<Node *> child;
    Node(bool a) : bit(a), count(0) {
        child.assign(2, NULL);
    }
};

class Trie {
private:
    Node *root;

    int getAns(int p, int l, int dep, Node *curNode) {
        if (curNode == NULL) {
            return 0;
        }

        bool curBit = bool(((1 << dep) & p)) ^ curNode->bit;

        if (curBit) {
            if ((1 << dep) & l) {
                return getAns(p, l, dep - 1, curNode->child[0]) +
                        getAns(p, l, dep - 1, curNode->child[1]);
            } else {
                return 0;
            }
        } else {
            if ((1 << dep) & l) {
                return curNode->count;
            } else {
                return getAns(p, l, dep - 1, curNode->child[0]) +
                    getAns(p, l, dep - 1, curNode->child[1]);
            }
        }
    }

public:
    Trie() {
        root = new Node(false);
    }

    void insert(int p) {
        Node *cur = root;
        for (int i = 27; i >= 0; i--) {
            bool curBit = (1 << i) & p;
            if (cur->child[curBit] == NULL) {
                cur->child[curBit] = new Node(curBit);
            }
            cur = cur->child[curBit];
            cur->count++;
        }
    }

    void remove(int p) {
        Node *cur = root;
        for (int i = 27; i >= 0; i--) {
            bool curBit = (1 << i) & p;
            cur = cur->child[curBit];
            cur->count--;
        }
    }

    int getAns(int p, int l) {
        Node *newRoot = root;
        return getAns(p, l, 28, newRoot);
    }
};