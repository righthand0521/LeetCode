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
    def __init__(self) -> None:
        self.strPush = "Push"
        self.strPop = "Pop"

    def buildArray(self, target: List[int], n: int) -> List[str]:
        retVal = []

        targetSize = len(target)
        targetIndex = 0
        for i in range(1, n + 1):
            if targetIndex >= targetSize:
                break

            if i == target[targetIndex]:
                retVal.append(self.strPush)
                targetIndex += 1
            else:
                retVal.append(self.strPush)
                retVal.append(self.strPop)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for target, n in zip([[1, 3], [1, 2, 3], [1, 2]], [3, 3, 4]):
            # /* Example
            #  *  Input: target = [1,3], n = 3
            #  *  Output: ["Push","Push","Pop","Push"]
            #  *
            #  *  Input: target = [1,2,3], n = 3
            #  *  Output: ["Push","Push","Push"]
            #  *
            #  *  Input: target = [1,2], n = 4
            #  *  Output: ["Push","Push"]
            #  */
            logging.info("Input: target = %s, n = %s", target, n)

            retVal = pSolution.buildArray(target, n)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
