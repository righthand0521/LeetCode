from typing import List


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __str__(self):
        # defining a blank res variable
        res = ""

        # initializing ptr to head
        ptr = self

        # traversing and adding it to res
        while ptr:
            res += str(ptr.val) + ", "
            ptr = ptr.next

        # removing trailing commas
        res = res.strip(", ")

        # chen checking if
        # anything is present in res or not
        if len(res):
            return "[" + res + "]"
        else:
            return "[]"

    def buildList(nums: List[int]):
        pHead = ListNode(0)
        pCurrent = pHead
        for pNode in nums:
            pCurrent.next = ListNode(pNode)
            pCurrent = pCurrent.next
        pHead = pHead.next

        return pHead


class ListNodeCommon:
    def __init__(self) -> None:
        self.cycleIndex = -1

    def printListNode(self, head: ListNode) -> None:
        pNode = head
        while pNode != None:
            print(pNode.val, end="," if pNode.next != None else "")
            pNode = pNode.next

    def addListNodeCycle(self, head: ListNode, pos: int) -> ListNode:
        retVal = head

        if pos == self.cycleIndex:
            return retVal

        pCycle = head
        pNode = head
        while pNode.next != None:
            if pos == 0:
                pCycle = pNode
            pNode = pNode.next
            pos -= 1
        pNode.next = pCycle

        return retVal


class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
