#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

class Set {
private:
    vector<int> elements;

public:
    // a. Add (new Element) - Place a value into the set
    void add(int element) {
        if (!contains(element)) {
            elements.push_back(element);
        }
    }

    // b. Remove (element) - Remove the value from the set
    void remove(int element) {
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            if (*it == element) {
                elements.erase(it);
                return;
            }
        }
    }

    // c. Contains (element) - Return true if element is in collection
    bool contains(int element) const {
        for (int e : elements) {
            if (e == element) {
                return true;
            }
        }
        return false;
    }

    // d. Size () - Return number of values in the collection
    int size() const {
        return elements.size();
    }

    // e. Iterator () - Return an iterator to loop over collection
    vector<int>::iterator iterator() {
        return elements.begin();
    }

    // f. Intersection of two sets
    Set intersection(const Set &other) const {
        Set result;
        for (int e : elements) {
            if (other.contains(e)) {
                result.add(e);
            }
        }
        return result;
    }

    // g. Union of two sets
    Set unionSet(const Set &other) const {
        Set result = *this;  // Start with current set
        for (int e : other.elements) {
            result.add(e);
        }
        return result;
    }

    // h. Difference between two sets
    Set difference(const Set &other) const {
        Set result;
        for (int e : elements) {
            if (!other.contains(e)) {
                result.add(e);
            }
        }
        return result;
    }

    // i. Subset check
    bool isSubset(const Set &other) const {
        for (int e : elements) {
            if (!other.contains(e)) {
                return false;
            }
        }
        return true;
    }

    // Print set for demonstration
    void printSet() const {
        cout << "{ ";
        for (int e : elements) {
            cout << e << " ";
        }
        cout << "}" << endl;
    }
};

int main() {
    Set set1;
    set1.add(1);
    set1.add(2);
    set1.add(3);
    set1.add(4);
    set1.add(5);

    cout << "Set 1: ";
    set1.printSet();

    Set set2;
    set2.add(4);
    set2.add(5);
    set2.add(6);
    set2.add(7);

    cout << "Set 2: ";
    set2.printSet();

    // f. Intersection
    Set intersectionSet = set1.intersection(set2);
    cout << "Intersection of Set 1 and Set 2: ";
    intersectionSet.printSet();

    // g. Union
    Set unionSet = set1.unionSet(set2);
    cout << "Union of Set 1 and Set 2: ";
    unionSet.printSet();

    // h. Difference
    Set differenceSet = set1.difference(set2);
    cout << "Difference (Set 1 - Set 2): ";
    differenceSet.printSet();

    // i. Subset check
    cout << "Is Set 1 a subset of Set 2? " << (set1.isSubset(set2) ? "Yes" : "No") << endl;
    
    return 0;
}
