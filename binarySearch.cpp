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
    /**
     * 
     * @param x int整型 
     * @return int整型
     */
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






