#include "elf_maker.h"
#include "elf_maker_special_sections.h"
#include <string.h>

int main()
{
  /* elf maker init */
  elf_file_t *elf_file = elf_maker_init();
//  elf_file->header.e_entry = 0x10000;

  /* get sections info */
  SLLInfo *sections_info = (SLLInfo *)elf_file->sections->data;

  /* add null section */
  elf_section_t *null_section = add_null_section(elf_file);

  /* add strings section (can't be the first section)*/
  elf_section_t *strings_section = add_strings_section(elf_file);

  /* add symbol table section */
  elf_section_t *symbol_table_section = add_symbol_table_section(elf_file);

  /* add symbol table strings section */
  elf_section_t *symbol_table_strings_section = add_symbol_table_strings_section(elf_file, symbol_table_section);

  /* add text section*/
  elf_section_t *text_section = add_text_section(elf_file, symbol_table_section, symbol_table_strings_section, 0x10000);

  unsigned char code[] = {0xc7,0x05,0x00,0x80,0x0b,0x00,0x4f,0x2f, 0x4b,0x2f,0xe9,0x74,0x00,0x40,0x00,0xf4};
  elf_maker_add_section_entry(text_section, code, 16);

  /* finalize the string section */
  finalize_strings_section(elf_file, strings_section);

  /* prepare output file */
  FILE *ofile = fopen("output", "w");
  if (!ofile)
  {
    fprintf(stderr, "ERORR: couldn't open output file\n");
    exit(1);
  }

  /* write the elf file*/
  elf_maker_write(elf_file, ofile);

  /*cleanup */
  fclose(ofile);
  elf_maker_free(elf_file);
}
