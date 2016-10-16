#ifndef CONNECTION_DATA_HPP_
#define CONNECTION_DATA_HPP_

namespace Sniffer {
    namespace Communications {
        class ConnectionData {
            private:
                int session_id_;

            public:
                ConnectionData();

                ConnectionData(int session_id);

                int get_session_id() const;

                bool operator==(const ConnectionData& other) const;

                bool operator!=(const ConnectionData& other) const;
        };
    }
}

#endif
