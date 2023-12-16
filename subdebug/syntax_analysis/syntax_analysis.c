
#include "syntax_analysis.h"


void	syntax_pipe(char **cmd_line, int *token, int *i, t_cmd *node)
{
	int	pipe_index;
	int	tmp;

	tmp = i[1];
	pipe_index = find_pipe(token, i);
	node = generate_tree_node(NODE_CMD, pipe_index);
	if (pipe_index != -1)
	{
		i[1] = pipe_index - 1;
		if (i[1] == i[0])
		{
			perror("syntax error near unexpected token '|'\n");
			return ;
		}
	}
	syntax_cmds(cmd_line, token, i, node->left_child);
	if (pipe_index != -1)
	{
		i[0] = pipe_index + 1;
		i[1] = tmp;
		syntax_pipe(cmd_line, token, i, node->right_child);
	}
}

void	syntax_cmds(char **cmd_line, int *token, int *i, t_cmd *node)
{
	int	redirect_index;
	int	tmp;

	tmp = i[1];
	node = generate_tree_node(NODE_REDIRECTS, -1);
	redirect_index = find_redirection(token, i);
	if (redirect_index != -1)
		i[1] = redirect_index - 1;
	if (i[1] == i[0])
	{
		printf("syntax error near unexpected token %c", i[redirect_index]);
		return ;
	}
	syntax_simple_cmd(cmd_line, i, token, node->left_child);
	if (redirect_index != -1)
	{
		i[0] = redirect_index;
		i[1] = tmp;
		syntax_redirects(cmd_line, token, i, node->right_child);
	}
}

void	syntax_simple_cmd(char **cmd_line, int *i, int *token, t_cmd *node)
{
	int		pipe_e;

	pipe_e = find_pipe(token, i);
	node = generate_tree_node(NODE_SIMPLE_CMD, pipe_e);
	node->left_child = generate_end_node(cmd_line, NODE_FILE_PATH, i[0], i[0] + 1);
	node->right_child = generate_end_node(cmd_line, NODE_ARGV, i[0], i[1]);
}

void	syntax_redirects(char **cmd_line, int *token, int *i, t_cmd *node)
{
	int	redirect_index;
	int	tmp;

	tmp = i[1];
	redirect_index = find_redirection(token, i);
	if (redirect_index != -1)
		i[1] = redirect_index;
	syntax_simple_redirect(cmd_line, i, node->left_child);
	if (redirect_index != -1)
	{
		i[0] = redirect_index;
		i[1] = tmp;
		syntax_redirects(cmd_line, token, i, node->right_child);
	}
}

void	syntax_simple_redirect(char **cmd_line, /*int *token,*/ int *i, t_cmd *node)
{
	node = generate_tree_node(NODE_SIMPLE_REDIRECT, -1);
	node->left_child = generate_end_node(cmd_line, NODE_RED_TYPE,
						i[0], i[0] + 1);
	node->right_child = generate_end_node(cmd_line, NODE_FILE_NAME,
						i[0] + 1, i[1]);
}


int main()
{
    t_cmd *tree;

    t_cmd	*cmd_tree;
	char	**chopped_str;
    int     token[5] = {1, 2, 1, 1, 0};
	int		i[2];

	cmd_tree = NULL;
	chopped_str = chopping_str("ls | cat -e");
	if (!chopped_str)
		return (NULL);
    i[0] = 0;
    i[1] = 5;
    syntax_pipe(chopped_str, token, i, cmd_tree);
    
}