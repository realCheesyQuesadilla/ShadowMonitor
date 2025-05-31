#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>

#define WATCHED_FILE "/etc/shadow"
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF (1024 * EVENT_SIZE)

#define XOR_CODE "PASSCODE"
#define XOR_TIMES 3


void EncodeFile(char *File)
{
    return;
}

int main() {
    // check inotify return
    int inotify_fd = 0;
    // check watch return
    int watch_fd = 0;

    // make buffer for inotify_event
    char buffer[BUF];
    
    printf("Shadow monitor initialized\n");
    printf("Monitoring: %s\n", WATCHED_FILE);
    
    // intialize inotify
    inotify_fd = inotify_init();

    if (inotify_fd < 0)
    {
        printf("Error opening inotify\n");
        exit(EXIT_FAILURE);
    }

    // now to make watch
    watch_fd = inotify_add_watch(inotify_fd, WATCHED_FILE, IN_MODIFY);

    if (watch_fd < 0)
    {
        printf("Error reserving watcher\n");
        printf("Is this running in root?\n");
        exit(EXIT_FAILURE);
    }

    printf("Successfully monitoring %s using watch descriptor %d \n", WATCHED_FILE, watch_fd);
    printf("Running...\n Enter CTRL+C to stop\n");

    while(1)
    {
        // read inotify fd
        int length = read(inotify_fd, buffer, BUF);
        if (length < 0 )
        {
            printf("Error reading\n");
            break;
        }

        // process any events
        int i = 0;
        while (i < length)
        {
            struct inotify_event* event = (struct inotify_event *) &buffer[i];

            printf("Event detected\n");
            
            // Currently code only does modify so no need to check other notifies
            EncodeFile(WATCHED_FILE);

            i += EVENT_SIZE + event->len;
        }

    }

    inotify_rm_watch(inotify_fd, watch_fd);
    close(inotify_fd);
    return 0;
}
