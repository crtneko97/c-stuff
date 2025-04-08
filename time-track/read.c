#define _XOPEN_SOURCE 700  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE 1024

struct table {
    char project[30];
    char agenda[120];
    char start_time[32];
    char end_time[32];
    char sum_time[20]; 
};


void read_file(const char* file_name);
void calculate_duration(const char* start, const char* end, char* output_buffer);

int main(void) 
{
    read_file("project_log.csv");
    return 0;
}

void read_file(const char* file_name) 
{
    FILE *ftpr = fopen(file_name, "r");

    if (!ftpr) 
    {
        perror("Cannot open file");
        return;
    }

    char get_file_information[MAX_LINE];

    while (fgets(get_file_information, MAX_LINE, ftpr)) 
    {
        struct table entry;

        sscanf(get_file_information, "%29[^,],%119[^,],%31[^,],%31[^\n]",
               entry.project, entry.agenda, entry.start_time, entry.end_time);

        calculate_duration(entry.start_time, entry.end_time, entry.sum_time);

        printf("Project: %s\nAgenda: %s\nStart: %s\nEnd: %s\nTime Worked: %s\n\n",
               entry.project, entry.agenda, entry.start_time, entry.end_time, entry.sum_time);
    }

    fclose(ftpr);
}


void calculate_duration(const char* start, const char* end, char* output_buffer) 
{
    struct tm tm_start = {0}, tm_end = {0};

    if (strptime(start, "%Y-%m-%d %H:%M:%S", &tm_start) == NULL ||
        strptime(end, "%Y-%m-%d %H:%M:%S", &tm_end) == NULL) {
        strcpy(output_buffer, "Invalid time");
        return;
    }

    time_t t_start = mktime(&tm_start);
    time_t t_end = mktime(&tm_end);

    if (t_start == -1 || t_end == -1) {
        strcpy(output_buffer, "Time error");
        return;
    }

    double seconds = difftime(t_end, t_start);
    
    int hours = (int)seconds / 3600;
    int minutes = ((int)seconds % 3600) / 60;
    int secs = (int)seconds % 60;

    sprintf(output_buffer, "%02dh %02dm %02ds", hours, minutes, secs);
}

