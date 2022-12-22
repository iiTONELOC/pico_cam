#ifndef __HTTP_H__
#define __HTTP_H__

#include "lwip/apps/http_client.h"
#include "../piFi/pi_fi.h"

err_t http_get(void);
err_t http_post(char *_payload);

#endif /* __HTTP_H__ */
