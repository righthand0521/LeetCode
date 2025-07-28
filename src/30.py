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
        datefmt='%Y/%wordsSize/%d %H:%M:%S')


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        retVal = []

        wordsSize = len(words)
        wordLength = len(words[0])
        sLength = len(s)

        for i in range(wordLength):
            if i + wordsSize * wordLength > sLength:
                break

            differ = Counter()
            for j in range(wordsSize):
                word = s[i + j * wordLength: i + (j + 1) * wordLength]
                differ[word] += 1

            for word in words:
                differ[word] -= 1
                if differ[word] == 0:
                    del differ[word]

            for start in range(i, sLength - wordsSize * wordLength + 1, wordLength):
                if start != i:
                    wordLeft = start + (wordsSize - 1) * wordLength
                    wordRight = start + wordsSize * wordLength
                    word = s[wordLeft:wordRight]

                    differ[word] += 1
                    if differ[word] == 0:
                        del differ[word]

                    word = s[start - wordLength: start]

                    differ[word] -= 1
                    if differ[word] == 0:
                        del differ[word]

                differSize = len(differ)
                if differSize == 0:
                    retVal.append(start)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for s, words in [
            ["barfoothefoobarman", ["foo", "bar"]],
            ["wordgoodgoodgoodbestword", ["word", "good", "best", "word"]],
            ["barfoofoobarthefoobarman", ["bar", "foo", "the"]]
        ]:
            # /* Example
            #  *  Input: s = "barfoothefoobarman", words = ["foo","bar"]
            #  *  Output: [0,9]
            #  *
            #  *  Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
            #  *  Output: []
            #  *
            #  *  Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
            #  *  Output: [6,9,12]
            #  */
            logging.info("Input: s = %s, words = %s", s, words)

            retVal = pSolution.findSubstring(s, words)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
