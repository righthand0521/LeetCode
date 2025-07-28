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
    def isCircularSentence(self, sentence: str) -> bool:
        retVal = False

        sentenceSize = len(sentence)

        if sentence[0] != sentence[sentenceSize-1]:
            return retVal

        # A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
        for i in range(sentenceSize):
            if (sentence[i] == ' ') and (sentence[i-1] != sentence[i+1]):
                return retVal

        retVal = True

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for sentence in ["leetcode exercises sound delightful", "eetcode", "Leetcode is cool"]:
            # /* Example
            #  *  Input: sentence = "leetcode exercises sound delightful"
            #  *  Output: true
            #  *
            #  *  Input: sentence = "eetcode"
            #  *  Output: true
            #  *
            #  *  Input: sentence = "Leetcode is cool"
            #  *  Output: false
            #  */
            logging.info("Input: sentence = \"%s\"", sentence)

            retVal = pSolution.isCircularSentence(sentence)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
