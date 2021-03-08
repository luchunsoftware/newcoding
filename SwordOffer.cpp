#include<vector>
#include<unordered_map>
#include<string>
#include<stack>

using namespace std;
/*
03、找出数组中重复的数字。 
在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
请找出数组中任意一个重复的数字。
*/
int findRepeatNumber(vector<int>& nums) {
    unordered_map<int, int> map;
    for(int i = 0; i < nums.size(); i++){
        if(map.find(nums[i]) != map.end()){
            return nums[i];
        }else{
            map[nums[i]]++;
        }
    }
    return -1;
}
/*
04、二维数组的查找  （同leetcode240）二分
在一个 n * m 的二维数组中，
每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。
请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
*/
bool findNumberIn2DArray(vector<vector<int> >& matrix, int target) {
    if(matrix.empty()) return false;
    int row = matrix.size() - 1;
    int column = matrix[0].size() - 1;
    int i = row, j = 0;
    while(i >= 0 && j <= column){
        if(matrix[i][j] == target){
            return true;
        }else if(matrix[i][j] > target){
            i--;
        }else{
            j++;
        }
    }
    return false;
}

/*
05、替换空格
将字符串s中的每个空格替换成“%20”
*/
string replaceSpace(string s) {
    string res;
    for(int i = 0; i < s.size();i++){
        s[i] != ' ' ? res += s[i] : res += "%20"; 
    }
    return res;
}

/*
06、从尾到头打印链表
输入一个链表的头节点，从尾到头返回每个节点的值
*/
struct ListNode{
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(NULL){}
};
vector<int> reversePrint(ListNode* head) {
    vector<int> res;
    while(head){
        res.push_back(head -> val);
        head = head -> next;
    }
    reverse(res.begin(), res.end());
    return res;
}

/*
07、重建二叉树 （同leetcode105）
输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
*/
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return build(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }
    TreeNode* build(vector<int>& preorder, int prestart, int preend, vector<int>& inorder, int instart, int inend){
        if(preend - prestart == 0) return NULL;
        int rootvalue = preorder[prestart];
        TreeNode* root = new TreeNode(rootvalue);
        if(preend - prestart == 1) return root;
        int index;
        for(index = instart; index < inend; index++){
            if(inorder[index] == rootvalue) break;
        }
        //切分
        int leftinstart = instart, leftinend = index;
        int rightinstart = index + 1, rightinend = inend;
        int leftprestart = prestart + 1, leftpreend = prestart + 1 + index - instart;
        int rightprestart = leftpreend, rightpreend = preend;
        root -> left = build(preorder, leftprestart, leftpreend, inorder, leftinstart, leftinend);
        root -> right = build(preorder, rightprestart, rightpreend, inorder, rightinstart, rightinend);
        return root;
    }
};
/*
09、两个栈实现一个队列
*/
stack<int> stack1;
stack<int> stack2;
void push(int node) {
    stack1.push(node);
}

int pop() {
    if(stack2.empty()){
        while(!stack1.empty()){
            stack2.push(stack1.top());
            stack1.pop();
        }
    }
    int res = stack2.top();
    stack2.pop();
    return res;
}
/*
10-1、斐波那契数列
写一个函数，输入n，求斐波那契数列的第n项
f(0) = 0, f(1) = 1, f(n) = f(n - 1) + f(n - 2) n > 1
*/
int fib(int n) {
    if(n == 0) return 0;
    if(n <= 2) return 1;
    int a = 1, b = 1, c = 0;
    for(int i = 3; i <= n; i++){
        c = (a + b) % 1000000007;
        a = b;
        b = c;
    }
    return c;
}

/*
10-2、青蛙跳台阶问题
一次可以跳1级台阶，也可以跳2级台阶，求跳n级台阶总共有多少跳法，答案取模1000000007
*/
int numWays(int n) {
    if(n == 0) return 1;
    if(n <= 2) return n;
    int a = 1, b = 2, c = 0;
    for(int i = 3; i <= n; i++){
        c = (a + b) % 1000000007;
        a = b;
        b = c;
    }
    return c;
}

/*
11、旋转数组的最小数字（同leetcode154）
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。有重复数字
例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  
*/
int minArray(vector<int>& arr) {
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

/*
12、矩阵中的路径  （同leetcode 79）  dfs+回溯
请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。
如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。
例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。
*/

int rows, cols;
bool dfs(vector<vector<char> >& board, string word, int i, int j, int k) {
    //剪枝条件，遇到这种直接返回
    if(i >= rows || i < 0 || j >= cols || j < 0 || board[i][j] != word[k])
        return false;
    //终止条件
    if(k == word.size() - 1) 
        return true;
    board[i][j] = '\0';
    bool res = dfs(board, word, i + 1, j, k + 1) || dfs(board, word, i - 1, j, k + 1) || 
                    dfs(board, word, i, j + 1, k + 1) || dfs(board, word, i , j - 1, k + 1);
    board[i][j] = word[k];
    return res;
}

bool exist(vector<vector<char> >& board, string word) {
    rows = board.size();
    cols = board[0].size();
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(dfs(board, word, i, j, 0)) return true;
        }
    }
    return false;
}







/*
输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。

序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。
*/

vector<vector<int> > findContinuousSequence(int target) {
    vector<vector<int> > res;
    int l = 1;
    int r = 2;
    int curSum = 0;
    while (l < r){
        //核心是这个求和公式
        curSum = (l+r)*(r-l+1)/2;
        if (curSum == target){
            vector<int> curRes;
            for (int i = l; i <= r; ++i){
                curRes.push_back(i);
            }
            res.push_back(curRes);
            ++l;
        }
        else if (curSum < target) ++r;
        else ++l;
    }
    return res;
}