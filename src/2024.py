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
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:
        retVal = 0

        # answerKey[i] is either 'T' or 'F'
        MAX_RECORD = 26
        Record = [0] * MAX_RECORD

        maxRecord = 0
        answerKeysSize = len(answerKey)
        left = 0
        right = 0
        while right < answerKeysSize:
            idx = ord(answerKey[right]) - ord("A")
            Record[idx] += 1

            maxRecord = max(maxRecord, Record[idx])
            if right - left + 1 - maxRecord > k:
                Record[ord(answerKey[left]) - ord("A")] -= 1
                left += 1

            right += 1

        retVal = right - left

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for answerKey, k in zip(["TTFF", "TFFT", "TTFTTFTT"], [2, 1, 1]):
            # /* Example
            #  *  Input: answerKey = "TTFF", k = 2
            #  *  Output: 4
            #  *
            #  *  Input: answerKey = "TFFT", k = 1
            #  *  Output: 3
            #  *
            #  *  Input: answerKey = "TTFTTFTT", k = 1
            #  *  Output: 5
            #  */
            logging.info("Input: answerKey = \"%s\", k = %s", answerKey, k)

            retVal = pSolution.maxConsecutiveAnswers(answerKey, k)
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
