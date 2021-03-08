#include<iostream>
#include<vector>

using namespace std;


/*
请实现有重复数字的升序数组的二分查找。
输出在数组中第一个大于等于查找值的位置，如果数组中不存在这样的数，则输出数组长度加一。
*/
class Solution {
public:
    int upper_bound_(int n, int v, vector<int>& arr) {
        int left = 0, right = n;
        while( left < right){
            int mid = left + (right - left) / 2;
            if(arr[mid] >= v) {
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        return left + 1;
    }
};



/*
leetcode 153 旋转数组的最小数字 无重复元素

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。
*/
class Solution{
public:
    int minArray(vector<int>& arr){
        int left = 0, right = arr.size() - 1;
        while(left < right){
            int mid = left + (right - left) / 2;
            if(arr[mid] > arr[right]) left = mid + 1;
            else{
                right = mid;
            }
        }
        return arr[left];
    }
};



/*
leetcode 154 旋转数组的最小数字 有重复元素

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。 
*/
class Solution{
public:
    int minArray(vector<int>& arr){
        int left = 0, right = arr.size() - 1;
        while(left < right){
            int mid = left + (right - left) / 2;
            if(arr[mid] > arr[right]) left = mid + 1;
            else if(arr[mid] < arr[right]) right = mid;
            else{
                right--;
            }
        }
        return arr[left];
    }
};



/*
转动过的有序数组求目标值

给出一个转动过的有序数组，你事先不知道该数组转动了多少
(例如,0 1 2 4 5 6 7可能变为4 5 6 7 0 1 2).
在数组中搜索给出的目标值，如果能在数组中找到，返回它的索引，否则返回-1。
假设数组中不存在重复项。

*/
class Solution {
public:
    // 不要被“旋转”而迷惑，“有序”并不是二分查找的核心
    // 二分查找的核心是"通过界桩快速决定查找方向，大幅缩短查找空间"
    // 只要能快速确定界桩，就能使用二分查找
    // 充分利用有序数组能够快速获取边界值的特性
    // 利用这一特性可以快速确定目标值应处的区间
    int search(vector<int>& nums, int target) {
        if (nums.empty())
            return -1;
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] == target)
                return mid;
            // 只要在普通的二分查找判断语句中加一层 && 来确定目标值所在的区间，即可以同样O(logn)的复杂度查找
            if (nums[left] <= nums[mid] && (nums[left] <= target && target < nums[mid]))
                right = mid - 1;
            else if (nums[mid] <= nums[right] && !(nums[mid] < target && target <= nums[right]))
                right = mid - 1;
            else
                left = mid + 1;
        }
        return -1;
    }
};

/*
NC32 求平方根，向下取整
实现函数 int sqrt(int x).
计算并返回x的平方根（向下取整）
*/
class Solution {
public:
    int sqrt(int x) {
        int left = 0, right = x, res = -1;
        while (left <= right) { 
            int mid = left + (right - left) / 2;
            if ((long long)mid * mid <= x) {
                res = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return res;
    }
};

/*
数值的整数次方  采用二分的思路，时间复杂度n(logn)
实现函数double Power(double base, int exponent)，求base的exponent次方。
不得使用库函数，同时不需要考虑大数问题。
*/
class Solution{
public:
    double power(double x, int n){
        if(x == 0) return 0;
        long m = n;
        double res = 1;
        if(m < 0){
            x = 1 / x;
            m = -m;
        }
        while(m > 0){
            if(m % 2 == 1) res *= x;
            m /= 2;
            x *= x;
        }
        return res;
    }
};

/*
0 ~ n-1 中 缺失的数字
一个长度为n-1的递增排序数组中的所有数字都是唯一的，
并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。

*/
int missingNumber(vector<int>& nums){
    int n = nums.size();
    int left = 0, right = n - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == mid){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    return left;
}



/*
二分法
寻找两个正序数组的中位数
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //如果两个数组的中位数mid1 < mid2, 则说明合并后的中位数位于nums1 right+ num2之间
        //否则合并后的中位数位于 nums2.right + nums1 之间 (right 是相对于 mid 而言的) 
        //findKth 函数负责找到两个数组合并(假设)后有序的数组中的第 k 个元素, k 从 1 开始计算
    
        if(nums1.size() == 0 && nums2.size() == 0) return 0.0;
        int m = nums1.size(), n = nums2.size();
        int l = (m + n + 1) / 2;
        int r = (m + n + 2) / 2;
        if(l == r) return findKth(nums1, 0, nums2, 0, l);
        else return (findKth(nums1, 0, nums2, 0, l) + findKth(nums1, 0, nums2, 0, r)) / 2.0;
    }
    int findKth(vector<int>& nums1, int i, vector<int>& nums2, int j, int k){
        //边界情况，如果nums1数组穷尽了，则只能返回nums2中的第k个元素
        if(i >= nums1.size()) return nums2[j + k - 1];
        if(j >= nums2.size()) return nums1[i + k - 1];
        //边界情况，如果k==1，则返回两个数组中最小的那个
        if(k == 1){
            return min(nums1[i], nums2[j]);
        }
        //在nums1和nums2的当前范围内找出mid1和mid2，判断舍弃哪半部分
        int mid1 = INT_MAX;
        int mid2 = INT_MAX;
        if(i + k/2 - 1 < nums1.size()) mid1 = nums1[i + k/2 - 1];
        if(j + k/2 - 1 < nums2.size()) mid2 = nums2[j + k/2 - 1];
        //mid1 < mid2 在num1.right和nums2之间搜索，丢掉k/2个数
        if(mid1 < mid2){
            return findKth(nums1, i + k/2, nums2, j, k - k/2);
        }else{
            return findKth(nums1, i, nums2, j + k/2, k - k/2);
        }
    }
};






