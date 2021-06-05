#ifndef TIME_H
#define TIME_H

void timer(double *temps, bool *lose);
bool chrono(clock_t start, bool *lose);
double chrono_end(clock_t start);

#endif