#include "httpserver.h"
pthread_mutex_t mut;
/* ideas: *make n amount of threads in which n is the amount of requests. A thread becomes a worker thread if a worker thread 
is done in which it's blocked untl then. the threads then pop from queue which will also be blocked if queue is empty.*/

typedef struct queue_L {
    queue_t *q;
    List l;
    pthread_mutex_t mutex;
} queue_L;

typedef struct kv {
    char *uri;
    rwlock_t *lock;
} kv;

queue_L *ql_create(int thread) {
    queue_L *ql = malloc(sizeof(queue_L));
    ql->q = queue_new(thread);
    ql->l = newList();
    pthread_mutex_init(&(ql->mutex), NULL);
    return ql;
}
void run_get(int sock, char *uri, int id) {
    DIR *dir = opendir(uri);
    if (dir != NULL) {
        char *rong = "HTTP/1.1 403 Forbidden\r\nContent-Length: 10\r\n\r\nForbidden\n";
        write_n_bytes(sock, rong, strlen(rong));
        fprintf(stderr, "GET,%s,403,%d\n", uri, id);
        return;
    }
    struct stat fileStat;
    int fd = open(uri, O_RDONLY);
    if (fd == -1) {
        if (errno == EACCES) {
            char *rong = "HTTP/1.1 403 Forbidden\r\nContent-Length: 10\r\n\r\nForbidden\n";
            write_n_bytes(sock, rong, strlen(rong));
            fprintf(stderr, "GET,%s,403,%d\n", uri, id);
            return;
        } else if (errno == ENOENT) {
            char *rong = "HTTP/1.1 404 Not Found\r\nContent-Length: 10\r\n\r\nNot Found\n";
            write_n_bytes(sock, rong, strlen(rong));
            fprintf(stderr, "GET,%s,404,%d\n", uri, id);
            return;
        } else {
            char *rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                         "Server Error\n";
            write_n_bytes(sock, rong, strlen(rong));
            fprintf(stderr, "GET,%s,500,%d\n", uri, id);
            return; //add 500 error
        }
    }
    if (fstat(fd, &fileStat) == -1) {
        char *rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                     "Server Error\n";
        write_n_bytes(sock, rong, strlen(rong));
        fprintf(stderr, "GET,%s,500,%d\n", uri, id);
        close(fd);
        return;
    }

    int length = snprintf(NULL, 0, "%ld", fileStat.st_size);
    char enough[length + 1];
    sprintf(enough, "%ld", fileStat.st_size);
    char *rong = "HTTP/1.1 200 OK\r\nContent-Length: ";
    char *rong2 = "\r\n\r\n";
    write_n_bytes(sock, rong, strlen(rong));
    write_n_bytes(sock, enough, strlen(enough));
    write_n_bytes(sock, rong2, strlen(rong2));
    pass_n_bytes(fd, sock, fileStat.st_size);
    fprintf(stderr, "GET,%s,200,%d\n", uri, id);
    close(fd);
}

void run_put(int sock, char *uri, char *buf, int length, int end, int pos, int id) {
    char *rong;
    int code;
    DIR *dir = opendir(uri);
    if (dir != NULL) {
        rong = "HTTP/1.1 403 Forbidden\r\nContent-Length: 10\r\n\r\nForbidden\n";
        write_n_bytes(sock, rong, strlen(rong));
        fprintf(stderr, "PUT,%s,403,%d\n", uri, id);
        return;
    }

    if (access(uri, F_OK) != 0) {
        rong = "HTTP/1.1 201 Created\r\nContent-Length: 8\r\n\r\nCreated\n";
        code = 201;
    } else {
        rong = "HTTP/1.1 200 OK\r\nContent-Length: 3\r\n\r\nOK\n";
        code = 200;
    }
    int fd = open(uri, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        if (errno == EACCES) {
            rong = "HTTP/1.1 403 Forbidden\r\nContent-Length: 10\r\n\r\nForbidden\n";
            write_n_bytes(sock, rong, strlen(rong));
            fprintf(stderr, "PUT,%s,403,%d\n", uri, id);
            return;
        } else {
            rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                   "Server Error\n";
            write_n_bytes(sock, rong, strlen(rong));
            fprintf(stderr, "PUT,%s,500,%d\n", uri, id);
            return;
        }
    }
    int combo = end - pos;
    if (length < (combo)) {
        combo = (end - (combo - length)) - pos;
        if (write_n_bytes(fd, buf + pos, combo) == -1) {
            rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                   "Server Error\n";
            code = 500;
        }
        write_n_bytes(sock, rong, strlen(rong));
        fprintf(stderr, "PUT,%s,%d,%d\n", uri, code, id);
        close(fd);
    } //subtract from content length
    else {
        length -= combo;
        if (write_n_bytes(fd, buf + pos, combo) == -1) {
            rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                   "Server Error\n";
            code = 500;
            write_n_bytes(sock, rong, strlen(rong));
            fprintf(stderr, "PUT,%s,%d,%d\n", uri, code, id);
            close(fd);
            return;
        }
        //possibility that pas_n_bytes is overwriting what is in combo? since no offset provided
        pass_n_bytes(sock, fd, length);
        write_n_bytes(sock, rong, strlen(rong));
        fprintf(stderr, "PUT,%s,%d,%d\n", uri, code, id);
        close(fd);
    }
}
void *handle_connection(void *arg) {
    queue_L **ql = (queue_L **) arg;
    while (true) {
        uintptr_t new_sock = 0;
        char *endptr;
        queue_pop((*ql)->q, (void **) &new_sock);
        new_sock = (uintptr_t) new_sock;
        char buf[2048] = { '\0' };
        memset(buf, '\0', 2048);

        int bytes_read;
        if ((bytes_read = read_until(new_sock, buf, 2048, "\r\n\r\n")) == -1) {
            char *rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                         "Server Error\n";
            write_n_bytes(new_sock, rong, strlen(rong));
            /*add an audit log*/
            close(new_sock);
            continue;
        }

        //reg check for request line
        regex_t preg;
        if (regcomp(&preg, REQUEST_LINE_REGEX "(" HEADER_FIELD_REGEX ")*" EMPTY_LINE_REGEX,
                REG_EXTENDED | REG_NEWLINE)
            != 0) {
            char *rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal "
                         "Server Error\n";
            write_n_bytes(new_sock, rong, strlen(rong));
            close(new_sock);
            continue;
        }

        regmatch_t pmatch[7];
        if (regexec(&preg, buf, 7, pmatch, 0) != 0) {
            char *rong = "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n";
            write_n_bytes(new_sock, rong, strlen(rong));
            regfree(&preg);
            close(new_sock);
            continue;
        }

        char method[pmatch[1].rm_eo - pmatch[1].rm_so + 1];
        char uri[pmatch[2].rm_eo - pmatch[2].rm_so + 1];
        char version[pmatch[3].rm_eo - pmatch[3].rm_so + 1];

        for (int i = 1; i < 4; i++) {
            if (i == 1) {
                method[pmatch[1].rm_eo - pmatch[1].rm_so] = '\0';
                strncpy(method, buf + pmatch[1].rm_so, pmatch[1].rm_eo - pmatch[1].rm_so);
            } else if (i == 2) {
                uri[pmatch[2].rm_eo - pmatch[2].rm_so] = '\0';
                strncpy(uri, buf + pmatch[2].rm_so, pmatch[2].rm_eo - pmatch[2].rm_so);
            } else if (i == 3) {
                version[pmatch[3].rm_eo - pmatch[3].rm_so] = '\0';
                strncpy(version, buf + pmatch[3].rm_so, pmatch[3].rm_eo - pmatch[3].rm_so);
            }
        }

        if (strncmp(HTTP_VERSION_REGEX, version, 8) != 0) {
            char *rong = "HTTP/1.1 505 Version Not Supported\r\nContent-Length: 22\r\n\r\nVersion "
                         "Not Supported\n";
            write_n_bytes(new_sock, rong, strlen(rong));
            close(new_sock);
            regfree(&preg);
            continue;
        }
        /*search in dictionary*/
        //needs a lock since they all share dictionary
        pthread_mutex_lock(&mut);
        rwlock_t *rw;
        kv *temp;
        moveFront((*ql)->l);
        while (ind((*ql)->l) != -1) {
            temp = (kv *) get((*ql)->l);
            if (strcmp(temp->uri, uri) == 0) {
                rw = temp->lock;
                break;
            }
            moveNext((*ql)->l);
        }
        if (ind((*ql)->l) == -1) {
            rw = rwlock_new(N_WAY, 1);
            kv *entry = malloc(sizeof(kv));
            entry->uri = strdup(uri);
            entry->lock = rw;
            append((*ql)->l, (void *) entry);
        }
        pthread_mutex_unlock(&mut);

        //check for get or put
        if (strcmp(method, "GET") == 0) {
            int id = 0;
            regex_t reg;
            if (regcomp(&reg, HEADER_FIELD_REGEX, REG_EXTENDED | REG_NEWLINE) != 0) {
                char *rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: "
                             "22\r\n\r\nInternal Server Error\n";
                write_n_bytes(new_sock, rong, strlen(rong));
                close(new_sock);
                regfree(&preg);
                continue;
            }
            regmatch_t hmatch[3];
            int offset = pmatch[3].rm_eo + 2;
            while (regexec(&reg, buf + offset, 3, hmatch, 0) == 0) {
                char key[hmatch[1].rm_eo - hmatch[1].rm_so + 1];
                key[hmatch[1].rm_eo - hmatch[1].rm_so] = '\0';
                strncpy(key, buf + offset + hmatch[1].rm_so, hmatch[1].rm_eo - hmatch[1].rm_so);
                if (strcmp(key, "Request-Id") == 0) {
                    char val[hmatch[2].rm_eo - hmatch[2].rm_so + 1];
                    val[hmatch[2].rm_eo - hmatch[2].rm_so] = '\0';
                    strncpy(val, buf + offset + hmatch[2].rm_so, hmatch[2].rm_eo - hmatch[2].rm_so);
                    id = strtoll(val, &endptr, 10);
                    offset += hmatch[0].rm_eo;
                } else {
                    offset += hmatch[0].rm_eo;
                }
            }
            regfree(&reg);
            reader_lock(rw);
            run_get(new_sock, uri, id);
            reader_unlock(rw);
        } else if (strcmp(method, "PUT") == 0) {
            //go thorugh the headers
            int content_length = 0;
            int found = 0;
            int id = 0;
            regex_t reg;
            if (regcomp(&reg, HEADER_FIELD_REGEX, REG_EXTENDED | REG_NEWLINE) != 0) {
                char *rong = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: "
                             "22\r\n\r\nInternal Server Error\n";
                write_n_bytes(new_sock, rong, strlen(rong));
                close(new_sock);
                regfree(&preg);
                continue;
            }
            regmatch_t hmatch[3];
            int offset = pmatch[3].rm_eo + 2;
            while (regexec(&reg, buf + offset, 3, hmatch, 0) == 0) {
                char key[hmatch[1].rm_eo - hmatch[1].rm_so + 1];
                key[hmatch[1].rm_eo - hmatch[1].rm_so] = '\0';
                strncpy(key, buf + offset + hmatch[1].rm_so, hmatch[1].rm_eo - hmatch[1].rm_so);
                if (strcmp(key, "Content-Length") == 0) {
                    char val[hmatch[2].rm_eo - hmatch[2].rm_so + 1];
                    val[hmatch[2].rm_eo - hmatch[2].rm_so] = '\0';
                    strncpy(val, buf + offset + hmatch[2].rm_so, hmatch[2].rm_eo - hmatch[2].rm_so);
                    content_length = strtoll(val, &endptr, 10);
                    found = 1;
                    offset += hmatch[0].rm_eo;
                } else if (strcmp(key, "Request-Id") == 0) {
                    char val[hmatch[2].rm_eo - hmatch[2].rm_so + 1];
                    val[hmatch[2].rm_eo - hmatch[2].rm_so] = '\0';
                    strncpy(val, buf + offset + hmatch[2].rm_so, hmatch[2].rm_eo - hmatch[2].rm_so);
                    id = strtoll(val, &endptr, 10);
                    offset += hmatch[0].rm_eo;
                } else {
                    offset += hmatch[0].rm_eo;
                }
            }
            if (strncmp(buf + offset, "\r\n", 2) != 0) {
                char *rong
                    = "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n"; //issue is here
                write_n_bytes(new_sock, rong, strlen(rong));
                regfree(&preg);
                regfree(&reg);
                close(new_sock);
                continue;
            }
            if (found == 0) {
                char *rong
                    = "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n"; //issue is here
                write_n_bytes(new_sock, rong, strlen(rong));
                regfree(&preg);
                regfree(&reg);
                close(new_sock);
                continue; //reponse and continue its a bad request free reg and preg and close sock
            }
            regfree(&reg);
            writer_lock(rw);
            run_put(new_sock, uri, buf, content_length, bytes_read, pmatch[0].rm_eo, id);
            writer_unlock(rw);
        } else {
            char *rong
                = "HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot Implemented\n";
            write_n_bytes(new_sock, rong, strlen(rong));
        }
        close(new_sock);
        regfree(&preg);
    }
}

int main(int argc, char **argv) {
    int thread = 4;
    pthread_mutex_init(&mut, NULL);
    int opt = getopt(argc, argv, "t:");
    if (opt == 't') {
        char *endptr;
        thread = strtoll(optarg, &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stdout, "not a number\n");
            return 1;
        }
    }
    char *endptr;
    int port = strtoll(argv[optind], &endptr, 10);

    if (*endptr != '\0' || port < 1 || port > 65535) {
        fprintf(stdout, "Invalid Port\n");
        return 1;
    }
    //singal handler
    signal(SIGPIPE, SIG_IGN);

    //create socket called sock
    Listener_Socket sock;

    //called on init to start binding socket to port and check if it failed or not
    if (listener_init(&sock, port) != 0) {
        fprintf(stdout, "Invalid Port\n");
        return 1;
    }
    pthread_t *workers = malloc(thread * sizeof(pthread_t));
    queue_L *ql = ql_create(thread);

    for (int i = 0; i < thread; i++) {
        pthread_create(&workers[i], NULL, handle_connection, (void *) &ql);
    }
    while (true) {
        intptr_t new_sock;
        if ((new_sock = listener_accept(&sock)) == -1) {
            return 1;
        }
        queue_push(ql->q, (void *) new_sock);
    }
    return 0;
}
