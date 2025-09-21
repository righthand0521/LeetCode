import logging
import sys
from bisect import bisect_left, bisect_right
from collections import Counter, defaultdict, deque
from functools import cache, lru_cache
from heapq import heapify, heappop, heappush
from itertools import accumulate
from typing import List, Optional

from sortedcontainers import SortedList


def logging_setting():
    LOG_LEVEL = logging.INFO    # DEBUG, INFO, WARNING, ERROR, CRITICAL
    if __debug__:
        LOG_LEVEL = logging.DEBUG

    logging.basicConfig(
        stream=sys.stderr,
        level=LOG_LEVEL,
        format="%(levelname)-6s %(asctime)s %(module)s:%(funcName)s:%(lineno)-4s %(message)s",
        datefmt='%Y/%m/%d %H:%M:%S')


class MovieRentingSystem:
    def __init__(self, n: int, entries: List[List[int]]):
        self.t_price = dict()
        self.t_valid = defaultdict(SortedList)
        self.t_rent = SortedList()
        for shop, movie, price in entries:
            self.t_price[(shop, movie)] = price
            self.t_valid[movie].add((price, shop))

    def search(self, movie: int) -> List[int]:
        retVal = []

        t_valid_ = self.t_valid
        if movie not in t_valid_:
            return retVal
        retVal = [shop for (price, shop) in t_valid_[movie][:5]]

        return retVal

    def rent(self, shop: int, movie: int) -> None:
        price = self.t_price[(shop, movie)]
        self.t_valid[movie].discard((price, shop))
        self.t_rent.add((price, shop, movie))

    def drop(self, shop: int, movie: int) -> None:
        price = self.t_price[(shop, movie)]
        self.t_valid[movie].add((price, shop))
        self.t_rent.discard((price, shop, movie))

    def report(self) -> List[List[int]]:
        retVal = [(shop, movie) for price, shop, movie in self.t_rent[:5]]

        return retVal

# Your MovieRentingSystem object will be instantiated and called as such:
# obj = MovieRentingSystem(n, entries)
# param_1 = obj.search(movie)
# obj.rent(shop,movie)
# obj.drop(shop,movie)
# param_4 = obj.report()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        for methods, val in zip(
            [["MovieRentingSystem", "search", "rent", "rent", "report", "drop", "search"]],
            [[
                [3, [[0, 1, 5], [0, 2, 6], [0, 3, 7], [1, 1, 4], [1, 2, 7], [2, 1, 5]]],
                [1],
                [0, 1],
                [1, 2],
                [],
                [1, 2],
                [2]
            ]]
        ):
            # /* Example
            #  *  Input
            #  *  ["MovieRentingSystem", "search", "rent", "rent", "report", "drop", "search"]
            #  *  [[3, [[0, 1, 5], [0, 2, 6], [0, 3, 7], [1, 1, 4], [1, 2, 7], [2, 1, 5]]], [1], [0, 1], [1, 2], [], [1, 2], [2]]
            #  *  Output
            #  *  [null, [1, 0, 2], null, null, [[0, 1], [1, 2]], null, [0, 1]]
            #  */
            logging.info("Input:")
            logging.info("%s", methods)
            logging.info("%s", val)

            displayStr = []
            for key, value in zip(methods, val):
                if key == "MovieRentingSystem":
                    obj = MovieRentingSystem(value[0], value[1])
                    displayStr.append(None)
                elif key == "search":
                    retVal = obj.search(value[0])
                    displayStr.append(retVal)
                elif key == "rent":
                    obj.rent(value[0], value[1])
                    displayStr.append(None)
                elif key == "report":
                    retVal = obj.report()
                    displayStr.append(retVal)
                elif key == "drop":
                    obj.drop(value[0], value[1])
                    displayStr.append(None)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

        print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__, exception, exc_info=True)
        pass

        sys.exit(0)
