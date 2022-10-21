// You are given a string of length n and a dictionary containing k words.
// In how many ways can you create the string using the words?
class Trie {
private:
    struct Node {
        char alphabet;
        bool exist;
        vector<Node*> child;
        Node(char a): alphabet(a), exist(false) {
            child.assign(26, NULL);
        }
    };
    int dp[N];
    Node* root;
public:
    Trie() {
        root = new Node('!');
        memset(dp, -1, sizeof dp);
    }
    void insert(string word) {
        Node* cur = root;
        for (int i = 0; i < (int)word.size(); i++) {
            int alphaNum = word[i]-'a';
            if (cur -> child[alphaNum] == NULL)
                cur -> child[alphaNum] = new Node(word[i]);
            cur = cur -> child[alphaNum];
        }
        cur -> exist = true;
    }
    int calc(int index, const string&s){
        if(index == (int)s.size()) {
            return 1;
        }
        if(dp[index] != -1) {
            return dp[index];
        }
        auto &ret = dp[index];
        ret = 0;
        Node* cur = root;
        for (int i = index; i < (int)s.size(); i++) {
            int alphaNum = s[i]-'a';
            if (cur -> child[alphaNum] == NULL) {
                break;
            }
            cur = cur -> child[alphaNum];
            if (cur -> exist) {
                ret = add(ret, calc(i + 1, s));
            }
        }
        return ret;
    }
};
int main(){
    Trie trie;    
    string s;
    cin >> s;
    int k;
    cin >> k;
    while (k--) {
        string s;
        cin >> s;
        trie.insert(s);
    }
    cout<<trie.calc(0, s);
}