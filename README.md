## MINISHELL


## Description  
Minishell est un projet en langage C visant à **reproduire le fonctionnement d’un terminal Unix** de base.    
Le but est de comprendre et de mettre en œuvre les mécanismes d’un shell : lecture de ligne de commande, exécution de processus, gestion des redirections, pipelines, etc.

le project a été testé et concus sur un systeme macos

## Fonctionnalités  
### ✅ Implémentées  
- Parsing de la ligne de commande  
- Exécution de programmes externes (via `execve`)  
- Gestion des chemins (`PATH`)  
- Redirections d’entrée et de sortie (`<`, `>`, `>>`)
- gestion des processus
- Pipelines (`|`)  
- Commandes internes basiques / Builtins (`cd`, `echo`, `exit`, etc)  
- Gestion des signaux (CTRL-C, CTRL-D…)  

## Technologies & architecture  
- Langage : C  
- Makefile pour automatiser la compilation  
- Structure du projet :  
  - `inc/` : fichiers d’en-tête  
  - `src/` : fichiers sources  
  - `Lib/Libft/` : librairie personnelle (libft)  
- Respect des conventions de codage (norme, indentation, etc)  

## Installation / Compilation  
clone the repository
```bash
$ git clone https://github.com/Zkevitz/minishell.git
$ cd minishell
$ make
```

si vous n'avez pas Readline d'instaler :   
`sudo apt update
sudo apt install libreadline-dev
`

run the program
`./minishell`


## Auteurs 

Travail réalisé dans le cadre de notre cursus a 42 Bruxelles 
- **Rheck** - [Github](https://github.com/Robthebob34)
- **Mgigot** - [Github](https://github.com/Zkevitz)
