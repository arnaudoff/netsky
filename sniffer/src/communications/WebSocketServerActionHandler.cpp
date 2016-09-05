#include <spdlog/spdlog.h>

#include "include/WebSocketServerActionHandler.hpp"

using namespace Sniffer::Communications;

void WebSocketServerActionHandler::on_open(connection_hdl handle) {
    {
        lock_guard<mutex> guard(action_lock_);
        actions_.push(action(SUBSCRIBE, handle));
    }

    action_cond_.notify_one();
}

void WebSocketServerActionHandler::on_close(connection_hdl handle) {
    {
        lock_guard<mutex> guard(action_lock_);
        actions_.push(action(UNSUBSCRIBE, handle));
    }

    action_cond_.notify_one();
}

void WebSocketServerActionHandler::on_message(connection_hdl handle,
        message_ptr_t message) {
    {
        lock_guard<mutex> guard(action_lock_);
        actions_.push(action(MESSAGE, handle, message));
    }

    action_cond_.notify_one();
}

void WebSocketServerActionHandler::handle(WebSocketServer* server) {
    while (1) {
        unique_lock<mutex> lock(action_lock_);

        while (actions_.empty()) {
            action_cond_.wait(lock);
        }

        action current_action = actions_.front();
        actions_.pop();

        lock.unlock();

        if (current_action.type == SUBSCRIBE) {
            lock_guard<mutex> guard(connection_lock_);
            server->add_connection(current_action.handle);
        } else if (current_action.type == UNSUBSCRIBE) {
            lock_guard<mutex> guard(connection_lock_);
            server->remove_connection(current_action.handle);
        } else if (current_action.type == MESSAGE) {
            lock_guard<mutex> guard(connection_lock_);
            command_invoker_->invoke(current_action.message->get_payload());
        } else {
            spdlog::get("console")->info("The WebSocket server received an action that cannot be handled.");
        }
    }
}

