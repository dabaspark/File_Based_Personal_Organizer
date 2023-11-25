// Note.h
#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <vector>

struct Note {
    std::string category;
    std::string content;
};

void addNote(std::vector<Note> &notes);
void editNote(std::vector<Note> &notes, int index);
void deleteNote(std::vector<Note> &notes, int index);

#endif // NOTE_H
