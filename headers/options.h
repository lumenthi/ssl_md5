#ifndef OPTIONS_H
# define OPTIONS_H

# define OPT_VERBOSE		(1UL << 0)

typedef struct		s_msg {
	struct message	*message;
	struct s_msg	*next;
}					t_msg;

#endif
