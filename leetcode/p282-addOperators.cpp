#include "utils.hpp"

class Solution
{
public:
    struct Context
    {
        int64_t nums[3];
        char ops[2];
        short opi, numi;

        inline void push_num(int num)
        {
            nums[numi++]=num;
        }

        void push_op(char op)
        {
            if (op=='*') {
                if (opi>0 && ops[opi-1]=='*') {
                    nums[numi-2]*=nums[numi-1];
                    --numi; ops[opi-1]='*';
                }
                else
                {
                    ops[opi++]='*';
                }
                
            }
            else {
                finish();
                ops[opi++]=op;
            }
        }

        void finish()
        {
            while(opi>0) {
                switch(ops[opi-1]) {
                    case '+': nums[numi-2]+=nums[numi-1]; break;
                    case '-': nums[numi-2]-=nums[numi-1]; break;
                    case '*': nums[numi-2]*=nums[numi-1]; break;
                }
                --numi,--opi;
            }
        }
    };

    void try3ops(size_t offset, const Context &ctx)
    {
        size_t bookmark = path.size();

        Context ctx2 = ctx;
        ctx2.push_op('+');
        path.push_back('+');
        dfs(offset, ctx2);

        ctx2 = ctx;
        ctx2.push_op('-');
        path.resize(bookmark);
        path.push_back('-');
        dfs(offset, ctx2);

        ctx2 = ctx;
        ctx2.push_op('*');
        path.resize(bookmark);
        path.push_back('*');
        dfs(offset, ctx2);
        path.resize(bookmark);
    }

    void dfs(size_t offset, Context ctx)
    {
        int64_t num = (*s)[offset] - '0';
        path.push_back((*s)[offset]);
        ctx.push_num(num);
        if (offset + 1 == s->size())
        {      
            ctx.finish();    
            if (ctx.nums[0] == target)
                ans.push_back(path);
            return;
        }

        try3ops(offset + 1, ctx);
        if (num==0) return;

        for (size_t i = offset + 1; i + 1 < s->size(); ++i)
        {
            num=num*10+((*s)[i]-'0');
            if (num>INT_MAX) return;
            path.push_back((*s)[i]);
            ctx.nums[ctx.numi-1]=num;
            try3ops(i + 1, ctx);            
        }
        
        num=num*10+(s->back()-'0');
        path.push_back(s->back());
        if (num<=INT_MAX) {
            ctx.nums[ctx.numi-1]=num;
            ctx.finish();
            if (ctx.nums[0] == target)
                ans.push_back(path);           
        }
    }

    vector<string> addOperators(string num, int _target)
    {
        size_t n = num.size();
        target = _target;
        s = &num;
        if (n == 0)
            return {};
        if (n == 1)
        {
            if (num[0] - '0' == _target)
                return {num};
            else
                return {};
        }
        path.reserve(n + n - 1);
        Context ctx{0};
        dfs(0, ctx);
        return ans;
    }

private:
    string path;
    int target;
    string *s;
    vector<string> ans;
};

class Solution2 {
public:
    static inline int64_t calc(char op, int64_t x1, int64_t x2) {
        switch(op) {
            case '+': return x1+x2;
            case '-': return x1-x2;
            case '*': return x1*x2;
            default: return 0;
        }
    }

    static inline int64_t calc(char op1, char op2, int64_t x1, int64_t x2, int64_t x3) {
        if (op2!='*' || op1=='*') return calc(op2, calc(op1, x1, x2), x3);  
        return calc(op1, x1, calc(op2, x2, x3));   
    }

    void try3ops(size_t offset, char op1, char op2, int64_t x1, int64_t x2, int64_t x3) {
        size_t bookmark=path.size();

        if (op2!='*' || op1=='*') { x1 = calc(op1, x1, x2); x2 = x3; op1=op2; }
        else { x2 *= x3; }

        path.push_back('+');
        dfs(offset, op1, x1, x2, '+');
        path.resize(bookmark); 
        
        path.push_back('-');
        dfs(offset, op1, x1, x2, '-');
        path.resize(bookmark); 

        path.push_back('*');
        dfs(offset, op1, x1, x2, '*');
        path.resize(bookmark);               
    }

    void dfs(size_t offset, char op1, int64_t x1, int64_t x2, char op2) {
        int64_t x3=(*s)[offset] - '0';
        path.push_back((*s)[offset]);
        if (offset+1==n) {
            if (calc(op1, op2, x1, x2, x3)==target) ans.push_back(path);
            return;  
        }
        
        try3ops(offset + 1, op1, op2, x1, x2, x3);
        if (x3==0) return;   
        
        for (size_t i = offset + 1; i + 1 < n; ++i)
        {
            x3=x3*10+((*s)[i]-'0');
            if (x3>INT_MAX) return;
            path.push_back((*s)[i]);
            try3ops(i + 1, op1, op2, x1, x2, x3);           
        }
        
        x3=x3*10+(s->back()-'0');
        path.push_back(s->back());
        if (x3<=INT_MAX) {
            if (calc(op1, op2, x1, x2, x3)==target) ans.push_back(path);        
        }    
    }

    vector<string> addOperators(string num, int _target)
    {
        n = num.size();
        if (n == 0) return {};
        target = _target;
        s = &num;
        path.reserve(n + n - 1);
        dfs(0, '+', 0, 0, '+');
        return ans;
    }

private:
    string path;
    int target;
    string *s;
    size_t n;
    vector<string> ans;
}; 

int main(int argc, char **argv)
{
    cout << Solution().addOperators("105", 5) << endl;
    cout << Solution2().addOperators("123", 6) << endl;
}
