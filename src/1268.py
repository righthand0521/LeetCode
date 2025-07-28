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


class Trie:
    def __init__(self):
        self.child = dict()
        self.words = list()


class Solution:
    def addWord(self, root, product) -> None:
        pCurrent = root
        for c in product:
            if c not in pCurrent.child:
                pCurrent.child[c] = Trie()
            pCurrent = pCurrent.child[c]
            pCurrent.words.append(product)
            pCurrent.words.sort()
            if len(pCurrent.words) > 3:
                pCurrent.words.pop()

    def suggestedProducts(self, products: List[str], searchWord: str) -> List[List[str]]:
        retVal = []

        #
        root = Trie()
        for product in products:
            self.addWord(root, product)

        #
        pCurrent = root
        flag = False
        for c in searchWord:
            if flag or c not in pCurrent.child:
                retVal.append(list())
                flag = True
            else:
                pCurrent = pCurrent.child[c]
                retVal.append(pCurrent.words)

        return retVal


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        pSolution = Solution()
        for products, searchWord in zip([["mobile", "mouse", "moneypot", "monitor", "mousepad"], ["havana"]],
                                        ["mouse", "havana"]):
            # /* Example
            #  *  Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
            #  *  Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],
            #  *  ["mouse","mousepad"],["mouse","mousepad"]]
            #  *
            #  *  Input: products = ["havana"], searchWord = "havana"
            #  *  Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
            #  */
            logging.info("Input: products = %s, searchWord = '%s'", products, searchWord)

            retVal = pSolution.suggestedProducts(products, searchWord)
            logging.info("Output: %s", retVal)

            print()
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

    sys.exit(0)
