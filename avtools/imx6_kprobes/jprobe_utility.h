
#define JPROBE_STRUCT(hook_fn) \
static struct jprobe jprobe_##hook_fn = { \
	.entry = hook_##hook_fn, \
	.kp = { \
		.symbol_name = #hook_fn, \
	}, \
};

#define HOOK_FUNCTION_INT(hook_fn) \
{ \
	pr_info("<%s>: %pS\n", \
		__FUNCTION__, \
		__builtin_return_address(0) \
		); \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return 0; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_INT_VAR(hook_fn, var) \
{ \
	pr_info("<%s>: %d, %pS\n", \
		__FUNCTION__, var, \
		__builtin_return_address(0) \
		); \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return 0; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_INT_ARG(hook_fn, arg, count) \
{ \
	static unsigned int num = 0; \
	if (count <= 1 || ++num % count == 1) { \
		pr_info("<%s>: num:%d," #arg ":%d, %pS\n", \
			__FUNCTION__, \
			num, arg, __builtin_return_address(0) \
		); \
	} \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return 0; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_VOID(hook_fn) \
{ \
	pr_info("<%s>: %pS\n", \
		__FUNCTION__, \
		__builtin_return_address(0) \
		); \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_VOID_ARG(hook_fn, arg, count) \
{ \
	static unsigned int num = 0; \
	if (count <= 1 || ++num % count == 1) { \
		pr_info("<%s>: num:%d," #arg ":%d, %pS\n", \
			__FUNCTION__, \
			num, arg, __builtin_return_address(0) \
		); \
	} \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_IPU_CHANNEL(hook_fn, chan, count) \
{ \
	static unsigned int num = 0; \
	if (count <= 1 || ++num % count == 1) { \
		pr_info("<%s>: num:%d, chan:%d, %pS\n", \
			__FUNCTION__, \
			num, IPU_CHAN_ID(chan), __builtin_return_address(0) \
		); \
	} \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return 0; \
} \
JPROBE_STRUCT(hook_fn)

#define _HOOK_FUNCTION_IPU_CHANNEL(hook_fn, chan, count) \
{ \
	static unsigned int num = 0; \
	if (count <=1 || ++num % count == 1) { \
		pr_info("<%s>: num:%d, chan:%d, %pS\n", \
			__FUNCTION__, \
			num, IPU_CHAN_ID(chan), __builtin_return_address(0) \
		); \
	} \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_IPU_CHANNEL2(hook_fn, chan1, chan2, count) \
{ \
	static unsigned int num = 0; \
	if (++num % count == 1) { \
		pr_info("<%s>: num:%d, chan1:%d, chan2:%d, %pS\n", \
			__FUNCTION__, \
			num, IPU_CHAN_ID(chan1), IPU_CHAN_ID(chan2), __builtin_return_address(0) \
		); \
	} \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return 0; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_IPU_IRQ(hook_fn, irq, count) \
{ \
	static unsigned int num = 0; \
	static int irq_prev; \
	if (irq_prev != irq || count <= 1 || ++num % count == 1) { \
		pr_info("<%s>: num:%d, irq:%d, %pS\n", \
			__FUNCTION__, \
			num, irq, __builtin_return_address(0) \
		); \
	} \
	irq_prev = irq; \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return 0; \
} \
JPROBE_STRUCT(hook_fn)

#define HOOK_FUNCTION_IPU_CMD(hook_fn, cmd, count) \
{ \
	static unsigned int num = 0; \
	if (count <= 1 || ++num % count == 1) { \
		pr_info("<%s>: num:%d, cmd:%d, %pS\n", \
			__FUNCTION__, \
			num, _IOC_NR(cmd), __builtin_return_address(0) \
		); \
	} \
	/* Always end with a call to jprobe_return(). */ \
	jprobe_return(); \
	return 0; \
} \
JPROBE_STRUCT(hook_fn)


