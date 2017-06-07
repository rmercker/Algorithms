#include <iostream>

class Node {
private:
	int data;
	Node *next;

public:
	Node(int d) {
		data = d;
		next = NULL;
	}
	Node *getNext() {
		return next;
	}
	void setNext(Node *n) {
		next = n;
	}
	int getData() {
		return data;
	}
};

class LL {
private:
	Node *head;
	Node *last;

public:
	LL() {
		head = NULL;
		last = NULL;
	}
	Node *getHead() {
		return head;
	}
	void insert(int d) {
		if (head != NULL) {
			last->setNext(new Node(d));
			last = last->getNext();
			return;
		}
		head = new Node(d);
		last = head;
	}
	void print() {
		Node *p = head;
		while (p != NULL) {
			std::cout << p->getData() << ' ';
			p = p->getNext();
		}
	}
	void interleave(LL list, int step) {
		int i = 1;
		Node *p = head;
		Node *l = list.head;
		Node *tempP = NULL;
		Node *tempL = NULL;
		while (l != NULL) {
			if (i % step == 0) {
				tempP = p->getNext();
				tempL = l->getNext();
				p->setNext(l);
				l->setNext(tempP);
				l = tempL;
				p = p->getNext();
			}
			p = p->getNext();
			i++;
		}
	}
};

int main(void) {
	std::ios_base::sync_with_stdio(false);

	LL list1;
	int size = 0;
	int step = 0;
	int oper = 0;
	int num = 0;

	std::cin >> size;

	while (size > 0) {
		std::cin >> num;
		list1.insert(num);
		size--;
	}

	std::cin >> oper;

	while (oper > 0) {
		LL *list2 = new LL();

		std::cin >> step;
		std::cin >> size;

		while (size > 0) {
			std::cin >> num;
			list2->insert(num);
			size--;
		}

		list1.interleave(*list2, step);
		delete(list2);
		oper--;
	}

	list1.print();

	return 0;
}