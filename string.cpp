#include<string>
#include<stack>

using namespace std;
/*
括号序列 
给出一个仅包含字符'(',')','{','}','['和']',的字符串，判断给出的字符串是否是合法的括号序列
括号必须以正确的顺序关闭，"()"和"()[]{}"都是合法的括号序列，但"(]"和"([)]"不合法。
示例1
*/
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(int  i = 0; i < s.size(); i++){
            if(st.empty()){
                st.push(s[i]);
                continue;
            }
            if(s[i] == ')' && st.top()=='(') st.pop();
            else if(s[i] == '}' && st.top() == '{') st.pop();
            else if(s[i] == ']' && st.top() == '[') st.pop();
            else{
                st.push(s[i]);
            }
        }
        return st.empty();
    }
};

