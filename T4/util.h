void error(char *fmt, ...);
int leer(int fd, char *buf, int n);
void sendstr(int s, char *str);
char *getstr(int s);
void fsendstr(FILE *sf, char *str);
char *fgetstr(FILE *sf);
