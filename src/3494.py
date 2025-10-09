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
    def minTime(self, skill: List[int], mana: List[int]) -> int:
        retVal = 0

        skillSize = len(skill)
        manaSize = len(mana)

        times = [0] * skillSize
        for j in range(manaSize):
            currentTime = 0
            for i in range(skillSize):
                currentTime = max(currentTime, times[i]) + skill[i] * mana[j]
            times[skillSize - 1] = currentTime
            for i in range(skillSize - 2, -1, -1):
                times[i] = times[i + 1] - skill[i + 1] * mana[j]
        retVal = times[skillSize - 1]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for skill, mana in [[[1, 5, 2, 4], [5, 1, 4, 2]], [[1, 1, 1], [1, 1, 1]], [[1, 2, 3, 4], [1, 2]]]:
            # /* Example
            #  *  Input: skill = [1,5,2,4], mana = [5,1,4,2]
            #  *  Output: 110
            #  *
            #  *  Input: skill = [1,1,1], mana = [1,1,1]
            #  *  Output: 5
            #  *
            #  *  Input: skill = [1,2,3,4], mana = [1,2]
            #  *  Output: 21
            #  */
            logging.info("Input: skill = %s, mana = %s", skill, mana)

            retVal = pSolution.minTime(skill, mana)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
