#include <unistd.h>
#include <linux/inotify.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <string.h>

#define ERROR(text) error(1, errno, "%s", text)

struct EventMask {
	int        flag;
	const char *name;

};

int freadsome(void *dest, size_t remain, FILE *file)
{
	char *offset = (char*)dest;
	while (remain) {
		int n = fread(offset, 1, remain, file);
		if (n==0) {
			return -1;
		}

		remain -= n;
		offset += n;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	const char *target;
	if (argc == 1) {
		target = ".";
	} else {
		target = argv[1];
	}

	struct EventMask event_masks[] = {
           {IN_ACCESS        , "IN_ACCESS"}        ,  
           {IN_ATTRIB        , "IN_ATTRIB"}        ,  
           {IN_CLOSE_WRITE   , "IN_CLOSE_WRITE"}   ,  
           {IN_CLOSE_NOWRITE , "IN_CLOSE_NOWRITE"} ,  
           {IN_CREATE        , "IN_CREATE"}        ,  
           {IN_DELETE        , "IN_DELETE"}        ,  
           {IN_DELETE_SELF   , "IN_DELETE_SELF"}   ,  
           {IN_MODIFY        , "IN_MODIFY"}        ,  
           {IN_MOVE_SELF     , "IN_MOVE_SELF"}     ,  
           {IN_MOVED_FROM    , "IN_MOVED_FROM"}    ,  
           {IN_MOVED_TO      , "IN_MOVED_TO"}      ,  
           {IN_OPEN          , "IN_OPEN"}          ,  

           {IN_DONT_FOLLOW   , "IN_DONT_FOLLOW"}   ,  
           {IN_EXCL_UNLINK   , "IN_EXCL_UNLINK"}   ,  
           {IN_MASK_ADD      , "IN_MASK_ADD"}      ,  
           {IN_ONESHOT       , "IN_ONESHOT"}       ,  
           {IN_ONLYDIR       , "IN_ONLYDIR"}       ,  

           {IN_IGNORED       , "IN_IGNORED"}       ,  
           {IN_ISDIR         , "IN_ISDIR"}         ,  
           {IN_Q_OVERFLOW    , "IN_Q_OVERFLOW"}    ,  
           {IN_UNMOUNT       , "IN_UNMOUNT"}       ,  
	};

	int monitor = inotify_init();
	if ( -1 == monitor ) {
		ERROR("monitor");
	}

	int watcher = inotify_add_watch(monitor, target, IN_ALL_EVENTS);
	if ( -1 == watcher  ) {
		ERROR("inotify_add_watch");
	}

	FILE *monitor_file = fdopen(monitor, "r");
	char last_name[1024];
	char name[1024];

	/* event:inotify_event -> name:char[event.len] */
	while (1) {
		struct inotify_event event;
		if ( -1 == freadsome(&event, sizeof(event), monitor_file) ) {
			ERROR("freadsome");
		}
		if (event.len) {
			freadsome(name, event.len, monitor_file);
		} else {
			sprintf(name, "FD: %d\n", event.wd);
		}

		if (strcmp(name, last_name) != 0) {
			puts(name);
			strcpy(last_name, name);
		}

		/* 显示event的mask的含义 */
		for (int i=0; i<sizeof(event_masks)/sizeof(struct EventMask); ++i) {
			if (event.mask & event_masks[i].flag) {
				printf("\t%s\n", event_masks[i].name);
			}
		}
	}
	return 0;
}
