#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <net/sock.h>
#include <net/net_namespace.h>
#include <net/icmp.h>
#include <net/inet_hashtables.h>
#include <net/tcp.h>
#include <net/transp_v6.h>
#include <net/ipv6.h>
#include <net/inet_common.h>
#include <net/timewait_sock.h>
#include <net/xfrm.h>
#include <net/netdma.h>
#include <net/secure_seq.h>
#include <net/tcp_memcontrol.h>
#include <net/busy_poll.h>

#include <linux/inet.h>
#include <linux/ipv6.h>
#include <linux/stddef.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/crypto.h>
#include <linux/scatterlist.h>

static long jdo_sys_open(int dfd, const char __user *filename, int flags, umode_t mode)
{
	pr_info("jprobe: dfd = 0x%x, filename = 0xs "
		"flags = 0x%x mode umode %x\n", dfd, filename, flags, mode);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static void jdo_tcp_time_wait(struct sock *sk, int state, int timeo)
{
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = &(sk->__sk_common);
	skc_prot = sk->sk_prot;
	
	pr_info("jprobe: prot:%d(%s), daddr:%x:%d, family:%x, state:%d, timeo:%d\n",
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_daddr,
		sk->sk_dport,
		sk->sk_family,
		state, timeo);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

static struct sock *jdo_inet_csk_accept(struct sock *sk, int flags, int *err)
{
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = &(sk->__sk_common);
	skc_prot = sk->sk_prot;

	pr_info("jprobe: inet_csk_accept: prot:%d, %s, port:%d, daddr:%x, family:%x, flags:%x\n",
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_dport,
		sk->sk_daddr,
		sk->sk_family,
		flags);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

static void jdo_sk_common_release(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	if (sk->sk_protocol == 6) {
	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d,%pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		__builtin_return_address(0)
		);
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

static char *tcp_state_names[] = {
	"TCP_ESTABLISHED",
	"TCP_SYN_SENT",
	"TCP_SYN_RECV",
	"TCP_FIN_WAIT1",
	"TCP_FIN_WAIT2",
	"TCP_TIME_WAIT",
	"TCP_CLOSE",
	"TCP_CLOSE_WAIT",
	"TCP_LAST_ACK",
	"TCP_LISTEN",
	"TCP_CLOSING",	/* Now a valid state */

	"TCP_UNKONOWN_STATES"	/* Leave at the end! */
};

static void jdo_tcp_set_state(struct sock *sk, int state)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d, %s,%pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		(state>=0 && state<TCP_MAX_STATES) ? tcp_state_names[state]:tcp_state_names[TCP_MAX_STATES-1],
		__builtin_return_address(0));
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

void jdo_tcp_close(struct sock *sk, long timeout)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d, timeout:%ld,%pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		timeout,
		__builtin_return_address(0));
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

void jdo_sk_stream_wait_close(struct sock *sk, long timeout)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d, timeout:%ld,%pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		timeout,
		__builtin_return_address(0));
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

void jdo_tcp_done(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d,%pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

static void jdo_sock_release(struct socket *sock) {
	struct sock		*sk = sock->sk;
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	if (sk->sk_protocol == 6) {
	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d, %pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		__builtin_return_address(0)
		);
	}


	/* Always end with a call to jprobe_return(). */
	jprobe_return();
}
static void jdo_sk_free(struct sock *sk) {
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	if (sk->sk_protocol == 6) {
	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d,%pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		__builtin_return_address(0)
		);
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
}

void jdo_tcp_init_congestion_control(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);
	
	struct socket_common *skc;
	struct proto	*skc_prot;
	skc = (struct socket_common *)&(sk->__sk_common);
	skc_prot = sk->sk_prot;

	pr_info("%s: prot:%d(%s), family:%d, src:%x:%d, dst:%x:%d, %pS\n",
		__FUNCTION__,
		sk->sk_protocol,
		skc_prot->name,
		sk->sk_family,
		inet->inet_saddr,
		ntohs(inet->inet_sport),
		inet->inet_daddr,
		ntohs(inet->inet_dport),
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
}

static struct jprobe my_jprobe_tcp_done = {
	.entry = jdo_tcp_done, //jdo_sk_stream_wait_close, //jdo_tcp_close, //jdo_tcp_set_state, //jdo_sk_common_release, //jdo_inet_csk_accept, //jdo_tcp_time_wait, //jdo_sys_open,
	.kp = {
		.symbol_name = "tcp_done", //"sk_stream_wait_close", //"tcp_close", //"tcp_set_state", //"sk_common_release",tcp_close
		//"inet_csk_accept", //"tcp_time_wait", // "do_sys_open",
	},
};

static struct jprobe my_jprobe_tcp_close = {
	.entry = jdo_tcp_close, 
	.kp = {
		.symbol_name = "tcp_close", 
	},
};

static struct jprobe my_jprobe_sk_stream_wait_close = {
	.entry = jdo_sk_stream_wait_close, 
	.kp = {
		.symbol_name = "sk_stream_wait_close", 
	},
};
static struct jprobe my_jprobe_tcp_time_wait = {
	.entry = jdo_tcp_time_wait, 
	.kp = {
		.symbol_name = "tcp_time_wait", 
	},
};
static struct jprobe my_jprobe_sk_common_release = {
	.entry = jdo_sk_common_release, 
	.kp = {
		.symbol_name = "sk_common_release", 
	},
};
static struct jprobe my_jprobe_sock_release = {
	.entry = jdo_sock_release, 
	.kp = {
		.symbol_name = "sock_release", 
	},
};

static struct jprobe my_jprobe_sk_free = {
	.entry = jdo_sk_free, 
	.kp = {
		.symbol_name = "sk_free", 
	},
};

static struct jprobe my_jprobe_tcp_set_state = {
	.entry = jdo_tcp_set_state, 
	.kp = {
		.symbol_name = "tcp_set_state", 
	},
};

static struct jprobe my_jprobe_tcp_init_congestion_control = {
	.entry = jdo_tcp_init_congestion_control, 
	.kp = {
		.symbol_name = "tcp_init_congestion_control", 
	},
};

static struct jprobe *my_jprobes[] = {
	&my_jprobe_tcp_set_state,
	&my_jprobe_tcp_done,
	&my_jprobe_sk_stream_wait_close,
	&my_jprobe_tcp_time_wait,
	&my_jprobe_sk_common_release,
	&my_jprobe_sock_release,
	&my_jprobe_sk_free,
	&my_jprobe_tcp_close,
	&my_jprobe_tcp_init_congestion_control
};

static int jprobe_init(void)
{
	int ret;
	int i, num = sizeof(my_jprobes) / sizeof(struct jprobe *);
	ret = register_jprobes(my_jprobes, num);
	if (ret < 0) {
		pr_err("register_jprobe failed, returned %d\n", ret);
		return -1;
	}
	for (i = 0; i < num; i++) {
		pr_info("Planted jprobe at %p(%s), handler addr %p\n",
			my_jprobes[i]->kp.addr, my_jprobes[i]->kp.symbol_name, my_jprobes[i]->entry);
	}
	return 0;
}

static void jprobe_exit(void)
{
	int i, num = sizeof(my_jprobes) / sizeof(struct jprobe *);
	unregister_jprobes(my_jprobes, num);
	for (i = 0; i < num; i++) {
		pr_info("jprobe at %p (%s) unregistered\n", my_jprobes[i]->kp.addr, my_jprobes[i]->kp.symbol_name);
	}
}

module_init(jprobe_init)
module_exit(jprobe_exit)
MODULE_LICENSE("GPL");
