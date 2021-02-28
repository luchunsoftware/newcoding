
//用优先队列来做，默认大顶堆
#include<vector>
#include<queue>

using namespace std;

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> res;
        if(k == 0 || input.size() < k) return res;
        priority_queue<int, vector<int> > pq;
        for(int i = 0; i < input.size(); ++i){
            if(pq.size() < k) pq.push(input[i]);
            else{
                if(pq.top() > input[i]){
                    pq.pop();
                    pq.push(input[i]);
                }
            }
        }
        while(!pq.empty()){
            res.push_back(pq.top());
            pq.pop();
        }
        return res;
    }
};

/*
快排
*/
class Solution{
    vector<int> my_sort(vector<int>& input){
        quickSort(input, 0, input.size() - 1);
        return input;
    }

    void quickSort(vector<int>& arr, int low, int high){
        int mid = partition(arr, low, high);
        if(low < mid - 1) quickSort(arr, low, mid - 1);
        if(mid + 1 < high) quickSort(arr, mid + 1, high);
    }

    int partition(vector<int> arr, int low, int high){
        int pivot = arr[low];
        while(low < high){
            while(low < high && arr[high] > pivot) high --;
            arr[low] = arr[high];
            while(low < high && arr[low] < pivot) low ++;
            arr[high] = arr[low];
        }
        arr[low] = pivot;
        return low;
    }
};