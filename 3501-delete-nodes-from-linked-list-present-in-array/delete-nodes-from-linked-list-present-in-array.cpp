/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    bool is_inside(const std::unordered_set<int> &nums, int target){
        std::unordered_set<int> nums_set(nums.begin(), nums.end());
        return nums_set.find(target) != nums_set.end();
    }
    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        if(head==NULL)
            return NULL;
            
        ListNode *current= head;
        ListNode *prev= NULL;
        std::unordered_set<int> nums_set(nums.begin(), nums.end());
        while(current && current->next!=NULL){
            if(nums_set.find(current->val) != nums_set.end()){
                if(head==current){
                    head=current->next;
                    current=head;
                }else{
                    prev->next=current->next;
                    current=prev->next;
                }

            }else{
                prev=current;
                current=current->next;
            }
        }
        if(current && nums_set.find(current->val) != nums_set.end()){
            prev->next=NULL;
            delete current;
        }
        return head;
 
           
    } 

};