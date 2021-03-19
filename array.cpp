#include<vector>
#include<unordered_set>

using namespace std;
/*
数组中从未出现的正整数

给定一个无序数组arr，找到数组中未出现的最小正整数
例如arr = [-1, 2, 3, 4]。返回1
arr = [1, 2, 3, 4]。返回5
[要求]
时间复杂度为O(n)，空间复杂度为O(1)
*/
int minNumberdisappered(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n; i++){
        while(arr[i] > 0 && arr[i] < n && arr[i] != arr[arr[i] - 1]){
            swap(arr[i], arr[arr[i] - 1]);
        }
    }
    for(int i = 0; i < n; i++){
        if(arr[i] != i + 1) return i + 1; 
    }
    return n + 1;
}

/*
缺失数字   二分的思路
从0,1,2,...,n这n+1个数中选择n个数，组成有序数组，请找出缺失的那个数，要求O(n)尽可能小
*/
int solve(int* a, int aLen) {
    int  i = 0, j = aLen - 1;
    while(i <= j){
        int mid = i + (j - i) / 2;
        if(a[mid] == mid){
            i = mid + 1;
        }else{
            j = mid - 1;
        }
    }
    return i;
}

/*
三数之和
*/
vector<vector<int> > threeSum(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int> > res;
    if(n < 3) return res;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < n; i++){
        if(i > 0 && nums[i] == nums[i -1]) continue;
        int k = n - 1;
        int target = 0 - nums[i];
        for(int j = i + 1; j < n; j++){
            if(j > i + 1 && nums[j] == nums[j - 1])continue;
            while(j < k && nums[j] + nums[k] > target) k--;
            if(j == k) break;
            if(nums[j] + nums[k] == target){
                res.push_back({nums[i], nums[j], nums[k]});
            }
        }
    }
    return res;
}

/*
16.最接近的三数之和
给定一个包括 n 个整数的数组 nums 和 一个目标值 target。
找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。
假定每组输入只存在唯一答案。
*/
int threeSumClosest(vector<int>& nums, int target){
    sort(nums.begin(), nums.end());
    int res = nums[0] + nums[1] + nums[2];
    int value = abs(res - target);
    int sum;
    for(int i = 0; i < nums.size(); ++i){
        int l = i + 1;
        int r = nums.size() - 1; 
        while(l < r) {
            sum = nums[i] + nums[l] + nums[r];
            if(sum > target) --r;
            else if(sum < target) ++l;
            else return sum;
            if(abs(sum - target) < value){
                res = sum;
                value = abs(sum - target);
            }
        }
    }
    return res;
}

/*
128.最长连续序列
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
*/
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> set;
    for (int i = 0; i < nums.size(); i++){
        set.insert(nums[i]); 
    }
    int res = 0;
    for (int x : nums) {            // 遍历每一个数 
        if (!set.count(x - 1)){     // 当前数之前不连续，即当前数为连续序列的第一个数时
            int curNum = x;
            int curLen = 1;
            while (set.count(curNum + 1)){  //判断当前数之后是否连续
                curNum ++ ;
                curLen ++ ;
            }
            res = max(res, curLen);   //每次遍历更新最大长度
        }
    }
    return res;
}