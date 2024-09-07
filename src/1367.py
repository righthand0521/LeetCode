import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

from list import ListNode, ListNodeCommon
from tree import TreeNode


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def dfs(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        retVal = False

        if head is None:
            retVal= True
        elif root is None:
            retVal= False
        elif head.val != root.val:
            retVal= False
        else:
            retVal = self.dfs(head.next, root.left) or self.dfs(head.next, root.right)

        return retVal

    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        retVal = False

        if root is None:
            return retVal

        retVal = self.dfs(head, root) or self.isSubPath(head, root.left) or self.isSubPath(head, root.right)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for head, root in zip(
                [
                    [4, 2, 8],
                    [1, 4, 2, 6],
                    [1, 4, 2, 6, 8]
                ],
                [
                    [1, 4, 4, None, 2, 2, None, 1, None, 6, 8, None, None, None, None, 1, 3],
                    [1, 4, 4, None, 2, 2, None, 1, None, 6, 8, None, None, None, None, 1, 3],
                    [1, 4, 4, None, 2, 2, None, 1, None, 6, 8, None, None, None, None, 1, 3]
                ]
        ):
            # /* Example
            #  *  Input: head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
            #  *  Output: true
            #  *
            #  *  Input: head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
            #  *  utput: true
            #  *
            #  *  Input: head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
            #  *  Output: false
            #  */
            logging.info("Input: head = %s, root = %s", head, root)

            retVal = pSolution.isSubPath(ListNode.buildList(head), TreeNode().buildTree(root))
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
