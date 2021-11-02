#pragma once

#define SECOND 1
#define MSECOND SECOND/1000
#define MINUTE 60 * SECOND
#define HOUR 60 * MINUTE
#define TIMER_TEXT_CHARS 15

void getTimerText(float timer, char *out);

// Serialização do Tempo
// Quase ISO 8601, assim: 'PT00H00M00.000S' 15 chars;
// Valores maiores que 99H devem retornar erros;
#define TIME_S_CHARS 15


void textSerializeTimer(float timer, char *out);

void textDeserializeTimer(const char *text, float *timerOut);

int getHours(float timer);

int getMinutes(float timer);

int getSeconds(float timer);

int getMSeconds(float timer);