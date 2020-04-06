#include "utils.hpp"

class Solution {
public:
    void dfs(string& s, size_t idx, size_t left, size_t right, size_t removed) {
        if (removed==redundancy || idx==s.size()) {
            size_t i=idx;
            while(i<s.size()) {
                if (s[i]=='(') ++left;
                else if (s[i]==')') {
                    ++right;
                    if (right>left) return;
                }
                ++i;
            }  
            if (left==right) 
                ans.insert(path+s.substr(idx));  
            return;                 
        }

        if (s[idx]=='(') {
            dfs(s, idx+1, left, right, removed+1);
            path.push_back(s[idx]);
            dfs(s, idx+1, left+1, right, removed);
            path.pop_back();
        }
        else if (s[idx]==')') {
            dfs(s, idx+1, left, right, removed+1);
            if (left>right) {
                path.push_back(s[idx]);
                dfs(s, idx+1, left, right+1, removed);
                path.pop_back();
            }
        }
        else {
            path.push_back(s[idx]);
            dfs(s, idx+1, left, right, removed);
            path.pop_back();
        }
    }

    vector<string> removeInvalidParentheses(string s) {
        size_t left=0,right=0;
        redundancy=0;
        for(size_t i=0;i<s.size();++i) {
            if (s[i]=='(') {
                if (right>left) {
                    redundancy+=right-left;
                    left=right=0;
                }
                ++left;
            }
            else if (s[i]==')') 
                ++right;
        }
        if (redundancy==0 && left==right) return {s};
        if (left<right) redundancy+=right-left;
        else redundancy+=left-right;
        path.reserve(s.size());
        dfs(s, 0, 0, 0, 0);
        if (ans.empty()) return {""};
        return vector<string>(ans.begin(),ans.end());
    }
private:
    unordered_set<string> ans;
    string path;
    size_t redundancy;
};

int main() {
    cout << Solution().removeInvalidParentheses(")()))())))");
    return 0;
}