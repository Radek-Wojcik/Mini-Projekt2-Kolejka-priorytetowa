/*#pragma once
#ifndef PRIORITY_QUEUE_LIST_H
#define PRIORITY_QUEUE_LIST_H

template <typename T>
struct LNode {
	int priority;
	T data;
	LNode* next;
	LNode(T value, int priority, Node* tempNext) : data(value), priority(priority), next(tempNext) {}
};

template <typename T>
class ListQueue {
private:
	LNode* head;
	LNode* tail;
	int size;
public:
	ListQueue();
	int get_size() const;
	void insert(T e, int p);
	T extract_max();
	T find_max();
	void modify_key(T e, int p);
	//funkcje do menu
	void show() const;
	void clear();
	void build_from_file(const std::string& filename);
	void generate_random(int count, int minVal = 0, int maxVal = 100);
	~ListQueue();
};

#endif 

*/