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
    def minOperations(self, boxes: str) -> List[int]:
        retVal = []

        boxesSize = len(boxes)
        retVal = [0] * boxesSize

        ballsToLeft = 0
        movesToLeft = 0
        ballsToRight = 0
        movesToRight = 0
        for i in range(boxesSize):
            # Left pass
            retVal[i] += movesToLeft
            ballsToLeft += int(boxes[i])
            movesToLeft += ballsToLeft

            # Right pass
            j = boxesSize - 1 - i
            retVal[j] += movesToRight
            ballsToRight += int(boxes[j])
            movesToRight += ballsToRight

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for boxes in ["110", "001011"]:
            # /* Example
            #  *  Input: boxes = "110"
            #  *  Output: [1,1,3]
            #  *
            #  *  Input: boxes = "001011"
            #  *  Output: [11,8,5,4,3,4]
            #  */
            logging.info("Input: boxes = \"%s\"", boxes)

            retVal = pSolution.minOperations(boxes)
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
