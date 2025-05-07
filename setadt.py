# To create ADT that implement the "set" concept.
# a. Add (new Element) -Place a value into the set
# b. Remove (element) :- Remove the value 
# c. Contains (element) :- Return true if element is in collection
# d. Size () :- Return number of values in collection Iterator () Return an iterator used to loop over collection
# e. Intersection of two sets
# f. Union of two sets
# g. Difference between two sets, h. Subset
# Function to add a new element to the set (if not already present)
# When you define a method within a class, you always include self as the first parameter so that Python knows you're referring to the instance of the class on which the method is called.
class SetADT:
    def __init__(self):
        self.elements = set()  # 'self' refers to the current instance of SetADT
        
    def add(self, new_element):
        self.elements.add(new_element)  # 'self.elements' refers to the set of this instance

    def contains(self, element):
        return element in self.elements

    def size(self):
        return len(self.elements)

    def subset(self, other_set):
        return self.elements.issubset(other_set.elements)
    
    def iterator(self):# Return an iterator to loop over the set elements
        return iter(self.elements)

    def remove(self, element):
        if element in self.elements:
            self.elements.remove(element)

    def intersection(self, other_set):
        return SetADT().from_elements(self.elements & other_set.elements)  # Uses 'self' to get current set elements

    def union(self, other_set):
        return SetADT().from_elements(self.elements | other_set.elements)

    def difference(self, other_set):
        return SetADT().from_elements(self.elements - other_set.elements)

    def from_elements(self, elements):
        new_set = SetADT()  # 'new_set' is a new instance of SetADT
        new_set.elements = elements  # Set 'new_set' elements to the provided elements
        return new_set

set1 = SetADT()
set1.add(1)
set1.add(2)
set1.add(3)
set2 = SetADT()
set2.add(3)
set2.add(4)
set2.add(5)
print("Set1 contains 2?", set1.contains(2))
print("Set1 size:", set1.size())
intersection_set = set1.intersection(set2)
print("Intersection:", list(intersection_set.iterator()))
union_set = set1.union(set2)
print("Union:", list(union_set.iterator()))
difference_set = set1.difference(set2)
print("Difference:", list(difference_set.iterator()))
print("Is Set1 a subset of Set2?", set1.subset(set2))
