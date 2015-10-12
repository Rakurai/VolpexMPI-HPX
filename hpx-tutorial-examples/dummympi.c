/*
 * Copyright (c) 2006-2007     University of Houston. All rights reserved.
 * $COPYRIGHTS$
 *
 * Additional copyrights may follow
 *
 * $HEADERS$
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>


#include "dummympi.h"

#define MAXHOSTNAMELEN 256
#define MAXARGUMENTS 9

char ** local_read_argfile(void);
int MCFA_get_ip(char *ip);
int MCFA_connect(int id, char *as_host, int port);
void SL_configure_socket_nb ( int sd ); 

int SL_this_procid;
int SL_this_procport;


int MPI_Init      ( int *argc, char ***argv )
{
  char *hostname;
  int port;
  int id,event_handler_id, redundancy;
  char *path;		
  int spawn_flag, cluster_flag ;
  int ret;
  char **arg;
  char *hname=NULL;
  int myid;
  
  arg = local_read_argfile();
  path                = strdup (arg[1]);
  hostname            = strdup ( arg[2] );
  port                = atoi ( arg[3] );
  id                  = 1234;
  event_handler_id    = atoi (arg[4]);
  redundancy          = atoi (arg[5]);
  spawn_flag          = atoi (arg[6]);
  cluster_flag        = atoi (arg[7]);
  
  printf("path           : %s\n \
        hostname         : %s\n   \
        port             : %d\n   \
        id               : %d\n   \
        event_handler_id : %d\n   \
        red              : %d\n   \
        flag             : %d\n",
         path, hostname, port, id, event_handler_id, redundancy, spawn_flag);
  
  
  hname = (char*) malloc (256 *sizeof(char));
  MCFA_get_ip(hname);
  
  MCFA_connect(-64, hostname, port);
  printf("[%d]:My hostname is %s\n",SL_this_procid, hname);
  
  return MPI_SUCCESS;
}

#pragma weak MPI_Finalize = PMPI_Finalize
int PMPI_Finalize  ( void )
{
  return MPI_SUCCESS;
}


#pragma weak MPI_Comm_rank = PMPI_Comm_rank
int PMPI_Comm_rank ( MPI_Comm comm, int *rank )
{
  *rank = SL_this_procid;
  return MPI_SUCCESS;
}

#pragma weak MPI_Comm_size = PMPI_Comm_size
int PMPI_Comm_size ( MPI_Comm comm, int *size )
{
  *size = 2;
  return MPI_SUCCESS;
}

char **local_read_argfile(void)
{
  FILE *fp;
  char **arg = NULL;
  char exec[MAXNAMELEN];
  
  fp = fopen ("volpex", "r");
  if (fp == NULL)
    printf(" Error in opening condor input file \n");
  
  
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

int MCFA_get_ip(char *ip)
{
  char *ipp, *temp;
  char tip[200];
  FILE *fp;
  int i=0;
  fp = popen("/sbin/ifconfig | grep Bcast", "r");
  fgets(tip, 200, fp);
  
  ipp = strchr(tip,'1');
  
  temp = (char*) malloc (256 *sizeof(char));
  while(ipp[i] != ' '){
    temp[i] = ipp[i];
    i++;
  }
  
  strcpy (ip, temp);
  pclose(fp);
  free(temp);
  
  return 1;
  
}

int MCFA_connect(int id, char *as_host, int port)
{
  int tmp,len=256;
  struct sockaddr_in server;
  struct hostent     *host;
  int conn_ret=-1;
  int handle, newid, ret;
  char *hostname = NULL;
  
  hostname = (char*)malloc(256 * (sizeof(char)));
  if ( hostname == NULL){
    printf("ERROR: in allocating memory\n");
    exit(-1);
  }
  
  if ( gethostname(hostname, len ) != 0 ){
    printf("SERVER: could not determine my own hostname \n" );
  }
  
  SL_this_procid = id ;//MCFA_CONSTANT_ID;
  
  if ( ( handle = socket ( AF_INET, SOCK_STREAM, 0 ) ) == -1 ) {
    printf("[%d]:SL_socket: socket failed, %d %s\n", SL_this_procid, errno, strerror(errno));
    return -1;
  }
  SL_configure_socket_nb ( handle );
  
  
  if ( (host = gethostbyname ( as_host ) ) == NULL )   {
    printf("[%d]:SL_open_socket_conn_nb: failed to get hostname:%s, %d %s\n", SL_this_procid,
           as_host, h_errno, strerror(h_errno));
      return -1;
  }

  /*
  ** Fill in the important elements of the server-structure
  */
  memcpy (&server.sin_addr, host->h_addr, host->h_length );
  server.sin_family = AF_INET;
  server.sin_port   = htons ( port );
  
  conn_ret = connect(handle,(struct sockaddr *)&server, sizeof(server));
  
  read  ( handle, ( char *) &tmp, sizeof(int));
  write ( handle, (char *) &SL_this_procid, sizeof(int));
  
  
  printf("Receiving newID\n");
  
  write ( handle,  hostname, MAXHOSTNAMELEN );
  free(hostname);
  
  read ( handle, ( char *) &newid, sizeof(int));
  if ( newid == -1) {
    printf("I am no longer needed:%d\n", newid);
    exit(-1);
    return ret;
  }
  
  read ( handle, ( char *) &port, sizeof(int));
  SL_this_procport = port;
  close (handle );
  return 0;
}

void SL_configure_socket_nb ( int sd ) 
{
  int flag;
  struct linger ling;

  flag=1;
  if(setsockopt(sd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag))<0) {
    printf("[%d]:SL_configure_socket: could not configure socket\n",SL_this_procid);
  }
  
  flag=262142;
  if(setsockopt(sd, SOL_SOCKET, SO_SNDBUF, (char*)&flag, sizeof(flag))<0) {
    printf("[%d]:SL_configure_socket: could not configure socket\n",SL_this_procid);
  }
  
  flag=262142;
  if(setsockopt(sd, SOL_SOCKET, SO_RCVBUF, (char*)&flag, sizeof(flag))<0) {
    printf("[%d]:SL_configure_socket: could not configure socket\n",SL_this_procid);
  }
  
  flag=1;
  if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(flag))<0) {
    printf("[%d]:SL_configure_socket: Could not set SO_REUSEADDR\n",SL_this_procid);
  }
    
  ling.l_onoff  = 1;
  ling.l_linger = 0;
  if(setsockopt(sd, SOL_SOCKET, SO_LINGER, &ling, sizeof(struct linger))<0) {
    printf("[%d]:SL_configure_socket: Could not set SO_LINGER\n",SL_this_procid);
  }
  /*
  flag = fcntl ( sd, F_GETFL, 0 );
  fcntl ( sd, F_SETFL, flag | O_NONBLOCK );
  */
  return;
}
