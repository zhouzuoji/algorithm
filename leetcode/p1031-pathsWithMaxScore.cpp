#include "../common/utils.hpp"

/*
You are given a square board of characters. 
You can move on the board starting at the bottom right square marked with the character 'S'.
You need to reach the top left square marked with the character 'E'. 
The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. 
In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, 
and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

In case there is no path, return [0, 0].
*/

class Solution
{
public:
    vector<int> pathsWithMaxScore(const vector<string> &board)
    {
        static const int MODULO = 1000000007;
        vector<int> ans(2);
        int n = board.size();
        Array2D<int> dp(n + 1, n + 1);
        Array2D<int> pc(n + 1, n + 1);
        for (int i = 0; i <= n; ++i)
        {
            dp.set(i, 0, -1);
            dp.set(0, i, -1);
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                char c = board[i-1][j-1];
                if (c=='E') { dp.set(i, j, 0); pc.set(i,j,1); continue; }
                if (c == 'X')
                {
                    dp.set(i, j, -1);
                    continue;
                }
                int cur=c=='S'?0:c-'0';
                int val = max(-1, dp.get(i-1, j));
                val = max(val, dp.get(i, j - 1));
                val = max(val, dp.get(i-1, j - 1));
                if (val==-1) { dp.set(i, j, -1); continue; }
                dp.set(i,j,(val+cur)%MODULO);
                int path_cnt=0;
                if (dp.get(i, j - 1)==val) path_cnt+=pc.get(i,j-1);
                if (dp.get(i - 1, j - 1)==val) path_cnt=(path_cnt+pc.get(i-1,j-1))%MODULO;
                if (dp.get(i-1, j)==val) path_cnt=(path_cnt+pc.get(i-1,j))%MODULO;
                pc.set(i,j,path_cnt);
            }
        }
        ans[0] = max(0, dp.get(n, n));
        ans[1] = pc.get(n, n);
        return ans;
    }
};

int main()
{
    cout << Solution().pathsWithMaxScore({"E11","XXX","11S"}) << endl;
    return 0;
}