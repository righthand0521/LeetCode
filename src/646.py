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
    def __init__(self) -> None:
        self.method = 1

        if self.method == 1:
            print("Greedy")
        elif self.method == 2:
            print("Dynamic Programming")
        print()

    def findLongestChain(self, pairs: List[List[int]]) -> int:
        retVal = 0

        if self.method == 1:
            pairs.sort(key=lambda right: right[1])

            preRight = -1001    # -1000 <= lefti < righti <= 1000
            for left, right in pairs:
                if left > preRight:
                    retVal += 1
                    preRight = right
        elif self.method == 2:
            pairs.sort()

            # dp[i] will store the length of the longest chain starting from pair i
            pairsSize = len(pairs)
            dp = [1] * pairsSize
            for i in range(pairsSize - 1, -1, -1):
                preRight = pairs[i][1]
                for j in range(i + 1, pairsSize):
                    left = pairs[j][0]
                    if preRight < left:
                        dp[i] = max(dp[i], dp[j] + 1)
                retVal = max(retVal, dp[i])

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for pairs in [
            [[1, 2], [2, 3], [3, 4]],
            [[1, 2], [7, 8], [4, 5]],
            [[1, 2], [2, 5], [3, 9], [6, 7], [8, 9]],
            [[7, 9], [4, 5], [7, 9], [-7, -1], [0, 10], [3, 10], [3, 6], [2, 3]]
        ]:
            # /* Example
            # *  Input: pairs = [[1, 2], [2, 3], [3, 4]]
            # *  Output: 2
            # *
            # *  Input: pairs = [[1, 2], [7, 8], [4, 5]]
            # *  Output: 3
            # *
            # *  Input: pairs = [[1,2],[2,5],[3,9],[6,7],[8,9]]
            # *  Output: 3
            # *
            # *  Input: pairs = [[7,9],[4,5],[7,9],[-7,-1],[0,10],[3,10],[3,6],[2,3]]
            # *  Output: 4
            # */
            logging.info("Input: pairs = %s", pairs)

            retVal = pSolution.findLongestChain(pairs)
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
