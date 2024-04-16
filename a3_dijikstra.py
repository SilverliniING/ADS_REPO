import math

class BinomialHeapNode:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.degree = 0
        self.parent = None
        self.child = None
        self.sibling = None

class BinomialHeap:
    def __init__(self):
        self.head = None

    def merge(self, heap1, heap2):
        if not heap1:
            return heap2
        if not heap2:
            return heap1

        if heap1.key <= heap2.key:
            heap1.sibling = self.merge(heap1.sibling, heap2)
            return heap1
        else:
            heap2.sibling = self.merge(heap1, heap2.sibling)
            return heap2

    def union(self, heap):
        self.head = self.merge(self.head, heap.head)

    def insert(self, key, value):
        new_node = BinomialHeapNode(key, value)
        new_heap = BinomialHeap()
        new_heap.head = new_node
        self.union(new_heap)

    def find_min(self):
        if not self.head:
            return None

        min_node = self.head
        current = self.head.sibling
        while current:
            if current.key < min_node.key:
                min_node = current
            current = current.sibling
        return min_node

    def extract_min(self):
        if not self.head:
            return None

        min_node = self.find_min()
        if min_node == self.head:
            self.head = self.head.sibling
        else:
            prev = self.head
            while prev.sibling != min_node:
                prev = prev.sibling
            prev.sibling = min_node.sibling

        if min_node.child:
            new_heap = BinomialHeap()
            new_heap.head = min_node.child
            new_heap.reverse_linked_list()
            self.union(new_heap)

        return min_node

    def decrease_key(self, node, new_key):
        node.key = new_key
        while node.parent and node.key < node.parent.key:
            node.key, node.parent.key = node.parent.key, node.key
            node.value, node.parent.value = node.parent.value, node.value
            node = node.parent

    def reverse_linked_list(self):
        prev = None
        current = self.head
        while current:
            current.sibling, current.parent = prev, None
            prev, current = current, current.sibling
        self.head = prev

def dijkstra(graph, source):
    distance = {}
    for vertex in graph:
        distance[vertex] = math.inf
    distance[source] = 0

    heap = BinomialHeap()
    for vertex in graph:
        heap.insert(distance[vertex], vertex)

    while heap.head:
        min_node = heap.extract_min()
        u = min_node.value
        for v, w in graph[u].items():
            alt = distance[u] + w
            if alt < distance[v]:
                distance[v] = alt
                heap.decrease_key(heap.head, alt)

    return distance

# Example graph represented as an adjacency list
graph = {
    'A': {'B': 3, 'C': 5},
    'B': {'A': 3, 'C': 2, 'D': 6},
    'C': {'A': 5, 'B': 2, 'D': 7},
    'D': {'B': 6, 'C': 7}
}

source_node = 'A'
distances = dijkstra(graph, source_node)
print("Shortest distances from source node", source_node + ":")
for node, distance in distances.items():
    print("Distance to", node, "=", distance)
