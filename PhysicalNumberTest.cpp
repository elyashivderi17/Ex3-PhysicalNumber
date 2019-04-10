/**
 * Examples of automatic tests for the exercise on physical numbers.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
#include <sstream>
using std::cout, std::endl, std::istringstream;
#include "PhysicalNumber.h"
using ariel::PhysicalNumber, ariel::Unit;
#include "badkan.hpp"

int main()
{
  badkan::TestCase testcase;
  int grade = 0;
  int signal = setjmp(badkan::longjmp_buffer);
  if (signal == 0)
  {

    // BASIC TESTS - DO NOT CHANGE
    PhysicalNumber a(2, Unit::KM);
    PhysicalNumber b(300, Unit::M);
    PhysicalNumber c(2, Unit::HOUR);
    PhysicalNumber d(30, Unit::MIN);
    ////////////////////////////////
    PhysicalNumber e(5, Unit::CM);
    PhysicalNumber f(10, Unit::SEC);
    PhysicalNumber g(15, Unit::G);
    PhysicalNumber h(20, Unit::KG);
    PhysicalNumber i(25, Unit::TON);
    ////////////////////////////////

    testcase
        .setname("Basic output")
        .CHECK_OUTPUT(a, "2[km]")
        .CHECK_OUTPUT(b, "300[m]")
        /////////start//////////////
        .CHECK_OUTPUT(c, "2[h]")
        .CHECK_OUTPUT(d, "30[min]")
        .CHECK_OUTPUT(e, "5[cm]")
        .CHECK_OUTPUT(f, "10[sec]")
        .CHECK_OUTPUT(g, "15[g]")
        .CHECK_OUTPUT(h, "20[kg]")
        .CHECK_OUTPUT(i, "25[ton]")
        /////////end/////////////

        .setname("Compatible dimensions")
        .CHECK_OUTPUT(b + a, "2300[m]")
        .CHECK_OUTPUT((a += b), "2.3[km]")
        .CHECK_OUTPUT(a, "2.3[km]")
        .CHECK_OUTPUT(a + a, "4.6[km]")
        .CHECK_OUTPUT(b - b, "0[m]")
        .CHECK_OUTPUT(c, "2[hour]")
        .CHECK_OUTPUT(d, "30[min]")
        .CHECK_OUTPUT(d + c, "150[min]")
        ////////////start/////////////////
        .CHECK_OUTPUT(e + a, "200005[cm]")
        .CHECK_OUTPUT(e + b, "30005[cm]")
        .CHECK_OUTPUT(d + c, "150[sec]")
        .CHECK_OUTPUT(f + c, "7210[sec]")
        .CHECK_OUTPUT(f + d, "1810[sec]")
        .CHECK_OUTPUT(g + h, "20015[g]")
        .CHECK_OUTPUT(h + i, "25020[kg]")
        .CHECK_OUTPUT(g + i, "250000015[g]")
        /////////////end/////////////////

        .setname("Incompatible dimensions")
        .CHECK_THROWS(a + c)
        .CHECK_THROWS(a + d)
        .CHECK_THROWS(b + c)
        .CHECK_THROWS(b + d)
        //////////start//////
        .CHECK_THROWS(a + g)
        .CHECK_THROWS(b + f)
        .CHECK_THROWS(e + i)
        .CHECK_THROWS(c + g)
        .CHECK_THROWS(f + h)
        .CHECK_THROWS(c + i)
        .CHECK_THROWS(i + b)
        .CHECK_THROWS(g + e)
        .CHECK_THROWS(b + h)
        .CHECK_THROWS(a + h)
        //////////end///////

        .setname("Basic input")
        .CHECK_OK(istringstream("700[kg]") >> a)
        .CHECK_OUTPUT((a += PhysicalNumber(1, Unit::TON)), "1700[kg]")
        .CHECK_OUTPUT((b += PhysicalNumber(10, Unit::KM)), "10300[m]") 
        .CHECK_OUTPUT((b -= PhysicalNumber(10, Unit::KM)), "9700[m]") 
        .CHECK_OUTPUT(+a, "2[km]") 
        .CHECK_OUTPUT(-a, "-2[km]") 
        .CHECK_EQUAL((a==PhysicalNumber(20, Unit::KM)),true) 
        .CHECK_EQUAL((b==PhysicalNumber(400, Unit::M)),false)
        .CHECK_EQUAL((a<PhysicalNumber(7, Unit::KM)),true) 
        .CHECK_EQUAL((b>PhysicalNumber(3, Unit::KM)),false)
        .CHECK_EQUAL((e>=PhysicalNumber(5, Unit::CM)),true) 
        .CHECK_OUTPUT(h++, "21[kg]") 
        .CHECK_OUTPUT(h--, "19[kg]")
        .CHECK_OUTPUT(PhysicalNumber(10, Unit::KG)++, "11[kg]") 
        .CHECK_OUTPUT(PhysicalNumber(10, Unit::G)-- ,"9[g]") 
        .CHECK_OUTPUT(h+h , "40[kg]") 
        .CHECK_OUTPUT(i+PhysicalNumber(10, Unit::TON) , "35[ton]")
        .CHECK_OUTPUT(+b , "300[m]") 
        .CHECK_OUTPUT(-b , "-300[m]")
        .CHECK_EQUAL((PhysicalNumber(3, Unit::KM))>=(PhysicalNumber(300, Unit::M)),true)
        .CHECK_EQUAL((a>=PhysicalNumber(7, Unit::KM)),false) 
        .CHECK_EQUAL((PhysicalNumber(8, Unit::CM))<=(PhysicalNumber(8, Unit::CM)),true ) 
        .CHECK_EQUAL((b!=PhysicalNumber(6, Unit::KM)),true)  
        .CHECK_EQUAL((b!=PhysicalNumber(300, Unit::M)),false)
        .CHECK_EQUAL((PhysicalNumber(3000, Unit::M)!=PhysicalNumber(5, Unit::KM)) ,false) 
        .CHECK_OUTPUT((h += PhysicalNumber(2, Unit::KG)), "4[kg]")
        .CHECK_OUTPUT((h += PhysicalNumber(5, Unit::G)), "20.05[kg]") 
        .CHECK_OUTPUT((h -= PhysicalNumber(10, Unit::KG)), "10[kg]") 
        .CHECK_OUTPUT((h -= PhysicalNumber(20, Unit::KG)), "0[kg]") 
        .CHECK_OUTPUT((i += PhysicalNumber(5, Unit::TON)), "30[ton]") 
        .CHECK_OUTPUT(-h , "-20[kg]") 
        .CHECK_OUTPUT(+h, "20[kg]") 
        .CHECK_EQUAL((h!=PhysicalNumber(15, Unit::KG)),true)  
        .CHECK_EQUAL((i!=PhysicalNumber(10, Unit::TON)),true)
        .CHECK_EQUAL((h!=PhysicalNumber(20, Unit::KG)),false)  
        .CHECK_EQUAL((i!=PhysicalNumber(25, Unit::TON)),false)
        .CHECK_EQUAL((PhysicalNumber(i, Unit::TON))<=(PhysicalNumber(14000, Unit::KG)),false) 
        .CHECK_EQUAL((h<PhysicalNumber(1, Unit::TON)),true)
        .CHECK_EQUAL((g<PhysicalNumber(12, Unit::G)),false) 
        .CHECK_EQUAL((g>PhysicalNumber(10, Unit::TON)),false) 
        .CHECK_OUTPUT(PhysicalNumbe .CHECK_OUTPUT((d += PhysicalNumber(2, Unit::MIN)), "32[min]") 
        .CHECK_OUTPUT((PhysicalNumber(2, Unit::MIN) += PhysicalNumber(5, Unit::HOUR)), "5.20[hour]") 
        .CHECK_OUTPUT(((PhysicalNumber(1, Unit::MIN) += PhysicalNumber(10, Unit::HOUR)), "602.083[min]") 
        .CHECK_OUTPUT(((PhysicalNumber(1, Unit::MIN) -= PhysicalNumber(2, Unit::MIN)), "1[min]") 
        .CHECK_OUTPUT(-d , "-30[min]") 
        .CHECK_OUTPUT(+d, "30[min]") 
        .CHECK_EQUAL((c==PhysicalNumber(2, Unit::HOUR)),true) 
        .CHECK_EQUAL((f==PhysicalNumber(10, Unit::SEC)),true)  
        .CHECK_EQUAL((c!=PhysicalNumber(2, Unit::HOUR)),false)             
        .CHECK_EQUAL((e==PhysicalNumber(5, Unit::CM)),true)  
        .CHECK_EQUAL((e!=PhysicalNumber(5, Unit::CM)),false)
        .CHECK_EQUAL((f!=PhysicalNumber(10, Unit::SEC)),false) 
        .CHECK_EQUAL((PhysicalNumber(9, Unit::HOUR))<(PhysicalNumber(9, Unit::SEC)),false) 
        .CHECK_EQUAL((d<PhysicalNumber(4, Unit::HOUR)),true) 
       .CHECK_EQUAL((c<PhysicalNumber(50, Unit::SEC)),false) 
       .CHEr(2, Unit::HOUR)+PhysicalNumber(10, Unit::HOUR), "12[hour]") 
       .CK_EQUAL((d>PhysicalNumber(11, Unit::HOUR)),false) 
       .CHECK_EQUAL((PhysicalNumber(2, Unit::HOUR))>(PhysicalNumber(400, Unit::SEC)),true)
       .CHECK_EQUAL((c>PhysicalNumber(2, Unit::SEC)),true) 
       .CHECK_EQUAL((d>=PhysicalNumber(30, Unit::MIN)),true) 
       .CHECK_EQUAL((PhysicalNumber(30, Unit::HOUR))>=(PhysicalNumber(300, Unit::SEC)),true)
       .CHECK_EQUAL((PhysicalNumber(90, Unit::SEC))<=(PhysicalNumber(90, Unit::SEC)),true )
       .CHECK_EQUAL((PhysicalNumber(2, Unit::HOUR)!=PhysicalNumber(120, Unit::MIN)) ,false) 
       .CHECK_EQUAL((PhysicalNumber(2, Unit::HOUR)!=PhysicalNumber(12, Unit::HOUR)) ,true)
       .CHECK_OUTPUT(++d , "31[min]") 
       .CHECK_OUTPUT(++d , "32[min]") 
       .CHECK_OUTPUT(--d , "31[min]") 
       .CHECK_OUTPUT(--d , "30[min]")
       .CHECK_OUTPUT(PhysicalNumber(25, Unit::HOUR)++, "26[hour]") 
       .CHECK_OUTPUT(PhysicalNumber(25, Unit::SEC)-- ,"24[sec]") 
       .CHECK_EQUAL((PhysicalNumber(25, Unit::SEC)--) != (PhysicalNumber(23, Unit::SEC)++)) ,true)



        // YOUR TESTS - INSERT AS MANY AS YOU WANT

        .setname("...")

        .print(cout, /*show_grade=*/false);
    grade = testcase.grade();
  }
  else
  {
    testcase.print_signal(signal);
    grade = 0;
  }
  cout << "*** Grade: " << grade << " ***" << endl;
  return grade;
}
