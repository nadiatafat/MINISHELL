#!/bin/bash
# Test rapide expansion des variables
echo "=== Test expansion des variables ==="

tests=(
    "echo \$USER"
    "echo \$HOME"
    "echo \$?"
    "echo \$NONEXISTENT"
    "echo \"Hello \$USER\""
    "echo '\$USER'"
    "echo \$USER/\$HOME"
)

for cmd in "${tests[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done