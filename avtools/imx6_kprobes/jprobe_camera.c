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

/* drivers/dma/ipu/ipu_idmac.c */
#include <linux/dmaengine.h>
struct idmac_channel {
	struct dma_chan		dma_chan;
};


static int hook_ipu_enable_channel(struct idmac *idmac, struct idmac_channel *ichan)
HOOK_FUNCTION_IPU_CHANNEL(ipu_enable_channel, 0, 300)

static int hook_ipu_disable_channel(struct idmac *idmac, struct idmac_channel *ichan,
			       bool wait_for_stop)
HOOK_FUNCTION_IPU_CHANNEL(ipu_disable_channel, 0, 300)


/* /drivers/mxc/ipu3/ipu_common.c */
int hook_ipu_enable_irq(struct ipu_soc *ipu, uint32_t irq)
HOOK_FUNCTION_IPU_IRQ(ipu_enable_irq, irq, 1)

int hook_ipu_request_irq(struct ipu_soc *ipu, uint32_t irq,
		    irqreturn_t(*handler) (int, void *),
		    uint32_t irq_flags, const char *devname, void *dev_id)
HOOK_FUNCTION_IPU_IRQ(ipu_request_irq, irq, 1)

void hook_ipu_free_irq(struct ipu_soc *ipu, uint32_t irq, void *dev_id)
HOOK_FUNCTION_VOID_ARG(ipu_free_irq, irq, 300)

int32_t hook_ipu_enable_csi(struct ipu_soc *ipu, uint32_t csi)
HOOK_FUNCTION_INT_ARG(ipu_enable_csi, csi, 1)

int32_t hook_ipu_channel_request(struct ipu_soc *ipu, ipu_channel_t channel,
		ipu_channel_params_t *params, struct ipu_chan **p_ipu_chan)
HOOK_FUNCTION_IPU_CHANNEL(ipu_channel_request, channel, 1)

int32_t hook_ipu_init_channel(struct ipu_soc *ipu, ipu_channel_t channel, ipu_channel_params_t *params)
HOOK_FUNCTION_IPU_CHANNEL(ipu_init_channel, channel, 300)

static irqreturn_t hook_ipu_sync_irq_handler(int irq, void *desc)
HOOK_FUNCTION_IPU_IRQ(ipu_sync_irq_handler, irq, 300)

int32_t hook_ipu_select_buffer(struct ipu_soc *ipu, ipu_channel_t channel,
			ipu_buffer_t type, uint32_t bufNum)
HOOK_FUNCTION_IPU_CHANNEL(ipu_select_buffer, channel, 500)


int32_t hook_ipu_update_channel_buffer(struct ipu_soc *ipu, ipu_channel_t channel,
				ipu_buffer_t type, uint32_t bufNum, dma_addr_t phyaddr)
HOOK_FUNCTION_IPU_CHANNEL(ipu_update_channel_buffer, channel, 500)

/* drivers/mxc/mipi/mxc_mipi_csi2.c */
#define mxc_mipi_csi2 1
#if mxc_mipi_csi2
bool hook_mipi_csi2_enable(struct mipi_csi2_info *info)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

bool hook_mipi_csi2_disable(struct mipi_csi2_info *info)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_mipi_csi2_set_lanes(struct mipi_csi2_info *info, unsigned lanes)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

unsigned int hook_mipi_csi2_set_datatype(struct mipi_csi2_info *info,
					unsigned int datatype)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_mipi_csi2_pixelclk_enable(struct mipi_csi2_info *info)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

void hook_mipi_csi2_pixelclk_disable(struct mipi_csi2_info *info)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

#endif /* mxc_mipi_csi2 */

/* drivers/mxc/ipu3/ipu_capture.c */
#define ipu_capture 1
#if ipu_capture
int32_t hook_ipu_csi_init_interface(struct ipu_soc *ipu, uint16_t width, uint16_t height,
	uint32_t pixel_fmt, ipu_csi_signal_cfg_t cfg_param)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int32_t hook_ipu_csi_get_sensor_protocol(struct ipu_soc *ipu, uint32_t csi)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_ipu_csi_enable_mclk(struct ipu_soc *ipu, int csi, bool flag, bool wait)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

void hook_ipu_csi_set_window_size(struct ipu_soc *ipu, uint32_t width, uint32_t height, uint32_t csi)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_ipu_csi_set_mipi_di(struct ipu_soc *ipu, uint32_t num, uint32_t di_val, uint32_t csi)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_ipu_csi_set_skip_isp(struct ipu_soc *ipu, uint32_t skip, uint32_t max_ratio, uint32_t csi)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_ipu_csi_set_skip_smfc(struct ipu_soc *ipu, uint32_t skip,
	uint32_t max_ratio, uint32_t id, uint32_t csi)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

void hook_ipu_smfc_set_wmc(struct ipu_soc *ipu, ipu_channel_t channel, bool set, uint32_t level)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static irqreturn_t hook_csi_irq_handler(int irq, void *dev_id)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

#endif /* ipu_capture */

/* > drivers/media/platform/soc_camera/soc_camera.c */
#define soc_camera 1
#if soc_camera
int hook_soc_camera_power_on(struct device *dev, struct soc_camera_subdev_desc *ssdd,
			struct v4l2_clk *clk)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_soc_camera_power_off(struct device *dev, struct soc_camera_subdev_desc *ssdd,
			 struct v4l2_clk *clk)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int hook_soc_camera_clock_start(struct soc_camera_host *ici)

{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static void hook_soc_camera_clock_stop(struct soc_camera_host *ici)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

static int hook_soc_camera_streamon(struct file *file, void *priv,
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

static int hook_soc_camera_streamoff(struct file *file, void *priv,
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


static struct jprobe jprobe_soc_camera_power_on = {
	.entry = hook_soc_camera_power_on,
	.kp = {
		.symbol_name = "soc_camera_power_on", 
	},
};
static struct jprobe jprobe_soc_camera_power_off = {
	.entry = hook_soc_camera_power_off,
	.kp = {
		.symbol_name = "soc_camera_power_off", 
	},
};
static struct jprobe jprobe_soc_camera_clock_start = {
	.entry = hook_soc_camera_clock_start,
	.kp = {
		.symbol_name = "soc_camera_clock_start", 
	},
};
static struct jprobe jprobe_soc_camera_clock_stop = {
	.entry = hook_soc_camera_clock_stop,
	.kp = {
		.symbol_name = "soc_camera_clock_stop", 
	},
};
static struct jprobe jprobe_soc_camera_streamon = {
	.entry = hook_soc_camera_streamon,
	.kp = {
		.symbol_name = "soc_camera_streamon", 
	},
};
static struct jprobe jprobe_soc_camera_streamoff = {
	.entry = hook_soc_camera_streamoff,
	.kp = {
		.symbol_name = "soc_camera_streamoff", 
	},
};
#endif /* soc_camera */

/* drivers/media/platform/mxc/subdev/ov5640_mipi.c */
#define ov5640_mipi 1
#if ov5640_mipi
static int hook_ov5640_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *a)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int hook_ov5640_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *a)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static struct jprobe jprobe_ov5640_g_parm = {
	.entry = hook_ov5640_g_parm,
	.kp = {
		.symbol_name = "ov5640_g_parm", 
	},
};
static struct jprobe jprobe_ov5640_s_parm = {
	.entry = hook_ov5640_s_parm,
	.kp = {
		.symbol_name = "ov5640_s_parm", 
	},
};

#define jprobes_ov5640_mipi \
	&jprobe_ov5640_g_parm, \
	&jprobe_ov5640_s_parm,
#endif /* ov5640_mipi */

#if mxc_mipi_csi2
static struct jprobe jprobe_mipi_csi2_enable = {
	.entry = hook_mipi_csi2_enable,
	.kp = {
		.symbol_name = "mipi_csi2_enable", 
	},
};
static struct jprobe jprobe_mipi_csi2_disable = {
	.entry = hook_mipi_csi2_disable,
	.kp = {
		.symbol_name = "mipi_csi2_disable", 
	},
};
static struct jprobe jprobe_mipi_csi2_set_lanes = {
	.entry = hook_mipi_csi2_set_lanes,
	.kp = {
		.symbol_name = "mipi_csi2_set_lanes", 
	},
};
static struct jprobe jprobe_mipi_csi2_set_datatype = {
	.entry = hook_mipi_csi2_set_datatype,
	.kp = {
		.symbol_name = "mipi_csi2_set_datatype", 
	},
};
static struct jprobe jprobe_mipi_csi2_pixelclk_enable = {
	.entry = hook_mipi_csi2_pixelclk_enable,
	.kp = {
		.symbol_name = "mipi_csi2_pixelclk_enable", 
	},
};
static struct jprobe jprobe_mipi_csi2_pixelclk_disable = {
	.entry = hook_mipi_csi2_pixelclk_disable,
	.kp = {
		.symbol_name = "mipi_csi2_pixelclk_disable", 
	},
};

#endif /* mxc_mipi_csi2 */

/* > drivers/media/platform/mxc/capture/mxc_v4l2_capture.c */
#define mxc_v4l2_capture 1
#if mxc_v4l2_capture
typedef struct _cam_data {
} cam_data;

static int hook_mxc_v4l2_s_fmt(cam_data *cam, struct v4l2_format *f)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

void hook_setup_ifparm(cam_data *cam, int init_defrect)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return;
}

static int hook_mxc_v4l2_s_param(cam_data *cam, struct v4l2_streamparm *parm)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int hook_mxc_v4l2_s_std(cam_data *cam, v4l2_std_id e)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int hook_mxc_v4l2_g_std(cam_data *cam, v4l2_std_id *e)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_mxc_cam_select_input(cam_data *cam, int index)
{
	pr_info("<%s>: index:%d, %pS\n",
		__FUNCTION__,
		index,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

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

static struct jprobe jprobe_mxc_v4l2_s_fmt = {
	.entry = hook_mxc_v4l2_s_fmt,
	.kp = {
		.symbol_name = "mxc_v4l2_s_fmt", 
	},
};

static struct jprobe jprobe_setup_ifparm = {
	.entry = hook_setup_ifparm,
	.kp = {
		.symbol_name = "setup_ifparm", 
	},
};
static struct jprobe jprobe_mxc_v4l2_s_param = {
	.entry = hook_mxc_v4l2_s_param,
	.kp = {
		.symbol_name = "mxc_v4l2_s_param", 
	},
};
static struct jprobe jprobe_mxc_v4l2_s_std = {
	.entry = hook_mxc_v4l2_s_std,
	.kp = {
		.symbol_name = "mxc_v4l2_s_std", 
	},
};
static struct jprobe jprobe_mxc_v4l2_g_std = {
	.entry = hook_mxc_v4l2_g_std,
	.kp = {
		.symbol_name = "mxc_v4l2_g_std", 
	},
};
static struct jprobe jprobe_mxc_cam_select_input = {
	.entry = hook_mxc_cam_select_input,
	.kp = {
		.symbol_name = "mxc_cam_select_input", 
	},
};

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

/* drivers/media/platform/mxc/capture/ipu_prp_enc.c */
#define ipu_prp_enc 1

#if ipu_prp_enc
static irqreturn_t hook_prp_enc_callback(int irq, void *dev_id)
{
	static int count = 0;
	if (++count % 100 == 1) {
		pr_info("<%s>: %pS\n",
			__FUNCTION__,
			__builtin_return_address(0)
		);
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_prp_enc_select(void *private)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int hook_prp_enc_deselect(void *private)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int hook_prp_enc_enable_csi(void *private)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int hook_prp_enc_disable_csi(void *private)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int hook_prp_enc_disabling_tasks(void *private)
{
	pr_info("<%s>: %pS\n",
		__FUNCTION__,
		__builtin_return_address(0)
		);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static struct jprobe jprobe_prp_enc_callback = {
	.entry = hook_prp_enc_callback,
	.kp = {
		.symbol_name = "prp_enc_callback", 
	},
};

static struct jprobe jprobe_prp_enc_select = {
	.entry = hook_prp_enc_select,
	.kp = {
		.symbol_name = "prp_enc_select", 
	},
};

static struct jprobe jprobe_prp_enc_deselect = {
	.entry = hook_prp_enc_deselect,
	.kp = {
		.symbol_name = "prp_enc_deselect", 
	},
};
static struct jprobe jprobe_prp_enc_enable_csi = {
	.entry = hook_prp_enc_enable_csi,
	.kp = {
		.symbol_name = "prp_enc_enable_csi", 
	},
};
static struct jprobe jprobe_prp_enc_disable_csi = {
	.entry = hook_prp_enc_disable_csi,
	.kp = {
		.symbol_name = "prp_enc_disable_csi", 
	},
};
static struct jprobe jprobe_prp_enc_disabling_tasks = {
	.entry = hook_prp_enc_disabling_tasks,
	.kp = {
		.symbol_name = "prp_enc_disabling_tasks", 
	},
};

#define jprobes_prp_enc_callback \
	&jprobe_prp_enc_callback, \
	&jprobe_prp_enc_select, \
	&jprobe_prp_enc_deselect, \
	&jprobe_prp_enc_enable_csi, \
	&jprobe_prp_enc_disable_csi, \
	&jprobe_prp_enc_disabling_tasks,
	
#endif /* ipu_prp_enc */

/* drivers/media/platform/mxc/capture/ipu_csi_enc.c */
#define ipu_csi_enc 1

#if ipu_csi_enc
static irqreturn_t hook_csi_enc_callback(int irq, void *dev_id)
{
	static int count = 0;
	if (++count % 100 == 1) {
		pr_info("<%s>: %pS\n",
			__FUNCTION__,
			__builtin_return_address(0)
		);
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static struct jprobe jprobe_csi_enc_callback = {
	.entry = hook_csi_enc_callback,
	.kp = {
		.symbol_name = "csi_enc_callback", 
	},
};

#define jprobes_csi_enc_callback \
	&jprobe_csi_enc_callback,

#endif /* ipu_csi_enc */

/* drivers/media/platform/mxc/capture/ov5640_mipi.c , ov5640_camera_mipi_int*/
#define ov5640_mipi 0

#if ov5640_mipi
static int ioctl_send_command(struct v4l2_int_device *s, struct v4l2_send_command_control *vc) {
static int ioctl_s_power(struct v4l2_int_device *s, int on)

#endif /* ov5640_mipi */

#if ipu_capture
static struct jprobe jprobe_ipu_csi_init_interface = {
	.entry = hook_ipu_csi_init_interface,
	.kp = {
		.symbol_name = "ipu_csi_init_interface", 
	},
};
static struct jprobe jprobe_ipu_csi_get_sensor_protocol = {
	.entry = hook_ipu_csi_get_sensor_protocol,
	.kp = {
		.symbol_name = "ipu_csi_get_sensor_protocol", 
	},
};
static struct jprobe jprobe_ipu_csi_enable_mclk = {
	.entry = hook_ipu_csi_enable_mclk,
	.kp = {
		.symbol_name = "ipu_csi_enable_mclk", 
	},
};
static struct jprobe jprobe_ipu_csi_set_window_size = {
	.entry = hook_ipu_csi_set_window_size,
	.kp = {
		.symbol_name = "ipu_csi_set_window_size", 
	},
};
static struct jprobe jprobe_ipu_csi_set_mipi_di = {
	.entry = hook_ipu_csi_set_mipi_di,
	.kp = {
		.symbol_name = "_ipu_csi_set_mipi_di", 
	},
};
static struct jprobe jprobe_ipu_csi_set_skip_isp = {
	.entry = hook_ipu_csi_set_skip_isp,
	.kp = {
		.symbol_name = "_ipu_csi_set_skip_isp", 
	},
};
static struct jprobe jprobe_ipu_csi_set_skip_smfc = {
	.entry = hook_ipu_csi_set_skip_smfc,
	.kp = {
		.symbol_name = "_ipu_csi_set_skip_smfc", 
	},
};
static struct jprobe jprobe_ipu_smfc_set_wmc = {
	.entry = hook_ipu_smfc_set_wmc,
	.kp = {
		.symbol_name = "_ipu_smfc_set_wmc", 
	},
};
static struct jprobe jprobe_csi_irq_handler = {
	.entry = hook_csi_irq_handler,
	.kp = {
		.symbol_name = "csi_irq_handler", 
	},
};

#endif /* ipu_capture */

static struct jprobe *my_jprobes[] = {
	&jprobe_ipu_enable_channel,
	&jprobe_ipu_disable_channel,
	
	&jprobe_ipu_enable_irq,
	&jprobe_ipu_request_irq,
	&jprobe_ipu_free_irq,
	&jprobe_ipu_enable_csi,
	&jprobe_ipu_channel_request,
	&jprobe_ipu_init_channel,
	&jprobe_ipu_sync_irq_handler,
	&jprobe_ipu_select_buffer,
	&jprobe_ipu_update_channel_buffer,
#if mxc_mipi_csi2
	&jprobe_mipi_csi2_enable,
	&jprobe_mipi_csi2_disable,
	&jprobe_mipi_csi2_set_lanes,
	&jprobe_mipi_csi2_set_datatype,
	&jprobe_mipi_csi2_pixelclk_enable,
	&jprobe_mipi_csi2_pixelclk_disable,

#endif /* mxc_mipi_csi2 */

#if ipu_capture
	&jprobe_ipu_csi_init_interface,
	&jprobe_ipu_csi_get_sensor_protocol,
	&jprobe_ipu_csi_enable_mclk,
	&jprobe_ipu_csi_set_window_size,
	&jprobe_ipu_csi_set_mipi_di,
	&jprobe_ipu_csi_set_skip_isp,
	&jprobe_ipu_csi_set_skip_smfc,
	&jprobe_ipu_smfc_set_wmc,
	&jprobe_csi_irq_handler,
#endif /* ipu_capture */

#if soc_camera
	&jprobe_soc_camera_power_on,
	&jprobe_soc_camera_power_off,
	&jprobe_soc_camera_clock_start,
	&jprobe_soc_camera_clock_stop,
	&jprobe_soc_camera_streamon,
	&jprobe_soc_camera_streamoff,
#endif /* soc_camera */

#if ov5640_mipi
	jprobes_ov5640_mipi
#endif /* ov5640_mipi */

#if mxc_v4l2_capture
	jprobes_mxc_v4l2_capture
#endif /* mxc_v4l2_capture */

#if ipu_prp_enc
	jprobes_prp_enc_callback
#endif /* ipu_prp_enc */

#if ipu_csi_enc
	jprobes_csi_enc_callback
#endif /* ipu_csi_enc */

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
