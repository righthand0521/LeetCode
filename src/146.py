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


class DoublyLinkedNode:
    def __init__(self, key=0, value=0):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None


class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = defaultdict()
        self.size = 0

        self.head = DoublyLinkedNode()
        self.tail = DoublyLinkedNode()
        self.head.next = self.tail
        self.tail.prev = self.head

    def addToHead(self, node):
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node

    def removeNode(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev

    def moveToHead(self, node):
        self.removeNode(node)
        self.addToHead(node)

    def removeTail(self):
        node = self.tail.prev
        self.removeNode(node)
        return node

    def get(self, key: int) -> int:
        retVal = -1

        if key not in self.cache:
            return retVal

        node = self.cache[key]
        self.moveToHead(node)
        retVal = node.value

        return retVal

    def put(self, key: int, value: int) -> None:
        if key not in self.cache:
            node = DoublyLinkedNode(key, value)
            self.cache[key] = node
            self.addToHead(node)
            self.size += 1
            if self.size > self.capacity:
                removed = self.removeTail()
                self.cache.pop(removed.key)
                self.size -= 1
        else:
            node = self.cache[key]
            node.value = value
            self.moveToHead(node)

# Your LRUCache object will be instantiated and called as such:
# obj = LRUCache(capacity)
# param_1 = obj.get(key)
# obj.put(key,value)


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in zip([
            ["LRUCache", "put", "put", "get", "put",
                "get", "put", "get", "get", "get"],
            ["LRUCache", "put", "put", "get", "put", "put", "get"]
        ], [
            [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]],
            [[2], [2, 1], [2, 2], [2], [1, 1], [4, 1], [2]]
        ]):
            # /* Example
            #  *  Input
            #  *  ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
            #  *  [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
            #  *  Output
            #  *  [null, null, null, 1, null, -1, null, -1, 3, 4]
            #  *
            #  *  Input
            #  *  ["LRUCache", "put", "put", "get", "put", "put", "get"]
            #  *  [[2], [2,1], [2,2], [2], [1,1], [4,1], [2]]
            #  *  Output
            #  *  [null, null, null, 2, null, null, -1]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "LRUCache":
                    obj = LRUCache(value[0])
                    displayStr.append(None)
                elif key == "get":
                    retVal = obj.get(value[0])
                    displayStr.append(retVal)
                elif key == "put":
                    obj.put(value[0], value[1])
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

    sys.exit(0)
