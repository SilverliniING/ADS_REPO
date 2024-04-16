class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class StackLinkedList:
    def __init__(self):
        self.head = None
    
    def push(self, data):
        new_node = Node(data)
        new_node.next = self.head
        self.head = new_node
    
    def pop(self):
        if self.head is None:
            return None
        popped = self.head.data
        self.head = self.head.next
        return popped

class StackArray:
    def __init__(self, size):
        self.size = size
        self.stack = [None] * size
        self.top = -1
    
    def push(self, data):
        if self.top == self.size - 1:
            print("Stack Overflow")
            return
        self.top += 1
        self.stack[self.top] = data
    
    def pop(self):
        if self.top == -1:
            #print("Stack Underflow")
            return None
        popped = self.stack[self.top]
        self.top -= 1
        return popped

class TwoStacks:
    def __init__(self, size):
        self.size = size
        self.stack = [None] * size
        self.top1 = -1
        self.top2 = size
    
    def push1(self, data):
        if self.top1 < self.top2 - 1:
            self.top1 += 1
            self.stack[self.top1] = data
        else:
            print("Stack Overflow for Stack 1")
    
    def push2(self, data):
        if self.top1 < self.top2 - 1:
            self.top2 -= 1
            self.stack[self.top2] = data
        else:
            print("Stack Overflow for Stack 2")
    
    def pop1(self):
        if self.top1 >= 0:
            popped = self.stack[self.top1]
            self.top1 -= 1
            return popped
        else:
            #print("Stack Underflow for Stack 1")
            return None
    
    def pop2(self):
        if self.top2 < self.size:
            popped = self.stack[self.top2]
            self.top2 += 1
            return popped
        else:
            #print("Stack Underflow for Stack 2")
            return None

class KStacks:
    def __init__(self, k, size):
        self.k = k
        self.size = size
        self.stack = [None] * size
        self.top = [-1] * k
        self.next = list(range(1, size))
        self.next.append(-1)
        self.free = 0
    
    def is_full(self):
        return self.free == -1
    
    def is_empty(self, sn):
        return self.top[sn] == -1
    
    def push(self, item, sn):
        if self.is_full():
            print("Stack Overflow")
            return
        insert_at = self.free
        self.free = self.next[self.free]
        self.stack[insert_at] = item
        self.next[insert_at] = self.top[sn]
        self.top[sn] = insert_at
    
    def pop(self, sn):
        if self.is_empty(sn):
           # print("Stack Underflow")
            return None
        popped_index = self.top[sn]
        popped_item = self.stack[popped_index]
        self.top[sn] = self.next[popped_index]
        self.next[popped_index] = self.free
        self.free = popped_index
        return popped_item

def find_merging_point(list1, list2):
    def get_length(head):
        length = 0
        while head:
            length += 1
            head = head.next
        return length

    len1 = get_length(list1)
    len2 = get_length(list2)

    ptr1 = list1
    ptr2 = list2

    # Move pointers to the same starting position
    while len1 > len2:
        ptr1 = ptr1.next
        len1 -= 1
    while len2 > len1:
        ptr2 = ptr2.next
        len2 -= 1

    # Move both pointers until they meet or reach the end
    while ptr1 and ptr2:
        if ptr1 == ptr2:
            return ptr1
        ptr1 = ptr1.next
        ptr2 = ptr2.next

    return None

def main():
    # Creating linked list nodes
    node1 = Node(1)
    node2 = Node(2)
    node3 = Node(3)
    node4 = Node(4)
    node5 = Node(5)
    node6 = Node(6)
    node7 = Node(7)

    # Constructing linked lists
    list1 = node1
    node1.next = node2
    node2.next = node3
    node3.next = node6
    node6.next = node7

    list2 = node4
    node4.next = node5
    node5.next = node6  # Intersection point with list1

    # Creating stack instances
    stack_linked_list = StackLinkedList()
    stack_array = StackArray(size=5)
    two_stacks = TwoStacks(size=10)
    k_stacks = KStacks(k=3, size=15)

    # Pushing and popping elements to demonstrate stack operations
    for i in range(1, 6):
        stack_linked_list.push(i)
        stack_array.push(i)
        two_stacks.push1(i)
        two_stacks.push2(i)
        k_stacks.push(i, sn=0)

    # Displaying popped elements
    print("Popped elements from StackLinkedList:")
    while True:
        popped = stack_linked_list.pop()
        if popped is None:
            break
        print(popped, end=' ')

    print("\nPopped elements from StackArray:")
    while True:
        popped = stack_array.pop()
        if popped is None:
            break
        print(popped, end=' ')

    print("\nPopped elements from TwoStacks:")
    for _ in range(5):
        popped1 = two_stacks.pop1()
        popped2 = two_stacks.pop2()
        print(popped1, popped2, end=' ')

    print("\nPopped elements from KStacks:")
    for i in range(3):
        for j in range(5):
            popped = k_stacks.pop(i)
            print(popped, end=' ')

    # Finding the merging point of the linked lists
    merging_point = find_merging_point(list1, list2)
    if merging_point:
        print("\nMerging point of the linked lists:", merging_point.data)
    else:
        print("\nNo merging point found.")


if __name__ == "__main__":
    main()

#StackArray: It shows "Stack Underflow" after printing the popped elements. 
    #This message indicates that the stack is empty, which is expected behavior after popping all elements. 
    #However, it might confuse readers because it's displayed as if it's an error. You can remove this message to avoid confusion.
#TwoStacks: It shows "None" after popping elements from the second stack. 
    #This is expected because the second stack doesn't have any elements. 
    #However, it's cleaner to handle this case by checking if the popped element is None and not displaying it.