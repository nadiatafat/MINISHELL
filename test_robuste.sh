#!/bin/bash
# Test de robustesse - Inputs malformés et cases edge pour détecter les crashes

echo "=== Test de Robustesse ==="

# Variables malformées
echo -e "\n--- Variables malformées ---"
malformed_vars=(
    "echo \$"
    "echo \$\$\$\$\$\$\$"
    "echo \$\$HOME\$\$"
    "echo \$@#%^&*()"
    "echo \$12345678901234567890"
)

for cmd in "${malformed_vars[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Quotes malformées simples
echo -e "\n--- Quotes malformées ---"
malformed_quotes=(
    'echo """""""""""""""'
    "echo '''''''''''''''"
)

for cmd in "${malformed_quotes[@]}"; do
    echo -e "\n>>> [QUOTES RÉPÉTÉES]"
    echo "$cmd" | ./minishell
done

# Redirections malformées extrêmes
echo -e "\n--- Redirections malformées ---"
malformed_redir=(
    "echo > > > > > >"
    "echo < < < < < <"
    "echo >>>>>>>>>>>>>>"
    "echo <<<<<<<<<<<<<<<"
    "echo > ''"
    'echo > ""'
)

for cmd in "${malformed_redir[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Pipes malformés extrêmes
echo -e "\n--- Pipes malformés ---"
malformed_pipes=(
    "echo | | | | | | |"
    "| | | echo hello | | |"
    "echo |||||||||||||"
)

for cmd in "${malformed_pipes[@]}"; do
    echo -e "\n>>> $cmd"
    echo "$cmd" | ./minishell
done

# Inputs vides et caractères spéciaux simples
echo -e "\n--- Inputs spéciaux ---"
special_inputs=(
    ""
    "   "
    "echo \$\$\$\$\$"
    "echo \$"
    "echo \$\$"
    "\$\$\$\$\$"
    ";"
    "&"
)

for cmd in "${special_inputs[@]}"; do
    echo -e "\n>>> [INPUT SPÉCIAL]"
    echo "$cmd" | ./minishell
done

echo -e "\n=== Test de robustesse terminé ==="
echo "Si aucun crash n'est apparu, ton parser est robuste !"