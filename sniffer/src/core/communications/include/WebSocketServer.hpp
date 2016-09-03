#ifndef WEB_SOCKET_SERVER_HPP_
#define WEB_SOCKET_SERVER_HPP_

#include <set>
#include <memory>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/common/thread.hpp>

#include "Server.hpp"

namespace Sniffer {
    namespace Core {
        namespace Communications {
            using websocketpp::connection_hdl;
            using websocketpp::lib::placeholders::_1;
            using websocketpp::lib::placeholders::_2;
            using websocketpp::lib::bind;
            using websocketpp::lib::thread;

            class WebSocketServerActionHandler;

            class WebSocketServer : public Server {
                typedef websocketpp::server<websocketpp::config::asio> server_t;
                typedef std::set<
                    connection_hdl,
                    std::owner_less<connection_hdl>> connection_list_t;

                private:
                    server_t server_;
                    connection_list_t connections_;
                    std::shared_ptr<ConfigManager> config_manager_;
                    std::unique_ptr<WebSocketServerActionHandler> action_handler_;

                    void run(uint16_t port);

                public:
                    WebSocketServer(
                            std::shared_ptr<ConfigManager> manager,
                            std::unique_ptr<WebSocketServerActionHandler> handler);

                    virtual void start(uint16_t port) override;

                    virtual void stop() override;

                    virtual void broadcast(const std::string& message) override;

                    void add_connection(connection_hdl handle);

                    void remove_connection(connection_hdl handle);
            };
        }
    }
}

#endif
