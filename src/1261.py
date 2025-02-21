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
class FindElements:
    def __init__(self, root: Optional[TreeNode]):
        self.seen = set()
        self.dfs(root, 0)

    def dfs(self, currentNode, currentValue):
        if currentNode is None:
            return

        # visit current node by adding its value to seen
        self.seen.add(currentValue)
        self.dfs(currentNode.left, currentValue * 2 + 1)
        self.dfs(currentNode.right, currentValue * 2 + 2)

    def find(self, target: int) -> bool:
        retVal = target in self.seen

        return retVal

# Your FindElements object will be instantiated and called as such:
# obj = FindElements(root)
# param_1 = obj.find(target)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, val in zip([["FindElements", "find", "find"],
                                 ["FindElements", "find", "find", "find"],
                                 ["FindElements", "find", "find", "find", "find"]],
                                [[[[-1, None, -1]], [1], [2]],
                                 [[[-1, -1, -1, -1, -1]], [1], [3], [5]],
                                 [[[-1, None, -1, -1, None, -1]], [2], [3], [4], [5]]]):
            # /* Example
            #  *  Input
            #  *  ["FindElements","find","find"]
            #  *  [[[-1,null,-1]],[1],[2]]
            #  *  Output
            #  *  [null,false,true]
            #  *
            #  *  Input
            #  *  ["FindElements","find","find","find"]
            #  *  [[[-1,-1,-1,-1,-1]],[1],[3],[5]]
            #  *  Output
            #  *  [null,true,true,false]
            #  *
            #  *  Input
            #  *  ["FindElements","find","find","find","find"]
            #  *  [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
            #  *  Output
            #  *  [null,true,false,false,true]
            #  */
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "FindElements":
                    obj = FindElements(TreeNode().buildTree(value[0]))
                    displayStr.append(None)
                elif key == "find":
                    retVal = obj.find(value[0])
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
