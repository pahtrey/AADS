#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

/*
2. ������  ������������  ������  ���������� ������.  ������
������ ������:
1) ���������� ��������;
2) �� ���������� ��������;
3) ��������� �������;
4) ��������� ������, ������ �� �������.
*/

const int DL = 20;

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
	m = 0; //������� ���� �������
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
		p->leftChild = NULL;
		p->rightChild = NULL;

		if (k == 0) //������
		{
			*tree = p;
			t = *tree;
			continue;
		}

		if (k > m) //������
		{
			t->leftChild = p;
			p->father = t;
		}
		else if (k == m) //��� �� �������
		{
			t->rightChild = p;
			p->father = t->father;
		}
		else // ������ �� ������ �� m-k �������
		{
			q = t;
			for (i = 0; i < m - k; i++)
			{
				q = q->father;
			}
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

		while (str[i++] = (tree->name)[j++])
		{
			printf("%s\n", str);
		}

		BackFromBin(tree->leftChild);
		BackFromBin(tree->rightChild);
	}
}

int main()
{
    return 0;
}