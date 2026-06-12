#include <example/example.h>

int main(void) {
    int value = 0;
    return texteditor_add_checked(1, 2, &value) && value == 3 ? 0 : 1;
}
