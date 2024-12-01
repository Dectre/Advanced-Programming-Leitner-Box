#pragma once
#include "flashcard.hpp"

class Box {
public:
    Box();
    vector<Flashcard> &getFlashcards();
    void addFlashcard(Flashcard card);
    void removeFlashcard(size_t index);
    int findFlashcardinBox(Flashcard card);

private:
    vector<Flashcard> flashcards;
};