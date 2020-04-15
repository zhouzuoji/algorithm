#include "../common/utils.hpp"

class Solution {
private:
    struct TreeNode{
        int val,lchild,rchild,numless,repeat;
        inline void init() { lchild=rchild=-1; numless=0; repeat=1;  }
    };    
public:
    vector<int> countSmaller(const vector<int>& nums) {
        if (nums.empty()) return {};
        int n=nums.size();
        vector<int> ans(n);
        m_nodes.resize(n);   
        int root=n-1;
        m_nodes[root].init();
        m_nodes[root].val=nums[root];
        ans[root]=0;
        m_nodes[root].repeat=1;
        for(int i=n-2;i>=0;--i) {
            int cur=root, numless=0;
            while (cur>=0) {
                if (m_nodes[cur].val==nums[i]) {
                    m_nodes[cur].repeat++;
                    ans[i]=m_nodes[cur].numless+numless;
                    break;
                }   
                if (m_nodes[cur].val<nums[i]) { 
                    numless+=m_nodes[cur].numless+m_nodes[cur].repeat;
                    if (m_nodes[cur].rchild>=0) {
                        cur=m_nodes[cur].rchild;
                        continue;
                    }
                    else {
                        m_nodes[cur].rchild=i;
                        m_nodes[i].init();
                        m_nodes[i].val=nums[i];                      
                        ans[i]=numless;
                        break;                        
                    }
                }
                else {
                    m_nodes[cur].numless++;
                    if (m_nodes[cur].lchild>=0) {
                        cur=m_nodes[cur].lchild;
                        continue;
                    }
                    else {
                        m_nodes[cur].lchild=i;
                        m_nodes[i].init();
                        m_nodes[i].val=nums[i];   
                        ans[i]=numless;
                        break;                        
                    }                   
                }                     

            }
        }
        return ans;
    }
private:
    vector<TreeNode> m_nodes;
};

int main() {
    vector<int> nums=randomInts(20);
    cout << nums << endl;
    cout << Solution().countSmaller(nums) << endl;
    return 0;
}