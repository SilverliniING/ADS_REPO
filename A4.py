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
    
    def longest_common_prefix(self):
        node = self.root
        prefix = ""
        while len(node.children) == 1 and not node.is_end_of_word:
            char = list(node.children.keys())[0]
            prefix += char
            node = node.children[char]
        return prefix

def longest_common_prefix(words):
    trie = Trie()
    for word in words:
        trie.insert(word)
    return trie.longest_common_prefix()

def main():
    words = input("Enter words separated by spaces: ").split()
    print("Longest Common Prefix:", longest_common_prefix(words))

if __name__ == "__main__":
    main()
