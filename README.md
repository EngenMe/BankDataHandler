# BankDataHandler

**BankDataHandler** is designed to simulate a basic banking environment where users can manage clients, perform transactions, view balances, and update user information. It uses C++ for its backend logic and includes functionalities for user authentication, permission management, client CRUD operations, transaction logging, and interface communication.

## Features

- Client Management: Add, update, delete clients with account details.
- Transactions: Perform deposit, withdrawal, transfer operations between accounts.
- User Management: Manage users with different access permissions.
- Transaction Logging: Log all transactions for audit purposes.
- Interface Communication: Abstract interface for sending emails and SMS messages (In Progress).

## Installation

Ensure you have a C++ compiler that supports C++11 or later. Here are some options based on your operating system:

- [GCC](https://gcc.gnu.org/install/) for Linux.
- [MinGW](http://www.mingw.org/) or [Visual Studio](https://visualstudio.microsoft.com/vs/features/cplusplus/) for Windows.

To get started, clone this repository:

```bash
git clone https://github.com/EngenMe/BankDataHandler.git
cd BankDataHandler
```

## Compile the program

```bash
g++ -o BankHandler main.cpp
```

## Usage

Run the program:

```bash
./BankHandler
```

Follow the on-screen instructions to choose the number of questions, difficulty level, and type of arithmetic operations.

## Contributing

Contributions to the Math Challenge Game are welcome! If you have suggestions for improvements or bug reports, please open an issue or submit a pull request.

## License

This project is open source and available under the `MIT` License.