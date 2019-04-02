#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>
#include <dirent.h>

#define MAX_STRTMP_LEN 128

#define MAX_DEVPATH_LEN 256
#define RBUF_SZ 128
#define DIALUP_SOCKET "/var/volatile/dialup.skt"

void thr_pppd(void *args);
int is_cmd_running(const char *cmd);

int main(int argc, char **argv)
{
	int ret;
	int srvfd, clifd;
	int srvlen, clilen;
	struct sockaddr_un srvaddr, cliaddr;
	char rbuf[RBUF_SZ];

	pthread_t tid;

	unlink(DIALUP_SOCKET);

	srvfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (-1 == srvfd) {
		perror("socket error()");
		exit(EXIT_FAILURE);
	}
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sun_family = AF_UNIX;
	strcpy(srvaddr.sun_path, DIALUP_SOCKET);
	srvlen = sizeof(srvaddr);

	ret = bind(srvfd, (struct sockaddr *)&srvaddr, srvlen);
	if (-1 == ret) {
		perror("bind() error");
		exit(EXIT_FAILURE);
	}
	ret = listen(srvfd, 8);
	if (-1 == ret) {
		perror("listen() error");
		exit(EXIT_FAILURE);
	}
	while (1) {
		clifd = accept(srvfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
		ret = read(clifd, rbuf, RBUF_SZ-1);

		printf("[d] fd: %d, rr: %d\n", clifd, ret);

		if (ret > 0) {
			rbuf[ret] = '\0';
			printf("[d] SOCK RD %d bytes: %s\n", ret, rbuf);
			if (!strcmp(rbuf, "PPPD")) {
				pthread_create(&tid, NULL, (void *)thr_pppd, (void *)0);
			}
		}
		close(clifd);
	}

	exit(EXIT_SUCCESS);
}

void thr_pppd(void *args)
{
	while (1 == is_cmd_running("pppd") || 1 == is_cmd_running("chat")) {
		system("killall pppd; sleep 3; killall chat");
	}

	system("pppd call evdo &");
}
int is_cmd_running(const char *cmd)
{
	DIR *dir = NULL;
	struct dirent *ptr = NULL;
	FILE *fp = NULL;
	char cmdpath[MAX_STRTMP_LEN] = {0};
	char cmdname[MAX_STRTMP_LEN] = {0};
	int ret = 0;

	dir = opendir("/proc");
	if (NULL != dir) {
		while (NULL != (ptr = readdir(dir))) {
			if ((0 == strcmp(ptr->d_name, ".")) || (0 == strcmp(ptr->d_name, ".."))) {
				continue;
			}   
			if (DT_DIR != ptr->d_type) {
				continue;
			}   

			sprintf(cmdpath, "/proc/%s/cmdline", ptr->d_name);
			fp = fopen(cmdpath, "r");
			if (NULL != fp) {
				fread(cmdname, 1, MAX_STRTMP_LEN, fp);
				cmdname[MAX_STRTMP_LEN-1] = '\0';
				fclose(fp);
				if (cmdname == strstr(cmdname, cmd)) {
					ret = 1;
					break;
				}   
			}   
		}   
		closedir(dir);
	}   

	return ret;
}
