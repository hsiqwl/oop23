#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "clamp/clamp.h"
#include "LogicElement/LogicElement.h"
using namespace clamp_class;
using namespace LogicElementClass;
TEST_CASE("Clamp constructors")
{
    SECTION("Default")
    {
        Clamp a;
        REQUIRE(a.get_type() == in);
        REQUIRE(a.get_signal() == undefined);
        REQUIRE(a.get_link_num() == 0);
    }SECTION("initializing constructor")
    {
        Clamp a(clamp_type::out, low, 2);
        REQUIRE(a.get_type() == out);
        REQUIRE(a.get_signal() == low);
        REQUIRE(a.get_link_num() == 2);
        Clamp b(clamp_type::in, high, 1);
        REQUIRE(b.get_type() == in);
        REQUIRE(b.get_signal() == high);
        REQUIRE(b.get_link_num() == 1);
        Clamp c{clamp_type::out};
        REQUIRE(c.get_type() == out);
        REQUIRE(c.get_signal() == undefined);
        REQUIRE(c.get_link_num() == 0);
        Clamp d(clamp_type::in, high, 0);
        REQUIRE(d.get_type() == in);
        REQUIRE(d.get_signal() == undefined);
        REQUIRE(d.get_link_num() == 0);
    }SECTION("constructor exceptions")
    {
        REQUIRE_THROWS(Clamp(in, undefined, 2));
        REQUIRE_THROWS(Clamp(out, undefined, 4));
        REQUIRE_THROWS(Clamp(in, undefined, -1));
        REQUIRE_THROWS(Clamp(out, undefined, -3));
    }
}

TEST_CASE("setters") {
    SECTION("clamp setters")
    {
        Clamp a;
        a.set_type(in);
        REQUIRE(a.get_type() == in);
        a.set_type(out);
        REQUIRE(a.get_type() == out);
        REQUIRE_THROWS(a.set_status(low));
        REQUIRE_THROWS(a.set_status(high));
        REQUIRE_THROWS(a.set_status(undefined));
        REQUIRE(a.get_signal() == undefined);
        a.set_link_num(1);
        REQUIRE(a.get_link_num() == 1);
        a.set_link_num(3);
        REQUIRE(a.get_link_num() == 3);
        REQUIRE_THROWS(a.set_link_num(-1));
        REQUIRE_THROWS(a.set_link_num(5));
        a.set_status(high);
        REQUIRE(a.get_signal() == high);
        a.set_link_num(0);
        a.set_type(in);
        a.set_link_num(1);
        REQUIRE(a.get_link_num() == 1);
        a.set_status(high);
        REQUIRE_THROWS(a.set_link_num(-1));
        REQUIRE_THROWS(a.set_link_num(2));
    }
}

TEST_CASE("operators") {
    SECTION("++ and -- operators")
    {
        Clamp a;
        ++a;
        REQUIRE(a.get_link_num() == 1);
        REQUIRE_THROWS(++a);
        a.set_link_num(0);
        Clamp b = a++;
        REQUIRE(b.get_link_num() == 0);
        REQUIRE(a.get_link_num() == 1);
        b.set_type(out);
        ++b;
        ++b;
        REQUIRE(b.get_link_num() == 2);
        ++b;
        REQUIRE(b.get_link_num() == 3);
        REQUIRE_THROWS(++b);
        REQUIRE_THROWS(b++);
        Clamp c = b--;
        REQUIRE(c.get_link_num() == 3);
        REQUIRE(b.get_link_num() == 2);
        --b;
        --c;
        REQUIRE(c.get_link_num() == 2);
        REQUIRE(b.get_link_num() == 1);
        --b;
        REQUIRE_THROWS(--b);
        REQUIRE_THROWS(b--);
    }SECTION(">> and << operators")
    {
        Clamp a(out, high, 1);
        Clamp b;
        a >> b;
        REQUIRE(b.get_signal() == high);
        a << b;
        REQUIRE(b.get_signal() == undefined);
        b >> a;
        REQUIRE(b.get_signal() == high);
        b << a;
        REQUIRE(b.get_signal() == undefined);
        b.set_type(out);
        REQUIRE_THROWS(a >> b);
        REQUIRE_THROWS(b >> a);
        REQUIRE_THROWS(a << b);
        REQUIRE_THROWS(b << a);
    }SECTION("! operator")
    {
        Clamp a(out, high, 3);
        !a;
        REQUIRE(a.get_signal() == low);
        !a;
        REQUIRE(a.get_signal() == high);
        a.set_status(undefined);
        REQUIRE_THROWS(!a);
    }
}

TEST_CASE("LogicElement constructors"){
    SECTION("default constructor"){
        LogicElement a;
        REQUIRE(a.get_curr_size()==0);
        REQUIRE(a.get_max_size()==0);
        REQUIRE(a.get_num_of_in()==0);
        REQUIRE(a.get_num_of_out()==0);
        REQUIRE(a.get_ptr() == nullptr);
    }
    SECTION("Init constructors"){
        LogicElement a{3,4};
        REQUIRE(a.get_curr_size() == 7);
        REQUIRE(a.get_max_size() == 7);
        REQUIRE(a.get_num_of_in() == 4);
        REQUIRE(a.get_num_of_out() == 3);
        REQUIRE(a.get_ptr() != nullptr);
        Clamp arr[] = {Clamp{in,undefined,0} , Clamp{out,high,2}};
        LogicElement b{arr,2};
        REQUIRE(b.get_curr_size() == 2);
        REQUIRE(b.get_max_size() == 2);
        REQUIRE(b.get_num_of_out() == 1);
        REQUIRE(b.get_num_of_in() == 1);
        REQUIRE(b.get_ptr() != nullptr);
    }SECTION("copy constructor"){
        LogicElement a{2,1};
        LogicElement b{a};
        REQUIRE(b.get_curr_size() == 3);
        REQUIRE(b.get_max_size() == 3);
        REQUIRE(b.get_num_of_out() == 2);
        REQUIRE(b.get_num_of_in() == 1);
        {
            LogicElement c{a};
        }
        REQUIRE(a.get_curr_size() == 3);
        REQUIRE(a.get_max_size() == 3);
        REQUIRE(a.get_num_of_out() == 2);
        REQUIRE(a.get_num_of_in() == 1);
    }SECTION("move constructor"){
        LogicElement a{2,1};
        LogicElement b{std::move(a)};
        REQUIRE(b.get_curr_size() == 3);
        REQUIRE(b.get_max_size() == 3);
        REQUIRE(b.get_num_of_out() == 2);
        REQUIRE(b.get_num_of_in() == 1);
        REQUIRE(b.get_ptr()!= nullptr);
        REQUIRE(a.get_curr_size() == 0);
        REQUIRE(a.get_max_size() == 0);
        REQUIRE(a.get_num_of_out() == 0);
        REQUIRE(a.get_num_of_in() == 0);
        REQUIRE(a.get_ptr()== nullptr);
    }
}

TEST_CASE("LogicElement operators"){
    SECTION("copy assignment"){
        LogicElement a{2,1};
        {
            LogicElement b;
            b = a;
            REQUIRE(b.get_curr_size() == 3);
            REQUIRE(b.get_max_size() == 3);
            REQUIRE(b.get_num_of_out() == 2);
            REQUIRE(b.get_num_of_in() == 1);
            REQUIRE(b.get_ptr()!= nullptr);
        }
        REQUIRE(a.get_curr_size() == 3);
        REQUIRE(a.get_max_size() == 3);
        REQUIRE(a.get_num_of_out() == 2);
        REQUIRE(a.get_num_of_in() == 1);
        REQUIRE(a.get_ptr()!= nullptr);
    }SECTION("move assignment"){
        LogicElement a{2,1};
        LogicElement b;
        b = std::move(a);
        REQUIRE(b.get_curr_size() == 3);
        REQUIRE(b.get_max_size() == 3);
        REQUIRE(b.get_num_of_out() == 2);
        REQUIRE(b.get_num_of_in() == 1);
        REQUIRE(b.get_ptr()!= nullptr);
        REQUIRE(a.get_curr_size() == 0);
        REQUIRE(a.get_max_size() == 0);
        REQUIRE(a.get_num_of_out() == 0);
        REQUIRE(a.get_num_of_in() == 0);
        REQUIRE(a.get_ptr() == nullptr);
    }SECTION("operator []"){
        LogicElement a{2,1};
        REQUIRE_THROWS(a[a.get_curr_size()]);
        Clamp b = a[0];
        REQUIRE(b.get_type() == out);
        REQUIRE(b.get_signal() == undefined);
        REQUIRE(b.get_link_num() == 0);
        Clamp c = a[2];
        REQUIRE(c.get_type() == in);
        REQUIRE(c.get_signal() == undefined);
        REQUIRE(c.get_link_num() == 0);
    }SECTION("operator <=>"){
        LogicElement a{2,3};
        LogicElement b{3,2};
        LogicElement c{3,3};
        REQUIRE(a<=>b == std::weak_ordering::greater);
        REQUIRE(a<=>c == std::weak_ordering::equivalent);
        REQUIRE(b<=>a == std::weak_ordering::less);
    }SECTION(">> operator"){
        Clamp ptr1[] = {Clamp{out,high,2}, Clamp{in,low,1}};
        LogicElement a(ptr1,2);
        Clamp ptr2[] = {Clamp{in,high,1}, Clamp{in,low,1}};
        LogicElement b(ptr2,2);
        REQUIRE_THROWS(a >> b);
        Clamp ptr3[] = {Clamp{in,undefined,0}, Clamp{in,low,1}};
        LogicElement c(ptr3,2);
        REQUIRE_NOTHROW(a >> c);
        Clamp d = a[0];
        Clamp e = c[0];
        REQUIRE(d.get_link_num() == 3);
        REQUIRE(e.get_link_num() == 1);
        REQUIRE(e.get_signal() == high);
    }
}
