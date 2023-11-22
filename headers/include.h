#include <sys/socket.h> // basic socket definitions
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h> // for variadic function
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <regex>
#include <termios.h>
#include <stdarg.h> // for varaidic functions
#include <fstream>
#include <filesystem>
#include "../libraries/structures.h"

// standard for webpages
#define WEB_SERVER_PORT 80


#define MAX_PORT_VAL 65535 // a 16-bit value's largest number is 65536, but we also can count 0, so - 1.

#define MAX_URL 2097152 // The maximum length of a url.

// buffer length for where data is read back in
#define MAXLINE 4096

#define IP_COUNT 5

#define RETRIEVE_INFO_ERROR 1
#define FILE_NOT_EXIST_ERROR 2
#define CANNOT_OPEN_FILE 3


#ifdef __unix__

#define SYS_SLASH "/"

#else

#define SYS_SLASH "\\"

#endif


char* copy_str(char* the_string) {
    char* the_answer = (char*) malloc(sizeof(char) * 1);
    if (!the_answer) {
        fprintf(stderr, "Error allocating memory to copy string \"%s\"\n", the_string);
        exit(2);
    }
    unsigned long index;
    for (index = 0; the_string[index] != '\0'; index = index + 1) {
        the_answer[index] = the_string[index];
        the_answer = (char*) realloc(the_answer, sizeof(char) * (index + 1));
        if (!the_answer) {
            // error reallocating the_answer
            fprintf(stderr, "Error reallocating memory to copy over the string \"%s\"\n", the_string);
            free(the_answer);
            exit(3);
        }
    }
    the_answer[index] = '\0';
    return the_answer;
}


int get_a_char() {
    struct termios old_terminal, new_terminal;
    int this_entry;
    tcgetattr(STDIN_FILENO, &old_terminal);
    new_terminal = old_terminal;
    new_terminal.c_lflag = new_terminal.c_lflag & ~ICANON;
    new_terminal.c_lflag = new_terminal.c_lflag & ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);
    this_entry = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
    return this_entry;
}


char* get_c_string(char finish, signed long input_length, const char* prompt, ...) {
    char* the_answer = (char*) malloc(sizeof(char) * 1);
    if (!the_answer) {
        fprintf(stderr, "Error allocating memory to get input\n");
        exit(4);
    }
    va_list ap;
    va_start(ap, prompt);
    vfprintf(stdout, prompt, ap);
    fflush(stdout);
    va_end(ap);
    int c;
    unsigned long index = 0;
    the_answer[index] = '\0';
    while ((c = get_a_char()) != (int) finish) {
        the_answer[index] = (char) c;
        the_answer = (char*) realloc(the_answer, (index + 1));
        if (!the_answer) {
            fprintf(stderr, "Error re-allocating memory for the string to be returned.\n");
            exit(5);
        }
        index = index + 1;
        if (((signed long) index) == ((signed long) input_length)) {
            break;
        }
    }
    the_answer[index] = '\0';
    return the_answer;
}


std::string get_string(char finish, signed long input_length, const char* prompt, ...) {
    va_list ap;
    va_start(ap, prompt);
    char* input = get_c_string(finish, input_length, prompt, ap);
    va_end(ap);
    std::string the_answer = std::string(input);
    free(input);
    return the_answer;
}


bool file_exists(std::string file) {
    std::fstream check(file);
    if (!check) {
        return false;
    }
    check.close();
    return true;
}



namespace web_scraping {

    namespace {

        const char* ipv4_pattern = (char*) "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
        const char* ipv6_pattern = (char*) "((([0-9a-fA-F]){1,4})\\:){7}([0-9a-fA-F]){1,4}";
        const char* url_pattern = (char*) "((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)";

        typedef enum {
            ip4 = 4,
            ip6 = 6
        } ip_ver;

        class host_address {

            private:

                std::string ip_address;
                ip_ver v;

            public:

                host_address() {
                    this->ip_address = "127.0.0.1";
                    this->v = ip4;
                }


                host_address(std::string address, unsigned short int ip_) {
                    this->ip_address = address;
                    this->v = (ip_ == 4) ? ip4 : ip6;
                }


                void set_ip_address(std::string address) {
                    this->ip_address = address;
                }


                std::string get_ip_address() const {
                    return this->ip_address;
                }


                void set_ip_4() {
                    this->v = ip4;
                }


                void set_ip_6() {
                    this->v = ip6;
                }


                unsigned short get_ip_version() const {
                    return (this->v == ip4) ? 4 : 6;
                }

        };

    }


    class host_info {

        private:
            std::string url;
            std::string connect_port;
            data_structures::linear_linked_list<host_address> addresses;
            const std::string host_indent = "\t\t";
            const std::string gap = " : ";
            const std::string host_separator = "----------------------";

            signed int index_of(std::string to_search, bool ip4 = true) {
                std::smatch finder;
                fprintf(stdout, "Calling index_of(%s, %s)\n", to_search.c_str(), (ip4) ? "true" : "false");
                if (ip4) {
                    std::regex_search(to_search, finder, std::regex(std::string(ipv4_pattern)));
                    if (finder.size() > 0) {
                        return (signed int) finder.position(0);
                    }
                    return -1;
                }
                std::regex_search(to_search, finder, std::regex(std::string(ipv6_pattern)));
                if (finder.size() > 0) {
                    return (signed int) finder.position(0);
                }
                return -1;

            }

            bool is_url(std::string url) {
                fprintf(stdout, "is_url(%s) is about to return %s\n", url.c_str(), std::regex_search(url, std::regex(std::string(url_pattern))) ? "true" : "false");
                return std::regex_search(url, std::regex(std::string(url_pattern)));
            }

            bool is_ip4(std::string ip) {
                return std::regex_match(ip, std::regex(std::string(ipv4_pattern)));
            }

            bool is_ip6(std::string ip) {
                return std::regex_match(ip, std::regex(std::string(ipv6_pattern)));
            }

            bool is_ip_address(std::string address) {
                return this->is_ip4(address) || this->is_ip6(address);
            }

            bool valid_port(std::string port) {
                return std::regex_match(port, std::regex("[0-9]{1,5}")) && port.length() <= 5;
            }

            void retrieve_ip_addresses() {
                int status;
                struct addrinfo initial_vals, *response, *current;
                char this_ip_address[INET6_ADDRSTRLEN];
                
                
                
                memset(&initial_vals, 0, sizeof(initial_vals)); // make sure the initial_vals struct is zero-ed out.

                // Set the starting points.
                initial_vals.ai_family = AF_UNSPEC; // specify that it can be either IP4 or IP6 (retrieve both)
                initial_vals.ai_socktype = SOCK_STREAM; // addrinfo gets the TCP stream sockets
                initial_vals.ai_flags = AI_PASSIVE; // fill in my IP address for me.


                // retrieve the host information
                if ((status = getaddrinfo(this->url.c_str(), this->connect_port.c_str(), &initial_vals, &response)) != 0) {
                    fprintf(stderr, "Error retrieving information for \"%s\". Error : %s\n", this->url.c_str(), gai_strerror(status));
                    exit(RETRIEVE_INFO_ERROR);
                }

                // initial_vals now points to a linked list with all the host information.
                // response points to the same location

                // now iterate through all the different host information struct addrinfo structs and retrieve their info.
                void* address;
                char* ip_version;
                struct sockaddr_in* ip_ver4;
                struct sockaddr_in6* ip_ver6;

                for (current = response; current != NULL; current = current->ai_next) {

                    // IP 4, so fill in ip_ver4
                    if (current->ai_family == AF_INET) { 
                        ip_ver4 = (struct sockaddr_in*) current->ai_addr;
                        address = &(ip_ver4->sin_addr); // a in_addr struct which holds a uint32_t representing the 32-but int representing the internet address.
                    }

                    else {
                        // IP 6, so fill in ip_ver6
                        ip_ver6 = (struct sockaddr_in6 *) current->ai_addr;
                        address = &(ip_ver6->sin6_addr);  // a in6_addr struct holding an unsigned char[16] with the IPv6 address.
                    }
                    inet_ntop(current->ai_family, address, this_ip_address, sizeof(this_ip_address));
                    host_address new_host(std::string(this_ip_address), (current->ai_family == AF_INET) ? 4 : 6);
                    this->addresses.push(new_host);

                }

                freeaddrinfo(response); // free the linked list

            }

            void write_data(std::string data, std::string file) {
                std::fstream write_file;
                write_file.open(file, std::ios::app);
                if (!write_file.is_open()) {
                    fprintf(stderr, "Could not open \"%s\"\n", file.c_str());
                    exit(CANNOT_OPEN_FILE);
                }
                write_file << data;
                write_file.close();
            }

            void read_from(std::string file) {
                std::fstream read_file(file);
                if (!read_file) {
                    fprintf(stderr, "Could not open file \"%s\"\n", file.c_str());
                    exit(CANNOT_OPEN_FILE);
                }
                // file was opened
                std::string this_line = "-1";
                while (std::getline(read_file, this_line)) {
                    if (!useful_functions::same_char(this_line[0], '\t')) {
                        // this is the url
                        fprintf(stdout, "determined %s is the url\n", this_line.c_str());
                        this->url = this_line;
                        this_line = "";
                        continue;
                    }
                    else {
                        // fprintf(stdout, "this_line = \"%s\"\n", this_line.c_str());
                        unsigned short ip_version = (unsigned short) (this_line[host_indent.length()] - '0');
                        host_address new_host(this_line.substr(host_indent.length() + gap.length()), ip_version);
                        this->addresses.push(new_host);
                    }
                }
            }

        public:


            host_info() {
                this->url = "localhost";
                this->connect_port = "80";
            }


            host_info(std::string host, std::string port = "80") {

                if (this->is_ip_address(host)) {
                    // need to find a way to convert an ip address into a url.
                    fprintf(stdout, "Working Progress. Not yet implemented a way to retrieve url from an ip address. For now please enter URL address instead.\n");
                    host = get_string('\n', -1, "Enter url corresponding with %s : ", host.c_str());
                }

                else {
                    // a url was given. Not sure what the pattern is for a valid url, need to research that for regex.
                    this->url = host;
                }

                while (!this->valid_port(port)) {
                    fprintf(stdout, "\"%s\" is not a valid port.\n", port.c_str());
                    port = get_string('\n', -1, "Enter a valid port number [0, %d] : ", MAX_PORT_VAL);
                }

                // host and port are now valid.
                this->retrieve_ip_addresses();
            }


            host_info& operator=(host_info& other) {
                if (this == &other) {
                    return *this;
                }
                this->url = other.get_url();
                this->addresses = other.addresses;
                this->connect_port = other.connect_port;
                return *this;
            }


            void print_host_info() {
                unsigned long index;
                for (index = 0; index < this->addresses.length(); index = index + 1) {
                    fprintf(stdout, "%lu.)\tIP version %u:\t%s\n", index + 1, this->addresses[index].get_ip_version(), this->addresses[index].get_ip_address().c_str());
                }
            }


            void save(std::string file_name) {
                if (file_exists(file_name)) {
                    std::filesystem::remove(file_name);
                }
                unsigned long index;
                this->write_data(this->url + "\n", file_name);
                for (index = 0; index < this->addresses.length(); index = index + 1) {
                    this->write_data(std::string(host_indent) + std::to_string(this->addresses[index].get_ip_version()) + std::string(this->gap) + this->addresses[index].get_ip_address() + ((index + 1 == this->addresses.length()) ? "" : "\n"), file_name);
                }
            }


            void fill_from_file(std::string file_name) {
                if (!file_exists(file_name)) {
                    fprintf(stdout, "No file \"%s\" exists. It will be created.\n", file_name.c_str());
                }
                this->read_from(file_name);
            }


            std::string get_url() const {
                return this->url;
            }


            void set_url(std::string url) {
                this->url = url;
            }


            data_structures::linear_linked_list<host_address> get_host_addresses() {
                return this->addresses;
            }


            void set_connect_port(std::string port_) {
                this->connect_port = port_;
            }


            std::string get_connect_port() const {
                return this->connect_port;
            }

    };


    class scrapper {

        private:

            host_info host;
            std::string save_directory, save_file;


        public:

            scrapper() {

            }

            scrapper(std::string url, std::string port = "80", std::string save_dir = "files", std::string save_f = "scrapper.data") {
                this->host.set_url(url);
                this->host.set_connect_port(port);
                this->save_directory = save_dir;
                this->save_file = save_f;
            }


        


    };

}