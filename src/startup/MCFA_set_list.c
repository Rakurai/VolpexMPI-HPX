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
#include "SL.h"

extern int SL_this_procport;
extern int SL_init_numprocs;
extern struct      MCFA_host_node *hostList;
extern struct      MCFA_proc_node *procList;
extern char hostname[MAXHOSTNAMELEN];


struct MCFA_proc_node* MCFA_set_liststraight(int initid,char **hostName, char *path, int port, int jobID, int numprocs,int hostCount, int redundancy)
{
  /*
    initid   - val = -1 if a process is spawned first time
    != -1 if a processes is added to the existing job pool
    
    hostName - consists of the array of hostnames taken from hostfile. If a particular host is repeated n times then there are n entries
    of it.
    path     - path of the executable file
    port     - port at which mcfarun is running
    numprocs - total number of processes to be spawned
    hostCount - total number of entries in hostfile
    redundancy -
  */
  
  struct      MCFA_host *node=NULL;
  int         i,id, j=0;
  char        fullrank[16];
  char        level = 'A';
  char        rank = -1  ;
  struct    MCFA_proc_node *newproclist = NULL;
  char    newlevel;
  
  for(i=0;i<numprocs;i++) {
    id = MCFA_get_nextID();
    node = MCFA_search_hostname(hostList,hostName[j]);
    if(node != NULL){
      node->id[node->numofProcs].procID = id;
      node->id[node->numofProcs].jobID = jobID;
      MCFA_get_exec_name(path,node->id[node->numofProcs].exec);
      node->numofProcs++;
      node->lastPortUsed++;
    }
    if (initid != -1) {
      newlevel = MCFA_search_rank_lastlevel(procList,initid);
      newlevel++;
      sprintf(fullrank,"%d,%c",initid,newlevel);
    }
    else if(initid == -1) {
      if (rank == (numprocs/redundancy)-1) {
        rank = 0;
        level++;
      }
      else
        rank++;
      
      sprintf(fullrank,"%d,%c",rank,level);
    }
    
    port = node->lastPortUsed ;
    PRINTF(("MCFA_startprocs: Adding proc %d with jobid %d hostname %s to processList\n",id,jobID,node->hostname));
    MCFA_add_proc(&procList, id, node->hostname,port, jobID,-1, 1,path,fullrank);    //for each process adding it process list
    MCFA_add_proc(&newproclist, id, node->hostname,port, jobID,-1, 1,path,fullrank);
    j++;
    if (j==hostCount) {
      j=0;
    }
    
  }/* end for */
  return(newproclist);
}


struct MCFA_proc_node* MCFA_set_listsroundrobin(int initid,char **hostName, char *path, int port, int jobID, int numprocs,int hostCount, int redundancy)
{
  /*
    hostName - consists of the array of hostnames taken from hostfile. If a particular host is repeated n times then there are n entries
    of it.
    path     - path of the executable file
    port     - port at which mcfarun is running
    numprocs - total number of processes to be spawned
    hostCount - total number of entries in hostfile
    redundancy -
  */
  
  struct      MCFA_host *node=NULL;
  struct      MCFA_host_node *currhost=NULL;
  int         i,id;
  char        fullrank[16];
  char        level = 'A';
  char        rank = -1  ;
  struct    MCFA_proc_node *newproclist = NULL;
  char    newlevel;
  
  hostCount =  MCFA_get_total_hosts(hostList);
  currhost = hostList;
  
  for(i=0;i<numprocs;i++) {
    id = MCFA_get_nextID();
    node = currhost->hostdata;
    
    if(node != NULL) {
      node->id[node->numofProcs].procID = id;
      node->id[node->numofProcs].jobID = jobID;
      MCFA_get_exec_name(path,node->id[node->numofProcs].exec);
      node->numofProcs++;
      node->lastPortUsed++;
    }
    
    if (initid != -1) {
      newlevel = MCFA_search_rank_lastlevel(procList,initid);
      newlevel++;
      sprintf(fullrank,"%d,%c",initid,newlevel);
    }
    else if(initid == -1) {
      if (rank == (numprocs/redundancy)-1) {
        rank = 0;
        level++;
      }
      else
        rank++;
      
      sprintf(fullrank,"%d,%c",rank,level);
    }
    port = node->lastPortUsed ;
    PRINTF(("MCFA_startprocs: Adding proc %d with jobid %d hostname %s to processList\n",id,jobID,hostname));
    MCFA_add_proc(&procList, id, node->hostname,port, jobID,-1, 1,path,fullrank);    //for each process adding it process list
    MCFA_add_proc(&newproclist, id, node->hostname,port, jobID,-1, 1,path,fullrank);
    
    if(currhost->next == NULL)
      currhost = hostList;
    else
      currhost = currhost->next;
  }/* end for */
  return(newproclist);
}


struct MCFA_proc_node* MCFA_set_listsconcentrate(int initid,char **hostName, char *path, int port, 
                                                 int jobID, int numprocs,int hostCount, int redundancy)
{
  /*
    hostName - consists of the array of hostnames taken from hostfile. If a particular host is repeated n times then there are n entries
    of it.
    path     - path of the executable file
    port     - port at which mcfarun is running
    numprocs - total number of processes to be spawned
    hostCount - total number of entries in hostfile
    redundancy -
  */
  
  struct      MCFA_host *node=NULL;
  struct      MCFA_host_node *currhost=NULL;
  int         i,id, j=0;
  char        fullrank[16];
  char        level = 'A';
  char        rank = -1  ;
  struct    MCFA_proc_node *newproclist = NULL;
  char    newlevel;
  
  hostCount =  MCFA_get_total_hosts(hostList);
  currhost = hostList;
  for(i=0;i<numprocs;i++) {
    id = MCFA_get_nextID();
    node = currhost->hostdata;
    
    if(node != NULL) {
      node->id[node->numofProcs].procID = id;
      node->id[node->numofProcs].jobID = jobID;
      MCFA_get_exec_name(path,node->id[node->numofProcs].exec);
      node->numofProcs++;
      node->lastPortUsed++;
    }
    
    if (initid != -1) {
      newlevel = MCFA_search_rank_lastlevel(procList,initid);
      newlevel++;
      sprintf(fullrank,"%d,%c",initid,newlevel);
    }
    else if(initid == -1) {
      if (rank == (numprocs/redundancy)-1) {
        rank = 0;
        level++;
      }
      else
        rank++;
      
      sprintf(fullrank,"%d,%c",rank,level);
    }
        
    port = node->lastPortUsed ;
    PRINTF(("MCFA_startprocs: Adding proc %d with jobid %d hostname %s to processList\n",id,jobID,hostname));
    MCFA_add_proc(&procList, id, node->hostname,port, jobID,-1, 1,path,fullrank);    //for each process adding it process list
    MCFA_add_proc(&newproclist, id, node->hostname,port, jobID,-1, 1,path,fullrank);
    j++;
    
    if (j==numprocs/redundancy) {
      currhost = currhost->next;
      
      if(currhost == NULL)
        currhost = hostList;
    }
  }/* end for */
  return(newproclist);
}


void MCFA_shuffle(int *array, size_t n)
{
  srand(time(NULL));
  if (n > 1) {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      int j = i + (rand() % (n-i));
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}


struct MCFA_proc_node* MCFA_set_listsrandom(int initid,char **hostName, char *path, int port, int jobID, int numprocs,int hostCount, int redundancy)
{
  /*
    initid   - val = -1 if a process is spawned first time
    != -1 if a processes is added to the existing job pool
    
    hostName - consists of the array of hostnames taken from hostfile. If a particular host is repeated n times then there are n entries
    of it.
    path     - path of the executable file
    port     - port at which mcfarun is running
    numprocs - total number of processes to be spawned
    hostCount - total number of entries in hostfile
    redundancy -
  */
  
  int *rand_array;
  struct      MCFA_host *node=NULL;
  int         i,id, j=0;
  char        fullrank[16];
  char        level = 'A';
  char        rank = -1  ;
  struct    MCFA_proc_node *newproclist = NULL;
  char    newlevel;
  
  rand_array = (int *) malloc (hostCount * sizeof(int));
  for(i=0;i<hostCount;i++) {
	rand_array[i] = i; 
  }
  MCFA_shuffle(rand_array,hostCount);
  
  for(i=0;i<hostCount;i++) {
    printf("%d  ", rand_array[i]);
  }
  
  for(i=0;i<numprocs;i++) {
    id = MCFA_get_nextID();
    node = MCFA_search_hostname(hostList,hostName[rand_array[j]]);
    if(node != NULL) {
      node->id[node->numofProcs].procID = id;
      node->id[node->numofProcs].jobID = jobID;
      MCFA_get_exec_name(path,node->id[node->numofProcs].exec);
      node->numofProcs++;
      node->lastPortUsed++;
    }
    if (initid != -1) {
      newlevel = MCFA_search_rank_lastlevel(procList,initid);
      newlevel++;
      sprintf(fullrank,"%d,%c",initid,newlevel);
    }
    else if(initid == -1) {
      if (rank == (numprocs/redundancy)-1) {
        rank = 0;
        level++;
      }
      else
        rank++;
      
      sprintf(fullrank,"%d,%c",rank,level);
    }
    
    port = node->lastPortUsed ;
    PRINTF(("MCFA_startprocs: Adding proc %d with jobid %d hostname %s to processList\n",id,jobID,hostname));
    MCFA_add_proc(&procList, id, node->hostname,port, jobID,-1, 1,path,fullrank);    //for each process adding it process list
    MCFA_add_proc(&newproclist, id, node->hostname,port, jobID,-1, 1,path,fullrank);
    j++;
    if (j==hostCount) {
      j=0;
    }
  }/* end for */
  return(newproclist);
}

