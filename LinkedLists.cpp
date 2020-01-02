#include <iostream>
#include <string.h>
using namespace std;

//struct for singly linked list nodes
typedef struct SLL_NODE{
	int val;
	struct SLL_NODE *next;
}SLL_NODE;

//struct for doubly linked list nodes
typedef struct DLL_NODE{
	int val;
	struct DLL_NODE *next, *prev;
}DLL_NODE;

class SLL //singly linked list
{

public:
	SLL_NODE *head, *tail;

	SLL() //default constructor
	{
		head = NULL;
		tail = NULL;
	}

	void add(int x) //adds values to the list
	{
		SLL_NODE *temp;
		temp = new SLL_NODE;

		temp->val = x;
		temp->next = head;
		head = temp;

		return;
	}

	//This does the same thing as add, but we were told to write it anyway
	void add_to_front(int x) //adds to the front of the list 
	{
		SLL_NODE *curr = new SLL_NODE; //allocates memory for new node

		//stores the value and sets head as the next pointer
		curr->val = x;
		curr->next = head;

		head = curr;  //makes head the newly added node
	}

	void remove(int x) //removes value from the list
	{
		SLL_NODE *curr, *prev;

		curr = head;

		while(curr->val != x && curr != NULL)
		{
			prev = curr;
			curr = curr->next;
		}

		if(curr == head)  //deleting first node
		{
			head = head->next;
			delete curr;
		}

		else if(curr != NULL)  //not at the end of the list
		{
			prev->next = curr->next;
			delete curr;
		}
		
		else //no more instances of the value are in the list
			return;
	}
	void remove_after(int x) //removes the node after value
	{
		SLL_NODE *curr, *next, *temp; 

		curr = head; //starts at the beginning of the list

		while(curr->next != NULL) //to check for multiple instances
		{
			while(curr->val != x && curr->next != NULL)  //finds the value
			{
				curr = curr->next;
			}

			if(curr == head) //removing after first node
			{
				next = curr->next;
				curr->next = next->next;
				head = curr;
				curr = curr->next;  //moves current to the nexr node
				delete next;
			}
			
			else if(curr->next != NULL) //removing from the middle and end
			{
				next = curr->next;
				curr->next = next->next;
				if(curr->next != NULL)
					curr = curr->next;  //moves current to the next node if there is one
				delete next;
			}
		}

		return; //value at the end of the list, or not in the list
	}

	int max()  //finds max value
	{
		int maximum;
		SLL_NODE *curr;

		curr = head->next;
		maximum = head->val;

		while(curr != NULL) //goes to the end of the list
		{
			if(curr->val > maximum)  //updates max if necessary
				maximum = curr->val;

			curr = curr->next;
		}
		return maximum;  //returns max
	}

	int recursive_max(int key, SLL_NODE *curr) //finds max recusively
	{
		if(curr->val > key) //updates the key if it is less than current nodes value
			key = curr->val;
		
		if(curr->next == NULL) //returns the max once the last node is checked
			return key;
		else
			return SLL::recursive_max(key, curr->next);  //checks the next node
	}

	void move_to_front(char input[]) //moves duplicates to the front
	{
		for(int i=0; i<strlen(input); i++)
		{
			if(SLL::search((int)input[i]) == 0) //letter not in list
				SLL::add((int)input[i]); //adds to the list
			else  //duplicate letter
			{
				//prints the list, then removes the letter and adds it to the front before printing again
				SLL::print_charList(); 
				SLL::remove((int)input[i]);
				SLL::add_to_front((int)input[i]);
				SLL::print_charList();
			}
		}
		return;
	}
	int search(int x)  //searches the list for value x, returns 1 if found
	{
		SLL_NODE *curr = head;

		while(curr != NULL)
		{
			if(x == curr->val)
				return 1;
			else
				curr = curr->next;
		}
		return 0;
	}

	void print_list() //prints the list
	{
		SLL_NODE *curr = head;

		while(curr != NULL)
		{
			cout<< curr->val;
			if(curr->next != NULL)
				cout<<", ";
			curr = curr->next;
		}
		cout<<endl;
	}

	void print_charList()  //prints the list in characters
	{
		SLL_NODE *curr = head;

		while(curr != NULL)
		{
			cout<< (char)(curr->val);
			if(curr->next != NULL)
				cout<<", ";
			curr = curr->next;
		}
		cout<<endl;
	}

	void delete_list() //deletes the list
	{
		SLL_NODE *prev;

		while(head != NULL)
		{
			prev = head;
			head = head->next;
			delete prev;
		}
	}
};

class DLL //double linked list
{
public:
	DLL_NODE *head; //sentinel for the start of the list
	DLL_NODE *tail;  //sentinel for the end of the list

	DLL() //default constructor
	{
		head = new DLL_NODE;
		tail = new DLL_NODE;
		tail->prev = head;
		head->next = tail;
		head->prev = NULL;
		tail->next = NULL;
	}

	void add(int x) //adds values to the list
	{
		DLL_NODE *temp = new DLL_NODE;

		temp->val = x;

		head->next->prev = temp;
		temp->next = head->next;
		temp->prev = head;
		head->next = temp;	
	}

	void remove(int x)  //removes value from the list
	{
		DLL_NODE *curr, *temp;

		curr = head->next;

		while(curr->val != x && curr != tail)
		{
			curr = curr->next;
		}

		if(curr != tail)
		{
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			delete curr;
		}
		
		else
			return;
	}
	void remove_after(int x) //removes the node after value
	{
		DLL_NODE *curr, *next;

		curr = head->next;

		while(curr->next != tail)
		{
			while(curr->val != x && curr->next != tail)
			{
				curr = curr->next;
			}

			if(curr->next != tail)
			{
				next = curr->next;
				curr->next = next->next;
				next->next->prev = curr;
				curr = curr->next;
				delete next;
			}
		}
		
		return;
	}

	int max()  //finds max value
	{
		int maximum;
		DLL_NODE *curr;

		curr = head->next;
		maximum = curr->val;

		curr = curr->next;
		while(curr->next != tail) //goes to the end of the list
		{
			if(curr->val > maximum)  //updates max if necessary
				maximum = curr->val;

			curr = curr->next;
		}
		return maximum;  //returns max
	}
	int recursive_max(int key, DLL_NODE *curr) //finds max recusively
	{
		if(curr->val > key) //updates the key if it is less than current nodes value
			key = curr->val;

		if(curr->next == tail) //returns the max once the last node is checked
			return key;

		else
			return DLL::recursive_max(key, curr->next);  //checks the next node
	}
	int search(int x) //searches for the value
	{
		DLL_NODE *curr = head->next;

		while(curr != tail)
		{
			if(x == curr->val)  //returns 1 if the value is found
				return 1;
			else
				curr = curr->next;
		}
		return 0;  //otherwise returns 0
	}

	void move_to_front(char input[]) //moves duplicates to the front
	{

		for(int i=0; i<strlen(input); i++)
		{
			if(DLL::search((int)input[i]) == 0) //letter not in list
				DLL::add((int)input[i]); //adds to the list
			else  //duplicate letter
			{
				//prints the list, then removes the letter and adds it to the front before printing again
				DLL::print_charList(); 
				DLL::remove((int)input[i]);
				DLL::add((int)input[i]);
				DLL::print_charList();
			}
		}
		return;
	}

	void print_list() //prints the list
	{
		DLL_NODE *curr = head->next;

		while(curr != tail)
		{
			cout<< curr->val;
			if(curr->next != tail)
				cout<<", ";
			curr = curr->next;
		}
		cout<<endl;
	}

	void print_charList()  //prints the list in characters
	{
		DLL_NODE *curr = head->next;

		while(curr != tail)
		{
			cout<< (char)(curr->val);
			if(curr->next != tail)
				cout<<", ";
			curr = curr->next;
		}
		cout<<endl;
	}

};




int main()
{
	int data[] = {1, 10, 15, 50, 2, 11, 100, 33, 22};
	int size = 9;

	SLL singly_list;

	//creating the list
	for(int i=0; i<size; i++)
	{
		singly_list.add(data[i]);
	}

	cout<<"Singly Linked List: "<<endl<<endl;

	/////////////////////////////////////////////////////
	//Question 1
	/////////////////////////////////////////////////////

	// Remove from the middle of the list 
	singly_list.print_list();
	singly_list.remove_after(15);
	singly_list.print_list();

	// Remove from the start of the list 
	singly_list.remove_after(1);
	singly_list.print_list();

	// Remove from the end of the list 
	singly_list.remove_after(22);
	singly_list.print_list();

	////////////////////////////////////////////////////
	//Question 2
	////////////////////////////////////////////////////

	//find max
	cout<< "Max = " << singly_list.max() <<endl;

	///////////////////////////////////////////////////
	//Question 3
	///////////////////////////////////////////////////

	//find max recusively
	cout<<"Max = " << singly_list.recursive_max(0, singly_list.head) << endl;

	////////////////////////////////////////////////////
	//Question 4
	////////////////////////////////////////////////////

	//delete the old list
	singly_list.delete_list();

	//move to front using following string
	char input[] = "Hello CSE 2010";

	singly_list.move_to_front(input);
	singly_list.print_charList();

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	DLL doubly_list;

	for(int i=0; i<size; i++)
	{
		doubly_list.add(data[i]);
	}

	cout<<endl <<"Doubly Linked List:"<<endl<<endl;

	/////////////////////////////////////////////////////
	//Question 1
	/////////////////////////////////////////////////////

	// Remove from the middle of the list 
	doubly_list.print_list();
	doubly_list.remove_after(15);
	doubly_list.print_list();

	// Remove from the start of the list 
	doubly_list.remove_after(1);
	doubly_list.print_list();

	// Remove from the end of the list 
	doubly_list.remove_after(22);
	doubly_list.print_list();

	////////////////////////////////////////////////////
	//Question 2
	////////////////////////////////////////////////////

	//find max
	cout<< "Max = " << doubly_list.max() <<endl;

	///////////////////////////////////////////////////
	//Question 3
	///////////////////////////////////////////////////

	//find max recusively
	cout<<"Max = " << doubly_list.recursive_max(0, doubly_list.head->next) << endl;

	////////////////////////////////////////////////////
	//Question 4
	////////////////////////////////////////////////////

	DLL doubly_list2;

	//move to front using following string

	doubly_list2.move_to_front(input);
	doubly_list2.print_charList();

	return 0;


}
