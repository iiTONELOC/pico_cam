#include "lwip/apps/http_client.h"
#include "../piFi/pi_fi.h"
#include "http.h"

static err_t headers_done_fn(httpc_state_t *connection, void *arg,
                             struct pbuf *hdr, u16_t hdr_len, u32_t content_len)
{
    printf("in headers_done_fn\n");
    return ERR_OK;
}

static void result_fn(void *arg, httpc_result_t httpc_result, u32_t rx_content_len, u32_t srv_res, err_t err)
{
    printf(">>> result_fn >>>\n");
    printf("httpc_result: %s\n",
           httpc_result == HTTPC_RESULT_OK                ? "HTTPC_RESULT_OK"
           : httpc_result == HTTPC_RESULT_ERR_UNKNOWN     ? "HTTPC_RESULT_ERR_UNKNOWN"
           : httpc_result == HTTPC_RESULT_ERR_CONNECT     ? "HTTPC_RESULT_ERR_CONNECT"
           : httpc_result == HTTPC_RESULT_ERR_HOSTNAME    ? "HTTPC_RESULT_ERR_HOSTNAME"
           : httpc_result == HTTPC_RESULT_ERR_CLOSED      ? "HTTPC_RESULT_ERR_CLOSED"
           : httpc_result == HTTPC_RESULT_ERR_TIMEOUT     ? "HTTPC_RESULT_ERR_TIMEOUT"
           : httpc_result == HTTPC_RESULT_ERR_SVR_RESP    ? "HTTPC_RESULT_ERR_SVR_RESP"
           : httpc_result == HTTPC_RESULT_ERR_MEM         ? "HTTPC_RESULT_ERR_MEM"
           : httpc_result == HTTPC_RESULT_LOCAL_ABORT     ? "HTTPC_RESULT_LOCAL_ABORT"
           : httpc_result == HTTPC_RESULT_ERR_CONTENT_LEN ? "HTTPC_RESULT_ERR_CONTENT_LEN"
                                                          : "*UNKNOWN*");
    printf("received %ld bytes\n", rx_content_len);
    printf("err: %d\n", err);
    printf("<<< result_fn <<<\n");
}

static err_t recv_fn(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    printf(">>> recv_fn >>>\n");
    if (p == NULL)
    {
        printf("p is NULL\n");
    }
    else
    {
        printf("p: %p\n", p);
        printf("next: %p\n", p->next);
        printf("payload: %p\n", p->payload);

        // convert the payload to a string
        char *str = (char *)malloc(p->len + 1);
        memcpy(str, p->payload, p->len);
        str[p->len] = '\0';

        printf("Payload - str: %s\n", str);

        printf("len: %d\n", p->len);
        free(str);
    }
    printf("<<< recv_fn <<<\n");

    // close the connection
    pbuf_free(p);
    tcp_close(tpcb);
    return ERR_OK;
}

httpc_connection_t settings = {
    .use_proxy = 0,
    .headers_done_fn = headers_done_fn,
    .result_fn = result_fn};
httpc_state_t *connection = NULL;

// HTTP GET REQUEST
err_t http_get()
{
    ip4_addr_t server_ip = {0};
    IP4_ADDR(&server_ip, SERVER_IP_QUART_1, SERVER_IP_QUART_2,
             SERVER_IP_QUART_3, SERVER_IP_QUART_4);

    return httpc_get_file(&server_ip, SERVER_PORT, SERVER_UPLOAD_ENDPOINT,
                          &settings, recv_fn, NULL, &connection);
}

// HTTP POST REQUEST
// accept a string of uknown length as the argument
err_t http_post(char *payload)
{
    ip4_addr_t server_ip = {0};
    IP4_ADDR(&server_ip, SERVER_IP_QUART_1, SERVER_IP_QUART_2,
             SERVER_IP_QUART_3, SERVER_IP_QUART_4);

    httpc_request_info_t request_info = {
        .request_type = 1,     // Post
        .application_type = 0, // JSON
        .payload = payload};   // body

    return httpc_post_file(&server_ip, SERVER_PORT, SERVER_UPLOAD_ENDPOINT,
                           &request_info, &settings, recv_fn, NULL, &connection);
}
