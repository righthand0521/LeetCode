import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

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


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        retVal = None

        inorderSize = len(inorder)
        preorderSize = len(preorder)

        if preorderSize == 0:
            return retVal

        preorderIndex = preorderSize
        inorderIndex = 0
        stack = []

        # /* Example
        #  *      (3)        v  pre: 3  9 20 15  7
        #  *   (9)   (20)    v   in: 9  3 15 20  7
        #  *      (15)  (7)    post: 9 15  7 20  3
        #  */
        retVal = TreeNode(preorder[0])
        stack.append(retVal)
        for i in range(1, preorderIndex):
            preorderVal = preorder[i]
            node = stack[-1]
            if node.val != inorder[inorderIndex]:
                node.left = TreeNode(preorderVal)
                stack.append(node.left)
            else:
                while (len(stack) != 0) and (stack[-1].val == inorder[inorderIndex]):
                    node = stack[-1]
                    stack.pop()
                    inorderIndex += 1
                node.right = TreeNode(preorderVal)
                stack.append(node.right)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for preorder, inorder in zip([[3, 9, 20, 15, 7], [-1]], [[9, 3, 15, 20, 7], [-1]]):
            # /* Example
            #  *  Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
            #  *  Output: [3,9,20,null,null,15,7]
            #  *
            #  *  Input: preorder = [-1], inorder = [-1]
            #  *  Output: [-1]
            #  */
            logging.info("Input: preorder = %s, inorder = %s",
                         preorder, inorder)

            retVal = pSolution.buildTree(preorder, inorder)
            retVal = TreeNode().printLevelOrder(retVal)
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
