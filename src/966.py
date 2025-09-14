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
    def devowel(self, word: str) -> str:
        retVal = ""

        vowels = set('aeiou')
        for ch in word.lower():
            if ch in vowels:
                retVal += "*"
            else:
                retVal += ch

        return retVal

    def spellchecker(self, wordlist: List[str], queries: List[str]) -> List[str]:
        retVal = []

        exact_set = set(wordlist)
        case_map = {}
        vowel_map = {}
        for word in wordlist:
            lower = word.lower()
            case_map.setdefault(lower, word)
            vowel_map.setdefault(self.devowel(word), word)

        for q in queries:
            if q in exact_set:
                retVal.append(q)
            elif q.lower() in case_map:
                retVal.append(case_map[q.lower()])
            elif self.devowel(q) in vowel_map:
                retVal.append(vowel_map[self.devowel(q)])
            else:
                retVal.append("")

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for wordlist, queries in [
                [
                    ["KiTe", "kite", "hare", "Hare"],
                    ["kite", "Kite", "KiTe", "Hare", "HARE", "Hear", "hear", "keti", "keet", "keto"]
                ],
                [
                    ["yellow"],
                    ["YellOw"]
                ]
        ]:
            # /* Example
            #  *  Input: wordlist = ["KiTe","kite","hare","Hare"],
            #  *  queries = ["kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"]
            #  *  Output: ["kite","KiTe","KiTe","Hare","hare","","","KiTe","","KiTe"]
            #  *
            #  *  Input: wordlist = ["yellow"], queries = ["YellOw"]
            #  *  Output: ["yellow"]
            #  */
            logging.info("Input: wordlist = %s, queries = %s", wordlist, queries)

            retVal = pSolution.spellchecker(wordlist, queries)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
