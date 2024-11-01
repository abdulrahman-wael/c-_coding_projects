# Overview of the Expedia.com Simulation Console Application
This console application simulates Expedia.com, a popular booking website, providing a simplified experience of online travel bookings.

## Structure of the Application
1. Back-End Subsystems:
  Itineraries System: Manages travel itineraries for users.
  Payment System: Handles payment processing.
  Users System: Manages user accounts and information.
2. Front-End System:
  Expedia: The user interface for interacting with the booking system.
3. Global Helper Functions and Properties:
  Utilities and shared functionalities to support the application.

## Key Features
1. Polymorphism: The application is designed to leverage polymorphism for extensibility, allowing for easier updates and enhancements. 🌟
2. Dynamic Memory Management: Extensive use of pointers and dynamic allocation to manage resources effectively. 🔄
3. API Handling: Localized API handling for inter-system communication. 🔗
4. Properties as Interfaces: Properties are utilized to serve as interfaces for different functionalities. 🛠️
5. Factory Design Pattern: The factory design pattern is prominently employed to create objects in a flexible and reusable manner. 🏭
6. Operator Overloading: Enhances code readability and usability through operator overloading. ✍️
7. Code Organization: The project is organized with abstract .h files for declarations and .cpp files for implementation details. 📂
## Limitations
1. Dummy Data Usage: The application uses dummy data for simplicity rather than permanent storage. ⚠️
2. User Input Vulnerabilities: The system is susceptible to incorrect user input, such as entering a string instead of an integer. ❌
3. Non-Copyable Classes: Some classes are designated as non-copyable to ensure only one instance exists. 🚫
4. Customer-Focused: The application primarily focuses on the customer's view without backend administrative features. 👤
## Additional Note
Any member function named "dummy reader" is designed to initialize objects with dummy data for quick and easy usage. 📝
