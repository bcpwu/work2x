/* video interface, pipeline
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#include <linux/stddef.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/crypto.h>
#include <linux/scatterlist.h>


#include <linux/dma-mapping.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include <linux/list.h>
#include <linux/clk.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
//#include <linux/dma/ipu-dma.h>

#include <linux/busfreq-imx.h>
#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/ipu-v3.h>
#include <linux/irq.h>
#include <linux/irqdesc.h>
#include <linux/module.h>
#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/pm_runtime.h>
#include <linux/reset.h>
#include <linux/spinlock.h>
#include <linux/types.h>

#include "jprobe_utility.h"

/* > drivers/media/platform/mxc/output/mxc_vout.c */
#define mxc_vout 1
#if mxc_vout
/* v4l2_ioctl_ops */
static int hook_mxc_vidioc_qbuf(struct file *file, void *fh,
			struct v4l2_buffer *buffer)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe jprobe_mxc_vidioc_qbuf = {
	.entry = hook_mxc_vidioc_qbuf,
	.kp = {
		.symbol_name = "mxc_vidioc_qbuf", 
	},
};

static int hook_mxc_vidioc_dqbuf(struct file *file, void *fh, struct v4l2_buffer *b)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe jprobe_mxc_vidioc_dqbuf = {
	.entry = hook_mxc_vidioc_dqbuf,
	.kp = {
		.symbol_name = "mxc_vidioc_dqbuf", 
	},
};

static int hook_mxc_vidioc_streamon(struct file *file, void *fh,
				enum v4l2_buf_type i)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe jprobe_mxc_vidioc_streamon = {
	.entry = hook_mxc_vidioc_streamon,
	.kp = {
		.symbol_name = "mxc_vidioc_streamon", 
	},
};

static int hook_mxc_vidioc_streamoff(struct file *file, void *fh,
				enum v4l2_buf_type i)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static struct jprobe jprobe_mxc_vidioc_streamoff = {
	.entry = hook_mxc_vidioc_streamoff,
	.kp = {
		.symbol_name = "mxc_vidioc_streamoff", 
	},
};

/* videobuf_queue_ops */
static int hook_mxc_vout_buffer_prepare(struct videobuf_queue *q,
			    struct videobuf_buffer *vb,
			    enum v4l2_field field)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe jprobe_mxc_vout_buffer_prepare = {
	.entry = hook_mxc_vout_buffer_prepare,
	.kp = {
		.symbol_name = "mxc_vout_buffer_prepare", 
	},
};
static void hook_mxc_vout_buffer_queue(struct videobuf_queue *q,
			  struct videobuf_buffer *vb)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe jprobe_mxc_vout_buffer_queue = {
	.entry = hook_mxc_vout_buffer_queue,
	.kp = {
		.symbol_name = "mxc_vout_buffer_queue", 
	},
};
static void hook_mxc_vout_buffer_release(struct videobuf_queue *q,
			    struct videobuf_buffer *vb)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe jprobe_mxc_vout_buffer_release = {
	.entry = hook_mxc_vout_buffer_release,
	.kp = {
		.symbol_name = "mxc_vout_buffer_release", 
	},
};

#define jprobes_mxc_vout \
	&jprobe_mxc_vidioc_qbuf, \
	&jprobe_mxc_vidioc_dqbuf, \
	&jprobe_mxc_vidioc_streamon, \
	&jprobe_mxc_vidioc_streamoff, \
	&jprobe_mxc_vout_buffer_prepare, \
	&jprobe_mxc_vout_buffer_queue, \
	&jprobe_mxc_vout_buffer_release,

#endif /* mxc_v4l2_capture */

/* drivers/mxc/vpu/mxc_vpu.c  */
#define mxc_vpu 1
#if mxc_vpu
static long hook_vpu_ioctl(struct file *filp, u_int cmd,
		     u_long arg)
HOOK_FUNCTION_IPU_CMD(vpu_ioctl, cmd, 10)

static irqreturn_t hook_vpu_ipi_irq_handler(int irq, void *dev_id)
HOOK_FUNCTION_INT_ARG(vpu_ipi_irq_handler, irq, 10)

#define jprobes_mxc_vpu \
	&jprobe_vpu_ioctl, \
	&jprobe_vpu_ipi_irq_handler,

#endif /* mxc_vpu */

/* drivers/mxc/ipu3/ipu_disp.c  */
#define ipu_disp 1
#if ipu_disp
struct dp_csc_param_t {
	int mode;
	const void *coeff;
};
static void hook__ipu_dc_link_event(struct ipu_soc *ipu,
		int chan, int event, int addr, int priority)
_HOOK_FUNCTION_IPU_CHANNEL(_ipu_dc_link_event, chan, 1)

void hook___ipu_dp_csc_setup(struct ipu_soc *ipu,
		int dp, struct dp_csc_param_t dp_csc_param,
		bool srm_mode_update)
HOOK_FUNCTION_VOID(__ipu_dp_csc_setup)

int hook__ipu_dp_init(struct ipu_soc *ipu,
		ipu_channel_t channel, uint32_t in_pixel_fmt,
		uint32_t out_pixel_fmt)
HOOK_FUNCTION_IPU_CHANNEL(_ipu_dp_init, channel, 1)

void hook__ipu_dc_init(struct ipu_soc *ipu, int dc_chan, int di, bool interlaced, uint32_t pixel_fmt)
HOOK_FUNCTION_VOID(_ipu_dc_init)

void hook__ipu_dp_dc_enable(struct ipu_soc *ipu, ipu_channel_t channel)
_HOOK_FUNCTION_IPU_CHANNEL(_ipu_dp_dc_enable, channel, 1)

static irqreturn_t hook_dc_irq_handler(int irq, void *dev_id)
HOOK_FUNCTION_IPU_IRQ(dc_irq_handler, irq, 1)

void hook__ipu_dp_dc_disable(struct ipu_soc *ipu, ipu_channel_t channel, bool swap)
_HOOK_FUNCTION_IPU_CHANNEL(_ipu_dp_dc_disable, channel, 1)

int32_t hook_ipu_init_sync_panel(struct ipu_soc *ipu, int disp, uint32_t pixel_clk,
			    uint16_t width, uint16_t height,
			    uint32_t pixel_fmt,
			    uint16_t h_start_width, uint16_t h_sync_width,
			    uint16_t h_end_width, uint16_t v_start_width,
			    uint16_t v_sync_width, uint16_t v_end_width,
			    uint32_t v_to_h_sync, ipu_di_signal_cfg_t sig)
HOOK_FUNCTION_INT(ipu_init_sync_panel)

int hook_ipu_init_async_panel(struct ipu_soc *ipu, int disp, int type, uint32_t cycle_time,
			 uint32_t pixel_fmt, ipu_adc_sig_cfg_t sig)
HOOK_FUNCTION_INT(ipu_init_async_panel)

int32_t hook_ipu_disp_set_color_key(struct ipu_soc *ipu, ipu_channel_t channel,
				bool enable, uint32_t color_key)
HOOK_FUNCTION_INT(ipu_disp_set_color_key)

int32_t hook_ipu_disp_set_window_pos(struct ipu_soc *ipu, ipu_channel_t channel,
				int16_t x_pos, int16_t y_pos)
HOOK_FUNCTION_INT(ipu_disp_set_window_pos)

#define jprobes_ipu_disp \
	&jprobe__ipu_dc_link_event, \
	&jprobe___ipu_dp_csc_setup, \
	&jprobe__ipu_dp_init, \
	&jprobe__ipu_dc_init, \
	&jprobe__ipu_dp_dc_enable, \
	&jprobe_dc_irq_handler, \
	&jprobe__ipu_dp_dc_disable, \
	&jprobe_ipu_init_sync_panel, \
	&jprobe_ipu_init_async_panel, \
	&jprobe_ipu_disp_set_color_key, \
	&jprobe_ipu_disp_set_window_pos,
#endif /* ipu_disp */

/* drivers/mxc/ipu3/ipu_ic.c  */
#define ipu_ic 1
#if ipu_ic
void hook__ipu_ic_enable_task(struct ipu_soc *ipu, ipu_channel_t channel)
_HOOK_FUNCTION_IPU_CHANNEL(_ipu_ic_enable_task, channel, 300)

void hook__ipu_ic_disable_task(struct ipu_soc *ipu, ipu_channel_t channel)
_HOOK_FUNCTION_IPU_CHANNEL(_ipu_ic_disable_task, channel, 300)

void hook__ipu_vdi_init(struct ipu_soc *ipu, ipu_channel_t channel, ipu_channel_params_t *params)
_HOOK_FUNCTION_IPU_CHANNEL(_ipu_vdi_init, channel, 1)

void hook__ipu_vdi_uninit(struct ipu_soc *ipu)
HOOK_FUNCTION_VOID(_ipu_vdi_uninit)

int hook__ipu_ic_init_prpvf(struct ipu_soc *ipu, ipu_channel_params_t *params,
		       bool src_is_csi)
HOOK_FUNCTION_INT_ARG(_ipu_ic_init_prpvf, src_is_csi, 300)

void hook__ipu_ic_uninit_prpvf(struct ipu_soc *ipu)
HOOK_FUNCTION_VOID_ARG(_ipu_ic_uninit_prpvf, 0, 300)
int hook__ipu_ic_init_prpenc(struct ipu_soc *ipu, ipu_channel_params_t *params,
			bool src_is_csi)
HOOK_FUNCTION_INT(_ipu_ic_init_prpenc)
void hook__ipu_ic_uninit_prpenc(struct ipu_soc *ipu)
HOOK_FUNCTION_VOID(_ipu_ic_uninit_prpenc)
int hook__ipu_ic_init_pp(struct ipu_soc *ipu, ipu_channel_params_t *params)
HOOK_FUNCTION_INT(_ipu_ic_init_pp)
void hook__ipu_ic_uninit_pp(struct ipu_soc *ipu)
HOOK_FUNCTION_VOID(_ipu_ic_uninit_pp)
int hook__ipu_ic_idma_init(struct ipu_soc *ipu, int dma_chan,
		uint16_t width, uint16_t height,
		int burst_size, ipu_rotate_mode_t rot)
HOOK_FUNCTION_INT_ARG(_ipu_ic_idma_init, dma_chan, 500)

#define jprobes_ipu_ic \
	&jprobe__ipu_ic_enable_task, \
	&jprobe__ipu_ic_disable_task, \
	&jprobe__ipu_vdi_init, \
	&jprobe__ipu_vdi_uninit, \
	&jprobe__ipu_ic_init_prpvf, \
	&jprobe__ipu_ic_uninit_prpvf, \
	&jprobe__ipu_ic_init_prpenc, \
	&jprobe__ipu_ic_uninit_prpenc, \
	&jprobe__ipu_ic_init_pp, \
	&jprobe__ipu_ic_uninit_pp, \
	&jprobe__ipu_ic_idma_init, \

#endif /* ipu_ic */

/* drivers/mxc/ipu3/ipu_device.c  */
#define ipu_device 1
#if ipu_device
static long hook_mxc_ipu_ioctl(struct file *file,
		unsigned int cmd, unsigned long arg)
HOOK_FUNCTION_IPU_CMD(mxc_ipu_ioctl, cmd, 500)

static irqreturn_t hook_task_irq_handler(int irq, void *dev_id)
HOOK_FUNCTION_IPU_IRQ(task_irq_handler, irq, 300)

static void hook_do_task(struct ipu_task_entry *t)
HOOK_FUNCTION_VOID_ARG(do_task, 0, 300)

static int hook_mxc_ipu_mmap(struct file *file, struct vm_area_struct *vma)
HOOK_FUNCTION_INT(mxc_ipu_mmap)

/* ipu_common.c */
int32_t hook_ipu_init_channel_buffer(struct ipu_soc *ipu, ipu_channel_t channel,
				ipu_buffer_t type,
				uint32_t pixel_fmt,
				uint16_t width, uint16_t height,
				uint32_t stride,
				ipu_rotate_mode_t rot_mode,
				dma_addr_t phyaddr_0, dma_addr_t phyaddr_1,
				dma_addr_t phyaddr_2,
				uint32_t u, uint32_t v)
HOOK_FUNCTION_IPU_CHANNEL(ipu_init_channel_buffer, channel, 300)

#define jprobes_ipu_device \
	&jprobe_mxc_ipu_ioctl, \
	&jprobe_task_irq_handler, \
	&jprobe_do_task, \
	&jprobe_ipu_init_channel_buffer, \
	&jprobe_mxc_ipu_mmap, \

#endif /* ipu_device */

/* > drivers/media/platform/mxc/capture/mxc_v4l2_capture.c */
#define mxc_v4l2_capture 1
#if mxc_v4l2_capture
typedef struct _cam_data {
} cam_data;

static int hook_mxc_v4l2_s_fmt(cam_data *cam, struct v4l2_format *f)
HOOK_FUNCTION_INT(mxc_v4l2_s_fmt)

void hook_setup_ifparm(cam_data *cam, int init_defrect)
HOOK_FUNCTION_VOID(setup_ifparm)


static int hook_mxc_v4l2_s_param(cam_data *cam, struct v4l2_streamparm *parm)
HOOK_FUNCTION_INT(mxc_v4l2_s_param)

static int hook_mxc_v4l2_s_std(cam_data *cam, v4l2_std_id e)
HOOK_FUNCTION_INT(mxc_v4l2_s_std)


static int hook_mxc_v4l2_g_std(cam_data *cam, v4l2_std_id *e)
HOOK_FUNCTION_INT(mxc_v4l2_g_std)

int hook_mxc_cam_select_input(cam_data *cam, int index)
HOOK_FUNCTION_INT_VAR(mxc_cam_select_input, index)


static long hook_mxc_v4l_do_ioctl(struct file *file,
			    unsigned int ioctlnr, void *arg)
{
	static unsigned int nr_counts[256];
	int nr = _IOC_NR(ioctlnr);
	bool show = true;
	nr_counts[nr] ++;
	if ((nr == 17 || nr == 15) && (nr_counts[nr] % 500 != 1))
		show = false;
	if (show)
	pr_info("<%s>: ioctl:%d, cnt:%d, %pS\n",
		__FUNCTION__,
		nr, nr_counts[nr],
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe jprobe_mxc_v4l_do_ioctl = {
	.entry = hook_mxc_v4l_do_ioctl,
	.kp = {
		.symbol_name = "mxc_v4l_do_ioctl", 
	},
};
#define jprobes_mxc_v4l2_capture \
	&jprobe_mxc_v4l2_s_fmt, \
	&jprobe_setup_ifparm, \
	&jprobe_mxc_v4l2_s_param, \
	&jprobe_mxc_v4l2_s_std, \
	&jprobe_mxc_v4l2_g_std, \
	&jprobe_mxc_cam_select_input, \
	&jprobe_mxc_v4l_do_ioctl,

#endif /* mxc_v4l2_capture */

static struct jprobe *my_jprobes[] = {
#if mxc_vout
	jprobes_mxc_vout
#endif /* mxc_vout */
#if mxc_vpu
	jprobes_mxc_vpu
#endif /* mxc_vpu */
#if ipu_disp
	jprobes_ipu_disp
#endif /* ipu_disp */
#if ipu_device
	jprobes_ipu_device
#endif /* ipu_device */
#if ipu_ic
	jprobes_ipu_ic
#endif /* ipu_ic */

#if mxc_v4l2_capture
	jprobes_mxc_v4l2_capture
#endif /* mxc_v4l2_capture */
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
