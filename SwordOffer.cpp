#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<stack>
#include<queue>

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
    board[i][j] = '\0';  //标记已访问过的元素
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
13、机器人运动范围 dfs+回溯
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
也不能进入行坐标和列坐标的数位之和大于k的格子。
例如，当k为18时，机器人能够进入方格 [35, 37] ，
因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。
请问该机器人能够到达多少个格子？
*/

//在(i, j)坐标上，数位和是si和sj
int dfs(int i, int j, int si, int sj,  int m, int n, int k, vector<vector<bool> > &visited) {
    //剪枝操作，在搜索中，遇到数位和超出目标值、此元素已访问，则应立即返回
    if(i >= m || j >= n || k < si + sj || visited[i][j]) return 0;
    visited[i][j] = true;
    //(i + 1) % 10 != 0 ? si + 1 : si - 8 之前数位和是si，i+1以后，可能会从9 -> 10,这样si相当于减了8
    return 1 + dfs(i + 1, j, (i + 1) % 10 != 0 ? si + 1 : si - 8, sj, m, n, k, visited) +
                dfs(i, j + 1, si, (j + 1) % 10 != 0 ? sj + 1 : sj - 8, m, n, k, visited);
}
int movingCount(int m, int n, int k) {
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    return dfs(0, 0, 0, 0, m, n, k, visited);
}

/*
14、剪绳子
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），
每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
*/
int cuttingRope(int n){
    if(n <= 3) return n - 1;
    long res = 1;
    while(n > 4){
        res *= 3;
        n -= 3;
    }
    return res * n;
}

/*
15、二进制中1的个数
请实现一个函数，输入一个整数（以二进制串形式），输出该数二进制表示中 1 的个数。
例如，把 9 表示成二进制是 1001，有 2 位是 1。因此，如果输入 9，则该函数输出 2。
*/
int hammingWeight(uint32_t n) {
    int sum = 0;
    while(n){
        sum++;
        n &= (n - 1);
    }
    return sum;
}

/*
16、数值的整数次方 （二分）
实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。
*/

double myPow(double x, int n) {
    if(x == 0) return 0;
    long m = n;
    double res = 1;
    if(m < 0){
        x = 1 / x;
        m = -m;
    }
    while(m > 0){
        if(m % 2 == 1) res *= x;
        m /= 2;
        x *= x;
    }
    return res;
}

/*
17、打印从1到最大的n位数
输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。
*/
vector<int> printNumbers(int n) {
    int endVal = pow(10, n) - 1;
    vector<int> res(endVal);
    for (int i = 0; i < endVal; ++i)
    {
        res[i] = i + 1;
    }
    return res;
}

/*
18、删除链表的节点
给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。
返回删除后的链表的头节点。
*/
ListNode* deleteNode(ListNode* head, int val) {
    ListNode* dummy = new ListNode(0);
    dummy -> next = head;
    ListNode* cur = dummy;
    while(cur -> next){
        if(cur -> next -> val == val){
            cur -> next = cur -> next -> next;
            break;
        }else{
            cur = cur -> next;
        }
    }
    return dummy -> next;
}

/*
19、正则表达式匹配
请实现一个函数用来匹配包含'. '和'*'的正则表达式。
模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。
在本题中，匹配是指字符串的所有字符匹配整个模式。
例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();

        auto matches = [&](int i, int j) {
            if (i == 0) {
                return false;
            }
            if (p[j - 1] == '.') {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int> > f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) {
                        f[i][j] |= f[i - 1][j];
                    }
                }
                else {
                    if (matches(i, j)) {
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }
};

/*
20、表示数值的字符串
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"-1E-16"、"0123"都表示数值，
但"12e"、"1a3.14"、"1.2.3"、"+-5"及"12e+5.4"都不是。

*/
class Solution {
public:
    bool isNumber(string s) {
        //1）先去除字符串首尾的空格
        //2）然后根据e划分指数和底数
        //3）判断指数和底数是否合法即可

        //1、从首尾寻找s中不为空格首尾位置，也就是去除首尾空格
        int i=s.find_first_not_of(' ');
        if(i==string::npos)return false;
        int j=s.find_last_not_of(' ');
        s=s.substr(i,j-i+1);
        if(s.empty())return false;

        //2、根据e来划分底数和指数
        int e=s.find('e');

        //3、指数为空，判断底数
        if(e==string::npos)return judgeP(s);

        //4、指数不为空，判断底数和指数
        else return judgeP(s.substr(0,e))&&judgeS(s.substr(e+1));
    }

    bool judgeP(string s)//判断底数是否合法
    {
        bool result=false,point=false;
        int n=s.size();
        for(int i=0;i<n;++i)
        {
            if(s[i]=='+'||s[i]=='-'){//符号位不在第一位，返回false
                if(i!=0)return false;
            }
            else if(s[i]=='.'){
                if(point)return false;//有多个小数点，返回false
                point=true;
            }
            else if(s[i]<'0'||s[i]>'9'){//非纯数字，返回false
                return false;
            }
            else{
                result=true;
            }
        }
        return result;
    }

    bool judgeS(string s)//判断指数是否合法
    {   
        bool result=false;
        //注意指数不能出现小数点，所以出现除符号位的非纯数字表示指数不合法
        for(int i=0;i<s.size();++i)
        {
            if(s[i]=='+'||s[i]=='-'){//符号位不在第一位，返回false
                if(i!=0)return false;
            }
            else if(s[i]<'0'||s[i]>'9'){//非纯数字，返回false
                return false;
            }
            else{
                result=true;
            }
        }
        return result;
    }
};

/*
21、调整数组顺序使奇数在偶数前面
输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。
*/
vector<int> exchange(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    while(left < right){
        if(nums[left] % 2  == 1){
            left++;
        }else if(nums[right] %2 == 0){
            right--;
        }else{
            swap(nums[left++], nums[right--]);
        } 
    }
    return nums;
}

/*
22、链表的倒数第k个节点
输入一个链表，输出该链表中倒数第k个节点。
为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
*/
ListNode* getKthFromEnd(ListNode* head, int k) {
    ListNode* fast = head;
    ListNode* slow = head;
    while(k--){
        fast = fast -> next;
    }
    while(fast){
        fast = fast -> next;
        slow = slow -> next;
    }
    return slow;
}

/*
24、反转链表
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
*/
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

/*
25、合并两个排序好的链表
输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
*/
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    if(l1 -> val < l2 -> val){
        l1 -> next = mergeTwoLists(l1 -> next, l2);
        return l1;
    }else{
        l2 -> next = mergeTwoLists(l1, l2 -> next);
        return l2;
    }
}

/*
26、树的子结构
输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
B是A的子结构， 即 A中有出现和B相同的结构和节点值。
*/
bool isSubStructure(TreeNode* A, TreeNode* B) {
    return (A && B) && (recur(A, B) ||isSubStructure(A -> left, B) || isSubStructure(A -> right, B));
}
bool recur(TreeNode* A, TreeNode* B){
    if(B == NULL) return true;
    if(A == NULL || A -> val != B -> val) return false;
    return recur(A -> left, B -> left) && recur(A -> right, B -> right);
}

/*
27、二叉树的镜像
请完成一个函数，输入一个二叉树，该函数输出它的镜像。
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
28、对称二叉树
请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。
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
29、顺时针打印矩阵
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。
*/
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.size() == 0) return res;
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;
        while(true){
            for(int i = left; i <= right; i++){
                res.push_back(matrix[top][i]);        
            }
            if(++top > bottom) break;     //最上面一行遍历完删除
            for(int i = top; i <= bottom; i++){
                res.push_back(matrix[i][right]);
            }
            if(--right < left) break;     //最右边一列遍历完删除
            for(int i = right; i >= left; i--){
                res.push_back(matrix[bottom][i]);
            }
            if(--bottom < top) break;     //
            for(int i = bottom; i >= top; i--){
                res.push_back(matrix[i][left]);
            }
            if(++left > right) break;
        }
        return res;
    }
};

/*
30、包含min函数的栈
定义栈的数据结构，
请在该类型中实现一个能够得到栈的最小元素的 min 函数在该栈中，
调用 min、push 及 pop 的时间复杂度都是 O(1)。
*/
class MinStack {
private:
  stack<int> stk;
  stack<int> monoStk;     ////< @note 单调栈，从栈顶到栈底递增
public:
  MinStack() {
  }

  void push(int x) {
    stk.push(x);
    if (monoStk.empty() || monoStk.top() >= x) {
      monoStk.push(x);     ////< @note 必须是大于等于，否则弹出时缺少最小值
    }
  }

  void pop() {
    if (stk.top() == monoStk.top()) {
      monoStk.pop();
    }
    stk.pop();
  }

  int top() {
    return stk.top();
  }

  int min() {
    return monoStk.top();
  }
};

/*
31、栈的压入、弹出序列
输入两个整数序列，第一个序列表示栈的压入顺序，
请判断第二个序列是否为该栈的弹出顺序。
假设压入栈的所有数字均不相等。
例如，序列 {1,2,3,4,5} 是某栈的压栈序列，
序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，
但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。
*/

//因为元素唯一，所以压入和弹出的顺序是固定的，每次将pushed当中的元素入栈，
//并将栈顶元素与popped中的元素一直比较，若相等则出栈，否则结束while循环，重新从pushed当中取元素入栈。
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    stack<int> st;
    int index = 0;
    for (auto x : pushed) {
        st.push(x);
        while (!st.empty() && st.top() == popped[index]) {
            st.pop();
            ++index;
        }
    }
    return st.empty();
}

/*
32-1、从上到下打印二叉树
从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
*/
vector<int> levelOrder1(TreeNode* root) {
    vector<int> res;
    if(root == NULL) return res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int cursize = q.size();
        for(int i = 0; i < cursize; i++){
            TreeNode* node = q.front();
            q.pop();
            res.push_back(node -> val);
            if(node -> left) q.push(node -> left);
            if(node -> right) q.push(node -> right);
        }
    }
    return res;
}

/*
32-2、从上到下打印二叉树
从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
*/
vector<vector<int> > levelOrder2(TreeNode* root) {
    vector<vector<int> > res;
    if(root == NULL) return res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int cursize = q.size();
        vector<int> vec;
        for(int i = 0; i < cursize; i++){
            TreeNode* node = q.front();
            vec.push_back(node -> val);
            q.pop();
            if(node -> left) q.push(node -> left);
            if(node -> right) q.push(node -> right);
        }
        res.push_back(vec);
    }
    return res;
}

/*
32-3 之字型打印二叉树
请实现一个函数按照之字形顺序打印二叉树，
即第一行按照从左到右的顺序打印，
第二层按照从右到左的顺序打印，
第三行再按照从左到右的顺序打印，其他行以此类推。
*/
vector<vector<int> > levelOrder3(TreeNode* root) {
    vector<vector<int> > res;
    if(root == NULL) return res;
    queue<TreeNode*> q;
    q.push(root);
    int flag = 1;
    while(!q.empty()){
        int size = q.size();
        vector<int> vec;
        for(int i = 0; i < size; i++){
            TreeNode* node = q.front();
            q.pop();
            vec.push_back(node -> val);
            if(node -> left) q.push(node -> left);
            if(node -> right) q.push(node -> right);
        }
        if(flag % 2 == 0){
            reverse(vec.begin(), vec.end());
        }
        flag++;
        res.push_back(vec);
    }
    return res;
}

/*
33、二叉搜素树的后序遍历序列
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。
如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。
输入: [1,3,2,6,5]
输出: true
输入: [1,6,3,2,5]
输出: false
*/
bool dfs(vector<int>& postorder, int start, int end){
    if (start >= end)  return true;    // 单个结点，必然是二叉树
    int p = start;
    int rootVal = postorder[end];
    while (postorder[p] < rootVal){    // 找左子树的结束位置
        ++p;
    }
    int leftEnd = p - 1;               // 设置左子树结束位置
    while (postorder[p] > rootVal){    // 找右子树的结束位置
        ++p;
    }
    // 右子树结束位置应该正好在end这里
    return p == end && dfs(postorder, start, leftEnd) && dfs(postorder, leftEnd+1, end-1);
}
bool verifyPostorder(vector<int>& postorder) {
    return dfs(postorder, 0, postorder.size()-1);
}

/*
35、复杂链表的复制
请实现 copyRandomList 函数，复制一个复杂链表。
在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，
还有一个 random 指针指向链表中的任意节点或者 null。
*/
struct Node{
    int val;
    Node* next;
    Node* random;
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
Node* copyRandomList(Node* head) {
    if(head == NULL)  return head;
    unordered_map<Node*, Node*> map;
    Node* t = head;
    while(t != NULL){
        map[t] = new Node(t -> val);
        t = t -> next;
    }
    t = head;
    while(t != NULL){
        if(t -> next){
            map[t] -> next = map[t -> next];
        }
        if(t -> random){
            map[t] -> random = map[t -> random];
        }
        t = t->next;
    }
    return map[head];
}

/*
36、二叉搜索树和双向链表
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。
要求不能创建任何新的节点，只能调整树中节点指针的指向。
希望可以就地完成转换操作。
当转化完成以后，树中节点的左指针需要指向前驱，
树中节点的右指针需要指向后继。
还需要返回链表中的第一个节点的指针
*/
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
Node *pre, *head;
void dfs(Node* cur) {
    if(cur == nullptr) return;
    dfs(cur->left);
    if(pre != nullptr) pre->right = cur;
    else head = cur;
    cur->left = pre;
    pre = cur;
    dfs(cur->right);
}
Node* treeToDoublyList(Node* root) {
    if(root == nullptr) return nullptr;
    dfs(root);
    head->left = pre;
    pre->right = head;
    return head;
}

/*
37、序列化二叉树
实现两个函数，分别用来序列化和反序列化二叉树。
*/
class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "X";
        string l = "(" + serialize(root->left) + ")";
        string r = "(" + serialize(root->right) + ")";
        return  l + to_string(root->val) + r;
    }

    inline TreeNode* parseSubtree(const string &data, int &ptr) {
        ++ptr; // 跳过左括号
        TreeNode* subtree = parse(data, ptr);
        ++ptr; // 跳过右括号
        return subtree;
    }

    inline int parseInt(const string &data, int &ptr) {
        int x = 0, sgn = 1;
        if (!isdigit(data[ptr])) {
            sgn = -1;
            ++ptr;
        }
        while (isdigit(data[ptr])) {
            x = x * 10 + data[ptr++] - '0';
        }
        return x * sgn;
    }

    TreeNode* parse(const string &data, int &ptr) {
        if (data[ptr] == 'X') {
            ++ptr;
            return nullptr;
        }
        TreeNode* cur = new TreeNode(0);
        cur->left = parseSubtree(data, ptr);
        cur->val = parseInt(data, ptr);
        cur->right = parseSubtree(data, ptr);
        return cur;
    }

    TreeNode* deserialize(string data) {
        int ptr = 0;
        return parse(data, ptr);
    }
};

/*
38、字符串的排列
输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
*/
void backtracking(string s, int startIndex, vector<string>& res){
    if(startIndex == s.size()){
        res.push_back(s);
        return;
    }
    unordered_set<char> set;
    for(int i = startIndex; i < s.size(); i++){
        if(set.find(s[i]) != set.end()){
            continue;
        }else{
            set.insert(s[i]);
        }
        swap(s[i], s[startIndex]);
        backtracking(s, startIndex + 1, res);
        swap(s[i], s[startIndex]);
    }
}
vector<string> permutation(string s) {
    vector<string> res;
    backtracking(s, 0, res);
    return res;
}

/*
39、数组中次数超过一半的数字
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。
*/
int moreThanHalf(vector<int>& arr){
    int res = 0, vote = 0;
    for(int i = 0; i < arr.size(); i++){
        if(vote == 0) res = arr[i];
        if(res == arr[i]){
            vote++;
        }else{
            vote--;
        }   
    }
    return res;
}

/*
40、最小的k个数
输入整数数组 arr ，找出其中最小的 k 个数。
例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
*/
vector<int> getLeastNumbers(vector<int>& arr, int k) {
    vector<int> res;
    if(arr.size() == 0 || k > arr.size() || k <= 0) return res;
    if(k == arr.size()) return arr;
    int left = 0, right = arr.size() - 1;
    while(left < right){
        int mid = partition(arr, left, right);
        if(mid == k) break;
        else if(mid > k){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    for(int i = 0; i < k; i++){
        res.push_back(arr[i]);
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
41、数据流中的中位数
如何得到一个数据流中的中位数？
如果从数据流中读出奇数个数值，
那么中位数就是所有数值排序之后位于中间的数值。
如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
*/
/*
每插入一个数之前，先判断两个堆的 size() 是否相等。
若相等，先将这个数插入大顶堆，然后将大顶堆的 top() 插入小顶堆。
这么做可以保证小顶堆的所有数永远大于等于大顶堆的 top()。
若不相等，先将这个数插入小顶堆，然后将小顶堆的 top() 插入大顶堆。
这么做可以保证大顶堆的所有数永远小于等于小顶堆的 top()。
整个过程动态地做到了平衡两个堆的 size()，即保证它们的 size() 最大只相差了 1
*/
class MedianFinder {
public:

    priority_queue<int, vector<int>, less<int> > maxheap;
    priority_queue<int, vector<int>, greater<int> > minheap;

    MedianFinder() {

    }
    void addNum(int num) {
        if(maxheap.size() == minheap.size()) {
            maxheap.push(num);
            minheap.push(maxheap.top());
            maxheap.pop();
        }
        else {
            minheap.push(num);
            maxheap.push(minheap.top());
            minheap.pop();
        }
    }
    
    double findMedian() {
        int maxSize = maxheap.size(), minSize = minheap.size();
        int mid1 = maxheap.top(), mid2 = minheap.top();
        return maxSize == minSize ? ((mid1 + mid2) * 0.5) : mid2;
    }
};

/*
42、连续子数组的最大和
输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。
要求时间复杂度为O(n)。
*/
int maxSubArray(vector<int>& nums) {
    vector<int> dp(nums.size());
    dp[0] = nums[0];
    int res = dp[0];
    for(int i = 1; i < nums.size(); i++){
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        res = max(res, dp[i]);
    }
    return res;
}

/*
43、1～n整数中 1 的个数
输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。

例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。
*/
int countDigitOne(int n) {
    long digit = 1; // digit 需为 long 型，因为比如 n 是 INT_MAX，digit 会在最后一次循环越界
    int high = n / 10, cur = n % 10, low = 0;
    int res = 0;
    while (high != 0 || cur != 0) {
        if (cur == 0) {
            res += high * digit;
        }
        else if (cur == 1) {
            res += high * digit + low + 1;
        }
        else {
            res += (high + 1) * digit;
        }
        low += cur * digit;
        cur = high % 10;
        high /= 10;
        digit *= 10; 
    }
    return res;
}

/*

*/






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