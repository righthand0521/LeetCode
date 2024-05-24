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
        self.max_score = 0
        # words[i], letters[i] contains only lower case English letters.
        self.letters = 26
        self.asciiBase = 97

    # Check if adding this word exceeds the frequency of any letter
    def is_valid_word(self, freq: List[int], subset_letters: List[int]) -> bool:
        retVal = True

        for c in range(self.letters):
            if freq[c] < subset_letters[c]:
                retVal = False
                break

        return retVal

    def check(self, w: int, words: List[str], score, freq: List[int], subset_letters: List[int], total_score: int) -> None:
        # If all words have been iterated, check the score of this subset
        if w == -1:
            self.max_score = max(self.max_score, total_score)
            return

        # Not adding words[w] to the current subset
        self.check(w - 1, words, score, freq, subset_letters, total_score)

        # Adding words[w] to the current subset
        L = len(words[w])
        for i in range(L):
            c = ord(words[w][i]) - self.asciiBase
            subset_letters[c] += 1
            total_score += score[c]

        # Consider the next word if this subset is still valid
        if self.is_valid_word(freq, subset_letters):
            self.check(w - 1, words, score, freq, subset_letters, total_score)

        # Rollback effects of this word
        for i in range(L):
            c = ord(words[w][i]) - self.asciiBase
            subset_letters[c] -= 1
            total_score -= score[c]

    def maxScoreWords(self, words: List[str], letters: List[str], score: List[int]) -> int:
        retVal = 0

        self.max_score = 0  # Count how many times each letter occurs

        wordsSize = len(words)
        freq = [0 for i in range(self.letters)]
        for c in letters:
            freq[ord(c) - self.asciiBase] += 1
        subset_letters = [0 for i in range(self.letters)]

        self.check(wordsSize - 1, words, score, freq, subset_letters, 0)
        retVal = self.max_score  # Return max_score as the result

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for words, letters, score in zip(
            [
                ["dog", "cat", "dad", "good"],
                ["xxxz", "ax", "bx", "cx"],
                ["leetcode"]
            ],
            [
                ["a", "a", "c", "d", "d", "d", "g", "o", "o"],
                ["z", "a", "b", "c", "x", "x", "x"],
                ["l", "e", "t", "c", "o", "d"]
            ],
            [
                [1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
                 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                [4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 10],
                [0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0,
                 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
            ]
        ):
            # /* Example
            #  *  Input: words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"],
            #  *  score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
            #  *  Output: 23
            #  *
            #  *  Input: words = ["xxxz","ax","bx","cx"], letters = ["z","a","b","c","x","x","x"],
            #  *  score = [4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,10]
            #  *  Output: 27
            #  *
            #  *  Input: words = ["leetcode"], letters = ["l","e","t","c","o","d"],
            #  *  score = [0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0]
            #  *  Output: 0
            #  */
            logging.info("Input: words = %s, letters = %s, score = %s",
                         words, letters, score)

            retVal = pSolution.maxScoreWords(words, letters, score)
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
