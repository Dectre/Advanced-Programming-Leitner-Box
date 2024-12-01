#pragma once
#include "box.hpp"

class LeitnerBox {
public:
    LeitnerBox() : streak(0), day(1), boxes(NUM_OF_BOXES) {}
    int getStreak();
    int getDay();
    void getTodayFlashcards(vector<Flashcard>& todayFlashcards);
    int findBox(Flashcard flashcard);
    void upgradeFlashcard(Flashcard flashcard);

    void downgradeFlashcard(Flashcard flashcard);
    void downgradeBox(int boxIndex);
    void downgradeFlashcardsOnZeroStreak();
    void downgradeRemainingFlashcards(vector<Flashcard>& remainingFlashcards);
    Box& getBox(int boxLevel);
    int getMasteredFlashcards();
    void incStreak();
    void resetStreak();
    void incDay();

private:
    vector<Box> boxes;
    int streak;
    int day;
    int masteredFlashcards = 0;
};