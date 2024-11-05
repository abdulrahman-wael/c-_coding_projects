# Overview

The project is a question-and-answer system that allows users to register, log in, and post questions either anonymously or publicly. 
The system manages user accounts, their questions, and answers, facilitating interaction in a structured manner. 
Users can choose to keep their identities hidden when asking questions, enhancing privacy and encouraging open discussion. 
The application leverages file handling for persistent storage of user and question data, allowing for data retrieval and management between sessions.

## Features

- **User Registration and Login**: Users can sign up by providing a username, email, password, and personal details. The login feature authenticates users based on their credentials.
- **Anonymous Questioning**: Users have the option to post questions anonymously, enabling them to seek answers without revealing their identities.
- **Persistent Storage**: User data and questions are stored in text files, allowing for data persistence between sessions. This ensures that user interactions and queries are retained even after the application is closed.
- **Input Validation**: The system includes input validation for user choices, ensuring that only valid data is processed, which enhances the overall robustness of the application.
- **Dynamic User Management**: The application maintains a map of users and their details, facilitating easy access and updates to user information and their associated questions.
- **User-Friendly Menu Interface**: A simple text-based menu guides users through available actions, making it easy to navigate the system.
- **Question Management**: Users can post questions, view answers, and manage their inquiries. Each question can be linked to a specific user, and the system can display whether a question has been answered or not.
- **Clear Output Formatting**: The system provides clear and structured outputs for user interactions, making it easy to read and understand the data being presented.

## Key Learning Outcomes

1. **File I/O Operations** 🗂️ 
   Learn how to read from and write to files using C++, enabling data persistence and retrieval.
2. **Data Structures** 📊 
   Understand the use of `vector` and `map` for storing and organizing data efficiently, facilitating user and question management.
3. **Object-Oriented Programming** 🏗️
   Gain hands-on experience with OOP principles, such as encapsulation and constructors, by creating user and question classes.
4. **User Authentication** 🔐
   Implement a simple user login and sign-up system, ensuring user data security through password handling.
5. **Error Handling** 🚨
   Practice validating user inputs and handling errors gracefully, improving program robustness and user experience.
6. **Data Transformation** 🔄
   Learn string manipulation techniques to convert between formats, such as dashes and spaces, enhancing data consistency.
7. **Basic Command-Line Interface** 🖥️
   Develop a command-line menu system for user interaction, teaching how to create a user-friendly text-based interface.
8. **Assertion for Debugging** 🧪
   Utilize assertions to verify program correctness and data integrity, reinforcing the importance of debugging in software development.
