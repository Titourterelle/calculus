#ifndef SCORE_H
#define SCORE_H

struct Score
{
    int maxCalculs = 10;
    int calculsMade = 0;
    int goodAnswers = 0;

    bool isFinished() const
    {
        return calculsMade >= maxCalculs;
    }
};

#endif // SCORE_H
