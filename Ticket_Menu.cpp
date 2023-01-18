#include <iostream>

#include <string>

#include <ctime>

#include <fstream>

#include <cstdio>

#include <regex>

#include<vector>

#include<conio.h>

using namespace std;
std::string inputstr();
class manageTicket {
  public:
    // Varible Declaration

    int PID; // Project ID number(4)
  string TID;
  int TC; // Ticket ID number(4) auto increment
  string create_EID; // Created By number(4) = Employee ID of login Employee
  string assign_EID; // Assigned to number(4) = Employee ID of login Employee
  int fixTime; // int(2) = number of hours required to fix bug
  char Priority; // char(1) = (L)ow, (M)edium, (H)igh, (S)evere
  char date[80]; // Create Date date (DD/MM/YYYY format) = today�s date
  char closeDate[80]; // Closing date of the ticket date (DD/MM/YYYY format)= closing date
  char Status; // char(1) = (O)pen, (A)ssigned, (F)ixed, (S)ubmitted, (Q)uality checked, (C)lose
  std::string bug_Description; // Bug Description string(50)
  std::string Note; // Note to the code string(540)
  std::string code_Snippet; // Code Snippet string(540)
  int c = 100;

  // Function Declaration

  int login();
  void getdata();
  void showdata();
  void Option();
  int Add();
  int Modify();
  int Close();
  int add_Note();
  int Snippet();
  void Quit();
  manageTicket() {
    TC = 1;
  }
};
int manageTicket::login() {
  string password = " ";
  string line;
  string vali;
  string substr;
  vector < string > vc;
  char ch;
  cout << "Enter Employee ID" << endl;
  cin >> create_EID;
  step5:
    cout << "Enter Password" << endl;
  /*ch=_getch();
   while(ch!='\0')
   {
       password.push_back(ch);
       cout<<"*";
       ch=_getch();
   }*/
  cin >> password;
  ifstream infile("Employees.txt");
  if (!infile) {
    cout << "Can't open file" << endl;
    exit(0);
  }
  while (getline(infile, line)) {
    //cout<<"I am here";
    std::size_t found = line.find(create_EID);
    if (found != std::string::npos) {

      stringstream ss(line);
      while (ss.good()) {

        getline(ss, substr, ',');
        vc.push_back(substr);
      }
      break;
    }
  }
  vali = vc[1];
  if (!password.compare(vali)) {
    cout << "Login Successful" << endl;
    password = "";
  } else {
    cout << "Wrong Password" << endl;
    goto step5;
  }
}
int manageTicket::Add() {
  int count = 0;
  string line;
  ifstream infile("tickets.txt");
  if (!infile) {
    cout << "Can't open file" << endl;
  }

  if (!infile.eof()) {

    while (infile.peek() != EOF) {
      getline(infile, line);
      count++;
    }
    TC = TC + count;
  }
  std::string TID = "T" + std::to_string(TC);
  cout << "To Raise Ticket" << endl;
  cout << "Enter Your Project ID" << endl;
  cin >> PID;
  cout << "Enter The priority of this Ticket" << endl;
  cin >> Priority;
  cout << "Enter Description" << endl;
  cin.ignore();
  bug_Description = inputstr();
  cout << "Current date is taken" << endl;
  time_t tmNow = time(0);
  strftime(date, 80, "%d/%m/%Y", localtime( & tmNow));
  cout << "Enter Status" << endl;
  cin >> Status;
  cout << "Enter estimated time to fix" << endl;
  cin >> fixTime;
  cout << "Add note" << endl;
  cin >> Note;
  cout << "Add code snippet" << endl;
  cin >> code_Snippet;
  ofstream outfile("tickets.txt", ios::app);
  outfile << PID << "," << TID << "," << Priority << "," << create_EID << "," << bug_Description << "," << date << "," << create_EID << "," <<
    "EMPTY" <<
    "," << Status << "," << fixTime << "," << Note << "," << code_Snippet << endl;
  cout << "\n" <<
    PID << "," << TID << "," << Priority << "," << create_EID << "," << bug_Description << "," << date << "," << create_EID << "," <<
    "EMPTY" <<
    "," << Status << "," << fixTime << "," << Note << "," << code_Snippet << endl;
  outfile.close();
  return 1;

}

int manageTicket::Modify() {
  int counts = 0,count=0,i;
  string lineno;
  string new_eid,cid2,eid2;
  vector < string > v;
  vector < string > v2;
   vector < string > v3;
  string substr;
  stringstream cid,eid;
  cid<<create_EID;
  eid<<assign_EID;
  int linenos = 1;
  string line;
  string data;
  cout << data << endl;
  cout << "Enter Ticket Id" << endl;
  cin >> lineno;
  ifstream infile("tickets.txt");
  if (!infile) {
    cout << "Can't open file" << endl;
    exit(0);
  }
  while (getline(infile, line)) {

    std::size_t found = line.find(lineno);
    if (found != std::string::npos) {
      stringstream ss(line);
      while (ss.good()) {

        getline(ss, substr, ',');
        v.push_back(substr);
      }
      cid2=v[3];
      eid2=v[6];
      if(!cid2.compare(cid.str()) || !eid2.compare(eid.str()))
      {
          cout<<"You are not allowed to make changes to this ticket"<<endl;
          exit(0);
      }
      break;
    }
  }
  cout << "Enter the Employee ID of whom to assign" << endl;
  cin >> new_eid;
  cout << "Select Status of the Ticket" << endl;
  cout << "(O)pen" << endl;
  cout << "(A)ssigned" << endl;
  cout << "(F)ixed" << endl;
  cout << "(S)ubmitted" << endl;
  cout << "(Q)uality checked" << endl;
  cout << "(C)lose" << endl;
  cin >> Status;
  time_t tmNow = time(0);
  strftime(date, 80, "%d/%m/%Y", localtime( & tmNow));
  ofstream outfile("trails.txt", ios::app);
  outfile << v[1] << "," << date << "," << v[6] << "," << new_eid << "," << v[8] << "," << Status << endl;
  outfile.close();
  infile.close();
   ifstream infiles("tickets.txt");
  if (!infiles) {
    cout << "Can't open file" << endl;
    exit(0);
  }

  while (getline(infiles, line)) {
    //cout << "i am here" << endl;
    ++count;
    std::size_t found = line.find(lineno);
    if (found != std::string::npos) {

      stringstream ss(line);
      while (ss.good()) {

        getline(ss, substr, ',');
        v.push_back(substr);
      }
      break;
    }
  }
  infiles.close();

  ifstream outfiles("tickets.txt");
  while (getline(outfiles, data)) {
    v2.push_back(data);
  }
  outfiles.close();
  cout << v2.size() << endl;
  cout << count << endl;
  ofstream out("tickets.txt");
  count--;
  for (i = 0; i < v2.size(); i++) {
    cout << "i am here";
    if (i != count) {
      out << v2[i] << endl;
    } else {

        out << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "," << v[4] << "," << v[5] << "," << new_eid << "," << v[7] << "," << Status << "," << v[9] << "," << v[10] << "," << v[11] << "," << endl;

    }
  }
  return 1;

}
int manageTicket::Close() {
  string t_id, line, substr, data,cid2,eid2;
  vector < string > v;
  vector < string > v2;
  stringstream cid,eid;
  cid<<create_EID;
  eid<<assign_EID;
  int count = 0, i;
  cout << "Enter Ticket ID:" << endl;
  cin >> t_id;
  ifstream infile("tickets.txt");
  if (!infile) {
    cout << "Can't open file" << endl;
    exit(0);
  }

  while (getline(infile, line)) {
    //cout << "i am here" << endl;
    ++count;
    std::size_t found = line.find(t_id);
    if (found != std::string::npos) {

      stringstream ss(line);
      while (ss.good()) {

        getline(ss, substr, ',');
        v.push_back(substr);
      }
      cid2=v[3];
      eid2=v[6];
      cout<<cid2<<endl;
      cout<<eid2<<","<<cid.str()<<","<<eid.str()<<endl;
      if(cid2.compare(create_EID) || eid2.compare(assign_EID))
      {
          cout<<"You are not allowed to make changes to this ticket"<<endl;
          exit(0);
      }
      break;
    }

  }
  infile.close();

  ifstream outfile("tickets.txt");
  while (getline(outfile, data)) {
    v2.push_back(data);
  }
  outfile.close();
  cout << v2.size() << endl;
  cout << count << endl;
  ofstream out("tickets.txt");
  count--;
  for (i = 0; i < v2.size(); i++) {
    cout << "i am here";
    if (i != count) {
      out << v2[i] << endl;
    } else {
      if (v[8] == "C") {

        out << v2[i] << endl;
      } else {
        out << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "," << v[4] << "," << v[5] << "," << v[6] << "," << v[7] << "," << "C" << "," << v[9] << "," << v[10] << "," << v[11] << "," << endl;
      }
    }
  }
  return 1;
}
int manageTicket::add_Note() {
  string t_id, line, substr, data, note,cid2,eid2;
  vector < string > v;
  vector < string > v2;
  stringstream cid,eid;
  cid<<create_EID;
  eid<<assign_EID;
  int count = 0, i;
  cout << "Enter Ticket ID:" << endl;
  cin >> t_id;

  ifstream infile("tickets.txt");
  if (!infile) {
    cout << "Can't open file" << endl;
    exit(0);
  }

  while (getline(infile, line)) {
    //cout << "i am here" << endl;
    ++count;
    std::size_t found = line.find(t_id);
    if (found != std::string::npos) {

      stringstream ss(line);
      while (ss.good()) {

        getline(ss, substr, ',');
        v.push_back(substr);
      }
      cid2=v[3];
      eid2=v[6];
      if(!cid2.compare(cid.str()) || !eid2.compare(eid.str()))
      {
          cout<<"You are not allowed to make changes to this ticket"<<endl;
          exit(0);
      }
      break;
    }

  }
    cout << "Enter the note you want to add" << endl;
  cin.ignore();
  getline(cin, note);
  infile.close();
  v[10] = v[10] + " " + note;
  ifstream outfile("tickets.txt");
  while (getline(outfile, data)) {
    v2.push_back(data);
  }
  outfile.close();
  cout << v2.size() << endl;
  cout << count << endl;
  ofstream out("tickets.txt");
  count--;
  for (i = 0; i < v2.size(); i++) {
    //cout << "i am here";
    if (i != count) {
      out << v2[i] << endl;
    } else {
      out << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "," << v[4] << "," << v[5] << "," << v[6] << "," << v[7] << "," << "C" << "," << v[9] << "," << v[10] << "," << v[11] << "," << endl;
    }
  }
  return 1;
}
int manageTicket::Snippet() {
  string t_id, line, substr, data, snippet,cid2,eid2;
  vector < string > v;
  vector < string > v2;
  stringstream cid,eid;
  cid<<create_EID;
  eid<<assign_EID;
  int count = 0, i;
  cout << "Enter Ticket ID:" << endl;
  cin >> t_id;

  ifstream infile("tickets.txt");
  if (!infile) {
    cout << "Can't open file" << endl;
    exit(0);
  }

  while (getline(infile, line)) {
    cout << "i am here" << endl;
    ++count;
    std::size_t found = line.find(t_id);
    if (found != std::string::npos) {

      stringstream ss(line);
      while (ss.good()) {

        getline(ss, substr, ',');
        v.push_back(substr);
      }
      cid2=v[3];
      eid2=v[6];
      if(!cid2.compare(cid.str()) || !eid2.compare(eid.str()))
      {
          cout<<"You are not allowed to make changes to this ticket"<<endl;
          exit(0);
      }
      break;
    }

  }

  infile.close();
  cout << "Enter the snippet you want to add" << endl;
  cin.ignore();
  getline(cin, snippet);
  v[11] = v[11] + " " + snippet;
  ifstream outfile("tickets.txt");
  while (getline(outfile, data)) {
    v2.push_back(data);
  }
  outfile.close();
  cout << v2.size() << endl;
  cout << count << endl;
  ofstream out("tickets.txt");
  count--;
  for (i = 0; i < v2.size(); i++) {
    cout << "i am here";
    if (i != count) {
      out << v2[i] << endl;
    } else {
      out << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << "," << v[4] << "," << v[5] << "," << v[6] << "," << v[7] << "," << "C" << "," << v[9] << "," << v[10] << "," << v[11] << "," << endl;
    }
  }
  return 1;
}
void manageTicket::Option() {
  menu: cout << "  -------------------------- Tickets Menu---------------------------" << endl;
  int ch,
  x,
  y,
  z,
  u,
  v;
  cout << "1. Add Ticket" << endl;
  cout << "2. Modify Ticket" << endl;
  cout << "3. Close Ticket" << endl;
  cout << "4. Add Note to Ticket" << endl;
  cout << "5. Add Code Snippet to Ticket" << endl;
  cout << "0. Quit" << endl;
  cout << "Enter your choice" << endl;
  cin >> ch;
  switch (ch) {
  case 0:
    // Quit();
    break;
  case 1:
    x = Add();
    if (x = 1)
      goto menu;
    break;
  case 2:
    y = Modify();
    if (y == 0)
      goto menu;
    break;
  case 3:
    z = Close();
    if (z == 1)
      goto menu;
    break;
  case 4:
    u = add_Note();
    if (u == 1)
      goto menu;
    break;
  case 5:
    v = Snippet();
    if (v == 1)
      goto menu;
    break;
  default:
    cout << "INVALID CHOICE";
    goto menu;
    break;
  }
}
string inputstr() {
  string str;
  regex regex_int("^.{1,50}$");
  do {
    cout << "Input length must be between 1 to 50 only: ";
    getline(cin, str);
  } while (!regex_match(str, regex_int));
  return str;
}
int main() {
  manageTicket ticket;
  ticket.login();
  ticket.Option();
}
