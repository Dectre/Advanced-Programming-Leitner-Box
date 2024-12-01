#include "leitnerbox.hpp"

int LeitnerBox::getStreak() { return streak; };
int LeitnerBox::getDay() { return day; };
void LeitnerBox::getTodayFlashcards(vector<Flashcard>& todayFlashcards) {
    for (int i = 3 ; i > -1; i--) {
        if (day % LEVELS[i] == 0) {
            for (auto flashcard: getBox(i).getFlashcards()) {
                todayFlashcards.push_back(flashcard);
            }
        }
    }
}
int LeitnerBox::findBox(Flashcard flashcard) {
        for (int i = 0; i < NUM_OF_BOXES; i++) {
            int index = boxes[i].findFlashcardinBox(flashcard);
            if (index != -1) {
                return i;
            }
        }
    }
void LeitnerBox::upgradeFlashcard(Flashcard flashcard) {
    int boxLevel = findBox(flashcard);
    if (boxLevel != MONTHLY)
        boxes[boxLevel + 1].addFlashcard(flashcard);
    else
        masteredFlashcards += 1;
    int index = boxes[boxLevel].findFlashcardinBox(flashcard);
    boxes[boxLevel].removeFlashcard(index);
}

void LeitnerBox::downgradeFlashcard(Flashcard flashcard) {
    int boxLevel = findBox(flashcard);
    if (boxLevel != DAILY) {
        boxes[boxLevel - 1].addFlashcard(flashcard);
        int index = boxes[boxLevel].findFlashcardinBox(flashcard);
        boxes[boxLevel].removeFlashcard(index);
    }
}
void LeitnerBox::downgradeBox(int boxIndex) {
    auto flashcards = boxes[boxIndex].getFlashcards();
    for (int i = 0; i < size(flashcards); i++)  {
        boxes[boxIndex - 1].addFlashcard(flashcards[i]);
        boxes[boxIndex].removeFlashcard(i);
    }
}
void LeitnerBox::downgradeFlashcardsOnZeroStreak() {
    int today = getDay();
    for (int i = 1; i < NUM_OF_BOXES ; i++) {
        if (today % LEVELS[i] == 0) {
            downgradeBox(i);
        }
    }
}
void LeitnerBox::downgradeRemainingFlashcards(vector<Flashcard>& remainingFlashcards) {
    for (auto flashcard : remainingFlashcards) {
        downgradeFlashcard(flashcard);
    }
}
Box& LeitnerBox::getBox(int boxLevel) { return boxes[boxLevel]; }
int LeitnerBox::getMasteredFlashcards() { return masteredFlashcards; }
void LeitnerBox::incStreak() { streak+= 1; }
void LeitnerBox::resetStreak() {streak = 0; }
void LeitnerBox::incDay() { day+= 1; }
