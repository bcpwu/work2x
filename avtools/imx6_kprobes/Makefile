obj-m += kprobe_open.o
obj-m += jprobe_open.o
obj-m += jprobe_fs.o
obj-m += jprobe_net.o
obj-m += jprobe_camera.o
obj-m += jprobe_video.o
obj-m += jprobe_preview.o
KDIR= /media/pwu/WD3LINUX1/yocto/imx6-0901/boundary-eval-image/tmp/work/nitrogen6x-fslc-linux-gnueabi/linux-boundary/4.1.15-r0/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* .c* .t*
       