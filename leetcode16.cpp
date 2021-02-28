#include <iostream>
#include <vector>
using namespace std;

class Solution{
public:
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
};

int main(){
    vector<int> arr = {-1, 2, 1, -4};
    int s = 1;
    Solution solution;
    int res = solution.threeSumClosest(arr, s);
    cout << res << endl;
}