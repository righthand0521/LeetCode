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
    def backtrack(self, s: str, word_set: set, current_sentence: List[str], results: List[str], start_index: int) -> None:
        # If we've reached the end of the string, add the current sentence to results
        if start_index == len(s):
            results.append(" ".join(current_sentence))
            return

        # Iterate over possible end indices
        for end_index in range(start_index + 1, len(s) + 1):
            word = s[start_index:end_index]
            # If the word is in the set, proceed with backtracking
            if word in word_set:
                current_sentence.append(word)
                # Recursively call backtrack with the new end index
                self.backtrack(s, word_set, current_sentence, results, end_index)
                # Remove the last word to backtrack
                current_sentence.pop()

    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        retVal = []

        # Convert wordDict to a set for O(1) lookups
        word_set = set(wordDict)

        # Start the backtracking process
        self.backtrack(s, word_set, [], retVal, 0)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, wordDict in zip(["catsanddog", "pineapplepenapple", "catsandog"],
                               [["cat", "cats", "and", "sand", "dog"],
                                ["apple", "pen", "applepen", "pine", "pineapple"],
                                ["cats", "dog", "sand", "and", "cat"]]):
            # /* Example
            #  *  Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
            #  *  Output: ["cats and dog","cat sand dog"]
            #  *
            #  *  Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
            #  *  Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
            #  *
            #  *  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
            #  *  Output: []
            #  */
            logging.info("Input: s = \"%s\", wordDict = %s", s, wordDict)

            retVal = pSolution.wordBreak(s, wordDict)
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
