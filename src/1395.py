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
    def numTeams(self, rating: List[int]) -> int:
        retVal = 0

        ratingSize = len(rating)
        for middle in range(ratingSize):
            # Count soldiers with smaller ratings on the left side of the current soldier
            leftSmaller = 0
            for left in range(middle - 1, -1, -1):
                if rating[left] < rating[middle]:
                    leftSmaller += 1

            # Count soldiers with larger ratings on the right side of the current soldier
            rightLarger = 0
            for right in range(middle + 1, ratingSize):
                if rating[right] > rating[middle]:
                    rightLarger += 1

            # Calculate and add the number of ascending rating teams (small-middle-large)
            retVal += (leftSmaller * rightLarger)

            # Calculate soldiers with larger ratings on the left and smaller ratings on the right
            leftLarger = middle - leftSmaller
            rightSmaller = ratingSize - middle - 1 - rightLarger

            # Calculate and add the number of descending rating teams (large-middle-small)
            retVal += (leftLarger * rightSmaller)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for rating in [[2, 5, 3, 4, 1], [2, 1, 3], [1, 2, 3, 4]]:
            # /* Example
            #  *  Input: rating = [2,5,3,4,1]
            #  *  Output: 3
            #  *
            #  *  Input: rating = [2,1,3]
            #  *  Output: 0
            #  *
            #  *  Input: rating = [1,2,3,4]
            #  *  Output: 4
            #  */
            logging.info("Input: rating = %s", rating)

            retVal = pSolution.numTeams(rating)
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
