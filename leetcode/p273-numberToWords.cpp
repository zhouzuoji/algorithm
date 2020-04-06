#include "utils.hpp"

class Solution
{ 
public:
    void belowThousand(ostringstream& ans, int num) {
        static const string ONES[] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
        static const string TEENS[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        static const string TIES[] = {"One", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        int tmp;
        if (num>=100) {
            tmp = num/100;
            num -= tmp*100;
            ans << " " << ONES[tmp-1] << " Hundred";
        }

        if (num>=20) {
            tmp = num/10;
            num -= tmp*10;
            ans << " " << TIES[tmp - 1]; 
            if (num > 0)
                ans << " " << ONES[num-1];
        }
        else if (num>=10)           
            ans << " " << TEENS[num-10];
        else if (num > 0)
            ans << " " << ONES[num-1];
    }

    string numberToWords(int num) {
        if (num == 0) return "0";
        ostringstream ans;
        int tmp;
        if (num>=1000000000) {
            tmp = num/1000000000;
            num -= tmp*1000000000;
            belowThousand(ans, tmp);
            ans << " Billion";
        }

        if (num>=1000000) {
            tmp = num/1000000;
            num -= tmp*1000000;
            belowThousand(ans, tmp);
            ans << " Million";
        }

         if (num>=1000) {
            tmp = num/1000;
            num -= tmp*1000;
            belowThousand(ans, tmp);
            ans << " Thousand";
        }   

        if (num > 0) 
            belowThousand(ans, num);  

        return ans.str().substr(1); 
    }
};

int main() {
    cout << Solution().numberToWords(12345);
    return 0;
}