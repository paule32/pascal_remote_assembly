# include <httpd.h>
# include <http_config.h>
# include <http_protocol.h>

static int apaka_handler(request_rec *r) {
    if (!r->handler || strcmp(r->handler, "apaka-handler") != 0) {
        return DECLINED;
    }

    if (r->method_number != M_GET) {
        return HTTP_METHOD_NOT_ALLOWED;
    }

    ap_set_content_type(r, "text/html");
    ap_rprintf(r, "<html><body><h1>Hello, Apache Module!</h1></body></html>");

    return OK;
}

static void apaka_register_hooks(apr_pool_t *p) {
    ap_hook_handler(apaka_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA apaka_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                     // Per-directory configuration handler
    NULL,                     // Merge handler for per-directory configurations
    NULL,                     // Per-server configuration handler
    NULL,                     // Merge handler for per-server configurations
    NULL,                     // Any directives we may have for httpd
    apaka_register_hooks      // Our hook registering function
};
