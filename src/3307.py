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
    def kthCharacter(self, k: int, operations: List[int]) -> str:
        retVal = ""

        ans = 0
        k -= 1
        for i in range(k.bit_length() - 1, -1, -1):
            if (k >> i) & 1:
                ans += operations[i]
        retVal = chr(ord("a") + (ans % 26))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for k, operations in [[5, [0, 0, 0]], [10, [0, 1, 0, 1]]]:
            # /* Example
            #  *  Input: k = 5, operations = [0,0,0]
            #  *  Output: "a"
            #  *
            #  *  Input: k = 10, operations = [0,1,0,1]
            #  *  Output: "b"
            #  */
            logging.info("Input: k = %s, operations = %s", k, operations)

            retVal = pSolution.kthCharacter(k, operations)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
