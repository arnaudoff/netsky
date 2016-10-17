#include <spdlog/spdlog.h>

#include "include/WebSocketServer.hpp"
#include "include/WebSocketServerActionHandler.hpp"

using namespace Sniffer::Communications;

WebSocketServer::WebSocketServer(
        const ConfigurationMgr& manager,
        std::unique_ptr<WebSocketServerActionHandler> handler)
    : Server(manager), action_handler_{std::move(handler)} {
        server_.init_asio();
        server_.set_open_handler(bind(
                    &WebSocketServerActionHandler::on_open,
                    action_handler_.get(),
                    ::_1));

        server_.set_close_handler(bind(
                    &WebSocketServerActionHandler::on_close,
                    action_handler_.get(),
                    ::_1));

        server_.set_message_handler(bind(
                    &WebSocketServerActionHandler::on_message,
                    action_handler_.get(),
                    ::_1,
                    ::_2));
}

void WebSocketServer::run(uint16_t port) {
    server_.listen(port);
    server_.start_accept();

    try {
        server_.run();
    } catch (const std::exception & e) {
        spdlog::get("console")->critical("Running the WebSocket server failed: {0}",
                e.what());
    }

}

void WebSocketServer::start(uint16_t port) {
    try {
        thread t(bind(
                    &WebSocketServerActionHandler::handle,
                    action_handler_.get(),
                    this));
        run(port);

        t.join();
    } catch (websocketpp::exception const & e) {
        spdlog::get("console")->critical("Running the WebSocket server failed: {0}",
                e.what());
    }
}

void WebSocketServer::stop() {
    server_.stop_listening();
}

void WebSocketServer::unicast(const ConnectionData& con_data, const std::string& msg) {
    for (auto it = connections_.begin(); it != connections_.end(); ++it) {
        if (it->second == con_data) {
            server_.send(it->first, msg, websocketpp::frame::opcode::text);
            break;
        }
    }
}

void WebSocketServer::broadcast(const std::string& message) {
    connection_list_t::iterator it;
    for (it = connections_.begin(); it != connections_.end(); ++it) {
        server_.send(it->first, message, websocketpp::frame::opcode::text);
    }
}

void WebSocketServer::add_connection(connection_hdl handle) {
    ConnectionData data { session_id_++ };
    connections_[handle] = data;

    // TODO: use connection::get_remote_endpoint() here
    spdlog::get("console")->info("Session established: {0}", data.get_session_id());
}

void WebSocketServer::remove_connection(connection_hdl handle) {
    auto data = get_connection_data_from_hdl(handle);

    connections_.erase(handle);

    // TODO: use connection::get_remote_endpoint() here
    spdlog::get("console")->info("Session killed: {0}", data.get_session_id());
}

ConnectionData WebSocketServer::get_connection_data_from_hdl(connection_hdl hdl) {
    auto it = connections_.find(hdl);

    if (it == connections_.end()) {
        throw std::invalid_argument("No connection data avaliable for this handle");
    }

    return it->second;
}
