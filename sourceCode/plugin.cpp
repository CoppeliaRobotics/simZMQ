#include <string>
#include <vector>
#include <set>
#include <map>
#include <stdexcept>
#include <simPlusPlus/Plugin.h>
#include <simPlusPlus/Handles.h>
#include "config.h"
#include "plugin.h"
#include "stubs.h"
#include "zmq.h"

typedef void zmq_context_t;
typedef void zmq_socket_t;

class Plugin : public sim::Plugin
{
public:
    void onInit()
    {
        if(!registerScriptStuff())
            throw std::runtime_error("failed to register script stuff");

        sim::registerScriptVariable("EADDRINUSE", EADDRINUSE, 0);
        sim::registerScriptVariable("EADDRNOTAVAIL", EADDRNOTAVAIL, 0);
        sim::registerScriptVariable("EAGAIN", EAGAIN, 0);
        sim::registerScriptVariable("EFAULT", EFAULT, 0);
        sim::registerScriptVariable("EFSM", EFSM, 0);
        sim::registerScriptVariable("EHOSTUNREACH", EHOSTUNREACH, 0);
        sim::registerScriptVariable("EINTR", EINTR, 0);
        sim::registerScriptVariable("EINVAL", EINVAL, 0);
        sim::registerScriptVariable("EMFILE", EMFILE, 0);
        sim::registerScriptVariable("EMTHREAD", EMTHREAD, 0);
        sim::registerScriptVariable("ENOCOMPATPROTO", ENOCOMPATPROTO, 0);
        sim::registerScriptVariable("ENODEV", ENODEV, 0);
        sim::registerScriptVariable("ENOENT", ENOENT, 0);
        sim::registerScriptVariable("ENOMEM", ENOMEM, 0);
        sim::registerScriptVariable("ENOTSOCK", ENOTSOCK, 0);
        sim::registerScriptVariable("ENOTSUP", ENOTSUP, 0);
        sim::registerScriptVariable("EPROTONOSUPPORT", EPROTONOSUPPORT, 0);
        sim::registerScriptVariable("ETERM", ETERM, 0);

#include "zmq_constants.cpp"

        setExtVersion("ZeroMQ Plugin");
        setBuildDate(BUILD_DATE);
    }

    void onCleanup()
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
            global_context_handle = "";
        }
    }

    void onScriptStateAboutToBeDestroyed(int scriptHandle, long long scriptUid)
    {
        for(auto msg : msgHandles.find(scriptHandle))
        {
            delete msgHandles.remove(msg);
        }
        for(auto socket : socketHandles.find(scriptHandle))
        {
            void *s = const_cast<void*>(socket);
            zmq_close(s);
            socketHandles.remove(socket);
        }
        for(auto context : contextHandles.find(scriptHandle))
        {
            void *c = const_cast<void*>(context);
            zmq_term(c);
            zmq_ctx_destroy(c);
            contextHandles.remove(context);
        }
    }

    void bind(bind_in *in, bind_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_bind(socket, in->endpoint.c_str());
    }

    void close(close_in *in, close_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_close(socket);
        socketHandles.remove(socket);
    }

    void connect(connect_in *in, connect_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_connect(socket, in->endpoint.c_str());
    }

    void ctx_get(ctx_get_in *in, ctx_get_out *out)
    {
        void *context = contextHandles.get(in->context);
        out->result = zmq_ctx_get(context, in->option_name);
    }

    void ctx_new(ctx_new_in *in, ctx_new_out *out)
    {
        void *context = zmq_ctx_new();
        out->context = contextHandles.add(context, in->_.scriptID);
    }

    void ctx_set(ctx_set_in *in, ctx_set_out *out)
    {
        void *context = contextHandles.get(in->context);
        out->result = zmq_ctx_set(context, in->option_name, in->option_value);
    }

    void ctx_shutdown(ctx_shutdown_in *in, ctx_shutdown_out *out)
    {
        void *context = contextHandles.get(in->context);
        if(global_context && context == global_context)
            throw std::runtime_error("singleton context must not be shutdown");
        out->result = zmq_ctx_shutdown(context);
    }

    void ctx_term(ctx_term_in *in, ctx_term_out *out)
    {
        void *context = contextHandles.get(in->context);
        if(global_context && context == global_context)
            throw std::runtime_error("singleton context must not be terminated");
        out->result = zmq_ctx_term(context);
        contextHandles.remove(context);
    }

    void ctx_singleton(ctx_singleton_in *in, ctx_singleton_out *out)
    {
        if(!global_context)
        {
            global_context = zmq_ctx_new();
            global_context_handle = contextHandles.add(global_context);
        }
        out->context = global_context_handle;
    }

    void disconnect(disconnect_in *in, disconnect_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_disconnect(socket, in->endpoint.c_str());
    }

    void errnum(errnum_in *in, errnum_out *out)
    {
        out->result = zmq_errno();
    }

    void getsockopt(getsockopt_in *in, getsockopt_out *out)
    {
        void *socket = socketHandles.get(in->socket);
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
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_close(msg);
    }

    void msg_copy(msg_copy_in *in, msg_copy_out *out)
    {
        zmq_msg_t *dest = msgHandles.get(in->dest);
        zmq_msg_t *src = msgHandles.get(in->src);
        out->result = zmq_msg_copy(dest, src);
    }

    void msg_data(msg_data_in *in, msg_data_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        void *data = zmq_msg_data(msg);
        if(data)
            out->data = std::string(reinterpret_cast<const char*>(data), zmq_msg_size(msg));
    }

    void msg_destroy(msg_destroy_in *in, msg_destroy_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        delete msgHandles.remove(msg);
    }

    void msg_gets(msg_gets_in *in, msg_gets_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        const char *s = zmq_msg_gets(msg, in->property.c_str());
        out->result = s ? 0 : -1;
        if(s) out->value = s;
    }

    void msg_get(msg_get_in *in, msg_get_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_get(msg, in->property);
    }

    void msg_init_size(msg_init_size_in *in, msg_init_size_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_init_size(msg, in->size);
    }

    void msg_init(msg_init_in *in, msg_init_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_init(msg);
    }

    void msg_more(msg_more_in *in, msg_more_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_more(msg);
    }

    void msg_move(msg_move_in *in, msg_move_out *out)
    {
        zmq_msg_t *dest = msgHandles.get(in->dest);
        zmq_msg_t *src = msgHandles.get(in->src);
        out->result = zmq_msg_move(dest, src);
    }

    void msg_new(msg_new_in *in, msg_new_out *out)
    {
        zmq_msg_t *msg = new zmq_msg_t;
        out->msg = msgHandles.add(msg, in->_.scriptID);
    }

    void msg_recv(msg_recv_in *in, msg_recv_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_msg_recv(msg, socket, in->flags);
    }

    void msg_send(msg_send_in *in, msg_send_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_msg_send(msg, socket, in->flags);
    }

    void msg_set(msg_set_in *in, msg_set_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_set(msg, in->property, in->value);
    }

    void msg_size(msg_size_in *in, msg_size_out *out)
    {
        zmq_msg_t *msg = msgHandles.get(in->msg);
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
            items[i].socket = socketHandles.get(in->sockets[i]);
            items[i].events = in->events[i];
        }
        out->result = zmq_poll(items, n, in->timeout);
        for(size_t i = 0; i < n; i++)
            out->revents.push_back(items[i].revents);
        delete[] items;
    }

    void proxy_steerable(proxy_steerable_in *in, proxy_steerable_out *out)
    {
        void *frontend = socketHandles.get(in->frontend);
        void *backend = socketHandles.get(in->backend);
        void *capture = socketHandles.get(in->capture);
        void *control = socketHandles.get(in->control);
        out->result = zmq_proxy_steerable(frontend, backend, capture, control);
    }

    void proxy(proxy_in *in, proxy_out *out)
    {
        void *frontend = socketHandles.get(in->frontend);
        void *backend = socketHandles.get(in->backend);
        void *capture = socketHandles.get(in->capture);
        out->result = zmq_proxy(frontend, backend, capture);
    }

    void recv(recv_in *in, recv_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        if(in->max_buf_size.has_value())
        {
            int sz = in->max_buf_size.value();
            std::string buf(sz, 0);
            out->result = zmq_recv(socket, buf.data(), sz, in->flags);
            if(out->result != -1)
                out->data = buf.substr(0, out->result);
        }
        else
        {
            // buffer size not specified -> use tmp zmq_msg_t
            int rc;
            zmq_msg_t msg;
            rc = zmq_msg_init(&msg);
            if(rc != 0) throw sim::exception("zmq_msg_init: %s", zmq_strerror(errno));
            out->result = zmq_msg_recv(&msg, socket, in->flags);
            if(out->result != -1)
            {
                std::string buf(reinterpret_cast<const char*>(zmq_msg_data(&msg)), zmq_msg_size(&msg));
                out->data = buf;
            }
            rc = zmq_msg_close(&msg);
            if(rc != 0) throw sim::exception("zmq_msg_close: %s", zmq_strerror(errno));
        }
    }

    void send(send_in *in, send_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_send(socket, in->data.data(), in->data.size(), in->flags);
    }

    void setsockopt(setsockopt_in *in, setsockopt_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_setsockopt(socket, in->option_name, in->option_value.c_str(), in->option_value.size());
    }

    void socket_monitor(socket_monitor_in *in, socket_monitor_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_socket_monitor(socket, in->endpoint.c_str(), in->events);
    }

    void socket(socket_in *in, socket_out *out)
    {
        void *context = contextHandles.get(in->context);
        void *socket = zmq_socket(context, in->type);
        out->socket = socketHandles.add(socket, in->_.scriptID);
    }

    void strerror(strerror_in *in, strerror_out *out)
    {
        out->message = zmq_strerror(in->errnum);
    }

    void unbind(unbind_in *in, unbind_out *out)
    {
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_unbind(socket, in->endpoint.c_str());
    }

    void version(version_in *in, version_out *out)
    {
        zmq_version(&out->major, &out->minor, &out->patch);
    }

    void ctx_set_ext(ctx_set_ext_in *in, ctx_set_ext_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        void *context = contextHandles.get(in->context);
        out->result = zmq_ctx_set_ext(context, in->option_name, in->option_value.data(), in->option_value.size());
#endif // ZMQ_BUILD_DRAFT_API
    }

    void ctx_get_ext(ctx_get_ext_in *in, ctx_get_ext_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        char buf[256];
        size_t sz;
        void *context = contextHandles.get(in->context);
        out->result = zmq_ctx_get_ext(context, in->option_name, &buf[0], &sz);
        out->data = std::string(buf, sz);
#endif // ZMQ_BUILD_DRAFT_API
    }

    void join(join_in *in, join_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_join(socket, in->group.c_str());
#endif // ZMQ_BUILD_DRAFT_API
    }

    void leave(leave_in *in, leave_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_leave(socket, in->group.c_str());
#endif // ZMQ_BUILD_DRAFT_API
    }

    void connect_peer(connect_peer_in *in, connect_peer_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        void *socket = socketHandles.get(in->socket);
        out->result = zmq_connect_peer(socket, in->addr.c_str());
#endif // ZMQ_BUILD_DRAFT_API
    }

    void msg_set_routing_id(msg_set_routing_id_in *in, msg_set_routing_id_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_set_routing_id(msg, in->routing_id);
#endif // ZMQ_BUILD_DRAFT_API
    }

    void msg_routing_id(msg_routing_id_in *in, msg_routing_id_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->routing_id = zmq_msg_routing_id(msg);
#endif // ZMQ_BUILD_DRAFT_API
    }

    void msg_set_group(msg_set_group_in *in, msg_set_group_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        zmq_msg_t *msg = msgHandles.get(in->msg);
        out->result = zmq_msg_set_group(msg, in->group.c_str());
#endif // ZMQ_BUILD_DRAFT_API
    }

    void msg_group(msg_group_in *in, msg_group_out *out)
    {
#ifdef ZMQ_BUILD_DRAFT_API
        zmq_msg_t *msg = msgHandles.get(in->msg);
        const char *g = zmq_msg_group(msg);
        if(g)
        {
            out->result = 0;
            out->group = std::string(g);
        }
        else
        {
            out->result = -1;
        }
#endif // ZMQ_BUILD_DRAFT_API
    }

private:
    void *global_context = nullptr;
    std::string global_context_handle;
    sim::Handles<zmq_context_t*> contextHandles{"zmq.context"};
    sim::Handles<zmq_socket_t*> socketHandles{"zmq.socket"};
    sim::Handles<zmq_msg_t*> msgHandles{"zmq.msg"};
};

SIM_PLUGIN(Plugin)
#include "stubsPlusPlus.cpp"
