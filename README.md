MINISHELL - Documentation Interface Parser

Vue d'ensemble
Ce parser traite une ligne de commande et génère un AST (Abstract Syntax Tree) prêt pour l'exécution.

Flow principal :
Input → lexer_split() → validate_syntax() → expand_tokens() → parse_tokens() → AST

Structures de données
t_node - Nœud de l'AST
typedef struct s_node
{
    t_node_type type;        // NODE_COMMAND ou NODE_PIPE
    struct s_node *left;     // Nœud gauche (pour pipes)
    struct s_node *right;    // Nœud droit (pour pipes)
    t_command *command;      // Données de commande (si type = NODE_COMMAND)
} t_node;

Types possibles :
•	NODE_COMMAND : Commande simple
•	NODE_PIPE : Pipe entre deux commandes

t_command - Données d'une commande
typedef struct s_command
{
    char **argv;            // Arguments de la cmd (argv[0] = nom commande, NULL-terminated)
    t_redirect *redir;      // Liste chaînée des redirections (peut être NULL)
} t_command;

t_redirect - Redirection
typedef struct s_redirect
{
    int type;                    // REDIR_IN, REDIR_OUT, REDIR_APPEND, REDIR_HEREDOC
    char *filename;              // Nom du fichier ou délimiteur heredoc
    struct s_redirect *next;     // Redirection suivante (NULL si dernière)
} t_redirect;

Types de redirections :
typedef enum e_redir_type
{
    REDIR_IN = 1,            // <  (input)
    REDIR_OUT,               // >  (output, écrase)
    REDIR_APPEND,        // >> (output, ajoute)
    REDIR_HEREDOC      // << (heredoc)
} t_redir_type;

t_expand_ctx - Contexte d'expansion
typedef struct s_expand_ctx
{
    char **env;              // Tableau des variables d'environnement
    int last_exit_code;      // Code de retour dernière commande ($?)
} t_expand_ctx;
 
Fonctions principales
Parsing  =
lexer_split()
char **lexer_split(char *line);
•	Entrée : Ligne de commande brute
•	Sortie : Tableau de tokens (NULL-terminated) ou NULL si erreur
•	Erreurs : Retourne NULL si quotes non fermées ou malloc failed

validate_syntax()
int validate_syntax(char **tokens);
•	Entrée : Tableau de tokens
•	Sortie : 1 si syntaxe valide, 0 sinon
•	Vérifie : Pipes et redirections valides

expand_tokens()
char **expand_tokens(char **tokens, t_expand_ctx *ctx);
•	Entrée : Tokens bruts + contexte d'expansion
•	Sortie : Tokens avec variables expandées (nouveau tableau)
•	Gère : $VAR,$?, contextes de quotes

parse_tokens()
t_node *parse_tokens(char **tokens);
•	Entrée : Tokens expandés et validés
•	Sortie : Racine de l'AST ou NULL si erreur
•	Crée : Structure complète de l'arbre

Libération mémoire
free_node()
void free_node(t_node *node);
•	Libère récursivement : Tout l'AST (nodes, commands, redirections, argv)

free_tokens()
void free_tokens(char **tokens);
•	Libère : Tableau de tokens
 
Structure de l'AST - Exemples
Commande simple
Input: "echo hello"

AST:
NODE_COMMAND
├── argv = ["echo", "hello", NULL]
└── redir = NULL
Commande avec redirection
Input: "cat < input.txt > output.txt"

AST:
NODE_COMMAND
├── argv = ["cat", NULL]
└── redir → [type=REDIR_IN, file="input.txt", next→]
            [type=REDIR_OUT, file="output.txt", next=NULL]

Pipe multiple
Input: "ls | grep txt | wc -l"

AST:
NODE_PIPE
├── left = NODE_PIPE
│   ├── left = NODE_COMMAND ["ls"]
│   └── right = NODE_COMMAND ["grep", "txt"]
└── right = NODE_COMMAND ["wc", "-l"]
Pipe avec redirections
Input: "ls -l | grep txt > output.txt"

AST:
NODE_PIPE
├── left = NODE_COMMAND ["ls", "-l"]
└── right = NODE_COMMAND ["grep", "txt"]
    └── redir → [type=REDIR_OUT, file="output.txt"]
 
Parcours de l'AST
Identifier le type de nœud
if (node->type == NODE_COMMAND)
{
    // Exécuter la commande
    execute_command(node->command);
}
else if (node->type == NODE_PIPE)
{
    // Traiter le pipe récursivement
    execute_pipe(node->left, node->right);
}


Accéder aux arguments
if (node->type == NODE_COMMAND && node->command && node->command->argv)
{
    char **args = node->command->argv;
    char *cmd_name = args[0];  // Nom de la commande
    
    // Parcourir tous les arguments
    int i = 0;
    while (args[i])
    {
        printf("Arg %d: %s\n", i, args[i]);
        i++;
    }
}

Gestion des erreurs
Messages d'erreur
•	"Lexer error : quotes not closed or failed malloc": Quotes non fermées ou problème mémoire
•	"Syntax error" : Pipes ou redirections invalides

Codes de retour
•	NULL : Échec du parsing/lexing/expansion
•	Pointeur valide : Opération réussie
 
Expansion des variables
Variables supportées
•	$VAR : Variables d'environnement (ex: $USER, $HOME)
•	$? : Code de retour dernière commande

Contextes de quotes
•	Single quotes'…': Pas d'expansion, tout est littéral
•	Double quotes "…" : Expansion des variables activée

Exemples :
bash
$ echo '$USER'     → $USER (pas d'expansion)
$ echo "$USER"     → sdossa (expansion)

Mécanisme technique
1.	Lexer : Détecte les single quotes et ajoute un marqueur \x01 au début du token
2.	Expansion : Détecte le marqueur et skip l'expansion pour ces tokens
3.	Double quotes : Pas de marqueur, donc expansion normale
<img width="454" height="713" alt="image" src="https://github.com/user-attachments/assets/f65f238b-bb79-4df2-b0a0-0ddab7545cdb" />
