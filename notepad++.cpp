#include<iostream>
#include<string>
#include<conio.h>
using namespace std;
class notepad {
	struct node {
		char ch;
		node* up, * down, * right, * left;
		node()
		{
			ch = '/0';
			up = down = right = left = NULL;
		}
	};
	int count, pageLayout;
	node* head, * current, * prev;
public:
	notepad()
	{
		head = current = prev = NULL;
		count = 1;
		pageLayout = 0;
	}
private:
	void func_ENTER()
	{
		if (count == 0)
		{
			while (current->right != NULL && current->ch != 13)
			{
				prev->down = current;
				current->up = prev;
				current = current->right;
				prev = prev->right;
			}
			count += 3;
		}
		else
		{
			if (current->left != NULL && current->left->ch == 13)
			{
				count++;
				if (count == 2)
					prev = head;
				else
				{
					while (prev->ch != 13)
					{
						prev = prev->right;
					}
					prev = prev->right;
				}
			}
			if (count > 1)
			{
				if (current->ch != 13 && prev->ch != 13)
				{
					prev->down = current;
					current->up = prev;
					prev = prev->right;
				}
			}
		}
	}
	void func_MoveCursor()
	{
		char ch = _getch();
		if ((int)ch == 75)
		{
			if (current->left != NULL)
			{
				current = current->left;
			}
		}
		else if ((int)ch == 77)
		{
			if (current->right != NULL)
			{
				current = current->right;
			}
		}
		else if ((int)ch == 72)
		{
			if (current->up != NULL)
			{
				current = current->up;
			}
		}
		else if ((int)ch == 80)
		{
			if (current->down != NULL)
			{
				current = current->down;
			}
		}
	}
	void print()
	{
		system("cls");
		cout << "\t\t\t\t\tPRESS ESC KEY TO SHOW MENU!!!\n\n";
		node* p = head;
		while (p != NULL)
		{
			if ((int)p->ch == 13)
				cout << endl;
			else
				cout << p->ch;
			if (p == current)
				cout << "|";
			p = p->right;
		}
	}
	void func_Backspace()
	{
		if (current == head)
		{
			if (current->right != NULL && current->ch != 13)
			{
				node* temp = current;
				while (temp->right != NULL && temp->ch != 13)
				{
					swap(temp->ch, temp->right->ch);
					if (temp->ch == 13)
					{
						temp = temp->right;
						break;
					}
					temp = temp->right;
				}
				if (temp->right != NULL)
				{
					temp->left->right = temp->right;
					temp->right->left = temp->left;
				}
				else
				{
					temp->left->right = NULL;
				}
				delete temp;
			}
			else if (current->ch == 13 && current->right != NULL)
			{
				pageLayout = 1;
				node* temp = current->right;
				temp->up = NULL;
				temp->left = NULL;
				head = temp;
				prev = temp;
				temp = temp->right;
				while (temp->right != NULL && temp->left->ch != 13)
				{
					pageLayout++;
					temp->up = NULL;
					temp = temp->right;
				}
				while (prev->down->down != NULL)
					prev = prev->down;
				temp = current;
				current = head;
				delete temp;
			}
			else if (current->right == NULL)
			{
				head = NULL;
				prev = NULL;
				count = 1;
				delete current;
				current = NULL;
			}
		}
		else if (current->left != NULL && current->right != NULL)
		{
			if (current->ch == 13 && current->right != NULL)
			{
				pageLayout = 1;
				node* temp = current;
				prev = current->left;
				while (prev->left != NULL && prev->left->ch != 13)
				{
					pageLayout++;
					prev->down = NULL;
					prev = prev->left;
				}
				prev->down = NULL;
				current = current->right;
				pageLayout++;
				while (current->right != NULL && current->ch != 13)
				{
					pageLayout++;
					current->up = current->down = NULL;
					current = current->right;
				}
				current->up = current->down = NULL;
				temp->left->right = temp->right;
				temp->right->left = temp->left;
				temp->up = temp->down = NULL;
				delete temp;
				if (current->right != NULL)
				{
					count = 0;
					current = current->right;
					func_ENTER();
				}
				else
				{
					count = 1;
					linkUp();
				}
			}
			else if (current->ch != 13 && current->right != NULL)
			{
				node* temp1 = current;
				current = current->left;
				while (temp1->right != NULL && temp1->right->ch != 13)
				{
					swap(temp1->ch, temp1->right->ch);
					temp1 = temp1->right;
				}
				if (temp1->right != NULL)
				{
					temp1->up = NULL;
					temp1->down = NULL;
					swap(temp1->ch, temp1->right->ch);
					temp1 = temp1->right;
					temp1->left->right = temp1->right;
					temp1->right->left = temp1->left;
					delete temp1;
				}
				else
				{
					temp1->left->right = NULL;
					node* t = temp1->up;
					if (t != NULL)
						t->down = NULL;
					delete temp1;
				}
			}
		}
		else
		{
			node* temp = current;
			if (temp->up != NULL)
				temp = temp->up;
			if (temp->down != NULL)
				temp->down = NULL;
			temp = current;
			current = current->left;
			current->right = NULL;
			delete temp;
		}
		pageLayout--;
	}
	void linkUp()
	{
		if (prev->up != NULL)
		{
			node* t = prev->up;
			while (prev->ch != 13 && t->ch != 13)
			{
				t->down = prev;
				prev->up = t;
				prev = prev->right;
				t = t->right;
			}
		}
	}
	void linking()
	{
		if (current->right->down != NULL && current->right->up == NULL)
		{
			node* ptr = current;
			node* t = current->right->down;
			while (current->ch != 13 && t->ch != 13)
			{
				current->down = t;
				t->up = current;
				current = current->right;
				t = t->right;
			}
			if (current->ch != 13 && t->ch == 13)
			{
				node* temp = current;
				while (temp->right != NULL && temp->ch != 13)
				{
					temp->down = NULL;
					temp = temp->right;
				}
			}
			else if (current->ch == 13 && t->ch != 13)
			{
				while (t->right != NULL && t->ch != 13)
				{
					t->up = NULL;
					t = t->right;
				}
			}
			current = ptr;
		}
		else if (current->right->up != NULL && current->right->down != NULL)
		{
			node* ptr = current;
			node* t1 = current->right->up, * t2 = current->right->down;
			while (current->ch != 13 && (t1->ch != 13 || (t2->ch != 13 && t2->right != NULL)))
			{
				if (t1->ch != 13)
				{
					t1->down = current;
					current->up = t1;
					t1 = t1->right;
				}
				if (t2->ch != 13)
				{
					t2->up = current;
					current->down = t2;
					if (t2->right != NULL)
						t2 = t2->right;
				}
				current = current->right;
			}
			if (current->ch != 13 && t1->ch == 13 && t2->right == NULL)
			{
				node* t = current->right;
				while (t->ch != 13)
				{
					t->up = t->down = NULL;
					t = t->right;
				}
			}
			else if (current->ch != 13 && t1->ch == 13 && t2->ch == 13)
			{
				node* t = current;
				while (t->right != NULL && t->ch != 13)
				{
					t->up = t->down = NULL;
					t = t->right;
				}
			}
			else if (t1->ch != 13 && current->ch == 13 && t2->ch == 13)
			{
				while (t1->right != NULL && t1->ch != 13)
				{
					t1->down = NULL;
					t1 = t1->right;
				}
			}
			else if (t2->right != NULL && t2->ch != 13 && current->ch == 13 && t2->ch == 13)
			{
				while (t2->right != NULL && t2->ch != 13)
				{
					t2->up = NULL;
					t2 = t2->right;
				}
			}
			current = ptr;
		}
		else if (current->right->up != NULL && current->right->down == NULL)
		{
			node* ptr = current;
			node* t = current->right->up;
			while (current->right != NULL && current->ch != 13 && t->ch != 13)
			{
				current->up = t;
				t->down = current;
				current = current->right;
				t = t->right;
			}
			if (current->ch != 13 && t->ch == 13)
			{
				node* temp = current;
				while (temp->right != NULL && temp->ch != 13)
				{
					temp->up = NULL;
					temp = temp->right;
				}
			}
			else if (current->ch == 13 && t->ch != 13)
			{
				while (t->right != NULL && t->ch != 13)
				{
					t->down = NULL;
					t = t->right;
				}
			}
			current = ptr;
		}
	}
	void swap(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}
	bool menu()
	{
		system("cls");
		cout << "\t\t\t\t\tPRESS ESC KEY TO QUIT NOTEPAD!!!\n\n";
		cout << "1:FIND\n2:UNDO\n3:REDO\n4:BACK\n";
		char s = _getch();
		if ((int)s == 27)
			return false;
		else
		{
			static char temp = '/0';
			while (s != '4')
			{
				if (s == '1')
				{
					string str;
					cout << "ENTER WORD TO FIND:";
					getline(cin, str);
					int l = str.length(), i = 0;
					node* ptr = head;
					if (ptr == NULL)
					{
						cout << "WORD NOT FOUND PRESS ENTER TO CONTINUE\n";
						system("pause>0");
					}
					else
					{
						while (ptr != NULL && l >= 0)
						{
							if (ptr->ch == str[i])
							{
								l--;
								i++;

							}
							else
							{
								l = str.length();
								i = 0;
							}
							if (l == 0)
							{
								current = ptr;
								cout << "WORD FOUND PRESS ENTER TO CONTINUE\n";
								system("pause>0");
								return true;
							}
							ptr = ptr->right;
						}
					}
				}
				else if (s == '2')
				{
					if (head == NULL)
						return true;
					else
					{
						int count = 0;
						while (current->right != NULL)
						{
							current = current->right;
						}
						while (current->left != NULL)
						{
							count++;
							current = current->left;
						}
						while (current->right != NULL)
						{
							current = current->right;
						}
						if (count >= 10)
						{
							for (int i = 0; i < 10; i++)
							{
								if (i == 9)
									temp = current->ch;
								func_Backspace();
							}
						}
						return true;
					}
				}
				else if (s == '3')
				{
					node* pt = new node;
					pt->ch = temp;
					while (current->right != NULL)
						current = current->right;
					pt->left = current;
					current->right = pt;
					if (current->up != NULL && current->up->right != NULL && current->right->ch != 13)
						current->up->right->down = pt->up;

					return true;
				}
				system("cls");
				cout << "\t\t\t\t\tPRESS ESC KEY TO QUIT NOTEPAD!!!\n\n";
				cout << "1:FIND\n2:UNDO\n3:REDO\n4:BACK\n";
				s = _getch();
				if ((int)s == 27)
					return false;
			}
		}
		return true;
	}
public:
	void insertion()
	{
		bool check = true;
		cout << "\t\t\t\t\tPRESS ESC KEY TO SHOW MENU!!!\n\n";
		while (check == true)
		{
			char c;
			if (pageLayout <= 70)
				c = _getch();
			else
			{
				c = '\n';
				pageLayout = 0;
			}
			if (c == 27)
			{
				check = menu();
				if (check == false)
					break;
				print();
				continue;
			}
			node* p = new node;
			p->ch = c;
			if (head == NULL)
			{
				current = head = prev = p;
			}
			else if (p->ch != -32 && p->ch != 8)
			{
				if (current->right == NULL)
				{
					p->left = current;
					current->right = p;
					current = p;
				}
				else if (current->right != NULL && current->left != NULL)
				{
					p->right = current->right;
					current->right->left = p;
					p->left = current;
					current->right = p;
					current = p;
					print();
					linking();
					continue;
				}
			}
			if (p->ch != -32 && p->ch != 8)
				func_ENTER();
			else if (p->ch == 8)
				func_Backspace();
			else if (p->ch == -32)
				func_MoveCursor();
			print();
			if (p->ch != -32 && p->ch != 8)
				pageLayout++;
		}
	}

};
int main()
{
	notepad* note = new notepad;
	note->insertion();
	system("pause>0");
}
