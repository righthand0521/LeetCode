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
    def dfs(self, n: int, k: int, node: int, visit: set, answer: list) -> None:
        highest = 10 ** (n - 1)
        for x in range(k):
            neighbor = node * 10 + x
            if neighbor not in visit:
                visit.add(neighbor)
                self.dfs(n, k, neighbor % highest, visit, answer)
                answer.append(str(x))

    def crackSafe(self, n: int, k: int) -> str:
        retVal = ""

        visit = set()
        answer = list()
        self.dfs(n, k, 0, visit, answer)
        retVal = "".join(answer) + "0" * (n - 1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for n, k in zip([1, 2], [2, 2]):
            # /* Example
            #  *  Input: n = 1, k = 2
            #  *  Output: "10"
            #  *
            #  *  Input: n = 2, k = 2
            #  *  Output: "01100"
            #  */
            logging.info("Input: n = %s, k = %s", n, k)

            retVal = pSolution.crackSafe(n, k)
            logging.info("Output: \"%s\"", retVal)

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
