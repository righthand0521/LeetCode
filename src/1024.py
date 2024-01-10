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
    def videoStitching(self, clips: List[List[int]], time: int) -> int:
        retVal = -1

        record = [0] * time
        for start, end in clips:
            if start < time:
                record[start] = max(record[start], end)

        retVal = 0
        lastEnd = 0
        previousEnd = 0
        for i in range(time):
            lastEnd = max(lastEnd, record[i])
            if i == lastEnd:
                retVal = -1
                break
            elif i == previousEnd:
                retVal += 1
                previousEnd = lastEnd

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for clips, time in zip(
            [[[0, 2], [4, 6], [8, 10], [1, 9], [1, 5], [5, 9]],
             [[0, 1], [1, 2]],
             [[0, 1], [6, 8], [0, 2], [5, 6], [0, 4], [0, 3], [6, 7], [1, 3], [4, 7], [1, 4], [2, 5], [2, 6], [3, 4], [4, 5], [5, 7], [6, 9]]],
                [10, 5, 9]):
            # /* Example
            #  *  Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
            #  *  Output: 3
            #  *
            #  *  Input: clips = [[0,1],[1,2]], time = 5
            #  *  Output: -1
            #  *
            #  *  Input: clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], time = 9
            #  *  Output: 3
            #  */
            logging.info("Input: clips = %s, time = %s", clips, time)

            retVal = pSolution.videoStitching(clips, time)
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
