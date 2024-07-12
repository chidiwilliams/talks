---
theme: default
highlighter: shiki
lineNumbers: false
info:
drawings:
  persist: false
mdc: true
author: Chidi Williams
download: true
exportFilename: "Text Search with Tries"
keywords:
colorSchema: "light"
fonts:
  sans: IBM Plex Sans
---

# Text Search with Tries

## Wolfstation DSA Program, Module 10

<div class="absolute bottom-10">
  <span class="font-400 text-neutral-500">
    <span class="text-[#066e2e] font-600">WDSAP</span> / 2024-07-14 / Chidi Williams
  </span>
</div>

---

# About me

Chidi Williams

- Co-founder, Rulebase
- (Formerly) Software Engineer, Goldman Sachs
- Mentor, Wolfstation DSA Program
- Co-Lead, SysDsgn

---

# Outline

- Problems tries solve
- Structure of a trie
- Applications of tries
- Exercises

---

# Find the prefix

- **Problem**: Write a function that checks if a list of words contains a given prefix.

```python
def list_contains_prefix(words, prefix):
  for word in words:
    if len(word) < len(prefix):
      continue
    for i in range(len(prefix)):
      if word[i] != prefix[i]:
        break
    else:
      return True
  return False

words # ['ant', 'antelope', 'bear', 'cat', 'dog']
list_contains_prefix(words, 'ant') # True
list_contains_prefix(words, 'bear') # True
list_contains_prefix(words, 'lion') # False
```

---

# Find the prefix: Summary

- To find the matches in `list_contains_prefix`, we check every word in the list and then compare the prefix to the word.
- If the length of the list is $p$ and the length of the prefix is $q$, the runtime complexity of finding the prefix is $O(p * q)$.
- **Can we do better?**

---

# Grouping the list

- Grouping related entities together often helps us find them faster.
- We'll use a similar approach to speed up the prefix search.
- Instead of putting all the words in one big list, we'll group them by their first letter.
- All the words that start with 'a' will be in one group, 'b' in another, and so on.

```python
def group_insert(group, word):
    group_index = string.ascii_lowercase.index(word[0])
    group[group_index].append(word)

group = [[] for _ in range(26)]
group_insert(group, 'ant')
group_insert(group, 'antelope')
group_insert(group, 'bear')
group_insert(group, 'lion')
group_insert(group, 'rhino')

group[0][0] # 'ant'
group[0][1] # 'antelope'
group[1][0] # 'bear'
group[11][0] # 'lion'
```

---

# Grouping the list

- Now, instead of searching the entire list, we can search only the group starting with the same first letter as the prefix.

```python
def group_contains_prefix(group, prefix):
    group_index = string.ascii_lowercase.index(prefix[0])
    return list_contains_prefix(group[group_index], prefix)

group_contains_prefix(group, 'ant') # True
group_contains_prefix(group, 'bear') # True
group_contains_prefix(group, 'zebra') # False
```

---

# Grouping the list: Summary

- Instead of searching the entire list, we search only the group starting with the same first letter as the prefix.
- Assuming the words are uniformly distributed by their first letters, the time complexity will be $O(1 + (p/26) * q)$
  - Check for the correct group based on the first letter: $O(1)$
  - Check for the prefix in the group: $O((p/26) * q)$
- $0(1 + (p/26) * q)$ is better than $O(p * q)$ for large $p$!
- **Can we do even better?**

---

# Grouping the list (again)

- We can apply the grouping technique again, now grouping words by their first and second characters.
- All the words starting with 'aa' in one list, all the words starting with 'ab' in another list, both inside the 'a' list, etc.

```python
def group2_insert(group, word):
  # Find the group for the first character of the word
  group = group.children[string.ascii_lowercase.index(word[0])]
  if len(word) == 1:
    # The group is not just a "container", but also a word itself
    group.is_word = True
    return

  # Find the group for the second character of the word
  group = group.children[string.ascii_lowercase.index(word[1])]
  if len(word) == 2:
    # The group is not just a "container", but also a word itself
    group.is_word = True
    return

  group.children.append(word)
```

---

# Grouping the list (again)

- We now check only the group starting with the same first two letters as the prefix.
- If the prefix is less than three characters long, we check the first- and second-letter groups using the `is_word` flag.

```python
def group2_contains_prefix(group, prefix):
  group = group.children[string.ascii_lowercase.index(prefix[0])]
  if len(prefix) == 1:
    return group.is_word

  group = group.children[string.ascii_lowercase.index(prefix[1])]
  if len(prefix) == 2:
    return group.is_word

  return list_contains_prefix(group.children, prefix[2:])
```

---

# Grouping the list (again): Summary

- Assuming the words are evenly distributed by their first two letters, the time complexity will be $O(2 + (p/26^2) * q)$
  - Check for the correct group based on the first two letters: $O(1 + 1)$
  - Check for the prefix in the group: $O((p/26^2) * q)$
- $O(2 + (p/26^2) * q)$ is better than $O(1 + (p/26) * q)$ for large $p$!
- **How much better can it get?**

---

# Tries

- We can group by not just the first one or two letters, but by all the letters in the word.
- This data structure is called a trie!

```python
def trie_insert(trie, word):
  node = trie
  for letter in word:
    index = string.ascii_lowercase.index(letter)
    if node.children[index] is None:
      node.children[index] = Node()
    node = node.children[index]

  node.is_word = True
```

---
layout: two-cols
---

# Tries

```python
trie = Node()
trie_insert(trie, 'a')
trie_insert(trie, 'ant')
trie_insert(trie, 'antelope')
trie_insert(trie, 'bear')
trie_insert(trie, 'boar')
trie_insert(trie, 'lion')
trie_insert(trie, 'rhino')
```

::right::

```text
- a (word)
   - n
       - t (word)
           - e
               - l
                   - o
                       - p
                           - e (word)
- b
   - e
       - a
           - r (word)
   - o
       - a
           - r (word)
- l
   - i
       - o
           - n (word)
- r
   - h
       - i
           - n
               - o (word)
```

---

# Tries

- To check that the list contains a prefix:

```python
def trie_contains_prefix(trie, prefix):
  node = trie
  for letter in prefix:
    index = string.ascii_lowercase.index(letter)
    if node.children[index] is None:
      return False
    node = node.children[index]

  return True
```

---

# Tries: Summary

- A trie is a compressed list of strings
- The runtime complexity of finding the prefix in a trie is $O(q)$, where $q$ is the length of the prefix
- $O(q)$ is much better than where we started, $O(p * q)$!
- We've moved all the work up-front: retrieving from the dictionary is now a lot faster at the cost of slower insertion
  - This is fine if we know we'll be retrieving more often than inserting
  - _Trie_ comes from the "re*trie*val"!

---

# Applications of Tries

- **Auto-completion**: Find all words that start with a given prefix
- **Spell-checking**: Find all words that are similar to a given word
- **Text search**: Find all words in a document that match a given prefix

---

# Exercises

1. What is the time complexity of inserting a word into a trie?
2. Extend the trie implementation to:
   1. Get _all_ the words in the trie that match a given prefix
   2. Remove a word from the trie
3. Using a trie, write a function that checks if a given word contains a substring
