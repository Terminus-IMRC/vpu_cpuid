#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <mailbox.h>
#include <vc4vec.h>

int main()
{
	int mbfd = -1;
	int s;

	const uint8_t code[] = {
		0xe0, 0x00, /* r0 <- cpuid */
		0x5a, 0x00 /* branch to link address */
	};
	const int code_size = sizeof(code);
	struct vc4vec_mem code_mem;

	vc4vec_init();
	vc4vec_mem_alloc(&code_mem, code_size);
	memcpy(code_mem.cpu_addr, code, code_size);

	mbfd = xmbox_open();

	s = execute_code(mbfd, code_mem.gpu_addr, 0, 0, 0, 0, 0, 0);

	xmbox_close(mbfd);

	vc4vec_mem_free(&code_mem);
	vc4vec_finalize();

	printf("0x%08x\n", s);

	return 0;
}
