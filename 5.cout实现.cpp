/*************************************************************************
	> File Name: 5.cout实现.cpp
	> Author: houhaien 
	> Mail: github.com/houhaien 
	> Created Time: 2019年10月06日 星期日 11时19分23秒
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <string.h>

namespace haizei{
    class ostream {
    public :
        ostream &operator<<(int x) {
            printf("%d",x);
            return *this;
        }
        ostream &operator<<(const std::string &str) {
            printf("%s", str.c_str());
            return *this;
        }
        
        ostream &operator<<(const char &ch) {
            printf("%c", ch);
            return *this;
        }
        
        ostream &operator<<(const double &a) {
            /*
            char e_str[20];
            int e_num, temp;
            sprintf(e_str, "%.5e", a);
            sscanf(e_str, "%d.%de%d",&temp,&temp, &e_num);
            printf("e_num : %d\n", e_num);
            if(e_num >= 6 || e_num <= -5) {
                printf("%s", e_str);
            } else {
                temp = 5 - e_num;
                sprintf(e_str,"%%.%dlf", temp);
                printf(e_str,a);
            }
            return *this;
            */
            printf("%g",a);
            return *this;
        }
    };
    char endl = '\n';
    ostream cout;
}


int main() {
    haizei::cout << "hello" << haizei::endl;
    haizei::cout << 123 << haizei::endl;
    haizei::cout << 1236.7894565 << haizei::endl;
    haizei::cout << 12.56236532 << haizei::endl;
    haizei::cout << 'a' << haizei::endl;
    haizei::cout << 123 << 123. <<  haizei::endl;
    std::cout << 123<< 123. <<  std::endl;
    haizei::cout << 123.78787878 << haizei::endl;
    haizei::cout << 3.78787878 << haizei::endl;

    return 0;
}
