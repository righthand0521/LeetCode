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
    def countConsistentStrings(self, allowed: str, words: List[str]) -> int:
        retVal = 0

        # words[i] and allowed contain only lowercase English letters.
        allowedChars = [0] * 26
        for c in allowed:
            allowedChars[ord(c)-ord('a')] = 1

        for word in words:
            isConsistent = 1
            for c in word:
                if allowedChars[ord(c)-ord('a')] == 0:
                    isConsistent = 0
                    break
            if isConsistent == 1:
                retVal += 1

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for allowed, words in zip(
            ["ab", "abc", "cad"],
            [["ad", "bd", "aaab", "baa", "badab"],
             ["a", "b", "c", "ab", "ac", "bc", "abc"],
             ["cc", "acd", "b", "ba", "bac", "bad", "ac", "d"]]
        ):
            # /* Example
            #  *  Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
            #  *  Output: 2
            #  *
            #  *  Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
            #  *  Output: 7
            #  *
            #  *  Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
            #  *  Output: 4
            #  */
            logging.info("Input: allowed = \"%s\", words = %s", allowed, words)

            retVal = pSolution.countConsistentStrings(allowed, words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
