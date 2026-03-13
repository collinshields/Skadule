#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

template <typename T> class LinkedList {
private:
	struct Node {
		T data;
		Node* next;
		Node(const T& value) : data(value), next(nullptr) {}
	};
	Node* head;
	Node* iterator_focus;
public:
	LinkedList() : head(nullptr) {}
	~LinkedList() {
		Node* current = head;
		while (current) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	void add(const T& value) {
		Node* newNode = new Node(value);
		if (!head) {
			head = newNode;
			return;
		}
		Node* current = head;
		while (current->next) {
			current = current->next;
		}
		current->next = newNode;
	}
	void remove(const T& value) {
		if (!head) return;
		if (head->data == value) {
			Node* temp = head;
			head = head->next;
			delete temp;
			return;
		}
		Node* current = head;
		while (current->next && current->next->data != value) {
			current = current->next;
		}
		if (current->next) {
			Node* temp = current->next;
			current->next = current->next->next;
			delete temp;
		}
	}
	T* next() {
		if (!iterator_focus) {
			iterator_focus = head;
		} else {
			iterator_focus = iterator_focus->next;
		}
		return iterator_focus ? &iterator_focus->data : nullptr;
	}
};
#endif