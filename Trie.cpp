class Trie {
private:
    struct Node {
        char alphabet;
        bool exist; // or end of word, or count of words
        vector<Node*> child;
        Node(char a): alphabet(a), exist(false) {
            child.assign(26, NULL);
        }
    };
    
    Node* root;
 
public:
    Trie() {
        root = new Node('!');
    }
 
    void insert(string word) {
        Node* cur = root;
        for (int i = 0; i < (int) word.size(); i++) {
            int alphaNum = word[i] - 'a';
            if (cur -> child[alphaNum] == NULL) {
                cur -> child[alphaNum] = new Node(word[i]);
            }
            cur = cur -> child[alphaNum];
        }
        cur -> exist = true;
    }
};
