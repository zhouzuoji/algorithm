#include "../common/utils.hpp"

class Solution {
public:
    int dfs(const vector<int>& nums, int begin, int m) {
        int ans=dp[begin*M+m-1];
        if (ans>=0) return ans;
        int n=nums.size(),right=n-m+1;
        int sum=0; ans=INT_MAX;
        for(int i=begin;i<right;i++) {
            sum+=nums[i];
            if (sum>ans) break;
            ans=min(ans, max(sum,dfs(nums, i+1, m-1)));
        }
        dp[begin*M+m-1]=ans;
        return ans;
    }

    int splitArray(const vector<int>& nums, int m) {
        M=m;
        int n=nums.size();
        if (m==n) {
            int ans=INT_MIN;
            for(int x: nums) ans=max(x,ans);
            return ans;
        }
        dp.resize(n*m, -1);
        int sum=0;
        for(int i=n-1;i>=0;--i)
            dp[i*m]=(sum+=nums[i]);
        return dfs(nums, 0, m);
    }
private:
    int M;
    vector<int> dp;
};

int main() {
    cout << Solution().splitArray({1,1,1,1,1,3,2}, 5) << endl;
    return 0;
}