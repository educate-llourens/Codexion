/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_tests.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lelouren <lelouren@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/10/13 17:37:53 by lelouren      #+#    #+#                 */
/*   Updated: 2026/10/19 14:56:43 by lelouren      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

/*
** Expected argument order (subject, chapter V):
** [0] number_of_coders          [4] time_to_refactor
** [1] time_to_burnout           [5] number_of_compiles_required
** [2] time_to_compile           [6] dongle_cooldown
** [3] time_to_debug             [7] scheduler (exactly "fifo" or "edf")
*/

static int	g_run;
static int	g_failed;

static void	expect(const char *name, int got, int want)
{
	g_run++;
	if (got == want)
		printf("[ OK ] %s\n", name);
	else
	{
		printf("[FAIL] %s (got %d, want %d)\n", name, got, want);
		g_failed++;
	}
}

static void	fill(char **list)
{
	list[0] = "5";
	list[1] = "800";
	list[2] = "200";
	list[3] = "200";
	list[4] = "200";
	list[5] = "3";
	list[6] = "10";
	list[7] = "fifo";
	list[8] = NULL;
}

/* ---------------------------- check_argc ---------------------------- */

static void	test_argc(void)
{
	printf("\n--- check_argc (value = args after program name) ---\n");
	expect("0 args   -> error", check_argc(0), PARSING_ERROR);
	expect("1 arg    -> error (too few)", check_argc(1), PARSING_ERROR);
	expect("7 args   -> error (scheduler missing)", check_argc(7),
		PARSING_ERROR);
	expect("8 args   -> OK", check_argc(8), OK);
	expect("9 args   -> error (too many)", check_argc(9), PARSING_ERROR);
	expect("100 args -> error (too many)", check_argc(100), PARSING_ERROR);
}

/* ---------------------------- check_argv ---------------------------- */

static void	test_argv_valid(void)
{
	char	*list[9];
	char	big[16];

	printf("\n--- check_argv: valid input ---\n");
	fill(list);
	expect("typical values with fifo", check_argv(list), OK);
	list[7] = "edf";
	expect("typical values with edf", check_argv(list), OK);
	fill(list);
	list[0] = "1";
	expect("1 coder is valid (subject allows it)", check_argv(list), OK);
	snprintf(big, sizeof(big), "%d", MAX_NBR_CODERS);
	list[0] = big;
	expect("coders == MAX_NBR_CODERS", check_argv(list), OK);
	fill(list);
	list[1] = "2147483647";
	list[2] = "2147483647";
	list[3] = "2147483647";
	list[4] = "2147483647";
	list[5] = "2147483647";
	list[6] = "2147483647";
	expect("every time/count field == INT_MAX", check_argv(list), OK);
}

static void	test_argv_coders(void)
{
	char	*list[9];
	char	big[16];

	printf("\n--- check_argv: number_of_coders ---\n");
	fill(list);
	snprintf(big, sizeof(big), "%d", MAX_NBR_CODERS + 1);
	list[0] = big;
	expect("coders == MAX_NBR_CODERS + 1 -> error", check_argv(list),
		PARSING_ERROR);
	fill(list);
	list[0] = "0";
	expect("coders == 0 -> error (my reading: no coders, no simulation)",
		check_argv(list), PARSING_ERROR);
}

static void	test_argv_bad_everywhere(void)
{
	char	*list[9];
	char	*bad[8];
	char	label[96];
	int		pos;
	int		b;

	printf("\n--- check_argv: bad value in every numeric position ---\n");
	bad[0] = "-1";
	bad[1] = "abc";
	bad[2] = "";
	bad[3] = "5.5";
	bad[4] = "12a";
	bad[5] = "2147483648";
	bad[6] = "99999999999";
	bad[7] = NULL;
	pos = 0;
	while (pos < 7)
	{
		b = 0;
		while (bad[b])
		{
			fill(list);
			list[pos] = bad[b];
			snprintf(label, sizeof(label), "arg %d = \"%s\" -> error",
				pos + 1, bad[b]);
			expect(label, check_argv(list), PARSING_ERROR);
			b++;
		}
		pos++;
	}
}

static void	test_argv_null(void)
{
	printf("\n--- check_argv: NULL list ---\n");
	expect("NULL list -> error", check_argv(NULL), PARSING_ERROR);
}

/* --------------------- input_checks (scheduler + modes) -------------- */

static int	run_with_scheduler(char *sched)
{
	char	*argv[10];

	argv[0] = "codexion";
	argv[1] = "5";
	argv[2] = "800";
	argv[3] = "200";
	argv[4] = "200";
	argv[5] = "200";
	argv[6] = "3";
	argv[7] = "10";
	argv[8] = sched;
	argv[9] = NULL;
	return ((int)input_checks(9, argv));
}

static void	test_scheduler(void)
{
	char	label[96];
	char	*bad[8];
	int		b;

	printf("\n--- input_checks: scheduler (must be exactly fifo or edf) ---\n");
	expect("\"fifo\" -> OK", run_with_scheduler("fifo"), OK);
	expect("\"edf\"  -> OK", run_with_scheduler("edf"), OK);
	bad[0] = "FIFO";
	bad[1] = "EDF";
	bad[2] = "Fifo";
	bad[3] = "";
	bad[4] = "priority";
	bad[5] = "fifo ";
	bad[6] = "5";
	bad[7] = NULL;
	b = 0;
	while (bad[b])
	{
		snprintf(label, sizeof(label), "\"%s\" -> error", bad[b]);
		expect(label, run_with_scheduler(bad[b]), PARSING_ERROR);
		b++;
	}
}

static void	test_input_checks_counts(void)
{
	char	*seven[9];
	char	*nine[11];

	printf("\n--- input_checks: argument counts (argc includes program) ---\n");
	seven[0] = "codexion";
	seven[1] = "5";
	seven[2] = "800";
	seven[3] = "200";
	seven[4] = "200";
	seven[5] = "200";
	seven[6] = "3";
	seven[7] = "10";
	seven[8] = NULL;
	expect("7 args (no scheduler) -> error",
		(int)input_checks(8, seven), PARSING_ERROR);
	nine[0] = "codexion";
	nine[1] = "5";
	nine[2] = "800";
	nine[3] = "200";
	nine[4] = "200";
	nine[5] = "200";
	nine[6] = "3";
	nine[7] = "10";
	nine[8] = "fifo";
	nine[9] = "extra";
	nine[10] = NULL;
	expect("9 args (one extra) -> error",
		(int)input_checks(10, nine), PARSING_ERROR);
}

static void	test_single_string_mode(void)
{
	char	*argv[3];

	printf("\n--- input_checks: all args in one quoted string (argc == 2) ---\n");
	argv[0] = "codexion";
	argv[2] = NULL;
	argv[1] = "5 800 200 200 200 3 10 fifo";
	expect("one string, 8 values -> OK", (int)input_checks(2, argv), OK);
	argv[1] = "5 800 200 200 200 3 10";
	expect("one string, 7 values -> error", (int)input_checks(2, argv),
		PARSING_ERROR);
	argv[1] = "5 800 200 200 200 3 10 fifo extra";
	expect("one string, 9 values -> error", (int)input_checks(2, argv),
		PARSING_ERROR);
	argv[1] = "5 800 abc 200 200 3 10 fifo";
	expect("one string, non-number -> error", (int)input_checks(2, argv),
		PARSING_ERROR);
}

int	input_tests_main(void)
{
	test_argc();
	test_argv_valid();
	test_argv_coders();
	test_argv_bad_everywhere();
	test_argv_null();
	test_scheduler();
	test_input_checks_counts();
	test_single_string_mode();
	printf("\n%d tests run, %d failed\n", g_run, g_failed);
	return (g_failed != 0);
}
