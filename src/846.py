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
    def isNStraightHand(self, hand: List[int], groupSize: int) -> bool:
        retVal = False

        handSize = len(hand)
        if handSize % groupSize > 0:
            return retVal

        hand.sort()

        count = Counter(hand)
        for x in hand:
            if count[x] == 0:
                continue

            for num in range(x, x + groupSize):
                if count[num] == 0:
                    return retVal
                count[num] -= 1
        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for hand, groupSize in zip([[1, 2, 3, 6, 2, 3, 4, 7, 8], [1, 2, 3, 4, 5]], [3, 4]):
            # /* Example
            #  *  Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3
            #  *  Output: true
            #  *
            #  *  Input: hand = [1,2,3,4,5], groupSize = 4
            #  *  Output: false
            #  */
            logging.info("Input: hand = %s, groupSize = %s", hand, groupSize)

            retVal = pSolution.isNStraightHand(hand, groupSize)
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
