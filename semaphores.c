/******************************************************************************/
/******************************************************************************/
/* file   semaphores.c
*
*  brief    Semaphores APIs
*
* Author Shilesh babu
*
*/

/******************************************************************************/
/******************************************************************************
 *          Header Files
 *****************************************************************************/
#include "semaphores.h"

/******************************************************************************/
/* fn       init_sem(semaphore_ctx *sem_ctx, unsigned int sem_val)
 *
 *  brief   This function will init the un-named semaphore
 *
 *  param   [IN]  sem_ctx  - semaphore context
 *  param   [IN]  sem_val  - value of semaphore
 *
 *  return  int
 */
/******************************************************************************/
int init_sem(semaphore_ctx *sem_ctx, unsigned int sem_val)
{
   int status = 0;

   do
   {
      //Check semaphore is already initialized
      if (0 != sem_ctx->sem_init)
      {
         printf("Semaphore is already initialized, sem_ctx->mutex: %p\n", sem_ctx->mutex);
         status = -1;
         break;
      }

      sem_ctx->mutex = &(sem_ctx->unnamed_sem);
      status = sem_init(sem_ctx->mutex, 0, sem_val);

      if (0 > status)
      {
         printf("Fail to initialize semaphore\n");
         status = -1;
         break;
      }

      //Enable init flag
      sem_ctx->sem_init = 1;
      sem_ctx->value = sem_val;

   } while(0);

   return status;
}

/******************************************************************************/
/* fn deinit_sem(semaphore_ctx *sem_ctx)
 *
 * brief   This function will destroy un-named semaphore
 *
 * param   sem_ctx   - semaphore context
 *
 * return  int
 */
/******************************************************************************/
int  deinit_sem(semaphore_ctx *sem_ctx)
{
   int     ret_status   = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p\n", sem_ctx->mutex);
         ret_status = -1;
         break;
      }

      //Disable Init flag
      sem_ctx->sem_init = 0;

      //Destroy semaphore
      ret_status = sem_destroy(sem_ctx->mutex);
      if(0 > ret_status)
      {
         printf("Fail to deinitialize semaphore\n");
         ret_status = -1;
         break;
      }

   } while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       open_sem(semaphore_ctx *sem_ctx)
 *
 * brief   This function will init the semaphore
 *
 * param   sem_ctx   - semaphore context
 *
 * return  int
 */
/******************************************************************************/
int  open_sem(semaphore_ctx *sem_ctx)
{
   int     ret_status   = 0;

   do
   {
      //Check semaphore is already initialized
      if (0 != sem_ctx->sem_init)
      {
         printf("Semaphore is already initialized, sem_ctx->mutex: %p\n", sem_ctx->mutex);
         ret_status = -1;
         break;
      }
      //Check identity name
      if (0 >= strlen(sem_ctx->sem_name))
      {
         printf("Invalid semaphore name with 0 length\n");
         ret_status = -1;
         break;
      }
   sem_ctx->mutex = sem_open(sem_ctx->sem_name, O_CREAT, THIRDEYE_SEM_PERMISSION, THIRDEYE_SEM_VALUE);
      if (SEM_FAILED == sem_ctx->mutex)
      {
         printf("Fail to initialize semaphore, errno: %d, str_errno: %s\n", errno, strerror(errno));
         ret_status = -1;
         break;
      }
#else
      char buf[512] = {0};
      snprintf(buf, 512, "/tmp/.%s.lock", sem_ctx->sem_name);

      errno = 0;
      sem_ctx->fd = open(buf, O_RDWR | // open the file for both read and write access
            O_CREAT | // create file if it does not already exist
            O_CLOEXEC , // close on execute
            S_IRUSR | // user permission: read
            S_IWUSR ); // user permission: write
      if (-1 == sem_ctx->fd)
      {
         printf("Fail to initialize semaphore, errno: %d, str_errno: %s", errno, strerror(errno));
         ret_status = -1;
         break;
      }
#endif
      sem_ctx->sem_init = 1;
      sem_ctx->value = THIRDEYE_SEM_VALUE;

   } while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       close_sem(semaphore_ctx *sem_ctx)
 *
 * brief   This function will de-init the named semaphore
 *
 * param   sem_ctx   - semaphore context
 *
 * return  int
 */
/******************************************************************************/
int  close_sem(semaphore_ctx *sem_ctx)
{
   int     ret_status   = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p\n", sem_ctx->mutex);
         ret_status = -1;
         break;
      }

      sem_ctx->sem_init = 0;
#if 1
      //Close semaphore
      if (0 != sem_close(sem_ctx->mutex))
      {
         printf("Fail to de-initialize semaphore, errno: %d, str_errno: %s", errno, strerror(errno));
         ret_status = -1;
         break;
      }
#else
      errno = 0;
      if (-1 == close(sem_ctx->fd))
      {
    	  printf("Fail to de-initialize semaphore, errno: %d, str_errno: %s", errno, strerror(errno));
         ret_status = -1;
         //break; //Commenting to stop recursive thing
      }
#endif
      //To remove semaphore entry completely
      //sem_unlink()

   } while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       wait_sem(semaphore_ctx *sem_ctx)
 *
 * brief   This function will acquire semaphore
 *
 * param   sem_ctx   - semaphore context
 *
 * return  int
 */
/******************************************************************************/
int  wait_sem(semaphore_ctx *sem_ctx)
{
   int     ret_status   = 0;
   int     sem_val  = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p\n", sem_ctx->mutex);
         ret_status = -1;
         break;
      }

#if 1
      //Get semaphore value
      get_sem_value(sem_ctx, &sem_val);
      if (sem_ctx->value < sem_val)
      {
         //Set default value of semaphore
         set_sem_value(sem_ctx, sem_ctx->value);
      }

      //Acquire semaphore
      if (0 != sem_wait(sem_ctx->mutex))
      {
         printf("Fail to acquire semaphore, errno: %d, str_errno: %s", errno, strerror(errno));
         ret_status = -1;
         break;
      }

#else
      if (0 != lockf(sem_ctx->fd, F_LOCK, 0))
      {
         printf("Fail to lock, errno: %d, str_errno: %s", errno, strerror(errno));
         status = DS3_FAIL_SEM_GET;
         break;
      }
#endif

   } while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       trywait_sem(semaphore_ctx *sem_ctx)
 *
 * brief   This function will try to acquire semaphore
 *
 * param   sem_ctx   - semaphore context
 *
 * return  int
 */
/******************************************************************************/
int  trywait_sem(semaphore_ctx *sem_ctx)
{
   int     	ret_status   = 0;
   int      sem_val  = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p\n", sem_ctx->mutex);
         ret_status = -1;
         break;
      }

#if 1
      //Get semaphore value
      get_sem_value(sem_ctx, &sem_val);
      if (sem_ctx->value < sem_val)
      {
         //Set default value of semaphore
         set_sem_value(sem_ctx, sem_ctx->value);
      }

      //Acquire semaphore
      if (0 != sem_trywait(sem_ctx->mutex))
      {
         printf("Fail to acquire semaphore, errno: %d, str_errno: %s\n", errno, strerror(errno));
         ret_status = -1;
         break;
      }

#else
      if (0 != lockf(sem_ctx->fd, F_LOCK, 0))
      {
         printf("Fail to lock, errno: %d, str_errno: %s", errno, strerror(errno));
         status = -1;
         break;
      }
#endif

   } while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       waittimeout_sem(semaphore_ctx *sem_ctx, struct timespec *ts)
 *
 * brief   This function will release semaphore
 *
 * param   sem_ctx   - semaphore context
 *
 *  return  int
 */
/******************************************************************************/
int  waittimeout_sem(semaphore_ctx *sem_ctx, struct timespec *ts)
{
   int    ret_status   = 0;
   int    sem_val  = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p", sem_ctx->mutex);
         ret_status = -1;
         break;
      }
#if 1
      //Get semaphore value
      get_sem_value(sem_ctx, &sem_val);
      if (sem_ctx->value < sem_val)
      {
         //Set default value of semaphore
         set_sem_value(sem_ctx, sem_ctx->value);
      }

      //Acquire semaphore
      if (-1 == sem_timedwait(sem_ctx->mutex, ts))
      {
         printf("Semaphore wait timeout reached,errno: %d, str_errno: %s\n", errno, strerror(errno));
         ret_status = -1;
         break;
      }
#else
      unsigned long int i = 0;
      unsigned long int timeout_us = (((ts->tv_sec * 1000000000) + ts->tv_nsec) / 1000);//Timeout in micro second

      for (i=0 ; i < timeout_us ; i+=1000)
      {
         if (0 != lockf(sem_ctx->fd, F_TLOCK, 0))
         {
            printf("Fail to lock, errno: %d, str_errno: %s", errno, strerror(errno));
            ret_status = -1;
         }
         else
         {
            status = 0;
            break;
         }
         usleep(1000);
      }
#endif
   }while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       post_sem(semaphore_ctx *sem_ctx)
 *
 * brief   This function will release semaphore
 *
 * param   sem_ctx   - semaphore context
 *
 * return  int
 */
/******************************************************************************/
int  post_sem(semaphore_ctx *sem_ctx)
{
   int     ret_status   = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p", sem_ctx->mutex);
         ret_status = -1;
         break;
      }

#if 1
      //Release semaphore
      if (0 != sem_post(sem_ctx->mutex))
      {
         printf("Fail to release semaphore, errno: %d, str_errno: %s", errno, strerror(errno));
         ret_status = -1;
         break;
      }
#else
      if (0 != lockf(sem_ctx->fd, F_ULOCK, 0))
      {
         printf("Fail to release semaphore, errno: %d, str_errno: %s\n", errno, strerror(errno));
         status = -1;
         break;
      }
#endif

   } while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       get_sem_value(semaphore_ctx *sem_ctx, int *value)
 *
 * brief   This function will get semaphore value
 *
 * param   sem_ctx   - semaphore context
 * param   value     - value of semaphore
 *
 * return  int
 */
/******************************************************************************/
int  get_sem_value(semaphore_ctx *sem_ctx, int *value)
{
  int     ret_status   = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p", sem_ctx->mutex);
         ret_status = -1;
         break;
      }

      //Get value of semaphore
      if (0 != sem_getvalue(sem_ctx->mutex, value))
      {
         printf("Fail to get semaphore value, errno: %d, str_errno: %s", errno, strerror(errno));
         ret_status = -1;
         break;
      }

   } while(0);

   return ret_status;
}

/******************************************************************************/
/* fn       set_sem_value(semaphore_ctx *sem_ctx, int value)
 *
 * brief   This function will set semaphore value
 *
 * param   sem_ctx   - semaphore context
 * param   value     - value of semaphore
 *
 * return  int
 */
/******************************************************************************/
int  set_sem_value(semaphore_ctx *sem_ctx, int value)
{
   int    ret_status   = 0;
   int    cur_val  = 0;
   int    i        = 0;

   do
   {
      //Check semaphore is initialized
      if (0 == sem_ctx->sem_init)
      {
         printf("Semaphore is not initialized, sem_ctx->mutex: %p", sem_ctx->mutex);
         ret_status = -1;
         break;
      }

      //Get value of semaphore
      if (0 != sem_getvalue(sem_ctx->mutex, &cur_val))
      {
         printf("Fail to get semaphore value, errno: %d, str_errno: %s", errno, strerror(errno));
         ret_status = -1;
         break;
      }

      //Need to call sem_post to increase current sem value
      if (value > cur_val)
      {
         for (i=cur_val; value > i; i++)
         {
            //Release semaphore
            if (0 != sem_post(sem_ctx->mutex))
            {
               printf("Fail to release semaphore, errno: %d, str_errno: %s", errno, strerror(errno));
               ret_status = -1;
               break;
            }
         }
      }
      //Need to call sem_wait to decrease current sem value
      else if (value < cur_val)
      {
         if (value >= 0)
         {
            for (i=cur_val; value < i; i--)
            {
               //Acquire semaphore
               if (0 != sem_wait(sem_ctx->mutex))
               {
                  printf("Fail to acquire semaphore, errno: %d, str_errno: %s", errno, strerror(errno));
                  ret_status = -1;
                  break;
               }
            }
         }
         else
         {
            printf( "Invalid value:%d received for semaphore", value);
            ret_status = -1;
         }
      }
      else
      {
         //Given value is already set
      }

   } while(0);

   return ret_status;
}
