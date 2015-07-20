#ifndef MERGER_H
#define MERGER_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

enum {
    idxsz = 250,                          // merge at most <idxsz-1> files
    bufsz = 1000 * 1000 * 100,            // initial memory allocation size: <bufsz> bytes
};

struct mem {
    unsigned int idx[idxsz];
    size_t sz;
    char *buf;
};

void initMem(mem *m);
void freeMem(mem *m);
void patchMem(mem *m, size_t sz, char *buf);
void saveMem(const char *path, const mem *m);
void loadParseSave(const char *ipath, const char *opath);

#endif
