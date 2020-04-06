#include "utils.hpp"

class Solution
{
public:
    inline uint64_t makeKey(uint64_t left, uint64_t right, uint64_t begin, uint64_t end)
    {
        return (left << 48) + (right << 32) + (begin << 16) + end;
    }

    int dfs(const vector<int> &nums, size_t left, size_t right, size_t begin, size_t end)
    {
        uint64_t key = makeKey(left, right, begin, end);
        auto it = dp.find(key);
        if (it != dp.end())
            return it->second;
        int lr = left * right;
        if (begin + 1 == end)
            return lr * nums[begin];
        int ans = max(lr * nums[begin] + dfs(nums, nums[begin], right, begin + 1, end),
                      lr * nums[end - 1] + dfs(nums, left, nums[end - 1], begin, end - 1));
        for (size_t i = begin + 1; i + 1 < end; ++i)
        {
            int x = dfs(nums, left, nums[i], begin, i);
            int y = dfs(nums, nums[i], right, i + 1, end);
            int sum = x + y + nums[i] * lr;
            if (sum > ans)
                ans = sum;
        }
        dp.insert({key, ans});
        return ans;
    }

    int maxCoins(const vector<int> &nums)
    {
        size_t n = nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];
        int ans = dfs(nums, 1, 1, 0, n);
        return ans;
    }

private:
    unordered_map<uint64_t, int> dp;
};

class Solution2
{
public:
    int dodp(size_t left, size_t right)
    {
        if (left + 1 == right)
            return 0;
        int ans = dp.get(left, right);
        if (ans > 0)
            return ans;
        int LxR = nums[left] * nums[right];
        for (size_t i = left + 1; i < right; ++i)
            ans = max(ans, nums[i] * LxR + dodp(left, i) + dodp(i, right));
        dp.set(left, right, ans);
        return ans;
    }

    int maxCoins(const vector<int> &_nums)
    {
        size_t n = _nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return _nums[0];
        n += 2;
        nums.resize(n);
        nums[0] = nums[n - 1] = 1;
        std::copy(_nums.begin(), _nums.end(), nums.begin() + 1);
        dp.resize(n, n);
        return dodp(0, n - 1);
    }

private:
    vector<int> nums;
    Array2D<int> dp;
};

class Solution3
{
public:
    int maxCoins(const vector<int> &_nums)
    {
        size_t n = _nums.size();
        if (n == 0)
            return 0;
        if (n == 1)
            return _nums[0];
        else
        {
            n+=2;
            vector<int> nums(n);
            nums[0] = nums[n-1] = 1;
            std::copy(_nums.begin(), _nums.end(), nums.begin() + 1);
            Array2D<int> dp(n, n);
            for(size_t len=1;len<=n-2;++len) {
                size_t rmargin=n-1-len;
                for(size_t i=1;i<=rmargin;++i) {
                    size_t left=i-1,right=i+len;  
                    int LxR=nums[left]*nums[right], val=0;
                    for(size_t j=i;j<right;++j)
                        val=max(val, LxR*nums[j]+dp.get(left,j)+dp.get(j,right));
                    dp.set(left,right,val);               
                }              
            }
            return dp.get(0,n-1);
        }
    }
};

int main()
{
    cout << Solution().maxCoins({3, 1, 5, 8}) << endl;
    cout << Solution2().maxCoins({3, 1, 5, 8}) << endl;
    cout << Solution3().maxCoins({3, 1, 5, 8}) << endl;
    return 0;
}