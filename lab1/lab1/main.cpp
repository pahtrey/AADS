#include "stdafx.h"

using namespace std;

enum MenuLevel {
	MainMenu,
	AdditionalMenu
};

struct Queue
{
	string element;
	struct Queue *next;
};

struct Stack
{
	Queue *element;
	Queue *last;
	struct Stack *next;
};

void ShowMenu(int level);

void Push();
void Pop();
void ShowStack();

void Add(string element);
void Delete();
void ShowQueue(Queue *qu);

Stack *topStack = nullptr, *p;
Queue *lastQueue = nullptr, *firstQueue = nullptr, *q;

int main()
{
	const int PROGRAMM_EXIT_CODE = 53;
	const int MENU_BACK_CODE = 52;
	char ch;

	setlocale(LC_ALL, "Rus");

	ShowMenu(MainMenu);
	do {
		ch = _getch();

		switch (ch)
		{
		case 49:
			ShowMenu(MainMenu);
			Push();
			cout << "������ ���� � ������ �������" << endl;
			break;
		case 50:
			ShowMenu(MainMenu);
			Pop();
			break;
		case 51:
			ShowMenu(MainMenu);
			ShowStack();
			break;
		case 52:
			ShowMenu(AdditionalMenu);

			do
			{
				string str;
				ch = _getch();

				switch (ch)
				{
				case 49:
					ShowMenu(AdditionalMenu);

					if (topStack == nullptr)
					{
						cout << "�� ������ ������� �����." << endl;
						break;
					}

					cout << "������� �������: ";
					getline(cin, str);
					Add(str);
					ShowMenu(AdditionalMenu);
					break;
				case 50:
					ShowMenu(AdditionalMenu);
					Delete();
					break;
				case 51:
					ShowMenu(AdditionalMenu);
					ShowQueue(firstQueue);
					break;
				default:
					ShowMenu(AdditionalMenu);
					break;
				}
			} while (ch != MENU_BACK_CODE);

			ShowMenu(MainMenu);
			break;
		default:
			ShowMenu(MainMenu);
			break;
		}
	} while (ch != PROGRAMM_EXIT_CODE);

	return 0;
}

void ShowMenu(int level)
{
	system("cls");
	switch (level)
	{
	case MainMenu:
		cout << "1. �������� � ����" << endl;
		cout << "2. ������� �� �����" << endl;
		cout << "3. �������� �����" << endl;
		cout << "4. ������ � ��������" << endl;
		cout << "5. �����" << endl;
		break;
	case AdditionalMenu:
		cout << "1. �������� � �������" << endl;
		cout << "2. ���������� �������" << endl;
		cout << "3. ����� �������" << endl;
		cout << "4. ������� � ������� ����" << endl;
	default:
		break;
	}
}

void Push()
{
	firstQueue = new Queue;
	firstQueue->next = nullptr;
	firstQueue->element = "";
	lastQueue = firstQueue;

	p = new Stack;
	p->element = firstQueue;
	p->next = topStack;
	p->last = lastQueue;
	topStack = p;
}

void Pop()
{
	if (topStack == nullptr)
	{
		cout << "���� ����" << endl;
		return;
	}

	if (topStack->next == nullptr)
	{
		topStack = nullptr;
		firstQueue = nullptr;
		lastQueue = nullptr;
		return;
	}

	p = topStack;
	topStack = p->next;
	firstQueue = topStack->element;
	lastQueue = topStack->last;
	delete(p);
}

void ShowStack()
{
	if (topStack == nullptr)
	{
		cout << "���� ����" << endl;
		return;
	}

	p = topStack;
	while (p != nullptr)
	{
		ShowQueue(p->element);
		p = p->next;
	}
}

void Add(string element)
{
	if (firstQueue == nullptr || firstQueue->element == "")
	{
		firstQueue->element = element;
		firstQueue->next = nullptr;
	}
	else
	{
		q = new Queue;
		q->next = nullptr;
		q->element = element;
		lastQueue->next = q;
		lastQueue = q;
		topStack->last = lastQueue;
	}
}

void Delete()
{
	if (firstQueue->next == nullptr)
	{
		cout << "������� �����" << endl;
		firstQueue->element = "";
		return;
	}

	q = firstQueue;
	firstQueue = q->next;
	topStack->element = firstQueue;
	delete(q);
}

void ShowQueue(Queue *qu)
{
	q = qu;

	if (q == nullptr || q->element == "")
	{
		cout << "������� �����" << endl;
		return;
	}

	while (q != nullptr)
	{
		cout << q->element << ' ';
		q = q->next;
	}
	cout << endl;
}