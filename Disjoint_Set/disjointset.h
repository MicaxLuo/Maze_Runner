// Course: 							DSA555 NSA
// Assignment:      		1
// Name: 								Xiaomin (Mica) Luo
// Seneca Student ID:   133728170
// Seneca email: 				xluo42@myseneca.ca

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSet {
	struct Node{
		int m_data;
		int m_rep;
		Node* m_prev;
		Node* m_next;
		Node(const int& data = int{}, const int& rep = int{}, Node* next = nullptr, Node* prev = nullptr) {
			m_data = data;
			m_rep = rep;
			m_next = next;
			m_prev = prev;
		};
	};
	int m_size;
	Node** m_node;
public:
	DisjointSet(int max);
	DisjointSet(const DisjointSet& other);
	DisjointSet(DisjointSet&& other);
	DisjointSet& operator=(const DisjointSet& other);
	DisjointSet& operator=(DisjointSet&& other);
	~DisjointSet();
	bool makeSet(int object);
	int findSet(int object) const;
	bool unionSets(int rep1, int rep2);
};

#endif // !DISJOINTSET_H