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


class Node:
    def __init__(self, freq):
        self.freq = freq
        self.prev = None
        self.next = None
        self.keys = set()


class AllOne:
    def __init__(self):
        self.head = Node(0)  # Dummy head
        self.tail = Node(0)  # Dummy tail
        self.head.next = self.tail  # Link dummy head to dummy tail
        self.tail.prev = self.head  # Link dummy tail to dummy head
        self.map = {}  # Mapping from key to its node

    def removeNode(self, node):
        prevNode = node.prev
        nextNode = node.next

        prevNode.next = nextNode  # Link previous node to next node
        nextNode.prev = prevNode  # Link next node to previous node

    def inc(self, key: str) -> None:
        if key in self.map:
            node = self.map[key]
            freq = node.freq
            node.keys.remove(key)  # Remove key from current node

            nextNode = node.next
            if (nextNode == self.tail) or (nextNode.freq != freq + 1):
                # Create a new node if next node does not exist or freq is not freq + 1
                newNode = Node(freq + 1)
                newNode.keys.add(key)
                newNode.prev = node
                newNode.next = nextNode
                node.next = newNode
                nextNode.prev = newNode
                self.map[key] = newNode
            else:
                # Increment the existing next node
                nextNode.keys.add(key)
                self.map[key] = nextNode

            if not node.keys:   # Remove the current node if it has no keys left
                self.removeNode(node)
        else:  # Key does not exist
            firstNode = self.head.next
            if (firstNode == self.tail) or (firstNode.freq > 1):
                # Create a new node
                newNode = Node(1)
                newNode.keys.add(key)
                newNode.prev = self.head
                newNode.next = firstNode
                self.head.next = newNode
                firstNode.prev = newNode
                self.map[key] = newNode
            else:
                firstNode.keys.add(key)
                self.map[key] = firstNode

    def dec(self, key: str) -> None:
        if key not in self.map:  # Key does not exist
            return

        node = self.map[key]
        node.keys.remove(key)
        freq = node.freq

        if freq == 1:   # Remove the key from the map if freq is 1
            del self.map[key]
        else:
            prevNode = node.prev

            # Create a new node if the previous node does not exist or freq is not freq - 1
            if (prevNode == self.head) or (prevNode.freq != freq - 1):
                newNode = Node(freq - 1)
                newNode.keys.add(key)
                newNode.prev = prevNode
                newNode.next = node
                prevNode.next = newNode
                node.prev = newNode
                self.map[key] = newNode
            else:   # Decrement the existing previous node
                prevNode.keys.add(key)
                self.map[key] = prevNode

        if not node.keys:   # Remove the node if it has no keys left
            self.removeNode(node)

    def getMaxKey(self) -> str:
        retVal = ""

        if self.tail.prev != self.head:
            # Return one of the keys from the tail's previous node
            retVal = next(iter(self.tail.prev.keys))

        return retVal

    def getMinKey(self) -> str:
        retVal = ""

        if self.head.next != self.tail:
            # Return one of the keys from the head's next node
            retVal = next(iter(self.head.next.keys))

        return retVal


# Your AllOne object will be instantiated and called as such:
# obj = AllOne()
# obj.inc(key)
# obj.dec(key)
# param_3 = obj.getMaxKey()
# param_4 = obj.getMinKey()


if __name__ == "__main__":
    logging_setting()

    try:
        logging.info("sys.version: %s", sys.version)
        print()

        logging.info("Input")
        for methods, values in zip([["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]],
                                   [[[], ["hello"], ["hello"], [], [], ["leet"], [], []]]):
            # /* Example
            #  *  Input
            #  *  ["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
            #  *  [[], ["hello"], ["hello"], [], [], ["leet"], [], []]
            #  *  Output
            #  *  [null, null, null, "hello", "hello", null, "hello", "leet"]
            #  */
            logging.info("%s", methods)
            logging.info("%s", values)

            displayStr = []
            for key, value in zip(methods, values):
                if key == "AllOne":
                    obj = AllOne()
                    displayStr.append(None)
                elif key == "inc":
                    obj.inc(value[0])
                    displayStr.append(None)
                elif key == "dec":
                    obj.dec(value[0])
                    displayStr.append(None)
                elif key == "getMaxKey":
                    retVal = obj.getMaxKey()
                    displayStr.append(retVal)
                elif key == "getMinKey":
                    retVal = obj.getMinKey()
                    displayStr.append(retVal)
            logging.info("Output")
            logging.info("%s", displayStr)

            print("")
    except KeyboardInterrupt as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass
    except Exception as exception:
        logging.error("%s: %s", exception.__class__.__name__,
                      exception, exc_info=True)
        pass

    sys.exit(0)
