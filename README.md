# File-Based Personal Organizer

Welcome to the File-Based Personal Organizer! This console-based application helps you manage tasks, appointments, and notes efficiently.

## System Requirements

- **Operating System:** Ubuntu 22.04 or compatible Linux distribution
- **Compiler:** g++ (GNU Compiler Collection)

## Build Instructions

1. **Clone the Repository:**

```bash
   git clone <repository-url>
   cd <repository-directory>
```

1. Compile the Code:

```bash
make
```

2. Run the Executable:
```bash
./daba_organizer
```

## Libraries
The File-Based Personal Organizer uses the following C++ standard libraries:

iostream
fstream
vector
algorithm
chrono
cctype
sstream
ctime
iomanip
limits
thread
string
map
unordered_map
termios
unistd

## Usage Instructions

1. Password Entry:

The default password is "123456".
Upon launching the application, you will be prompted to enter the password.

2. Main Menu:

The main menu allows you to navigate between task, appointment, and note management.
View reminders, save changes, export data to CSV, and exit the program.

3. Task Management:

Add, delete, and edit tasks.
View tasks sorted by deadline, creation date, or priority.

4. Appointment Scheduler:

Add, delete, and edit appointments.
View upcoming appointments in daily/weekly/monthly formats.

5. Personal Notes:

Create, edit, and delete text-based notes.
Organize notes in categories.

6. Persistent Storage:

All data is stored in files and loaded on program start.

7. Search Functionality:

Search tasks, appointments, and notes based on keywords.

8. Data Export to CSV (Extra Feature):

Export tasks, appointments, and notes to CSV files.


### Important Notes
Make sure your system meets the specified requirements.
- When prompted for password entry, use the default "123456".
- Data is saved upon choosing "Save Changes to File" or "Save and Quit" from the main menu.
- To exit without saving changes, choose "Quit without Saving."