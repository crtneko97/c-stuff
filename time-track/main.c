#include <stdio.h>
#include <time.h>
#include <string.h>

void get_user_input(const char *prompt, char *buffer, size_t size);
void write_to_file(const char *filename, const char *project_name, const char *description, const char *start_time, const char *end_time);
void get_current_time_str(char *buffer, size_t size);

int main() {
    char project_name[100];
    char description[100];
    char start_time[100];
    char end_time[100];

    get_user_input("Enter project name: ", project_name, sizeof(project_name));

    get_user_input("What are you doing: ", description, sizeof(description));

    get_current_time_str(start_time, sizeof(start_time));
    printf("Started at: %s\n", start_time);

    printf("Press Enter to stop...");
    getchar();

    get_current_time_str(end_time, sizeof(end_time));
    printf("Stopped at: %s\n\n\n", end_time);

    write_to_file("project_log.csv", project_name, description, start_time, end_time);

    return 0;
}

void get_user_input(const char *prompt, char *buffer, size_t size) {
    if (buffer == NULL || size == 0) {
        return;
    }

    printf("%s", prompt);
    if (fgets(buffer, size, stdin)) {
        char *newline = strchr(buffer, '\n');
        if (newline) {
            *newline = '\0';
        }
    }
}

void write_to_file(const char *filename, const char *project_name, const char *description, const char *start_time, const char *end_time) {
    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "%s,%s,%s,%s\n", project_name, description, start_time, end_time);
        fclose(file);
    } else {
        perror("Failed to open file");
    }
}


void get_current_time_str(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    if (local) {
        strftime(buffer, size, "%Y-%m-%d %H:%M:%S", local);
    } else {
        snprintf(buffer, size, "Unknown time");
    }
}

