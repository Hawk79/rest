
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <random>
#include <sys/time.h>

#include "cpprest/json.h"
#include "cpprest/http_listener.h"
#include "cpprest/uri.h"
#include "cpprest/asyncrt_utils.h"


using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace std;

class TestServer
{
public:
    TestServer() {}
    TestServer(utility::string_t url) 
    : m_listener(url)
{
    m_listener.support(methods::GET, std::bind(&TestServer::handle_get, this, std::placeholders::_1));
}

    pplx::task<void> open() { return m_listener.open(); }
    pplx::task<void> close() { return m_listener.close(); }

private:

    void handle_get(http_request message) {
           ucout <<  message.to_string() << endl;

           message.reply(status_codes::OK, "Hello John!");
           return;
    };

    http_listener m_listener;   
};

std::unique_ptr<TestServer> g_httpServer;

void on_initialize(const string_t& address)
{
    uri_builder uri(address);
    uri.append_path(U("hello"));

    auto addr = uri.to_uri().to_string();
    g_httpServer = std::unique_ptr<TestServer>(new TestServer(addr));
    g_httpServer->open().wait();
    
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown()
{
    g_httpServer->close().wait();
    return;
}

int main(int argc, char *argv[])
{
    utility::string_t port = U("8080");
    if(argc == 2)
    {
        port = argv[1];
    }

    utility::string_t address = U("http://0.0.0.0:");
    address.append(port);

    on_initialize(address);
    /*
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);
    */ 

    while(1) sleep(1000);

    on_shutdown();
    return 0;
}
