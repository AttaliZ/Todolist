#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <windows.h>

#define TK 100
#define LG 100
#define NAME 100

typedef struct {
    char des[LG];
    int prio;
    int day;
    int month;
    int year;
    int comp;
} task;

task list[TK];
int numt = 0;

int maxmonth(int month) {
    return (month >= 1 && month <= 12);
}

int maxyear(int year) {
    return (year >= 1900 && year <= 9999);
}

void addtask(char des[], int prio, int day, int month, int year) {
    if (numt < TK) {
        strcpy(list[numt].des, des);
        list[numt].prio = prio;
        list[numt].day = day;
        list[numt].month = month;
        list[numt].year = year;
        list[numt].comp = 0;
        numt++;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Task added successfully!\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Sorry list is full.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void output() {
    if (numt == 0) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("No tasks found.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        printf("To-Do List:\n");
        for (int i = 0; i < numt; i++) {
            printf("%d. %s - Priority: %d - Date: %02d/%02d/%d - %s\n", i + 1, list[i].des, list[i].prio, list[i].day, list[i].month, list[i].year, list[i].comp ? "Complete" : "Incomplete");
        }
    }
}

void mark(int index) {
    if (index >= 0 && index < numt) {
        list[index].comp = 1;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Task marked as complete.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Invalid task index.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void Delete(int indexdl) {
    if (indexdl >= 0 && indexdl < numt) {
        for (int i = indexdl; i < numt - 1; i++) {
            strcpy(list[i].des, list[i + 1].des);
            list[i].prio = list[i + 1].prio;
            list[i].day = list[i + 1].day;
            list[i].month = list[i + 1].month;
            list[i].year = list[i + 1].year;
            list[i].comp = list[i + 1].comp;
        }
        numt--;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Task deleted successfully.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Invalid task index.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void edit(int Nindex, char newdes[], int newprio, int newday, int newmon, int newyear) {
    if (Nindex >= 0 && Nindex < numt) {
        strcpy(list[Nindex].des, newdes);
        list[Nindex].prio = newprio;
        list[Nindex].day = newday;
        list[Nindex].month = newmon;
        list[Nindex].year = newyear;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Task edited successfully.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Invalid task index.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void clear() {
    numt = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    printf("All tasks cleared.\n");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void save(const char *foldername) {
    char filename[LG];
    sprintf(filename, "%s/ku101.txt", foldername);

    if (_mkdir(foldername) == -1) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Error: Unable to create folder '%s'.\n", foldername);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return;
    }

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < numt; i++) {
            fprintf(file, "%s|%d|%d|%d|%d|%d\n", list[i].des, list[i].prio, list[i].day, list[i].month, list[i].year, list[i].comp);
        }
        fclose(file);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Tasks saved to folder '%s' successfully.\n", foldername);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Error: Unable to save tasks to folder '%s'.\n", foldername);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void load(const char *foldername) {
    char filename[NAME];
    sprintf(foldername, "%s/ku101.txt", foldername);
    FILE *file = fopen(foldername, "r");
    if (file != NULL) {
        char temp[LG];
        int prio, day, month, year, comp;
        while (fgets(temp, LG, file) != NULL) {
            sscanf(temp, "%[^|]|%d|%d|%d|%d|%d", list[numt].des, &prio, &day, &month, &year, &comp);
            list[numt].prio = prio;
            list[numt].day = day;
            list[numt].month = month;
            list[numt].year = year;
            list[numt].comp = comp;
            numt++;
        }
        fclose(file);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Tasks loaded from folder '%s' successfully.\n", foldername);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Error: Unable to load tasks from folder '%s'.\n", foldername);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void setprio() {
    for (int i = 0; i < numt - 1; i++) {
        for (int j = 0; j < numt - i - 1; j++) {
            if (list[j].prio < list[j + 1].prio) {
                task temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
    printf("Tasks sorted by priority.\n");
}
void rainbow(char *text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to get console handle\n");
        return;
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("%s", text);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("%s", text);

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    printf("%s", text);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    printf("%s", text);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE);
    printf("%s", text);

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
    printf("%s", text);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void showPG() {
    printf("Progress Graph:\n");
    for (int i = 0; i < numt; i++) {
        printf("%d. %s - ", i + 1, list[i].des);
        for (int j = 0; j < 10; j++) {
            if (j < list[i].prio) {
               const char *message = "#";
    	rainbow(message);
            } else {
                printf("-");
            }
        }
        printf(" - %s\n", list[i].comp ? "Completed" : "Incomplete");
    }
}

void backup() {
    FILE *file = fopen("ku101_backup.txt", "w");
    if (file != NULL) {
        for (int i = 0; i < numt; i++) {
            fprintf(file, "%s|%d|%d|%d|%d|%d\n", list[i].des, list[i].prio, list[i].day, list[i].month, list[i].year, list[i].comp);
        }
        fclose(file);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Tasks backed up successfully.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Error: Unable to backup tasks.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

void re() {
    FILE *file = fopen("ku101_backup.txt", "r");
    if (file != NULL) {
        clear(); 
        char temp[LG];
        int prio, day, month, year, comp;
        while (fgets(temp, LG, file) != NULL) {
            sscanf(temp, "%[^|]|%d|%d|%d|%d|%d", list[numt].des, &prio, &day, &month, &year, &comp);
            list[numt].prio = prio;
            list[numt].day = day;
            list[numt].month = month;
            list[numt].year = year;
            list[numt].comp = comp;
            numt++;
        }
        fclose(file);
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("Tasks restored successfully.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf("Error: Unable to restore tasks from backup.\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

int main() {
    int choice, index, prio, day, month, year;
    char des[LG], newdes[LG];
    char foldername[NAME];
    HANDLE hConsole;

    printf("Welcome to the To-Do List Program!");
    do {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY); 
        printf("\n1. Add Task\n2. Display Tasks\n3. Mark Task as Complete\n4. Delete Task\n5. Edit Task\n6. Clear All Tasks\n7. Save Tasks to Folder\n8. Load Tasks from Folder\n9. Sort Tasks by Priority\n10. Show Progress Graph\n11. Backup Tasks\n12. Restore Tasks\n13. Quit\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                do {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    printf("Enter task description: ");
                    scanf(" %[^\n]", des);
                    printf("Enter priority (1 - 10): ");
                    scanf("%d", &prio);
                    printf("Enter day (1 - 31): ");
                    scanf("%d", &day);
                    printf("Enter month (1 - 12): ");
                    scanf("%d", &month);
                    printf("Enter year (1900 - 9999): ");
                    scanf("%d", &year);
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    if (!maxmonth(month)) {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("Invalid month. Please enter a month between 1 and 12.\n");
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    } else if (!maxyear(year)) {
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                        printf("Invalid year. Please enter a year between 1900 and 9999.\n");
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    }
                } while (!maxmonth(month) || !maxyear(year));
                addtask(des, prio, day, month, year);
                break;
            case 2:
                output();
                break;
            case 3:
                printf("Enter the index of the task to mark as complete: ");
                scanf("%d", &index);
                mark(index - 1);
                break;
            case 4:
                printf("Enter the index of the task to delete: ");
                scanf("%d", &index);
                Delete(index - 1);
                break;
            case 5:
                printf("Enter the index of the task to edit: ");
                scanf("%d", &index);
                printf("Enter new task description: ");
                scanf(" %[^\n]", newdes);
                printf("Enter new priority (1 - 10): ");
                scanf("%d", &prio);
                printf("Enter new day (1 - 31): ");
                scanf("%d", &day);
                printf("Enter new month (1 - 12): ");
                scanf("%d", &month);
                printf("Enter new year (1900 - 9999): ");
                scanf("%d", &year);
                edit(index - 1, newdes, prio, day, month, year);
                break;
            case 6:
                clear();
                break;
            case 7:
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                printf("Enter folder name to save tasks to: ");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                scanf("%s", foldername);
                save(foldername);
                break;

            case 8:
                printf("Enter folder name to load tasks: ");
                scanf(" %[^\n]", foldername);
                load(foldername);
                break;
            case 9:
                setprio();
                break;
            case 10:
                showPG();
                break;
            case 11:
                backup();
                break;
            case 12:
                re();
                break;
            case 13:
                printf("Exiting program...\n");
                break;
            default:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                printf("Invalid choice. Please enter a number between 1 and 13.\n");
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    } while (choice != 13);

    return 0;
}
