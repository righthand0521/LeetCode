import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class Solution:
    def validateBinaryTreeNodes(self, n: int, leftChild: List[int], rightChild: List[int]) -> bool:
        retVal = False

        root = -1
        children = set(leftChild) | set(rightChild)
        for i in range(n):
            if i not in children:
                root = i
                break
        if root == -1:
            return retVal

        visited = {root}
        bfsQueue = deque([root])
        while bfsQueue:
            node = bfsQueue.popleft()
            for child in [leftChild[node], rightChild[node]]:
                if child == -1:
                    continue
                if child in visited:
                    return retVal
                bfsQueue.append(child)
                visited.add(child)
        if len(visited) == n:
            retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, leftChild, rightChild in zip([4, 4, 2],
                                            [[1, -1, 3, -1], [1, -1, 3, -1], [1, 0]],
                                            [[2, -1, -1, -1], [2, 3, -1, -1], [-1, -1]]):
            # /* Example
            #  *  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
            #  *  Output: true
            #  *
            #  *  Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
            #  *  Output: false
            #  *
            #  *  Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
            #  *  Output: false
            #  */
            logging.info("Input: n = %s, leftChild = %s, rightChild = %s", n, leftChild, rightChild)

            retVal = pSolution.validateBinaryTreeNodes(n, leftChild, rightChild)
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
