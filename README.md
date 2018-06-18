# power-optimisation-in-HPC
Save all files in same folder.

compile it using - 
$g++ main1.c cpufreq.c sysfs.c target.c -o filename -Wall

If your system do not have pci.install it by -
$sudo apt-get install pciutils-devel.*86_64

You will get a object file names as filename,run it by -
$./filename

