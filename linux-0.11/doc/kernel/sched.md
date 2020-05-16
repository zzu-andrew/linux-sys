# 内核中有关调度的基本函数

`schedule`是早期`linus`大神在`linux` 0.11中就实现的函数。后期虽然有了很多的变化，但是本质上的实现原理是相同的。

```c

/*
 *  'schedule()' is the scheduler function. This is GOOD CODE! There
 * probably won't be any reason to change this, as it should work well
 * in all circumstances (ie gives IO-bound processes good response etc).
 * The one thing you might take a look at is the signal-handler code here.
 *
 *   NOTE!!  Task 0 is the 'idle' task, which gets called when no other
 * tasks can run. It can not be killed, and it cannot sleep. The 'state'
 * information in task[0] is never used.
 */
void schedule(void)
{
	int i,next,c;
	struct task_struct ** p;

/* check alarm, wake up any interruptible tasks that have got a signal */

	for(p = &LAST_TASK ; p > &FIRST_TASK ; --p)
		if (*p) {
			if ((*p)->alarm && (*p)->alarm < jiffies) {
					(*p)->signal |= (1<<(SIGALRM-1));
					(*p)->alarm = 0;
				}
			if (((*p)->signal & ~(_BLOCKABLE & (*p)->blocked)) &&
			(*p)->state==TASK_INTERRUPTIBLE)
				(*p)->state=TASK_RUNNING;
		}

    /* this is the scheduler proper: */
    //这里是任务调度的核心部分
	while (1) {
		c = -1;
		next = 0;
		i = NR_TASKS;
		p = &task[NR_TASKS];
        // NR_TASKS 任务的最大数值
            /*这段代码也是从任务数组最后开始循环处理，并跳过不合理的任务曹，比较每个就绪状态任务的                       counter(任务运行        时间递减)值，哪个值大，运行时间还不长，next就指向那个任务号
            */
		while (--i) {
			if (!*--p)
				continue;
            ///那个任务的counter值大，说明运行的时间还不是很长，就讲Next赋值给那个任务
			if ((*p)->state == TASK_RUNNING && (*p)->counter > c)
				c = (*p)->counter, next = i;
		}
		if (c) break;
		for(p = &LAST_TASK ; p > &FIRST_TASK ; --p)
			if (*p)
				(*p)->counter = ((*p)->counter >> 1) +
						(*p)->priority;
	}
	switch_to(next);
}
```





