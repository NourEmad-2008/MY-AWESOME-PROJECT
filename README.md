# Real Estate Management System (C++)

A high-performance, console-based  backend application designed to manage property listings, client portfolios, and real estate transactions. This project demonstrates core Object-Oriented Programming (OOP) principles, robust memory management, and file-based data persistence in C++.

---

## 🚀 Key Features

- **Property Portfolio Management:** Full CRUD (Create, Read, Update, Delete) operations for multiple property types (Apartments, Villas, Commercial Spaces).
- **Advanced Search & Filter Engine:** Filter listings instantly by location, price range, property type, and square footage.
- **Client & Agent Tracking:** Separate data tracking for Buyers, Sellers, and Real Estate Agents with transaction history.
- **Data Persistence:** Automatically saves and loads all system states (properties, user data) to local storage using file streams (`std::fstream`).

---

## 🛠️ System Architecture & OOP Design

This project is structured around clean, modular class design to ensure scalability and eliminate memory leaks.

- **Inheritance & Polymorphism:** A base `Property` class utilizes virtual methods, extended by specialized derived classes (`Apartment`, `Villa`, `Commercial`) to handle unique attributes like garden size or business zoning laws.
- **Encapsulation:** Strict use of private attributes with secure getters, setters, and data validation rules to protect system integrity.
- **Composition:** The `Transaction` class encapsulates both `User` and `Property` objects to model real-world sales mechanics.
- **Data Structures:** Custom management utilizing `std::vector` for dynamic memory allocation and efficient data traversal.

---

## 📂 Project Structure

```text
├── src/
│   ├── main.cpp             # Application entry point
│   ├── Property.cpp         # Base property implementation
│   ├── Apartment.cpp        # Derived apartment mechanics
│   ├── Villa.cpp            # Derived villa mechanics
│   ├── UserManager.cpp      # Handles authentication and client roles
│   └── Database.cpp         # Handles file I/O operations
├── include/
│   └── [All corresponding .h header files]
├── data/
│   ├── properties.txt       # Saved property database
│   └── users.txt            # Saved user accounts
└── README.md
