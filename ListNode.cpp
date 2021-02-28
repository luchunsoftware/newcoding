#include<vector>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


/*
翻转链表 简单
*/
class Solution{
public:
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
按k个一组翻转链表 困难
*/
class Solution {
public:
  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* pre = dummy; 
    ListNode* cur = dummy;
    while(cur->next != NULL) {
      for(int i = 0; i < k && cur != NULL; i++){
          cur = cur -> next;
      }
      if(cur == NULL) break;
      ListNode* start = pre->next;
      ListNode* end = cur->next;
      cur->next = NULL;   // 方便翻转子链表
      pre->next = reverseList(start);
      start->next = end;

      pre = start; 
      cur = start;    // 更新到下一段的前驱位置
    }
    return dummy->next;
  }

  ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    while(curr != NULL) {
      ListNode* next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    return prev;
  }
};



/*
剑指offer22.链表中倒数第k个节点 简单
*/
class Solution {
public:
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
};


/*
19.删除倒数第n个节点 中等

双指针，第二个指针指向dummyNode*/
class Solution{
public:
    ListNode* deleteNthFromEnd(ListNode* head, int n){
        ListNode* dummy = new ListNode(0);
        dummy -> next = head;
        ListNode* first = head;
        ListNode* second = dummy;
        for(int i = 0; i < n; i++){
            first = first -> next;
        }
        while(first){
            first = first -> next;
            second = second -> next;
        }
        second -> next = second -> next -> next;
        return dummy -> next;
    }
};

/*
142.链表中环的入口 中等

快慢指针，一个一步，一个两步
*/
class Solution{
public:
    ListNode* detectCycle(ListNode* head){
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast && fast -> next){
            fast = fast -> next -> next;
            slow = slow -> next;
            if(fast == slow){
                ListNode* index1 = fast;
                ListNode* index2 = head;
                while(index1 != index2){
                    index1 = index1 -> next;
                    index2 = index2 -> next;
                }
                return index1;
            }
        }
        return nullptr;
    }
};

/*
21.合并两个有序链表 简单
*/

class Solution{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2){
        if(l1 == nullptr) return l2;
        if(l2 == nullptr) return l1;
        if(l1 -> val < l2 -> val){
            l1 -> next = mergeTwoLists(l1 -> next, l2);
            return l1;
        }else{
            l2 -> next = mergeTwoLists(l1, l2 -> next);
            return l2;
        }
    }
};

/*
234.回文链表 简单
先用数组存起来，再双指针判断回文
*/
class Solution{
public:
    bool isPalindrome(ListNode* head){
        vector<int> vec;
        while(head){
            vec.push_back(head -> val);
            head = head -> next;
        }
        int size = vec.size();
        int i = 0, j = size - 1;
        while( i < j){
            if(vec[i++] == vec[j--]){
            }else{
                return false;
            }
        }
        return true;
    }
};

/*
两个链表的第一个公共节点 简单

双指针 两个都走l1 + l2 + c步的时候，相遇
*/
class Selation{
public:
    ListNode* get1stmeet(ListNode* l1,ListNode* l2){
        ListNode* node1 = l1;
        ListNode* node2 = l2;
        while(node1 != node2){
            node1 = node1 != nullptr ? node1 -> next : l2;
            node2 = node2 != nullptr ? node2 -> next : l1;
        }
        return node1;
    }
};
