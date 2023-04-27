#define _POSIX_C_SOURCE 1
#include <error.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct {
    const char* instruction;
    size_t size;
} Op;

Op Disassemble(uint8_t opcode) {
    Op op;
    op.size = 1;
    op.instruction = "NOP";
    switch (opcode) {
        case 0x00:
            op.instruction = "NOP";
            break;
        case 0x01:
            op.instruction = "LXI\tB,%02x%02x";
            op.size = 3;
            break;
        case 0x02:
            op.instruction = "STAX\tB";
            break;
        case 0x03:
            op.instruction = "INX\tB";
            break;
        case 0x04:
            op.instruction = "INR\tB";
            break;
        case 0x05:
            op.instruction = "DCR\tB";
            break;
        case 0x06:
            op.instruction = "MVI\tB,%02x";
            op.size = 2;
            break;
        case 0x07:
            op.instruction = "RLC";
            break;
        case 0x08:
            op.instruction = "NOP";
            break;
        case 0x09:
            op.instruction = "DAD\tB";
            break;
        case 0x0A:
            op.instruction = "LDAX\tB";
            break;
        case 0x0B:
            op.instruction = "DCX\tB";
            break;
        case 0x0C:
            op.instruction = "INR\tC";
            break;
        case 0x0D:
            op.instruction = "DCR\tC";
            break;
        case 0x0E:
            op.instruction = "MVI\tC,%02x";
            op.size = 2;
            break;
        case 0x0F:
            op.instruction = "RRC";
            break;

        case 0x10:
            break;
        case 0x11:
            op.instruction = "LXI\tD,%02x%02x";
            op.size = 3;
            break;
        case 0x12:
            op.instruction = "STAX\tD";
            break;
        case 0x13:
            op.instruction = "INX\tD";
            break;
        case 0x14:
            op.instruction = "INR\tD";
            break;
        case 0x15:
            op.instruction = "DCR\tD";
            break;
        case 0x16:
            op.instruction = "MVI\tD,%02x";
            op.size = 2;
            break;
        case 0x17:
            op.instruction = "RAL";
            break;
        case 0x18:
            op.instruction = "NOP";
            break;
        case 0x19:
            op.instruction = "DAD\tD";
            break;

        case 0x1a:
            op.instruction = "LDAX\tD";
            break;
        case 0x1b:
            op.instruction = "DCX\tD";
            break;
        case 0x1c:
            op.instruction = "INR\tE";
            break;
        case 0x1d:
            op.instruction = "DCR\tE";
            break;
        case 0x1e:
            op.instruction = "MVI\tE,%02x";
            op.size = 2;
            break;
        case 0x1f:
            op.instruction = "RAR";
            break;

        case 0x20:
            /* This is RIM on 8085 systems ...
             * undefined, but functionally "NOP" on 8080 */
            op.instruction = "RIM";
            break;
        case 0x21:
            op.instruction = "LXI\tH,%02x%02x";
            op.size = 3;
            break;
        case 0x22:
            op.instruction = "SHLD\t%02x%02x";
            op.size = 3;
            break;
        case 0x23:
            op.instruction = "INX\tH";
            break;
        case 0x24:
            op.instruction = "INR\tH";
            break;
        case 0x25:
            op.instruction = "DCR\tH";
            break;
        case 0x26:
            op.instruction = "MVI\tH,%02x";
            op.size = 2;
            break;
        case 0x27:
            op.instruction = "DAA";
            break;
        case 0x28:
            /* empty instruction */
            op.instruction = "NOP";
            break;
        case 0x29:
            op.instruction = "DAD\tH";
            break;
        case 0x2a:
            op.instruction = "LHLD\t%02x%02x";
            op.size = 3;
            break;
        case 0x2b:
            op.instruction = "DCX\tH";
            break;
        case 0x2c:
            op.instruction = "INR\tL";
            break;
        case 0x2d:
            op.instruction = "DCR\tL";
            break;
        case 0x2e:
            op.instruction = "MVI\tL,%02x";
            op.size = 2;
            break;
        case 0x2f:
            /* accumulator complement */
            op.instruction = "CMA";
            break;

        case 0x30:
            /* SIM instruction on 8085;
             * undefined in 8080 */
            op.instruction = "SIM";
            break;
        case 0x31:
            op.instruction = "LXI\tSP,%02x%02x";
            op.size = 3;
            break;
        case 0x32:
            op.instruction = "STA\t%02x%02x";
            op.size = 3;
            break;
        case 0x33:
            op.instruction = "INX\tSP";
            break;
        case 0x34:
            op.instruction = "INR\tM";
            break;
        case 0x35:
            op.instruction = "DCR\tM";
            break;
        case 0x36:
            op.instruction = "MVI\tM,%02x";
            op.size = 2;
            break;
        case 0x37:
            op.instruction = "STC";
            break;
        case 0x38:
            /* no instruction */
            op.instruction = "NOP";
            break;
        case 0x39:
            op.instruction = "DAD\tSP";
            break;
        case 0x3a:
            op.instruction = "LDA\t%02x%02x";
            op.size = 3;
            break;
        case 0x3b:
            op.instruction = "DCX\tSP";
            break;
        case 0x3c:
            op.instruction = "INR\tA";
            break;
        case 0x3d:
            op.instruction = "DCR\tA";
            break;
        case 0x3e:
            op.instruction = "MVI\tA,%02x";
            op.size = 2;
            break;
        case 0x3f:
            op.instruction = "CMC";
            break;

        case 0x40:
            op.instruction = "MOV\tB,B";
            break;
        case 0x41:
            op.instruction = "MOV\tB,C";
            break;
        case 0x42:
            op.instruction = "MOV\tB,D";
            break;
        case 0x43:
            op.instruction = "MOV\tB,E";
            break;
        case 0x44:
            op.instruction = "MOV\tB,H";
            break;
        case 0x45:
            op.instruction = "MOV\tB,L";
            break;
        case 0x46:
            op.instruction = "MOV\tB,M";
            break;
        case 0x47:
            op.instruction = "MOV\tB,A";
            break;
        case 0x48:
            op.instruction = "MOV\tC,B";
            break;
        case 0x49:
            op.instruction = "MOV\tC,C";
            break;
        case 0x4a:
            op.instruction = "MOV\tC,D";
            break;
        case 0x4b:
            op.instruction = "MOV\tC,E";
            break;
        case 0x4c:
            op.instruction = "MOV\tC,H";
            break;
        case 0x4d:
            op.instruction = "MOV\tC,L";
            break;
        case 0x4e:
            op.instruction = "MOV\tC,M";
            break;
        case 0x4f:
            op.instruction = "MOV\tC,A";
            break;

        case 0x50:
            op.instruction = "MOV\tD,B";
            break;
        case 0x51:
            op.instruction = "MOV\tD,C";
            break;
        case 0x52:
            op.instruction = "MOV\tD,D";
            break;
        case 0x53:
            op.instruction = "MOV\tD,E";
            break;
        case 0x54:
            op.instruction = "MOV\tD,H";
            break;
        case 0x55:
            op.instruction = "MOV\tD,L";
            break;
        case 0x56:
            op.instruction = "MOV\tD,M";
            break;
        case 0x57:
            op.instruction = "MOV\tD,A";
            break;
        case 0x58:
            op.instruction = "MOV\tE,B";
            break;
        case 0x59:
            op.instruction = "MOV\tE,C";
            break;
        case 0x5a:
            op.instruction = "MOV\tE,D";
            break;
        case 0x5b:
            op.instruction = "MOV\tE,E";
            break;
        case 0x5c:
            op.instruction = "MOV\tE,H";
            break;
        case 0x5d:
            op.instruction = "MOV\tE,L";
            break;
        case 0x5e:
            op.instruction = "MOV\tE,M";
            break;
        case 0x5f:
            op.instruction = "MOV\tE,A";
            break;

        case 0x60:
            op.instruction = "MOV\tH,B";
            break;
        case 0x61:
            op.instruction = "MOV\tH,C";
            break;
        case 0x62:
            op.instruction = "MOV\tH,D";
            break;
        case 0x63:
            op.instruction = "MOV\tH,E";
            break;
        case 0x64:
            op.instruction = "MOV\tH,H";
            break;
        case 0x65:
            op.instruction = "MOV\tH,L";
            break;
        case 0x66:
            op.instruction = "MOV\tH,M";
            break;
        case 0x67:
            op.instruction = "MOV\tH,A";
            break;
        case 0x68:
            op.instruction = "MOV\tL,B";
            break;
        case 0x69:
            op.instruction = "MOV\tL,C";
            break;
        case 0x6a:
            op.instruction = "MOV\tL,D";
            break;
        case 0x6b:
            op.instruction = "MOV\tL,E";
            break;
        case 0x6c:
            op.instruction = "MOV\tL,H";
            break;
        case 0x6d:
            op.instruction = "MOV\tL,L";
            break;
        case 0x6e:
            op.instruction = "MOV\tL,M";
            break;
        case 0x6f:
            op.instruction = "MOV\tL,A";
            break;

        case 0x70:
            op.instruction = "MOV\tM,B";
            break;
        case 0x71:
            op.instruction = "MOV\tM,C";
            break;
        case 0x72:
            op.instruction = "MOV\tM,D";
            break;
        case 0x73:
            op.instruction = "MOV\tM,E";
            break;
        case 0x74:
            op.instruction = "MOV\tM,H";
            break;
        case 0x75:
            op.instruction = "MOV\tM,L";
            break;
        case 0x76:
            /* halt instruction */
            op.instruction = "HLT";
            break;
        case 0x77:
            op.instruction = "MOV\tM,A";
            break;
        case 0x78:
            op.instruction = "MOV\tA,B";
            break;
        case 0x79:
            op.instruction = "MOV\tA,C";
            break;
        case 0x7a:
            op.instruction = "MOV\tA,D";
            break;
        case 0x7b:
            op.instruction = "MOV\tA,E";
            break;
        case 0x7c:
            op.instruction = "MOV\tA,H";
            break;
        case 0x7d:
            op.instruction = "MOV\tA,L";
            break;
        case 0x7e:
            op.instruction = "MOV\tA,M";
            break;
        case 0x7f:
            op.instruction = "MOV\tA,A";
            break;

        case 0x80:
            op.instruction = "ADD\tB";
            break;
        case 0x81:
            op.instruction = "ADD\tC";
            break;
        case 0x82:
            op.instruction = "ADD\tD";
            break;
        case 0x83:
            op.instruction = "ADD\tE";
            break;
        case 0x84:
            op.instruction = "ADD\tH";
            break;
        case 0x85:
            op.instruction = "ADD\tL";
            break;
        case 0x86:
            op.instruction = "ADD\tM";
            break;
        case 0x87:
            op.instruction = "ADD\tA";
            break;
        case 0x88:
            op.instruction = "ADC\tB";
            break;
        case 0x89:
            op.instruction = "ADC\tC";
            break;
        case 0x8a:
            op.instruction = "ADC\tD";
            break;
        case 0x8b:
            op.instruction = "ADC\tE";
            break;
        case 0x8c:
            op.instruction = "ADC\tH";
            break;
        case 0x8d:
            op.instruction = "ADC\tL";
            break;
        case 0x8e:
            op.instruction = "ADC\tM";
            break;
        case 0x8f:
            op.instruction = "ADC\tA";
            break;

        case 0x90:
            op.instruction = "SUB\tB";
            break;
        case 0x91:
            op.instruction = "SUB\tC";
            break;
        case 0x92:
            op.instruction = "SUB\tD";
            break;
        case 0x93:
            op.instruction = "SUB\tE";
            break;
        case 0x94:
            op.instruction = "SUB\tH";
            break;
        case 0x95:
            op.instruction = "SUB\tL";
            break;
        case 0x96:
            op.instruction = "SUB\tM";
            break;
        case 0x97:
            op.instruction = "SUB\tA";
            break;
        case 0x98:
            op.instruction = "SBB\tB";
            break;
        case 0x99:
            op.instruction = "SBB\tC";
            break;
        case 0x9a:
            op.instruction = "SBB\tD";
            break;
        case 0x9b:
            op.instruction = "SBB\tE";
            break;
        case 0x9c:
            op.instruction = "SBB\tH";
            break;
        case 0x9d:
            op.instruction = "SBB\tL";
            break;
        case 0x9e:
            op.instruction = "SBB\tM";
            break;
        case 0x9f:
            op.instruction = "SBB\tA";
            break;

        case 0xa0:
            op.instruction = "ANA\tB";
            break;
        case 0xa1:
            op.instruction = "ANA\tC";
            break;
        case 0xa2:
            op.instruction = "ANA\tD";
            break;
        case 0xa3:
            op.instruction = "ANA\tE";
            break;
        case 0xa4:
            op.instruction = "ANA\tH";
            break;
        case 0xa5:
            op.instruction = "ANA\tL";
            break;
        case 0xa6:
            op.instruction = "ANA\tM";
            break;
        case 0xa7:
            op.instruction = "ANA\tA";
            break;
        case 0xa8:
            op.instruction = "XRA\tB";
            break;
        case 0xa9:
            op.instruction = "XRA\tC";
            break;
        case 0xaa:
            op.instruction = "XRA\tD";
            break;
        case 0xab:
            op.instruction = "XRA\tE";
            break;
        case 0xac:
            op.instruction = "XRA\tH";
            break;
        case 0xad:
            op.instruction = "XRA\tL";
            break;
        case 0xae:
            op.instruction = "XRA\tM";
            break;
        case 0xaf:
            op.instruction = "XRA\tA";
            break;

        case 0xb0:
            op.instruction = "ORA\tB";
            break;
        case 0xb1:
            op.instruction = "ORA\tC";
            break;
        case 0xb2:
            op.instruction = "ORA\tD";
            break;
        case 0xb3:
            op.instruction = "ORA\tE";
            break;
        case 0xb4:
            op.instruction = "ORA\tH";
            break;
        case 0xb5:
            op.instruction = "ORA\tL";
            break;
        case 0xb6:
            op.instruction = "ORA\tM";
            break;
        case 0xb7:
            op.instruction = "ORA\tA";
            break;
        case 0xb8:
            op.instruction = "CMP\tB";
            break;
        case 0xb9:
            op.instruction = "CMP\tC";
            break;
        case 0xba:
            op.instruction = "CMP\tD";
            break;
        case 0xbb:
            op.instruction = "CMP\tE";
            break;
        case 0xbc:
            op.instruction = "CMP\tH";
            break;
        case 0xbd:
            op.instruction = "CMP\tL";
            break;
        case 0xbe:
            op.instruction = "CMP\tM";
            break;
        case 0xbf:
            op.instruction = "CMP\tA";
            break;

        case 0xc0:
            /* return if not zero */
            op.instruction = "RNZ";
            break;
        case 0xc1:
            op.instruction = "POP\tB";
            break;
        case 0xc2:
            /* jump if not zero */
            op.instruction = "JNZ\t%02x%02x";
            op.size = 3;
            break;
        case 0xc3:
            op.instruction = "JMP\t%02x%02x";
            op.size = 3;
            break;
        case 0xc4:
            /* call if not zero */
            op.instruction = "CNZ\t%02x%02x";
            op.size = 3;
            break;
        case 0xc5:
            op.instruction = "PUSH\tB";
            break;
        case 0xc6:
            /* immediate add */
            op.instruction = "ADI\t%02x";
            op.size = 2;
            break;
        case 0xc7:
            op.instruction = "RST\t0";
            break;
        case 0xc8:
            /* if zero, return */
            op.instruction = "RZ";
            break;
        case 0xc9:
            /* pop the address off the stack, assign to program counter */
            op.instruction = "RET";
            break;
        case 0xca:
            op.instruction = "JZ\t%02x%02x";
            op.size = 3;
            break;
        case 0xcb:
            op.instruction = "NOP";
            /* blank instruction */
            break;
        case 0xcc:
            op.instruction = "CZ\t%02x%02x";
            op.size = 3;
            break;
        case 0xcd:
            op.instruction = "CALL\t%02x%02x";
            op.size = 3;
            break;
        case 0xce:
            op.instruction = "ACI\t%02x";
            op.size = 2;
            break;
        case 0xcf:
            op.instruction = "RST\t1";
            break;

        case 0xd0:
            /* if no carry, return */
            op.instruction = "RNC";
            break;
        case 0xd1:
            op.instruction = "POP\tD";
            break;
        case 0xd2:
            op.instruction = "JNC\t%02x%02x";
            op.size = 3;
            break;
        case 0xd3:
            /* send contents of Accumulator to Output Device #{Byte} */
            op.instruction = "OUT\t%02x";
            op.size = 2;
            break;
        case 0xd4:
            /* if no carry, call */
            op.instruction = "CNC\t%02x%02x";
            op.size = 3;
            break;
        case 0xd5:
            op.instruction = "PUSH\tD";
            break;
        case 0xd6:
            /* immediate subtract */
            op.instruction = "SUI\t%02x";
            op.size = 2;
            break;
        case 0xd7:
            op.instruction = "RST\t2";
            break;
        case 0xd8:
            /* if carry, return */
            op.instruction = "RC";
            break;
        case 0xd9:
            op.instruction = "NOP";
            /* blank instruction */
            break;
        case 0xda:
            op.instruction = "JC\t%02x%02x";
            op.size = 3;
            break;
        case 0xdb:
            /* read 8 bits of data from Input Device ${Byte} into Accumulator */
            op.instruction = "IN\t%02x";
            op.size = 2;
            break;
        case 0xdc:
            op.instruction = "CC\t%02x%02x";
            op.size = 3;
            break;
        case 0xdd:
            op.instruction = "NOP";
            /* blank instruction */
            break;
        case 0xde:
            /* immediate subtraction with carry */
            op.instruction = "SBI\t%02x";
            op.size = 2;
            break;
        case 0xdf:
            op.instruction = "RST\t3";
            break;
        case 0xe0:
            /* if PO, return */
            op.instruction = "RPO";
            break;
        case 0xe1:
            op.instruction = "POP\tH";
            break;
        case 0xe2:
            op.instruction = "JPO\t%02x%02x";
            op.size = 3;
            break;
        case 0xe3:
            /* exchange stack with the contents of H/L */
            op.instruction = "XTHL";
            break;
        case 0xe4:
            op.instruction = "CPO\t%02x%02x";
            op.size = 3;
            break;
        case 0xe5:
            op.instruction = "PUSH\tH";
            break;
        case 0xe6:
            op.instruction = "ANI\t%02x";
            op.size = 2;
            break;
        case 0xe7:
            op.instruction = "RST\t4";
            break;
        case 0xe8:
            op.instruction = "RPE";
            break;
        case 0xe9:
            op.instruction = "PCHL";
            break;
        case 0xea:
            op.instruction = "JPE\t%02x%02x";
            op.size = 3;
            break;
        case 0xeb:
            op.instruction = "XCHG";
            break;
        case 0xec:
            op.instruction = "CPE\t%02x%02x";
            op.size = 3;
            break;
        case 0xed:
            op.instruction = "NOP";
            /* blank instruction */
            break;
        case 0xee:
            /* immediate xor */
            op.instruction = "XRI\t%02x";
            op.size = 2;
            break;
        case 0xef:
            op.instruction = "RST\t5";
            break;

        case 0xf0:
            /* if P, return */
            op.instruction = "RP";
            break;
        case 0xf1:
            op.instruction = "POP\tPSW";
            break;
        case 0xf2:
            op.instruction = "JP\t%02x%02x";
            op.size = 3;
            break;
        case 0xf3:
            op.instruction = "DI";
            break;
        case 0xf4:
            op.instruction = "CP\t%02x%02x";
            op.size = 3;
            break;
        case 0xf5:
            op.instruction = "PUSH\tPSW";
            break;
        case 0xf6:
            /* immediate or */
            op.instruction = "ORI\t%02x";
            op.size = 2;
            break;
        case 0xf7:
            op.instruction = "RST\t6";
            break;
        case 0xf8:
            /* if M, return */
            op.instruction = "RM";
            break;
        case 0xf9:
            op.instruction = "SPHL";
            break;
        case 0xfa:
            op.instruction = "JM\t%02x%02x";
            op.size = 3;
            break;
        case 0xfb:
            op.instruction = "EI";
            break;
        case 0xfc:
            op.instruction = "CM\t%02x%02x";
            op.size = 3;
            break;
        case 0xfd:
            op.instruction = "NOP";
            /* blank instruction */
            break;
        case 0xfe:
            op.instruction = "CPI\t%02x";
            op.size = 2;
            break;
        case 0xff:
            op.instruction = "RST\t7";
            break;
    }
    return op;
}

#define BUF_SIZE 10000
int main(int argc, char** argv)
{
    char* program_name = *argv++;
    if (argc < 2) {
        fprintf(stderr, "%s: missing argument\n", program_name);
        exit(EXIT_FAILURE);
    }
    if (argc > 2) {
        fprintf(stderr, "%s: too many arguments\n", program_name);
        exit(EXIT_FAILURE);
    }
    FILE* asmb = fopen(*argv, "r");
    if (!asmb) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    struct stat sb;
    if (fstat(fileno(asmb), &sb) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }
    /* allocate a string big enough to fit the entire file */
    uint8_t* buf = malloc(sb.st_size);
    fread(buf, 1, sb.st_size, asmb);
    if (ferror(asmb)) {
        perror("fread");
        exit(EXIT_FAILURE);
    }
    /* buffer is now full; file is read */
    /* file can now be closed */
    fclose(asmb);

    /* now it's time to do our disassembly */
    uint8_t* bufp = buf;
    size_t count;
    while ((count = bufp - buf) < sb.st_size) {
        Op op = Disassemble(*bufp);
        uint8_t a, b;
        /* count the current hex byte */
        printf("%04lx: ", count);
        switch (op.size) {
            case 1:
                printf("%s", op.instruction);
                break;
            case 2:
                if (count + 1 >= sb.st_size) {
                    goto malformed_error;
                }
                a = *++bufp;
                printf(op.instruction, a);
                break;
            case 3:
                if (count + 2 >= sb.st_size) {
                    goto malformed_error;
                }
                a = *++bufp;
                b = *++bufp;
                printf(op.instruction, a, b);
                break;
        }
        printf("\n");
        ++bufp;
    }

    free(buf);
    exit(EXIT_SUCCESS);

    malformed_error:
    fprintf(stderr, "%s: malformed bytecode at byte 0x%lx\n", program_name, count);
    fprintf(stderr, "%s: aborting disassembly\n", program_name);
    exit(EXIT_FAILURE);
}
