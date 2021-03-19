/*
牛客算法高频题不太熟练题集合
*/
#include<vector>
#include<string>
#include<stack>
#include<unordered_set>

using namespace std;
/*
tag: 哈希、双指针、字符串  滑动窗口
给定一个数组arr，返回arr的最长无重复子串的长度(无重复指的是所有数字都不相同)。
*/

int maxLength(vector<int>& arr) {
    if(arr.size() == 0) return 0;
    unordered_set<int> set;
    int res = 0, left = 0;
    for(int i = 0; i < arr.size(); i++){
        while(set.find(arr[i]) != set.end()){
            set.erase(arr[left]);
            left++;
        }
        res = max(res, i - left + 1);
        set.insert(arr[i]);
    }
    return res;
}

/*
补充：滑动窗口最大值
维护一个双端队列，用来存储滑动窗口中可能出现的最大值，
当新的元素比队尾元素大时，将队尾元素移除，直到队列为空，
或新元素不大于队尾元素，将新元素加入到队尾，
这样做的原因是当前的最大元素可能会由于滑动窗口的改变而失效，新的元素依旧有机会成为窗口内的最大元素。
*/
vector<int> maxInWindows(vector<int>& num, unsigned int size)
{
    vector<int> res;
    deque<int> dq;
    for(int i = 0; i < num.size(); ++i){
        while(!dq.empty() && num[dq.back()] < num[i])
            dq.pop_back();
        dq.push_back(i);
        if(dq.front() == i - size)
            dq.pop_front();
        if(i >=  size - 1)
            res.push_back(num[dq.front()]);
    }
    return res;
}

/*
数组中次数超过一半的数字
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。
由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。
*/
int moreThenHalfNum(vector<int>& nums){
    int res = 0, vote = 0;
    for(int i = 0; i < nums.size(); i++){
        if(vote == 0){
            res = nums[i];
        }
        if(res == nums[i]){
            vote++;
        }else{
            vote--;
        }
    }
    int count = 0;
    for(auto n : nums){
        if(n == res) ++count;
    }
    return count > nums.size() / 2 ? res : 0;
}

/*
k个一组翻转链表
将给出的链表中的节点每 k 个一组翻转，返回翻转后的链表
如果链表中的节点数不是 k 的倍数，将最后剩下的节点保持原样
你不能更改节点中的值，只能更改节点本身。
要求空间复杂度  O(1)
例如：
给定的链表是1→2→3→4→5
对于 k=2, 你应该返回 2→1→4→3→5
对于 k=3, 你应该返回 3→2→1→4→5
*/
struct  ListNode{
    int val;
    ListNode* next;
    ListNode(int x) : val(x),next(NULL){}
    ListNode(int x, ListNode*(node)): val(x) , next(node){}
};
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0);
        dummy -> next = head;
        ListNode* pre = dummy;      //pre记录翻转后的开始节点
        ListNode* cur = dummy;      //cur 记录第k个的节点
        while(cur -> next){
            for(int i = 0 ; i < k && cur != nullptr; i++){
                cur = cur -> next;
            }
            if(cur == nullptr) break;
            ListNode* start = pre -> next;
            ListNode* end = cur -> next;
            
            cur -> next = nullptr;  //先将第k个节点与后面的节点断开
            pre -> next = reverse(start);
            start -> next = end;     //将翻转后前k个节点与后面的连起来
            
            pre = start, cur = start;      //指向下一次的起始节点
            
        }
        return dummy -> next;
    }
    ListNode* reverse(ListNode* head){
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while(cur){
            ListNode* node = cur -> next;
            cur -> next = pre;
            pre = cur;
            cur = node;
        }
        return pre;
        
    }
};

/*

*/

/*
最近公共祖先

最近公共祖先和o1,o2有三种关系：

o1,o2 分别在 祖先左右两侧
祖先是o1，o2在祖先左/右侧
祖先是o2，o1在祖先左/右侧
使用 后序 遍历DFS ，如果节点为o1,o2中其中一个直接返回，如果节点超过叶子节点也返回
*/

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
};
class Solution {
public:
    
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        return common(root, o1, o2) -> val;
    }
    TreeNode* common(TreeNode* root, int o1, int o2){
        //root 为公共祖先，只有三种情况p 和 q 在 root的子树中，且分列 root 的 异侧（即分别在左、右子树中）；
        //p = root 且 q 在 root 的左或右子树中；
        //q = root 且 p 在 root 的左或右子树中；
        //通过递归对二叉树进行后序遍历，当遇到节点 p 或 q 时返回，从底至顶回溯，
        //当节点 p, q在节点 root 的异侧时，节点 root 即为最近公共祖先，则向上返回 root 。

        if(!root || root -> val == o1 || root -> val == o2) 
            return root;
        TreeNode* leftnode = common(root->left, o1, o2);  //返回的是左子树中是否包含o1或o2
        TreeNode* rightnode = common(root -> right, o1, o2);   // 返回的是右字树中是否包含o1或o2
        if(leftnode == nullptr) return rightnode;
        if(rightnode == nullptr) return leftnode;
        return root;
    }
};

/*
（补充）二叉搜索树的最近公共祖先
 对二叉搜索树来说
 满足根节点比左子树大比右子树小的性质 通过比较val值就能知道是不是在该节点
*/
class Solution{
public:
    TreeNode* binarySearchTree(TreeNode* root, TreeNode* p, TreeNode* q){
        if(p -> val > q -> val) swap(p, q);
        while(root){
            if(root -> val  < p -> val){
                root = root -> right;
            }else if(root -> val > q -> val){
                root = root -> left;
            }else break;
        }
        return root;
    }
};

/*
4.二叉树指定和路径  二叉树方案搜索问题，使用回溯法解决  先序遍历 + 路径记录
给定一个二叉树和一个值 sum，请找出所有的根节点到叶子节点的节点值之和等于 sum 的路径，
例如：
sum=22，
返回：
[
[5,4,11,2],
[5,8,9]
]
*/
vector<vector<int> > res;
vector<int> path;
void backtracking(TreeNode* root, int sum){
    if(root == nullptr) return;
    path.push_back(root -> val);
    sum -= root -> val;
    if(sum == 0 && root -> left == nullptr && root -> right == nullptr){
        res.push_back(path);
    }
    backtracking(root -> left, sum);
    backtracking(root -> right, sum);
    path.pop_back();
}

vector<vector<int> > pathSum(TreeNode* root, int sum){
    backtracking(root, sum);
    return res;
}

/*
5.二叉树根节点到所有子节点的和  
根节点为1 子节点为 2 和 3 
sum = 12 + 13 = 25
*/
int dfs(TreeNode* root, int sum){
    if(root == nullptr) return 0;
    sum = 10 * sum + root -> val;
    if(!root -> left && !root -> right){
        return sum;
    }
    return dfs(root -> left, sum) + dfs(root -> right, sum);
}

int sumNumbers(TreeNode* root){
    if(root == nullptr) return 0;
    return dfs(root, 0);
}

/*
6.二叉树的最大路径和

后序遍历，记录左右子树最大的路径节点和
因为需要分别记录左子树和右子树的最大路径和，用循环实现起来比较麻烦
*/
class Solution {
public:
    int maxSum = INT_MIN;
    int dfs(TreeNode* root){
        if(!root) return 0;
        int left = dfs(root -> left);
        int right = dfs(root -> right);
        int cur = root -> val;
        if(left > 0) cur += left;
        if(right > 0) cur += right;
        maxSum = max(maxSum, cur);
        //此处返回的是max(左+中，右+中, 中)，左+右+中不满足题意
        return max(root -> val, max(left, right) + root -> val);
    }
    int maxPathSum(TreeNode* root) {
        dfs(root);
        return maxSum;
    }
};

/*
7.括号序列  栈的操作
利用栈 一个个括号来匹配，只要匹配到了就弹出
*/
bool isValid(string s){
    stack<char> st;
    for(int i = 0; i < s.size(); i++){
        if(st.empty()){
            st.push(s[i]);
            continue;
        }
        if(st.top() == '(' && s[i] == ')') st.pop();
        else if(st.top() == '{' && s[i] == '}') st.pop();
        else if(st.top() == '[' && s[i] == ']') st.pop();
        else{
            st.push(s[i]);
        }
    }
    return st.empty();
}


/*
8、岛屿数量  DFS
深度遍历去感染，只要是1的，都赋给0，一个个遍历
*/

void dfs(vector<vector<char> >& grid, int i, int j) {
    int row = grid.size();
    int column = grid[0].size();
    grid[i][j] = '0';
    if (i - 1 >= 0 && grid[i-1][j] == '1') dfs(grid, i - 1, j);
    if (i + 1 < row && grid[i+1][j] == '1') dfs(grid, i + 1, j);
    if (j - 1 >= 0 && grid[i][j-1] == '1') dfs(grid, i, j - 1);
    if (j + 1 < column && grid[i][j+1] == '1') dfs(grid, i, j + 1);
}

int numIslands(vector<vector<char> >& grid) {
    int row = grid.size();
    if (row == 0) return 0;
    int column = grid[0].size();

    int res = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (grid[i][j] == '1') {
                ++res;
                dfs(grid, i, j);
            }
        }
    }
    return res;
}
/*
回溯+判断
数字字符串转ip地址  
现在有一个只包含数字的字符串，将该字符串转化成IP地址的形式，返回所有可能的情况。
例如：
给出的字符串为"25525522135",
返回["255.255.22.135", "255.255.221.35"]. (顺序没有关系)
*/
class solution{
    vector<string> res;
    vector<string> restore(string s){
        backtracking(s, 0, 0);
        return res;
    }
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
            }else break;
        }
    }
    bool isValid(string s, int start, int end){
        if(start > end) return false;
        if(s[start] == '0' && start != end){
            return false;
        }
        int num = 0;
        for(int i = start; i <= end; i++){
            num = num * 10 + s[i] - '0';
            if(s[i] > '9' || s[i] < '0' || num > 255){
                return false;
            }
        }
        return true;
    }

};


/*
双指针
接雨水问题    
认为如果一端有更高的条形块（例如右端），积水的高度依赖于当前方向的高度（从左到右）。
当我们发现另一侧（右侧）的条形块高度不是最高的，我们则开始从相反的方向遍历（从右到左）。
我们必须在遍历时维护 left_max 和 right_max ，
可以使用两个指针交替进行，实现 1 次遍历即可完成。

*/
int trap(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int leftmax = 0, rightmax = 0;
    int res;
    while(left < right){
        leftmax = max(leftmax, height[left]);
        rightmax = max(rightmax, height[right]);
        if(leftmax < rightmax ){
            res += leftmax - height[left];
            left++;
        }else{
            res += rightmax - height[right];
            right--;
        }
    }
    return res;
}

/*
动态规划
编辑距离 较难
dp[i][j] 表示的是 word1中前i个字符，变换到word2中前j个字符所需要操作的次数
考虑边界条件，word1为空或者word2为空的情况
转移条件：
增：dp[i][j] = dp[i - 1][j] + 1;
删：dp[i][j] = dp[i][j + 1] + 1;
改：dp[i][j] = dp[i - 1][j - 1] + 1;
如果word1[i - 1] == word2[j - 1] dp[i][j] =min(dp[i-1][j-1],dp[i][j]);

*/

int minDistance(string word1, string word2){
    int m = word1.size();
    int n = word2.size();
    vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
    for(int i = 0; i <= m; i++){
        dp[i][0] = i; 
    }
    for(int j = 0; j <= n; j++){
        dp[0][j] = j;
    }
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j],dp[i][j-1])) + 1;
            if(word1[i-1] == word2[j-1]){
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
            }
        }
    }
    return dp[m][n];
}

/*
动态规划  中等
目标和
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数 S。
现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 - 中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

转化为0-1背包问题
假设加法的总和为x，那么减法对应的总和就是sum - x。
所以我们要求的是 x - (sum - x) = S
x = (S + sum) / 2
数组为候选集，X为背包容量
*/

int findTargetSumWays(vector<int>& nums, int S) {
    int sum = 0;
    for (int i = 0; i < nums.size(); i++){
        sum += nums[i];
    }        
    if (S > sum || (S + sum) % 2 == 1) return 0;   // 此时没有方案
    int target = (S + sum) / 2;
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < nums.size(); i++) {
        for (int j = target; j >= nums[i]; j--){     //0-1背包倒序遍历
            dp[j] += dp[j - nums[i]];    
        }
    }
    return dp[target];
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

/*
股票  无限次交易
*/
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    if(n <= 1) return 0;
    int profit = 0;
    for(int i = 1; i < n; i++){
        profit += max(prices[i] - prices[i - 1], 0);
    }
    return profit;
}
/*
股票 一次交易
*/
int maxProfit(vector<int>& prices) {
    int left = INT_MAX;
    int res = 0;
    for(int i = 0; i < prices.size(); i++){
        left = min(left, prices[i]);
        res = max(res, prices[i] - left);
    }
    return res;
}




