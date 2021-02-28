#include<string>

using namespace std;
/*
进制转换 

给定一个十进制数M，以及需要转换的进制数N。将十进制数M转化为N进制数
*/
class Solution {
public:
    string solve(int M, int N) {
        string t = "0123456789ABCDEF";
        string ans = "";
        if(M==0) return "0";
        bool flag = false;
        if(M < 0){
            flag = true;
            M = -M;
        }
        while(M){
            ans += t[M%N];
            M /= N;
        }
        if(flag){
            ans += "-";
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

/*
二进制数中的位数 简单
*/
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int sum = 0;
        while(n){
            sum++;
            n &= (n - 1);
        }
        return sum;
    }
};

/*
剪绳子问题
*/