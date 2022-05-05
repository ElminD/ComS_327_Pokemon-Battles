#ifndef IO_H
# define IO_H

class Character;
typedef int16_t pair_t[2];

static void io_display_pokemon();
void io_select_first_pokemon(void);
void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(void);
void io_handle_input(pair_t dest);
void io_queue_message(const char *format, ...);
void io_battle(Character *aggressor, Character *defender);
void io_encounter_pokemon(void);

#endif
