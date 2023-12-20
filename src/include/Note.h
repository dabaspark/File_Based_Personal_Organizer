// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <limits>

#include "Utilities.h"

struct Note {
    std::string title;
    std::string category;
    std::string content;
    std::string creationDate;
};

class NoteManager {
public:
    bool unsavedChanges;
    std::vector<Note> notes;

    // Constructor
    NoteManager(const std::string& filename);

    // Destructor
    ~NoteManager();

    // Function to add a new note
    void addNote();

    // Function to display all notes
    void displayNotes();

    // Function to edit a note
    void editNote();

    // Function to delete a note
    void deleteNote();

    // Function to search for a note
    void searchNotesByKeyword() const;

    // Function to save notes to a file
    void saveNotesToFile() const;

    // Function to load notes from a file
    void loadNotesFromFile();

    // Function to run the note management window
    void runWindow_Note();

    // Function to display notes by category
    void displayNotesByCategory() const;

    // Function to export notes to CSV
    void exportNotesToCSV(const std::string& filename) const;


private:
    std::string note_filename;
    // previous categories
    std::vector<std::string> previousCategories;

    // Utility functions for entering note details
    std::string enterNoteTitle() const;
    std::string enterNoteCategory();
    std::string enterNoteContent() const;

    // Utility functions for displaying note details
    void displayNotesDetailed(const std::vector<Note>& notes, bool clearScreen);


};

#endif // NOTE_H