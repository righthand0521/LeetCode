import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from copy import deepcopy
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
    def smallestChair(self, times: List[List[int]], targetFriend: int) -> int:
        retVal = 0

        times = sorted([(arrival, leave, index) for index, (arrival, leave) in enumerate(times)])

        nextChair = 0
        availableChairs = []
        leavingQueue = []
        for time in times:
            arrival, leave, index = time

            while leavingQueue and leavingQueue[0][0] <= arrival:
                _, chair = heappop(leavingQueue)
                heappush(availableChairs, chair)

            if availableChairs:
                currentChair = heappop(availableChairs)
            else:
                currentChair = nextChair
                nextChair += 1

            heappush(leavingQueue, (leave, currentChair))

            if index == targetFriend:
                retVal = currentChair
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for times, targetFriend in zip([[[1, 4], [2, 3], [4, 6]], [[3, 10], [1, 5], [2, 6]]], [1, 0]):
            # /* Example
            #  *  Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
            #  *  Output: 1
            #  *
            #  *  Input: times = [[3,10],[1,5],[2,6]], targetFriend = 0
            #  *  Output: 2
            #  */
            logging.info("Input: times = %s, targetFriend = %s", times, targetFriend)

            retVal = pSolution.smallestChair(times, targetFriend)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
