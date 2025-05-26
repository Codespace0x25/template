#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int copy_file(const char *src, const char *dest) {
    FILE *in = fopen(src, "rb");
    if (!in) return -1;
    FILE *out = fopen(dest, "wb");
    if (!out) { fclose(in); return -1; }

    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), in)) > 0)
        fwrite(buf, 1, n, out);

    fclose(in);
    fclose(out);
    return 0;
}

int copy_dir(const char *src, const char *dest) {
    DIR *dir = opendir(src);
    if (!dir) return -1;

    mkdir(dest, 0755);  // create dest directory

    struct dirent *entry;
    char src_path[1024], dest_path[1024];

    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);

        struct stat st;
        stat(src_path, &st);

        if (S_ISDIR(st.st_mode)) {
            copy_dir(src_path, dest_path);
        } else {
            copy_file(src_path, dest_path);
        }
    }

    closedir(dir);
    return 0;
}
