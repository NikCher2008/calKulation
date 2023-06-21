#include <iostream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

struct Node
{
	Node* next = nullptr;
	char value;
};

Node* head = nullptr;
Node* tail = nullptr;

inline bool is_empty1()
{
	return head == nullptr;
}

void append(char val) {
	Node* new_element = new Node;
	new_element->value = val;
	if (!is_empty1()) {
		tail->next = new_element;
		tail = new_element;
		tail->next = head;
	}
	else {
		head = new_element;
		tail = new_element;
		tail->next = head;
	}
}

void add_to_head(char val) {
	Node* new_element = new Node;
	new_element->value = val;
	if (!is_empty1()) {
		new_element->next = head;
		head = new_element;
		tail->next = head;
	}
	else {
		head = new_element;
		tail = new_element;
		tail->next = head;
	}
}

int count_1() {
	Node* elem = head;
	int count = 0;
	do {
		count += 1;
		elem = elem->next;
	} while (elem != head);
	return count;
}

void insert(int pos, char val) {
	Node* elem = head;
	Node* new_element = new Node;
	new_element->value = val;
	int count = 0;
	if (pos <= 0) {
		add_to_head(val);
	}
	else if (pos >= count_1()) {
		append(val);
	}
	else {
		do {
			count += 1;
			if (count == pos) {
				break;
			}
			elem = elem->next;

		} while (true);

		new_element->next = elem->next;
		elem->next = new_element;
	}
}

void clear() {
	Node* elem = head;
	Node* elemm;
	do {
		elemm = elem->next;
		delete[] elem;
		elem = elemm;
	} while (elem != head);

}

void print() {
	Node* elem = head;
	do {
		cout << elem->value << " ";
		elem = elem->next;
	} while (elem != head);
}

void delete_end() {
	if (!is_empty1()) {
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			Node* element = head;
			while (element->next != tail)
				element = element->next;
			delete tail;
			tail = element;
			tail->next = head;
		}
	}
}

inline char get_tail() {
	return tail->value;
}

void PUSH(char val)
{
	append(val);
}

char POP()
{
	char buffer = get_tail();
	delete_end();
	return buffer;
}

bool check_skob(char* virazhenie) {

	for (int i = 0; i < strlen(virazhenie); i++) {
		if (virazhenie[i] == '(') {
			PUSH(1);
		}
		else if (virazhenie[i] == ')') {
			if (!is_empty1()) {
				POP();
			}
			else {
				cout<< "oy may";
				break;
			}
		}

	}
	return is_empty1();
}

void add_char(char* str, char c) {
	int len = strlen(str);
	str[len] = c;
	str[len + 1] = '\0';
}

char oper[6] = "(+-/*";
short prior[5] = { -1, 0, 0, 1, 1 };

int main()
{
	char virazhenie[100];
	char prefix[100] = "\0";
	do {
		gets_s(virazhenie);
	} while (!check_skob(virazhenie));

	char numbers[100] = "\0";
	for (int i = 0; i < strlen(virazhenie); i++) {

		if (isdigit(virazhenie[i])) {
			add_char(numbers, virazhenie[i]);
		}
		else {
			if (strlen(numbers) > 0) {
				strcat(prefix, numbers);
				numbers[0] = '\0';
				add_char(prefix, ' ');
			}
			if (virazhenie[i] == '*' ||
				virazhenie[i] == '/' ||
				virazhenie[i] == '+' ||
				virazhenie[i] == '-')
			{
				while (!is_empty1() && (prior[strchr(oper, get_tail()) - oper] >=
					prior[strchr(oper, virazhenie[i]) - oper]))
				{
					add_char(prefix, POP());
					add_char(prefix, ' ');
				}

				PUSH(virazhenie[i]);
			}
			else if (virazhenie[i] == '(') {
				PUSH(virazhenie[i]);
			}
			else if (virazhenie[i] == ')') {
				while (!is_empty1() && get_tail() != '(') {
					add_char(prefix, POP());
					add_char(prefix, ' ');
				}
				POP();
			}
		}
	}
	if (strlen(numbers) > 0) {
		strcat(prefix, numbers);
		numbers[0] = '\0';
		add_char(prefix, ' ');
	}
	while (!is_empty1()) {
		add_char(prefix, POP());
		add_char(prefix, ' ');
	}

	cout<< prefix<< endl;

}
	
