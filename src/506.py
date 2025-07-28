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
    def findRelativeRanks(self, score: List[int]) -> List[str]:
        retVal = []

        sortScore = sorted(enumerate(score), key=lambda x: x[1], reverse=True)

        scoreSize = len(score)
        retVal = [""] * scoreSize
        for i in range(scoreSize):
            if i == 0:
                retVal[sortScore[i][0]] = "Gold Medal"
            elif i == 1:
                retVal[sortScore[i][0]] = "Silver Medal"
            elif i == 2:
                retVal[sortScore[i][0]] = "Bronze Medal"
            else:
                retVal[sortScore[i][0]] = str(i+1)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for score in [[5, 4, 3, 2, 1], [10, 3, 8, 9, 4]]:
            # /* Example
            #  *  Input: score = [5,4,3,2,1]
            #  *  Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
            #  *
            #  *  Input: score = [10,3,8,9,4]
            #  *  Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
            #  */
            logging.info("Input: score = %s", score)

            retVal = pSolution.findRelativeRanks(score)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
