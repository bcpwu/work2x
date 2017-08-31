#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#include <linux/stddef.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/crypto.h>
#include <linux/scatterlist.h>

#include <linux/buffer_head.h>

long jdo_sys_open(int dfd, const char __user *filename, int flags, umode_t mode)
{
	pr_info("jprobe: dfd = 0x%x, filename = 0xs "
		"flags = 0x%x mode umode %x\n", dfd, filename, flags, mode);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

struct dentry *jdo_mount_bdev(struct file_system_type *fs_type,
	int flags, const char *dev_name, void *data,
	int (*fill_super)(struct super_block *, void *, int))
{
	pr_info("%s: \n", __FUNCTION__);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int jdo_ext4_get_block(struct inode *inode, sector_t iblock,
			   struct buffer_head *bh, int flags)
{
	int len = bh->b_size >> inode->i_blkbits;
	int dev_major, dev_minor;
	dev_major = MAJOR(inode->i_sb->s_dev);
	dev_minor = MINOR(inode->i_sb->s_dev);
	if (dev_minor != 1) {
	pr_info("%s: dev:%d %d, iblock:%d, len:%d, flags:%x\n", __FUNCTION__,
		dev_major, dev_minor,
		(int)iblock, len, flags);
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}		   
static struct jprobe my_jprobe = {
	.entry = jdo_ext4_get_block, //jdo_mount_bdev, //jdo_sys_open,
	.kp = {
		.symbol_name = "_ext4_get_block", //"jdo_mount_bdev", //"do_sys_open",
	},
};

static int jprobe_init(void)
{
	int ret;
	ret = register_jprobe(&my_jprobe);
	if (ret < 0) {
		pr_err("register_jprobe failed, returned %d\n", ret);
		return -1;
	}
	pr_info("Planted jprobe at %p, handler addr %p\n",
		my_jprobe.kp.addr, my_jprobe.entry);
	return 0;
}

static void jprobe_exit(void)
{
	unregister_jprobe(&my_jprobe);
	pr_info("jprobe at %p unregistered\n", my_jprobe.kp.addr);
}

module_init(jprobe_init)
module_exit(jprobe_exit)
MODULE_LICENSE("GPL");
