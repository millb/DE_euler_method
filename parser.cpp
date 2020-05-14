#include "parser.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <dlfcn.h>

using namespace std;

void safe_write(int fd, const char *data, size_t len) {
    size_t writed = 0;
    while ((writed += write(fd, data + writed, len - writed)) < len);
}

func_t parse(const string &s) {
    char tmpsource[] = "XXXXXX.c";
    int fd = mkstemps(tmpsource, 2);
    static char prefix[] = "#include <math.h>\ndouble f(double x, double y){return ";
    static char suffix[] = ";}\n";
    safe_write(fd, prefix, strlen(prefix));
    safe_write(fd, s.data(), s.size());
    safe_write(fd, suffix, strlen(suffix));
    close(fd);
    char tmpshared[] = "XXXXXX.so";
    close(mkstemps(tmpshared, 3));
    if (system((string("gcc -fpic -Ofast -shared -o ") + tmpshared + " " + tmpsource +
        " 2> /dev/null").data())) {
        unlink(tmpsource);
        return nullptr;
    }
    void *lib = dlopen((string("./") + tmpshared).data(), RTLD_LAZY);
    func_t ans = reinterpret_cast<func_t>(dlsym(lib, "f"));
    unlink(tmpsource);
    unlink(tmpshared);
    return ans;
}