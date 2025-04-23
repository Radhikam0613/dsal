# To create ADT that implement the "set" concept.
# a. Add (new Element) -Place a value into the set
# b. Remove (element) :- Remove the value 
# c. Contains (element) :- Return true if element is in collection
# d. Size () :- Return number of values in collection Iterator () Return an iterator used to loop over collection
# e. Intersection of two sets
# f. Union of two sets
# g. Difference between two sets, h. Subset
# Function to add a new element to the set (if not already present)
def add(set, element):
    # Check if the element is already in the set, if not, add it
    if element not in set:
        set.append(element)

# Function to remove an element from the set (if it exists)
def remove(set, element):
    # Check if the element exists in the set, if yes, remove it
    if element in set:
        set.remove(element)

# Function to check if an element is present in the set
def contains(set, element):
    # Return True if element is in the set, else False
    return element in set

# Function to return the number of elements in the set
def size(set):
    # Return the length (size) of the set
    return len(set)

# Function to print the elements of the set
def print_set(set):
    # Iterate over each element in the set and print it
    for element in set:
        print(element, end=" ")
    # Print a newline after all elements are printed
    print()

# Function to find the intersection of two sets (elements common to both)
def intersection(set1, set2):
    # Initialize an empty list to store the common elements
    common_elements = []
    # Loop through each element in set1
    for element in set1:
        # Check if this element is also present in set2
        if element in set2:
            # If it is, add this element to the common_elements list
            common_elements.append(element)
    return common_elements


# Function to find the union of two sets (all elements from both sets)
def union(set1, set2):
    # Return a list of unique elements from both set1 and set2
    return list(set(set1 + set2))

# Function to find the difference between two sets (elements in set1 but not in set2)
def difference(set1, set2):
    # Return a list of elements that are in set1 but not in set2
    diff = []
    # Loop through each element in set1
    for element in set1:
        # If the element is not in set2, add it to the diff list
        if element not in set2:
            diff.append(element)
    # Return the resulting difference
    return diff

# Function to check if set1 is a subset of set2
def is_subset(set1, set2):
    # Check if every element in set1 is present in set2
    for element in set1:
        # If any element of set1 is not in set2, return False
        if element not in set2:
            return False
    # If all elements are in set2, return True
    return True


# Create two empty sets (represented as lists)
set1 = []
set2 = []

# Add elements to set1
add(set1, 1)
add(set1, 2)
add(set1, 3)
add(set1, 4)
add(set1, 5)

# Print the elements of set1
print("Set 1:", end = " ")
print_set(set1)

# Add elements to set2
add(set2, 4)
add(set2, 5)
add(set2, 6)
add(set2, 7)

# Print the elements of set2
print("Set 2:", end=" ")
print_set(set2)

# Find the intersection of set1 and set2
intersection_set = intersection(set1, set2)
print("Intersection of Set 1 and Set 2:", end=" ")
print_set(intersection_set)

# Find the union of set1 and set2
union_set = union(set1, set2)
print("Union of Set 1 and Set 2:", end=" ")
print_set(union_set)

# Find the difference between set1 and set2
difference_set = difference(set1, set2)
print("Difference (Set 1 - Set 2):", end=" ")
print_set(difference_set)

# Check if set1 is a subset of set2
print("Is Set 1 a subset of Set 2?", "Yes" if is_subset(set1, set2) else "No")
