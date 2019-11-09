#include <iostream>
#include "Biset.h"

using namespace std;
using namespace CTRL;

int main() {
    std::cout << "Hello, World!" << std::endl;
    Biset c;
    c.Reserve(10);

    auto i = c.FormerEnd();
    while (!i.BeforeFormerBegin()) {
        const auto r = i.Value();
//        cout << i.Value() << endl;
        if (r % 2 != 0) {
            i.MoveToLatterAndGoPrevious();
        } else {
            --i;
        }
    }

    cout << "----------------" << endl;

    auto j = c.FormerBegin();
    while (!j.AfterFormerEnd()) {
        cout << j.Value() << endl;
        ++j;
    }

    c.Mark();

    auto ii = c.FormerEnd();
    while (!ii.BeforeFormerBegin()) {
        const auto r = ii.Value();
//        cout << ii.Value() << endl;
        if (r % 3 != 0) {
            ii.MoveToLatterAndGoPrevious();
        } else {
            --ii;
        }
    }

    cout << "----------------" << endl;

    auto jj = c.FormerBegin();
    while (!jj.AfterFormerEnd()) {
        cout << jj.Value() << endl;
        ++jj;
    }

    c.BackToMark();

    cout << "----------------" << endl;

    auto k = c.FormerBegin();
    while (!k.AfterFormerEnd()) {
        cout << k.Value() << endl;
        ++k;
    }

    return 0;
}