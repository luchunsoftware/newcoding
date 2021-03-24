#include<iostream>
#include<vector>

using namespace std;

/*
跳台阶【最简单的动归问题】 注意初始化的条件。斐波那契与本题几乎一直，只是初始化不同。

一只青蛙一次可以跳上1级台阶，也可以跳上2级。
求该青蛙跳上一个n级的台阶总共有多少种跳法。

dp[1] = 1, dp[2] = 2;
dp[n] = dp[n - 1] + dp[n - 2];
*/
int jumpFloor(int num) {
    if(num <= 2) return num;
    int a = 1, b = 2, c = 0;
    for(int i = 3; i <= num; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

/*
改进版 跳台阶 不能连着两次跳2阶
1、从 n-1 阶跳1阶跳上去
2、从 n-2 阶跳2阶跳上去（同时 n-2 阶必须是跳 1 阶跳上去的）
限制：从 n-2 阶跳 2 阶跳到 n 阶的 n-2 阶状态必须是从 n-3 阶跳1阶跳到 n-2 阶的
f(n) 表示跳到第 n 阶的总方法数，用 g(n)表示最后一步跳一阶跳到第 n 阶的方法数
f(n) = f(n - 1) + g(n - 2)
g(n) = f(n - 1)              得到：f(n) = f(n - 1) + f(n - 3)
*/
int jumpFloor1(int n){
    if (n <= 3) return n;
    int n_3 = 1;
    int n_2 = 2;
    int n_1 = 3;
    int res = 4;
    for (int i = 4; i <= n; i++) {
        res = n_1 + n_3;
        n_3 = n_2;
        n_2 = n_1;
        n_1 = res;
    }
    return res;
}

/*
53.最大子序和 

给定一个数组arr，返回子数组的最大累加和
例如，arr = [1, -2, 3, 5, -2, 6, -1]，所有子数组中，[3, 5, -2, 6]可以累加出最大的和12，所以返回12.
题目保证没有全为负数的数据
*/
class Solution {
public:
    int maxsumofSubarray(vector<int>& arr) {
        vector<int> dp(arr.size());
        dp[0] = arr[0];
        int res = dp[0];
        for(int i = 1; i < arr.size(); i++){
            dp[i] = max(dp[i - 1] + arr[i], arr[i]);
            res = max(dp[i], res);
        }
        return res;
    }
};

/*
最长公共子序列

给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。

一个字符串的 子序列 是指这样一个新的字符串：
它是由原字符串在不改变字符的相对顺序的情况下删除某些字符
（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。

输入：text1 = "abcde", text2 = "ace" 
输出：3  
解释：最长公共子序列是 "ace"，它的长度为 3。

若这两个字符串没有公共子序列，则返回 0。
*/

class Solution{
public:
    int LongestCommonSubsequence(string text1, string text2){
        int  m = text1.size(), n = text2.size();
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(text1[i - 1] == text2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }else{
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};

/*
300.最长递增子序列
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。

例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列
*/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> dp(n, 1);
        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

/*
198.打家劫舍
*/
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums[0];
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for(int i = 2; i < nums.size(); i++){
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[nums.size() - 1];
    }
    //优化空间复杂度为o(1)的做法
    int rob1(vector<int>& nums) {
        int size = nums.size();
        if(size == 0) return 0;
        if(size == 1) return nums[0];
        int first = nums[0], second = max(nums[0], nums[1]);
        for (int i = 2; i < size; i++) {
            int temp = second;
            second = max(first + nums[i], second);
            first = temp;
        }
        return second;
    }
};

/*
213.打家劫舍II  环形居住
*/
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        if(nums.size() == 1) return nums[0];
        int result1 = robhelp(nums, 0, nums.size() - 2);
        int result2 = robhelp(nums, 1, nums.size() - 1);
        return max(result1, result2);
    }

    int robhelp(vector<int>& nums, int start, int end){
        if(end - start == 0) return nums[start];
        vector<int> dp(nums.size());
        dp[start] = nums[start];
        dp[start + 1] = max(nums[start], nums[start + 1]);
        for(int i = start + 2; i <= end; i++){
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[end];
    }

};

/*
91、解码方法
一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：
'A' -> 1
'B' -> 2
...
'Z' -> 26
要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。
例如，"111" 可以将 "1" 中的每个 "1" 映射为 "A" ，从而得到 "AAA" ，
或者可以将 "11" 和 "1"（分别为 "K" 和 "A" ）映射为 "KA" 。
注意，"06" 不能映射为 "F" ，因为 "6" 和 "06" 不同。
给你一个只含数字的 非空 字符串 num ，请计算并返回 解码 方法的 总数 。
题目数据保证答案肯定是一个 32 位 的整数。
*/
int numDecodings(string s) {
    if(s[0] == '0') return 0;  
    vector<int> dp(s.size()+1, 1);
    for(int i = 1; i < s.size(); ++i){  
        //当当前数字为0前面不为1或2时直接return 0。
        //没有违规时前面肯定为1或者2，这个时候我们需要借用前面的数字来形成10和20，所以说前面那个数字所形成的
        //状态无效，所以我们得取1或2前面的那个数字的状态，所以为：dp[i+1] = dp[i-1];
        if(s[i] == '0'){
            if(s[i-1] != '1' && s[i-1] != '2') return 0;
            dp[i+1] = dp[i-1];
            continue;
        }
        //当前面数字为1时或者为2且当前数字小于7时，那么我们可以开始变换。
        //这里的动态方程为：dp[i+1] = dp[i] + dp[i-1];
        //当上述情况都不存在时证明此数字不会存在变换，所以直接取前面的状态。dp[i+1] = dp[i];
        if(s[i-1] == '1' || (s[i-1] == '2' && s[i] < '7'))
            dp[i+1] = dp[i] + dp[i-1];
        else
            dp[i+1] = dp[i];
    }
    return dp[s.size()];
}

