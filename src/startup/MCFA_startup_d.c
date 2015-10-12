/*
  #
  # Copyright (c) 2006-2012      University of Houston. All rights reserved.
  # $COPYRIGHT$
  #
  # Additional copyrights may follow
  #
  # $HEADER$
  #
*/
#include "MCFA.h"
#include "MCFA_internal.h"


/**
   arg[0]  = type of connection
   arg[1]  = name of host where process is to be spawned (since we need to do ssh shark01)
   0.   arg[2]  = path of deamon
   1.   arg[3]  = path of executable
   2.   arg[4]  = hostname of mcfarun
   3.   arg[5]  = port of mcfarun
   4.   arg[6]  = rank of mcfarun
   5.   arg[7]  = redundancy
   6.   arg[8]  = spawn flag
   6.   arg[9]  = cluster flag
   
   7.   arg[10]  = number of proccesses on each host
   8.   arg[11] = SL_id of procs  
   9.  arg[11] = jobID(no need)
   10.  arg[12] = Volpex_id of procs(no need)
   11.  arg[13] = fullrank (e.g 0,A)(no need)
   
   12.  arg[14] = NULL
   
**/


int main(int argc, char **argv)
{
  char *hostname;
  int port;
  int id,event_handler_id;
  char *path;
  int red,numprocs;
  int spawn_flag, cluster_flag;
  int pid = 10;
  int status;
  char **arg = NULL;
  
  char *hname;
  hname = (char*) malloc (256 *sizeof(char));
  
  MCFA_get_ip(&hname);
  
  /** For condor since same executable is used by each deamon rename the file and then use it using 
      system( 'rename volpex.* volpex' );*/ 
  
  if (argc > 1) {
	path 		= strdup (argv[1]);
	hostname            = strdup ( argv[2] );
	port                = atoi ( argv[3] );
	event_handler_id    = atoi (argv[4]);                
	red         	= atoi (argv[5]);   
	spawn_flag		= atoi (argv[6]);
	cluster_flag		= atoi(argv[7]);
	numprocs		= atoi (argv[8]);
  }
  else {
    arg = MCFA_read_argfile();
    path                = strdup (arg[1]);
    hostname            = strdup ( arg[2] );
    port                = atoi ( arg[3] );
    event_handler_id    = atoi (arg[4]);
    red                 = atoi (arg[5]);
    spawn_flag          = atoi (arg[6]);
    cluster_flag        = atoi(arg[7]);
    numprocs            = atoi (argv[8]);
  }
  
  int i;
  PRINTF( ("Total number of arguments:%d\n",argc));
  for(i=9;i<argc;i++)
    {
      PRINTF(("%d.  %s\n",i,argv[i]));
    }
  
  int nextSL;
  nextSL = 9;
  if (spawn_flag != 0 )
	numprocs = 1;
  
  int *ids;
  ids = (int*)malloc(numprocs*sizeof(int));
  for(i=0;i<numprocs;i++){
	ids[i] = atoi(argv[nextSL]);
	nextSL++;
  }
  
  char **arg1;
  int numarguments = argc-nextSL+2;
  arg1 = (char **) malloc (numarguments*sizeof(char*));
  if(arg1 == NULL){
    printf("ERROR: in allocating memory");
    exit(-1);
  }
  arg1[0] = strdup(path);
  int j=1;
  for(i=nextSL;i<argc;i++)
    arg1[j++] = strdup(argv[i]);
  
  arg1[j] = NULL;
  
  for(i=0;i<numprocs;i++){
	id = ids[i];
	MCFA_set_env(path, hostname, port, id, event_handler_id, red, spawn_flag, cluster_flag);
    
	PRINTF(("path           : %s\n \
	hostname         : %s\n        \
	port             : %d\n        \
	id               : %d\n        \
	event_handler_id : %d\n        \
	red	        	 : %d\n        \
	flag		     : %d\n        \
	cluster_flag	 : %d\n        \
	numprocs	     : %d\n",
            path, hostname, port, id, event_handler_id,red,spawn_flag, cluster_flag,numprocs));
    
   	pid = fork();
   	if (pid == 0){
	  if(-1 ==  execv(path, arg1)){
	    printf("Error!! in spawning the program:%s\n", hname);
	    return 0;
	  }
	}
  }
  
  for (i=0;i<numprocs;i++){
   	wait(&status);
    if (WIFEXITED(status)) {
      PRINTF(("exited, status=%d proc:%d\n", WEXITSTATUS(status),i));
	} else if (WIFSIGNALED(status)) {
      printf("killed by signal %d proc:%s\n", WTERMSIG(status),hname);
	} else if (WIFSTOPPED(status)) {
      printf("stopped by signal %d\n", WSTOPSIG(status));
	}
  }
  

  free (hname);
  free(ids);
  for(i=0; i<8; i++){
    free(arg[i]);
  }
  free(arg);

  return 1;
}


char ** MCFA_read_argfile()
{
  FILE *fp;
  char        **arg = NULL;
  char exec[MAXNAMELEN];
  
  fp = fopen ("volpex", "r");
  if (fp == NULL) {
    printf(" Error in opening condor input file \n");
  }
  
  arg = (char **)malloc(MAXARGUMENTS * sizeof(char*));
  if(arg == NULL){
    printf("ERROR: in allocating memory\n");
    exit(-1);
  }
  
  arg[0] = (char *) malloc (10);
  if (NULL == arg[0]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  sprintf(arg[0], "%s", "condor");
  
  arg[1] = (char *) malloc (MAXNAMELEN);
  if (NULL == arg[1]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  fscanf(fp, "%s", exec);
  strcpy(arg[1], exec);
  
  arg[2] = (char *) malloc (MAXHOSTNAMELEN);
  if (NULL == arg[2]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  fscanf(fp, "%s", arg[2]);
  
  arg[3] = (char *) malloc (sizeof (int)+1);
  if (NULL == arg[3]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  fscanf(fp, "%s", arg[3]);
  
  arg[4] = (char *) malloc (sizeof (int)+1);
  if (NULL == arg[4]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  fscanf(fp, "%s", arg[4]);
  
  arg[5] = (char *) malloc (sizeof (int)+1);
  if (NULL == arg[5]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  fscanf(fp, "%s", arg[5]);
  
  arg[6] = (char *) malloc (sizeof (int)+1);
  if (NULL == arg[6]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  fscanf(fp, "%s", arg[6]);
  
  arg[7] = (char *) malloc (16 * sizeof(char));
  if (NULL == arg[7]){
	printf("ERROR: in allocating memory\n");
	exit(-1);
  }
  fscanf(fp, "%s", arg[7]);
  
  arg[8] = (char *) malloc (16 * sizeof(char));
  if (NULL == arg[8]){
    printf("ERROR: in allocating memory\n");
    exit(-1);
  }
  fscanf(fp, "%s", arg[8]);
  
  return arg;
}
