/*
剑指offer 
17.电话号码的字母组合
93. 数字字符串转IP地址
38. 字符串的全排列 有重复 中等 去重
46. 全排列 无重复数字 中等
47. 全排列 有重复数字 中等 去重
39、组合总和   无重复数字，可重复选取
40.加起来和为目标值的组合 中等 去重
*/


#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>

using namespace std;

/*
17.电话号码的字母组合
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
*/
vector<string> board = { "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
vector<string> res;
string path;
void backtracking(string digits, int startIndex){
    if(path.size() == digits.size()){
        res.push_back(path);
        return;
    }
    int num = digits[startIndex] - '0';
    for(int i = 0; i < board[num].size();i++){
        path.push_back(board[num][i]);
        backtracking(digits, startIndex + 1);
        path.pop_back();
    }            
}
vector<string> letterCombinations(string digits) {
    if(digits.size() == 0) return res;
    backtracking(digits, 0);
    return res;
}


/*
93.数字字符串转ip地址

现在有一个只包含数字的字符串，将该字符串转化成IP地址的形式，返回所有可能的情况。
例如：
给出的字符串为"25525522135",
返回["255.255.22.135", "255.255.221.35"]. (顺序没有关系)
*/
vector<string> res;
void backtracking(string s, int startindex, int point){
    if(point == 3){
        if(isValid(s, startindex, s.size() - 1)){
            res.push_back(s);
        }
        return;
    }
    for(int i = startindex; i < s.size(); i++){
        if(isValid(s, startindex, i)){
            s.insert(s.begin() + i + 1, '.');
            point++;
            backtracking(s, i + 2, point);
            point--;
            s.erase(s.begin() + i + 1);
        }else{
            break;
        }
    }
}
bool isValid(string s, int start, int end){
    if(start > end) return false;
    if(s[start] == '0' && start != end) return false;
    int num = 0;
    for(int i = start; i <= end; i++){
        num = num * 10 + s[i] - '0';
        if(s[i] > '9' || s[i] < '0' || num > 255){
            return false;
        }
    }
    return true;
}
vector<string> restoreIpAddresses(string s) {
    backtracking(s, 0, 0);
    return res;
}


/*
剑指offer 38.字符串的全排列 有重复 中等
*/
class Solution{
public:
    void backtracking(string s, int startIndex, vector<string>& res){
        if(startIndex == s.size() - 1){
            res.push_back(s);
            return;
        }
        unordered_set<char> used;
        for(int i = startIndex; i < s.size(); i++){
            if(used.find(s[i]) != used.end()){
                continue;
            }else{
                used.insert(s[i]);
            }
            swap(s[i], s[startIndex]);
            backtracking(s, startIndex + 1, res);
            swap(s[i], s[startIndex]);
        }
    }

    vector<string> permutation(string s){
        vector<string> res;
        backtracking(s, 0, res);
        return res;
    }
};

/*
46.全排列 无重复数字 中等
输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/
class Solution{
public:
    vector<vector<int> > res;
    vector<int> path;
    void backtracking(vector<int>& arr, vector<bool>& used){
        if(path.size() == arr.size()){
            res.push_back(path);
            return;
        }
        for(int i = 0; i < arr.size(); i++){
            if(used[i] == false){
                path.push_back(arr[i]);
                used[i] = true;
                backtracking(arr,used);
                used[i] = false;
                path.pop_back();
            }
        }
    }

    vector<vector<int> > permute(vector<int>& arr){
        vector<bool> used(arr.size(), false);
        backtracking(arr,used);
        return res;
    }
};

/*
47. 全排列 有重复数字 中等 去重
*/

class Solution{
public:
    vector<vector<int> > res;
    vector<int> path;
    void backtracking(vector<int>& arr, vector<bool>& used){
        if(path.size() == arr.size()){
            res.push_back(path);
            return;
        }
        for(int i = 0; i < arr.size(); i++){
            if(i > 0 && arr[i] == arr[i - 1] && used[i - 1] == false) continue;
            if(used[i] == false){
                path.push_back(arr[i]);
                used[i] = true;
                backtracking(arr, used);
                used[i] = false;
                path.pop_back();
            }
        }
    }

    vector<vector<int> > permute(vector<int>& arr){
        vector<bool> used(arr.size(), false);
        sort(arr.begin(), arr.end());
        backtracking(arr,used);
        return res;
    }
};

/*
39、组合总和   无重复数字，可重复选取
给定一个无重复元素的数组 candidates 和一个目标数 target ，
找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。

输入：candidates = [2,3,6,7], target = 7,
所求解集为：
[[7],
[2,2,3]]
*/
vector<vector<int> > res;
vector<int> path;
void backtracking(vector<int>& candidates, int startindex, int sum, int target){
    if(sum > target) return;
    if(sum == target){
        res.push_back(path);
        return;
    }
    for(int i = startindex; i < candidates.size(); i++){
        sum += candidates[i];
        path.push_back(candidates[i]);
        backtracking(candidates, i, sum, target);
        sum -= candidates[i];
        path.pop_back();
    }
}
vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
    backtracking(candidates, 0, 0, target);
    return res;
}


/*
40.加起来和为目标值的组合 中等 去重操作
*/
class Solution {
public:
    vector<vector<int> > res;
    vector<int> path;
    void backtracking(vector<int>& nums, int target, int startIndex, int sum, vector<bool>& used){
        if(sum > target) return;
        if(sum == target){
            res.push_back(path);
            return;
        }
        for(int i = startIndex; i < nums.size(); i++){
            if(i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) continue;
            path.push_back(nums[i]);
            used[i] = true;
            sum += nums[i];
            backtracking(nums, target, i + 1, sum, used);
            path.pop_back();
            sum -= nums[i];
            used[i] = false;
        }
    }
    vector<vector<int> > combinationSum2(vector<int> &num, int target) {
        sort(num.begin(), num.end());
        vector<bool> used(num.size(), false);
        backtracking(num, target, 0, 0, used);
        return res;
    }
};