import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

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
    def recoverFromPreorder(self, traversal: str) -> Optional[TreeNode]:
        retVal = None

        traversalSize = len(traversal)
        stack = []
        index = 0
        while index < traversalSize:
            # Count the number of dashes
            depth = 0
            while (index < traversalSize) and (traversal[index] == "-"):
                depth += 1
                index += 1

            # Extract the node value
            value = 0
            while (index < traversalSize) and (traversal[index].isdigit()):
                value = value * 10 + int(traversal[index])
                index += 1

            # Create the current node
            node = TreeNode(value)

            # Adjust the stack to the correct depth
            while len(stack) > depth:
                stack.pop()

            # Attach the node to the parent
            if stack:
                if stack[-1].left is None:
                    stack[-1].left = node
                else:
                    stack[-1].right = node

            # Push the current node onto the stack
            stack.append(node)

        retVal = stack[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for traversal in ["1-2--3--4-5--6--7", "1-2--3---4-5--6---7", "1-401--349---90--88"]:
            # /* Example
            #  *  Input: traversal = "1-2--3--4-5--6--7"
            #  *  Output: [1,2,5,3,4,6,7]
            #  *
            #  *  Input: traversal = "1-2--3---4-5--6---7"
            #  *  Output: [1,2,5,3,null,6,null,4,null,7]
            #  *
            #  *  Input: traversal = "1-401--349---90--88"
            #  *  Output: [1,401,null,349,88,90]
            #  */
            logging.info("Input: traversal = \"%s\"", traversal)

            retVal = pSolution.recoverFromPreorder(traversal)
            retVal = TreeNode().printLevelOrder(retVal)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
