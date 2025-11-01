# Definition for singly-linked list.
# class ListNode(object):
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution(object):
    def modifiedList(self, nums, head):
        """
        :type nums: List[int]
        :type head: Optional[ListNode]
        :rtype: Optional[ListNode]
        """
        temp=head
        prev=None
        numset=set(nums)
        while temp:
            if head.val in numset:
                head=head.next
            else:
                temp=None
        temp=head.next
        prev=head
        while temp:
            if(temp.val in numset):
                prev.next=temp.next
                
                if(temp.next is None):
                    break
            else:
                prev=temp
            temp=temp.next
        return head

            
        