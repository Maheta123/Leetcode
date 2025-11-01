#include <unordered_set>
#include <vector>
class Solution {
public:
    ListNode* modifiedList(std::vector<int>& nums, ListNode* head) {
        std::unordered_set<int> nums_set(nums.begin(), nums.end());
        ListNode dummy(-1);
        dummy.next = head;
        ListNode* prev = &dummy;
        ListNode* current = head;
        while (current) {
            if (nums_set.find(current->val) != nums_set.end()) {
                prev->next = current->next;
            } else {
                prev = current;
            }
            current = current->next;
        }
        return dummy.next;
    }
};