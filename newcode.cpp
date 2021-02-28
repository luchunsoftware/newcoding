/*
牛客算法高频题不太熟练题集合
*/
#include<vector>
#include<string>
#include<unordered_set>

using namespace std;
/*
tag: 哈希、双指针、字符串  滑动窗口
1.给定一个数组arr，返回arr的最长无重复子串的长度(无重复指的是所有数字都不相同)。
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
2.k个一组翻转链表
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
            auto node = cur -> next;
            cur -> next = pre;
            pre = cur;
            cur = node;
        }
        return pre;
        
    }
};

/*
3.最近公共祖先

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
        TreeNode* rightnode = common(root -> right, o1, o2);   // 返回的是左字树中是否包含o1或o2
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
vector<vector<int>> res;
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

vector<vector<int>> pathSum(TreeNode* root, int sum){
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
7.括号序列
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





