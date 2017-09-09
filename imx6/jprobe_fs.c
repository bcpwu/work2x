#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

#include <linux/stddef.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/jbd2.h>

#include <linux/crypto.h>
#include <linux/scatterlist.h>

#include <linux/buffer_head.h>
#include <linux/device.h>
#include <linux/genhd.h>

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

static int jdo_ext4_load_journal(struct super_block *sb,
			     struct ext4_super_block *es,
			     unsigned long journal_devnum)
{
	pr_info("%s: \n", __FUNCTION__);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static journal_t *jdo_ext4_get_journal(struct super_block *sb,
				   unsigned int journal_inum)
{
	pr_info("%s: journal_inum:%d\n", __FUNCTION__, journal_inum);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static journal_t *jdo_ext4_get_dev_journal(struct super_block *sb,
				       dev_t j_dev)
{
	pr_info("%s: \n", __FUNCTION__);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

handle_t *jdo_ext4_journal_start_sb(struct super_block *sb, unsigned int line,
				  int type, int blocks, int rsv_blocks)
{
	pr_info("%s: \n", __FUNCTION__);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int jdo_ext4_fill_super(struct super_block *sb, void *data, int silent)
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
	pr_info("%s: dev:%d %d, iblock:%d, len:%d, flags:%x, %pS\n", __FUNCTION__,
		dev_major, dev_minor,
		(int)iblock, len, flags, __builtin_return_address(5));
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

struct buffer_head *jdo__bread(struct block_device *bdev, sector_t block, unsigned size)
{
	int dev_major, dev_minor;
	if (bdev && bdev->bd_super) {
		dev_major = MAJOR(bdev->bd_super->s_dev);
		dev_minor = MINOR(bdev->bd_super->s_dev);
		if (dev_minor != 1 && block > 1000) {
			pr_info("%s: dev:%d %d, block:%d, size:%d, %pS\n", __FUNCTION__,
				dev_major, dev_minor,
				(int)block, size, __builtin_return_address(1));
		}
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int jdo_submit_bh(int rw, struct buffer_head *bh, unsigned long bio_flags)
{
	int dev_major, dev_minor;
	struct block_device *bdev = bh->b_bdev;
	int sector = bh->b_blocknr * (bh->b_size >> 9);
	if (bdev && bdev->bd_super) {
		dev_major = MAJOR(bdev->bd_super->s_dev);
		dev_minor = MINOR(bdev->bd_super->s_dev);
		if (dev_minor != 1) {
			pr_info("%s: dev:%d %d, sector:%d, page:%d,size:%d, %pS\n", __FUNCTION__,
				dev_major, dev_minor,
				(int)sector, bh->b_page, bh->b_size, __builtin_return_address(0));
		}
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

struct inode *jdo_ext4_iget(struct super_block *sb, unsigned long ino)
{
	int dev_major, dev_minor;
	dev_major = MAJOR(sb->s_dev);
	dev_minor = MINOR(sb->s_dev);
	if (dev_minor != 1) {
		pr_info("%s: dev:%d %d, ino:%d, %pS\n", __FUNCTION__,
			dev_major, dev_minor,
			ino, __builtin_return_address(1));
	}
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

static int jdo_journal_get_superblock(journal_t *journal)
{
	struct buffer_head *bh;
	journal_superblock_t *sb;
	int dev_major = 0, dev_minor = 0;

	bh = journal->j_sb_buffer;
	sb = journal->j_superblock;

	struct block_device *bdev = bh->b_bdev;
	int sector = bh->b_blocknr * (bh->b_size >> 9);

	if (bdev && bdev->bd_super) {
		dev_major = MAJOR(bdev->bd_super->s_dev);
		dev_minor = MINOR(bdev->bd_super->s_dev);
	}

	pr_info("%s: magic:%x,%x, dev:%d,%d, sector:%d,%d,%d, bsize:%d,%d,%pS\n", __FUNCTION__, 
		sb->s_header.h_magic, cpu_to_be32(JBD2_MAGIC_NUMBER),
		dev_major, dev_minor,
		sector, bh->b_blocknr, bh->b_size,
		sb->s_blocksize, cpu_to_be32(journal->j_blocksize),
		__builtin_return_address(0));
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

journal_t * jdo_jbd2_journal_init_inode (struct inode *inode)
{
	pr_info("%s: inode %s/%ld, size %Ld, bits %d, blksize %ld\n",
		  __FUNCTION__, inode->i_sb->s_id, inode->i_ino,
		  (long long) inode->i_size,
		  inode->i_sb->s_blocksize_bits, inode->i_sb->s_blocksize);
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

struct hd_struct *jdo_add_partition(struct gendisk *disk, int partno,
				sector_t start, sector_t len, int flags,
				struct partition_meta_info *info)
{
	struct device *ddev = disk_to_dev(disk);
	const char *dname;
	dname = dev_name(ddev);
	pr_info("%s: %s, partno:%d,start:%d, len:%d, flags:%x, %pS\n",
		  __FUNCTION__, dname, partno, (int)start, (int)len, flags, __builtin_return_address(0));
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

void jdo_add_disk(struct gendisk *disk)
{
	struct device *ddev = disk_to_dev(disk);
	const char *dname;
	dname = dev_name(ddev);
	pr_info("%s: %s, %pS\n",
		  __FUNCTION__, dname, __builtin_return_address(0));
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}

int jdo_msdos_partition(struct parsed_partitions *state)
{
	pr_info("%s: %pS\n",
		  __FUNCTION__, __builtin_return_address(0));
	/* Always end with a call to jprobe_return(). */
	jprobe_return();
	return 0;
}
static struct jprobe my_jprobe_ext4_get_block = {
	.entry = jdo_ext4_get_block, //jdo_mount_bdev, //jdo_sys_open,
	.kp = {
		.symbol_name = "_ext4_get_block", //"jdo_mount_bdev", //"do_sys_open",
	},
};
static struct jprobe my_jprobe_ext4_fill_super = {
	.entry = jdo_ext4_fill_super,
	.kp = {
		.symbol_name = "ext4_fill_super",
	},
};
static struct jprobe my_jprobe_ext4_journal_start_sb = {
	.entry = jdo_ext4_journal_start_sb, 
	.kp = {
		.symbol_name = "__ext4_journal_start_sb", 
	},
};

static struct jprobe my_jprobe_ext4_get_journal = {
	.entry = jdo_ext4_get_journal, 
	.kp = {
		.symbol_name = "ext4_get_journal", 
	},
};
static struct jprobe my_jprobe__bread = {
	.entry = jdo__bread, 
	.kp = {
		.symbol_name = "__bread", 
	},
};

static struct jprobe my_jprobe_journal_get_superblock = {
	.entry = jdo_journal_get_superblock, 
	.kp = {
		.symbol_name = "journal_get_superblock", 
	},
};

static struct jprobe my_jprobe_jbd2_journal_init_inode = {
	.entry = jdo_jbd2_journal_init_inode, 
	.kp = {
		.symbol_name = "jbd2_journal_init_inode", 
	},
};

static struct jprobe my_jprobe_submit_bh = {
	.entry = jdo_submit_bh, 
	.kp = {
		.symbol_name = "_submit_bh", 
	},
};

static struct jprobe my_jprobe_ext4_iget = {
	.entry = jdo_ext4_iget, 
	.kp = {
		.symbol_name = "ext4_iget", 
	},
};

static struct jprobe my_jprobe_add_partition = {
	.entry = jdo_add_partition, 
	.kp = {
		.symbol_name = "add_partition", 
	},
};

static struct jprobe my_jprobe_add_disk = {
	.entry = jdo_add_disk, 
	.kp = {
		.symbol_name = "add_disk", 
	},
};

static struct jprobe my_jprobe_msdos_partition = {
	.entry = jdo_msdos_partition, 
	.kp = {
		.symbol_name = "msdos_partition", 
	},
};

static struct jprobe *my_jprobes[] = {
//	&my_jprobe_ext4_get_block,
	&my_jprobe_ext4_fill_super,
	//&my_jprobe_ext4_iget,
	//&my_jprobe__bread,
	&my_jprobe_journal_get_superblock,
	&my_jprobe_jbd2_journal_init_inode,
	&my_jprobe_add_partition,
	&my_jprobe_add_disk,
	&my_jprobe_msdos_partition,
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
