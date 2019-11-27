#include "cpu/exec.h"
void raise_intr(uint32_t NO, vaddr_t ret_addr);
make_EHelper(lidt)
{
    cpu.IDTR.len = vaddr_read(id_dest->addr, 2);
    rtl_mv(&cpu.IDTR.head, &id_dest->val);
    print_asm_template1(lidt);
}

make_EHelper(mov_r2cr)
{
    TODO();

    print_asm("movl %%%s,%%cr%d", reg_name(id_src->reg, 4), id_dest->reg);
}

make_EHelper(mov_cr2r)
{
    TODO();

    print_asm("movl %%cr%d,%%%s", id_src->reg, reg_name(id_dest->reg, 4));

    difftest_skip_ref();
}

make_EHelper(int)
{
    raise_intr(id_dest->val, decinfo.seq_pc);
    print_asm("int %s", id_dest->str);

    difftest_skip_dut(1, 2);
}

make_EHelper(iret)
{
    rtl_pop(&cpu.pc);
    rtl_pop(&cpu.cs);
    rtl_pop(&cpu.EFLAGS);
    rtl_j(cpu.pc);

    print_asm("iret");
}

uint32_t pio_read_l(ioaddr_t);
uint32_t pio_read_w(ioaddr_t);
uint32_t pio_read_b(ioaddr_t);
void pio_write_l(ioaddr_t, uint32_t);
void pio_write_w(ioaddr_t, uint32_t);
void pio_write_b(ioaddr_t, uint32_t);

make_EHelper(in)
{
    if (id_src->width == 1) {
        s0 = pio_read_b(id_src->val);
    } else if (id_src->width == 2) {
        s0 = pio_read_w(id_src->val);
    } else {
        s0 = pio_read_l(id_src->val);
    }
    operand_write(id_dest, &s0);
    print_asm_template2(in);
}

make_EHelper(out)
{
    if (id_src->width == 1) {
        pio_write_b(id_dest->val, id_src->val);
    } else if (id_src->width == 2) {
        pio_write_w(id_dest->val, id_src->val);
    } else {
        pio_write_l(id_dest->val, id_src->val);
    }

    print_asm_template2(out);
}