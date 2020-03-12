/********************************
*Author: Mohanad Fawzy Sallam   *
*Version: v01                   *
*Date: 11/03/2020               *
********************************/
#ifndef URTM_INTERFACE_H
#define URTM_INTERFACE_H
                             
#define URTM_SEND_SYNCH      0
#define URTM_SEND_ASYNCH     1
#define URTM_RECEIVE_SYNCH   2
#define URTM_RECEIVE_ASYNCH  3

typedef struct 
{
  u8 JobType ;
  u8* DataBuffer ;
  u8 Length ;
  void (*CallBack) (void);
}URTM_JobRequest;

u8 URTM_u8PerformJobRequest (URTM_JobRequest Copy_JobInfo);
#endif