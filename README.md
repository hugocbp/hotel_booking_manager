# Hotel Booking Manager

This is a program to manage bookings of clients for a ficticious hotel, developed as a class project for the CPSC 2150 Algorithms & Data Structures II class at Langara College.

## Instructions

1. Download or clone
2. ```make && ./hotelTester```

## Requirements & Constraints

* Hotel should have 100 rooms with 1 bed, 50 rooms with 2 beds and 30 rooms with 3 beds
* A Customers.txt file is provided to be fed into the algorithm
* No customer can be rejected if there are enough beds available to satisfy the request
* Room and Customer must be implemented in separate classes
* Program should accomodate customers in more than one room if necessary to satisfy the booking request
* If it is impossible to accomodate the customer, program should diplay it on logfile
* Program should be fast and efficient space-wise
* You can accomodate a new customer in a room on its checkout date (ex: previous customer leaves at 12 PM, new customer checks-in at 1 PM)

## Sample Output

For the program:

```
Detailed, step-by-step logging printed on logfile
PERFORMANCE: 100000 requests, with 6615 booked and 93385 rejected. Success rate: 6.615%
TIME: 1522 ms
OPERATIONS: 316571
```

For logfile:
```
[VACANCY]: 100 one-beds, 50 two-beds, 30 three-beds

Reading from file...

1/1/2018 | ID: 843A62A1MR | Beds: 3 | Duration:  7
Finding a room for CUSTOMER: 843A62A1MR - Beds: 3
	[SEARCHING] Trying 3-bed rooms 	
	[EMPTY] Found room 3-1 empty
	[FOUND] Reserving room 3-1 until all beds are satisfied...
	[SUCCESS] Found space for all beds. Confirming booking... 
	[ROOM] 3-1 booked. Check-In: 1 | Check-Out: 7 | CUSTOMER: 843A62A1MR - Beds: 3
	[TRANSACTION COMPLETED] You are our customer number 1!
	[VACANCY]: 100 one-beds, 50 two-beds, 29 three-beds

1/1/2018 | ID: VN7OJWM77Z | Beds: 1 | Duration:  2
Finding a room for CUSTOMER: VN7OJWM77Z - Beds: 1
	[SEARCHING] Trying 1-bed rooms 	
	[EMPTY] Found room 1-1 empty
	[FOUND] Reserving room 1-1 until all beds are satisfied...
	[SUCCESS] Found space for all beds. Confirming booking... 
	[ROOM] 1-1 booked. Check-In: 1 | Check-Out: 2 | CUSTOMER: VN7OJWM77Z - Beds: 1
	[TRANSACTION COMPLETED] You are our customer number 2!
	[VACANCY]: 99 one-beds, 50 two-beds, 29 three-beds
```

## Miscellaneous

All rights reserved. Don't use this code for your own assignments/labs.