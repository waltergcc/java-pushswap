# Java PushSwap

Java PushSwap is a program that simulates a sorting algorithm for a list of integers using a set of specific commands.

This project is a Java implementation of the `42-push_swap` sorting project. It takes a list of integers and sorts them using a specific set of commands. The program was designed to use the least amount of commands possible to sort the list. 

## Commands set

- **sa** : swap the first two elements of stack A
- **pa** : take the first element from stack B and put it at the top of stack A
- **pb** : take the first element from stack A and put it at the top of stack B
- **ra** : shift up all elements of stack A by 1. The first element becomes the last one.
- **rb** : shift up all elements of stack B by 1. The first element becomes the last one.
- **rr** : ra and rb at the same time.
- **rra** : shift down all elements of stack A by 1. The last element becomes the first one.
- **rrb** : shift down all elements of stack B by 1. The last element becomes the first one.
- **rrr** : rra and rrb at the same time.

## Getting Started

To get started with this project, you'll need to have Java and a Java compiler installed on your machine. You can clone this repository to your local system and compile the source code to run the program.

### Prerequisites

- Java Development Kit (JDK)

### Installation

1. Clone the repository:

   ```sh
   git clone ***
   ```

2. Navigate to the project directory:

   ```sh
   cd ***
   ```

3. Compile the Java source code:

   ```sh
   make
   ```

## Usage

The project provides a set of Makefile random test cases. Avaliable rules: `2` `3` `10` `25` `100` `500` `1250`. To use the program, follow these steps:


```sh
make 2 # or any other these rules 3, 10, 25, 100, 500, 1250
```
To use the program without the MakeFile tests, just run the program manually. For this, follow the steps below:

```sh
java -cp src Main 2 1 3 6 5 8 7 4 9 10 # or any other list of integers
```

## Disclaimer
I used this project as a challenge to write code in other languages. As I've been more accustomed to writing in C lately, so I started by writing it in an object-oriented language I'm already familiar with, which is C++. This made it much easier to write the code, so I've completed the Java version. I've left the C++ code in this [folder]() for future reference.