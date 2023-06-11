#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "session.h"
#include "tutor.h"
#include "student.h"
#include "constants.h"

// Declare global variables
struct Session sessions[MAX_SESSIONS]; // Array to store session records
struct Tutor tutors[MAX_TUTORS]; // Array to store tutor records
struct Student students[MAX_STUDENTS]; // Array to store student records
int tutorCount = 0; // Count of tutors in the system
int sessionCount = 0; // Count of sessions in the system
int studentCount = 0; // Count of students in the system

int userType; // Global variable to store the user's role

/**
 * Initializes the data by adding pre-defined tutor and session records.
 */
void initializeData() {
    FILE *tutorsFile = fopen("tutors.txt", "r");
    if (tutorsFile == NULL) {
        printf("Failed to open tutors.txt file.\n");
        exit(1);
    }

    FILE *sessionsFile = fopen("sessions.txt", "r");
    if (sessionsFile == NULL) {
        printf("Failed to open sessions.txt file.\n");
        exit(1);
    }

    char line[100];

    // Read tutors data
    while (fgets(line, sizeof(line), tutorsFile) != NULL) {
        char *code = strtok(line, ",");
        char *name = strtok(NULL, ",");
        char *title = strtok(NULL, ",");
        char *password = strtok(NULL, "\n");

        strcpy(tutors[tutorCount].id, code);
        strcpy(tutors[tutorCount].name, name);
        strcpy(tutors[tutorCount].title, title);
        strcpy(tutors[tutorCount].password, password);

        tutorCount++;
    }

    // Read sessions data
    while (fgets(line, sizeof(line), sessionsFile) != NULL) {
        char *code = strtok(line, ",");
        char *title = strtok(NULL, ",");
        char *day = strtok(NULL, ",");
        char *startTime = strtok(NULL, ",");
        char *location = strtok(NULL, ",");
        char *tutorCode = strtok(NULL, "\n");

        strcpy(sessions[sessionCount].code, code);
        strcpy(sessions[sessionCount].title, title);
        strcpy(sessions[sessionCount].day, day);
        strcpy(sessions[sessionCount].start_time, startTime);
        strcpy(sessions[sessionCount].location, location);
        strcpy(sessions[sessionCount].tutor_code, tutorCode);

        sessionCount++;
    }

    fclose(tutorsFile);
    fclose(sessionsFile);
}
void displayAdminMenu() {
    printf("Admin Menu\n");
    printf("1. Add Tutor\n");
    printf("2. Add Session\n");
    printf("3. Register Student\n");
    printf("4. Enroll Student into a Session\n");
    printf("5. List Sessions and Students\n");
    printf("6. Logout\n");
    printf("Enter your choice: ");
}

void displayTutorMenu() {
    printf("Tutor Menu\n");
    printf("1. List Assigned Sessions\n");
    printf("2. Logout\n");
    printf("Enter your choice: ");
}

void displayStudentMenu() {
    printf("Student Menu\n");
    printf("1. List Assigned Sessions\n");
    printf("2. Enroll in Session\n");
    printf("3. Logout\n");
    printf("Enter your choice: ");
}

void addTutor() {
    if (tutorCount == MAX_TUTORS) {
        printf("Maximum tutor limit reached!\n");
        return;
    }

    struct Tutor tutor;
    printf("Enter Tutor ID: ");
    scanf(" %s", tutor.id);
    printf("Enter Tutor Name: ");
    scanf(" %[^\n]", tutor.name);
    printf("Enter Tutor Title: ");
    scanf(" %[^\n]", tutor.title);
    printf("Enter Tutor Password: ");
    scanf(" %[^\n]", tutor.password);

    tutors[tutorCount] = tutor;
    tutorCount++;

    printf("Tutor added successfully!\n");
}

void addSession() {
    if (sessionCount == MAX_SESSIONS) {
        printf("Maximum session limit reached!\n");
        return;
    }

    struct Session session;
    printf("Enter Session Code: ");
    scanf(" %s", session.code);
    printf("Enter Session Title: ");
    scanf(" %[^\n]", session.title);
    printf("Enter Session Day: ");
    scanf(" %[^\n]", session.day);
    printf("Enter Session Start Time: ");
    scanf(" %[^\n]", session.start_time);
    printf("Enter Session Location: ");
    scanf(" %[^\n]", session.location);

    int tutorIndex = -1;
    char tutorCode[20];
    printf("Available Tutors:\n");
    for (int i = 0; i < tutorCount; i++) {
        printf("%s. %s\n", tutors[i].id, tutors[i].name);
    }

    while (tutorIndex == -1) {
        printf("Enter Tutor Code: ");
        scanf(" %s", tutorCode);

        for (int i = 0; i < tutorCount; i++) {
            if (strcmp(tutors[i].id, tutorCode) == 0) {
                tutorIndex = i;
                break;
            }
        }

        if (tutorIndex == -1) {
            printf("Invalid Tutor Code! Please try again.\n");
        }
    }

    strcpy(session.tutor_code, tutorCode);
    session.numEnrolledStudents = 0; // Initialize numEnrolledStudents to 0

    sessions[sessionCount] = session;
    sessionCount++;

    printf("Session added successfully!\n");
}
void registerStudent() {
    if (studentCount == MAX_STUDENTS) {
        printf("Maximum student limit reached!\n");
        return;
    }

    struct Student student;
    printf("Enter Student ID: ");
    scanf(" %s", student.id);
    printf("Enter Student Name: ");
    scanf(" %[^\n]", student.name);
    printf("Enter Student Password: ");
    scanf(" %[^\n]", student.password);
    student.numAssignedSessions = 0;
    
    students[studentCount] = student;
    studentCount++;

    printf("Student registered successfully!\n");
}

void enrollStudent() {
    if (sessionCount == 0) {
        printf("No sessions available for enrollment!\n");
        return;
    }

    printf("Available Sessions:\n");
    for (int i = 0; i < sessionCount; i++) {
        printf("%s. %s\n", sessions[i].code, sessions[i].title);
    }

    char sessionCode[20];
    printf("Enter Session Code: ");
    scanf(" %s", sessionCode);

    int sessionIndex = -1;
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].code, sessionCode) == 0) {
            sessionIndex = i;
            break;
        }
    }

    if (sessionIndex != -1) {
        printf("Available Students:\n");
        for (int i = 0; i < studentCount; i++) {
            printf("%s. %s\n", students[i].id, students[i].name);
        }

        char studentID[20];
        printf("Enter Student ID: ");
        scanf(" %s", studentID);

        int studentIndex = -1;
        for (int i = 0; i < studentCount; i++) {
            if (strcmp(students[i].id, studentID) == 0) {
                studentIndex = i;
                break;
            }
        }

        if (studentIndex != -1) {
            struct Session* session = &sessions[sessionIndex];
            struct Student* student = &students[studentIndex];
            
            // Check if the student is already enrolled in the session
            for (int i = 0; i < session->numEnrolledStudents; i++) {
                if (strcmp(session->studentIDs[i], student->id) == 0) {
                    printf("Student '%s' is already enrolled in session '%s'.\n", student->name, session->code);
                    return;
                }
            }
            // printf("Check if the student is already enrolled in the student %d\n",student->numAssignedSessions);
            
            // Check if the student is already enrolled in the session
            for (int i = 0; i < student->numAssignedSessions; i++) {
                if (strcmp(student->assignedSessions[i].code, session->code) == 0) {
                    printf("Student '%s' is already enrolled in session '%s'.\n", student->name, session->code);
                    return;
                }
            }
            // printf("Session '%d' is already full'.\n", session->numEnrolledStudents);
            
            // printf("Check if the student is already enrolled in the student");
            // Enroll the student in the session
            if (session->numEnrolledStudents < MAX_STUDENTS_PER_SESSION) {
                strcpy(session->studentIDs[session->numEnrolledStudents], student->id);
                session->numEnrolledStudents++;
                // printf("Check if the student is already enrolled in the student2"); 
                // Add the session to the student's assigned sessions
                strcpy(student->assignedSessions[student->numAssignedSessions].code, session->code);
                strcpy(student->assignedSessions[student->numAssignedSessions].tutor_code, session->tutor_code);
                strcpy(student->assignedSessions[student->numAssignedSessions].location, session->location);
                student->numAssignedSessions++;

                printf("Student '%s' has been enrolled in session '%s'.\n", student->name, session->code);
            } else {
                printf("Session '%s' is already full. Cannot enroll student '%s'.\n", session->code, student->name);
            }
        } else {
            printf("Invalid Student ID! Enrollment failed.\n");
        }
    } else {
        printf("Invalid Session Code! Enrollment failed.\n");
    }
}

char* getStudentNameByID(const char* studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
            char* studentName = malloc(strlen(students[i].name) + 1);
            strcpy(studentName, students[i].name);
            return studentName;
        }
    }
    return NULL; // Return NULL if student ID is not found
}
void listSessionsAndStudents() {
    printf("Listing of Programming Café sessions and participating students:\n");
    printf("Student Name, Session Code, Tutor Code, Location\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < sessionCount; i++) {
        for (int j = 0; j < sessions[i].numEnrolledStudents; j++) {
            char* studentName = getStudentNameByID(sessions[i].studentIDs[j]);
            printf("%s, %s, %s, %s\n", studentName, sessions[i].code, sessions[i].tutor_code, sessions[i].location);
        }
    }
}

void listAssignedSessionsForStudent(struct Student student) {
    printf("Assigned Sessions for Student: %s\n", student.name);
    printf("--------------------------------------------------\n");
    printf("Session Code\tTutor Code\tLocation\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < student.numAssignedSessions; i++) {
        printf("%s\t\t%s\t\t%s\n", student.assignedSessions[i].code, student.assignedSessions[i].tutor_code, student.assignedSessions[i].location);
    }

    printf("--------------------------------------------------\n");
}
void enrollInSession(struct Student* student) {
    printf("Available Sessions:\n");
    for (int i = 0; i < sessionCount; i++) {
        printf("%s. %s\n", sessions[i].code, sessions[i].title);
    }
    
    char sessionCode[100];
    printf("Enter the Session Code you want to enroll in: ");
    scanf("%s", sessionCode);

    // Find the session with the given code
    int sessionIndex = -1;
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].code, sessionCode) == 0) {
            sessionIndex = i;
            break;
        }
    }

    // Check if the session exists
    if (sessionIndex == -1) {
        printf("Invalid Session Code. Enrollment failed.\n");
        return;
    }

    // Check if the session is already full
    // Assuming a session can have a maximum capacity of MAX_STUDENTS_PER_SESSION students
    if (sessions[sessionIndex].numEnrolledStudents >= MAX_STUDENTS_PER_SESSION) {
        printf("Session is already full. Enrollment failed.\n");
        return;
    }
     
    // Check if the student is already enrolled in the session
    for (int i = 0; i < student->numAssignedSessions; i++) {
        if (strcmp(student->assignedSessions[i].code, sessionCode) == 0) {
            printf("Student '%s' is already enrolled in session '%s'.\n", student->name, sessionCode);
            return;
        }
    }
    

    // Enroll the student in the session
    strcpy(sessions[sessionIndex].studentIDs[sessions[sessionIndex].numEnrolledStudents], student->id);
    sessions[sessionIndex].numEnrolledStudents++;

    // Update the assigned sessions for the student
    strcpy(student->assignedSessions[student->numAssignedSessions].code, sessions[sessionIndex].code);
    strcpy(student->assignedSessions[student->numAssignedSessions].tutor_code, sessions[sessionIndex].tutor_code);
    strcpy(student->assignedSessions[student->numAssignedSessions].location, sessions[sessionIndex].location);
    student->numAssignedSessions++;

    printf("Enrollment successful.\n");
}

void loginAsStudent() {
    char id[100];
    char password[100];
    int choice;

    printf("Enter your ID: ");
    scanf("%s", id);
    printf("Enter your password: ");
    scanf("%s", password);

    // Validate the login credentials
    int isValidLogin = 0;
    struct Student* loggedInStudent;

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, id) == 0 && strcmp(students[i].password, password) == 0) {
            isValidLogin = 1;
            loggedInStudent = &students[i];
            break;
        }
    }

    if (!isValidLogin) {
        printf("Invalid login credentials.\n");
        return;
    }

    do {
        displayStudentMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                listAssignedSessionsForStudent(*loggedInStudent);
                break;
            case 2:
                enrollInSession(loggedInStudent);
                break;
            case 3:
                printf("Logged out as Student.\n");
                userType = 0; // Set the user type to 0 to return to the main menu
                break; // Break from the switch statement to go back to the main menu
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (choice != 3);
}

void listAssignedSessions(char* tutorCode) {
    printf("Assigned Sessions: %s \n",tutorCode);
    
    // Iterate through all sessions and check if the tutor code matches
    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].tutor_code, tutorCode) == 0) {
            printf("Session Code: %s\n", sessions[i].code);
            printf("Title: %s\n", sessions[i].title);
            printf("Day: %s\n", sessions[i].day);
            printf("Start Time: %s\n", sessions[i].start_time);
            printf("Location: %s\n", sessions[i].location);
            printf("-------------------------\n");
        }
    }

    printf("\n");
}
void loginAsTutor() {
    char code[100];
    char password[100];
    int found = 0;
    int choice;

    printf("Enter tutor ID: ");
    scanf("%s", code);
    printf("Enter password: ");
    scanf("%s", password);
    
    // printf("tutorCount %d",tutorCount);
    printf("Successfully Logged in! \n\n ");

    for (int i = 0; i < tutorCount; i++) {
        if (strcmp(tutors[i].id, code) == 0 && strcmp(tutors[i].password, password) == 0) {
            found = 1;
            // listAssignedSessions(code); // Call the function to list assigned sessions
            break;
        }
    }

    if (found) {
        do {
            displayTutorMenu();
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    listAssignedSessions(code); // Call the function to list assigned sessions
                    break;
                case 2:
                    printf("Logged out as Tutor.\n");
                    userType = 0; // Set the user type to 0 to return to the main menu
                    break; // Break from the switch statement to go back to the main menu
                // case 3:
                //     printf("Going back to Main Menu.\n");
                //     userType = -1; // Set the user type to -1 to return to the main menu
                //     break; // Break from the switch statement to go back to the main menu
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }
            printf("\n");
        } while (choice != 2 && choice != 3);
    } else {
        printf("Invalid tutor code or password. Login failed.\n");
        userType = -1; // Set the user type to -1 to return to the main menu
    }
}

void loginAsAdmin() {
    int choice;
    do {
        displayAdminMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addTutor();
                break;
            case 2:
                addSession();
                break;
            case 3:
                registerStudent();
                break;
            case 4:
                enrollStudent();
                break;
            case 5:
                listSessionsAndStudents();
                break;
            case 6:
                printf("Logged out as Admin.\n");
                userType = 0; // Set the user type to 0 to return to the main menu
                break; // Break from the switch statement to go back to the main menu
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (choice != 6);
}
int main() {
    initializeData();

    do {
        printf("User Type:\n");
        printf("1. Admin\n");
        printf("2. Tutor\n");
        printf("3. Student\n");
        printf("Enter your choice: ");
        scanf("%d", &userType);

        switch (userType) {
            case 1:
                loginAsAdmin();
                break;
            case 2:
                loginAsTutor();
                break;
            case 3:
                loginAsStudent();
                break;
            default:
                printf("Invalid user type. Exiting program.\n");
                break;
        }

        printf("\n");
    } while (userType != -1); // Continue looping until user selects to return to main menu

    printf("Returned to Main Menu. Exiting program.\n");

    return 0;
}