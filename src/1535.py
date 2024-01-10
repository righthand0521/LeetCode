import sys
import logging
from typing import List, Optional
from collections import defaultdict, deque, Counter
from functools import cache, lru_cache
from bisect import bisect_left, bisect_right
from itertools import accumulate
from heapq import heapify, heappush, heappop


def logging_setting():
    LOG_LEVEL = logging.INFO  # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt="%Y/%m/%d %H:%M:%S",
    )


class Solution:
    def getWinner(self, arr: List[int], k: int) -> int:
        retVal = 0

        arrSize = len(arr)

        winRounds = 0
        winIdx = 0
        for nextIdx in range(1, arrSize):  # 2 <= arr.length <= 10^5
            if arr[winIdx] > arr[nextIdx]:
                winRounds += 1
            elif arr[winIdx] < arr[nextIdx]:
                winIdx = nextIdx
                winRounds = 1
            elif arr[winIdx] == arr[nextIdx]:  # arr contains distinct integers.
                pass

            if winRounds == k:
                break

        retVal = arr[winIdx]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for arr, k in zip(
            [
                [2, 1, 3, 5, 4, 6, 7],
                [3, 2, 1],
                [1, 11, 22, 33, 44, 55, 66, 77, 88, 99],
                [1, 25, 35, 42, 68, 70],
            ],
            [2, 10, 1000000000, 1],
        ):
            # /* Example
            #  *  Input: arr = [2,1,3,5,4,6,7], k = 2
            #  *  Output: 5
            #  *
            #  *  Input: arr = [3,2,1], k = 10
            #  *  Output: 3
            #  *
            #  *  Input: arr = [1,11,22,33,44,55,66,77,88,99], k = 1000000000
            #  *  Output: 99
            #  *
            #  *  Input: arr = [1,25,35,42,68,70], k = 1
            #  *  Output: 25
            #  */
            logging.info("Input: arr = %s, k = %s", arr, k)

            retVal = pSolution.getWinner(arr, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
