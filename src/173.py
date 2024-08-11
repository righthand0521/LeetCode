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
class BSTIterator:
    def __init__(self, root: Optional[TreeNode]):
        self.queue = deque()
        self.inOrder(root)

    def inOrder(self, root: Optional[TreeNode]) -> None:
        if not root:
            return
        self.inOrder(root.left)
        self.queue.append(root.val)
        self.inOrder(root.right)

    def next(self) -> int:
        retVal = self.queue.popleft()

        return retVal

    def hasNext(self) -> bool:
        retVal = False

        queueSize = len(self.queue)
        if queueSize > 0:
            retVal = True

        return retVal


# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.next()
# param_2 = obj.hasNext()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]],
                                [[[[7, 3, 15, None, None, 9, 20]], [], [], [], [], [], [], [], [], []]]):
            # /* Example
            #  *  Input
            #  *  ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
            #  *  [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
            #  *  Output
            #  *  [null, 3, 7, true, 9, true, 15, true, 20, false]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "BSTIterator":
                    obj = BSTIterator(TreeNode().buildTree(value[0]))
                    displayStr.append(None)
                elif key == "next":
                    retVal = obj.next()
                    displayStr.append(retVal)
                elif key == "hasNext":
                    retVal = obj.hasNext()
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
