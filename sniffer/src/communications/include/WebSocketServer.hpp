#ifndef WEB_SOCKET_SERVER_HPP_
#define WEB_SOCKET_SERVER_HPP_

#include <map>
#include <memory>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/common/thread.hpp>

#include "Server.hpp"

namespace Sniffer {
    namespace Communications {
        using websocketpp::connection_hdl;
        using websocketpp::lib::placeholders::_1;
        using websocketpp::lib::placeholders::_2;
        using websocketpp::lib::bind;
        using websocketpp::lib::thread;

        class WebSocketServerActionHandler;

        class WebSocketServer : public Server {
            typedef websocketpp::server<websocketpp::config::asio> server_t;
            typedef std::map<
                connection_hdl,
                ConnectionData,
                std::owner_less<connection_hdl>> connection_list_t;

            private:
                std::unique_ptr<WebSocketServerActionHandler> action_handler_;
                server_t server_;
                connection_list_t connections_;

                void run(uint16_t port);

            public:
                WebSocketServer(
                        const ConfigurationMgr& manager,
                        std::unique_ptr<WebSocketServerActionHandler> handler);

                virtual void start(uint16_t port) override;

                virtual void stop() override;

                virtual void unicast(
                        const ConnectionData& con_data,
                        const std::string& msg) override;

                virtual void broadcast(const std::string& message) override;

                void add_connection(connection_hdl handle);

                void remove_connection(connection_hdl handle);

                ConnectionData get_connection_data_from_hdl(connection_hdl hdl);

                ~WebSocketServer() override;
        };
    }
}

#endif
