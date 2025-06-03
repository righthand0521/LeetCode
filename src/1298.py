import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional


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
    def maxCandies(
        self,
            status: List[int],
            candies: List[int],
            keys: List[List[int]],
            containedBoxes: List[List[int]],
            initialBoxes: List[int]
    ) -> int:
        retVal = 0

        statusSize = len(status)
        canOpen = [status[i] == 1 for i in range(statusSize)]
        hasBox = [False] * statusSize
        used = [False] * statusSize

        bfsQueue = deque()
        for initialBox in initialBoxes:
            hasBox[initialBox] = True
            if canOpen[initialBox] == True:
                bfsQueue.append(initialBox)
                used[initialBox] = True
                retVal += candies[initialBox]

        bfsQueueSize = len(bfsQueue)
        while bfsQueueSize > 0:
            bigBox = bfsQueue.popleft()
            bfsQueueSize -= 1

            for key in keys[bigBox]:
                canOpen[key] = True
                if (used[key] == False) and (hasBox[key] == True):
                    bfsQueue.append(key)
                    bfsQueueSize += 1
                    used[key] = True
                    retVal += candies[key]

            for box in containedBoxes[bigBox]:
                hasBox[box] = True
                if (used[box] == False) and (canOpen[box] == True):
                    bfsQueue.append(box)
                    bfsQueueSize += 1
                    used[box] = True
                    retVal += candies[box]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for status, candies, keys, containedBoxes, initialBoxes in zip(
                [[1, 0, 1, 0], [1, 0, 0, 0, 0, 0]],
                [[7, 5, 4, 100], [1, 1, 1, 1, 1, 1]],
                [[[], [], [1], []], [[1, 2, 3, 4, 5], [], [], [], [], []]],
                [[[1, 2], [3], [], []], [[1, 2, 3, 4, 5], [], [], [], [], []]],
                [[0], [0]]
        ):
            # /* Example
            #  *  Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]],
            #  *  containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
            #  *  Output: 16
            #  *
            #  *  Input: status = [1,0,0,0,0,0], candies = [1,1,1,1,1,1], keys = [[1,2,3,4,5],[],[],[],[],[]],
            #  *  containedBoxes = [[1,2,3,4,5],[],[],[],[],[]], initialBoxes = [0]
            #  *  Output: 6
            #  */
            logging.info(
                "Input: status = %s, candies = %s, keys = %s, containedBoxes = %s, initialBoxes = %s",
                status, candies, keys, containedBoxes, initialBoxes)

            retVal = pSolution.maxCandies(status, candies, keys, containedBoxes, initialBoxes)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
