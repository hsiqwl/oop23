#ifndef DIALOGUE_DIALOGUE_H
#define DIALOGUE_DIALOGUE_H

#include <iostream>
#include <clamp/clamp.h>
using namespace clamp_class;
namespace dialog{
    extern const char *options[];
    extern const int opt_num;

    void show_options(const char *options[], const int opt_num);

    int get_command(int opt_num);

    void set_type(Clamp &obj);

    void set_status(Clamp &obj);

    void set_links(Clamp &obj);

    void get_type(Clamp &obj);

    void get_status(Clamp &obj);

    void get_links(Clamp &obj);

    void print(Clamp &obj);

    void increase_links(Clamp &obj);

    void decrease_links(Clamp &obj);

    void connect(Clamp &obj);

    void disconnect(Clamp &obj);
}
#endif //DIALOGUE_DIALOGUE_H
