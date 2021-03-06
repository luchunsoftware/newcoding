#include<string>
#include<vector>

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
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段，可能的最大乘积是多少？
例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
*/
int cut(int n){
    if(n <= 3) return n - 1;
    long res = 1;
    while(n > 4){
        res *= 3;
        res %= 1000000007;
        n -= 3; 
    }
    return res * n % 1000000007;
}

/*
异或操作
任何数和 0做异或运算，结果仍然是原来的数，即 a⊕0=a。
任何数和其自身做异或运算，结果是 0，即 a⊕a=0。
异或运算满足交换律和结合律,

lc136.只出现一次的数字
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。
找出那个只出现了一次的元素。
*/
int findSingleNumber(vector<int>& nums){
    int res = 0;
    for(int i = 0; i < nums.size(); i++){
        res ^= nums[i];
    }
    return res;
}
