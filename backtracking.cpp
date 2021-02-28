/*
剑指offer 38.字符串的全排列 有重复 中等 去重
46.全排列 无重复数字 中等
47. 全排列 又重复数字 中等 去重
40.加起来和为目标值的组合 中等 去重操作
*/


#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;
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
    vector<vector<int>> res;
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

    vector<vector<int>> permute(vector<int>& arr){
        vector<bool> used(arr.size(), false);
        backtracking(arr,used);
        return res;
    }
};

/*
47. 全排列 又重复数字 中等 去重
*/

class Solution{
public:
    vector<vector<int>> res;
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
                backtracking(arr,used);
                used[i] = false;
                path.pop_back();
            }
        }
    }

    vector<vector<int>> permute(vector<int>& arr){
        vector<bool> used(arr.size(), false);
        sort(arr.begin(), arr.end());
        backtracking(arr,used);
        return res;
    }
};

/*
40.加起来和为目标值的组合 中等 去重操作
*/
class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& nums, int target, int startIndex, int sum, vector<bool>& used){
        if(sum > target) return;
        if(sum == target){
            result.push_back(path);
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
        return result;
    }
};