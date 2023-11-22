#include "../headers/include.h"



int main(int len, char** args) {

    // printf("Reached :D\n");
    std::string ip_address, save_file;
    if (len < 2) {
        ip_address = get_string('\n', -1, "Enter an IP address: ");
        save_file = get_string('\n', -1, "Enter save file");
    }
    else if ( len > 2) {
        ip_address = std::string(args[1]);
        save_file = std::string(args[2]);
    }
    else {
        ip_address = std::string(args[1]);
    }
    fprintf(stdout, "SYS_SLASH is %s\n", SYS_SLASH);
    web_scraping::host_info inputted_host(ip_address), other_host;
    printf("inputted_host_info : \n");
    inputted_host.print_host_info();
    inputted_host.save(save_file);
    printf("\nEnd of inputted_host info\n\nother_host info:\n");
    other_host.fill_from_file(save_file);
    other_host.print_host_info();
    printf("\nEnd of other_host info\n");
    return 0;
}