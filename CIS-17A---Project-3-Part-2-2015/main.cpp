#pragma once
#include "Folder.h"
#include <iostream>
using namespace std;
void DisplayMenu(shared_ptr<Folder> currentFolder, shared_ptr<Folder> parent);
void AddFileMenu(shared_ptr<Folder> currentFolder);
void AddFolderMenu(shared_ptr<Folder> currentFolder);
shared_ptr<Folder> NavigateToFolder(shared_ptr<Folder> currentFolder);
void SearchFileMenu(shared_ptr<Folder> currentFolder);

int main()
{
	const auto BASE = "Root";
	auto currentFolder = make_shared<Folder>(BASE);
	auto parentFolder = make_shared<Folder>();
	parentFolder = nullptr;
	int choice = 0;
	while (choice != -1) {
		DisplayMenu(currentFolder, parentFolder);
		cin >> choice;
		switch (choice)
		{
		case 1: {
			system("cls"); cout << "Contents of " << currentFolder->getName()
			<< currentFolder->ListContents() << endl; system("pause");
			break;
		}
		case 2: AddFileMenu(currentFolder); break;
		case 3: {
			auto newcurrent = NavigateToFolder(currentFolder); 
			parentFolder = currentFolder;
			currentFolder = newcurrent;
			cout << endl << "Now in folder " << newcurrent->getName() << "!";
			break;
		}
		case 5: SearchFileMenu(currentFolder); break;
		case 4: AddFolderMenu(currentFolder); break;
		case 6: {
			if (parentFolder != nullptr && currentFolder->getName() != BASE) {
				currentFolder = parentFolder;
				if (currentFolder->getName() == BASE)
				{
					parentFolder = nullptr;
				}
				cout << endl << "Now in folder " << currentFolder->getName() << "!";
			}
			break;
		}
		default: choice = -1; break;
		}
	}
	system("pause");
}

shared_ptr<Folder> NavigateToFolder(shared_ptr<Folder> currentFolder) 
{
	cout << "Folder Name: ";
	string name;
	cin >> name;
	cin.ignore();

	auto folder = currentFolder->FindFolder(name);
	return folder;
}

void DisplayMenu(shared_ptr<Folder> currentFolder, shared_ptr<Folder> parent)
{
	system("cls");
	cout << "Now in " << currentFolder->getName() << endl;
	cout << "*****************************************" << endl;
	cout << "1) List folder contents" << endl;	
	cout << "2) Add file to folder" << endl;
	cout << "3) Open" << endl;
	cout << "4) Add sub folder" << endl;
	cout << "5) Search For File" << endl;
	if (parent != nullptr) {
		cout << "6) Return to [" << parent->getName() << "]"<< endl;
	}
	
}

void AddFileMenu(shared_ptr<Folder> currentFolder)
{
	system("cls");
	cout << "Enter new file name: ";
	string name;
	cin >> name;
	cin.ignore();

	auto newFile = make_shared<File>(name);
	currentFolder->AddFile(newFile);
}

void AddFolderMenu(shared_ptr<Folder> currentFolder)
{
	system("cls");
	cout << "Enter new folder name: ";
	string name;
	cin >> name;
	cin.ignore();

	auto newFolder = make_shared<Folder>(name);
	currentFolder->AddFolder(newFolder);
}

void SearchFileMenu(shared_ptr<Folder> currentFolder)
{
	system("cls");
	cout << "Enter file name: ";
	string name;
	cin >> name;
	cin.ignore();

	auto result = currentFolder->FindFile(name);
	if (result != nullptr)
	{
		cout << "File Found: " << result->getName()<< endl;
		
	}
	else
	{
		cout << "File Not Found " << endl;
	}
	system("pause");
}