#TOBENAMED

---

`<program>.tas` -> **T**iny **AS**sembly file, write code here

`$ ./assembler <program>.tas` -> Compile your program

`$ ./main <program>.bin` -> Run

---

## Opcode table

| done | code     | name | desc |
| ---- | -------- | ---- | ---- |
| - [x]  | 0x99   | DBG | Dump hardware state to console |
| - [x]  | 0x0    | NOP | no op |
| - [x]  | 0x1    | HLT | Halt |
| - [x]  | 0x2    | LDA | load %addr to reg A |
| - [x]  | 0x3    | LDB | load %addr to B |
| - [x]  | 0x4    | ADD | add %addr to A then store in A |
| - [x]  | 0x5    | SUB ||
| - [x]  | 0x6    | MUL ||
| - [x]  | 0x7    | DIV ||
| - [x]  | 0x8    | MOV ||
| - [x]  | 0x9    | JMP | Set PC to val in %addr |
| - [x]  | 0xA    | PRNT| print A to console |
| - [x]  | 0xB    | CMP | %addr1 < %addr2 :: ZF=0,CF=1 <br> %addr1 > %addr2 :: ZF=0,CF=0 <br> %addr1 = %addr2 :: ZF=1,CF=0
| - [x]  | 0xC    | JC | Jmp if Carry == 1 |
| - [x]  | 0xD    | JZ | Jmp if Zero == 1 |