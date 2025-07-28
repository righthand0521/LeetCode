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
    # https://leetcode.com/problems/put-marbles-in-bags/solutions/3111736/java-c-python-3-approachs-best-o-n/
    # https://leetcode.cn/problems/put-marbles-in-bags/solutions/2080577/by-wan-shi-liang-de-mang-fu-mwjh/
    def putMarbles(self, weights: List[int], k: int) -> int:
        retVal = 0

        # /* Example: weights = [1,3,5,1], k = 2. Return the difference between the maximum and minimum scores.
        #  *  [1] [3,5,1]: (1+1) + (3+1) = 6  ->  6 - (1+1) = 4
        #  *  [1,3] [5,1]: (1+3) + (5+1) = 10 -> 10 - (1+1) = 8
        #  *  [1,3 5] [1]: (1+5) + (1+1) = 8  ->  8 - (1+1) = 6
        #  *
        #  *  [1,3,5,1] => [(1+3),(3+5),(5+1)] = [4,8,6]
        #  *
        #  *  1. 對weights進行兩兩求和得到map
        #  *  2. map中挑k-1個值，並累和得到sum
        #  *  3. 求出sum的最大值和最小值並做差
        #  */
        weightsSize = len(weights)
        map = []
        for i in range(1, weightsSize):
            map.append(weights[i] + weights[i - 1])
        map.sort()
        mapSize = len(map)

        minimumScores = 0
        maximumScores = 0
        for i in range(k - 1):
            minimumScores += map[i]
            maximumScores += map[mapSize - 1 - i]
        retVal = maximumScores - minimumScores

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for weights, k in zip([[1, 3, 5, 1], [1, 3], [11]], [2, 2, 1]):
            # /* Example
            #  *  Input: weights = [1,3,5,1], k = 2
            #  *  Output: 4
            #  *
            #  *  Input: weights = [1, 3], k = 2
            #  *  Output: 0
            #  *
            #  *  Input: weights = [11], k = 1
            #  *  Output: 0
            #  */
            logging.info("Input: weights = %s, k = %s", weights, k)

            retVal = pSolution.putMarbles(weights, k)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
