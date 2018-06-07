#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <rpimemmgr.h>
#include <mailbox.h>

int main()
{
    int err = 0;

    struct rpimemmgr mgr;
	int mb = -1;
    uint32_t vpuid;

	const uint8_t code[] = {
		0xe0, 0x00, /* r0 <- cpuid */
		0x5a, 0x00 /* branch to link address */
	};
	const int code_size = sizeof(code);
    void *shmem_usr = NULL;
    uint32_t shmem_bus;

    err = rpimemmgr_init(&mgr);
    if (err)
        return err;

    mb = mailbox_open();
    if (mb < 0)
        return 1;

    err = rpimemmgr_alloc_vcsm(code_size, 4096, VCSM_CACHE_TYPE_NONE,
            &shmem_usr, &shmem_bus, &mgr);
    if (err)
        return err;

    memcpy(shmem_usr, code, code_size);

	vpuid = mailbox_execute_code(mb, shmem_bus, 0, 0, 0, 0, 0, 0);
	printf("0x%08x\n", vpuid);

    err = rpimemmgr_free_by_usraddr(shmem_usr, &mgr);
    if (err)
        return err;

    err = mailbox_close(mb);
    if (err)
        return err;

    return rpimemmgr_finalize(&mgr);
}
