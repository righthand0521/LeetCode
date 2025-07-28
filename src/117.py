import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop

from treeNode import Node


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


# """
# # Definition for a Node.
# class Node:
#     def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
#         self.val = val
#         self.left = left
#         self.right = right
#         self.next = next
# """
class Solution:
    def connect(self, root: 'Node') -> 'Node':
        retVal = None

        if root is None:
            return None

        queue = deque([root])
        while queue:
            queueSize = len(queue)
            last = None
            for _ in range(queueSize):
                node = queue.popleft()
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
                if last:
                    last.next = node
                last = node
        retVal = root

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 3, 4, 5, None, 7], []]:
            # /* Example
            #  *  Input: root = [1,2,3,4,5,null,7]
            #  *  Output: [1,#,2,3,#,4,5,7,#]
            #  *
            #  *  Input: root = []
            #  *  Output: []
            #  */
            logging.info("Input: root = %s", root)

            root = Node().buildTree(root)
            retVal = pSolution.connect(root)
            retVal = Node().displayNodeTreeByNext(retVal)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
