#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main() {

  key_t key;
  int shmid;
  char * data;
  char answer[256];

  key = ftok("foo", 'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);

  if (data[0]) {
    printf("Data: %s\n", data);
  }
  else {
    printf("MEM Created\n");
  }

  printf("Change content? [y/n] \n");
  fgets(answer, 200, stdin);
  printf("\n");

  
  if (! strcmp(answer, "y\n") ) {
    printf("Enter stored value: \n");
    fgets(answer, 200, stdin);
    answer[strlen(answer) - 1] = 0;
    strcpy(data, answer);
  }

  printf("Delete Contents? [y/n]");
  fgets(answer, 200, stdin);

  if(! strcmp(answer, "y\n") ){
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Deleted");
  }

  return 0;
}
