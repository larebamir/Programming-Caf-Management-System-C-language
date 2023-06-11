#include "constants.h"
#ifndef STUDENT_H
#define STUDENT_H



struct Student {
    char id[20];
    char name[50];
    char password[20];
    struct Session assignedSessions[MAX_ASSIGNED_SESSIONS];
    int numAssignedSessions;
};

extern struct Student students[MAX_STUDENTS];
extern int studentCount;

#endif /* STUDENT_H */
