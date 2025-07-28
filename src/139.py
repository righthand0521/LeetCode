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
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        retVal = False

        sSize = len(s)

        dp = [False] * (sSize+1)
        dp[0] = True
        for i in range(sSize+1):
            for j in range(i):
                if dp[j] == False:
                    continue
                for word in wordDict:
                    if s[j:i] == word:
                        dp[i] = True
                        j = i
                        break
        retVal = dp[sSize]

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, wordDict in zip(
            ["leetcode", "applepenapple", "catsandog"],
            [["leet", "code"], ["apple", "pen"], ["cats", "dog", "sand", "and", "cat"]]
        ):
            # /* Example
            #  *  Input: s = "leetcode", wordDict = ["leet","code"]
            #  *  Output: true
            #  *
            #  *  Input: s = "applepenapple", wordDict = ["apple","pen"]
            #  *  Output: true
            #  *
            #  *  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
            #  *  Output: false
            #  */
            logging.info("Input: s = %s, wordDict = %s", s, wordDict)

            retVal = pSolution.wordBreak(s, wordDict)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
