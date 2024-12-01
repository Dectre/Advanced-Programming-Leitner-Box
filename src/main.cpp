#include "leitnerbox.hpp"
#include "day.hpp"

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
            flashcard.mistake();
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
    leitnerBox.incStreak();
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
        todayFlashcards.erase(todayFlashcards.begin());
    }
    cout << MSG_TODAYS_REVIEW << endl;
}


void checkStreak(LeitnerBox& leitnerBox, vector<Day>& days, vector<Flashcard>& todayFlashcards) {
    int index = leitnerBox.getDay() - 1;
    if (days[index].getTotalAnswers() == 0) {
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
    todayFlashcards.clear();
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
    vector<Flashcard> todayFlashcards;
    while (getline(cin, input)) {
        vector<string> argument = splitStringBy(input, ' ');
        string command = argument[0];
        if (todayFlashcards.empty())
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