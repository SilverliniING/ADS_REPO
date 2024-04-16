class TrieNode:
    def __init__(self):
        self.children = {}
        self.is_end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.is_end_of_word = True
    
    def _preorder_traversal(self, node, prefix, result):
        if node.is_end_of_word:
            result.append(prefix)
        for char, child in sorted(node.children.items()):
            self._preorder_traversal(child, prefix + char, result)
    
    def lexicographic_sort(self):
        result = []
        self._preorder_traversal(self.root, "", result)
        return result

def main():
    words = input("Enter words separated by spaces: ").split()
    trie = Trie()
    for word in words:
        trie.insert(word)
    sorted_words = trie.lexicographic_sort()
    print("Lexicographically Sorted Words:")
    for word in sorted_words:
        print(word)

if __name__ == "__main__":
    main()
