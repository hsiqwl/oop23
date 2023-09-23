#include <iostream>
#include <dialogue/dialogue.h>
#include <clamp/clamp.h>
#include <utils/utils.h>
using namespace clamp_class;
using namespace utils;
using std::cin;
using std::cout;
using namespace dialog;
 int main(){
     try {
         cout << "let's init our object\n";
         cout << "enter type(0 - in, 1 - out), status(0 - low, 1 - high, 2 - undefined) and link_num:";
         int c_type, status, link_num;
         c_type = getNum<int>();
         status = getNum<int>();
         link_num = getNum<int>();
         Clamp obj(static_cast<clamp_type>(c_type), static_cast<signal>(status), link_num);
         void (*func[])(Clamp& ) = {nullptr,set_type,
                                    set_status,
                                    set_links,
                                    get_type,
                                    get_status,
                                    get_links,
                                    print,
                                    increase_links,
                                    decrease_links,
                                    connect,
                                    disconnect};
         show_options(options, opt_num);
         int command = get_command(dialog::opt_num);
         while(command!=0){
             try{
                 func[command](obj);
             }
             catch(clamp_exception& a){
                 cout<< a.exception_info()<<'\n';
             }
             show_options(options, opt_num);
             command = get_command(opt_num);
         }
     }
     catch (std::exception &e){
         cout<<e.what()<<'\n';
     }
     return 0;
}