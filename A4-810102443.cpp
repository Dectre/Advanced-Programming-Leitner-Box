#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

const string CMD_STREAK = "streak";
const string CMD_ADD_FLASHCARD = "add_flashcard";
const string CMD_REVIEW_TODAY = "review_today";
const string CMD_GET_REPORT = "get_report";
const string CMD_GET_PROGRESS_REPORT = "get_progress_report";
const string CMD_NEXT_DAY = "next_day";

const vector<int> LEVELS = {1, 3, 7, 30};

const int NUM_OF_BOXES = 4;

const int DAILY = 0;
const int THREEDAYS = 1;
const int WEEKLY = 2;
const int MONTHLY = 3;

const string MSG_FLASHCARD_ADDED_SUCCESSFULLY = "flashcards added to the daily box";
const vector<string> MSG_NEXT_DAY = {"Good morning! Today is day ", " of our journey.\nYour current streak is: "
        , "\nStart reviewing to keep your streak!"};
const string MSG_CORRECT_ANSWER = "\nYour answer was correct! Well done, keep it up!";
const vector<string> MSG_WRONG_ANSWER = {"\nYour answer was incorrect. Don't worry! The correct answer is: ",
                                         ". Keep practicing!"};
const string MSG_FLASHCARD_QUESTION = "Flashcard: ";
const string MSG_YOUR_ANSWER = "Your answer: ";
const string MSG_TODAYS_REVIEW = "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!";
const vector<string> MSG_STREAK = {"Your current streak is: ",
                                   "\nKeep going!"};
const vector<string> MSG_REPORT = {"Day: ",  "Correct Answers: ", "Incorrect Answers: ", "Total: ", " to "};
const vector<string> MSG_PROGRESS_REPORT = {"Challenge Progress Report:\n", "Day of the Challenge: ",
                                            "Streak: ", "Total Days Participated: ", "Mastered Flashcards: ",
                                            "\nKeep up the great work! You're making steady progress toward mastering your flashcards."};

class Flashcard {
public:
    Flashcard();
    Flashcard(string q, string a) : question(q), answer(a) {}
    string getQuestion() { return question; }
    string getAnswer() { return answer; }
    void mistake() { wrongAnswer = true; }
    void mistakeCorrected() { wrongAnswer = false; }
    bool wasMistaken() { return wrongAnswer; }
    bool cardCompare(Flashcard card) {
        if (card.question == question)
            return true;
        return false;
    }
private:
    string question;
    string answer;
    bool wrongAnswer = false;
};

class Box {
public:
    Box() = default;
    vector<Flashcard>& getFlashcards() { return flashcards; }
    void addFlashcard(Flashcard card) { flashcards.push_back(card); }
    void removeFlashcard(size_t index) { flashcards.erase(flashcards.begin() + index); }
    int findFlashcardinBox(Flashcard card) {
        for (int i = 0; i <= flashcards.size(); i++) {
            if (flashcards[i].cardCompare(card)) return i;
        }
        return -1;
    }
private:
    vector<Flashcard> flashcards;
};

class LeitnerBox {
public:
    LeitnerBox() : streak(0), day(1), boxes(NUM_OF_BOXES) {}
    int getStreak() { return streak; };
    int getDay() { return day; };
    void getTodayFlashcards(vector<Flashcard>& todayFlashcards) {
        for (int i = 3 ; i > -1; i--) {
            if (day % LEVELS[i] == 0) {
                for (auto flashcard: getBox(i).getFlashcards()) {
                    todayFlashcards.push_back(flashcard);
                }
            }
        }
    }
    int findBox(Flashcard flashcard) {
        for (int i = 0; i < NUM_OF_BOXES; i++) {
            int index = boxes[i].findFlashcardinBox(flashcard);
            if (index != -1) {
                return i;
            }
        }
    }
    void upgradeFlashcard(Flashcard flashcard) {
        int boxLevel = findBox(flashcard);
        if (boxLevel != MONTHLY)
            boxes[boxLevel + 1].addFlashcard(flashcard);
        else
            masteredFlashcards += 1;
        int index = boxes[boxLevel].findFlashcardinBox(flashcard);
        boxes[boxLevel].removeFlashcard(index);
    }

    void downgradeFlashcard(Flashcard flashcard) {
        int boxLevel = findBox(flashcard);
        if (boxLevel != DAILY) {
            boxes[boxLevel - 1].addFlashcard(flashcard);
            int index = boxes[boxLevel].findFlashcardinBox(flashcard);
            boxes[boxLevel].removeFlashcard(index);
        }
    }
    void downgradeBox(int boxIndex) {
        auto flashcards = boxes[boxIndex].getFlashcards();
        for (int i = 0; i < size(flashcards); i++)  {
            boxes[boxIndex - 1].addFlashcard(flashcards[i]);
            boxes[boxIndex].removeFlashcard(i);
        }
    }
    void downgradeFlashcardsOnZeroStreak() {
        int today = getDay();
        for (int i = 1; i < NUM_OF_BOXES ; i++) {
            if (today % LEVELS[i] == 0) {
                downgradeBox(i);
            }
        }
    }
    void downgradeRemainingFlashcards(vector<Flashcard>& remainingFlashcards) {
        for (auto flashcard : remainingFlashcards) {
            downgradeFlashcard(flashcard);
        }
    }
    Box& getBox(int boxLevel) { return boxes[boxLevel]; }
    int getMasteredFlashcards() { return masteredFlashcards; }
    void incStreak() { streak+= 1; }
    void resetStreak() {streak = 0; }
    void incDay() { day+= 1; }

private:
    vector<Box> boxes;
    int streak;
    int day;
    int masteredFlashcards = 0;
};

class Day {
public:
    Day() : correctAnswers(0), wrongAnswers(0), totalAnswers(0) {}
    int getCorrectAnswers() { return correctAnswers; }
    int getWrongAnswers() { return wrongAnswers; }
    int getTotalAnswers() {return totalAnswers; }
    void incCorrectAnswers() { correctAnswers+= 1; }
    void incWrongAnswers() { wrongAnswers+= 1; }
    void incTotalAnswers() { totalAnswers+= 1; }
private:
    int correctAnswers;
    int wrongAnswers;
    int totalAnswers;
};

vector<string> splitStringBy(const string& sentence, char delimiter) {
    vector<string> words;
    istringstream stream(sentence);
    string word;

    while(getline(stream, word, delimiter)) {
        words.push_back(word);
    }

    return words;
}

void addFlashcard(LeitnerBox& leitnerBox, vector<string> argument) {
    int numOfQuestions = stoi(argument[1]);
    for (int i = 0; i < numOfQuestions; i++) {
        string question;
        string answer;
        getline(cin, question);
        getline(cin, answer);
        Flashcard newCard(question, answer);
        leitnerBox.getBox(DAILY).addFlashcard(newCard);
    }
    cout << MSG_FLASHCARD_ADDED_SUCCESSFULLY << endl;
}

bool getAnswer(LeitnerBox& leitnerBox, string answer) {
    string userAnswer;
    getline(cin, userAnswer);
    if (userAnswer.compare(answer) == 0) {
        cout << MSG_CORRECT_ANSWER << endl;
        return true;
    }
    cout << MSG_WRONG_ANSWER[0] << answer << MSG_WRONG_ANSWER[1] << endl;
    return false;
}
void handleTransfers(LeitnerBox& leitnerBox, bool result, Flashcard flashcard) {
    if (result) {
        leitnerBox.upgradeFlashcard(flashcard);
    }
    else {
        if (flashcard.wasMistaken()) {
            leitnerBox.downgradeFlashcard(flashcard);
            flashcard.mistakeCorrected();
        }
        else {
            flashcard.wasMistaken();
        }
    }
}

void grading(Day& day, bool result) {
    if (result)
        day.incCorrectAnswers();
    else
        day.incWrongAnswers();
    day.incTotalAnswers();
}

void reviewFlashcards(LeitnerBox& leitnerBox, vector<Flashcard>& todayFlashcards, vector<Day>& days, vector<string> argument) {
    int cardsNum = stoi(argument[1]);
    Day& today = days[leitnerBox.getDay() - 1];
    for (int i = 0; i < cardsNum ; i++) {
        Flashcard flashcard = todayFlashcards[0];
        cout << MSG_FLASHCARD_QUESTION << flashcard.getQuestion() << endl;
        cout << MSG_YOUR_ANSWER;
        string correctAnswer = flashcard.getAnswer();
        bool result = getAnswer(leitnerBox, correctAnswer);
        grading(today, result);
        handleTransfers(leitnerBox, result, flashcard);
        todayFlashcards.erase(todayFlashcards.begin() + i);
    }
    cout << MSG_TODAYS_REVIEW << endl;
}


void checkStreak(LeitnerBox& leitnerBox, vector<Day>& days, vector<Flashcard>& todayFlashcards) {
    int index = leitnerBox.getDay() - 1;
    if (days[index].getTotalAnswers() > 0)
        leitnerBox.incStreak();
    else {
        leitnerBox.resetStreak();
        leitnerBox.downgradeFlashcardsOnZeroStreak();
    }
}

void nextDay(LeitnerBox& leitnerBox, vector<Day>& days, vector<Flashcard>& todayFlashcards) {
    checkStreak(leitnerBox, days, todayFlashcards);
    if (! (todayFlashcards.empty()) )
        leitnerBox.downgradeRemainingFlashcards(todayFlashcards);
    leitnerBox.incDay();
    days.push_back(Day());
    cout << MSG_NEXT_DAY[0] << leitnerBox.getDay() << MSG_NEXT_DAY [1] << leitnerBox.getStreak() << MSG_NEXT_DAY[2] << endl;
}

void showStreak(LeitnerBox& leitnerBox) {
    cout << MSG_STREAK[0] << leitnerBox.getStreak() << MSG_STREAK[1] << endl;
}
void displayReport(int start, int end, int correct, int wrong, int total) {
    if (start != end)
        cout << MSG_REPORT[0] << start+1 << MSG_REPORT[4] << end+1 << endl;
    else
        cout << MSG_REPORT[0] << start+1 << endl;
    cout << MSG_REPORT[1] << correct << endl;
    cout << MSG_REPORT[2] << wrong << endl;
    cout << MSG_REPORT[3] << total << endl;
}

void getReport(vector<Day>& days, vector<string> argument) {
    int start = stoi(argument[1]) - 1; int end = stoi(argument[2]) - 1;
    int sumOfCorrect = 0; int sumOfWrong = 0; int sumOfTotal = 0;
    for (int i = start; i <= end; i++) {
        sumOfCorrect+= days[i].getCorrectAnswers();
        sumOfWrong+= days[i].getWrongAnswers();
        sumOfTotal+= days[i].getTotalAnswers();
    }
    displayReport(start, end, sumOfCorrect, sumOfWrong, sumOfTotal);
}

int getParticapatedDays(vector<Day>& days) {
    int participatedDays = 0;
    for (auto day : days) {
        if (day.getTotalAnswers() > 0)
            participatedDays++;
    }
    return participatedDays;
}
void displayProgressReport(LeitnerBox& leitnerBox, vector<Day>& days) {
    cout << MSG_PROGRESS_REPORT[0] << endl;
    cout << MSG_PROGRESS_REPORT[1] << leitnerBox.getDay() << endl;
    cout << MSG_PROGRESS_REPORT[2] << leitnerBox.getStreak() << endl;
    cout << MSG_PROGRESS_REPORT[3] << getParticapatedDays(days) << endl;
    cout << MSG_PROGRESS_REPORT[4] << leitnerBox.getMasteredFlashcards() << endl;
    cout << MSG_PROGRESS_REPORT[5] << endl;
}

void handleInput(LeitnerBox& leitnerBox, vector<Day>& days) {
    string input;
    while (getline(cin, input)) {
        vector<string> argument = splitStringBy(input, ' ');
        string command = argument[0];

        vector<Flashcard> todayFlashcards;
        leitnerBox.getTodayFlashcards(todayFlashcards);

        if (command == CMD_ADD_FLASHCARD)
            addFlashcard(leitnerBox, argument);
        if (command == CMD_REVIEW_TODAY)
            reviewFlashcards(leitnerBox, todayFlashcards, days, argument);
        if (command == CMD_NEXT_DAY)
            nextDay(leitnerBox, days, todayFlashcards);
        if (command == CMD_STREAK)
            showStreak(leitnerBox);
        if (command == CMD_GET_REPORT)
            getReport(days, argument);
        if (command == CMD_GET_PROGRESS_REPORT)
            displayProgressReport(leitnerBox, days);
    }
}

int main() {
    LeitnerBox leitnerBox;
    Day temp;
    vector<Day> days = {temp};
    handleInput(leitnerBox, days);
}
