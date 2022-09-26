#include "bits/stdc++.h"
using namespace std;
typedef long long ll;

class LinesReaderForStupidProblems{
    string line;

public:
    vector<string> getStrings(string line) {
        string temp;
        vector<string> ret;
        for (auto ch: line) {
            if (ch == ' ') {
                ret.push_back(temp);
                temp.clear();
            } else {
                temp.push_back(ch);
            }
        }
        ret.push_back(temp);
        return ret;
    }
};