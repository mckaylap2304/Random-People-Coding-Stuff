#include "commands.h"
#include "colors.h"
#include "drivers/keyboard.h"
#include "layouts/kb_layouts.h"
#include "terminal/terminal.h"
#include "comos/comos.h"


// The command table
static Command commands[] = {
    { "help",  cmd_help  },
    { "hello", cmd_hello },
    { "contributors", cmd_contributors},
    { "setkeyswe", cmd_setkeyswe},
    { "setkeyus", cmd_setkeyus},
    { "setkeyuk", cmd_setkeyuk},
    { "clear", cmd_clear },
    { "version", cmd_version },
    { "comos", cmd_comos },
};

static int num_commands = sizeof(commands) / sizeof(commands[0]);

// ---- Command Functions ----

static void cmd_help(uint8_t color) {
    printf("\nhelp   - show this message\n", color);
    printf("hello  - say hello\n", color);
    printf("contributors - Displays names of all contributors\n", color);
    printf("setkeyswe - Sets keyboard layout to Swedish QWERTY\n", color); // Zorx555 - Keyboard layout commands
    printf("setkeyus - Sets keyboard layout to US QWERTY\n", color);
    printf("setkeyuk - Sets keyboard layout to UK QWERTY\n", color); // MorganPG1 - Add UK Keyboard layout
    printf("clear  - clear the screen\n", color); //ember
    printf("version - Version of the operating system\n", color); // TheOtterMonarch - Output version of the OS
    printf("comos  - run the .comos scripting language\n", color);
}

static void cmd_hello(uint8_t color) {
    printf("\nHello, world!\n", color);
}

static void cmd_contributors(uint8_t color) {
    printf("\n--- Contributors ---\n", color);
    printf("Ember2819 - Founder\n", BOLD_COLOR);
    printf("Sifi11\n", color);
    printf("Crim\n", color);
    printf("CheeseFunnel23\n", color);
    printf("bonk enjoyer/dorito girl\n", BOLD_COLOR);
    printf("KaleidoscopeOld5841\n", color);
    printf("billythemoon\n", color);
    printf("TheGirl790\n", color);
    printf("kotofyt\n", color);
    printf("xtn59\n", color);
    printf("c-bass\n", color);
    printf("u/EastConsequence3792\n", color);
    printf("MorganPG1\n", color);
    printf("Zorx555\n", color);
    printf("mckaylap2304\n", color);
    printf("TheOtterMonarch\n", color);
}

static void cmd_setkeyswe(uint8_t color) {
    set_layout(LAYOUTS[1]); // Changed to work with my layout system
    printf("\nKeyboard layout set to Swedish QWERTY\n", color);
}

static void cmd_setkeyus(uint8_t color) {
    set_layout(LAYOUTS[0]); // Changed to work with my layout system
    printf("\nKeyboard layout set to US QWERTY\n", color);
}


static void cmd_setkeyuk(uint8_t color) { // Added by MorganPG1
    set_layout(LAYOUTS[2]); 
    printf("\nKeyboard layout set to UK QWERTY\n", color);
}

static void cmd_clear(uint8_t color) {
    terminal_clear(color);
}

static void cmd_version(uint8_t color) {
    printf("\nCommunity OS v0.5\n", color);
}

//Ember2819,COMOS language 
static ComosState comos_state;

static void cmd_comos(uint8_t color) {
    // Demo program -- runs until FAT32 lets us load .comos files from disk
    static const char* demo =
        "print(\"CommunityOS scripting language (.comos)\")\n"
        "def fib(n):\n"
        "    if n <= 1:\n"
        "        return n\n"
        "    return fib(n - 1) + fib(n - 2)\n"
        "for i in range(8):\n"
        "    print(fib(i))\n";

    comos_init(&comos_state);
    comos_run(&comos_state, demo);
}

// ---- dispatcher ----
static int streq(unsigned char *a, char *b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == *b;
}

void run_command(unsigned char *input, uint8_t color) {
    // Check the input against command table
    for (int i = 0; i < num_commands; i++) {
        if (streq(input, commands[i].name)) {
            commands[i].func(color);
            return;
        }
    }
    printf("\nUnknown command. Type 'help' for available commands\n", color);
}
