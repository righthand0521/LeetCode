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
        self.small = -1
        self.large = 1
        self.equal = 0

    def compareVersion(self, version1: str, version2: str) -> int:
        retVal = self.equal

        version1Size = len(version1)
        version2Size = len(version2)

        idx1 = 0
        idx2 = 0
        while (idx1 < version1Size) or (idx2 < version2Size):
            sum1 = 0
            while (idx1 < version1Size) and (version1[idx1] != '.'):
                sum1 = sum1 * 10 + int(version1[idx1])
                idx1 += 1
            idx1 += 1

            sum2 = 0
            while (idx2 < version2Size) and (version2[idx2] != '.'):
                sum2 = sum2 * 10 + int(version2[idx2])
                idx2 += 1
            idx2 += 1

            if sum1 > sum2:
                retVal = self.large
                break
            elif sum1 < sum2:
                retVal = self.small
                break

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for version1, version2 in zip(["1.01", "1.0", "0.1", "1.1"], ["1.001", "1.0.0", "1.1", "1.10"]):
            # /* Example
            #  *  Input: version1 = "1.01", version2 = "1.001"
            #  *  Output: 0
            #  *
            #  *  Input: version1 = "1.0", version2 = "1.0.0"
            #  *  Output: 0
            #  *
            #  *  Input: version1 = "0.1", version2 = "1.1"
            #  *  Output: -1
            #  *
            #  *  Input: version1 = "1.1", version2 = "1.10"
            #  *  Output: -1
            #  */
            logging.info(
                "Input: version1 = \"%s\", version2 = \"%s\"", version1, version2)

            retVal = pSolution.compareVersion(version1, version2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
