#include "../common/utils.hpp"

/* 432. All O`one Data Structure
Implement a data structure supporting the following operations:

    Inc(Key) - Inserts a new key with value 1. Or increments an existing key by 1. Key is guaranteed to be a non-empty string.
    
    Dec(Key) - If Key's value is 1, remove it from the data structure. Otherwise decrements an existing key by 1. 
        If the key does not exist, this function does nothing. Key is guaranteed to be a non-empty string.
    
    GetMaxKey() - Returns one of the keys with maximal value. If no element exists, return an empty string "".
    
    GetMinKey() - Returns one of the keys with minimal value. If no element exists, return an empty string "".

Challenge: Perform all these in O(1) time complexity. 
*/

class AllOne {
public:
    AllOne() {
        sentinal.prior=sentinal.next=&sentinal;
    }
    
    void inc(string key) {
        DLinkNode<pair<string, int>>* node;
        auto it=dict.find(key);
        if (it==dict.end()) { 
            node=new DLinkNode<pair<string, int>>;
            node->data.first=key;
            node->data.second=1;
            node->insert_after(sentinal);
            dict.insert({key,node});
            return;         
        }
        node=it->second;
        int cnt = ++node->data.second;
        auto p=node->next;
        while(p!=&sentinal && p->data.second<cnt) 
            p=p->next;
        if (p!=node->next) {
            node->unlink();
            node->insert_after(*p->prior);
        }
    }
    
    void dec(string key) {
        DLinkNode<pair<string, int>>* node;
        auto it=dict.find(key);
        if (it==dict.end()) return;
        node=it->second;
        int cnt = --node->data.second;
        if (cnt==0) {
            node->unlink();
            dict.erase(it);
            return;
        }

        auto p=node->prior;
        while(p!=&sentinal && p->data.second>cnt) 
            p=p->prior;
        if (p!=node->prior) {
            node->unlink();
            node->insert_after(*p);
        }
    }
    
    string getMaxKey() {
        return sentinal.prior==&sentinal?"":sentinal.prior->data.first;
    }
    
    string getMinKey() {
        return sentinal.next==&sentinal?"":sentinal.next->data.first;
    }
private:
    DLinkNode<pair<string, int>> sentinal;
    unordered_map<string, DLinkNode<pair<string, int>>*> dict; 
};

int main() {
    AllOne* obj = new AllOne();
    obj->inc("cpp");
    obj->inc("java");
    obj->inc("java");
    cout << obj->getMaxKey() << endl;
    cout << obj->getMinKey() << endl;
    return 0;
}