#what is this?
a console application that simulates "Expedia.com" .. a popular booking website

#How it's structured?
1. It consists of 3 back-end subsystems (Itineraries system, Payment system, and Users system),
2. One front-end system (Expedia),
3. And some global helper functions and properties.

#Program features:
1. Polymorphism is the main target .. extensibility is to be achieved
2. Heavy use of pointers and dynamic allocation
3. API handling .. however, they are local
4. Using properties as interfaces
5. Factory design pattern is prominent
6. Operator overloading for nicer code
7. The project is separated into abstract .h files and implementation details in .cpp files

#unfortunately:
8. It uses dummy data instead of permanent storage for simplicity
9. The system is vulnerable to wrong user input .. like string instead of int and so
10. Some classes are non-copyable indicating that it's enough to have one copy of them
11. The application focuses on only the customer's view

#side note:
any member function named "dummy reader" has the purpose of initializing objects with dummy data .. for easy usage quickly
