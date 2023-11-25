#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "utils.h"

#define MAX_SERVERS 10

struct Server {
    char ip[255];
    int port;
};

int read_servers(const char *filename, struct Server *servers, int max_servers) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Can't open file %s\n", filename);
        return -1;
    }

    int i = 0;
    while (i < max_servers && fscanf(file, "%s %d", servers[i].ip, &servers[i].port) == 2) {
        i++;
    }

    fclose(file);
    return i;
}

int main(int argc, char **argv) {
  uint64_t k = -1;
  uint64_t mod = -1;
  char servers[255] = {'\0'}; // TODO: explain why 255

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"k", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
                                      {"servers", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1)
      break;

    switch (c) {
    case 0: {
      switch (option_index) {
      case 0:
        ConvertStringToUI64(optarg, &k);
        // TODO: your code here
        break;
      case 1:
        ConvertStringToUI64(optarg, &mod);
        // TODO: your code here
        break;
      case 2:
        // TODO: your code here
        memcpy(servers, optarg, strlen(optarg));
        break;
      default:
        printf("Index %d is out of options\n", option_index);
      }
    } break;

    case '?':
      printf("Arguments error\n");
      break;
    default:
      fprintf(stderr, "getopt returned character code 0%o?\n", c);
    }
  }

  if (k == -1 || mod == -1 || !strlen(servers)) {
    fprintf(stderr, "Using: %s --k 1000 --mod 5 --servers /path/to/file\n",
            argv[0]);
    return 1;
  }

  unsigned int servers_num = read_servers(servers, to, MAX_SERVERS);
if (servers_num <= 0) {
    fprintf(stderr, "No servers found in file %s\n", servers);
    return 1;
}

uint64_t begin = 1;
uint64_t end = k;
uint64_t range = (end - begin + 1) / servers_num;
uint64_t remainder = (end - begin + 1) % servers_num;

for (int i = 0; i < servers_num; i++) {
    struct hostent *hostname = gethostbyname(to[i].ip);
    if (hostname == NULL) {
        fprintf(stderr, "gethostbyname failed with %s\n", to[i].ip);
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(to[i].port);
    server.sin_addr.s_addr = *((unsigned long *)hostname->h_addr);

    int sck = socket(AF_INET, SOCK_STREAM, 0);
    if (sck < 0) {
        fprintf(stderr, "Socket creation failed!\n");
        exit(1);
    }

    if (connect(sck, (struct sockaddr *)&server, sizeof(server)) < 0) {
        fprintf(stderr, "Connection failed\n");
        exit(1);
    }

    uint64_t server_begin = begin + i * range;
    uint64_t server_end = server_begin + range - 1;
    if (i == servers_num - 1) {
        server_end += remainder;
    }

    char task[sizeof(uint64_t) * 3];
    memcpy(task, &server_begin, sizeof(uint64_t));
    memcpy(task + sizeof(uint64_t), &server_end, sizeof(uint64_t));
    memcpy(task + 2 * sizeof(uint64_t), &mod, sizeof(uint64_t));

    if (send(sck, task, sizeof(task), 0) < 0) {
        fprintf(stderr, "Send failed\n");
        exit(1);
    }

    char response[sizeof(uint64_t)];
    if (recv(sck, response, sizeof(response), 0) < 0) {
        fprintf(stderr, "Recieve failed\n");
        exit(1);
    }

    uint64_t answer = 0;
    memcpy(&answer, response, sizeof(uint64_t));
    printf("Server %s:%d answer: %llu\n", to[i].ip, to[i].port, answer);

    close(sck);
}
  free(to);

  return 0;
}