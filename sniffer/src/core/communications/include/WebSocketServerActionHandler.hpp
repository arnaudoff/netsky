#ifndef WEB_SOCKET_SERVER_ACTION_HANDLER_HPP_
#define WEB_SOCKET_SERVER_ACTION_HANDLER_HPP_

#include <queue>

#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/common/thread.hpp>

#include "WebSocketServer.hpp"
#include "ServerCommandInvoker.hpp"

namespace Sniffer {
    namespace Core {
        namespace Communications {
            using websocketpp::connection_hdl;
            using websocketpp::lib::mutex;
            using websocketpp::lib::lock_guard;
            using websocketpp::lib::unique_lock;
            using websocketpp::lib::condition_variable;

            typedef websocketpp::server<websocketpp::config::asio>::message_ptr
                message_ptr_t;

            enum action_type {
                SUBSCRIBE,
                UNSUBSCRIBE,
                MESSAGE
            };

            struct action {
                action(action_type type, connection_hdl handle)
                    : type{type}, handle{handle}
                {}

                action(action_type type, connection_hdl handle,
                        message_ptr_t msg)
                    : type{type}, handle{handle}, message{msg}
                {}

                action_type type;
                connection_hdl handle;
                message_ptr_t message;
            };

            class WebSocketServerActionHandler {
                private:
                    ServerCommandInvoker* command_invoker_;
                    std::queue<action> actions_;
                    mutex action_lock_;
                    mutex connection_lock_;
                    condition_variable action_cond_;

                public:
                    WebSocketServerActionHandler(ServerCommandInvoker* invoker)
                        : command_invoker_{invoker}
                    {}

                    void on_open(connection_hdl handle);

                    void on_close(connection_hdl handle);

                    void on_message(connection_hdl handle, message_ptr_t msg);

                    void handle(WebSocketServer* server);
            };
        }
    }
}

#endif
