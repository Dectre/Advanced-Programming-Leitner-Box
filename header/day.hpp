#pragma once

class Day {
public:
    Day() : correctAnswers(0), wrongAnswers(0), totalAnswers(0) {}
    int getCorrectAnswers();
    int getWrongAnswers();
    int getTotalAnswers();
    void incCorrectAnswers();
    void incWrongAnswers();
    void incTotalAnswers();
private:
    int correctAnswers;
    int wrongAnswers;
    int totalAnswers;
};
