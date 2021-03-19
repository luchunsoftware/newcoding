
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
最小的k个数
*/
vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
    vector<int> res;
    if(input.size() == 0 || k <= 0 || k > input.size()) return res;
    int start = 0, end = input.size() - 1;
    while(start < end){
        int mid = partition(input, start, end);
        if(mid == k) break;
        else if(mid < k) start = mid + 1;
        else{
            end = mid - 1;
        }
    }
    for(int i = 0; i < k; i++){
        res.push_back(input[i]);
    }
    return res;
}
int partition(vector<int>& arr,int low, int high){
    int pivot = arr[low];
    while(low < high){
        while(low < high && arr[high] >= pivot) high--;
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot) low++;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

/*
寻找第K大的数
*/
class Solution {
public:
    int findKth(vector<int>& arr, int n, int K) {
        int low = 0, high = n - 1;
        K = n - K;
        while(true){
            int m = partition(arr, low, high);
            if(m == K) return arr[K];
            else if(m > K){
                high = m - 1;
            }else{
                low = m + 1;
            }
        }
        return -1;
    }
    int partition(vector<int>& arr, int low, int high){
        int pivot = arr[low];
        while(low < high){
            while(low < high && arr[high] >= pivot) high--;
            arr[low] = arr[high];
            while(low < high && arr[low] <= pivot) low++;
            arr[high] = arr[low];
        }
        arr[low] = pivot;
        return low;
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

