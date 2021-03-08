#include<vector>

using namespace std;
/*
数组中从未出现的正整数

给定一个无序数组arr，找到数组中未出现的最小正整数
例如arr = [-1, 2, 3, 4]。返回1
arr = [1, 2, 3, 4]。返回5
[要求]
时间复杂度为O(n)，空间复杂度为O(1)
*/
class Solution {
public:
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
};