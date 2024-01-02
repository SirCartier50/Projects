#include "set.h"

#include <stdio.h>
Set set_empty(void) {
    Set s = 0;
    return s;
}
Set set_universal(void) {
    Set s = 0xFF;
    return s;
}
Set set_insert(Set s, int x) {
    return (s | (0x01 << x));
}
Set set_remove(Set s, int x) {
    return (s & ~(0x01 << x));
}
bool set_member(Set s, int x) {
    if ((s & 0x01 << x) != 0) {
        return true;
    } else {
        return false;
    }
}
Set set_union(Set s, Set t) {
    return (s | t);
}
Set set_intersect(Set s, Set t) {
    return (s & t);
}
Set set_difference(Set s, Set t) {
    return (s & (~t));
}
Set set_complement(Set s) {
    return ~s;
}
