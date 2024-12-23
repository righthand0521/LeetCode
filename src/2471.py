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
    def __init__(self) -> None:
        self.shift = 20
        self.mask = 0xFFFFF

    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        retVal = 0

        # Process tree level by level using BFS
        queue = deque([root])
        while queue:
            level_size = len(queue)
            nodes = []

            # Store node values with encoded positions
            for i in range(level_size):
                node = queue.popleft()
                # Encode value and index: high 20 bits = value, low 20 bits = index
                nodes.append((node.val << self.shift) + i)

                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)

            # Sort nodes by their values (high 20 bits)
            nodes.sort()

            # Count swaps needed to match indices with original positions
            i = 0
            while i < level_size:
                origPos = nodes[i] & self.mask
                if origPos != i:
                    # Swap nodes and decrement i to recheck current position
                    nodes[i], nodes[origPos] = nodes[origPos], nodes[i]
                    retVal += 1
                    i -= 1
                i += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 4, 3, 7, 6, 8, 5, None, None, None, None, 9, None, 10],
                     [1, 3, 2, 7, 6, 5, 4],
                     [1, 2, 3, 4, 5, 6]]:
            # /* Example
            #  *  Input: root = [1,4,3,7,6,8,5,null,null,null,null,9,null,10]
            #  *  Output: 3
            #  *
            #  *  Input: root = [1,3,2,7,6,5,4]
            #  *  Output: 3
            #  *
            #  *  Input: root = [1,2,3,4,5,6]
            #  *  Output: 0
            #  */
            logging.info("Input: root = %s", root)

            retVal = pSolution.minimumOperations(TreeNode().buildTree(root))
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
