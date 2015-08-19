#ifndef	_IFIBER_FIBER_H_
#define	_IFIBER_FIBER_H_

#define	FIBER_STACK_SIZE	(64 * 1024)				// Fiber stack size.

typedef struct 
{
	unsigned int	cwd;
	unsigned int	swd;
	unsigned int	twd;
	unsigned int	fip;
	unsigned int	fcs;
	unsigned int	foo;
	unsigned int	fos;
	unsigned char	st_space[80];
} I387Status, * I387StatusPtr;

typedef unsigned char SSEStatus[512];
typedef	SSEStatus * SSEStatusPtr;

typedef struct
{
	unsigned int		esp;										// Fiber stack pointer.
	unsigned int		eip;										// Fiber instruction pointer.
	SSEStatus			sse_status __attribute((aligned (16)));		// SSE Context.
	I387Status			i387_status;								// Intel 80387 Context.
	int					first;										// 0 if first run, 1 if not first run.
	unsigned char		stack[FIBER_STACK_SIZE];					// Fiber stack.
} Fiber, * FiberPtr;

typedef void (* FiberFunction)(void);

extern int InitMainFiber(FiberPtr fiber);
extern int InitFiber(FiberPtr fiber, FiberFunction func);
extern int SwitchFiber(FiberPtr current, FiberPtr target);

#endif
