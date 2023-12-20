// Note.cpp
#include "include/Note.h"

NoteManager::NoteManager(const std::string& filename) : note_filename(filename) {
    loadNotesFromFile();
    unsavedChanges = false;
}

NoteManager::~NoteManager() {
    // Clear the console
    std::system("clear");
}

void NoteManager::addNote() {
    print_menu_header("Main Menu >> Notes Menu >> Add a Note", true);

    std::cout << "Add Note:\n";
    std::cout << "Please enter the details for the new note.\n";
    std::cout << "You will be prompted for the title, category, and content.\n";
    std::cout << "---------------------------------------------\n";

    Note newNote;

    newNote.title = enterNoteTitle();
    newNote.category = enterNoteCategory();
    newNote.content = enterNoteContent();

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    newNote.creationDate = ctime(&now);
    newNote.creationDate.pop_back();

    // ask the user if they are sure they want to add the note
    char choice;
    std::cout << "Are you sure you want to add this note? (y/n): ";
    std::cin >> choice;
    std::cin.ignore(1, '\n');
    if (tolower(choice) != 'y' && tolower(choice) != 'Y') {
        std::cout << "Note not added.\n";
        return;
    }

    notes.push_back(newNote);
    unsavedChanges = true;
    std::cout << "Note added successfully!\n";

    print_menu_tail("Notes Menu", true);
}

void NoteManager::displayNotes() {
    print_menu_header("Main Menu >> Notes Menu >> Display Notes", true);

    // ask the user to show it in Table format or normal format
    std::cout << "How do you want to display the notes?\n";
    int choice = 0; 
    std::cout << "1. Detailed Format\n";
    std::cout << "2. Table Format\n";
    choice = getValidChoice(1, 2);

    std::cout << "The Notes are:\n";
    std::cout << "-----------------------------------------------\n";
    if (choice == 2) {
        // Display tasks in detailed format
        displayNotesDetailed(notes, false);
    } else {
        // Display the notes in a normal format
        for (const Note& note : notes) {
            std::cout << "Title: " << note.title << "\n";
            std::cout << "Category: " << note.category << "\n";
            std::cout << "Content: " << note.content << "\n";
            std::cout << "Creation Date: " << note.creationDate << "\n";
            std::cout << "-----------------\n";
        }
    }

    print_menu_tail("Notes Menu", true);
}
    

void NoteManager::editNote() {
    std::string searchTitle;

    print_menu_header("Main Menu >> Notes Menu >> Edit Notes", true);

    std::cout << "You will be prompted to enter the title of the note to be changed\n";
    std::cout << "Then, specify which field you want to edit.\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "The List of the Notes are:\n";
    std::cout << "---------------------------------------------\n";
    displayNotesDetailed(notes, false);

    std::cout << "---------------------------------------------\n";
    std::cout << "Enter the title of the note you want to edit: ";
    getline(std::cin, searchTitle);

    // Trim whitespaces from the input title
    searchTitle = trim(searchTitle);

    auto it = find_if(notes.begin(), notes.end(), [&searchTitle](const Note& note) {
        return note.title == searchTitle;
    });

    if (it != notes.end()) {
        Note editedNote = *it;

        // Display editing options
        std::cout << "Edit Note:\n";
        std::cout << "1. Title\n";
        std::cout << "2. Category\n";
        std::cout << "3. Content\n";
        std::cout << "4. All\n";

        int editOption;
        editOption = getValidChoice(1, 4);

        // Perform editing based on user choice
        switch (editOption) {
            case 1:
                editedNote.title = enterNoteTitle();
                break;
            case 2:
                editedNote.category = enterNoteCategory();
                break;
            case 3:
                editedNote.content = enterNoteContent();
                break;
            case 4:
                // If the user chooses to edit all fields, update all fields
                editedNote.title = enterNoteTitle();
                editedNote.category = enterNoteCategory();
                editedNote.content = enterNoteContent();
                break;
        }

        // Ask the user if they want to save changes
        char saveChoice;
        std::cout << "Are you sure you want to save the changes? (y/n): ";
        std::cin >> saveChoice;
        std::cin.ignore(1, '\n');
        if (tolower(saveChoice) == 'y') {
            *it = editedNote;
            std::cout << "Changes saved!\n";
            unsavedChanges = true;
        } else {
            std::cout << "Changes discarded.\n";
        }
    } else {
        std::cout << "Note not found.\n";
    }

    print_menu_tail("Notes Menu", true);
}

void NoteManager::deleteNote() {
    std::string searchTitle;
    print_menu_header("Main Menu >> Notes Menu >> Delete Notes", true);

    std::cout << "You will be prompted to enter the title of the note to be deleted\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "The List of the Notes are:\n";
    std::cout << "---------------------------------------------\n";

    displayNotesDetailed(notes, false);
    std::cout << "---------------------------------------------\n";
    std::cout << "Enter the title of the note you want to delete: ";

    getline(std::cin, searchTitle);

    auto it = find_if(notes.begin(), notes.end(), [&searchTitle](const Note& note) {
        return note.title == searchTitle;
    });

    if (it != notes.end()) {
        // Display the note to be deleted
        std::cout << "The note to be deleted is:\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "Title: " << it->title << "\n";
        std::cout << "Category: " << it->category << "\n";
        std::cout << "Content: " << it->content << "\n";
        std::cout << "Creation Date: " << it->creationDate << "\n";
        std::cout << "---------------------------------------------\n";

        // Ask the user if they are sure they want to delete the note
        char choice;
        std::cout << "Are you sure you want to delete this note? (y/n): ";
        std::cin >> choice;
        std::cin.ignore(1, '\n');
        if (tolower(choice) == 'y') {
            notes.erase(it);
            std::cout << "Note deleted successfully!\n";
            unsavedChanges = true;
        } else {
            std::cout << "Note not deleted.\n";
        }
    } else {
        std::cout << "Note not found.\n";
    }

    print_menu_tail("Notes Menu", true);
}

void NoteManager::searchNotesByKeyword() const {
    std::string keyword;

    print_menu_header("Main Menu >> Notes Menu >> Search Notes By Keyword", true);

    std::cout << "Enter the keyword of the note you want to search for: ";
    getline(std::cin, keyword);

    // Remove leading and trailing spaces from the user-entered keyword
    auto keywordBegin = std::find_if(keyword.begin(), keyword.end(), [](char c) {
        return !std::isspace(c);
    });

    auto keywordEnd = std::find_if(keyword.rbegin(), keyword.rend(), [](char c) {
        return !std::isspace(c);
    }).base();

    keyword = std::string(keywordBegin, keywordEnd);

    std::cout << "Notes:\n";

    for (const Note& note : notes) {
        // Remove leading and trailing spaces from the note title
        auto titleBegin = std::find_if(note.title.begin(), note.title.end(), [](char c) {
            return !std::isspace(c);
        });

        auto titleEnd = std::find_if(note.title.rbegin(), note.title.rend(), [](char c) {
            return !std::isspace(c);
        }).base();

        std::string trimmedTitle = std::string(titleBegin, titleEnd);

        // Remove leading and trailing spaces from the note content
        auto contentBegin = std::find_if(note.content.begin(), note.content.end(), [](char c) {
            return !std::isspace(c);
        });

        auto contentEnd = std::find_if(note.content.rbegin(), note.content.rend(), [](char c) {
            return !std::isspace(c);
        }).base();

        std::string trimmedContent = std::string(contentBegin, contentEnd);

        // Compare with the user-entered keyword (ignoring case)
        if (std::search(trimmedTitle.begin(), trimmedTitle.end(), keyword.begin(), keyword.end(),
            [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }) != trimmedTitle.end() ||
            std::search(trimmedContent.begin(), trimmedContent.end(), keyword.begin(), keyword.end(),
            [](char c1, char c2) { return std::toupper(c1) == std::toupper(c2); }) != trimmedContent.end()) {
            // Display the note details
            std::cout << "Title: " << note.title << "\n";
            std::cout << "Category: " << note.category << "\n";
            std::cout << "Content: " << note.content << "\n";
            std::cout << "Creation Date: " << note.creationDate << "\n";
            std::cout << "-----------------\n";
        }
    }

    print_menu_tail("Notes Menu", true);
}


void NoteManager::saveNotesToFile() const {
    std::ofstream file(note_filename);

    if (file.is_open()) {
        for (const Note& note : notes) {
            file << note.title << "\n";
            file << note.category << "\n";
            file << note.content << "\n";
            file << note.creationDate<< "\n";
        }

        std::cout << "Notes saved to file.\n";
    } else {
        std::cerr << "Unable to save notes to file.\n";
    }
    file.close();
}

void NoteManager::loadNotesFromFile() {
    std::ifstream file(note_filename);

    if (!file) {
        std::cout << "File not found. Starting with an empty task list.\n";
        return;
    }

    Note note;
    while (getline(file, note.title)) {
        getline(file, note.category);
        getline(file, note.content);
        getline(file, note.creationDate);

        notes.push_back(note);
    }

    // update the previous categories
    for (const Note& note : notes) {
        // make sure the category is not already in the previous categories
        if (std::find(previousCategories.begin(), previousCategories.end(), note.category) == previousCategories.end()){
            previousCategories.push_back(note.category);
        }
    }

    file.close();
}

void NoteManager::displayNotesByCategory() const {
    print_menu_header("Main Menu >> Notes Menu >> Display Notes By Category", true);

    // Display a list of available categories
    std::cout << "Available Categories:\n";
    for (size_t i = 0; i < previousCategories.size(); ++i) {
        std::cout << i + 1 << ". " << previousCategories[i] << "\n";
    }

    // Ask the user to choose a category
    std::cout << "Choose a category to display notes (enter 0 for all categories): ";
    size_t choice = static_cast<size_t>(getValidChoice(0, previousCategories.size()));

    // Display notes based on the chosen category
    std::cout << "Notes in ";
    if (choice == 0) {
        std::cout << "all categories:\n";
    } else {
        std::cout << previousCategories[choice - 1] << " category:\n";
    }

    for (const Note& note : notes) {
        // Display notes that match the chosen category
        if (choice == 0 || note.category == previousCategories[choice - 1]) {
            std::cout << "Title: " << note.title << "\n";
            std::cout << "Category: " << note.category << "\n";
            std::cout << "Content: " << note.content << "\n";
            std::cout << "Creation Date: " << note.creationDate << "\n";
            std::cout << "-----------------\n";
        }
    }

    print_menu_tail("Notes Menu", true);
}


void NoteManager::runWindow_Note() {
    int choice;

    do {
        print_menu_header("Main Menu >> Notes Menu", true);

        std::cout << "Number of Notes: " << notes.size() << ", "
                  << "File Status: " << (unsavedChanges ? "\033[1;31mNew Changes Not Saved to the File!\033[0m" : "Up to Date") << "\n";

        std::cout << "====================\n";
        std::cout << "1. Add a Note\n";
        std::cout << "2. Display Notes\n";
        std::cout << "3. Display Notes by Category\n";  // Added option
        std::cout << "4. Edit Notes\n";
        std::cout << "5. Delete Notes\n";
        std::cout << "6. Search Notes by Keyword\n";

        std::cout << "7. ";
        if (unsavedChanges) {
            std::cout << "\033[1;31mSave Current Changes to the File\033[0m";
        } else {
            std::cout << "Save Current Changes to the File";
        }
        std::cout << "\n";

        std::cout << "8. Go Back to Main Menu\n";

        choice = getValidChoice(1, 8);

        switch (choice) {
            case 1:
                addNote();
                break;
            case 2:
                displayNotes();
                break;
            case 3:
                displayNotesByCategory();  // Added option
                break;
            case 4:
                editNote();
                break;
            case 5:
                deleteNote();
                break;
            case 6:
                searchNotesByKeyword();
                break;
            case 7:
                saveNotesToFile();
                std::cout << "Tasks saved. \n";
                unsavedChanges = false;
                break;
            case 8:
                std::cout << "Going to the Main Menu.\n";
                break;
            default:
                break;
        }
    } while (choice != 8);

    print_menu_tail("Main Menu", false);
}

// Utility functions for entering note details

// Utility function to enter note title

std::string NoteManager::enterNoteTitle() const {
    std::cout << "Enter note title: ";
    std::string title;
    std::getline(std::cin, title);
    
    // Check if the title is empty
    // Check if the title is spaces only and if so, ask the user to enter a valid title
    // Check if the title is already used; if so, ask the user to enter a different title
    // Check if the title starts with a number or if it consists only of numbers
    while (
        title.empty() ||
        std::all_of(title.begin(), title.end(), [](char c) { return std::isspace(c); }) ||
        std::any_of(notes.begin(), notes.end(), [&title](const Note& note) { return note.title == title; }) ||
        std::isdigit(title.front()) ||
        std::all_of(title.begin(), title.end(), [](char c) { return std::isdigit(c); })
    ) {
        if (title.empty() || std::all_of(title.begin(), title.end(), [](char c) { return std::isspace(c); })) {
            std::cout << "Title cannot be empty or consist of spaces only. Please enter a valid title: ";
        } else if (std::any_of(notes.begin(), notes.end(), [&title](const Note& note) { return note.title == title; })) {
            std::cout << "Title already used. Please enter a different title: ";
        } else if (std::isdigit(title.front()) || std::all_of(title.begin(), title.end(), [](char c) { return std::isdigit(c); })) {
            std::cout << "Title cannot start with a number or consist only of numbers. Please enter a valid title: ";
        } else {
            // Currently, this else block covers the generic case of an invalid title.
            std::cout << "Invalid title. Please enter a valid title: ";
        }
        std::getline(std::cin, title);
    }

    return title;
}

// Utility function to enter note category
std::string NoteManager::enterNoteCategory() {
    std::cout << "Choose a note category or enter 0 to add a new category:\n";

    // Display previous categories with numbers
    for (size_t i = 0; i < previousCategories.size(); ++i) {
        std::cout << i + 1 << ". " << previousCategories[i] << "\n";
    }

    std::cout << "Enter your choice: ";
    size_t choice = static_cast<size_t>(getValidChoice(0, previousCategories.size()));
    
    if (choice >= 1 && choice <= previousCategories.size()) {
        // User chose an existing category
        return previousCategories[choice - 1];
    } else if (choice == 0) {
        // User wants to add a new category
        std::cout << "Enter a new category: ";
        std::string newCategory;
        std::getline(std::cin, newCategory);

        // Check if the new category is empty or consists of spaces only
        while (newCategory.empty() || std::all_of(newCategory.begin(), newCategory.end(), [](char c) { return std::isspace(c); })) {
            std::cout << "Category cannot be empty or consist of spaces only. Please enter a valid category: ";
            std::getline(std::cin, newCategory);
        }

        // Add the new category to the set of previous categories
        previousCategories.push_back(newCategory);
        return newCategory;
    } else {
        // Invalid choice, return an empty category
        return "";
    }
}

std::string NoteManager::enterNoteContent() const {
    std::cout << "Enter Note Content: ";
    std::string content;
    std::getline(std::cin, content);
    return content;
}


// Utility function to display detailed information about notes
void NoteManager::displayNotesDetailed(const std::vector<Note>& notes, bool clearScreen) {
    if (clearScreen) {
        // Clear the console
        std::system("clear");
    }

    // Display the sorted notes in a detailed format
    const int columnWidth = 20;

    std::cout << std::left << std::setw(columnWidth) << "Note Title";
    std::cout << std::setw(columnWidth) << "Category";
    std::cout << std::setw(columnWidth) << "Content";
    std::cout << std::setw(columnWidth) << "Creation Date\n";
    std::cout << std::string(4 * columnWidth, '-') << "\n";

    for (const Note& note : notes) {
        // Truncate note title to fit column width
        std::string truncatedTitle = note.title.substr(0, columnWidth - 3);
        if (note.title.length() > columnWidth)
            truncatedTitle += "...";

        // Truncate note category to fit column width
        std::string truncatedCategory = note.category.substr(0, columnWidth - 3);
        if (note.category.length() > columnWidth)
            truncatedCategory += "...";

        // Truncate note content to fit column width
        std::string truncatedContent = note.content.substr(0, columnWidth - 3);
        if (note.content.length() > columnWidth)
            truncatedContent += "...";

        // Truncate creation date to fit column width
        std::string truncatedCreationDate = note.creationDate.substr(0, columnWidth);
        if (note.creationDate.length() > columnWidth)
            truncatedCreationDate = "..." + note.creationDate.substr(note.creationDate.length() - columnWidth + 3);

        std::cout << std::setw(columnWidth) << truncatedTitle;
        std::cout << std::setw(columnWidth) << truncatedCategory;
        std::cout << std::setw(columnWidth) << truncatedContent;
        std::cout << std::setw(columnWidth) << truncatedCreationDate << "\n";
    }
}

void NoteManager::exportNotesToCSV(const std::string& filename) const {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const Note& note : notes) {
            file << note.title << "," << note.category << "," << note.content << "\n";
        }
        std::cout << "Notes exported to CSV file.\n";
    } else {
        std::cout << "Error: Unable to export notes to CSV file.\n";
    }

    file.close();
}