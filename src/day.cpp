#include "day.hpp"

int Day::getCorrectAnswers() { return correctAnswers; }
int Day::getWrongAnswers() { return wrongAnswers; }
int Day::getTotalAnswers() {return totalAnswers; }
void Day::incCorrectAnswers() { correctAnswers+= 1; }
void Day::incWrongAnswers() { wrongAnswers+= 1; }
void Day::incTotalAnswers() { totalAnswers+= 1; }
