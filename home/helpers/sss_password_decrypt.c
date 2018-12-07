/*
gcc -O2 -Wall -Wextra -o sss_password_decrypt sss_password_decrypt.c \
    -Wl,-rpath,/usr/lib/x86_64-linux-gnu/sssd \
    -L/usr/lib/x86_64-linux-gnu/sssd -lsss_crypt -ltalloc
*/

#include <stdio.h>
#include <stdlib.h>
#include <talloc.h>

int nspr_nss_init(void);
int nspr_nss_cleanup(void);
int sss_password_decrypt(TALLOC_CTX*, char*, char**);

static void fail_if(int b)
{
    if (b)
        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    fail_if(argc != 2);

    int ret;
    ret = nspr_nss_init();
    fail_if(ret != 0);

    ret = nspr_nss_cleanup();
    fail_if(ret != 0);

    TALLOC_CTX *ctx = talloc_new(NULL);
    fail_if(ctx == NULL);

    char *pwd = NULL;
    ret = sss_password_decrypt(ctx, argv[1], &pwd);
    fail_if(ret != 0);

    printf("%s\n", pwd);

    talloc_free(pwd);
    talloc_free(ctx);

    return EXIT_SUCCESS;
}
