#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

#include <cctype>

 // required for conversion to lowercase
class toLower {public: char operator()(char c) const {return tolower(c);}};

  // not allowable DEC ASCII characters in mail addresses
  // 0-42, 44, 47, 58-64, 91-94, 96, 123-127
  // if a line contains the character @, create the variables
  // s(start of email address), e(end of email adress), and
  // hasDot(does it have a .) and use loops to find their values
  // if the values for these three indicate that the @ is inside a
  // print that address to the console

struct myNode
{
  string anEmail;
  myNode* next; // the link
}; //myNode

void printValues(myNode* head)
{
	myNode* p;
	for (p = head; p; p = p->next)
	{
  	cout << p->anEmail << " " << endl;
	}
}

bool isDuplicate(string anEmail, myNode* head)
{
	string temp1 = anEmail;
	transform(temp1.begin(), temp1.end(), temp1.begin(), toLower());

	string temp2 = "";

	myNode* p;
	for (p = head; p; p = p->next)
	{
    	temp2 = p->anEmail;
    	transform(temp2.begin(), temp2.end(), temp2.begin(), toLower());
    	if (temp2 == temp1) return true;
	} // for
	return false;
}

bool isValidEmailCharacter(char c)
{
  if (c >= 'A' && c <= 'Z') return true;
  if (c >= 'a' && c <= 'z') return true;
  if (c >= '0' && c <= '9') return true;
  if (c == '.' || c == '-' || c == '+') return true;
  return false;
}

int main()
{
  myNode* head = 0; // I love linked lists

  string fileIn;
  string fileOut;
 
  const string DEFAULTFILEIN = "fileContainingEmails.txt";
  const string DEFAULTFILEOUT = "copyPasteMyEmails.txt";
 
  cout << "Enter input filename [default: " << DEFAULTFILEIN << "]: ";
  getline(cin, fileIn);
 
  if (fileIn == "")
  {
	fileIn = DEFAULTFILEIN;
	cout << "Enter output filename [default: " << DEFAULTFILEOUT << "]: ";
	getline(cin, fileOut);
  }
  else
  {
	cout << "Enter output filename [default: " << fileIn << "]: ";
	getline(cin, fileOut);
  }
 
  if (fileOut == "") fileOut = fileIn;
  if (fileOut == "" && fileIn == DEFAULTFILEIN) fileOut = DEFAULTFILEOUT;
 
  cout << "Input file: " << fileIn << endl;
  cout << "Output file: " << fileOut << endl;
 
  cout << endl;
 
  ifstream fin;
  fin.open(fileIn.c_str());
  if (!fin.good()) cout << "bad file" << endl;
 
  int s = 0;
  int e = 0;

  bool hasdot = false;
 
  while (fin.good())
  {
	string lineFromFile;
	getline(fin, lineFromFile);
    
  	//cout << "Analyzed: "<< lineFromFile << endl; DEBUG
    
	for (int i = 0; i < lineFromFile.length(); i++) // for each char in the string...
	{
  	if (lineFromFile[i] == 64)
  	{
      	//cout << endl << endl << "i: " << i << " / " << lineFromFile[i] << endl; DEBUG
    	s = i;
    	s--;
    	hasdot = false;
   	 
    	while (isValidEmailCharacter(lineFromFile[s]) == true)
    	{
      	if (s == 0) break;
        	// take s and if s = true then e-- if false then s++
        	//cout << "s: " << s << " / " << lineFromFile[s] << endl; DEBUG
      	s--;
    	}

    	if (isValidEmailCharacter(lineFromFile[s]) == false)
    	{
        	//cout << "character: " << lineFromFile[s] << " is no good"; DEBUG
      	s++;
        	//cout << "<go back one> s: " << s << " / " << lineFromFile[s] << endl; DEBUG
    	}
   	 
    	e = i;
    	e++;
   	 
    	while (isValidEmailCharacter(lineFromFile[e]) == true)
    	{
        	// cout << lineFromFile[e] << " "; DEBUG
      	if (e == lineFromFile.length()) break;
      	if (lineFromFile[e] == '.')
      	{
        	hasdot = true;
          	// cout << "the dot was" << endl; DEBUG
      	}
      	e++;
        	// cout << "e: " << e << " / " << lineFromFile[e] << endl; DEBUG
    	}
   	 
    	if (hasdot == true && s < i && e > i)
    	{
      	string anEmail = lineFromFile.substr(s, e-s);

      	if (isDuplicate(anEmail, head) == false)
      	{
        	myNode* n = new myNode;
        	n->anEmail = anEmail;

        	n->next = head;
        	head = n;
      	}
      	hasdot = false;
    	}
  	}
	}
  	//cout << endl << endl; DEBUG
  } // while
 
  fin.close();
 
  printValues(head);

  return 0;
} // main
