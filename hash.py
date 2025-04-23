# Consider telephone book database of N clients. Make use of a hash table implementation to quickly
# look up client‘s telephone number. Make use of two collision handling techniques and compare them
# using number of comparisons required to find a set of telephone numbers. 
SIZE = 10  # Size of the hash table

# Create an empty table and a flag list to track occupied slots
table = [None] * SIZE
occupied = [False] * SIZE

def hash_function(phone):
    last_two = int(phone) % 100       # Extract last two digits
    return last_two % SIZE            # Map to index in table

def insert(name, phone):
    index = hash_function(phone)      # Get hash index
    while occupied[index]:            # If occupied, use linear probing
        index = (index + 1) % SIZE
    table[index] = (name, phone)      # Insert name and phone
    occupied[index] = True            # Mark slot as filled

def search(phone):
    index = hash_function(phone)      # Get initial index
    start = index                     # Remember starting point
    comparisons = 0                   # Count number of comparisons
    while occupied[index]:            # Loop until an empty slot
        comparisons += 1
        if table[index][1] == phone:  # If phone matches, return
            return index, comparisons
        index = (index + 1) % SIZE    # Continue linear probing
        if index == start:            # Avoid infinite loop
            break
    return None, comparisons          # Not found

def display():
    print("\n--- Hash Table (Linear Probing) ---")
    for i, entry in enumerate(table):
        if entry:
            print(f"[{i}] -> Name: {entry[0]}, Phone: {entry[1]}")
        else:
            print(f"[{i}] -> Empty")

clients = [
    ("Alice", "9876543210"),
    ("Bob", "9765432198"),
    ("Charlie", "9632587412"),
]
# Insert all clients into hash table
for name, phone in clients:
    insert(name, phone)
# Display the hash table
display()
# Search and show comparisons
print("\n--- Search Comparisons ---")
for name, phone in clients:
    index, comparisons = search(phone)
    print(f"Searching for {name}'s number ({phone}): Found at index {index}, Comparisons: {comparisons}")