/*
 * $NetBSD: crypt.h,v 1.4 2006/10/27 18:22:56 drochner Exp $
 */
char	*md5crypt(const char *pw, const char *salt);

static unsigned char base64chars[] =            /* 0 ... 63 => ascii - 64 */
        "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
