#pragma once
#include <boost/asio.hpp>

using namespace boost;
using namespace std;

extern int accept_new_connection();
extern void use_buffer_str();
extern void use_buffer_array();
extern void use_const_buffer();
extern void use_stream_buffer();
extern int send_data_by_write_some();
extern int send_data_by_send();
extern int send_data_by_write();

extern int read_data_by_read_some();
extern int read_data_by_receive();
extern int read_data_by_read();

extern std::string read_data_by_until(asio::ip::tcp::socket& sock);
extern int async_write_data();