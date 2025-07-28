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
    def orderlyQueue(self, s: str, k: int) -> str:
        if k == 1:
            return min(s[i:] + s[:i] for i in range(len(s)))
        else:
            return ''.join(sorted(s))


if __name__ == "__main__":
    logging_setting()

    logging.info("sys.version: %s", sys.version)
    print("")
    try:
        testCase = [
            Counter(s="cba", k=1), Counter(s="baaca", k=3)
        ]

        pSolution = Solution()
        for i in range(0, len(testCase)):
            print('Input: s = "{}", k = {}'.format(
                testCase[i]['s'], testCase[i]['k']))

            retVal = pSolution.orderlyQueue(testCase[i]['s'], testCase[i]['k'])
            print('Output: {}'.format(retVal))

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
