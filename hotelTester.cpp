/**
** Program Name: Hotel Tester
** File Name: hotelTester.h
** Purpose: Tests the Hotel Booking program
** Author: Hugo Carlos Borges Pinto
** Date: May 17, 2019
*/
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Hotel.h"
#include "Operations.h"

using namespace std;

// To check performance improvements
long long ops = 0;

void readFile(Hotel &h);
int dateConversion(int day, int month);
string trim(string s);

int main() {
  // Redirect log stream to a file for tracing and debugging
  // might crash terminal if not redirected
  ofstream ofs("logfile");
  clog.rdbuf(ofs.rdbuf());

  // Start time measurement
  auto start = chrono::steady_clock::now();

  // Create a hotel
  Hotel h(100, 50, 30);

  // Double check available rooms
  h.vacancy();

  // Book customers from file
  readFile(h);

  // Check final vacancy
  h.vacancy();

  /*
   * =======
   * REPORTS
   * =======
   */
  // Info
  cout << "Detailed, step-by-step logging printed on logfile" << endl;

  // Algorithm efficiency
  h.performanceInfo();

  // Algorithm time
  auto end = chrono::steady_clock::now();
  cout << "TIME: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()
       << " ms" << endl;

  // Algorithm operations
  cout << "OPERATIONS: " << ops << endl;

  // TIME MEASUREMENT CODE FROM:
  // https://www.techiedelight.com/measure-elapsed-time-program-chrono-library/

  // Log redirection
  ofs.close();
  cout.rdbuf(nullptr);

  return 0;
}

void readFile(Hotel &h) {
  // Read Customers file
  ifstream file{"./Customers.txt", ios::in};

  // START LOGGING
  if (file.is_open()) clog << "\nReading from file...\n" << endl;
  // END LOGGING

  // Get header line
  string firstLine;
  getline(file, firstLine);  // and do nothing

  // Start reading each line
  while (!file.eof()) {
    // string date, id, beds, duration;
    string day, month, year, id, beds, duration, trash;

    // Get each piece of information, print for logging and double check
    getline(file, day, '/');
    day = trim(day);
    clog << day << "/";

    getline(file, month, '/');
    month = trim(month);
    clog << month << "/";

    getline(file, year, ',');
    year = trim(year);
    clog << year;

    getline(file, id, ',');
    id = trim(id);
    clog << " | ID: " << id;

    getline(file, beds, ',');
    beds = trim(beds);
    clog << " | Beds: " << beds;

    // For duration, add to checkIn, remove 1 day since last day room
    // is available again as per instructions (e.g. old customer checks
    // out until 12pm, new customer checks in after 12pm)
    getline(file, duration, '\n');

    // Get day of the year for the date
    int checkInDay = dateConversion(stoi(day), stoi(month));
    int checkOutDay = checkInDay + stoi(duration) - 1;

    clog << " | Duration: " << duration;

    clog << endl;

    // Finally, try to checkIn the customer
    h.book(Customer(id, stoi(beds)), checkInDay, checkOutDay);
  }

  // Close the open file
  file.close();
}

int dateConversion(int day, int month) {
  // The fall through is intentional here
  // comments required to bypass compiler warnings
  // of implicit fall through
  switch (month) {
    case 12:
      day += 30;
      // fall through
    case 11:
      day += 31;
      // fall through
    case 10:
      day += 30;
      // fall through
    case 9:
      day += 31;
      // fall through
    case 8:
      day += 31;
      // fall through
    case 7:
      day += 30;
      // fall through
    case 6:
      day += 31;
      // fall through
    case 5:
      day += 30;
      // fall through
    case 4:
      day += 31;
      // fall through
    case 3:
      day += 28;
      // fall through
    case 2:
      day += 31;
      // fall through
    case 1:
      // fall through
    default:
      break;
  }

  return day;
}

string trim(string s) {
  if (s[0] == ' ') return s.substr(1);
  return s;
}