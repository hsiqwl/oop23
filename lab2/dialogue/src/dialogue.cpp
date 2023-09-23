#include <iostream>
#include <clamp/clamp.h>
#include <dialogue/dialogue.h>
#include <utils/utils.h>
using std::cout;
using std::cin;
using namespace clamp_class;
using namespace utils;
#include <cstring>
namespace dialog{
    const char *options[] = {"0.exit", "1.set_type", "2.set_status", "3.set_links", "4.get_type", "5.get_status",
                             "6.get_links", "7.print", "8.increase links", "9.decrease links", "10.connect",
                             "11.disconnect"};
    const int opt_num = sizeof(options) / sizeof(options[0]);

    int get_command(int opt_num) {
        cout << "enter command nummber:";
        int command = getNum<int>(0, opt_num - 1);
        return command;
    }

    void show_options(const char *options[], const int opt_num) {
        for (int i = 0; i < opt_num; i++) {
            cout << options[i] << '\n';
        }
    }

    void set_type(Clamp &obj) {
        cout << "enter clamp_type(0 - in, 1 - out):";
        int clamp_type = getNum<int>();
        obj.set_type(static_cast<enum clamp_type>(clamp_type));
        obj.print(std::cout);
    }

    void set_status(Clamp &obj) {
        cout << "enter signal(0 - low, 1 - high, 2 - undefined):";
        int status = getNum<int>();
        obj.set_status(static_cast<enum signal>(status));
        obj.print(std::cout);
    }

    void set_links(Clamp &obj) {
        cout << "enter number of links:";
        int links = getNum<int>();
        obj.set_link_num(links);
        obj.print(std::cout);
    }

    void get_type(Clamp &obj) {
        cout << "type:" << obj.get_type() << '\n';
    }

    void get_status(Clamp &obj) {
        cout << "status:" << obj.get_signal() << '\n';
    }

    void get_links(Clamp &obj) {
        cout << "link_num:" << obj.get_link_num() << '\n';
    }

    void print(Clamp &obj) {
        obj.print(std::cout);
    }

    void increase_links(Clamp &obj) {
        cout << "before increasing:";
        obj.print(std::cout);
        ++obj;
        cout << "after increasing:";
        obj.print(std::cout);
    }

    void decrease_links(Clamp &obj) {
        cout << "before decreasing:";
        obj.print(std::cout);
        --obj;
        cout << "after decreasing:";
        obj.print(std::cout);
    }

    void connect(Clamp &obj) {
        if (strcmp(obj.get_type() ,"in") == 0) {
            Clamp new_obj(out);
            cout << "made new object\n";
            cout << "printing two objects before >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
            obj >> new_obj;
            cout << "printing two objects after >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
        } else {
            Clamp new_obj(in);
            cout << "made new object\n";
            cout << "printing two objects before >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
            obj >> new_obj;
            cout << "printing two objects after >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
        }
    }

    void disconnect(Clamp &obj) {
        if (strcmp(obj.get_type() ,"in") == 0) {
            Clamp new_obj(out);
            cout << "made new object\n";
            cout << "printing two objects before >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
            obj << new_obj;
            cout << "printing two objects after >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
        } else {
            Clamp new_obj(in);
            cout << "made new object\n";
            cout << "printing two objects before >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
            obj << new_obj;
            cout << "printing two objects after >>:";
            obj.print(std::cout);
            new_obj.print(std::cout);
        }
    }
}