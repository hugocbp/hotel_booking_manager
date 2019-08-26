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

## Write-up

The goal of the algorithm was to book as many customer as possible from the provided file, respecting the constraints and being as fast as possible.

For the rooms, a Circular Linked List was chosen since, after a customer is booked in a particular room, that room is the last one that should be looked into for the next customer. A Circular Linked List allows the best rotation of rooms and guaratees that the search for a room always starts from the room that has the highest chance of being free.

Since the requirements determined that a customer must have its request satisfied even if they need beds in different rooms, the algorithm uses a transaction-like pattern while finding rooms. It takes the beds requested by the customer and tries to find the most optimal room configutation. If it can't, it starts finding separate rooms until all beds are fulfilled. If there are not enough beds, the transaction is rolled back and none of the rooms are checked.

The resulting success rate is very close to the most optimal rate possible given the file (it is low because the file has thousands of customers checking in on the same date while the hotel only has 290 beds).

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

(...)

1/1/2018 | ID: WTHBEI0KUK | Beds: 3 | Duration:  1
Finding a room for CUSTOMER: WTHBEI0KUK - Beds: 3
	[SEARCHING] Trying 3-bed rooms 	.............................
	[SEARCHING] Trying 2-bed rooms 	
	[EMPTY] Found room 2-33 empty
	[FOUND] Reserving room 2-33 until all beds are satisfied...
	[SEARCHING] Trying 1-bed rooms 	
	[EMPTY] Found room 1-31 empty
	[FOUND] Reserving room 1-31 until all beds are satisfied...
	[SUCCESS] Found space for all beds. Confirming booking... 
	[ROOM] 2-33 booked. Check-In: 1 | Check-Out: 1 | CUSTOMER: WTHBEI0KUK - Beds: 3
	[ROOM] 1-31 booked. Check-In: 1 | Check-Out: 1 | CUSTOMER: WTHBEI0KUK - Beds: 3
	[TRANSACTION COMPLETED] You are our customer number 95!
	[VACANCY]: 69 one-beds, 17 two-beds, 0 three-beds

1/1/2018 | ID: BH40HKP5SL | Beds: 3 | Duration:  3
Finding a room for CUSTOMER: BH40HKP5SL - Beds: 3
	[SEARCHING] Trying 3-bed rooms 	.............................
	[SEARCHING] Trying 2-bed rooms 	
	[EMPTY] Found room 2-34 empty
	[FOUND] Reserving room 2-34 until all beds are satisfied...
	[SEARCHING] Trying 1-bed rooms 	
	[EMPTY] Found room 1-32 empty
	[FOUND] Reserving room 1-32 until all beds are satisfied...
	[SUCCESS] Found space for all beds. Confirming booking... 
	[ROOM] 2-34 booked. Check-In: 1 | Check-Out: 3 | CUSTOMER: BH40HKP5SL - Beds: 3
	[ROOM] 1-32 booked. Check-In: 1 | Check-Out: 3 | CUSTOMER: BH40HKP5SL - Beds: 3
	[TRANSACTION COMPLETED] You are our customer number 96!
	[VACANCY]: 68 one-beds, 16 two-beds, 0 three-beds

(...)

1/1/2018 | ID: HHM6MY65SX | Beds: 2 | Duration:  2
Finding a room for CUSTOMER: HHM6MY65SX - Beds: 2
	[SEARCHING] Trying 2-bed rooms 	.................................................
	[SEARCHING] Trying 1-bed rooms 	
	[EMPTY] Found room 1-100 empty
	[FOUND] Reserving room 1-100 until all beds are satisfied...
	[SEARCHING] Trying 1-bed rooms 	...........................
	[VACATING] Found room 1-28 that will be free today
	[FOUND] Reserving room 1-28 until all beds are satisfied...
	[SUCCESS] Found space for all beds. Confirming booking... 
	[ROOM] 1-100 booked. Check-In: 1 | Check-Out: 2 | CUSTOMER: HHM6MY65SX - Beds: 2
	[ROOM] 1-28 booked. Check-In: 1 | Check-Out: 2 | CUSTOMER: HHM6MY65SX - Beds: 2
	[TRANSACTION COMPLETED] You are our customer number 155!
	[VACANCY]: 0 one-beds, 0 two-beds, 0 three-beds

(...)

1/1/2018 | ID: JN4IZVKH6P | Beds: 3 | Duration:  5
Finding a room for CUSTOMER: JN4IZVKH6P - Beds: 3
	[SEARCHING] Trying 3-bed rooms 	.............................
	[SEARCHING] Trying 2-bed rooms 	.................................................
	[SEARCHING] Trying 1-bed rooms 	...................................................................................................
	[FAIL] Couldn't find enough rooms for CUSTOMER: JN4IZVKH6P - Beds: 3 - we are full...

(...)

1/1/2018 | ID: A4GSQL4NGD | Beds: 1 | Duration:  5
Finding a room for CUSTOMER: A4GSQL4NGD - Beds: 1
	[NO VACANCY] Sorry! We will only have more vacancies tomorrow...
	[VACANCY]: 0 one-beds, 0 two-beds, 0 three-beds
```

## Miscellaneous

All rights reserved. Don't use this code for your own assignments/labs.