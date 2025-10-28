#!/bin/bash
# Test redirections complexes - Cas avancés tirés du PDF

echo "=== Test Redirections Complexes ==="

# Redirections multiples valides
echo -e "\n--- Redirections multiples ---"
multiple_redir=(
    "echo hello > out.txt"
    "echo hello >> out.txt" 
    "cat < input.txt > output.txt"
    "echo test > file1.txt > file2.txt"
    "cat < file1.txt < file2.txt > result.txt"
    "echo hello > out.txt >> out.txt"
    "echo hello >> out.txt > out.txt"
)

for cmd in "${multiple_redir[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Redirections avec espaces
echo -e "\n--- Redirections avec espaces ---"
spaces_redir=(
    "echo hello >out.txt"
    "echo hello> out.txt" 
    "cat <input.txt"
    "cat< input.txt"
    "echo hello>out.txt"
    "cat<input.txt"
)

for cmd in "${spaces_redir[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Redirections avec pipes
echo -e "\n--- Redirections avec pipes ---"
pipe_redir=(
    "ls -l | grep txt > output.txt"
    "cat < input.txt | sort | uniq > result.txt"
    "echo hello | cat > output.txt"
    "ls | cat < input.txt"
)

for cmd in "${pipe_redir[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Redirections avec variables
echo -e "\n--- Redirections avec variables ---"
var_redir=(
    "echo hello > \$HOME/test.txt"
    "cat < \$HOME/input.txt" 
    "echo test > \$NONEXISTENT"
)

for cmd in "${var_redir[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Cas edge redirections
echo -e "\n--- Cases edge redirections ---"
edge_redir=(
    "> output.txt"
    "< input.txt"
    "< input.txt > output.txt"
    ">>output.txt"
    "<<EOF"
)

for cmd in "${edge_redir[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Redirections avec quotes
echo -e "\n--- Redirections avec quotes ---"
quote_redir=(
    "echo hello > 'out.txt'"
    'echo hello > "out.txt"'
    "cat < 'input.txt'"
    'cat < "input.txt"'
)

for cmd in "${quote_redir[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done