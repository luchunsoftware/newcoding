#include<vector>
#include<stack>

using namespace std;

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
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
            ListNode* node = cur -> next;
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
23、合并k个已排序的链表
合并 k个已排序的链表并将其作为一个已排序的链表返回。分析并描述其复杂度。 
*/
// 合并两个有序链表
ListNode* merge(ListNode* p1, ListNode* p2){
    if(!p1) return p2;
    if(!p2) return p1;
    if(p1->val <= p2->val){
        p1->next = merge(p1->next, p2);
        return p1;
    }else{
        p2->next = merge(p1, p2->next);
        return p2;
    }
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if(lists.size() == 0) return nullptr;
    ListNode* head = lists[0];
    for(int i = 1; i<lists.size(); ++i){
        if(lists[i]) head = merge(head, lists[i]);
    }
    return head;  
}

/*
148、排序链表
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

进阶：
你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
*/
ListNode * sortList(ListNode * head){
    return  (head == NULL)? NULL: mergeSort(head);
}
ListNode * findMid(ListNode * head){
    ListNode * slow = head;
    ListNode * fast = head;
    ListNode * pre = NULL;
    while (fast && fast->next){
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    pre->next = NULL;
    return slow;
}

ListNode * mergeTwoLists(ListNode * l1, ListNode * l2){
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;

    if(l1->val < l2->val){
        l1->next = mergeTwoLists(l1->next,l2);
        return l1;
    }else{
        l2->next = mergeTwoLists(l1,l2->next);
        return l2;
    }
}

ListNode * mergeSort(ListNode * head){
    if(head->next == NULL) return head;
    ListNode * mid = findMid(head);
    ListNode * l1 = mergeSort(head);
    ListNode * l2 = mergeSort(mid);
    return mergeTwoLists(l1, l2);
}

/*
栈先存储，逐个相加，cnt储存进位
两个链表生成相加链表
假设链表中每一个节点的值都在 0 - 9 之间，那么链表整体就可以代表一个整数。
给定两个这种链表，请生成代表两个整数相加值的结果链表。
例如：链表 1 为 9->3->7，链表 2 为 6->3，最后生成新的结果链表为 1->0->0->0。
*/
class Solution {
public:

    ListNode* addInList(ListNode* head1, ListNode* head2) {
        stack<int> st1, st2;
        while(head1){
            st1.push(head1 -> val);
            head1 = head1 -> next;
        }
        while(head2){
            st2.push(head2 -> val);
            head2 = head2 -> next;
        }
        int cnt = 0;  //存储进位
        ListNode* res = nullptr;
        while(!st1.empty() || !st2.empty()){
            int x1 = st1.empty() ? 0 : st1.top();
            int x2 = st2.empty() ? 0 : st2.top();
            if(!st1.empty()) st1.pop();
            if(!st2.empty()) st2.pop();
            int sum = x1 + x2 + cnt;
            cnt = sum / 10;
            ListNode* node = new ListNode(sum % 10);
            node -> next = res;
            res = node;
        }
        if(cnt > 0){
            ListNode* node = new ListNode(cnt);
            node -> next = res;
            res = node;
        }
        return res;
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
