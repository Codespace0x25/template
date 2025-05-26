#include "filesystem.h"
#include "string.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define TemplateStore "/usr/share/templates"

void show_help(const char *progname) {
    printf("Usage: %s <command> [options]\n\n", progname);
    printf("Commands:\n");
    printf("  help                             Show this help message\n");
    printf("  list [LANG]                      List available languages or templates\n");
    printf("  new <LANG> <TYPE> [-o NAME]      Create a new project from a template\n\n");
    printf("Examples:\n");
    printf("  %s new C basic -o myproject\n", progname);
    printf("  %s list\n", progname);
    printf("  %s list C\n", progname);
}

void list_templates(const char *lang) {
    char path[512];

    if (lang == NULL) {
        snprintf(path, sizeof(path), "%s", TemplateStore);
        DIR *dir = opendir(path);
        if (!dir) {
            fprintf(stderr, "ERROR: Unable to open template store: %s\n", path);
            return;
        }

        printf("Available languages:\n");
        struct dirent *entry;
        while ((entry = readdir(dir))) {
            if (entry->d_type == DT_DIR &&
                strcmp(entry->d_name, ".") != 0 &&
                strcmp(entry->d_name, "..") != 0) {
                printf("  %s\n", entry->d_name);
            }
        }
        closedir(dir);

    } else {
        snprintf(path, sizeof(path), "%s/%s", TemplateStore, lang);
        DIR *dir = opendir(path);
        if (!dir) {
            fprintf(stderr, "ERROR: No templates found for language: %s\n", lang);
            return;
        }

        printf("Templates for language '%s':\n", lang);
        struct dirent *entry;
        while ((entry = readdir(dir))) {
            if (entry->d_type == DT_DIR &&
                strcmp(entry->d_name, ".") != 0 &&
                strcmp(entry->d_name, "..") != 0) {
                printf("  %s\n", entry->d_name);
            }
        }
        closedir(dir);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "ERROR: Missing command. Try:\n  %s help\n", argv[0]);
        return 1;
    }

    const char *cmd = argv[1];

    if (strcmp(cmd, "help") == 0) {
        show_help(argv[0]);
        return 0;
    }

    if (strcmp(cmd, "list") == 0) {
        const char *lang = (argc >= 3) ? argv[2] : NULL;
        list_templates(lang);
        return 0;
    }

    if (strcmp(cmd, "new") == 0) {
        if (argc < 4) {
            fprintf(stderr, "ERROR: Usage: %s new <LANG> <TYPE> [-o NAME]\n", argv[0]);
            return 1;
        }

        const char *lang = argv[2];
        const char *type = argv[3];
        const char *out_name = type;

        if (argc >= 6 && strcmp(argv[4], "-o") == 0) {
            out_name = argv[5];
        }

        char template_path[512];
        snprintf(template_path, sizeof(template_path), "%s/%s/%s", TemplateStore, lang, type);

        if (copy_dir(template_path, out_name) == 0) {
            printf("SUCCESS: Created '%s' project from template '%s/%s'\n", out_name, lang, type);
            return 0;
        } else {
            fprintf(stderr, "ERROR: Failed to copy template from: %s\n", template_path);
            return 1;
        }
    }

    fprintf(stderr, "ERROR: Unknown command: %s\n", cmd);
    show_help(argv[0]);
    return 1;
}
