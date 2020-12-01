/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anatashi <anatashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 20:13:18 by skarry            #+#    #+#             */
/*   Updated: 2020/12/01 21:36:40 by anatashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <string.h>
# include <signal.h>

# define _DEF_	"\x1B[0m"
# define _RED_	"\x1B[31m"
# define _GRN_	"\x1B[32m"
# define _YEL_	"\x1B[33m"
# define _BLU_	"\x1B[34m"
# define _MAG_	"\x1B[35m"
# define _CYN_	"\x1B[36m"
# define _WHT_	"\x1B[37m"
# define BOLD	"\033[1m"

int g_status51;

typedef	struct			s_commands
{
	char				*cmd;
	char				*cmd_dir;
	char				**arg;
	int					dir_find;
	int					type_redir;
	int					invalid;
	struct s_commands	*redir;
	struct s_commands	*pipe;
	struct s_commands	*next;
}						t_commands;

typedef	struct			s_data
{
	int					fd1;
	int					fd0;
	char				*error;
	char				**arg;
	char				**env;
	char				*home_dir;
	int					env_home_dir;
	int					env_dir_i;
	int					env_old_dir_i;
	int					env_path_i;
	char				*file_dir;
}						t_data;

void					wait_str(t_data *all, char **line);
t_commands				*create_lst(char *line, t_data *all);
void					add_lst(char *line, t_commands *s_point,
						size_t pointd, t_data *all);
char					**line_to_mas(char *line, int *er, t_data *all);
size_t					skip_space(char *s);
void					free_cmd(t_commands *cmd);
char					*get_word(char **line, int *er, t_data *all);
void					write_data(t_commands *s_point, size_t *point,
						char *line, t_data *all);
void					record_redir(t_commands *cmd, t_data *all);
int						ft_creat_env(t_data *all, char **env);
void					ft_parse_env(t_data *all);
int						give_directory(t_commands *lst, t_data *all);
int						give_variable(char **env, char *var);
char					*re_malloc(char c, char *w);
char					*ft_strzero(char *str);
char					**ft_strdup_msv(char **str);
int						ft_strlen_msv(char **str);
int						ft_compare_str(char *s1, char *s2);
char					**free_msv(char **str);
int						ft_start (t_commands *cmd, t_data *all);
void					ft_give_pwd(t_commands *cmd);
void					ft_give_env(t_data *all);
int						ft_give_export(t_commands *cmd, t_data *all);
int						ft_give_unset(t_commands *cmd, t_data *all);
int						ft_give_command(t_commands *cmd, t_data *all);
int						ft_give_cd(t_commands *cmd, t_data *all);
int						ft_give_echo(t_data *all, t_commands *cmd);
int						ft_str_check(char *str, char **arg);
void					ft_init_struct(t_data *all);
char					**ft_str_replace(char **env, int i, int g);
int						ft_strcmp(char *s1, char *s2);
void					do_cmd(t_commands *cmd, t_data *all);
void					ft_putstr(char *str);
int						ft_str_check_uns(char *str, char **arg);
int						ft_supercheck_arg(char *arg);
void					ft_signal(int sig);
void					ft_signal_quit(int sig);
void					pipe_end(t_commands *pip, t_data *all,
						int fd0, int fd1);
int						redirects(t_commands *redir);
int						ft_str_check_exp(t_data *all, char **env, char *arg);
size_t					find_end_cmd(char *s, size_t *end_cmd, char **line2);
void					record_mas_to_mas(char ***m1, char **m2, int start);
int						if_basesim(char *line, int i, t_data *all, char **w);
int						if_dollar(char *line, t_data *all, char **w);
void					ft_exit(t_commands *cmd, t_data *all, t_commands *pip);
void					ft_malloc_error(void);
void					ft_give_exportss(t_commands *cmd, t_data *all, int i);
int						ft_find_equally(char *str, char *str2);
int						ft_fin_check(char **arg);
int						ft_utils_check(t_data *all, char *arg);
void					ft_give_tilda(t_commands *cmd, t_data *all);

#endif
