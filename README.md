[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=10809533&assignment_repo_type=AssignmentRepo)

# GenericDB
GenericDB has a **terminal console interface** that allows users to store and interact with data. Users can communicate through the terminal-based interface to create, add, delete, or modify documents. The system will be able to filter and search through these documents. We will only be dealing with JSON files for now.

## 👥 Team Members
- Rohit Chandran
- Kanin Liang 
- Nathan Tran
- Paulian Le 
- Ali Shaikh

## 🛠️ Technologies
- **Languages**: C/C++
- **Libraries**: nlohmann/json, RapidJSON

## 💡 Features
- **How users use the system:**
  - Users are prompted with a welcome message instructing them on how to navigate through the program. After reading the message, user may hit "enter" to see the menu. 
  - Users are greeted with a menu of options of what they can do to the database. From there, they can input the number correlating to what they want to do in the database.
  - For example, they can just input the number "1" to add a document to the database. 
  - The program may then ask follow up questions to succesfully accomplish the task the user asked for. 
  - The program continuously loops with a menu of options of what the user can do to the database. The program terminates when the user quits the program by inputting the number "20" into the program.
  
- **Code behind our terminal user interface at the moment:**
- Welcome Page
<img width="487" alt="Screen Shot 2023-05-18 at 3 52 05 PM" src="https://github.com/CS180-spring/cs180-23-thedreamteam/assets/43308867/6cdc6c22-a6da-4681-a814-55397772358f">

- User Menu
<img width="457" alt="Screen Shot 2023-05-18 at 3 52 25 PM" src="https://github.com/CS180-spring/cs180-23-thedreamteam/assets/43308867/f4974411-957f-4516-bd73-996ed27cc76e">


- **Our features:**
  - Feature 1: Ability to create, add, or delete documents. Can also update the documents.
  - Feature 2: Ability to search and filter documents in database.
  - Feature 3: Query the database using JSON.
  - Feature 4: Ability to create directories and nest documents under those directories. 
  - Feature 5: Ability to view all existing files and collections in the database.
  - Feature 6: Ability to view an entire file. 
