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
    def __init__(self) -> None:
        self.letter = 26

    def count(self, word) -> List[int]:
        retVal = []

        retVal = [0] * self.letter
        for letter in word:
            retVal[ord(letter) - ord('a')] += 1

        return retVal

    def wordSubsets(self, words1: List[str], words2: List[str]) -> List[str]:
        retVal = []

        bmax = [0] * self.letter
        for word in words2:
            for i, c in enumerate(self.count(word)):
                bmax[i] = max(bmax[i], c)

        for word in words1:
            flag = True
            for x, y in zip(self.count(word), bmax):
                if x < y:
                    flag = False
                    break
            if flag == True:
                retVal.append(word)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words1, words2 in [
            [["amazon", "apple", "facebook", "google", "leetcode"], ["e", "o"]],
            [["amazon", "apple", "facebook", "google", "leetcode"], ["l", "e"]]
        ]:
            # /* Example
            #  *  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
            #  *  Output: ["facebook","google","leetcode"]
            #  *
            #  *  Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
            #  *  Output: ["apple","google","leetcode"]
            #  */
            logging.info("Input: words1 = %s, words2 = %s", words1, words2)

            retVal = pSolution.wordSubsets(words1, words2)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
    sys.exit(0)
