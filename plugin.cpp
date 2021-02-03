#include <string>
#include <vector>
#include <set>
#include <map>
#include <stdexcept>
#include "simPlusPlus/Plugin.h"
#include "simPlusPlus/Handle.h"
#include "config.h"
#include "plugin.h"
#include "stubs.h"
#include "zmq.h"

using sim::Handle;

typedef void zmq_context_t;
typedef void zmq_socket_t;
template<> std::string Handle<void>::tag() { return "simZMQ.*"; }
template<> std::string Handle<zmq_msg_t>::tag() { return "simZMQ.msg"; }

class Plugin : public sim::Plugin
{
public:
    void onStart()
    {
        if(!registerScriptStuff())
            throw std::runtime_error("failed to register script stuff");

        sim::registerScriptVariable("simZMQ.EPERM", EPERM, 0);
        sim::registerScriptVariable("simZMQ.ENOENT", ENOENT, 0);
        sim::registerScriptVariable("simZMQ.ESRCH", ESRCH, 0);
        sim::registerScriptVariable("simZMQ.EINTR", EINTR, 0);
        sim::registerScriptVariable("simZMQ.EIO", EIO, 0);
        sim::registerScriptVariable("simZMQ.ENXIO", ENXIO, 0);
        sim::registerScriptVariable("simZMQ.E2BIG", E2BIG, 0);
        sim::registerScriptVariable("simZMQ.ENOEXEC", ENOEXEC, 0);
        sim::registerScriptVariable("simZMQ.EBADF", EBADF, 0);
        sim::registerScriptVariable("simZMQ.ECHILD", ECHILD, 0);
        sim::registerScriptVariable("simZMQ.EDEADLK", EDEADLK, 0);
        sim::registerScriptVariable("simZMQ.ENOMEM", ENOMEM, 0);
        sim::registerScriptVariable("simZMQ.EACCES", EACCES, 0);
        sim::registerScriptVariable("simZMQ.EFAULT", EFAULT, 0);
        sim::registerScriptVariable("simZMQ.ENOTBLK", ENOTBLK, 0);
        sim::registerScriptVariable("simZMQ.EBUSY", EBUSY, 0);
        sim::registerScriptVariable("simZMQ.EEXIST", EEXIST, 0);
        sim::registerScriptVariable("simZMQ.EXDEV", EXDEV, 0);
        sim::registerScriptVariable("simZMQ.ENODEV", ENODEV, 0);
        sim::registerScriptVariable("simZMQ.ENOTDIR", ENOTDIR, 0);
        sim::registerScriptVariable("simZMQ.EISDIR", EISDIR, 0);
        sim::registerScriptVariable("simZMQ.EINVAL", EINVAL, 0);
        sim::registerScriptVariable("simZMQ.ENFILE", ENFILE, 0);
        sim::registerScriptVariable("simZMQ.EMFILE", EMFILE, 0);
        sim::registerScriptVariable("simZMQ.ENOTTY", ENOTTY, 0);
        sim::registerScriptVariable("simZMQ.ETXTBSY", ETXTBSY, 0);
        sim::registerScriptVariable("simZMQ.EFBIG", EFBIG, 0);
        sim::registerScriptVariable("simZMQ.ENOSPC", ENOSPC, 0);
        sim::registerScriptVariable("simZMQ.ESPIPE", ESPIPE, 0);
        sim::registerScriptVariable("simZMQ.EROFS", EROFS, 0);
        sim::registerScriptVariable("simZMQ.EMLINK", EMLINK, 0);
        sim::registerScriptVariable("simZMQ.EPIPE", EPIPE, 0);
        sim::registerScriptVariable("simZMQ.EDOM", EDOM, 0);
        sim::registerScriptVariable("simZMQ.ERANGE", ERANGE, 0);
        sim::registerScriptVariable("simZMQ.EAGAIN", EAGAIN, 0);
        sim::registerScriptVariable("simZMQ.EWOULDBLOCK", EWOULDBLOCK, 0);
        sim::registerScriptVariable("simZMQ.EINPROGRESS", EINPROGRESS, 0);
        sim::registerScriptVariable("simZMQ.EALREADY", EALREADY, 0);
        sim::registerScriptVariable("simZMQ.ENOTSOCK", ENOTSOCK, 0);
        sim::registerScriptVariable("simZMQ.EDESTADDRREQ", EDESTADDRREQ, 0);
        sim::registerScriptVariable("simZMQ.EMSGSIZE", EMSGSIZE, 0);
        sim::registerScriptVariable("simZMQ.EPROTOTYPE", EPROTOTYPE, 0);
        sim::registerScriptVariable("simZMQ.ENOPROTOOPT", ENOPROTOOPT, 0);
        sim::registerScriptVariable("simZMQ.EPROTONOSUPPORT", EPROTONOSUPPORT, 0);
        sim::registerScriptVariable("simZMQ.ESOCKTNOSUPPORT", ESOCKTNOSUPPORT, 0);
        sim::registerScriptVariable("simZMQ.ENOTSUP", ENOTSUP, 0);
        sim::registerScriptVariable("simZMQ.EOPNOTSUPP", EOPNOTSUPP, 0);
        sim::registerScriptVariable("simZMQ.EPFNOSUPPORT", EPFNOSUPPORT, 0);
        sim::registerScriptVariable("simZMQ.EAFNOSUPPORT", EAFNOSUPPORT, 0);
        sim::registerScriptVariable("simZMQ.EADDRINUSE", EADDRINUSE, 0);
        sim::registerScriptVariable("simZMQ.EADDRNOTAVAIL", EADDRNOTAVAIL, 0);
        sim::registerScriptVariable("simZMQ.ENETDOWN", ENETDOWN, 0);
        sim::registerScriptVariable("simZMQ.ENETUNREACH", ENETUNREACH, 0);
        sim::registerScriptVariable("simZMQ.ENETRESET", ENETRESET, 0);
        sim::registerScriptVariable("simZMQ.ECONNABORTED", ECONNABORTED, 0);
        sim::registerScriptVariable("simZMQ.ECONNRESET", ECONNRESET, 0);
        sim::registerScriptVariable("simZMQ.ENOBUFS", ENOBUFS, 0);
        sim::registerScriptVariable("simZMQ.EISCONN", EISCONN, 0);
        sim::registerScriptVariable("simZMQ.ENOTCONN", ENOTCONN, 0);
        sim::registerScriptVariable("simZMQ.ESHUTDOWN", ESHUTDOWN, 0);
        sim::registerScriptVariable("simZMQ.ETOOMANYREFS", ETOOMANYREFS, 0);
        sim::registerScriptVariable("simZMQ.ETIMEDOUT", ETIMEDOUT, 0);
        sim::registerScriptVariable("simZMQ.ECONNREFUSED", ECONNREFUSED, 0);
        sim::registerScriptVariable("simZMQ.ELOOP", ELOOP, 0);
        sim::registerScriptVariable("simZMQ.ENAMETOOLONG", ENAMETOOLONG, 0);
        sim::registerScriptVariable("simZMQ.EHOSTDOWN", EHOSTDOWN, 0);
        sim::registerScriptVariable("simZMQ.EHOSTUNREACH", EHOSTUNREACH, 0);
        sim::registerScriptVariable("simZMQ.ENOTEMPTY", ENOTEMPTY, 0);
        sim::registerScriptVariable("simZMQ.EPROCLIM", EPROCLIM, 0);
        sim::registerScriptVariable("simZMQ.EUSERS", EUSERS, 0);
        sim::registerScriptVariable("simZMQ.EDQUOT", EDQUOT, 0);
        sim::registerScriptVariable("simZMQ.ESTALE", ESTALE, 0);
        sim::registerScriptVariable("simZMQ.EREMOTE", EREMOTE, 0);
        sim::registerScriptVariable("simZMQ.EBADRPC", EBADRPC, 0);
        sim::registerScriptVariable("simZMQ.ERPCMISMATCH", ERPCMISMATCH, 0);
        sim::registerScriptVariable("simZMQ.EPROGUNAVAIL", EPROGUNAVAIL, 0);
        sim::registerScriptVariable("simZMQ.EPROGMISMATCH", EPROGMISMATCH, 0);
        sim::registerScriptVariable("simZMQ.EPROCUNAVAIL", EPROCUNAVAIL, 0);
        sim::registerScriptVariable("simZMQ.ENOLCK", ENOLCK, 0);
        sim::registerScriptVariable("simZMQ.ENOSYS", ENOSYS, 0);
        sim::registerScriptVariable("simZMQ.EFTYPE", EFTYPE, 0);
        sim::registerScriptVariable("simZMQ.EAUTH", EAUTH, 0);
        sim::registerScriptVariable("simZMQ.ENEEDAUTH", ENEEDAUTH, 0);
        sim::registerScriptVariable("simZMQ.EPWROFF", EPWROFF, 0);
        sim::registerScriptVariable("simZMQ.EDEVERR", EDEVERR, 0);
        sim::registerScriptVariable("simZMQ.EOVERFLOW", EOVERFLOW, 0);
        sim::registerScriptVariable("simZMQ.EBADEXEC", EBADEXEC, 0);
        sim::registerScriptVariable("simZMQ.EBADARCH", EBADARCH, 0);
        sim::registerScriptVariable("simZMQ.ESHLIBVERS", ESHLIBVERS, 0);
        sim::registerScriptVariable("simZMQ.EBADMACHO", EBADMACHO, 0);
        sim::registerScriptVariable("simZMQ.ECANCELED", ECANCELED, 0);
        sim::registerScriptVariable("simZMQ.EIDRM", EIDRM, 0);
        sim::registerScriptVariable("simZMQ.ENOMSG", ENOMSG, 0);
        sim::registerScriptVariable("simZMQ.EILSEQ", EILSEQ, 0);
        sim::registerScriptVariable("simZMQ.ENOATTR", ENOATTR, 0);
        sim::registerScriptVariable("simZMQ.EBADMSG", EBADMSG, 0);
        sim::registerScriptVariable("simZMQ.EMULTIHOP", EMULTIHOP, 0);
        sim::registerScriptVariable("simZMQ.ENODATA", ENODATA, 0);
        sim::registerScriptVariable("simZMQ.ENOLINK", ENOLINK, 0);
        sim::registerScriptVariable("simZMQ.ENOSR", ENOSR, 0);
        sim::registerScriptVariable("simZMQ.ENOSTR", ENOSTR, 0);
        sim::registerScriptVariable("simZMQ.EPROTO", EPROTO, 0);
        sim::registerScriptVariable("simZMQ.ETIME", ETIME, 0);
        sim::registerScriptVariable("simZMQ.ENOPOLICY", ENOPOLICY, 0);
        sim::registerScriptVariable("simZMQ.ENOTRECOVERABLE", ENOTRECOVERABLE, 0);
        sim::registerScriptVariable("simZMQ.EOWNERDEAD", EOWNERDEAD, 0);
        sim::registerScriptVariable("simZMQ.EQFULL", EQFULL, 0);
        sim::registerScriptVariable("simZMQ.ELAST", ELAST, 0);
        sim::registerScriptVariable("simZMQ.EFSM", EFSM, 0);
        sim::registerScriptVariable("simZMQ.ENOCOMPATPROTO", ENOCOMPATPROTO, 0);
        sim::registerScriptVariable("simZMQ.ETERM", ETERM, 0);
        sim::registerScriptVariable("simZMQ.EMTHREAD", EMTHREAD, 0);
        sim::registerScriptVariable("simZMQ.IO_THREADS", ZMQ_IO_THREADS, 0);
        sim::registerScriptVariable("simZMQ.MAX_SOCKETS", ZMQ_MAX_SOCKETS, 0);
        sim::registerScriptVariable("simZMQ.SOCKET_LIMIT", ZMQ_SOCKET_LIMIT, 0);
        sim::registerScriptVariable("simZMQ.THREAD_PRIORITY", ZMQ_THREAD_PRIORITY, 0);
        sim::registerScriptVariable("simZMQ.THREAD_SCHED_POLICY", ZMQ_THREAD_SCHED_POLICY, 0);
        sim::registerScriptVariable("simZMQ.MAX_MSGSZ", ZMQ_MAX_MSGSZ, 0);
        sim::registerScriptVariable("simZMQ.MSG_T_SIZE", ZMQ_MSG_T_SIZE, 0);
        sim::registerScriptVariable("simZMQ.THREAD_AFFINITY_CPU_ADD", ZMQ_THREAD_AFFINITY_CPU_ADD, 0);
        sim::registerScriptVariable("simZMQ.THREAD_AFFINITY_CPU_REMOVE", ZMQ_THREAD_AFFINITY_CPU_REMOVE, 0);
        sim::registerScriptVariable("simZMQ.THREAD_NAME_PREFIX", ZMQ_THREAD_NAME_PREFIX, 0);
        sim::registerScriptVariable("simZMQ.IO_THREADS_DFLT", ZMQ_IO_THREADS_DFLT, 0);
        sim::registerScriptVariable("simZMQ.MAX_SOCKETS_DFLT", ZMQ_MAX_SOCKETS_DFLT, 0);
        sim::registerScriptVariable("simZMQ.THREAD_PRIORITY_DFLT", ZMQ_THREAD_PRIORITY_DFLT, 0);
        sim::registerScriptVariable("simZMQ.THREAD_SCHED_POLICY_DFLT", ZMQ_THREAD_SCHED_POLICY_DFLT, 0);
        sim::registerScriptVariable("simZMQ.PAIR", ZMQ_PAIR, 0);
        sim::registerScriptVariable("simZMQ.PUB", ZMQ_PUB, 0);
        sim::registerScriptVariable("simZMQ.SUB", ZMQ_SUB, 0);
        sim::registerScriptVariable("simZMQ.REQ", ZMQ_REQ, 0);
        sim::registerScriptVariable("simZMQ.REP", ZMQ_REP, 0);
        sim::registerScriptVariable("simZMQ.DEALER", ZMQ_DEALER, 0);
        sim::registerScriptVariable("simZMQ.ROUTER", ZMQ_ROUTER, 0);
        sim::registerScriptVariable("simZMQ.PULL", ZMQ_PULL, 0);
        sim::registerScriptVariable("simZMQ.PUSH", ZMQ_PUSH, 0);
        sim::registerScriptVariable("simZMQ.XPUB", ZMQ_XPUB, 0);
        sim::registerScriptVariable("simZMQ.XSUB", ZMQ_XSUB, 0);
        sim::registerScriptVariable("simZMQ.STREAM", ZMQ_STREAM, 0);
        sim::registerScriptVariable("simZMQ.AFFINITY", ZMQ_AFFINITY, 0);
        sim::registerScriptVariable("simZMQ.ROUTING_ID", ZMQ_ROUTING_ID, 0);
        sim::registerScriptVariable("simZMQ.SUBSCRIBE", ZMQ_SUBSCRIBE, 0);
        sim::registerScriptVariable("simZMQ.UNSUBSCRIBE", ZMQ_UNSUBSCRIBE, 0);
        sim::registerScriptVariable("simZMQ.RATE", ZMQ_RATE, 0);
        sim::registerScriptVariable("simZMQ.RECOVERY_IVL", ZMQ_RECOVERY_IVL, 0);
        sim::registerScriptVariable("simZMQ.SNDBUF", ZMQ_SNDBUF, 0);
        sim::registerScriptVariable("simZMQ.RCVBUF", ZMQ_RCVBUF, 0);
        sim::registerScriptVariable("simZMQ.RCVMORE", ZMQ_RCVMORE, 0);
        sim::registerScriptVariable("simZMQ.FD", ZMQ_FD, 0);
        sim::registerScriptVariable("simZMQ.EVENTS", ZMQ_EVENTS, 0);
        sim::registerScriptVariable("simZMQ.TYPE", ZMQ_TYPE, 0);
        sim::registerScriptVariable("simZMQ.LINGER", ZMQ_LINGER, 0);
        sim::registerScriptVariable("simZMQ.RECONNECT_IVL", ZMQ_RECONNECT_IVL, 0);
        sim::registerScriptVariable("simZMQ.BACKLOG", ZMQ_BACKLOG, 0);
        sim::registerScriptVariable("simZMQ.RECONNECT_IVL_MAX", ZMQ_RECONNECT_IVL_MAX, 0);
        sim::registerScriptVariable("simZMQ.MAXMSGSIZE", ZMQ_MAXMSGSIZE, 0);
        sim::registerScriptVariable("simZMQ.SNDHWM", ZMQ_SNDHWM, 0);
        sim::registerScriptVariable("simZMQ.RCVHWM", ZMQ_RCVHWM, 0);
        sim::registerScriptVariable("simZMQ.MULTICAST_HOPS", ZMQ_MULTICAST_HOPS, 0);
        sim::registerScriptVariable("simZMQ.RCVTIMEO", ZMQ_RCVTIMEO, 0);
        sim::registerScriptVariable("simZMQ.SNDTIMEO", ZMQ_SNDTIMEO, 0);
        sim::registerScriptVariable("simZMQ.LAST_ENDPOINT", ZMQ_LAST_ENDPOINT, 0);
        sim::registerScriptVariable("simZMQ.ROUTER_MANDATORY", ZMQ_ROUTER_MANDATORY, 0);
        sim::registerScriptVariable("simZMQ.TCP_KEEPALIVE", ZMQ_TCP_KEEPALIVE, 0);
        sim::registerScriptVariable("simZMQ.TCP_KEEPALIVE_CNT", ZMQ_TCP_KEEPALIVE_CNT, 0);
        sim::registerScriptVariable("simZMQ.TCP_KEEPALIVE_IDLE", ZMQ_TCP_KEEPALIVE_IDLE, 0);
        sim::registerScriptVariable("simZMQ.TCP_KEEPALIVE_INTVL", ZMQ_TCP_KEEPALIVE_INTVL, 0);
        sim::registerScriptVariable("simZMQ.IMMEDIATE", ZMQ_IMMEDIATE, 0);
        sim::registerScriptVariable("simZMQ.XPUB_VERBOSE", ZMQ_XPUB_VERBOSE, 0);
        sim::registerScriptVariable("simZMQ.ROUTER_RAW", ZMQ_ROUTER_RAW, 0);
        sim::registerScriptVariable("simZMQ.IPV6", ZMQ_IPV6, 0);
        sim::registerScriptVariable("simZMQ.MECHANISM", ZMQ_MECHANISM, 0);
        sim::registerScriptVariable("simZMQ.PLAIN_SERVER", ZMQ_PLAIN_SERVER, 0);
        sim::registerScriptVariable("simZMQ.PLAIN_USERNAME", ZMQ_PLAIN_USERNAME, 0);
        sim::registerScriptVariable("simZMQ.PLAIN_PASSWORD", ZMQ_PLAIN_PASSWORD, 0);
        sim::registerScriptVariable("simZMQ.CURVE_SERVER", ZMQ_CURVE_SERVER, 0);
        sim::registerScriptVariable("simZMQ.CURVE_PUBLICKEY", ZMQ_CURVE_PUBLICKEY, 0);
        sim::registerScriptVariable("simZMQ.CURVE_SECRETKEY", ZMQ_CURVE_SECRETKEY, 0);
        sim::registerScriptVariable("simZMQ.CURVE_SERVERKEY", ZMQ_CURVE_SERVERKEY, 0);
        sim::registerScriptVariable("simZMQ.PROBE_ROUTER", ZMQ_PROBE_ROUTER, 0);
        sim::registerScriptVariable("simZMQ.REQ_CORRELATE", ZMQ_REQ_CORRELATE, 0);
        sim::registerScriptVariable("simZMQ.REQ_RELAXED", ZMQ_REQ_RELAXED, 0);
        sim::registerScriptVariable("simZMQ.CONFLATE", ZMQ_CONFLATE, 0);
        sim::registerScriptVariable("simZMQ.ZAP_DOMAIN", ZMQ_ZAP_DOMAIN, 0);
        sim::registerScriptVariable("simZMQ.ROUTER_HANDOVER", ZMQ_ROUTER_HANDOVER, 0);
        sim::registerScriptVariable("simZMQ.TOS", ZMQ_TOS, 0);
        sim::registerScriptVariable("simZMQ.CONNECT_ROUTING_ID", ZMQ_CONNECT_ROUTING_ID, 0);
        sim::registerScriptVariable("simZMQ.GSSAPI_SERVER", ZMQ_GSSAPI_SERVER, 0);
        sim::registerScriptVariable("simZMQ.GSSAPI_PRINCIPAL", ZMQ_GSSAPI_PRINCIPAL, 0);
        sim::registerScriptVariable("simZMQ.GSSAPI_SERVICE_PRINCIPAL", ZMQ_GSSAPI_SERVICE_PRINCIPAL, 0);
        sim::registerScriptVariable("simZMQ.GSSAPI_PLAINTEXT", ZMQ_GSSAPI_PLAINTEXT, 0);
        sim::registerScriptVariable("simZMQ.HANDSHAKE_IVL", ZMQ_HANDSHAKE_IVL, 0);
        sim::registerScriptVariable("simZMQ.SOCKS_PROXY", ZMQ_SOCKS_PROXY, 0);
        sim::registerScriptVariable("simZMQ.XPUB_NODROP", ZMQ_XPUB_NODROP, 0);
        sim::registerScriptVariable("simZMQ.BLOCKY", ZMQ_BLOCKY, 0);
        sim::registerScriptVariable("simZMQ.XPUB_MANUAL", ZMQ_XPUB_MANUAL, 0);
        sim::registerScriptVariable("simZMQ.XPUB_WELCOME_MSG", ZMQ_XPUB_WELCOME_MSG, 0);
        sim::registerScriptVariable("simZMQ.STREAM_NOTIFY", ZMQ_STREAM_NOTIFY, 0);
        sim::registerScriptVariable("simZMQ.INVERT_MATCHING", ZMQ_INVERT_MATCHING, 0);
        sim::registerScriptVariable("simZMQ.HEARTBEAT_IVL", ZMQ_HEARTBEAT_IVL, 0);
        sim::registerScriptVariable("simZMQ.HEARTBEAT_TTL", ZMQ_HEARTBEAT_TTL, 0);
        sim::registerScriptVariable("simZMQ.HEARTBEAT_TIMEOUT", ZMQ_HEARTBEAT_TIMEOUT, 0);
        sim::registerScriptVariable("simZMQ.XPUB_VERBOSER", ZMQ_XPUB_VERBOSER, 0);
        sim::registerScriptVariable("simZMQ.CONNECT_TIMEOUT", ZMQ_CONNECT_TIMEOUT, 0);
        sim::registerScriptVariable("simZMQ.TCP_MAXRT", ZMQ_TCP_MAXRT, 0);
        sim::registerScriptVariable("simZMQ.THREAD_SAFE", ZMQ_THREAD_SAFE, 0);
        sim::registerScriptVariable("simZMQ.MULTICAST_MAXTPDU", ZMQ_MULTICAST_MAXTPDU, 0);
        sim::registerScriptVariable("simZMQ.VMCI_BUFFER_SIZE", ZMQ_VMCI_BUFFER_SIZE, 0);
        sim::registerScriptVariable("simZMQ.VMCI_BUFFER_MIN_SIZE", ZMQ_VMCI_BUFFER_MIN_SIZE, 0);
        sim::registerScriptVariable("simZMQ.VMCI_BUFFER_MAX_SIZE", ZMQ_VMCI_BUFFER_MAX_SIZE, 0);
        sim::registerScriptVariable("simZMQ.VMCI_CONNECT_TIMEOUT", ZMQ_VMCI_CONNECT_TIMEOUT, 0);
        sim::registerScriptVariable("simZMQ.USE_FD", ZMQ_USE_FD, 0);
        sim::registerScriptVariable("simZMQ.GSSAPI_PRINCIPAL_NAMETYPE", ZMQ_GSSAPI_PRINCIPAL_NAMETYPE, 0);
        sim::registerScriptVariable("simZMQ.GSSAPI_SERVICE_PRINCIPAL_NAMETYPE", ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE, 0);
        sim::registerScriptVariable("simZMQ.BINDTODEVICE", ZMQ_BINDTODEVICE, 0);
        sim::registerScriptVariable("simZMQ.MORE", ZMQ_MORE, 0);
        sim::registerScriptVariable("simZMQ.SHARED", ZMQ_SHARED, 0);
        sim::registerScriptVariable("simZMQ.DONTWAIT", ZMQ_DONTWAIT, 0);
        sim::registerScriptVariable("simZMQ.SNDMORE", ZMQ_SNDMORE, 0);
        sim::registerScriptVariable("simZMQ.NULL", ZMQ_NULL, 0);
        sim::registerScriptVariable("simZMQ.PLAIN", ZMQ_PLAIN, 0);
        sim::registerScriptVariable("simZMQ.CURVE", ZMQ_CURVE, 0);
        sim::registerScriptVariable("simZMQ.GSSAPI", ZMQ_GSSAPI, 0);
        sim::registerScriptVariable("simZMQ.GROUP_MAX_LENGTH", ZMQ_GROUP_MAX_LENGTH, 0);
        sim::registerScriptVariable("simZMQ.EVENT_CONNECTED", ZMQ_EVENT_CONNECTED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_CONNECT_DELAYED", ZMQ_EVENT_CONNECT_DELAYED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_CONNECT_RETRIED", ZMQ_EVENT_CONNECT_RETRIED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_LISTENING", ZMQ_EVENT_LISTENING, 0);
        sim::registerScriptVariable("simZMQ.EVENT_BIND_FAILED", ZMQ_EVENT_BIND_FAILED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_ACCEPTED", ZMQ_EVENT_ACCEPTED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_ACCEPT_FAILED", ZMQ_EVENT_ACCEPT_FAILED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_CLOSED", ZMQ_EVENT_CLOSED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_CLOSE_FAILED", ZMQ_EVENT_CLOSE_FAILED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_DISCONNECTED", ZMQ_EVENT_DISCONNECTED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_MONITOR_STOPPED", ZMQ_EVENT_MONITOR_STOPPED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_ALL", ZMQ_EVENT_ALL, 0);
        sim::registerScriptVariable("simZMQ.EVENT_HANDSHAKE_FAILED_NO_DETAIL", ZMQ_EVENT_HANDSHAKE_FAILED_NO_DETAIL, 0);
        sim::registerScriptVariable("simZMQ.EVENT_HANDSHAKE_SUCCEEDED", ZMQ_EVENT_HANDSHAKE_SUCCEEDED, 0);
        sim::registerScriptVariable("simZMQ.EVENT_HANDSHAKE_FAILED_PROTOCOL", ZMQ_EVENT_HANDSHAKE_FAILED_PROTOCOL, 0);
        sim::registerScriptVariable("simZMQ.EVENT_HANDSHAKE_FAILED_AUTH", ZMQ_EVENT_HANDSHAKE_FAILED_AUTH, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_UNSPECIFIED", ZMQ_PROTOCOL_ERROR_ZMTP_UNSPECIFIED, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_UNEXPECTED_COMMAND", ZMQ_PROTOCOL_ERROR_ZMTP_UNEXPECTED_COMMAND, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_INVALID_SEQUENCE", ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_SEQUENCE, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_KEY_EXCHANGE", ZMQ_PROTOCOL_ERROR_ZMTP_KEY_EXCHANGE, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_UNSPECIFIED", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_UNSPECIFIED, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_MESSAGE", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_MESSAGE, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_HELLO", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_HELLO, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_INITIATE", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_INITIATE, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_ERROR", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_ERROR, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_READY", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_READY, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_WELCOME", ZMQ_PROTOCOL_ERROR_ZMTP_MALFORMED_COMMAND_WELCOME, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_INVALID_METADATA", ZMQ_PROTOCOL_ERROR_ZMTP_INVALID_METADATA, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_CRYPTOGRAPHIC", ZMQ_PROTOCOL_ERROR_ZMTP_CRYPTOGRAPHIC, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZMTP_MECHANISM_MISMATCH", ZMQ_PROTOCOL_ERROR_ZMTP_MECHANISM_MISMATCH, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZAP_UNSPECIFIED", ZMQ_PROTOCOL_ERROR_ZAP_UNSPECIFIED, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZAP_MALFORMED_REPLY", ZMQ_PROTOCOL_ERROR_ZAP_MALFORMED_REPLY, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZAP_BAD_REQUEST_ID", ZMQ_PROTOCOL_ERROR_ZAP_BAD_REQUEST_ID, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZAP_BAD_VERSION", ZMQ_PROTOCOL_ERROR_ZAP_BAD_VERSION, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZAP_INVALID_STATUS_CODE", ZMQ_PROTOCOL_ERROR_ZAP_INVALID_STATUS_CODE, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_ZAP_INVALID_METADATA", ZMQ_PROTOCOL_ERROR_ZAP_INVALID_METADATA, 0);
        sim::registerScriptVariable("simZMQ.PROTOCOL_ERROR_WS_UNSPECIFIED", ZMQ_PROTOCOL_ERROR_WS_UNSPECIFIED, 0);
        sim::registerScriptVariable("simZMQ.POLLIN", ZMQ_POLLIN, 0);
        sim::registerScriptVariable("simZMQ.POLLOUT", ZMQ_POLLOUT, 0);
        sim::registerScriptVariable("simZMQ.POLLERR", ZMQ_POLLERR, 0);
        sim::registerScriptVariable("simZMQ.POLLPRI", ZMQ_POLLPRI, 0);
        sim::registerScriptVariable("simZMQ.POLLITEMS_DFLT", ZMQ_POLLITEMS_DFLT, 0);
        sim::registerScriptVariable("simZMQ.HAS_CAPABILITIES", ZMQ_HAS_CAPABILITIES, 0);
        sim::registerScriptVariable("simZMQ.STREAMER", ZMQ_STREAMER, 0);
        sim::registerScriptVariable("simZMQ.FORWARDER", ZMQ_FORWARDER, 0);
        sim::registerScriptVariable("simZMQ.QUEUE", ZMQ_QUEUE, 0);
#ifdef ZMQ_BUILD_DRAFT_API
        sim::registerScriptVariable("simZMQ.SERVER", ZMQ_SERVER, 0);
        sim::registerScriptVariable("simZMQ.CLIENT", ZMQ_CLIENT, 0);
        sim::registerScriptVariable("simZMQ.RADIO", ZMQ_RADIO, 0);
        sim::registerScriptVariable("simZMQ.DISH", ZMQ_DISH, 0);
        sim::registerScriptVariable("simZMQ.GATHER", ZMQ_GATHER, 0);
        sim::registerScriptVariable("simZMQ.SCATTER", ZMQ_SCATTER, 0);
        sim::registerScriptVariable("simZMQ.DGRAM", ZMQ_DGRAM, 0);
        sim::registerScriptVariable("simZMQ.PEER", ZMQ_PEER, 0);
        sim::registerScriptVariable("simZMQ.CHANNEL", ZMQ_CHANNEL, 0);
        sim::registerScriptVariable("simZMQ.ZAP_ENFORCE_DOMAIN", ZMQ_ZAP_ENFORCE_DOMAIN, 0);
        sim::registerScriptVariable("simZMQ.LOOPBACK_FASTPATH", ZMQ_LOOPBACK_FASTPATH, 0);
        sim::registerScriptVariable("simZMQ.METADATA", ZMQ_METADATA, 0);
        sim::registerScriptVariable("simZMQ.MULTICAST_LOOP", ZMQ_MULTICAST_LOOP, 0);
        sim::registerScriptVariable("simZMQ.ROUTER_NOTIFY", ZMQ_ROUTER_NOTIFY, 0);
        sim::registerScriptVariable("simZMQ.XPUB_MANUAL_LAST_VALUE", ZMQ_XPUB_MANUAL_LAST_VALUE, 0);
        sim::registerScriptVariable("simZMQ.SOCKS_USERNAME", ZMQ_SOCKS_USERNAME, 0);
        sim::registerScriptVariable("simZMQ.SOCKS_PASSWORD", ZMQ_SOCKS_PASSWORD, 0);
        sim::registerScriptVariable("simZMQ.IN_BATCH_SIZE", ZMQ_IN_BATCH_SIZE, 0);
        sim::registerScriptVariable("simZMQ.OUT_BATCH_SIZE", ZMQ_OUT_BATCH_SIZE, 0);
        sim::registerScriptVariable("simZMQ.WSS_KEY_PEM", ZMQ_WSS_KEY_PEM, 0);
        sim::registerScriptVariable("simZMQ.WSS_CERT_PEM", ZMQ_WSS_CERT_PEM, 0);
        sim::registerScriptVariable("simZMQ.WSS_TRUST_PEM", ZMQ_WSS_TRUST_PEM, 0);
        sim::registerScriptVariable("simZMQ.WSS_HOSTNAME", ZMQ_WSS_HOSTNAME, 0);
        sim::registerScriptVariable("simZMQ.WSS_TRUST_SYSTEM", ZMQ_WSS_TRUST_SYSTEM, 0);
        sim::registerScriptVariable("simZMQ.ONLY_FIRST_SUBSCRIBE", ZMQ_ONLY_FIRST_SUBSCRIBE, 0);
        sim::registerScriptVariable("simZMQ.RECONNECT_STOP", ZMQ_RECONNECT_STOP, 0);
        sim::registerScriptVariable("simZMQ.HELLO_MSG", ZMQ_HELLO_MSG, 0);
        sim::registerScriptVariable("simZMQ.DISCONNECT_MSG", ZMQ_DISCONNECT_MSG, 0);
        sim::registerScriptVariable("simZMQ.RECONNECT_STOP_CONN_REFUSED", ZMQ_RECONNECT_STOP_CONN_REFUSED, 0);
        sim::registerScriptVariable("simZMQ.RECONNECT_STOP_HANDSHAKE_FAILED", ZMQ_RECONNECT_STOP_HANDSHAKE_FAILED, 0);
        sim::registerScriptVariable("simZMQ.ZERO_COPY_RECV", ZMQ_ZERO_COPY_RECV, 0);
        sim::registerScriptVariable("simZMQ.NOTIFY_CONNECT", ZMQ_NOTIFY_CONNECT, 0);
        sim::registerScriptVariable("simZMQ.NOTIFY_DISCONNECT", ZMQ_NOTIFY_DISCONNECT, 0);
        sim::registerScriptVariable("simZMQ.EVENT_PIPES_STATS", ZMQ_EVENT_PIPES_STATS, 0);
        sim::registerScriptVariable("simZMQ.CURRENT_EVENT_VERSION", ZMQ_CURRENT_EVENT_VERSION, 0);
        sim::registerScriptVariable("simZMQ.CURRENT_EVENT_VERSION_DRAFT", ZMQ_CURRENT_EVENT_VERSION_DRAFT, 0);
        sim::registerScriptVariable("simZMQ.EVENT_ALL_V1", ZMQ_EVENT_ALL_V1, 0);
        sim::registerScriptVariable("simZMQ.EVENT_ALL_V2", ZMQ_EVENT_ALL_V2, 0);
#endif // ZMQ_BUILD_DRAFT_API

        setExtVersion("ZeroMQ Plugin");
        setBuildDate(BUILD_DATE);
    }

    void onEnd()
    {
        if(global_context)
        {
            if(zmq_ctx_shutdown(global_context) == -1)
                switch(zmq_errno())
                {
                case EFAULT:
                    sim::addLog(sim_verbosity_errors, "zmq_ctx_shutdown: EFAULT");
                    break;
                default:
                    sim::addLog(sim_verbosity_errors, "zmq_ctx_shutdown: unknown error");
                    break;
                }
            if(zmq_ctx_destroy(global_context) == -1)
                switch(zmq_errno())
                {
                case EFAULT:
                    sim::addLog(sim_verbosity_errors, "zmq_ctx_destroy: EFAULT");
                    break;
                case EINTR:
                    sim::addLog(sim_verbosity_errors, "zmq_ctx_destroy: EINTR");
                    break;
                default:
                    sim::addLog(sim_verbosity_errors, "zmq_ctx_destroy: unknown error");
                    break;
                }
            global_context = nullptr;
        }
    }

    void bind(bind_in *in, bind_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_bind(socket, in->endpoint.c_str());
    }

    void close(close_in *in, close_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_close(socket);
    }

    void connect(connect_in *in, connect_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_connect(socket, in->endpoint.c_str());
    }

    void ctx_get(ctx_get_in *in, ctx_get_out *out)
    {
        void *context = Handle<zmq_context_t>::obj(in->context);
        out->result = zmq_ctx_get(context, in->option_name);
    }

    void ctx_new(ctx_new_in *in, ctx_new_out *out)
    {
        void *context = zmq_ctx_new();
        out->context = Handle<zmq_context_t>::str(context);
    }

    void ctx_set(ctx_set_in *in, ctx_set_out *out)
    {
        void *context = Handle<zmq_context_t>::obj(in->context);
        out->result = zmq_ctx_set(context, in->option_name, in->option_value);
    }

    void ctx_shutdown(ctx_shutdown_in *in, ctx_shutdown_out *out)
    {
        void *context = Handle<zmq_context_t>::obj(in->context);
        if(global_context && context == global_context)
            throw std::runtime_error("singleton context must not be shutdown");
        out->result = zmq_ctx_shutdown(context);
    }

    void ctx_term(ctx_term_in *in, ctx_term_out *out)
    {
        void *context = Handle<zmq_context_t>::obj(in->context);
        if(global_context && context == global_context)
            throw std::runtime_error("singleton context must not be terminated");
        out->result = zmq_ctx_term(context);
    }

    void ctx_singleton(ctx_singleton_in *in, ctx_singleton_out *out)
    {
        if(!global_context)
            global_context = zmq_ctx_new();
        out->context = Handle<zmq_context_t>::str(global_context);
    }

    void disconnect(disconnect_in *in, disconnect_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_disconnect(socket, in->endpoint.c_str());
    }

    void errnum(errnum_in *in, errnum_out *out)
    {
        out->result = zmq_errno();
    }

    void getsockopt(getsockopt_in *in, getsockopt_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        std::string buf(in->option_len, 0);
        size_t len = in->option_len;
        out->result = zmq_getsockopt(socket, in->option_name, reinterpret_cast<void*>(buf.data()), &len);
    }

    void has(has_in *in, has_out *out)
    {
        out->result = zmq_has(in->capability.c_str());
    }

    void msg_close(msg_close_in *in, msg_close_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        out->result = zmq_msg_close(msg);
    }

    void msg_copy(msg_copy_in *in, msg_copy_out *out)
    {
        zmq_msg_t *dest = Handle<zmq_msg_t>::obj(in->dest);
        zmq_msg_t *src = Handle<zmq_msg_t>::obj(in->src);
        out->result = zmq_msg_copy(dest, src);
    }

    void msg_data(msg_data_in *in, msg_data_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        void *data = zmq_msg_data(msg);
        if(data)
            out->data = std::string(reinterpret_cast<const char*>(data), zmq_msg_size(msg));
        out->result = data ? 0 : -1;
    }

    void msg_destroy(msg_destroy_in *in, msg_destroy_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        delete msg;
    }

    void msg_gets(msg_gets_in *in, msg_gets_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        const char *s = zmq_msg_gets(msg, in->property.c_str());
        out->result = s ? 0 : -1;
        if(s) out->value = s;
    }

    void msg_get(msg_get_in *in, msg_get_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        out->result = zmq_msg_get(msg, in->property);
    }

    void msg_init_size(msg_init_size_in *in, msg_init_size_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        out->result = zmq_msg_init_size(msg, in->size);
    }

    void msg_init(msg_init_in *in, msg_init_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        out->result = zmq_msg_init(msg);
    }

    void msg_more(msg_more_in *in, msg_more_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        out->result = zmq_msg_more(msg);
    }

    void msg_move(msg_move_in *in, msg_move_out *out)
    {
        zmq_msg_t *dest = Handle<zmq_msg_t>::obj(in->dest);
        zmq_msg_t *src = Handle<zmq_msg_t>::obj(in->src);
        out->result = zmq_msg_move(dest, src);
    }

    void msg_new(msg_new_in *in, msg_new_out *out)
    {
        zmq_msg_t *msg = new zmq_msg_t;
        out->msg = Handle<zmq_msg_t>::str(msg);
    }

    void msg_recv(msg_recv_in *in, msg_recv_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_msg_recv(msg, socket, in->flags);
    }

    void msg_send(msg_send_in *in, msg_send_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_msg_send(msg, socket, in->flags);
    }

    void msg_set(msg_set_in *in, msg_set_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        out->result = zmq_msg_set(msg, in->property, in->value);
    }

    void msg_size(msg_size_in *in, msg_size_out *out)
    {
        zmq_msg_t *msg = Handle<zmq_msg_t>::obj(in->msg);
        out->result = zmq_msg_size(msg);
    }

    void poll(poll_in *in, poll_out *out)
    {
        if(in->sockets.size() != in->events.size())
            throw std::runtime_error("'sockets' and 'events' must have the same length");
        int n = in->sockets.size();
        zmq_pollitem_t *items = new zmq_pollitem_t[n];
        for(size_t i = 0; i < n; i++)
        {
            items[i].socket = Handle<zmq_socket_t>::obj(in->sockets[i]);
            items[i].events = in->events[i];
        }
        out->result = zmq_poll(items, n, in->timeout);
        for(size_t i = 0; i < n; i++)
            out->revents.push_back(items[i].revents);
        delete[] items;
    }

    void proxy_steerable(proxy_steerable_in *in, proxy_steerable_out *out)
    {
        void *frontend = Handle<zmq_socket_t>::obj(in->frontend);
        void *backend = Handle<zmq_socket_t>::obj(in->backend);
        void *capture = Handle<zmq_socket_t>::obj(in->capture);
        void *control = Handle<zmq_socket_t>::obj(in->control);
        out->result = zmq_proxy_steerable(frontend, backend, capture, control);
    }

    void proxy(proxy_in *in, proxy_out *out)
    {
        void *frontend = Handle<zmq_socket_t>::obj(in->frontend);
        void *backend = Handle<zmq_socket_t>::obj(in->backend);
        void *capture = Handle<zmq_socket_t>::obj(in->capture);
        out->result = zmq_proxy(frontend, backend, capture);
    }

    void recv(recv_in *in, recv_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        std::string buf(in->max_buf_size, 0);
        out->result = zmq_recv(socket, buf.data(), in->max_buf_size, in->flags);
        out->data = buf.substr(0, out->result);
    }

    void send(send_in *in, send_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_send(socket, in->data.data(), in->data.size(), in->flags);
    }

    void setsockopt(setsockopt_in *in, setsockopt_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_setsockopt(socket, in->option_name, in->option_value.c_str(), in->option_value.size());
    }

    void socket_monitor(socket_monitor_in *in, socket_monitor_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_socket_monitor(socket, in->endpoint.c_str(), in->events);
    }

    void socket(socket_in *in, socket_out *out)
    {
        void *context = Handle<zmq_context_t>::obj(in->context);
        void *socket = zmq_socket(context, in->type);
        out->socket = Handle<zmq_socket_t>::str(socket);
    }

    void strerror(strerror_in *in, strerror_out *out)
    {
        out->message = zmq_strerror(in->errnum);
    }

    void unbind(unbind_in *in, unbind_out *out)
    {
        void *socket = Handle<zmq_socket_t>::obj(in->socket);
        out->result = zmq_unbind(socket, in->endpoint.c_str());
    }

    void version(version_in *in, version_out *out)
    {
        zmq_version(&out->major, &out->minor, &out->patch);
    }

private:
    void *global_context = nullptr;
};

SIM_PLUGIN(PLUGIN_NAME, PLUGIN_VERSION, Plugin)
#include "stubsPlusPlus.cpp"
