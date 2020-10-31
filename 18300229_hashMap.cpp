// 18300229_hashMap.cpp -- P2.2 Tabla Hash
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <stdio.h>
using namespace std;

template <class T>
class list	//Contains the activities of the list.
{
	class Node //Creates or nodes.
	{
	public:
		T data;  //Holds a generic data value.
		Node* link; //Points to the next element.
		Node()
		{
			link = nullptr;
		}
	};

	Node* beginning;

public:
	list()
	{
		beginning = nullptr;
	}

	void addItem(T data) //Adds an element to the list.
	{
		Node* newNode, * cursor;
		newNode = new Node();
		newNode->data = data;

		if (beginning == nullptr)
			beginning = newNode;
		else
		{
			cursor = beginning;
			while (cursor->link) //while next link is not empty.
				cursor = cursor->link;
			cursor->link = newNode;
		}
	}
	T getValue(int index)	//returns value of data in a certain position.
	{
		if (count() > index)
		{
			Node* cursor = beginning;
			for (int i = 0; i < index; i++)
				cursor = cursor->link;
			return cursor->data;
		}
		return beginning->data;
	}

	int getPosition(T searchValue) //Returns the position where data was found.
	{
		for (int pos = 0; pos < count(); pos++) //Search.
		{
			if (getValue(pos) == searchValue)
				return pos;
		}
		return -1;
	}

	int count() //Counts the elements in the list.
	{
		int elementCount = 0;
		Node* cursor = beginning;
		while (cursor)
		{
			elementCount++;
			cursor = cursor->link;
		}
		return elementCount;
	}

	void updateData(T valueToUpdate) //Changes the value of an element in the list.
	{
		int valuePos = getPosition(valueToUpdate);

		if (valuePos > -1) //If valuePos exists in the list.
		{
			int valueToReplace;
			Node* cursor = beginning;
			cout << "Input the updated value: "; cin >> valueToReplace;
			for (int i = 0; i < valuePos; i++)
				cursor = cursor->link;
			cursor->data = valueToReplace;

			cout << "\n>Value replaced successfully." << endl;
		}
		else
			cout << "\n>No matching values." << endl;
	}

	bool deleteParticular(int dataPos) //Deletes a particular acoording to it's position.
	{
		//int dataPos = getPosition(valueToDelete);

		if (dataPos > -1) //If element was found, execute erase function.
		{
			Node* erase = beginning,
				* prevElement = nullptr;

			if (dataPos == 0) //If first element is deleted.
			{
				beginning = beginning->link;
				delete erase;
			}
			else
			{
				for (int i = 0; i < dataPos; i++)
				{
					prevElement = erase;
					erase = erase->link;
				}
				prevElement->link = erase->link;
				delete erase;
			}
			return true; //Value found and deleted sucessfully
		}
		else
			return false; //Value not found.
	}

	void deleteAll() //Clears list.
	{
		Node* erase;

		while (beginning) //Deletes from first to last while link not null.
		{
			erase = beginning;
			beginning = beginning->link;
			delete erase;
		}
	}

	bool checkEmpty() //Checks if count is 0.
	{
		if (count() == 0)
		{
			cout << "List is empty." << endl;
			return true;
		}
		return false;
	}
};

struct Coordinate
{
public:
	int x, y;
	Coordinate()
	{
		x = 0;
		y = 0;
	}
	Coordinate(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

template <class T>
class cHash				//Controller Class.
{
	int mbucketNum = 10;
	int encode(T uncodedStr)	//casts each character into int and returns the sum.
	{
		int code = 0;
		for (int i = 0; i < uncodedStr.size(); i++)
			code += (int)uncodedStr[i];
		return code;
	}
public:
	int getBucketNum()
	{
		return mbucketNum;
	}
	int getBucketPos(T uncodedStr)	//returns
	{
		int bucketPos = encode(uncodedStr) % mbucketNum;
		return bucketPos;
	}
	int allCount(list<T> linkedList[])
	{
		int countSum = 0;

		for (int i = 0; i < mbucketNum; i++)
		{
			countSum += linkedList[i].count();
		}
		return countSum;
	}
	Coordinate search(list<T> linkedList[], T searchQuery)
	{
		Coordinate point;

		point.y = getBucketPos(searchQuery);			//Gets row (bucket)
		point.x = linkedList[point.y].getPosition(searchQuery);		//Gets column

		return point;
	}
	bool erase(list<T> linkedList[], T searchQuery)
	{
		Coordinate elementCoord = search(linkedList, searchQuery); //Calls search function
		int row = elementCoord.y,
			column = elementCoord.x;

		return linkedList[row].deleteParticular(column); //delete particular returns bool value
	}
	bool checkEmpty(list<T> linkedList[])
	{
		if (allCount(linkedList) == 0)
			return true;
		return false;
	}
};

int main()
{
	cHash<string> hashMap;
	int bucketNum = hashMap.getBucketNum(); //Gets the array size from class.
	list<string>* bucket = new list<string>[bucketNum]; //Creates a size dynamic array with prev value.
	string itemValue;
	int bucketPos = 0;
	Coordinate elementCoord(0, 0);
	do
	{
		char choice = 0;
		system("cls");
		cout << "========Hash Map=========" << endl;

		do //Loop until correct input
		{
			cout << endl << "Choose an option" << endl;
			cout << "[1] Add data to the collection." << endl;
			cout << "[2] Count total elements" << endl;
			cout << "[3] Search element in the list" << endl;
			cout << "[4] Delete a particular element" << endl;
			cout << "[5] Show all elements in the list." << endl;
			cout << "[6] Encode data value." << endl;
			cout << "[7] Erase an element in the collection." << endl;
			cout << "[8] Delete everything" << endl;
			cout << "[9] Exit." << endl;
			cout << ">Answer: "; choice = _getch();
			system("cls");
		} while (choice < 49 or choice > 57); //ASCII from 1 to 9.

		switch (choice)
		{
		case '1':	//Add

			cout << endl << "*** Press <Left control Key> on your last the data input to finish filling. ***" << endl;
			cout << "*** Data input will automatically stop after 100 elements." << endl << endl;
			cout << "Fill the array: " << endl;
			for (int i = 0; (GetAsyncKeyState(VK_LCONTROL)) == false and i < 100; i++)
			{
				if ((GetAsyncKeyState(VK_LCONTROL)) == false)
				{
					cout << "Add element: ";
					getline(cin, itemValue);
					bucketPos = hashMap.getBucketPos(itemValue);
					bucket[bucketPos].addItem(itemValue);
				}
				GetAsyncKeyState; //Gets the current pressed key from the user.
			}
			break;

		case '2':	//Count
		{
			int allCount = hashMap.allCount(bucket);
			cout << "The total count of elements = " << allCount << endl;
		}
		break;

		case '3': //Search
			if (hashMap.checkEmpty(bucket))
			{
				cout << "Hash Map is empty." << endl;
				break;
			}
			cout << "Input the value of the element you wish to search: "; getline(cin, itemValue);
			elementCoord = hashMap.search(bucket, itemValue);
			if (elementCoord.x > -1) //If element was found
			{
				cout << "\nMatching element." << endl;
				cout << " (Y) Row (bucket) --> " << elementCoord.y + 1 << endl;	//add 1 to display a understandable position
				cout << " (X) Column --> " << elementCoord.x + 1 << endl;
			}
			else
				cout << "No matching element.";
			break;
		case '4': //Delete.
			if (hashMap.checkEmpty(bucket))
			{
				cout << "Hash Map is empty." << endl;
				break;
			}
			cout << "Input the value of the element you wish to erase: "; getline(cin, itemValue);
			{
				bool elementDeleted;
				elementDeleted = hashMap.erase(bucket, itemValue);
				(elementDeleted) ?
					cout << "Element found and deleted succesfully." << endl
					:
					cout << "No matching values." << endl;
			}
			break;
			//case '2':	//Search
			//	if (bucket.checkEmpty())
			//		break;
			//	cout << "Input the value of the element you wish to search: "; cin >> itemValue;
			//	(bucket.getPosition(itemValue) == -1) ?
			//		cout << "\nNo matches have been found.\n"
			//		:
			//		cout << "\n>Matching value found \n";
			//	break;

			//case '3': //Show Value
			//	if (bucket.checkEmpty())
			//		break;
			//	cout << "Input the position of the element you wish to search: "; cin >> searchPos;
			//	(searchPos > bucket.count() or searchPos <= 0) ?
			//		cout << "\n>Out of boundaries.\n"
			//		:
			//		cout << "\n>Matching value in that postion = " << bucket.getValue(searchPos - 1) << endl;
			//	break;

			//case '4': //Count
			//	if (bucket.checkEmpty())
			//		break;
			//	cout << "\nThe element count is = " << bucket.count() << " elements.\n";
			//	break;

			//case '5': //Show all items
			//	if (bucket.checkEmpty())
			//		break;
			//	for (int i = 0; i < bucket.count(); i++)
			//		cout << "Item [" << i + 1 << "] = " << bucket.getValue(i) << endl;
			//	break;

			//case '6': //Update
			//	if (bucket.checkEmpty())
			//		break;
			//	cout << "Input the value of the element you wish to encode: ";
			//	getline(cin, itemValue);
			//	cout << bucket.encode(itemValue);
			//	break;

			//case '7':	//Delete particular
			//	if (bucket.checkEmpty()) break;
			//	cout << "Input the value of the element you wish to delete: ";  cin >> itemValue;
			//	bucket.deleteParticular(itemValue);
			//	break;

			//case '8':	//Clear list
			//	if (bucket.checkEmpty())
			//		break;
			//	bucket.deleteAll();
			//	cout << "\n hashMap is now clear, all elements deleted successfully\n";
			//	break;

		case '9':	//Exit
			cout << endl << "Successfully exited the program.\n";
			return 0;
			break;
		}
		cout << endl;
		system("pause");
	} while (1);	//Never ending loop
}