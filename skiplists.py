import random

class Node:
    def __init__(self, key, level):
        self.key = key
        # Array to hold pointers to node of different level
        self.forward = [None] * (level + 1)

class SkipList:
    def __init__(self, max_level, p):
        self.MAXLVL = max_level
        self.P = p
        self.level = 0
        # Pointer to header node
        self.header = Node(-1, max_level)

    # Generate random level for node
    def random_level(self):
        lvl = 0
        while random.random() < self.P and lvl < self.MAXLVL:
            lvl += 1
        return lvl

    # Create new node
    def create_node(self, key, level):
        return Node(key, level)

    # Insert given key in skip list
    def insert_element(self, key):
        current = self.header
        update = [None] * (self.MAXLVL + 1)

        # Start from highest level of skip list
        # Move the current pointer forward while key is greater than key of node next to current
        # Otherwise inserted current in update and move one level down and continue search
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]
            update[i] = current

        current = current.forward[0]

        if not current or current.key != key:
            rlevel = self.random_level()

            if rlevel > self.level:
                for i in range(self.level + 1, rlevel + 1):
                    update[i] = self.header
                self.level = rlevel

            n = self.create_node(key, rlevel)

            for i in range(rlevel + 1):
                n.forward[i] = update[i].forward[i]
                update[i].forward[i] = n

            print("Successfully Inserted key", key)

    # Display skip list level wise
    def display_list(self):
        print("\n*****Skip List*****")
        for i in range(self.level + 1):
            node = self.header.forward[i]
            print("Level", i, end=": ")
            while node:
                print(node.key, end=" ")
                node = node.forward[i]
            print()

    # Delete element from skip list
    def delete_element(self, key):
        current = self.header
        update = [None] * (self.MAXLVL + 1)

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]
            update[i] = current

        current = current.forward[0]

        if current and current.key == key:
            for i in range(self.level + 1):
                if update[i].forward[i] != current:
                    break
                update[i].forward[i] = current.forward[i]

            while self.level > 0 and not self.header.forward[self.level]:
                self.level -= 1
            print("Successfully deleted key", key)

    # Search for element in skip list
    def search_element(self, key):
        current = self.header

        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].key < key:
                current = current.forward[i]

        current = current.forward[0]

        if current and current.key == key:
            print("Found key:", key)
        else:
            print("Key not found:", key)




if __name__ == "__main__":
    # Create SkipList object with MAXLVL and P
    lst = SkipList(3, 0.5)

    # Insert some elements
    lst.insert_element(2)
    lst.insert_element(5)
    lst.insert_element(8)
    lst.insert_element(12)
    lst.insert_element(15)

    # Display the skip list
    lst.display_list()
