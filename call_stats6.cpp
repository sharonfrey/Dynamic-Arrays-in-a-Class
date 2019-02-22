/*
Objectives:
1.  Develop and use an ADT’s to define a class to manage a dynamic array;       
2.  Use a default constructor to initialize the state of your class;       
3.  Use a destructor to de-allocate memory allocated using the new operator;
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

class call_class
{
public:
	call_class();
	~call_class(); //de-allocates all memory allocate to call_DB by operator new.
	bool is_empty(); //inline implementation
	bool is_full();//inline implementation
	int search(const string key);//returns location if item in listl; otherwise return -1
	void add(); //adds a call record to call_DB
	void remove(const string key); //removes an item from the list
	void double_size();
	void process();
	void print(); //prints all the elements in the list to the screen
private:
	int count;
	int size;
	call_record *call_DB;
};




/************************************************************************************************************************************/
//Name: default constructor
//Precondition: The object has not been initialize student_DB,count and size have not been initialized.
//Postcondition: All student data has been entered into student_DB; count and size contain the appropriate values
//Decription: Reads the data file of call information (cell number, relays and call length) into the dynamic array of call record, 
//call_DB. If the count because equal to the size the function double_size is called and the memory allocated to call_DB is doubled.
/************************************************************************************************************************************/
call_class::call_class()
{
	//input file stream
	ifstream in;
	in.open("callstats_data.txt");

	count = 0;
	size = 1;
	call_DB = new call_record[size];

	if (in.fail())
	{
		cout << "Input file did not open correctly" << endl;
	}
	else
	{
		//loop to input data into the array at count limited to the amout of data in the input file
		while (!in.eof())
		{
			if (is_full())
			{
				double_size();
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
//Name: is_empty
//Precondition: takes in the count of the call record
//Postcondition: returns true if count = 0 and false if it anything else
//Decription: returns true if call_DB is empty
/**********************************************************************************************************************************/
bool call_class::is_empty()
{
	if (count == 0)
	{
		return true;
	}
	return false;
}

/**********************************************************************************************************************************/
//Name: is_full 
//Precondition: takes in the count and the size of the call record
//Postcondition: returns true if the count and size are equal to eachother and false if anything else
//Decription: returns true if call_DB is full
/*********************************************************************************************************************************/
bool call_class::is_full()
{
	if (count == size)
	{
		return true;
	}
	return false;	
}

/**********************************************************************************************************************************/
//Name: search
//Precondition: Student_DB has been initialize and there is a valid value for key 
//Postcondition: Location of key in Student_DB is returned; otherwise -l is returned.
//Decription: locates key in call_DB if it is there; otherwise -1 is returned
/*********************************************************************************************************************************/
int call_class::search(const string key)
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
//Name: add
//Precondition: Add a student record toStudent_DB if it is not full.  Is it is full, Double_size is called and the the record is add
//Postcondition: Student records has been added to Student_DB
//Decription: adds a call_record to call_DB; if call_DB is full, double_size is called to increase the size of call_DB. The user 
//            is prompted to enter the firstname, lastname, cell number, relays and call length. 
/********************************************************************************************************************************/
void call_class::add()
{
	if (is_full())
	{
		double_size();
	}

	cout << "Enter first name:  ";
	cin >> call_DB[count].firstname;
	cout << "Enter last name:  ";
	cin >> call_DB[count].lastname;
	cout << "Enter a cell number:  ";
	cin >> call_DB[count].cell_number;
	cout << "Enter relays:  ";
	cin >> call_DB[count].relays;
	cout << "Enter call length:  ";
	cin >> call_DB[count].call_length;

	process();

	count++;
}

/********************************************************************************************************************************/
//Name: remove
//Precondition: Student_DB, and key have been initialized
//Postcondition: The student record the matches key has been removed
//Decription: remove key from call_DB if it is there.
/*******************************************************************************************************************************/
void call_class::remove(const string key)
{
	if (!is_empty())
	{
		int location = search(key);
		while (location != -1)
		{
			for (int i = location; i < count - 1; i++)
			{
				call_DB[i] = call_DB[i + 1];
			}

			count--;
			location = search(key);
		}
	}
}

/******************************************************************************************************************************/
//Name: double_size
//Precondition: There is no free memory in Student_DB.  count == size --- Student_DB is full
//Postcondition: The capacity of memory of Student_DB has been doubled
//Decription: doubles the size (capacity) of call_DB
/******************************************************************************************************************************/
void call_class::double_size()
{
	size *= 2;
	call_record *temp = new call_record[size];

	for (int i = 0; i<count; i++)
	{
		temp[i] = call_DB[i];
	}

	delete[] call_DB;
	call_DB = temp;
}


/******************************************************************************************************************************/
//Name: process
//Precondition: gross pay has not been calculated
//Postcondition: gross pay has been calculated for all student records in Student_DB
//Decription: calculate the net cost, tax rate, call tax and total cost for every call record in call_DB.
/*****************************************************************************************************************************/
void call_class::process()
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
//Name: print
//Precondition: Student_DB, size and count have been initialized
//Postcondition: Records in Student_DB printed to screen
//Decription: prints every field of every call_record in call_DB formatted to the screen.
/***************************************************************************************************************************/
void call_class::print()
{
	int i;

	//output file stream
	ofstream out;
	out.open("weekly_call_info.txt");

	//magic formula at the hundreths in the file
	out.setf(ios::showpoint);
	out.setf(ios::fixed);
	out.precision(2);

	//magic formula at the hundreths on screen
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	cout.precision(2);

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
//Name: destructor
//Precondition: Student_DB, size and count have been initialized
//Postcondition: Memory allocated to Student_DB using new has been de-allocated using delete
//Decription: de-allocates all memory allocated to call_DB.  This should be the last function to be called before the program
//            is exited.
/***************************************************************************************************************************/
call_class::~call_class()
{
	cout << endl << endl << "de-allocating memory and ending program" << endl;
	delete[] call_DB;
	call_DB = 0;
}


//driver to test the functionality of your class.
int main()
{
	call_class MyClass;

	//testing double size, is full, process, and print
	cout << endl << "Printing out original call record:  " << endl << endl;
	MyClass.process();
	MyClass.print();

	//testing add, is full, process, and print
	cout << endl << endl << "Adding in two new records:  " << endl << endl;
	MyClass.add();
	MyClass.add();
	MyClass.print();

	//testing search, is empty, remove, and print
	cout << endl << endl << "Removing records with 3 different keys:  " << endl << endl;
	string key;
	key = "9546321555";
	MyClass.remove(key);
	key = "5617278899";
	MyClass.remove(key);
	key = "9546321555";
	MyClass.remove(key);
	MyClass.print();

	return 0;
}
