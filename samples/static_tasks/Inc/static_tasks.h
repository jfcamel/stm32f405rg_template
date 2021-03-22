#ifndef __STATIC_TASKS_H__
#define __STATIC_TASKS_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

  void task_init_tasks(void);

  void task_function1(void* args);
  void task_function2(void* args);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __STATIC_TASKS_H__
