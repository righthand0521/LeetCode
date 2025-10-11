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
    def maximumTotalDamage(self, power: List[int]) -> int:
        retVal = 0

        count = Counter(power)

        vec = [(-(10**9), 0)]
        for k in sorted(count.keys()):
            vec.append((k, count[k]))
        n = len(vec)

        f = [0] * n
        mx = 0
        j = 1
        for i in range(1, n):
            while (j < i) and (vec[j][0] < vec[i][0] - 2):
                mx = max(mx, f[j])
                j += 1
            f[i] = mx + vec[i][0] * vec[i][1]
        retVal = max(f)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for power in [[1, 1, 3, 4], [7, 1, 6, 6]]:
            # /* Example
            #  *  Input: power = [1,1,3,4]
            #  *  Output: 6
            #  *
            #  *  Input: power = [7,1,6,6]
            #  *  Output: 13
            #  */
            logging.info("Input: power = %s", power)

            retVal = pSolution.maximumTotalDamage(power)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
