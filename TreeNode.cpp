#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>

using namespace std;

struct TreeNode {
 	int val;
 	struct TreeNode *left;
	struct TreeNode *right;
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
class Solution{
public:
    bool isSymmetric(TreeNode* root){
        if(root == nullptr) return true;
        return compare(root -> left, root -> right);
    }
    bool compare(TreeNode* p, TreeNode* q){
        if(p == nullptr && q == nullptr) return true;
        if(p == nullptr || q == nullptr || p -> val != q -> val) return false;
        return compare(p -> left, q -> right) && compare(p -> right, q -> left);
    }
};
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


