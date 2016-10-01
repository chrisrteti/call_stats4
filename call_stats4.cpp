//Name: Christopher Teti                                Z#  : 23293126
	//	Course : Foundations of Computer Science(COP3014)
	//	Professor : Dr.Lofton Bullard
	//	Due Date 10/02/2016: Due Time 11:59pm:
	//									  Total Points : 20

	//										  Assignment 5: call_stats4.cpp
	/*Description :
	in this program we declared a new class called call_record. from there we pointed customer_record to call_record to retrieve
	the infomration declared inside the class. We used customer_record.the variables we needed to perform the actions in each function.
	we had three funtions for input, process and output. We got call info from a file and and processed it into the array declared as call_DB.
	we then filled the array with the input file.
	we passed the array to the process function which added call tax, net cost, total cost and tax rate.
	we then printed the information in the array to a text file. 
	*/





#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
const int SIZE = 200;
/*********************************************************
//Following is the declaration of a call record
**********************************************************/
class call_record
{
public:
	string cell_number;
	int relays;
	int call_length;
	double net_cost;
	double tax_rate;
	double call_tax;
	double total_cost;
};


//Prototypes for your functions: Input, Output, and Process will go here

void Input(call_record(&call_DB)[SIZE], int &count, ifstream &in);
void Process(call_record(&call_DB)[SIZE], int count);
void Output(call_record(&call_DB)[SIZE], int count, ofstream &out);




void Input(call_record(&call_DB)[SIZE], int &count, ifstream &in) {

	in.open("call_data.txt");
	count = 0;

	while (!in.eof() && count < SIZE) {


		in >> call_DB[count].cell_number;
		in >> call_DB[count].relays;
		in >> call_DB[count].call_length;


		count++;

	}
	in.close();


}

void Process(call_record(&call_DB)[SIZE], int count) {

	for (int i = 0; i < count; i++){

		if ((call_DB[i].relays >= 0) && (call_DB[i].relays <= 5)) {
			call_DB[i].tax_rate = 0.01;
		}
		else if ((call_DB[i].relays >= 6) && (call_DB[i].relays <= 11)) {
			call_DB[i].tax_rate = 0.03;
		}

		else if ((call_DB[i].relays >= 12) && (call_DB[i].relays <= 20)) {
			call_DB[i].tax_rate = .05;
		}

		else if ((call_DB[i].relays >= 21) && (call_DB[i].relays <= 50)) {
			call_DB[i].tax_rate = .08;
		}
		else {
			call_DB[i].tax_rate = 0.12;
		}
		call_DB[i].net_cost = call_DB[i].relays / 50.0 * .40 * call_DB[i].call_length;

		call_DB[i].call_tax = call_DB[i].net_cost*call_DB[i].tax_rate;


		call_DB[i].total_cost = call_DB[i].net_cost + call_DB[i].call_tax;

}


}

void Output(call_record(&call_DB)[SIZE], int count, ofstream &out) {
	out.setf(ios::fixed);
	out.setf(ios::showpoint);
	out.precision(2);

	out.open("weekly4_call_info.txt");

	
	for (int i = 0; i < count; i++) {

		out << right << setw(10) << call_DB[i].cell_number << "  ";
		out << right << setw(10) << call_DB[i].relays << "  ";
		out << right << setw(10) << call_DB[i].call_length << "  ";
		out << right << setw(10) << call_DB[i].net_cost << "  ";
		out << right << setw(10) << call_DB[i].tax_rate << "  ";
		out << right << setw(10) << call_DB[i].call_tax << "  ";
		out << right << setw(10) << call_DB[i].total_cost << endl;

	}
	out.close();
}

int main(){
	call_record call_DB[SIZE];
	int count;
	ifstream in;
	ofstream out;

	Input(call_DB, count, in);
	Process(call_DB, count);
	Output(call_DB, count, out);

}