#ifndef	_FIBER_H_
#define	_FIBER_H_

#define	FIBER_STACK_SIZE	(16 * 1024)

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
	unsigned int		esp;
	unsigned int		eip;
	unsigned int		null0;
	unsigned int		null1;
	SSEStatus			sse_status;
	I387Status			i387_status;
	int					first;
	unsigned char		stack[FIBER_STACK_SIZE];
} Fiber, * FiberPtr;

typedef void (* FiberFunction)(void);

extern int InitMainFiber(FiberPtr fiber);
extern int InitFiber(FiberPtr fiber, FiberFunction func);
extern int SwitchFiber(FiberPtr current, FiberPtr target);

#endif
