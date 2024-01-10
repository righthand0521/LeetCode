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
    # https://leetcode.cn/problems/tallest-billboard/solutions/368725/yi-quan-ji-ben-mei-shuo-ming-bai-de-zhe-pian-kan-l/
    def tallestBillboard(self, rods: List[int]) -> int:
        retVal = 0

        dp = defaultdict()
        dp[0] = 0
        for rod in rods:
            for key, value in list(dp.items()):
                dp[key + rod] = max(dp.get(key + rod, 0), value + rod)
                dp[key - rod] = max(dp.get(key - rod, 0), value)
        retVal = dp[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rods in [[1, 2, 3, 6], [1, 2, 3, 4, 5, 6], [1, 2]]:
            # /* Example
            #  *  Input: rods = [1,2,3,6]
            #  *  Output: 6
            #  *
            #  *  Input: rods = [1,2,3,4,5,6]
            #  *  Output: 10
            #  *
            #  *  Input: rods = [1,2]
            #  *  Output: 0
            #  */
            logging.info("Input: rods = %s", rods)

            retVal = pSolution.tallestBillboard(rods)
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
