
#include "disjointset.h"

DisjointSet::DisjointSet(int max) {
	m_size = max;
	m_node = new Node*[m_size];

	for (int i = 0; i < m_size; i++) {
		m_node[i] = nullptr;
	}
}

DisjointSet::DisjointSet(const DisjointSet& other) {
	// shallow copy on all non-resource instance variables
	m_size = other.m_size;
	m_node = new Node*[m_size];
	// allocate memory for each new resource, copy data from the source resource to the newly created resource
	for (int i = 0; i < m_size; i++) {
		if (other.m_node[i] != nullptr) {
			m_node[i] = new Node(other.m_node[i]->m_data, other.m_node[i]->m_rep, other.m_node[i]->m_next, other.m_node[i]->m_prev);
		}
	}
}

DisjointSet::DisjointSet(DisjointSet&& other) {
	m_size = other.m_size;
	m_node = other.m_node;
	//safety state
	other.m_size = 0;
	other.m_node = nullptr;
}

DisjointSet& DisjointSet::operator=(const DisjointSet& other) {
	if (this != &other) { // check for self assignment
		for (int i = 0; i < m_size; i++) {
			delete m_node[i];
		}
		delete m_node;
		m_size = other.m_size;
		if (m_size != 0) {
			m_node = new Node * [m_size];
			for (int i = 0; i < m_size; i++) {
				if (other.m_node[i] != nullptr) {
					m_node[i] = new Node(other.m_node[i]->m_data, other.m_node[i]->m_rep, other.m_node[i]->m_next,
						other.m_node[i]->m_prev);
				}
			}
		}
	}
	return *this;
}

DisjointSet& DisjointSet::operator=(DisjointSet&& other) {
	if (this != &other) {
		for (int i = 0; i < m_size; i++) {
			delete m_node[i];
		}
		delete m_node;
		m_size = other.m_size;
		m_node = other.m_node;
		other.m_node = nullptr;
	}
	return *this;
}

DisjointSet::~DisjointSet() {
	if (m_node != nullptr) {
		for (int i = 0; i < m_size; i++) {
				delete m_node[i];
		}
		delete m_node;
		m_node = nullptr;
	}
}

bool DisjointSet::makeSet(int object) {
	// Creates a new set with object as the only member of the set
	if (object >= m_size || object < 0 || m_node[object] != nullptr) {
		return false;
	}
	else {
		m_node[object] = new Node(object, object, nullptr, nullptr);
		return true;
	}
}

int DisjointSet::findSet(int object) const {
	// returns the representative of the set containing object
	if (object >= m_size || object < 0 || m_node[object] == nullptr) {
		return -1;
	}
	else {
		return m_node[object]->m_rep;
	}
}

bool DisjointSet::unionSets(int rep1, int rep2) {
	bool rc = false;
	if (rep1 >= m_size || rep1 < 0 || rep2 >= m_size || rep2 < 0 || m_node[rep1] == nullptr || m_node[rep2] == nullptr) {
		rc = false; // if either object1 or object2 are not in any set or is invalid, function does nothing and returns false
	}
	else if (m_node[rep1]->m_rep == m_node[rep2]->m_rep) {
		rc = true; // if object 1 and object 2 are in the same set, function does nothing and returns true
	}
	else { // combines 2 sets
		Node* first = m_node[rep1];
		int firstCount = 0;
		while (first->m_next != nullptr) {
			first = first->m_next;
			firstCount++;
		}

		Node* second = m_node[rep2];
		int secondCount = 0;
		while (second->m_next != nullptr) {
			second = second->m_next;
			secondCount++;
		}

		if (firstCount > secondCount) { // put bigger set in the front
			while (second->m_prev != nullptr) {
				second = second->m_prev;
			}
			first->m_next = second;
			second->m_prev = first;
			int rep = findSet(rep1);

			while (second != nullptr) {
				second->m_rep = rep;  // new rep is chosen
				second = second->m_next;
			}
		}
		else {
			while (first->m_prev != nullptr) {
				first = first->m_prev;
			}
			second->m_next = first;
			first->m_prev = second;
			int rep = findSet(rep2);

			while (first != nullptr) {
				first->m_rep = rep;
				first = first->m_next;
			}
		}
		rc = true;
	}

	return rc;
}