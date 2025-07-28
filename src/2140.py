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
    def mostPoints(self, questions: List[List[int]]) -> int:
        retVal = 0

        questionsSize = len(questions)
        dp = [0] * questionsSize
        dp[-1] = questions[-1][0]
        for i in range(questionsSize-2, -1, -1):
            dp[i] = questions[i][0]
            skip = questions[i][1]
            if i + skip + 1 < questionsSize:
                dp[i] += dp[i + skip + 1]
            dp[i] = max(dp[i], dp[i + 1])
        retVal = dp[0]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for questions in [[[3, 2], [4, 3], [4, 4], [2, 5]], [[1, 1], [2, 2], [3, 3], [4, 4], [5, 5]]]:
            # /* Example
            #  *  Input: questions = [[3,2],[4,3],[4,4],[2,5]]
            #  *  Output: 5
            #  *
            #  *  Input: questions = [[1,1],[2,2],[3,3],[4,4],[5,5]]
            #  *  Output: 7
            #  */
            logging.info("Input: questions = %s", questions)

            retVal = pSolution.mostPoints(questions)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
