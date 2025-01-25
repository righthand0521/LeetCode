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
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        retVal = nums

        returnSize = len(retVal)
        numsSorted = sorted(retVal)

        currGroup = 0
        numToGroup = {}
        numToGroup[numsSorted[0]] = currGroup

        groupToList = {}
        groupToList[currGroup] = deque([numsSorted[0]])

        for i in range(1, returnSize):
            if abs(numsSorted[i] - numsSorted[i - 1]) > limit:
                currGroup += 1
            numToGroup[numsSorted[i]] = currGroup

            if currGroup not in groupToList:
                groupToList[currGroup] = deque()
            groupToList[currGroup].append(numsSorted[i])

        for i in range(returnSize):
            num = retVal[i]
            group = numToGroup[num]
            retVal[i] = groupToList[group].popleft()

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for nums, limit in zip([[1, 5, 3, 9, 8], [1, 7, 6, 18, 2, 1], [1, 7, 28, 19, 10]], [2, 3, 3]):
            # /* Example
            #  *  Input: nums = [1,5,3,9,8], limit = 2
            #  *  Output: [1,3,5,8,9]
            #  *
            #  *  Input: nums = [1,7,6,18,2,1], limit = 3
            #  *  Output: [1,6,7,18,1,2]
            #  *
            #  *  Input: nums = [1,7,28,19,10], limit = 3
            #  *  Output: [1,7,28,19,10]
            #  */
            logging.info("Input: nums = %s, limit = %s", nums, limit)

            retVal = pSolution.lexicographicallySmallestArray(nums, limit)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
