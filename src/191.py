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
    def hammingWeight(self, n: int) -> int:
        return sum(((n & (1 << i)) != 0) for i in range(32))


if __name__ == "__main__":
    logging_setting()

    logging.info("sys.version: %s", sys.version)
    print("")
    try:
        testCase = [Counter(n="00000000000000000000000000001011"),
                    Counter(n="00000000000000000000000010000000"),
                    Counter(n="11111111111111111111111111111101")]
        # /* Example
        #  *  Input: n = 00000000000000000000000000001011
        #  *  Output: 3
        #  *
        #  *  Input: n = 00000000000000000000000010000000
        #  *  Output: 1
        #  *
        #  *  Input: n = 11111111111111111111111111111101
        #  *  Output: 31
        #  */

        pSolution = Solution()
        for i in range(0, len(testCase)):
            print('Input: n = {}'.format(testCase[i]['n']))

            retVal = pSolution.hammingWeight(int(testCase[i]['n'], 2))
            print('Output: {}'.format(retVal))

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
