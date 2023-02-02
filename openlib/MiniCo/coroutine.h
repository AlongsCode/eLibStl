#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#define COROUTINE_DEAD     0
#define COROUTINE_READY    1
#define COROUTINE_RUNNING  2
#define COROUTINE_SUSPEND  3


	typedef struct schedule schedule;
	typedef  void (WINAPI* coroutine_func)(schedule* s, void* ud);

	schedule* coroutine_open();
	void coroutine_close(schedule* s);
	int coroutine_new(schedule* s, coroutine_func, void* ud);
	void coroutine_resume(schedule* s, int id);
	void coroutine_yield(schedule* s);
	int coroutine_status(schedule* s, int id);
	int coroutine_running(schedule* s);



#ifdef __cplusplus
}
#endif

