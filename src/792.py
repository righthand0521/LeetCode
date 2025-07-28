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
    def numMatchingSubseq(self, s: str, words: List[str]) -> int:
        retVal = 0

        record = defaultdict(list)
        for wordsIndex, word in enumerate(words):
            record[word[0]].append((wordsIndex, 0))

        for c in s:
            entry = record[c]
            record[c] = []

            for wordsIndex, idx in entry:
                idx += 1
                if idx == len(words[wordsIndex]):
                    retVal += 1
                else:
                    record[words[wordsIndex][idx]].append((wordsIndex, idx))

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, words in zip(["abcde", "dsahjpjauf"],
                            [["a", "bb", "acd", "ace"], ["ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"]]):
            # /* Example
            #  *  Input: s = "abcde", words = ["a","bb","acd","ace"]
            #  *  Output: 3
            #  *
            #  *  Input: s = "dsahjpjauf", words = ["ahjpjau","ja","ahbwzgqnuk","tnmlanowax"]
            #  *  Output: 2
            #  */
            logging.info("Input: s = \"%s\", words = %s", s, words)

            retVal = pSolution.numMatchingSubseq(s, words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
