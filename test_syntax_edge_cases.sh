#!/bin/bash
# Test cases edge syntaxe - Validation des erreurs détectées par le parser

echo "=== Test Cases Edge Syntaxe ==="

# Tests qui DOIVENT être détectés comme "Syntax error"
syntax_errors=(
    # Redirections invalides
    ">"
    "<"
    ">>"
    "<<"
    "<>"
    ">>>>>"
    "<<<<<"
    "> > > >"
    ">> >> >> >>"
    ">>|><"
    
    # Pipes invalides  
    "|"
    "| hola"
    "| | |"
    "||"
    "|||||"
    "echo > <"
    "echo | |"
    
    # Combinaisons invalides
    "echo hola ||| cat"
    "ls |"
    "| ls"
    "cat < |"
    "echo >"
    "cat <"
    "ls >>"
    "echo > >"
)

echo -e "\n--- Tests erreurs syntaxe (doivent afficher 'Syntax error') ---"
for cmd in "${syntax_errors[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Tests qui NE DOIVENT PAS être des erreurs syntaxe
valid_syntax=(
    # Commandes vides ou espaces (pas d'erreur syntaxe)
    ""
    "   "
    "        "
    
    # Commandes valides
    "echo hello"
    "echo hello world"
    "echo hello | cat"
    "cat < input.txt"
    "echo hello > output.txt"
    "echo hello >> output.txt"
    "cat << EOF"
    "ls -l | grep txt"
)

echo -e "\n--- Tests syntaxe valide (ne doivent PAS afficher 'Syntax error') ---"
for cmd in "${valid_syntax[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Tests spéciaux - Lexer errors (quotes non fermées)
echo -e "\n--- Tests Lexer errors (quotes non fermées) ---"
lexer_errors=(
    'echo "'
    "echo '"
    'echo "hello'
    "echo 'world"
)

for cmd in "${lexer_errors[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done