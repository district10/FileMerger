#include "merger.h"

void initMem(mem *m)
{
    for (int i = 0; i < idxsz; ++i) {
        m->idx[i] = 0;
    }
    m->sz = bufsz;
    m->buf = (char *)malloc(m->sz);
}

void patchMem(mem *m, size_t sz, char *buf)
{
    ++m->idx[0];
    if (m->idx[0] == 1) {                                // the first one
        m->idx[m->idx[0]] = sz;
    } else {                                             // not the first one
        size_t end = m->idx[m->idx[0]-1] + sz;
        m->idx[m->idx[0]] = end;
        if (end > m->sz) {                               // too much bytes to store
            fprintf(stderr, "Bufsz: %d => %d\n", m->sz, 2*m->sz);
            m->sz *= 2;
            realloc(m->buf, m->sz);                      // this is buggy
        }
    }

    if (m->idx[0] == 1) {
        memcpy(m->buf, buf, sz);
    } else {
        size_t offset = 1 + m->idx[m->idx[0]-1];
        memcpy(m->buf + offset, buf, sz);
    }
    fprintf(stdout, "added %d bytes.\n", sz);
}

void freeMem(mem *m)
{
    free(m->buf);
}


void saveMem(const char *path, const mem *m)
{
    FILE *fp = fopen(path, "wb");

    fwrite(m->idx, sizeof(m->idx[0]), m->idx[0]+1, fp);

    size_t sz = m->idx[ m->idx[0] ];
    fwrite(m->buf, sz, 1, fp);
    fclose(fp);
}

void loadParseSave(const char *ipath, const char *opath)
{
    char path[100];

    FILE *ifp = fopen(ipath, "rb");
    unsigned int num = 0;
    unsigned int sz = 0;
    fread(&num, sizeof(num), 1, ifp);

    unsigned int *header = (unsigned int *)malloc(num*sizeof(unsigned int));
    fread(header, sizeof(unsigned int), num, ifp);
    char *buf = (char *)malloc(header[num-1]);
    fread(buf, 1, header[num-1], ifp);

    for (int i = 0; i < num; ++i) {
        sprintf(path, "%d_%s", i+1, opath);
        static size_t offset = 0;
        static size_t count = 0;

        if (i == 0) {
            offset = 0;
            count = header[0];
        } else {
            offset = header[i-1] + 1;
            count = header[i] - header[i-1];
        }

        FILE *ofp = fopen(path, "wb");
        fwrite(buf+offset, 1, count, ofp);
        fclose(ofp);
    }

    free(header);
    free(buf);
    fclose(ifp);
}
