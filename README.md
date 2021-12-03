# picore-raylib
A slightly modified version of picore that boots and launches a raylib based program. I am doing it by adding things to the main filesystem that is loaded instead of through extensions to try to make it boot to the program as quickly as possible. This may not be a great way to do it. 

**This is a very very early test version that has only been used to boot and run a non-interactive raylib program, testing input and audio will happen eventually**

1. get a piCore image from: http://tinycorelinux.net/13.x/armv6/releases/RPi/ - This repo is based on piCore-13.1.0.zip
2. write the image to a micro-sd card
3. load your raylib program into ./raylib/opt/raylib and change the name of the executable to "raylib-start" - there is an example program in that folder already.
4. Run rebuild-raylib.sh to generate a new raylib.gz file. This file contains your raylib program along with all the libraries necessary to support it on piCore.
5. Copy raylib.gz to the boot partition on the piCore sd card. It should end up in the same place as config.txt
6. Edit config.txt to include raylib.gz. For instance if you are targeting a Raspberry Pi Zero you would look for the PI0 section, find this line:

```
    [PI0]
    initramfs rootfs-13.1.0.gz,modules-5.10.77.gz,dr_n_u.gz followkernel
```

and change it to this:

```
    [PI0]
    initramfs rootfs-13.1.0.gz,modules-5.10.77.gz,dr_n_u.gz,raylib.gz followkernel
```

# todo
The /opt/bootlocal.sh should be modified by adding this:

```cd /opt/raylib && sudo ./raylib-start```

You can open the mydata.tgz file on the secondary partition on the piCore sd card and edit bootlocal.sh there. Just be sure the permissions are correct when you write it back to the sd card. I am working on moving this to raylib.gz as well.