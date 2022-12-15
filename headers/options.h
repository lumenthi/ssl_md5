#ifndef OPTIONS_H
# define OPTIONS_H

# define OPT_VERBOSE		(1UL << 0)
# define OPT_QUIET			(1UL << 1)
# define OPT_REVERSE		(1UL << 2)

typedef struct		s_msg {
	struct message	*message;
	struct s_msg	*next;
}					t_msg;

#endif
