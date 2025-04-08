#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct upload_status {
    const char *data;
    size_t bytes_read;
};

size_t payload_source(char *ptr, size_t size, size_t nmemb, void *userp) {
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    size_t room = size * nmemb;

    if (upload_ctx->data) {
        size_t len = strlen(upload_ctx->data);
        if (upload_ctx->bytes_read >= len) {
            return 0;
        }

        size_t remaining = len - upload_ctx->bytes_read;
        if (room > remaining)
            room = remaining;

        memcpy(ptr, upload_ctx->data + upload_ctx->bytes_read, room);
        upload_ctx->bytes_read += room;

        return room;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <receiver@example.com> <email_file.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *receiver = argv[1];
    const char *email_file = argv[2];

    const char *smtp_url = getenv("SMTP_SERVER");
    const char *smtp_user = getenv("SMTP_USER");
    const char *smtp_pass = getenv("SMTP_PASS");

    if (!smtp_url || !smtp_user || !smtp_pass) {
        fprintf(stderr, "SMTP environment variables not set properly.\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(email_file, "rb");
    if (!file) {
        perror("Error opening email file");
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    char *email_body = malloc(filesize + 1);
    fread(email_body, 1, filesize, file);
    email_body[filesize] = '\0';
    fclose(file);

    CURL *curl = curl_easy_init();
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx = { email_body, 0 };

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, smtp_url);
        curl_easy_setopt(curl, CURLOPT_USERNAME, smtp_user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, smtp_pass);

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, smtp_user);

        recipients = curl_slist_append(recipients, receiver);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printf("Email sent successfully to %s\n", receiver);

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    free(email_body);
    return (int)res;
}
