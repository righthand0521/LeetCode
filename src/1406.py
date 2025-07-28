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
    def stoneGameIII(self, stoneValue: List[int]) -> str:
        retVal = "Tie"

        stoneValueSize = len(stoneValue)
        dp = [0] * (stoneValueSize + 1)
        for i in range(stoneValueSize - 1, -1, -1):
            dp[i] = stoneValue[i] - dp[i + 1]
            if i + 2 <= stoneValueSize:
                dp[i] = max(dp[i], stoneValue[i] +
                            stoneValue[i + 1] - dp[i + 2])
            if i + 3 <= stoneValueSize:
                dp[i] = max(dp[i], stoneValue[i] + stoneValue[i +
                            1] + stoneValue[i + 2] - dp[i + 3])

        if dp[0] > 0:
            retVal = "Alice"
        elif dp[0] < 0:
            retVal = "Bob"

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for values in [[1, 2, 3, 7], [1, 2, 3, -9], [1, 2, 3, 6]]:
            # /* Example
            #  *  Input: values = [1,2,3,7]
            #  *  Output: "Bob"
            #  *
            #  *  Input: values = [1,2,3,-9]
            #  *  Output: "Alice"
            #  *
            #  *  Input: values = [1,2,3,6]
            #  *  Output: "Tie"
            #  */
            logging.info("Input: values = %s", values)

            retVal = pSolution.stoneGameIII(values)
            logging.info("Output: \"%s\"", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
