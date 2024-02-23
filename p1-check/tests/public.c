#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <check.h>

#include "../p1-check.h"

/* parse_command_line_p1 is declared and defined */
START_TEST (C_sanity_parse_is_declared)
{
    int argc = 1;
    char *argv[] = {"./y86", NULL };
    int rc = 0;
    bool header = false;
    char *file = NULL;

    rc = parse_command_line_p1 (argc, argv, &header, &file);
    ck_assert (rc || !rc);
}
END_TEST

/* read_header is declared and defined */
START_TEST (C_sanity_read_header_is_declared)
{
    elf_hdr_t elf;
    FILE *fp = fopen ("inputs/simple.o", "r");
    ck_assert (fp != NULL);
    bool rc = read_header (fp, &elf);
    ck_assert (rc || !rc);
}
END_TEST

/* dump_header is declared and defined */
START_TEST (C_sanity_dump_header_is_declared)
{
    elf_hdr_t elf;
    strncpy ((char*)&elf.magic, "ELF", sizeof (elf.magic));
    dump_header (elf);
    ck_assert (1 == 1);
}
END_TEST

/* check for the -h flag */
START_TEST (B_cmdline_H_flag)
{
    int argc = 3;
    char *argv[] = { "./y86", "-H", "empty.o", NULL };
    bool rc = 0;
    bool header = false;
    char *file = NULL;

    rc = parse_command_line_p1 (argc, argv, &header, &file);
    ck_assert (rc);
    ck_assert (header == true);
    ck_assert (!strcmp(file, "empty.o"));
}
END_TEST

/* check for the -h flag and a filename */
START_TEST (B_cmdline_H_flag_and_file)
{
    int argc = 3;
    char *argv[] = { "./y86", "-H", "inputs/add.o", NULL };
    bool rc = 0;
    bool header = false;
    char *file = NULL;

    rc = parse_command_line_p1 (argc, argv, &header, &file);
    ck_assert (rc);
    ck_assert (header == true);
    ck_assert (!strcmp (file, argv[2]));
}
END_TEST

void public_tests (Suite *s)
{
    TCase *tc_public = tcase_create ("Public");
    tcase_add_test (tc_public, C_sanity_parse_is_declared);
    tcase_add_test (tc_public, C_sanity_read_header_is_declared);
    tcase_add_test (tc_public, C_sanity_dump_header_is_declared);
    tcase_add_test (tc_public, B_cmdline_H_flag);
    tcase_add_test (tc_public, B_cmdline_H_flag_and_file);
    suite_add_tcase (s, tc_public);
}

