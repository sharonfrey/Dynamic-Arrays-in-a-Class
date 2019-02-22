/* 
Objectives:
1. Read the contents of a data file one record at a time in a dynamic array       
2. Process the data that was read from the data file one record at a time, into a dynamic array       
3. Print the records in a dynamic array to a datafile using an ofstream object      
4.  Use the operator new to allocate memory for a dynamic array      
5.  Use the operator delete to de-allocate the memory allocated by the new (basically, making previously used memory available for use again)       
6.  Copy the content of one dynamic array into another dynamic array (basically, copying memory from one location to another)       
7. Be able to use the fstream library      
8. Be able to use a dynamic array of record records       
9. Be able to use an ifstream object       
10. Be able to use an ofstream object
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;


class call_record
{
public:
	string firstname;
	string lastname;
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};


void Initialize(call_record *& call_DB, int & count, int & size);
bool Is_empty(const int count); //inline implementation
bool Is_full(const int count, int size);//inline implementation
int Search(const call_record *call_DB, const int count, const string key);//returns location if item in listl; otherwise return -1
void Add(call_record * &call_DB, int & count, int & size, const string key); //adds item inorder to the list
void Remove(call_record *call_DB, int & count, const string key); //removes an item from the list
void Double_size(call_record * &call_DB, int & count, int & size);
void Process(call_record *call_DB, const int & count);
void Print(const call_record *call_DB, int & count); //prints all the elements in the list to the screen
void Destroy_call_DB(call_record * &call_DB); //de-allocates all memory allocate to call_DB by operator new.



/************************************************************************************************************************************/
//Name: Initialize
//Precondition: the call record is empty and the count is set to 0
//Postcondition: data from the txt file is printed into the call record, if the record becomes full it doubles
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
void Initialize(call_record * & call_DB, int & count, int & size)
{
	//input file stream
	ifstream in;
	in.open("callstats_data.txt");

	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
	}
	else
	{
		//loop to input data into the array at count limited to the amout of data in the input file
		while (!in.eof())
		{
			if (Is_full(count, size))
			{
				Double_size(call_DB, count, size);
			}
			in >> call_DB[count].firstname;
			in >> call_DB[count].lastname;
			in >> call_DB[count].cell_number;
			in >> call_DB[count].relays;
			in >> call_DB[count].call_length;

			count++;
		}
	}

	//close input file stream
	in.close();
}

/***********************************************************************************************************************************/
//Name: Is_empty
//Precondition: takes in the count of the call record
//Postcondition: returns true if count = 0 and false if it anything else
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/

//ONE WAY TO MAKE A FUNCTION INLINE IS TO PUT THE KEYWORD "inline" in from of the 
//FUNCTION HEADER AS SHOWN BELOW:
inline bool Is_empty(const int count)
{
	if (count == 0)
	{
		return true;
	}
	return false;
}

//ONE WAY TO MAKE A FUNCTION INLINE IS TO PUT THE KEYWORD "inline" in from of the 
//FUNCTION HEADER AS SHOWN BELOW:
/**********************************************************************************************************************************/
//Name: Is_full 
//Precondition: takes in the count and the size of the call record
//Postcondition: returns true if the count and size are equal to eachother and false if anything else
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
inline bool Is_full(const int count, int size)
{
	if (count == size)
	{
		return true;
	}
	return false;
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: takes in the key and checks it with the cell numbers in the call record
//Postcondition: returns the location of the cell number that is the same as key
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int Search(const call_record *call_DB, const int count, const string key)
{
	int i;
	for (i = 0; i < count; i++)
	{
		if (call_DB[i].cell_number == key)
		{
			return i;
		}
	}
	return -1;
}

/*********************************************************************************************************************************/
//Name: Add
//Precondition: takes in the key and prompt the user for data to input for that key
//Postcondition: adds in a new record in the call record
//Decription: add key to call_DB; if call_DB is full, double_size is called to increase the size of call_DB.
/********************************************************************************************************************************/
void Add(call_record * &call_DB, int & count, int & size, const string key)
{
		if (Is_full(count, size))
		{
			Double_size(call_DB, count, size);
		}
		call_DB[count].cell_number = key;

		cout << "Enter first name:  ";
		cin >> call_DB[count].firstname;
		cout << "Enter last name:  ";
		cin >> call_DB[count].lastname;
		cout << "Enter relays:  ";
		cin >> call_DB[count].relays;
		cout << "Enter call length:  ";
		cin >> call_DB[count].call_length;

		Process(call_DB, count);

		count++;
}

/********************************************************************************************************************************/
//Name: Remove
//Precondition: takes in the key and searches for records matching 
//Postcondition: all records with the same key are deleted from the call record
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
void Remove(call_record *call_DB, int & count, const string key)
{
	if (!Is_empty(count))
	{
		int location = Search(call_DB, count, key);
		while (location != -1)
		{
			for (int i = location; i < count - 1; i++)
			{
				call_DB[i] = call_DB[i + 1];
			}

			count--;
			location = Search(call_DB, count, key);
		}
	}
}

/******************************************************************************************************************************/
//Name: Double_Size
//Precondition: takes in the size and the call record
//Postcondition: doubles the size of the call record
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void Double_size(call_record * &call_DB, int & count, int & size)
{
	size = size * 2;
	call_record *temp = new call_record[size];
	for (int i = 0; i < count; i++)
	{
		temp[i] = call_DB[i];
	}
	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: Process
//Precondition: takes in the relays and the call length of each call record
//Postcondition: calculates the rest of the slots and fills in the call record
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void Process(call_record *call_DB, const int & count)
{
	int i;

	//loop to process each record in the array upto where count ends
	for (i = 0; i < count; i++)
	{
		//to find the net cost at array point i
		call_DB[i].net_cost = call_DB[i].relays / 50.0*0.4*call_DB[i].call_length;

		//find the tax rate at array point i
		if (call_DB[i].relays >= 0 && call_DB[i].relays <= 5)
		{
			call_DB[i].tax_rate = 0.01;
		}
		else if (call_DB[i].relays >= 6 && call_DB[i].relays <= 11)
		{
			call_DB[i].tax_rate = 0.03;
		}
		else if (call_DB[i].relays >= 12 && call_DB[i].relays <= 20)
		{
			call_DB[i].tax_rate = 0.05;
		}
		else if (call_DB[i].relays >= 21 && call_DB[i].relays <= 50)
		{
			call_DB[i].tax_rate = 0.08;
		}
		else if (call_DB[i].relays > 50)
		{
			call_DB[i].tax_rate = 0.12;
		}

		//find the call tax at array point i
		call_DB[i].call_tax = (call_DB[i].net_cost * call_DB[i].tax_rate);

		//find the total cost at array point i
		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;
	}
}


/****************************************************************************************************************************/
//Name: Print
//Precondition: takes in the call recod and the count
//Postcondition: prints all the information in the call recod on screen and in a file
//Decription: prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
void Print(const call_record *call_DB, int & count)
{

	int i;

	//output file stream
	ofstream out;
	out.open("weekly_call_info.txt");

	//magic formula at the hundreths
	out.setf(ios::showpoint);
	out.precision(2);
	out.setf(ios::fixed);

	//print everything out on screen
	for (i = 0; i < count; i++)
	{
		cout << call_DB[i].firstname << "  ";
		cout << call_DB[i].lastname << "  ";
		cout << call_DB[i].cell_number << "  ";
		cout << call_DB[i].relays << "   ";
		cout << call_DB[i].call_length << "   ";
		cout << call_DB[i].net_cost << "   ";
		cout << call_DB[i].tax_rate << "   ";
		cout << call_DB[i].call_tax << "   ";
		cout << call_DB[i].total_cost << endl;
	}

	//print out all the elements of the call record into file output upto count in the array
	for (i = 0; i < count; i++)
	{
		out << call_DB[i].firstname << "  ";
		out << call_DB[i].lastname << "  ";
		out << call_DB[i].cell_number << "  ";
		out << call_DB[i].relays << "   ";
		out << call_DB[i].call_length << "   ";
		out << call_DB[i].net_cost << "   ";
		out << call_DB[i].tax_rate << "   ";
		out << call_DB[i].call_tax << "   ";
		out << call_DB[i].total_cost << endl;
	}

	//close output file stream
	out.close();
}

/****************************************************************************************************************************/
//Name: Destroy_call_DB
//Precondition: takes in the call record
//Postcondition: erases the recod and sets it to 0
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program is exited.
/***************************************************************************************************************************/
void Destroy_call_DB(call_record * &call_DB)
{
	delete[] call_DB;
	call_DB = 0;
}



int main()
{
	int size = 5; 
	int count = 0;
	call_record *call_DB = new call_record[size];

	//testing is empty function
	if (Is_empty(count))
	{
		cout << "call_DB is empty" << endl << endl;
	}		

	//testing initialize, double size, is full, process, and print
	cout << endl << "Printing out original call record:  " << endl << endl;
	Initialize(call_DB, count, size);
	Process(call_DB, count);
	Print(call_DB, count);

	//testing add, is full, process, and print
	cout << endl << endl << "Adding in two new records:  " << endl << endl;
	string key = "9544567891";
	Add(call_DB, count, size, key);
	key = "5618886767";
	Add(call_DB, count, size, key);
	cout << endl;
	Print(call_DB, count);

	//testing search, is empty, remove, and print
	cout << endl << endl << "Removing records with 3 different keys:  " << endl << endl;
	key = "9546321555";
	Remove(call_DB, count, key);
	key = "5617278899";
	Remove(call_DB, count, key);
	key = "9546321555";
	Remove(call_DB, count, key);
	Print(call_DB, count);

	//testing destroy call db
	Destroy_call_DB(call_DB);
	if (call_DB == 0)
	{
		cout << endl << endl << "End of Program" << endl;
	}
	return 0;
}


