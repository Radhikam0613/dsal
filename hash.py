# Consider telephone book database of N clients. Make use of a hash table implementation to quickly
# look up client‘s telephone number. Make use of two collision handling techniques and compare them
# using number of comparisons required to find a set of telephone numbers.
def hashfxn(key, size):
    return hash(key) % size

def linearinsert(table, key, value):
    index = hashfxn(key, len(table))
    while table[index] is not None:
        index = (index + 1) % len(table)
    table[index] = (key, value)

def doubleinsert(table, key, value):
    index = hashfxn(key, len(table))
    step = 1 + (hash(key) % (len(table) - 1))
    while table[index] is not None:
        index = (index + step) % len(table)
    table[index] = (key, value)

def linearsearch(table, key):
    index = hashfxn(key, len(table))        # Calculate initial index using hash function
    while table[index] is not None:               # While slot is not empty
        pair = table[index]                       # Get the key-value pair stored at index
        k = pair[0]                               # Extract key
        v = pair[1]                               # Extract value
        if k == key:                              # If keys match, return value
            return v
        index = (index + 1) % len(table)          # Move to next index (circular probing)
    return None                                   # If key not found

def doublesearch(table, key):
    index = hashfxn(key, len(table))                  # Primary hash to get initial index
    step = 1 + (hash(key) % (len(table) - 1))               # Secondary hash for step size
    while table[index] is not None:                         # While slot is not empty
        pair = table[index]                                 # Get the key-value pair at index
        k = pair[0]                                         # Extract key
        v = pair[1]                                         # Extract value
        if k == key:                                        # If keys match, return value
            return v
        index = (index + step) % len(table)                 # Move to next index using double hashing
    return None                                             # If key not found

def test(clientlist):
    size = 100
    lineartable = [None] * size
    doubletable = [None] * size
    for name, telephone in clientlist:
        linearinsert(lineartable, name, telephone)
        doubleinsert(doubletable, name, telephone)
    linearcomparison = 0
    for name, _ in clientlist: # _ used to ignore second parameter
        linearcomparison += 1
        linearsearch(lineartable, name)
    doublecomparison = 0
    for name, _ in clientlist:
        doublecomparison += 1
        doublesearch(doubletable, name)
    return linearcomparison, doublecomparison

if __name__ == "__main__":
    clients = [
        ("John", "123-456-7890"),
        ("Alice", "234-567-8901"),
        ("Bob", "345-678-9012"),
        ("Mary", "456-789-0123"),
        ("David", "567-890-1234")
    ]
    linear,double = test(clients)
    print("Linear Probing Comparisons:", linear)
    print("Double Hashing Comparisons:", double)