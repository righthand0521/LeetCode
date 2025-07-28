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
    def countCharacters(self, words: List[str], chars: str) -> int:
        retVal = 0

        # words[i] and chars consist of lowercase English letters.
        charsCount = [0] * 26

        for char in chars:
            idx = ord(char) - ord('a')
            charsCount[idx] += 1

        for word in words:
            check = charsCount.copy()
            count = 0
            for c in word:
                idx = ord(c) - ord('a')
                if check[idx] == 0:
                    break
                check[idx] -= 1
                count += 1

            wordSize = len(word)
            if count == wordSize:
                retVal += count

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, chars in zip([["cat", "bt", "hat", "tree"], ["hello", "world", "leetcode"]],
                                ["atach", "welldonehoneyr"]):
            # /* Example
            #  *  Input: words = ["cat","bt","hat","tree"], chars = "atach"
            #  *  Output: 6
            #  *
            #  *  Input: words = ["hello","world","leetcode"], chars = "welldonehoneyr"
            #  *  Output: 10
            #  */
            logging.info("Input: words = %s, chars = \"%s\"", words, chars)

            retVal = pSolution.countCharacters(words, chars)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
