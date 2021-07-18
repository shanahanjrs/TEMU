#include <stdio.h>
#include "utils.h"

#define arr_len(x) (sizeof(x)/sizeof(x[0]))

#define MEMORYSIZE 64
#define MEMPRNTWIDTH 16

int main()
{
    // These are for debugging
    int max_cycles = 100;
    int cycles = 0;

    int HALT = 0;
    int A = 0;   // A register
    int B = 0;   // B register
    int PC = 0;  // prog counter
    int ZF = 0;  // Zero flag
    int CF = 0;  // Carry flag

    int MEM[MEMORYSIZE] = {0x0};

    /* Programs arent loaded from a file yet */

    // Debugs, sets A to 0xff, then prints A
    //int ROM[] = {0x2, 0x5, 0xA, 0x99, 0x1, 0xff};

    // Debugs, sets A to 0xA, then Mul by 2
    int ROM[] = {0x99, 0x2, 0x8, 0x6, 0x9, 0xA, 0x1, 0x0, 0xA, 0x2};

    // Debug, set A to 255, print out A, loop forever via JMP to the print
    //int ROM[] = {0x99, 0x2, 0x6, 0xA, 0x9, 0x3, 0xff };

    mem_load(arr_len(ROM), 0, MEM, ROM);

    while (!HALT) {
        //printf("Loop: MEM[PC]:: 0x%x\n", MEM[PC]);
        if (cycles >= max_cycles) {
            printf("Max cycles reached.\n");
            return 0;
        }

        switch (MEM[PC]) {
            /*
             * Opcode table
             * done | code     | desc
             * -----------------------------------------------------------------------------
             * [X]  | 0x99     | DBG -> Dump hardware state to console
             * [X]  | 0x0      | NOP -> no op
             * [X]  | 0x1      | HLT -> Halt
             * [X]  | 0x2      | LDA -> load %addr to reg A
             * [X]  | 0x3      | LDB -> load %addr to B
             * [X]  | 0x4      | ADD -> add %addr to A then store in A
             * [X]  | 0x5      | SUB
             * [X]  | 0x6      | MUL
             * [X]  | 0x7      | DIV
             * [X]  | 0x8      | MOV
             * [X]  | 0x9      | JMP -> Set PC to val in %addr
             * [X]  | 0xA      | PRNT -> print A to console
             * [X]  | 0xB      | CMP -> %addr1 < %addr2 :: ZF=0,CF=1
             *                          %addr1 > %addr2 :: ZF=0,CF=0
             *                          %addr1 = %addr2 :: ZF=1,CF=0
             * [X]  | 0xC      | JC -> Jmp if Carry == 1
             * [X]  | 0xD      | JZ -> Jmp if Zero == 1
             */
            case 0x99 : // DBG
            {
                printf("======= Memory: ========\n");
                print_arr(arr_len(MEM), MEMPRNTWIDTH, MEM);
                printf("Reg A :: Hex: 0x%x, Dec:%d\n", A, A); 
                printf("Reg B :: Hex: 0x%x, Dec:%d\n", B, B); 
                printf("Flag ZF :: Hex: 0x%x, Dec:%d\n", ZF, ZF);
                printf("Flag CF :: Hex: 0x%x, Dec:%d\n", CF, CF);
                PC += 1;
                break;
            }

            case 0x0 : // NOP
            {
                PC += 1;
                break;
            }

            case 0x1 : // HLT
            {
                printf("Goodbye.\n");
                HALT = 1;
                break;
            }

            case 0x2 : // LDA
            {
                A = MEM[MEM[PC+1]];
                PC += 2;
                break;
            }

            case 0x3 : // LDB
            {
                B = MEM[MEM[PC+1]];
                PC += 2;
                break;
            }

            case 0x4 : // ADD
            {
                A += MEM[MEM[PC+1]];
                PC += 2;
                break;
            }

            case 0x5 : // SUB
            {
                A -= MEM[MEM[PC+1]];
                PC += 2;
                break;
            }

            case 0x6 : // MUL
            {
                A *= MEM[MEM[PC+1]];
                PC += 2;
                break;
            }

            case 0x7 : // DIV
            {
                A /= MEM[MEM[PC+1]];
                PC += 2;
                break;
            }

            case 0x8 : // MOV
            {
                MEM[MEM[PC+1]] = MEM[MEM[PC+2]];
                PC += 3;
                break;
            }

            case 0x9 : // JMP
            {
                PC = MEM[PC+1];
                break;
            }

            case 0xA : // PRNT
            {
                printf("Register A:: Hex: 0x%x, Dec: %d\n", A, A);
                PC += 1;
                break;
            }

            case 0xB : // CMP
            {
                int val_x = MEM[MEM[PC+1]];
                int val_y = MEM[MEM[PC+2]];
                if (val_x < val_y) {
                    // %addr1 < %addr2 :: ZF=0,CF=1
                    ZF = 0;
                    CF = 1;
                }
                if (val_x > val_y) {
                    // %addr1 > %addr2 :: ZF=0,CF=0
                    ZF = 0;
                    CF = 0;
                }
                if (val_x == val_y) {
                    // %addr1 == %addr2 :: ZF=1,CF=0
                    ZF = 1;
                    CF = 0;
                }
                PC += 3;
                break;
            }

            case 0xC : // JC
            {
                if (CF == 1) PC = MEM[PC+1];
                break;
            }

            case 0xD : // JZ
            {
                if (ZF == 1) PC = MEM[PC+1];
                break;
            }

            default: // ERR
            {
                printf("Unknown opcode 0x%x found. Exiting.\n", MEM[PC]);
                HALT = 1;
                break;
            }
        }

        cycles += 1;
    }


    return 0;
}
