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
    def dfs(self, root: 'Optional[Node]') -> None:
        if root == None:
            return

        # /* Example
        #  *                                          (01)
        #  *
        #  *                    (02) ------------------01-----------------> (03)
        #  *
        #  *         (04) -------04------> (05) -------02------> (06) -------08------> (07)
        #  *
        #  *    (08) -06-> (09) -05-> (10) -07-> (11) -03-> (12) -10-> (13) -09-> (14) -11-> (15)
        #  */
        left = root.left
        right = root.right
        while left != None:
            left.next = right
            left = left.right
            right = right.left
        self.dfs(root.left)
        self.dfs(root.right)

    def connect(self, root: 'Optional[Node]') -> 'Optional[Node]':
        retVal = root

        self.dfs(retVal)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[1, 2, 3, 4, 5, 6, 7], []]:
            # /* Example
            #  *  Input: root = [1,2,3,4,5,6,7]
            #  *  Output: [1,#,2,3,#,4,5,6,7,#]
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
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
