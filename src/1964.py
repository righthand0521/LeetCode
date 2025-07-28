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
    def __init__(self):
        self.method = 1

        if self.method == 1:
            print("BINARY_SEARCH")
        elif self.method == 2:
            print("DYNAMIC_PROGRAMMING: Time Limit Exceeded")
        print()

    def longestObstacleCourseAtEachPosition(self, obstacles: List[int]) -> List[int]:
        retVal = []

        if self.method == 1:
            greedy = []
            for obstacle in obstacles:
                if not greedy or obstacle >= greedy[-1]:
                    greedy.append(obstacle)
                    retVal.append(len(greedy))
                else:
                    position = bisect_right(greedy, obstacle)
                    retVal.append(position + 1)
                    greedy[position] = obstacle
        elif self.method == 2:
            obstaclesSize = len(obstacles)
            dp = [1] * obstaclesSize
            for i in range(obstaclesSize):
                for j in range(i):
                    if (obstacles[j] <= obstacles[i]):
                        dp[i] = max(dp[i], dp[j] + 1)
            retVal = dp

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for obstacles in [[1, 2, 3, 2], [2, 2, 1], [3, 1, 5, 6, 4, 2]]:
            # /* Example
            #  *  Input: obstacles = [1,2,3,2]
            #  *  Output: [1,2,3,3]
            #  *
            #  *  Input: obstacles = [2,2,1]
            #  *  Output: [1,2,1]
            #  *
            #  *  Input: obstacles = [3,1,5,6,4,2]
            #  *  Output: [1,1,2,3,2,2]
            #  */
            logging.info("Input: obstacles = %s", obstacles)

            retVal = pSolution.longestObstacleCourseAtEachPosition(obstacles)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
