#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>

using namespace std;

struct TreeNode {
 	int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*
二叉树的前序、中序和后序遍历（递归和迭代）
*/

class Solution {
public:
    vector<int> pre, mid, post;
    vector<vector<int> > threeOrders(TreeNode* root) {
        vector<vector<int> > res;
        preorder(root,pre);
        midorder(root,mid);
        postorder(root,post);
        res = {pre, mid, post};
        return res;
    }
    void preorder(TreeNode* root,vector<int>& pre){
        if(root == nullptr) return;
        pre.push_back(root -> val);
        preorder(root -> left, pre);
        preorder(root -> right, pre);
    }
    void midorder(TreeNode* root, vector<int>& mid){
        if(root == nullptr) return;
        preorder(root -> left, pre);
        pre.push_back(root -> val);
        preorder(root -> right, pre);
    }
    void postorder(TreeNode* root, vector<int>& post){
        if(root == nullptr) return;
        preorder(root -> left, pre);
        preorder(root -> right, pre);
        pre.push_back(root -> val);
    }


    void preorder(TreeNode* root,vector<int>& pre){
        stack<TreeNode*> st;
        while(!st.empty() || root){
            while(root){
                st.push(root);
                pre.push_back(root -> val);
                root = root -> left;
            }
            root = st.top();
            st.pop();
            root = root -> right;
        }
    }

    void midorder(TreeNode* root, vector<int>& mid){
        stack<TreeNode*> st;
        while(!st.empty() || root){
            while(root){
                st.push(root);
                root = root -> left;
            }
            root = st.top();
            st.pop();
            mid.push_back(root -> val);
            root = root -> right;
        }
    }
    
    void postorder(TreeNode* root, vector<int>& post){
        stack<TreeNode*> st;
        while(!st.empty() || root){
            while(root){
                st.push(root);
                post.push_back(root -> val);
                root = root -> right;
            }
            root = st.top();
            st.pop();
            root = root -> left;
        }
        reverse(post.begin(),post.end());
    }
};

/*
二叉树的层次遍历
*/
class Solution{
public:
    vector<vector<int> > levelorder(TreeNode* root){
        vector<vector<int> > res;
        if(root == nullptr) return res;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int cursize = q.size();
            vector<int> vec;
            for(int i = 0; i < cursize; i++){
                TreeNode* node = q.front();
                q.pop();
                vec.push_back(node -> val);
                if(node -> left) q.push(node -> left);
                if(node -> right) q.push(node -> right);
            }
            res.push_back(vec);
        }
        return res;
    }
};

/*
对称二叉树   从顶至底递归，判断每对节点是否对称，从而判断树是否为对称二叉树
判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。
*/

bool isSymmetric(TreeNode* root){
    if(root == nullptr) return true;
    return compare(root -> left, root -> right);
}
bool compare(TreeNode* p, TreeNode* q){
    if(p == nullptr && q == nullptr) return true;
    if(p == nullptr || q == nullptr || p -> val != q -> val) return false;
    return compare(p -> left, q -> right) && compare(p -> right, q -> left);
}
/*
给定一棵二叉树，已经其中没有重复值的节点，请判断该二叉树是否为搜索二叉树和完全二叉树。
*/
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
public:
    vector<bool> judgeIt(TreeNode* root) {
         return {isSearchTree(root,INT_MIN,INT_MAX),isCompletedTree(root)};
    }
    bool isSearchTree(TreeNode *root, int left, int right)
    {
        if(root == nullptr) 
            return true;
        if(root->val < left || root->val > right)
            return false;
        return isSearchTree(root->left,left,root->val) && isSearchTree(root->right, root->val,right);
    }
    bool isCompletedTree(TreeNode* root)
    {
        if(root == nullptr) 
            return true;
        if(root->left && root->right == nullptr)
            return isCompletedTree(root->left);
        if(root->left == nullptr && root->right)
            return false;
        return isCompletedTree(root->left) && isCompletedTree(root->right);
    }
};

/*
二叉树的镜像
*/
class Solution{
public:
    TreeNode* mirror(TreeNode* root){
        if(root == nullptr) return root;
        swap(root -> left, root -> right);
        mirror(root -> left);
        mirror(root -> right);
        return root;
    }
    TreeNode* mirrorTree(TreeNode* root) {
        stack<TreeNode*> st;
        if(root==NULL) return root;
        st.push(root);
        while(!st.empty()){
            TreeNode* node = st.top();
            st.pop();
            if(node -> left) st.push(node -> left);
            if(node -> right) st.push(node -> right);
            swap(node -> left, node -> right);
        }
        return root;
    }
};

/*
二叉树的最大深度
*/
class Solution{
public:
    int getDepth(TreeNode* root){
        if(root == nullptr) return 0;
        return 1 + max(getDepth(root -> left), getDepth(root -> right));
    }
};

/*
判断是否是平衡二叉树
*/
class Solution{
public:
    bool isBalance(TreeNode* root){
        if(root == nullptr) return true;
        return abs(getDepth(root -> left) - getDepth(root -> right)) <= 1 && isBalance(root -> left) && isBalance(root -> right);
    }

    int getDepth(TreeNode* root){
        if(root == nullptr) return 0;
        return 1 + max(getDepth(root -> left), getDepth(root -> right));
    }
};

/*
对称二叉树
*/
bool isSymmetric(TreeNode* root) {
    if(root == NULL) return true;
    return compare(root -> left, root -> right);
}
bool compare(TreeNode* p, TreeNode* q){
    if(p == NULL && q == NULL) return true;
    if(p == NULL || q == NULL || q -> val != p -> val) return false;
    return compare(p -> left, q -> right) && compare(p ->right, q -> left);
}

/*
二叉树的最近公共祖先
*/
class Solution{
public:
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        return common(root, o1, o2) -> val;
    }
    TreeNode* common(TreeNode* root, int o1, int o2){
        if(!root || root -> val == o1 || root -> val == o2) return root;
        TreeNode* leftnode = common(root->left, o1, o2);
        TreeNode* rightnode = common(root -> right, o1, o2);
        if(leftnode == nullptr) return rightnode;
        if(rightnode == nullptr) return leftnode;
        return root;
    }
};

/*
108、将有序数组转换为二叉搜索树
给你一个整数数组 nums ，其中元素已经按 升序 排列，
请你将其转换为一棵 高度平衡 二叉搜索树。
高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。
*/
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return helper(nums, 0, nums.size() - 1);
}
TreeNode* helper(vector<int>& nums, int left, int right) {
    if (left > right) {
        return nullptr;
    }
    // 总是选择中间位置左边的数字作为根节点
    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = helper(nums, left, mid - 1);
    root->right = helper(nums, mid + 1, right);
    return root;
}



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
二叉树根节点到叶子节点的所有路径之和

给定一个仅包含数字 0−9 的二叉树，每一条从根节点到叶子节点的路径都可以用一个数字表示。
例如根节点到叶子节点的一条路径是1→2→3,那么这条路径就用 123 来代替。
找出根节点到叶子节点的所有路径表示的数字之和
例如：
这颗二叉树一共有两条路径
根节点到叶子节点的路径 1→2 用数字 12 代替
根节点到叶子节点的路径 1→3 用数字 13 代替
所以答案为\ 12+13=25
*/

int dfs(TreeNode* root, int sum){
    if(root == nullptr) return 0;
    sum = 10 * sum + root -> val;
    if(root -> left == nullptr && root -> right == nullptr){
        return sum;
    }
    return dfs(root ->left, sum) + dfs(root -> right, sum);
}

int sumPath(TreeNode* root){
    if(root == nullptr) return 0;
    return dfs(root, 0);
}

/*
二叉树指定和路径  二叉树方案搜索问题，使用回溯法解决  先序遍历 + 路径记录
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
二叉树的最大路径和
路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。
同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root ，返回其最大路径和 。
*/
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

/*
重建二叉树
已知前序遍历结果和中序遍历结果，还原这棵二叉树
 */
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> in) {
        return help(pre, 0, pre.size(), in, 0, in.size());
    }
    TreeNode* help(vector<int>& pre, int prestart, int preend, vector<int>& in, int instart, int inend){
        if(preend - prestart == 0) return nullptr;
        int rootvalue = pre[prestart];
        TreeNode* root = new TreeNode(rootvalue);
        if(preend - prestart == 1) return root;
        int index;
        for(index = instart; index < inend; index++){
            if(in[index] == rootvalue) break;
        }
        //切分中序
        int leftinstart = instart, leftinend = index;
        int rightinstart = index + 1, rightinend = inend;
        //切分前序
        int leftprestart = prestart + 1, leftpreend = prestart + 1 + index - instart;
        int rightprestart = leftpreend, rightpreend = preend;
        
        root -> left = help(pre, leftprestart, leftpreend, in, leftinstart, leftinend);
        root -> right = help(pre, rightprestart, rightpreend, in, rightinstart, rightinend);
        return root;
    }
};

