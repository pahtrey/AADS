#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

/*
В файле дерево в виде
Ann
.Bor
..Fred
..Pat
...Stiv
...Tom
.Nina
..John
...Emily
...Natali
....Robert
.....Zack
..Jack
.Den

2. Ввести  произвольное  сильно  ветвящееся дерево.  Выдать
списки вершин:
1) являющихся листьями;
2) не являющихся листьями;
3) родителей листьев;
4) заданного уровня, считая от вершины.
*/

const int DL = 20;
const int FATHER_LEVEL = 1;
const int PROGRAMM_EXIT_CODE = 54;

using namespace std;

struct Tree
{
	char name[DL];
	int level;
	Tree *father, *leftChild, *rightChild;
};

int ReadFromFile(FILE *file, Tree **tree)
{
	char buffer[DL];
	int i, k, m, length;
	Tree *p, *q, *t;
	m = 0; //уровень пред вершины
	t = 0;

	while (!feof(file))
	{
		k = fscanf(file, "%s", buffer);
		length = strlen(buffer);

		if (length == 0)
		{
			break;
		}

		k = 0;

		while (buffer[k] == '.')
		{
			k++;
		}

		p = new Tree;
		strncpy(p->name, &buffer[k], length - k + 1);

		buffer[0] = '\0';

		p->level = k;
		p->leftChild = 0;
		p->rightChild = 0;

		if (k == 0) //корень
		{
			*tree = p;
			t = *tree;
			continue;
		}

		if (k > m) //ребёнок
		{
			t->leftChild = p;
			p->father = t;
		}
		else if (k == m) //тот же уровень
		{
			t->rightChild = p;
			p->father = t->father;
		}
		else // подъем по дереву на m-k уровней
		{
			q = t;
			for (i = 0; i < m - k; i++)
			{
				q = q->father;
			}
			p->father = q->father;
			q->rightChild = p;
		}

		m = k;
		t = p;
	}

	fclose(file);
	return 0;
}

void BackFromBin(Tree *tree)
{
	int i, j;
	char str[DL];
	if (tree)
	{
		for (i = 0; i < tree->level; i++)
		{
			str[i] = '.';
		}

		j = 0;

		while (str[i++] = (tree->name)[j++]);
		cout << str << endl;
		BackFromBin(tree->leftChild);
		BackFromBin(tree->rightChild);
	}
}

void printLeaves(Tree *tree)
{
	if (tree)
	{
		printLeaves(tree->leftChild);
		if (!tree->leftChild && !tree->leftChild)
		{
			cout << tree->name << endl;
		}
		printLeaves(tree->rightChild);
	}
}

void printNodes(Tree *tree)
{
	if (tree)
	{
		printNodes(tree->leftChild);
		if (tree->leftChild || tree->leftChild)
		{
			cout << tree->name << endl;
		}
		printNodes(tree->rightChild);
	}
}

void printLeavesFathers(Tree *tree)
{
	Tree *p;
	p = new Tree;
	if (tree)
	{
		printLeavesFathers(tree->leftChild);
		if (!tree->leftChild && !tree->leftChild)
		{
			cout << tree->father->name << endl;
		}
		printLeavesFathers(tree->rightChild);
	}
}

void printNodesByLevel(Tree *tree, int level)
{
	if (tree && tree->level <= level)
	{
		printNodesByLevel(tree->leftChild, level);
		cout << tree->name << endl;
		printNodesByLevel(tree->rightChild, level);
	}
}

void ShowMenu()
{
	system("cls");
	cout << "1. Вывод всего дерева" << endl;
	cout << "2. Список вершин, являющихся листьями" << endl;
	cout << "3. Список вершин, не являющихся листьями" << endl;
	cout << "4. Список вершин, являющихся родителями листьев" << endl;
	cout << "5. Список вершин заданного уровня, считая от корня" << endl;
	cout << "6. Выход" << endl;
}

int main(int argc, char* argv[])
{
	Tree *root = 0;
	FILE *file;
	string name;
	char ch, level;
	setlocale(LC_ALL, "Rus");

	if (argc != 2)
	{
		cout << "Неверное количество аргументов" << endl
			<< "Использовать: lab2.exe <file>" << endl;
		return 1;
	}

	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		cout << "Невозможно окрыть файл" << argv[1] << endl;
		return 1;
	}

	ReadFromFile(file, &root);

	ShowMenu();
	do
	{
		ch = getchar();

		switch (ch)
		{
		case 49:
			ShowMenu();
			cout << "Дерево:" << endl;
			BackFromBin(root);
			break;
		case 50:
			ShowMenu();
			cout << "Список вершин, являющихся листьями:" << endl;
			printLeaves(root);
			break;
		case 51:
			ShowMenu();
			cout << "Список вершин, не являющихся листьями:" << endl;
			printNodes(root);
			break;
		case 52:
			ShowMenu();
			cout << "Список вершин, являющихся родителями листьев:" << endl;
			printLeavesFathers(root);
			break;
		case 53:
			ShowMenu();
			cout << "Введите уровень:";
			level = getchar();
			level = getchar();
			cout << "Список вершин заданного уровня, считая от корня:" << endl;
			printNodesByLevel(root, (int) level - 48);
			break;
		default:
			break;
		}
	} while (ch != PROGRAMM_EXIT_CODE);

    return 0;
}