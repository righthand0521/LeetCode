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
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        retVal = root

        if not retVal:
            return retVal

        nodeQueue = deque([retVal])
        levelSums = []

        while nodeQueue:
            levelSum = 0

            levelSize = len(nodeQueue)
            for _ in range(levelSize):
                currentNode = nodeQueue.popleft()
                levelSum += currentNode.val
                if currentNode.left:
                    nodeQueue.append(currentNode.left)
                if currentNode.right:
                    nodeQueue.append(currentNode.right)

            levelSums.append(levelSum)

        nodeQueue.append(retVal)
        levelIndex = 1
        retVal.val = 0
        while nodeQueue:
            levelSize = len(nodeQueue)
            for _ in range(levelSize):
                currentNode = nodeQueue.popleft()

                siblingSum = 0
                if currentNode.left:
                    siblingSum += currentNode.left.val
                if currentNode.right:
                    siblingSum += currentNode.right.val

                if currentNode.left:
                    currentNode.left.val = levelSums[levelIndex] - siblingSum
                    nodeQueue.append(currentNode.left)
                if currentNode.right:
                    currentNode.right.val = levelSums[levelIndex] - siblingSum
                    nodeQueue.append(currentNode.right)

            levelIndex += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for root in [[5, 4, 9, 1, 10, None, 7], [3, 1, 2]]:
            # /* Example
            #  *  Input: root = [5,4,9,1,10,null,7]
            #  *  Output: [0,0,0,7,7,null,11]
            #  *
            #  *  Input: root = [3,1,2]
            #  *  Output: [0,0,0]
            #  */
            logging.info("Input: root = %s", root)

            root = TreeNode().buildTree(root)
            retVal = pSolution.replaceValueInTree(root)
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
