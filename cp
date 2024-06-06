cp

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
    char buff[30];
    int inp =open("/home/cvr/test",O_RDONLY);
    int op = open("/home/cvr/new",O_CREAT|O_RDWR,S_IRUSR |S_IWUSR |S_IRGRP |S_IROTH);
    while(read(inp,&buff,1)) 
        write(op,&buff,1);
    printf("File copied successfully!!");
    close(inp);
    close(op);
    return 0;
}

ls
#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
int main(){
    char dirname[10];
    DIR *P;
    struct dirent *d;
    printf("Enter the directry name:");
    scanf("%s",dirname);
    P=opendir(dirname);
    if(P==NULL){
        perror("Cannot find directory");
        exit(1);
    }
    while(d=readdir(P)){
        printf("%s\t",d->d_name);
    }

}


chmod
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char *argv[]) {
    if(argc<2) {
        printf("usage: perms file_name \nExample: 777 hi.txt");
        return -1;
    }
    const char *perms = argv[1];
    const char *filename = argv[2];
    mode_t mode = strtol(perms,NULL,8);
    if(chmod(filename,mode)==-1) {
        perror("chmod error");
        exit(EXIT_FAILURE);
    }
    printf("permissions changed successfully");
return 0;
}

ls-ls

  #include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    struct passwd *pw;
    struct group *gr;
    char buffer[1024];

    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((dir = opendir(argv[1])) == NULL)
    {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL)
    {
        sprintf(buffer, "%s/%s", argv[1], entry->d_name);

        if (stat(buffer, &fileStat) < 0)
        {
            perror("stat");
            continue;
        }

        printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf(" ");

        printf("%ld ", (long)fileStat.st_nlink);

        if ((pw = getpwuid(fileStat.st_uid)) != NULL)
            printf("%s ", pw->pw_name);
        else
            printf("%d ", fileStat.st_uid);

        if ((gr = getgrgid(fileStat.st_gid)) != NULL)
            printf("%s ", gr->gr_name);
        else
            printf("%d ", fileStat.st_gid);

        printf("%lld ", (long long)fileStat.st_size);

        strftime(buffer, sizeof(buffer), "%b %d %H:%M", localtime(&fileStat.st_mtime));
        printf("%s ", buffer);

        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}

fcfs

#include<stdio.h>
struct process{
	int pid;
	int burst;
	int wt;
	int tat;
};
void calculateTimes(struct process p[],int n){
	int total_waiting=0;
	int total_turnAround=0;
	p[0].wt=0;
	p[0].tat=p[0].burst;
	for(int i=1;i<n;i++){
		p[i].wt=p[i-1].wt+p[i-1].burst;
		p[i].tat=p[i].wt+p[i].burst;
	}
}
void display(struct process p[],int n){
	printf("Process Id\tBurst Time\tWaiting Time\tTurn Around Time\n");
	for(int i=0;i<n;i++)
		printf("%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].burst,p[i].wt,p[i].tat);
}
void calcAvg(struct process p[],int n,float *avg_wt,float *avg_tat){
	int total_waiting=0;
	int total_turnAround=0;
	for(int i=0;i<n;i++){
		total_waiting+=p[i].wt;
		total_turnAround+=p[i].tat;
	}
	*avg_wt=(float)total_waiting/n;
	*avg_tat=(float)total_turnAround/n;
}
int main(void){
	int n;
	printf("Enter num of processes :");
	scanf("%d",&n);
	struct process p[n];
	printf("Enter burst time for each process (in ms):\n");
	for(int i=0;i<n;i++){
		p[i].pid=i+1;
		printf("Process %d :",i+1);
		scanf(" %d",&p[i].burst);
	}
	calculateTimes(p,n);
	display(p,n);
	float avg_wt,avg_tat;
	calcAvg(p,n,&avg_wt,&avg_tat);
	printf("\nAverage waiting time :%2f ms\n",avg_wt);
	printf("\nAverage Turn Around time :%2f ms\n",avg_tat);
return 0;
}

sjf

#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

void sjf_scheduling(struct Process processes[], int n) {
    int completion_time[n];
    int waiting_time[n];
    int turnaround_time[n];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &processes[i].process_id);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        completion_time[i] = current_time + processes[i].burst_time;
        waiting_time[i] = current_time - processes[i].arrival_time;
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
        current_time += processes[i].burst_time;
    }
    printf("\nProcess\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, completion_time[i], waiting_time[i], turnaround_time[i]);
    }
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    sjf_scheduling(processes, n);

    return 0;
}

round robin


#include<stdio.h>  
#include<stdlib.h>  
void main(){  
        int i, NOP, sum=0,count=0, y, quant, wt=0, tat=0, at[10], bt[10], temp[10];  
        float avg_wt, avg_tat;  
        printf(" Total number of process in the system: ");  
        scanf("%d", &NOP);  
        y = NOP; 
     
    for(i=0; i<NOP; i++){  
    printf("\n Enter the Arrival and Burst time of the Process[%d]\n", i+1);  
    printf(" Arrival time is: \t"); 
    scanf("%d", &at[i]);  
    printf(" \nBurst time is: \t"); 
    scanf("%d", &bt[i]);  
    temp[i] = bt[i]; 
    }  
    printf("Enter the Time Quantum for the process: \t");  
    scanf("%d", &quant);  
    printf("\n Process No \t\t Burst Time \t\t TAT \t\t Waiting Time ");  
    for(sum=0, i = 0; y!=0; ){  
    if(temp[i] <= quant && temp[i] > 0) 
    {  
        sum = sum + temp[i];  
        temp[i] = 0;  
        count=1;  
        }    
        else if(temp[i] > 0)  
        {  
            temp[i] = temp[i] - quant;  
            sum = sum + quant;    
        }  
        if(temp[i]==0 && count==1)  
        {  
            y--; 
            printf("\nProcess No[%d] \t\t %d\t\t\t\t %d\t\t\t %d", i+1, bt[i], sum-at[i], sum-at[i]-bt[i]);  
            wt = wt+sum-at[i]-bt[i];  
            tat = tat+sum-at[i];  
            count =0;    
        }  
        if(i==NOP-1)  
            i=0;  
        else if(at[i+1]<=sum)   
            i++;  
        else  
            i=0;  
    }   
    avg_wt = wt * 1.0/NOP;  
    avg_tat = tat * 1.0/NOP;  
    printf("\n Average Turn Around Time: \t%f", avg_tat);  
    printf("\n Average Waiting Time: \t%f",avg_wt);
}

priority

#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int burstTime;
    int priority;
} Process;

void sortProcessesByPriority(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority < processes[j].priority) {
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void priorityScheduling(Process processes[], int n) {
    sortProcessesByPriority(processes, n);

    int totalWaitTime = 0;
    int totalTurnaroundTime = 0;

    printf("Process\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    
    int waitTime = 0;
    for (int i = 0; i < n; i++) {
        int turnaroundTime = waitTime + processes[i].burstTime;
        totalWaitTime += waitTime;
        totalTurnaroundTime += turnaroundTime;

        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].priority,
               processes[i].burstTime, waitTime, turnaroundTime);

        waitTime += processes[i].burstTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitTime / n);
    printf("Average Turnaround Time: %.2f\n", (float)totalTurnaroundTime / n);
}

int main() {
    int n;
    Process processes[MAX_PROCESSES];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter burst time and priority for process %d: ", i + 1);
        processes[i].id = i + 1;
        scanf("%d %d", &processes[i].burstTime, &processes[i].priority);
    }

    priorityScheduling(processes, n);

    return 0;
}


bankers

#include<stdio.h>

int main() {
  int p, c, count = 0, i, j, alc[5][3], max[5][3], need[5][3], safe[5], available[3], done[5], terminate = 0;
  printf("Enter the number of process and resources");
  scanf("%d %d", & p, & c);
  printf("enter allocation of resource of all process %dx%d matrix", p, c);
  for (i = 0; i < p; i++) {
    for (j = 0; j < c; j++) {
      scanf("%d", & alc[i][j]);
    }
  }
  printf("enter the max resource process required %dx%d matrix", p, c);
  for (i = 0; i < p; i++) {
    for (j = 0; j < c; j++) {
      scanf("%d", & max[i][j]);
    }
  }
  printf("enter the  available resource");
  for (i = 0; i < c; i++)
    scanf("%d", & available[i]);

  printf("\n need resources matrix are\n");
  for (i = 0; i < p; i++) {
    for (j = 0; j < c; j++) {
      need[i][j] = max[i][j] - alc[i][j];
      printf("%d\t", need[i][j]);
    }
    printf("\n");
  }
  for (i = 0; i < p; i++) {
    done[i] = 0;
  }
  while (count < p) {
    for (i = 0; i < p; i++) {
      if (done[i] == 0) {
        for (j = 0; j < c; j++) {
          if (need[i][j] > available[j])
            break;
        }
        if (j == c) {
          safe[count] = i;
          done[i] = 1;
          for (j = 0; j < c; j++) {
            available[j] += alc[i][j];
          }
          count++;
          terminate = 0;
        } else {
          terminate++;
        }
      }
    }
    if (terminate == (p - 1)) {
      printf("safe sequence does not exist");
      break;
    }

  }
  if (terminate != (p - 1)) {
    printf("\n available resource after completion\n");
    for (i = 0; i < c; i++) {
      printf("%d\t", available[i]);
    }
    printf("\n safe sequence are\n");
    for (i = 0; i < p; i++) {
      printf("p%d\t", safe[i]);
    }
  }

  return 0;
}

pipes

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main() {
    char write_msg[BUFFER_SIZE] = "Hello, Child Process!";
    char read_msg[BUFFER_SIZE];
    int fd[2]; 
    pid_t pid;

   
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed");
        return 1;
    }

   
    pid = fork();

    if (pid < 0) { 
        fprintf(stderr, "Fork failed");
        return 1;
    }

    if (pid > 0) {
        close(fd[READ_END]);

      
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

     
        close(fd[WRITE_END]);
    } else {
        
        close(fd[WRITE_END]);

       
        read(fd[READ_END], read_msg, BUFFER_SIZE);

    
        printf("Child received: %s\n", read_msg);

       
        close(fd[READ_END]);
    }

    return 0;
}
gcc -o pipe_ipc pipe_ipc.c
./pipe_ipc
Child received: Hello, Child Process!


fifos


mkfifo myfifo

write

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char write_msg[BUFFER_SIZE] = "Hello from the writer process!";

    
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

 
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

   
    write(fd, write_msg, strlen(write_msg) + 1);


    close(fd);

    return 0;
}


read

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 100

int main() {
    int fd;
    char read_msg[BUFFER_SIZE];

    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

   
    read(fd, read_msg, BUFFER_SIZE);

    
    printf("Received: %s\n", read_msg);

  
    close(fd);

    return 0;
}


gcc -o write_fifo write_fifo.c
gcc -o read_fifo read_fifo.c


./write_fifo

  ./read_fifo

msg queue

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

struct msg_buffer { 
    long msg_type; 
    char msg_text[100]; 
} msg; 
  
int main() 
{ 
    int msgqid = msgget(100, 0666 | IPC_CREAT); 
    msg.msg_type = 1;
    printf("Enter message: ");
    fgets(msg.msg_text,sizeof(msg.msg_text),stdin);
    msgsnd(msgqid,&msg,sizeof(msg),0);
    printf("Waiting for a message from client...\n");
    msgrcv(msgqid, &msg, sizeof(msg), 1, 0); 
    printf("Message received from client : %s\n",msg.msg_text); 
    msgctl(msgqid, IPC_RMID, NULL); 
    return 0; 
}

shared memory

// Program 1: This program creates a shared memory segment, attaches itself to it and then writes some content into the shared memory segment.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
int main()
{
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);
    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);
    printf("Enter some data to write to shared memory\n");
    read(0, buff, 100);
    strcpy(shared_memory, buff);
    printf("You wrote : %s\n", (char *)shared_memory);
}

// Program 2: This program attaches itself to the shared memory segment created in Program 1. Finally, it reads the content of the shared memory.
Solution :
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
    int
    main()
{
    int i;
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)2345, 1024, 0666);
    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);
    printf("Data read from shared memory is : %s\n", (char *)shared_memory);
}

producer consumer

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[count++] = item;
        printf("Produced: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1); // Simulate time taken to produce an item
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[--count];
        printf("Consumed: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1); // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}



	
