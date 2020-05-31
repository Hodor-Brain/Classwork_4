#include <iostream>
#include <fstream>
#include <stdio.h>
#include <conio.h>
using namespace std;

int menu();

enum type { pass = 0, cargo = 1 };

struct vagon {
	int number = 0;
	enum type aType;
};


struct train {
	vagon* first;
	vagon* last;
};

//template <typename T>
struct Stack {
	vagon array[10];
	int top = -1;
	//T* array;
	//int n = 0;

	//Stack() {}

	/*Stack(int n) {
		this->array = new T[n];
	}*/

	bool isEmpty() {
		if (top == -1)return true;
		return false;
	}

	/*~Stack() {
		delete[]this->array;
	}*/
	vagon* peek()
	{
		return &array[top];
	};
	void push(vagon& v)
	{
		array[++top] = v;
	};
	vagon* pop()
	{
		return &array[top--];
	};
};

void TrainSort(Stack& Train, Stack& Pass, Stack& Cargo) {
	while (!Train.isEmpty()) {
		if (Train.peek()->aType == pass)Pass.push(*Train.pop());
		else Cargo.push(*Train.pop());
	}
}

void StackPrint(Stack stack) {
	int i = 1;
	while (!stack.isEmpty()) {
		cout << "Vagon #" << i << ": ";
		cout << "Number " << stack.peek()->number << " ";
		if (stack.peek()->aType == 0)cout << "Passenger" << endl;
		else cout << "Cargo" << endl;
		stack.pop();
		++i;
	}
	system("pause");
}

void VagonMaker(Stack& stack, vagon*& mas, int k)
{
	system("cls");
	ofstream file("Vagons.bin", ios::binary);
	int key = 0;
	for (int i = 0; i < k; ++i) {
		cout << "Vagon #" << i + 1 << endl;
		mas[i].number = i + 1;
		cout << "Enter type of Vagon:\n0 --> Passenger\n1 --> Cargo\n";
		cin >> key;
		switch (key) {
		case 0:mas[i].aType = pass; break;
		case 1:mas[i].aType = cargo; break;
		}
		cin.clear();
		stack.array->aType = mas[i].aType;
		file.write((char*)& mas[i], sizeof(vagon));
		system("cls");
	}
	file.close();
	return;
}

int main()
{
	Stack Train, Pass, Cargo;

	int key = 0;

	bool isRunning = 1;
	while (isRunning) {
		key = menu();
		switch (key) {
		case 0: {
			cout << "There are 10 vagons\n";
			vagon* mas = new vagon[10];
			VagonMaker(Train, mas, 10);
			for (int i = 0; i < 10; ++i)cout << mas[i].aType << endl;
			StackPrint(Train);
			break;
		}
		case 1: {
			ifstream f("Vagons.bin", ios::binary);
			for (int i = 0; i < 10; ++i) {
				f.read((char*)& Train.array[i], sizeof(vagon));
				Train.push(Train.array[i]);
			}
			StackPrint(Train);
			TrainSort(Train, Pass, Cargo);
			system("cls");
			cout << "Passenger train:\n";
			StackPrint(Pass);
			cout << "\nCargo train:\n";
			StackPrint(Cargo);
			f.close();
			break;
		}
		case 2:isRunning = 0;
		}
	}

	return 0;
}


int menu()
{
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 3) % 3;
		if (key == 0) cout << "-> Create general train" << endl;
		else  cout << "   Create general train" << endl;
		if (key == 1) cout << "-> Sort train" << endl;
		else  cout << "   Sort train" << endl;
		if (key == 2) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}