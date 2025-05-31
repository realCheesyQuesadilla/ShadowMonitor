#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>

#define WATCHED_FILE "/etc/shadow"
#define EVENT_SIZE (sizeof(struct inotify_event))


int main() {
    // check inotify return
    int inotify_fd = 0;
    // check watch return
    int watch_fd = 0;

    printf("Shadow monitor initialized\n");
    printf("Monitoring: %s\n", WATCHED_FILE);
    
    // intialize inotify
    inotify_fd = inotify_init();

    if (inotify_fd < 0)
    {
        printf("Error opening inotify\n");
        close(inotify_fd);
        exit(EXIT_FAILURE);
    }

    printf("inotify successful\n");

    return 0;
}