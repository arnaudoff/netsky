#include <spdlog/spdlog.h>

#include "include/WebSocketServer.hpp"
#include "include/WebSocketServerActionHandler.hpp"

using namespace Sniffer::Core::Communications;

WebSocketServer::WebSocketServer(
        std::shared_ptr<ConfigManager> manager,
        std::unique_ptr<WebSocketServerActionHandler> handler)
    : Server{manager}, action_handler_{std::move(handler)} {
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

void WebSocketServer::broadcast(const std::string& message) {
    connection_list_t::iterator it;
    for (it = connections_.begin(); it != connections_.end(); ++it) {
        server_.send(*it, message, websocketpp::frame::opcode::text);
    }
}

void WebSocketServer::add_connection(connection_hdl handle) {
    connections_.insert(handle);
}

void WebSocketServer::remove_connection(connection_hdl handle) {
    connections_.erase(handle);
}
