#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

const int LOG = 19;

class PersistentQueue {
    struct Node {
        int val;
        vector<int> up;

        Node() {
            up.resize(LOG);
        }
    };

    struct Version {
        int lastNode, size; 

        Version(int lastNode, int size): lastNode(lastNode), size(size) {}
    };

    vector<Node> nodes;
    vector<Version> versions;
public:
    PersistentQueue() {
        nodes.push_back(Node());
        versions.push_back(Version(0, 0));
    }

    int pop(int v) {
        versions.push_back(Version(versions[v].lastNode, versions[v].size - 1));
        int node = versions[v].lastNode;
        int k = versions[v].size - 1;
        for (int i = LOG - 1; i >= 0; i--) {
            if (k & (1 << i)) {
                node = nodes[node].up[i];
            }
        }
        return nodes[node].val;
    }

    void push(int v, int x) {
        versions.push_back(Version(nodes.size(), versions[v].size + 1));
        nodes.push_back(Node());
        auto &node = nodes.back();
        node.val = x;
        node.up[0] = versions[v].lastNode;
        for (int i = 1; i < LOG; i++) {
            node.up[i] = nodes[node.up[i - 1]].up[i - 1];
        }
    }
};


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int q;
    cin >> q;

    PersistentQueue persistentQueue;

    while (q--) {
        int op, v;
        cin >> op >> v;
        v++;
        if (op == 0) {
            int x;
            cin >> x;
            persistentQueue.push(v, x);
        } else {
            cout << persistentQueue.pop(v) << '\n';
        }
    }
}