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
    def countDays(self, days: int, meetings: List[List[int]]) -> int:
        retVal = 0

        meetings.sort()

        latestEnd = 0
        for start, end in meetings:
            # Add current range of days without a meeting
            if start > latestEnd + 1:
                retVal += start - latestEnd - 1

            # Update latest meeting end
            latestEnd = max(latestEnd, end)

        # Add all days after the last day of meetings
        retVal += days - latestEnd

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for days, meetings in zip([10, 5, 6], [[[5, 7], [1, 3], [9, 10]], [[2, 4], [1, 3]], [[1, 6]]]):
            # /* Example
            #  *  Input: days = 10, meetings = [[5,7],[1,3],[9,10]]
            #  *  Output: 2
            #  *
            #  *  Input: days = 5, meetings = [[2,4],[1,3]]
            #  *  Output: 1
            #  *
            #  *  Input: days = 6, meetings = [[1,6]]
            #  *  Output: 0
            #  */
            logging.info("Input: days = %s, meetings = %s", days, meetings)

            retVal = pSolution.countDays(days, meetings)
            logging.info("Output: %d", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
