#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 10000

typedef struct s_testcase
{
	const char *input;
	const char *expected_output;
	int manual_mode;
	int expected_exit_code;
} t_testcase;

t_testcase tests[] = {
 	{"echo $\"HOME\"", "HOME"},
	{"echo $\"\"", "$"},
	{"echo \"$\"\"\"", "$"},
	{"echo '$'''", "$"},
	{"echo $''HOME", "HOME"},
	{"echo $\"\"HOME", "HOME"},
	{"echo \"$HO\"ME", "ME"},
	{"echo '$HO'ME", "$HOME"},
	{"echo \"$HO\"\"ME\"", "ME"},
	{"echo '$HO''ME'", "$HOME"},
	{"echo \"'$HO''ME'\"", "''ME'"},
	{"echo \"\"$HOME", "/Users/sdossa"},
	{"echo \"\" $HOME", " /Users/sdossa"},
	{"echo ''$HOME", "/Users/sdossa"},
	{"echo '' $HOME", " /Users/sdossa"},
	{"echo $\"HO\"\"ME\"", "HOME"},
	{"echo $'HO''ME'", "HOME"},
	{"echo $'HOME'", "HOME"},
	{"echo \"$\"HOME", "$HOME"},
	{"echo $=HOME", "$=HOME"},
	{"echo $\"HOLA\"", "HOLA"},
	{"echo $'HOLA'", "HOLA"},
	{"echo $DONTEXIST Hola", "Hola"},
	{"echo \"hola\"", "hola"},
	{"echo 'hola'", "hola"},
	{"echo ''hola''", "hola"},
	{"echo ''h'o'la''", "hola"},
	{"echo \"''h'o'la''\"", "''h'o'la''"},
	{"echo \"'\"h'o'la\"'\"", "'hola'"},
	{"echo\"'hola'\"", "minishell: echo'hola': command not found"},
	{"echo \"'hola'\"", "'hola'"},
	{"echo '\"hola\"'", "\"hola\""},
	{"echo '''ho\"''''l\"a'''", "ho\"l\"a"},
	{"echo hola\"\"\"\"\"\"\"\"\"\"", "hola"},
	{"echo hola\"''''''''''\"", "hola''''''''''"},
	{"echo hola''''''''''''", "hola"},
	{"echo hola'\"\"\"\"\"\"\"\"\"\"'", "hola\"\"\"\"\"\"\"\"\"\""},
	{"\"e\"'c'ho 'b'\"o\"nj\"o\"'u'r", "bonjour"},
	{"\"\"e\"'c'ho 'b'\"o\"nj\"o\"'u'r\"", "bash: e'c'ho 'b'onjo'u'r: command not found"},
	{"echo \"$DONTEXIST\"Makefile", "Makefile"},
	{"echo \"$DONTEXIST\"\"Makefile\"", "Makefile"},
	{"echo \"$DONTEXIST\" \"Makefile\"", "Makefile"},
	{"echo $?", "minishell: echo bonjour: command not found"},
	{"echo $?$?", "minishell: echo bonjour: command not found"},
	{"?$HOME", "?/Users/sdossa: No such file or directory"},
	{"$", "minishell: $: command not found"},
	{"$HOME", "minishell: /Users/sdossa: is a directory"},
	{"$HOMEdskjhfkdshfsd", ""},
	{"\"$HOMEdskjhfkdshfsd\"", "minishell: $HOMEdskjhfkdshfsd: command not found"},
	{"'$HOMEdskjhfkdshfsd'", "minishell: $HOMEdskjhfkdshfsd: command not found"},
	{"$DONTEXIST", ""},
	{"$LESS$VAR", ""},
	{"env | grep SHLVL=3", "SHLVL=3"},
	{"env hola", "env: hola: No such file or directory"},
	{"env hola que tal", "env: holaminishell: No such file or directory"},
	{"export       HOLA=bonjour", "env: holaminishell: No such file or directory"},
	{"export \"\"" ,  "minishell: export: `': not a valid identifier"},
	{"export =" ,  "minishell: export: `': not a valid identifier"},
	{"export %" ,  "minishell: export: `': not a valid identifier"},
	{"export $?" ,  "minishell: export: `': not a valid identifier"},
	{"export 9HOLA=" ,  "minishell: export: `': not a valid identifier"},
	{"export HOL@=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HOL\\~A=bonjourr", "minishell: export: `': not a valid identifier"},
	{"export -HOLA=bonjour", "minishell: export: `-H': invalid optiohn"},
	{"export --HOLA=bonjour", "minishell: export: `--: invalid option"},
	{"export HOLA-=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HO-LA=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HOL.A=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HOL\\\\\\$A=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HO\\\\\\LA=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HOL}A=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HOL{A=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HO*LA=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HO#LA=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HO@LA=bonjour", "minishell: export: `': not a valid identifier"},
	{"export +HOLA=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HOL+A=bonjour", "minishell: export: `': not a valid identifier"},
	{"export HOLA = bonjour", "minishell: export: `': not a valid identifier"},
	{"export HO\\\\\\LA=bonjour", "minishell: export: `': not a valid identifier"},
	{"export | grep HOLA", "declare -x HOLA=\"bonjour\""},
	{"export HOLA=\"cat Makefile | grep NAME\"", "Makefile"},
	{"export HOLA=key", ""},
	{"echo $HOLA$HOLA$HOLA=hey$HOLA", "keykeykey=heykey"},
	{"export HOLA=\"  bonjour  hey  \"", "HOLA=  bonjour  hey"},
	{"env | grep HOLA", "HOLA=bonjour"},
	{"export HOLA2", ""},
	{"export | grep HOLA2", "declare -x HOLA2"},
	{NULL, NULL}};


void trim_newline(char *s)
{
	char *p = strchr(s, '\n');
	if (p)
		*p = '\0';
}

int main(void)
{
	char buf[BUF_SIZE];

	for (int i = 0; tests[i].input != NULL; i++)
	{
		const char *cmd = tests[i].input;
		const char *expected = tests[i].expected_output;
		char bash_out[BUF_SIZE] = {0};
		char mini_out[BUF_SIZE] = {0};

		// BASH
		char bash_cmd[1024];
		snprintf(bash_cmd, sizeof(bash_cmd), "/bin/bash -c '%s'", cmd);
		FILE *bash_fp = popen(bash_cmd, "r");
		if (!bash_fp)
		{
			perror("bash");
			exit(1);
		}
		bash_out[0] = '\0';
		while (fgets(buf, sizeof(buf), bash_fp))
		{
			trim_newline(buf);
			if (bash_out[0])
				strcat(bash_out, " ");
			strcat(bash_out, buf);
		}

		int bash_status = pclose(bash_fp);
		int bash_exit_code = WEXITSTATUS(bash_status);

		char mini_cmd[1024];
		char exit_icmd[1024];
		//snprintf(mini_cmd, sizeof(mini_cmd), "echo '%s' | ./minishell", cmd);
		snprintf(mini_cmd, sizeof(mini_cmd), "echo '%s' | valgrind --leak-check=full --suppressions=readline.supp --show-leak-kinds=all ./minishell", cmd);
		FILE *mini_fp = popen(mini_cmd, "r");
		if (!mini_fp)
		{
			perror("minishell");
			exit(1);
		}
		mini_out[0] = '\0';
		while (fgets(buf, sizeof(buf), mini_fp))
		{
			trim_newline(buf);
			if (
				buf[0] == '\0' ||
				strncmp(buf, "minishell", 9) == 0 ||
				strncmp(buf, "🔧", 3) == 0 ||
				strncmp(buf, "✅", 3) == 0 ||
				strncmp(buf, "🧩", 3) == 0 ||
				strncmp(buf, "  [tok", 6) == 0 ||
				strncmp(buf, "  [ext", 6) == 0 ||
				strstr(buf, "[group") != NULL ||
				strstr(buf, "[tok") != NULL ||
				strstr(buf, "[ext") != NULL ||
				strstr(buf, "merge $'string' →") || // 👈
				strstr(buf, "merge $''string (ignore empty)") != NULL)
				continue;

			if (mini_out[0])
				strcat(mini_out, " ");
			strcat(mini_out, buf);
		}
		int mini_status = pclose(mini_fp);
		int mini_exit_code = WEXITSTATUS(mini_status);
		printf("[%02d] %-30s ... ", i + 1, cmd);
		if ((strcmp(bash_out, mini_out) == 0
		|| strcmp(mini_out, expected) == 0
		&& bash_exit_code == mini_exit_code)
		|| tests[i].manual_mode)
		{
			printf("✅ OK\n");
			//printf("     Bash     : [%s]\n", bash_out);
			//printf("     Minishell: [%s]\n", mini_out);
			//printf("     Expected : [%s]\n", expected);
			printf("     Mini exit : [%d]\n", mini_exit_code);
			printf("     Bash exit : [%d]\n", bash_exit_code);
		}
		else
		{
			printf("❌ FAIL\n");
			printf("     Bash     : [%s]\n", bash_out);
			printf("     Minishell: [%s]\n", mini_out);
			printf("     Expected : [%s]\n", expected);
			printf("     Mini exit : [%d]\n", mini_exit_code);
			printf("     Bash exit : [%d]\n", bash_exit_code);
		}
	}

	return 0;
}
