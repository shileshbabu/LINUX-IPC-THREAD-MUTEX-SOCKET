/*****************************************************************************/
/******************************************************************************/
/* file   semaphores.h
*
*  brief    Semaphores APIs
*
* Author Shilesh babu
*
*/

/******************************************************************************/
/*****************************************************************************/

#ifndef SEMAPHORES_H_
#define SEMAPHORES_H_

/******************************************************************************/
/******************************************************************************/
/* file   semaphores.h

  brief    Semaphores APIs

  ingroup  module
 */
/******************************************************************************
 *                               Header Files
 ******************************************************************************/
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <string.h>

/******************************************************************************
 *                               Macros
 *****************************************************************************/
/* var    THIRDEYE_SEM_PERMISSION
  brief    Semaphore region permission
 */
#define     THIRDEYE_SEM_PERMISSION          0666
/* var    THIRDEYE_SEM_VALUE
  brief    Semaphore region value
 */
#define     THIRDEYE_SEM_VALUE               1

/******************************************************************************
 *                               Enumerations
 *****************************************************************************/

/******************************************************************************
 *                               Structures
 *****************************************************************************/
/* typedef _semaphore_ctx_ semaphore_ctx
   brief  A type definition of semaphore context
   struct _semaphore_ctx_
   brief  Semaphore context
 */
typedef struct _semaphore_ctx_
{
   char     sem_init;
   char     sem_name[256];
   sem_t    *mutex;
   sem_t    unnamed_sem;
   unsigned int   value;
#if 0
   int      fd;
#endif

}semaphore_ctx;

/******************************************************************************
 *                               Function Declarations
 *****************************************************************************/
/******************************************************************************/
/*  fn       init_sem(semaphore_ctx *sem_ctx, unsigned int sem_val)
 *
 *   brief   This function will init the un-named semaphore
 *
 *   param   [IN]  sem_ctx  - semaphore context
 *   param   [IN]  sem_val  - value of semaphore
 *
 *   return  int
 */
/******************************************************************************/
int  init_sem(semaphore_ctx *sem_ctx, unsigned int sem_val);

/******************************************************************************/
/*   fn       deinit_sem(semaphore_ctx *sem_ctx)
 *
 *   brief   This function will destroy un-named semaphore
 *
 *   param   sem_ctx   - semaphore context
 *
 *   return  int
 */
/******************************************************************************/
int  deinit_sem(semaphore_ctx *sem_ctx);

/******************************************************************************/
/*  fn       open_sem(semaphore_ctx *sem_ctx)
 *
 *  brief   This function will init the semaphore
 *
 *  param   sem_ctx   - semaphore context
 *
 *  return  int
 */
/******************************************************************************/
int  open_sem(semaphore_ctx *sem_ctx);

/******************************************************************************/
/*  fn       close_sem(semaphore_ctx *sem_ctx)
 *
 *  brief   This function will de-init the named semaphore
 *
 *  param   sem_ctx   - semaphore context
 *
 *  return  int
 */
/******************************************************************************/
int  close_sem(semaphore_ctx *sem_ctx);

/******************************************************************************/
/*  fn       wait_sem(semaphore_ctx *sem_ctx)
 *
 *  brief   This function will acquire semaphore
 *
 *  param   sem_ctx   - semaphore context
 *
 *  return  int
 */
/******************************************************************************/
int  wait_sem(semaphore_ctx *sem_ctx);

/******************************************************************************/
/*!  fn       trywait_sem(semaphore_ctx *sem_ctx)
 *
 *   brief   This function will try to acquire semaphore
 *
 *   param   sem_ctx   - semaphore context
 *
 *   return  int
 */
/******************************************************************************/
int  trywait_sem(semaphore_ctx *sem_ctx);

/******************************************************************************/
/*   fn       waittimeout_sem(semaphore_ctx *sem_ctx)
 *
 *   brief   This function will release semaphore
 *
 *   param   sem_ctx   - semaphore context
 *
 *   return  int
 */
/******************************************************************************/
int  waittimeout_sem(semaphore_ctx *sem_ctx, struct timespec *ts);

/******************************************************************************/
/*   fn       post_sem(semaphore_ctx *sem_ctx)
 *
 *   brief   This function will release semaphore
 *
 *   param   sem_ctx   - semaphore context
 *
 *   return  int
 */
/******************************************************************************/
int  post_sem(semaphore_ctx *sem_ctx);

/******************************************************************************/
/*   fn       get_sem_value(semaphore_ctx *sem_ctx, int *value)
 *
 *   brief   This function will get semaphore value
 *
 *   param   sem_ctx   - semaphore context
 *   param   value     - value of semaphore
 *
 *   return  int
 */
/******************************************************************************/
int  get_sem_value(semaphore_ctx *sem_ctx, int *value);

/******************************************************************************/
/*   fn       set_sem_value(semaphore_ctx *sem_ctx, int value)
 *
 *   brief   This function will set semaphore value
 *
 *   param   sem_ctx   - semaphore context
 *   param   value     - value of semaphore
 *
 *   return  int
 */
/******************************************************************************/
int  set_sem_value(semaphore_ctx *sem_ctx, int value);



#endif /* SEMAPHORES_H_ */

