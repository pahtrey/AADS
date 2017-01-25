#include "stdafx.h"
#include <iostream>
#include <istream>
#include <fstream>
#include <string>

using namespace std;

void Distr(fstream& FileA, fstream& FileB, fstream& FileC, int seriesLength)
{
	int number;

	if (!FileA.eof())
	{
		FileA >> number;
	}

	while (!FileA.eof())
	{
		for (int i = 0; i < seriesLength; ++i)
		{
			FileB << number << " ";
			FileA >> number;
		}
		for (int j = 0; j < seriesLength; ++j)
		{
			FileC << number << " ";
			FileA >> number;
		}
	}
}

void Merge(fstream &FileA, fstream &FileB, fstream &FileC, int seriesLength)
{
	int number1, number2;

	if (!FileB.eof())
	{
		FileB >> number1;
	}

	if (!FileC.eof())
	{
		FileC >> number2;
	}

	while (!FileB.eof() && !FileC.eof())
	{
		int i = 0;
		int j = 0;
		while (i < seriesLength && j < seriesLength)
		{
			if (number1 < number2)
			{
				FileA << number1 << " ";
				FileB >> number1;
				++i;
			}
			else
			{
				FileA << number2 << " ";
				FileC >> number2;
				++j;
			}
		}

		while (i < seriesLength && !FileB.eof())
		{
			FileA << number1 << " ";
			FileB >> number1;
			++i;
		}

		while (j < seriesLength && !FileC.eof())
		{
			FileA << number2 << " ";
			FileC >> number2;
			++j;
		}
	}

	while (!FileB.eof())
	{
		FileA << number1 << " ";
		FileB >> number1;
	}

	while (!FileC.eof())
	{
		FileA << number2 << " ";
		FileC >> number2;
	}
}

void MergeSort(string &input)
{
	fstream FileA, FileB, FileC;
	int i = 1;
	int countIntegerInFile = 0;
	int sizeFileA = 0;
	int number;

	string FileNameA = input;

	//string FileNameA = "A.txt";
	string FileNameB = "B.txt";
	string FileNameC = "C.txt";

	FileA.open(FileNameA);

	while (FileA >> number)
	{
		++countIntegerInFile;
	}
	FileA.close();

	while (i < countIntegerInFile)
	{
		fstream FileA, FileB, FileC;
		FileA.open(FileNameA, std::ios::in);
		FileB.open(FileNameB, std::ios::out);
		FileC.open(FileNameC, std::ios::out);

		Distr(FileA, FileB, FileC, i);

		FileA.close();
		FileB.close();
		FileC.close();

		FileA.open(FileNameA, std::ios::out);
		FileB.open(FileNameB, std::ios::in);
		FileC.open(FileNameC, std::ios::in);

		Merge(FileA, FileB, FileC, i);

		FileA.close();
		FileB.close();
		FileC.close();

		i *= 2;
	}
	remove(FileNameB.c_str());
	remove(FileNameC.c_str());
}

void PrintFileElements(string &input)
{
	int number;
	fstream fileInput;

	fileInput.open(input);
	if (!fileInput.good())
	{
		cout << "Can not open file" << input << endl;
	}
	else
	{
		while (fileInput >> number)
		{
			cout << number << " ";
		}
		cout << endl;
	}
	fileInput.close();
}

int main()
{
	cout << "Merge Sort" << endl;
	string input;

	cout << "Enter file name to sort: ";
	cin >> input;

	cout << "Input elements:" << endl;
	PrintFileElements(input);

	MergeSort(input);

	cout << "Sorted elements:" << endl;
	PrintFileElements(input);

	system("pause");

    return 0;
}