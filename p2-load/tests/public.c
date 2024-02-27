#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <check.h>

#include "../p2-load.h"

/* check basic command line parsing */
START_TEST (C_cmdline_basic)
{
    int argc = 3;
    char *argv[] = { "./y86", "-H", "inputs/simple.o", NULL };
    int rc = 0;
    bool header = false;
    bool segments = false;
    bool membrief = false;
    bool memfull = false;
    char *file = NULL;

    rc = parse_command_line_p2 (argc, argv, &header, &segments,
                                &membrief, &memfull, &file);
    ck_assert (rc);
    ck_assert (header == true);
    ck_assert (segments == false);
    ck_assert (membrief == false);
    ck_assert (memfull == false);
    ck_assert (!strcmp (file, argv[2]));
}
END_TEST

/* check read_phdr (code section) */
START_TEST (C_read_phdr_code)
{
    FILE *fp = fopen ("inputs/stripped.o", "r");
    uint16_t offset = 0x10;
    elf_phdr_t phdr;
    bool rc = false;
    ck_assert (fp != NULL);

    rc = read_phdr (fp, offset, &phdr);
    ck_assert (rc == true);
    ck_assert (phdr.p_offset == 0x38);
    ck_assert (phdr.p_vaddr == 0x100);
    ck_assert (phdr.p_filesz == 0x15);
    ck_assert (phdr.p_type == CODE);
    ck_assert (phdr.p_flag == RX);
    ck_assert (phdr.magic == 0xDEADBEEF);
}
END_TEST

/* check read_phdr (data section) */
START_TEST (C_read_phdr_data)
{
    FILE *fp = fopen ("inputs/stripped.o", "r");
    uint16_t offset = 0x10 + sizeof(elf_phdr_t);
    elf_phdr_t phdr;
    bool rc = false;
    ck_assert (fp != NULL);

    rc = read_phdr (fp, offset, &phdr);
    ck_assert (rc == true);
    ck_assert (phdr.p_offset == 0x4d);
    ck_assert (phdr.p_vaddr == 0x200);
    ck_assert (phdr.p_filesz == 0x0b);
    ck_assert (phdr.p_type == DATA);
    ck_assert (phdr.p_flag == RW);
    ck_assert (phdr.magic == 0xDEADBEEF);
}
END_TEST

/* check load_segment */
START_TEST (C_load_segment)
{
    FILE *fp = fopen ("inputs/simple.o", "r");
    ck_assert (fp != NULL);
    memory_t memory = (memory_t) calloc (32, sizeof (uint8_t));
    elf_phdr_t phdr;
    phdr.p_offset = 0x30;
    phdr.p_vaddr = 0x10;
    phdr.p_filesz = 0x10;
    phdr.p_type = DATA;
    phdr.p_flag = RW;
    phdr.magic = 0xDEADBEEF;
    uint8_t expected[] = { 0, 0, 6, 0, 0xef, 0xbe, 0xad, 0xde,
        0x30, 0xf3, 0xf, 0, 0, 0, 0x20, 0x31 };
    size_t i = 0;

    bool rc = load_segment (fp, memory, phdr);
    ck_assert (rc == true);

    for (i = 0; i < 16; i++) {
        ck_assert (memory[i] == 0);
    }

    for (i = 0; i < 16; i++) {
        ck_assert (memory[i+16] == expected[i]);
    }
}
END_TEST

void public_tests (Suite *s)
{
    TCase *tc_public = tcase_create ("Public");
    tcase_add_test (tc_public, C_cmdline_basic);
    tcase_add_test (tc_public, C_read_phdr_code);
    tcase_add_test (tc_public, C_read_phdr_data);
    tcase_add_test (tc_public, C_load_segment);
    suite_add_tcase (s, tc_public);
}

