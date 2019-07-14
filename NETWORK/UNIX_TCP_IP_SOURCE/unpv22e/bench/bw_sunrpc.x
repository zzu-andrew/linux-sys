/* *INDENT-OFF* */
%#define	DEBUG		/* so server runs in foreground */

struct data_in {
  opaque	data<>;		/* variable-length opaque data */
};

program BW_SUNRPC_PROG {
    version BW_SUNRPC_VERS {
		void	BW_SUNRPC(data_in) = 1;
    } = 1;
} = 0x31230001;
/* *INDENT-ON* */
