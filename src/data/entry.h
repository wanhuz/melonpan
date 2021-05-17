#pragma once
#include <qstring.h>

/*Data type for dictionary entry. Each entry will have a kanji, readings, glossary and how common it is in real-life (frequency)*/
class entry {
private:
    QString kanji;
    QString reading;
    QString gloss;
    int freq;

public:
    entry(const QString kanji,  const QString reading,  const QString gloss, const int freq) { 
        this->kanji = kanji; 
        this->reading = reading; 
        this->gloss = gloss; 
        this->freq = freq;
    }

    QString getKanji() { return this->kanji; }
    QString getReading() { return this->reading; }
    QString getGloss() { return this->gloss; }
    int getFreq() { return this->freq; }
    void setFreq(int freq) { if (freq < 101 && freq > -1) { this->freq = freq; } }
};