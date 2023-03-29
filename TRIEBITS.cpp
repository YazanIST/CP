const int INT_SIZE = 30;
 
struct Node {
    int cnt;
    vector<Node *> child;
    Node() {
        cnt = 0;
        child.assign(2, NULL);
    }
};
 
class Trie {
private:
    Node *root;
 
public:
    Trie() {
        root = new Node();
    }
 
    void insert(int p) {
        Node *cur = root;
        for (int i = INT_SIZE - 1; i >= 0; i--) {
            bool curBit = (1 << i) & p;
            if (!cur->child[curBit]) {
                cur->child[curBit] = new Node();
            }
            cur = cur->child[curBit];
            cur->cnt++;
        }
    }

    void remove(int p) {
        Node *cur = root;
        for (int i = INT_SIZE - 1; i >= 0; i--) {
            bool curBit = (1 << i) & p;
            cur = cur->child[curBit];
            cur->cnt--;
        }
    }
 
    int searchMinXor(int x) {
        int ret = 0;
        Node *cur = root;
        for (int i = INT_SIZE - 1; i >= 0; i--) {
            bool curBit = (1 << i) & x;
            if (cur->child[curBit] && cur->child[curBit]->cnt > 0) {
                ret = (ret << 1);
                cur = cur->child[curBit];
            } else {
                ret = (ret << 1) | 1;
                cur = cur->child[!curBit];
            }
        }
        return ret;
    }

    int searchMaxXor(int x) {
        int ret = 0;
        Node *cur = root;
        for (int i = INT_SIZE - 1; i >= 0; i--) {
            bool curBit = (1 << i) & x;
            if (cur->child[!curBit]) {
                ret = (ret << 1) | 1;
                cur = cur->child[!curBit];
            } else {
                ret = (ret << 1);
                cur = cur->child[curBit];
            }
        }
        return ret;
    }
};
